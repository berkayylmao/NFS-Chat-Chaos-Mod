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
#include "Helpers/OpenSpeedEx.hpp"

namespace Extensions::Game::MW05::Effects {
  namespace details::InvisibleEverything {
    namespace H {
      static constexpr std::uintptr_t sBack   = 0x6CF574;
      static inline float             sFactor = 0.0f;

      static void __declspec(naked) detour() {
        _asm {
          fmul sFactor
          fstp dword ptr [esp+0x20]
          fild dword ptr [esp+0x30]
          jmp [sBack]
        }
      }
    }  // namespace H
    namespace V {
      static constexpr std::uintptr_t sBack   = 0x6CF583;
      static constexpr std::uintptr_t sInner  = 0x7C4B80;
      static inline float             sFactor = 0.0f;

      static void __declspec(naked) detour() {
        _asm {
          fmul sFactor
          call [sInner]
          jmp [sBack]
        }
      }
    }  // namespace V
  }    // namespace details::InvisibleEverything

  class InvisibleEverything : public IGameEffect {
    std::unique_ptr<MemoryEditor::Editor::DetourInfo> mDetourH;
    std::unique_ptr<MemoryEditor::Editor::DetourInfo> mDetourV;

   protected:
    virtual bool _activate() noexcept override {
      mDetourH = MemoryEditor::Get().Detour(0x6CF56C, reinterpret_cast<std::uintptr_t>(&details::InvisibleEverything::H::detour));
      mDetourV = MemoryEditor::Get().Detour(0x6CF57E, reinterpret_cast<std::uintptr_t>(&details::InvisibleEverything::V::detour));
      return true;
    }
    virtual bool _deactivate() noexcept override {
      mDetourH->Undetour();
      mDetourV->Undetour();
      mDetourH.reset();
      mDetourV.reset();
      return true;
    }

   public:
    explicit InvisibleEverything() : IGameEffect(113), mDetourH(nullptr), mDetourV(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects