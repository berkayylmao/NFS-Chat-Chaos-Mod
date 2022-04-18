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
#include "Extensions/Game/MW05/Modifiers/InputModifier.hpp"

namespace Extensions::Game::MW05::Effects {
  namespace details::MirrorPort {
    static constexpr std::uintptr_t sBack   = 0x6CF545;
    static constexpr std::uintptr_t sInner  = 0x7C4B80;
    static inline float             sFactor = -1.0f;

    static void __declspec(naked) detour() {
      _asm {
        fmul sFactor
        call [sInner]
        jmp [sBack]
      }
    }
  }  // namespace details::MirrorPort

  class MirrorPort : public IGameEffect {
    std::unique_ptr<MemoryEditor::Editor::DetourInfo> mDetour;

   protected:
    virtual bool _activate() noexcept override {
      mDetour                          = MemoryEditor::Get().Detour(0x6CF540, reinterpret_cast<std::uintptr_t>(&details::MirrorPort::detour));
      OpenMW::Variables::PrecullerMode = false;
      Modifiers::InputModifier::Get().SetInvertedSteering(true);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      mDetour->Undetour();
      mDetour.reset();
      OpenMW::Variables::PrecullerMode = true;
      Modifiers::InputModifier::Get().SetInvertedSteering(false);
      return true;
    }

   public:
    explicit MirrorPort() : IGameEffect(114), mDetour(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects
