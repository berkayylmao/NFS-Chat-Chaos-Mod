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
  class DriveOrDie : public IGameEffect {
    bool mAlreadyBlewEngine;

   protected:
    virtual bool _activate() noexcept override {
      if (OpenMW::GameStatusEx::SecondsSinceStartedRacing() < 10 && OpenMW::GameStatusEx::SecondsSinceStartedRoaming() < 10) return false;

      mAlreadyBlewEngine = false;
      return true;
    }

    virtual void _activeTick() noexcept override {
      if (mAlreadyBlewEngine) return;

      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      auto* input = player_vehicle->mInput | OpenMW::InputEx::AsInputPlayer;
      if (!input) return;

      // Check gas/blow engine
      if (input->GetControls().mGas < 0.9f) {
        OpenSpeed::MW05::Game::BlowEngine(player_vehicle);
        mAlreadyBlewEngine = true;
      }
    }

   public:
    explicit DriveOrDie() : IGameEffect(46), mAlreadyBlewEngine(false) {}
  };
}  // namespace Extensions::Game::MW05::Effects
