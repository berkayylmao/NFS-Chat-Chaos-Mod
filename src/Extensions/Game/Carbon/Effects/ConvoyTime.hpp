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
  class ConvoyTime : public IGameEffect {
   protected:
    virtual bool _deactivate() noexcept override {
      OpenCarbon::PVehicleEx::ForEachInstance([=](OpenCarbon::PVehicle* pvehicle) { pvehicle->ForceStopOff(OpenCarbon::IVehicle::ForceStopType::ForceStop); });
      return true;
    }

    virtual void _activeTick() noexcept override {
      auto* player_vehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      auto* player_rb = player_vehicle->GetRigidBody();

      OpenCarbon::UMath::Vector3 position = player_rb->GetPosition();
      OpenCarbon::UMath::Vector3 direction;
      player_rb->GetForwardVector(direction);

      OpenCarbon::PVehicleEx::ForEachInstance([=](OpenCarbon::PVehicle* pvehicle) mutable {
        if (pvehicle->GetOwnerHandle() == player_vehicle->GetOwnerHandle()) return;

        auto* target_rb = pvehicle->GetRigidBody();

        position.x -= direction.x * 8.0f;
        position.y -= direction.y * 8.0f;

        target_rb->SetPosition(position);

        pvehicle->ForceStopOn(OpenCarbon::IVehicle::ForceStopType::ForceStop);
      });
    }

   public:
    explicit ConvoyTime() : IGameEffect(87) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
