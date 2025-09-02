/*
// clang-format off
//
//    NFS Chaos Mod (NFS-Chat-Chaos-Mod)
//    Copyright (C) 2025 Berkay Yiğit <contact@withberkay.com>
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
  namespace details::Squeezy {
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
  }  // namespace details::Squeezy

  class Squeezy : public IGameEffect {
    std::unique_ptr<MemoryEditor::Editor::DetourInfo> mDetour;

   protected:
    virtual bool _activate() noexcept override {
      mDetour = MemoryEditor::Get().Detour(0x6CF56C, reinterpret_cast<std::uintptr_t>(&details::Squeezy::detour));
      return true;
    }
    virtual bool _deactivate() noexcept override {
      mDetour->Undetour();
      mDetour.reset();
      return true;
    }

    virtual void _activeTick() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return;

      auto speed                = pvehicle->GetSpeed();
      details::Squeezy::sFactor = 1.0f;
      if (speed > 20.0f) details::Squeezy::sFactor /= std::min(10.0f, (speed / 180.0f) * 10.0f);
    }

   public:
    explicit Squeezy() : IGameEffect(111), mDetour(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects
