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
  class FAK500 : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override {
      return OpenMW::GameStatusEx::HasFinishedPrologue() && !OpenMW::GameStatusEx::IsInPursuit();
    }

    virtual bool _activate() noexcept override {
      auto car_key  = OpenMW::Attrib::StringToKey("clk500");
      auto instance = OpenMW::Attrib::Gen::pvehicle::TryGetInstance(car_key);
      if (!instance.mCollection) return false;

      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      auto* db_car_record = db->GetUserProfile()->mPlayersCarStable.GetCarRecordByHandle(db->GetCareerSettings().GetCurrentCar());
      if (!db_car_record) return false;

      // Install random parts
      OpenMW::RideInfo ride_info(OpenMW::CarType::CLK500);
      ride_info.SetStockParts();
      ride_info.SetRandomPaint();
      ride_info.SetRandomParts();
      OpenMW::FECustomizationRecord customizations;
      customizations.WriteRideIntoRecord(&ride_info);
      customizations.mInstalledPhysics = OpenMW::PhysicsEx::GetRandomLevelPackage(instance);
      customizations.mTunings[0]       = OpenMW::Physics::Tunings(
                Random::Get().Generate(-2.0f, 0.0f), Random::Get().Generate(-2.0f, 0.0f), Random::Get().Generate(-2.0f, 0.0f), Random::Get().Generate(-2.0f, 0.0f),
                Random::Get().Generate(-2.0f, 0.0f), Random::Get().Generate(-2.0f, 0.0f), Random::Get().Generate(-2.0f, 0.0f));
      customizations.mActiveTuning = OpenMW::eCustomTuningType::Setting1;
      // Change car
      if (!OpenMW::PVehicleEx::ChangePlayerVehicle(car_key, &customizations)) return false;
      // Save to DB
      OpenMW::FEDatabaseEx::ChangeCarData(db_car_record, car_key, &customizations);

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::FAK);
      return true;
    }

   public:
    explicit FAK500() : IGameEffect(27) {}
  };
}  // namespace Extensions::Game::MW05::Effects
