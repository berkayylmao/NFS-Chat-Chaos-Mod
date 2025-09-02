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

namespace Extensions::Game::Carbon::Effects {
  class YoBroIsThatASupra : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return !OpenCarbon::GameStatusEx::IsInPursuit(); }

    virtual bool _activate() noexcept override {
      auto car_key = OpenCarbon::Attrib::StringToKey("supra");

      auto instance = OpenCarbon::Attrib::Gen::pvehicle::TryGetInstance(car_key);
      if (!instance.mCollection) return false;

      // Install random parts
      OpenCarbon::RideInfo ride_info(OpenCarbon::CarType::TOYOTA_SUPRA);
      ride_info.SetStockParts();
      ride_info.SetRandomPaint();
      ride_info.SetRandomParts();
      OpenCarbon::VehicleCustomizations customizations;
      customizations.ReadFrom(ride_info);
      // Change car
      if (!OpenCarbon::PVehicleEx::ChangePlayerVehicle(car_key, &customizations)) return false;

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::YoBroIsThatASupra);
      return true;
    }

   public:
    explicit YoBroIsThatASupra() : IGameEffect(56) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
