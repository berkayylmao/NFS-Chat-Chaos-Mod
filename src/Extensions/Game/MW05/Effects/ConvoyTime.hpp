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
  class ConvoyTime : public IGameEffect {
   protected:
    virtual bool _deactivate() noexcept override {
      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) { pvehicle->ForceStopOff(OpenMW::IVehicle::ForceStopType::ForceStop); });
      return true;
    }

    virtual void _activeTick() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      auto* player_rb = player_vehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!player_rb) return;

      OpenMW::UMath::Vector3 position = player_rb->GetPosition();
      const auto&            rotation = player_rb->GetRotation();
      OpenMW::UMath::Vector3 direction;
      player_rb->GetForwardVector(direction);

      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) mutable {
        if (pvehicle->GetOwnerHandle() == player_vehicle->GetOwnerHandle()) return;

        auto* target_rb = pvehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
        if (!target_rb) return;

        position.x -= direction.x * 8.0f;
        position.y -= direction.y * 8.0f;

        target_rb->SetPosition(position);
        target_rb->SetRotation(rotation);

        pvehicle->ForceStopOn(OpenMW::IVehicle::ForceStopType::ForceStop);
      });
    }

   public:
    explicit ConvoyTime() : IGameEffect(87) {}
  };
}  // namespace Extensions::Game::MW05::Effects
