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
  class Stretched4by3 : public IGameEffect {
    static constexpr std::uintptr_t target = 0x6CF568;
    static constexpr float          fov    = 3.0f;

    std::uintptr_t mSavedAddress;

   protected:
    virtual bool _activate() noexcept override {
      MemoryEditor::Get().UnlockMemory(target, sizeof(std::uintptr_t));
      auto* p       = reinterpret_cast<std::uintptr_t*>(target);
      mSavedAddress = *p;
      *p            = reinterpret_cast<std::uintptr_t>(&fov);

      MemoryEditor::Get().LockMemory(target);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      MemoryEditor::Get().UnlockMemory(target, sizeof(std::uintptr_t));
      *reinterpret_cast<std::uintptr_t*>(target) = mSavedAddress;

      MemoryEditor::Get().LockMemory(target);
      return true;
    }

   public:
    explicit Stretched4by3() : IGameEffect(108), mSavedAddress(0) {}
  };
}  // namespace Extensions::Game::MW05::Effects
