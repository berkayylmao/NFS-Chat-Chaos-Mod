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

#pragma warning(push, 0)  // disable any warnings from external headers

// Win32 targeting
#include <WinSDKVer.h>
#define _WIN32_WINNT 0x0601  // _WIN32_WINNT_WIN7
#include <SDKDDKVer.h>
// Win32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
// Commonly used headers
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>  // size_t
#include <cstdint>  // integer types
#include <cstdlib>  // atexit()
#include <deque>
#include <filesystem>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// DirectInput8
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// d3dx9
#include <d3dx9.h>

// Dear ImGui
#include "Helpers/Dear ImGui/imgui.h"
#include "Helpers/Dear ImGui/imgui_internal.h"
#include "Helpers/Dear ImGui/backends/imgui_impl_dx9.h"
#include "Helpers/Dear ImGui/backends/imgui_impl_win32.h"
#include "Helpers/Dear ImGui/misc/freetype/imgui_freetype.h"

// fmt
#include "Helpers/fmt/format.h"

// MirrorHook
#include <MirrorHook.hpp>

// OpenSpeed
#include <OpenSpeed.h>
#include <OpenSpeed/Core/MemoryEditor/MemoryEditor.hpp>

using namespace std::chrono_literals;

#pragma warning(pop)  // restore warnings

#include "Helpers/Config.hpp"
#include "Helpers/FMODWrapper.hpp"
#include "Helpers/Random.hpp"
#include "Helpers/TwitchIRC.hpp"
#include "Helpers/XInputWrapper.hpp"

#include "Extensions/Game/IGameEffectsHandler.hpp"

// Mod info
#define __STR__(x)          #x
#define __STR_EXPAND__(x)   __STR__(x)
#define __MOD_VERSION__     1.2.5.78
#define __MOD_VERSION_STR__ __STR_EXPAND__(__MOD_VERSION__)

#define __CONCAT_INNER__(a, b) a##b
#define __CONCAT__(a, b)       __CONCAT_INNER__(a, b)

#define __EXECUTE_EVERY_X_SECONDS__(fSecond)                            \
  static float __CONCAT__(__seconds_passed__, __LINE__) = 0.0f;         \
  __CONCAT__(__seconds_passed__, __LINE__) += ImGui::GetIO().DeltaTime; \
  if (__CONCAT__(__seconds_passed__, __LINE__) < fSecond) return;       \
  __CONCAT__(__seconds_passed__, __LINE__) = 0.0f

// Global vars

namespace ChaosMod {
  static HMODULE g_ThisHandle          = nullptr;
  static bool    g_GameWindowLostFocus = false;

  static OpenSpeed::SpeedGame                                   g_CurSpeedGame       = OpenSpeed::SpeedGame::NotSupported;
  static std::unique_ptr<Extensions::Game::IGameEffectsHandler> g_GameEffectsHandler = nullptr;

  static float g_IdleTimerSeconds       = 5.0f;
  static float g_VoteTimerSeconds       = 20.0f;
  static float g_ActivationTimerSeconds = 2.0f;

  static inline const std::filesystem::path& GetChaosModDirectory() {
    static bool                  initted = false;
    static std::filesystem::path path;
    if (initted) return path;

    std::wstring str_path(2048, 0);
    GetModuleFileNameW(NULL, &str_path[0], 2047);
    path    = std::move(std::filesystem::path(str_path).parent_path() / "ChatChaosMod");
    initted = true;
    return path;
  }

  static inline const std::filesystem::path& GetSoundFXDirectory() {
    static bool                  initted = false;
    static std::filesystem::path path;
    if (initted) return path;

    path    = GetChaosModDirectory() / "SoundFX";
    initted = true;
    return path;
  }

  // Will block
  static inline LPDIRECT3DDEVICE9 GetD3D9Device() {
    static LPDIRECT3DDEVICE9 pD3D9_device = nullptr;
    if (pD3D9_device) return pD3D9_device;

    // Wait for D3D9 device
    {
      auto** _ppD3DDev = reinterpret_cast<LPDIRECT3DDEVICE9*>(OpenSpeed::GetInformationOfCurrentSpeedGame().ppD3DDevice);
      while (pD3D9_device == nullptr) {
        pD3D9_device = *_ppD3DDev;
        std::this_thread::sleep_for(1s);
      }
    }
    return pD3D9_device;
  }
}  // namespace ChaosMod
