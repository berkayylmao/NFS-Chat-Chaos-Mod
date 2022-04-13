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
#include "Extensions/D3D9/D3D9.Base.hpp"
#include "Extensions/DInput8/DInput8.hpp"
#include "Extensions/Game/MW05/GameEffectsHandler.hpp"
#include "Extensions/Game/Carbon/GameEffectsHandler.hpp"
#include "Extensions/WndProc/DontStopGameOnFocussLoss.hpp"
#include "Extensions/WndProc/WindowedModeImprovements.hpp"

namespace ChaosMod {
  inline void prepdebug() {
#ifdef _DEBUG
    AllocConsole();
    ::_CrtSetDbgFlag(::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_CHECK_ALWAYS_DF);

    switch (g_CurSpeedGame) {
      case OpenSpeed::SpeedGame::MW05:
        // SkipFE
        MemoryEditor::Get().UnlockMemory(0x926064, 4);
        *reinterpret_cast<bool*>(0x926064) = true;
        MemoryEditor::Get().LockMemory(0x926064);
        break;
      case OpenSpeed::SpeedGame::Carbon:
        // SkipFE
        MemoryEditor::Get().UnlockMemory(0xA9E620, 4);
        *reinterpret_cast<bool*>(0xA9E620) = true;
        MemoryEditor::Get().LockMemory(0xA9E620);
        break;
    }
#endif
  }

  inline void Init() {
    // Try to detect parent game
    {
      g_CurSpeedGame = OpenSpeed::GetCurrentSpeedGame();
      switch (g_CurSpeedGame) {
        case OpenSpeed::SpeedGame::U2:
          break;
        case OpenSpeed::SpeedGame::MW05:
          g_GameEffectsHandler = std::make_unique<Extensions::Game::MW05::GameEffectsHandler>();
          break;
        case OpenSpeed::SpeedGame::Carbon:
          g_GameEffectsHandler = std::make_unique<Extensions::Game::Carbon::GameEffectsHandler>();
          break;
        default:
          // No compatible game was found! Shutting down mod.
          return;
      }

      g_GameEffectsHandler->Init();
      prepdebug();
    }

    // D3D9 extensions
    Extensions::D3D9::Init();
    std::atexit(Extensions::D3D9::Shared::OnExit);

    // DI8 extensions
    Extensions::DInput8::Init();

    // WndProc extensions
    Extensions::WndProc::DontStopGameOnFocusLoss::Init();
    Extensions::WndProc::WindowedModeImprovements::Init();

    // Load effects
    g_GameEffectsHandler->SetupEffects();
    // Load modifiers
    g_GameEffectsHandler->SetupModifiers();
    // Init FMOD
    FMODWrapper::Get().InitSoundFXMap(ChaosMod::GetSoundFXDirectory());

    // Bring game to foreground
    auto hwnd = MirrorHook::WndProc::GetWindowHandle();
    ::SetForegroundWindow(hwnd);
    ::SetFocus(hwnd);
    ::BringWindowToTop(hwnd);
  }
}  // namespace ChaosMod
