/*
// clang-format off
//
//    NFS Chaos Mod (NFS-Chat-Chaos-Mod)
//    Copyright (C) 2022 Berkay Yigit <berkaytgy@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program. If not, see <https://www.gnu.org/licenses/>.
//
// clang-format on
*/

#pragma once
#pragma warning(push, 0)
#include <chrono>
using namespace std::chrono_literals;

#include <cstddef>  // size_t
#include <cstdint>  // integer types
#include <deque>
#include <functional>
#include <regex>
#include <string>
#include <thread>
// ASIO
#include <asio.hpp>
// fmt
#include "Helpers/fmt/format.h"
#pragma warning(pop)

namespace TwitchIRC {
  struct TwitchUser {
    std::uint64_t mId;
    bool          mIsSubscriber;

    TwitchUser() : mId(NULL), mIsSubscriber(false) {}
    TwitchUser(std::uint64_t id, bool isSubscriber) : mId(id), mIsSubscriber(isSubscriber) {}
  };
  struct TwitchMessage {
    TwitchUser  mSender;
    std::string mType;
    std::string mContent;

    TwitchMessage() = default;
    TwitchMessage(TwitchUser sender, const std::string& type, const std::string& content) : mSender(sender), mType(type), mContent(content) {}
  };

  class TwitchTalk {
    constexpr static char CONST_HOSTNAME[] = "irc.chat.twitch.tv";
    constexpr static char CONST_PORT[]     = "6667";  // SSL: 6697

    static inline const auto STATIC_regexMessage = std::regex(R"__(;badges=.*?;subscriber=(\d);.*;user-id=(\d+);.*tmi\.twitch\.tv ([0-z]+).* :(.*))__");

    std::thread                           mASIO_ctx_thread;
    asio::io_context                      mASIO_ctx;
    asio::ip::tcp::resolver::results_type mASIO_endpoints;

    std::thread           mASIO_socket_keepalive_thread;
    asio::ip::tcp::socket mASIO_socket;

    std::string                                mChannelName, mUsername, mUserOAuth;
    std::deque<std::string>                    mSendQueue;
    std::function<void(bool isConnected)>      mCallbackConnect;
    std::function<void(TwitchMessage message)> mCallbackReceivedMessage;
    std::string                                mLastReadMessage;

    void _closeSocket() {
      asio::post(mASIO_ctx, [&] {
        if (!mASIO_socket.is_open()) return;
        mASIO_socket.shutdown(asio::ip::tcp::socket::shutdown_both);
        mASIO_socket.close();

        mASIO_socket = asio::ip::tcp::socket(mASIO_ctx);
      });
    }

    void _keepalive() {
      while (mASIO_socket.is_open()) {
        std::this_thread::sleep_for(1min);
        _queueMessageToWrite("PING :tmi.twitch.tv\r\n");
      }
    }
    void _onConnected() {
      mCallbackConnect(true);
      mASIO_socket_keepalive_thread = std::thread([&]() { _keepalive(); });
    }
    void _onDisconnected() { mCallbackConnect(false); }

    void _recv() {
      asio::async_read_until(mASIO_socket, asio::dynamic_buffer(mLastReadMessage, 4096), '\n', [&](std::error_code ec, std::size_t lenMsg) {
        if (ec) {
          _closeSocket();
          _onDisconnected();
          return;
        }

        if (mLastReadMessage._Starts_with("PING :tmi.twitch.tv")) {
          _queueMessageToWrite("PONG :tmi.twitch.tv\r\n");
        } else {
          std::smatch m;
          if (std::regex_search(mLastReadMessage, m, STATIC_regexMessage) && m.size() == 5) {
            mCallbackReceivedMessage({{std::stoull(m[2].str()), m[1].compare("0") == 0}, m[3].str(), m[4].str()});
          }
        }
        mLastReadMessage.erase(0, lenMsg);
        _recv();
      });
    }
    void _send() {
      asio::async_write(mASIO_socket, asio::buffer(mSendQueue.front().data(), mSendQueue.front().length()), [&](std::error_code ec, std::size_t) {
        if (ec) {
          _closeSocket();
          _onDisconnected();
          return;
        }

        mSendQueue.pop_front();
        if (!mSendQueue.empty()) _send();
      });
    }

    void _queueMessageToWrite(const std::string& message) {
      asio::post(mASIO_ctx, [&, message]() {
        bool is_writing = !mSendQueue.empty();
        mSendQueue.push_back(message);
        if (!is_writing) _send();
      });
    }
    void _queueLoginMessages() {
      asio::post(mASIO_ctx, [&] {
        bool is_writing = !mSendQueue.empty();
        mSendQueue.push_back(fmt::format("PASS {}\r\n", mUserOAuth));
        mSendQueue.push_back(fmt::format("NICK {}\r\n", mUsername));
        mSendQueue.push_back(fmt::format("JOIN #{}\r\n", mChannelName));
        mSendQueue.push_back("CAP REQ :twitch.tv/tags twitch.tv/commands\r\n");
        if (!is_writing) _send();
      });
    }

   public:
    void SendMessageToChannel(const std::string& message) { _queueMessageToWrite(fmt::format("PRIVMSG #{} :{}\r\n", mChannelName, message)); }

    // Spawns a thread
    void StartTalk(const std::string& channelName, const std::string& username, const std::string& userOAuth) {
      mChannelName = channelName;
      mUsername    = username;
      mUserOAuth   = userOAuth;

      mASIO_ctx.stop();
      if (mASIO_ctx_thread.joinable()) mASIO_ctx_thread.join();

      asio::async_connect(mASIO_socket, mASIO_endpoints, [&](std::error_code ec, asio::ip::tcp::endpoint) {
        if (ec) {
          _closeSocket();
          _onDisconnected();
          return;
        }

        _queueLoginMessages();
        asio::async_read_until(mASIO_socket, asio::dynamic_buffer(mLastReadMessage, 4096), ":Welcome, GLHF!", [&](std::error_code ec, std::size_t lenMsg) {
          if (ec) {
            _closeSocket();
            _onDisconnected();
            return;
          }

          _onConnected();
          mLastReadMessage.erase(0, lenMsg);
          _recv();
        });
      });

      mASIO_ctx.restart();
      mASIO_ctx_thread = std::thread([&]() { mASIO_ctx.run(); });
    }
    void StopTalk() {
      if (mASIO_socket.is_open()) {
        _queueMessageToWrite(fmt::format("PART #{}\n", mChannelName));
        _closeSocket();
      }
    }

    TwitchTalk(const std::function<void(bool isConnected)>& callbackConnect, const std::function<void(TwitchMessage message)>& callbackReceivedMessage) :
        mCallbackConnect(callbackConnect), mCallbackReceivedMessage(callbackReceivedMessage), mASIO_socket(mASIO_ctx) {
      mLastReadMessage.reserve(8192);

      mASIO_endpoints = asio::ip::tcp::resolver(mASIO_ctx).resolve(CONST_HOSTNAME, CONST_PORT);
    }
    ~TwitchTalk() {
      mASIO_ctx.stop();
      if (mASIO_ctx_thread.joinable()) mASIO_ctx_thread.join();
      _closeSocket();
      if (mASIO_socket_keepalive_thread.joinable()) mASIO_socket_keepalive_thread.join();
      mASIO_ctx.restart();
      mASIO_ctx.poll_one();
      mASIO_ctx.run();
    }
  };
}  // namespace TwitchIRC
