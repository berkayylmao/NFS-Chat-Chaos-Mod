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
  class SuddentlyItsADragRace : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenCarbon::GameStatusEx::IsRacing(); }

    virtual bool _activate() noexcept override {
      OpenCarbon::PVehicleEx::ForEachInstance([](OpenCarbon::PVehicle* pvehicle) {
        auto gear_id = pvehicle->mTranny->GetGear();
        pvehicle->SetDriverStyle(OpenCarbon::DriverStyle::Drag);
        pvehicle->mTranny->Shift(gear_id);
      });

      return true;
    }
    virtual bool _deactivate() noexcept override {
      OpenCarbon::PVehicleEx::ForEachInstance([](OpenCarbon::PVehicle* pvehicle) { pvehicle->SetDriverStyle(OpenCarbon::DriverStyle::Racing); });
      return true;
    }

   public:
    explicit SuddentlyItsADragRace() : IGameEffect(44) {}
  };
}  // namespace Extensions::Game::MW05::Effects
