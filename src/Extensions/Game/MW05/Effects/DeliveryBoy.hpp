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
  class DeliveryBoy : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return !OpenMW::GameStatusEx::IsInPursuit(); }

    virtual bool _activate() noexcept override {
      auto trafpizzza = std::pair<OpenMW::Attrib::StringKey, OpenMW::CarType>(OpenMW::Attrib::StringToKey("cs_clio_trafpizza"), OpenMW::CarType::PIZZA);
      auto instance   = OpenMW::Attrib::Gen::pvehicle::TryGetInstance(trafpizzza.first);
      if (!instance.mCollection) return false;

      // Install random parts
      OpenMW::RideInfo ride_info(trafpizzza.second);
      ride_info.SetStockParts();
      ride_info.SetRandomPaint();
      ride_info.SetRandomParts();
      OpenMW::FECustomizationRecord customizations;
      customizations.WriteRideIntoRecord(&ride_info);
      customizations.mInstalledPhysics = OpenMW::PhysicsEx::GetMaxLevelPackage(instance);
      customizations.mTunings[0]       = OpenMW::Physics::Tunings(2.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f);
      customizations.mActiveTuning     = OpenMW::eCustomTuningType::Setting1;
      // Swap car
      if (!OpenMW::PVehicleEx::ChangePlayerVehicle(trafpizzza.first, &customizations)) return false;
      return true;
    }

   public:
    explicit DeliveryBoy() : IGameEffect(84) {}
  };
}  // namespace Extensions::Game::MW05::Effects
