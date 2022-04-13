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

namespace Extensions::Game::Carbon::Effects {
  class Magneto : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenCarbon::PVehicle::GetInstancesCount() > 1; }

    virtual bool _activate() noexcept override {
      auto* player_vehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      auto* rb       = player_vehicle->GetRigidBody();
      auto  pos      = rb->GetPosition();
      auto  velocity = rb->GetLinearVelocity() + OpenCarbon::UMath::Vector3(0.0f, 0.0f, 20.0f);
      rb->SetLinearVelocity(velocity);

      OpenCarbon::PVehicleEx::ForEachInstance([=](OpenCarbon::PVehicle* pvehicle) {
        if (!pvehicle->IsPlayer() && !pvehicle->IsOwnedByPlayer()) {
          auto* p_rb = pvehicle->GetRigidBody();
          p_rb->SetPosition(pos);
          p_rb->SetLinearVelocity(velocity);
        }
      });

      return true;
    }

   public:
    explicit Magneto() : IGameEffect(34) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
