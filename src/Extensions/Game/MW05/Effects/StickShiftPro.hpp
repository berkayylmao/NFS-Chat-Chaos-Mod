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
  class StickShiftPro : public IGameEffect {
    OpenMW::eTransmissionType mSavedTransmission;

   protected:
    virtual bool _activate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      mSavedTransmission                   = db->GetPlayerSettings().Transmission;
      db->GetPlayerSettings().Transmission = OpenMW::eTransmissionType::Manual;
      return true;
    }
    virtual bool _deactivate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      db->GetPlayerSettings().Transmission = mSavedTransmission;
      return true;
    }
    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(2.0f);

      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) {
        if (auto* tranny = pvehicle->mTranny) {
          tranny->Shift(static_cast<OpenMW::ITransmission::GearID>(
              Random::Get().Generate(static_cast<std::int32_t>(OpenMW::ITransmission::GearID::Reverse), static_cast<std::int32_t>(tranny->GetTopGear()))));
        }
      });
    }

   public:
    explicit StickShiftPro() : IGameEffect(78), mSavedTransmission(OpenMW::eTransmissionType::Automatic) {}
  };
}  // namespace Extensions::Game::MW05::Effects
