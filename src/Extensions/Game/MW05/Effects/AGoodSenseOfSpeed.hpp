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
  namespace details::AGoodSenseOfSpeed {
    namespace H {
      static constexpr std::uintptr_t sBack   = 0x6CF574;
      static inline float             sFactor = 1.0f;

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
      static inline float             sFactor = 1.0f;

      static void __declspec(naked) detour() {
        _asm {
          fmul sFactor
          call [sInner]
          jmp [sBack]
        }
      }
    }  // namespace V
  }    // namespace details::AGoodSenseOfSpeed

  class AGoodSenseOfSpeed : public IGameEffect {
    std::unique_ptr<MemoryEditor::Editor::DetourInfo> mDetourH;
    std::unique_ptr<MemoryEditor::Editor::DetourInfo> mDetourV;

   protected:
    virtual bool _activate() noexcept override {
      mDetourH = MemoryEditor::Get().Detour(0x6CF56C, reinterpret_cast<std::uintptr_t>(&details::AGoodSenseOfSpeed::H::detour));
      mDetourV = MemoryEditor::Get().Detour(0x6CF57E, reinterpret_cast<std::uintptr_t>(&details::AGoodSenseOfSpeed::V::detour));
      return true;
    }
    virtual bool _deactivate() noexcept override {
      mDetourH->Undetour();
      mDetourV->Undetour();
      mDetourH.reset();
      mDetourV.reset();
      return true;
    }

    virtual void _activeTick() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return;

      auto speed                             = pvehicle->GetSpeed();
      details::AGoodSenseOfSpeed::H::sFactor = 1.0f;
      details::AGoodSenseOfSpeed::V::sFactor = 1.0f;
      if (speed > 20.0f) {
        details::AGoodSenseOfSpeed::H::sFactor /= std::min(10.0f, (speed / 180.0f) * 10.0f);
        details::AGoodSenseOfSpeed::V::sFactor *= std::min(1.75f, std::max(1.0f, (speed / 180.0f) * 5.0f));
      }
    }

   public:
    explicit AGoodSenseOfSpeed() : IGameEffect(109), mDetourH(nullptr), mDetourV(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects
