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
#include "Extensions/Game/MW05/Modifiers/CarScaleModifier.hpp"

namespace Extensions::Game::MW05::Effects {
  class DontLookBackInAnger : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      MemoryEditor::Get().UnlockMemory(0x6B6890, 4);
      *reinterpret_cast<std::uint32_t*>(0x6B6890) = 0xC301F083;
      MemoryEditor::Get().LockMemory(0x6B6890);

      Modifiers::CarScaleModifier::Get().AddModifier(Modifiers::CarScaleModifier::Modifier::FlippedCars);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      MemoryEditor::Get().UnlockMemory(0x6B6890, 4);
      *reinterpret_cast<std::uint32_t*>(0x6B6890) = 0x02DC81D9;
      MemoryEditor::Get().LockMemory(0x6B6890);

      Modifiers::CarScaleModifier::Get().RemoveModifier(Modifiers::CarScaleModifier::Modifier::FlippedCars);
      return true;
    }

   public:
    explicit DontLookBackInAnger() : IGameEffect(19) {}
  };
}  // namespace Extensions::Game::MW05::Effects
