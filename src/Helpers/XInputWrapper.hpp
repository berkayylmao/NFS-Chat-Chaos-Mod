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
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
// XInput
#include <Xinput.h>

#include <chrono>
using namespace std::chrono_literals;

#include <cmath>
#include <cstdint>
#include <unordered_map>
#include <thread>
#pragma warning(pop)

class XInputWrapper {
 public:
  struct StickInfo {
    float x, y;

    StickInfo() : x(0.0f), y(0.0f) {}
  };

  enum class KeyStatus : std::uint8_t { None, Down, Up, Held };

 private:
  // Updater thread
  std::thread mUpdaterThread;
  bool        mKeepRunningUpdater;

  // Controller info
  std::int32_t mMainControllerPort;
  XINPUT_STATE mControllerState;
  // Keys
  const std::unordered_map<std::uint32_t, std::uint32_t> mKeyMap;
  mutable std::unordered_map<std::uint32_t, KeyStatus>   mKeyStrokes;

  // Stick info
  StickInfo mLeftSick;
  StickInfo mRightSick;

  // Trigger info
  float mLeftTrigger;
  float mRightTrigger;

 private:
  bool CheckPort() {
    if (mMainControllerPort != -1 && XInputGetState(mMainControllerPort, &mControllerState) == ERROR_SUCCESS) return true;

    mMainControllerPort = -1;
    for (std::size_t i = 0; i < XUSER_MAX_COUNT; i++) {
      if (XInputGetState(i, &mControllerState) == ERROR_SUCCESS) {
        mMainControllerPort = i;
        return true;
      }
    }

    return false;
  }

  void Refresh() {
    while (mKeepRunningUpdater) {
      std::this_thread::sleep_for(10ms);

      // Reset old data
      ZeroMemory(&mControllerState, sizeof(XINPUT_STATE));
      ZeroMemory(&mLeftSick, sizeof(StickInfo));
      ZeroMemory(&mRightSick, sizeof(StickInfo));
      mLeftTrigger  = 0.0f;
      mRightTrigger = 0.0f;

      // Ensure connection
      if (!CheckPort() || mMainControllerPort == -1) continue;

      // Left stick
      {
        std::int16_t left_x = std::clamp(mControllerState.Gamepad.sThumbLX, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max());
        std::int16_t left_y = std::clamp(mControllerState.Gamepad.sThumbLY, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max());
        // Set values if thumb is inside standard deadzone
        if (std::abs(left_x) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) mLeftSick.x = static_cast<float>(left_x) / std::numeric_limits<std::int16_t>::max();
        if (std::abs(left_y) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) mLeftSick.y = static_cast<float>(left_y) / std::numeric_limits<std::int16_t>::max();
      }
      // Right stick
      {
        std::int16_t right_x =
            std::clamp(mControllerState.Gamepad.sThumbRX, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max());
        std::int16_t right_y =
            std::clamp(mControllerState.Gamepad.sThumbRY, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max());
        // Set values if thumb is inside standard deadzone
        if (std::abs(right_x) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) mRightSick.x = static_cast<float>(right_x) / std::numeric_limits<std::int16_t>::max();
        if (std::abs(right_y) > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) mRightSick.y = static_cast<float>(right_y) / std::numeric_limits<std::int16_t>::max();
      }
      // Left trigger
      if (mControllerState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        mLeftTrigger = static_cast<float>(mControllerState.Gamepad.bLeftTrigger) / 255.0f;
      // Right trigger
      if (mControllerState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
        mRightTrigger = static_cast<float>(mControllerState.Gamepad.bRightTrigger) / 255.0f;

      // Buttons
      static XINPUT_KEYSTROKE key;
      while (true) {
        ZeroMemory(&key, sizeof(XINPUT_KEYSTROKE));
        auto val = XInputGetKeystroke(mMainControllerPort, NULL, &key);
        if (val != ERROR_SUCCESS) break;

        KeyStatus status = KeyStatus::None;
        if (key.Flags & XINPUT_KEYSTROKE_KEYDOWN)
          status = KeyStatus::Down;
        else if (key.Flags & XINPUT_KEYSTROKE_KEYUP)
          status = KeyStatus::Up;
        else if (key.Flags & XINPUT_KEYSTROKE_REPEAT)
          status = KeyStatus::Held;

        mKeyStrokes[key.VirtualKey] = status;
      }
    }
  }

  void StartUpdater() {
    mKeepRunningUpdater = true;
    mUpdaterThread      = std::thread(&XInputWrapper::Refresh, this);
    mUpdaterThread.detach();
  }
  void StopUpdater() {
    mKeepRunningUpdater = false;
    mUpdaterThread.join();
  }

 public:
  bool                IsConnected() const { return mMainControllerPort != -1; }
  const XINPUT_STATE& GetState() const { return mControllerState; }
  const StickInfo&    GetLeftStick() const { return mLeftSick; }
  const StickInfo&    GetRightStick() const { return mRightSick; }
  const float&        GetLeftTrigger() const { return mLeftTrigger; }
  const float&        GetRightTrigger() const { return mRightTrigger; }
  KeyStatus           GetKeyState(std::uint32_t buttonId) const {
    auto it = mKeyMap.find(buttonId);
    if (it == std::cend(mKeyMap)) return KeyStatus::None;

    auto ret                = mKeyStrokes[it->second];
    mKeyStrokes[it->second] = KeyStatus::None;
    return ret;
  }

  bool Rumble(float lowFreqMotor = 0.5f, float highFreqMotor = 0.25f) const {
    if (!this->IsConnected()) return false;

    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed  = static_cast<std::uint16_t>(lowFreqMotor * static_cast<float>(UINT16_MAX));
    vibration.wRightMotorSpeed = static_cast<std::uint16_t>(highFreqMotor * static_cast<float>(UINT16_MAX));
    XInputSetState(mMainControllerPort, &vibration);
    return true;
  }
  bool StopRumble() const { return Rumble(0.0f, 0.0f); }

 private:
  XInputWrapper() :
      mKeepRunningUpdater(true),
      mMainControllerPort(-1),
      mKeyMap({{XINPUT_GAMEPAD_A, VK_PAD_A},
               {XINPUT_GAMEPAD_B, VK_PAD_B},
               {XINPUT_GAMEPAD_X, VK_PAD_X},
               {XINPUT_GAMEPAD_Y, VK_PAD_Y},
               {XINPUT_GAMEPAD_DPAD_UP, VK_PAD_DPAD_UP},
               {XINPUT_GAMEPAD_DPAD_RIGHT, VK_PAD_DPAD_RIGHT},
               {XINPUT_GAMEPAD_DPAD_DOWN, VK_PAD_DPAD_DOWN},
               {XINPUT_GAMEPAD_DPAD_LEFT, VK_PAD_DPAD_LEFT},
               {XINPUT_GAMEPAD_LEFT_SHOULDER, VK_PAD_LSHOULDER},
               {XINPUT_GAMEPAD_RIGHT_SHOULDER, VK_PAD_RSHOULDER},
               {XINPUT_GAMEPAD_BACK, VK_PAD_BACK},
               {XINPUT_GAMEPAD_START, VK_PAD_START}}) {
    StartUpdater();
  }

 public:
  ~XInputWrapper() { StopUpdater(); }
  XInputWrapper(const XInputWrapper&) = delete;
  void operator=(const XInputWrapper&) = delete;

  static XInputWrapper& Get() {
    static XInputWrapper singleton;
    return singleton;
  }
};
