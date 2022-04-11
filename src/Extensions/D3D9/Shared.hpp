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
#include "pch.h"

namespace Extensions::D3D9::Shared {
#pragma region TWITCH TALK
  /// TWITCH TALK

  // Object
  static std::unique_ptr<TwitchIRC::TwitchTalk> g_TwitchTalk;

  // Connection status
  // [IsConnecting, IsConnected]
  static std::pair<bool, bool> g_TwitchTalkStatus = {false, false};

  static inline void InitTwitchTalk(const std::function<void(bool isConnected)>&                 TWITCH_callbackConnect,
                                    const std::function<void(TwitchIRC::TwitchMessage message)>& TWITCH_callbackReceivedMessage) {
    g_TwitchTalk = std::make_unique<TwitchIRC::TwitchTalk>(TWITCH_callbackConnect, TWITCH_callbackReceivedMessage);
  }
#pragma endregion

#pragma region CHAOS
  /// CHAOS

#pragma region MODE
  /// MODE

  // Possible modes
  enum class ChaosMode : std::uint8_t { None, TwitchChat, SinglePlayer };

  static ChaosMode g_ChaosMode = ChaosMode::None;
#pragma endregion

#pragma region TIMER
  /// TIMER

  // Possible status values of the timer
  enum class TimerStatus : std::uint8_t { None, IdleTimer, VoteTimer, ActivationTimer };

  // Possible result values of the timer
  enum class TimerResult : std::uint8_t { None, IdleTimerCompleted, VoteTimerCompleted, ActivationTimerCompleted };

  // Current status of the timer
  static TimerStatus g_ChaosTimerStatus = TimerStatus::None;
#pragma endregion

  /// HELPERS

  // Called from 'D3D9.Base' when 'Start Chaos' is clicked
  static void StartChaos(bool isTwitch) {
    if (isTwitch) {
      if (!g_TwitchTalkStatus.second) return;
      g_ChaosMode = ChaosMode::TwitchChat;
    } else {
      g_ChaosMode = ChaosMode::SinglePlayer;
    }
    g_ChaosTimerStatus = TimerStatus::IdleTimer;
  }

  // Called every frame to check chaos' status
  static bool IsChaosRunning() { return g_ChaosTimerStatus != TimerStatus::None; }

#pragma endregion

#pragma region OnExit

  static void OnExit() {
    // Stop Chaos
    g_ChaosTimerStatus = TimerStatus::None;
    Game::IGameEffectsHandler::RemoveAllEffects();
    // Disconnect from Twitch
    g_TwitchTalkStatus = {false, false};
    g_TwitchTalk.reset();
  }

#pragma endregion
}  // namespace Extensions::D3D9::Shared
