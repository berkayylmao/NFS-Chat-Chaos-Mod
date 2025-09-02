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
  class FlashingCars : public IGameEffect {
    static constexpr std::uintptr_t target = 0x6B6FD9;

   protected:
    virtual bool _activate() noexcept override {
      MemoryEditor::Get().UnlockMemory(target, sizeof(std::uint16_t));
      *reinterpret_cast<std::uint16_t*>(target) = 0x0EEB;
      MemoryEditor::Get().LockMemory(target);

      return true;
    }
    virtual bool _deactivate() noexcept override {
      MemoryEditor::Get().UnlockMemory(target, sizeof(std::uint16_t));
      *reinterpret_cast<std::uint16_t*>(target) = 0x1274;
      MemoryEditor::Get().LockMemory(target);

      return true;
    }

   public:
    explicit FlashingCars() : IGameEffect(124) {}
  };
}  // namespace Extensions::Game::MW05::Effects
