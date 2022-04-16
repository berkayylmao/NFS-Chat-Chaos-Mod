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
  class TeleportToRandomCar : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenMW::PVehicle::GetInstancesCount() > 1; }

    virtual bool _activate() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      auto  count  = OpenMW::PVehicle::GetInstancesCount();
      auto* target = OpenMW::PVehicle::GetInstance(Random::Get().Generate(0, count)) | OpenMW::PVehicleEx::ValidatePVehicle;
      if (target->IsPlayer() || target->IsOwnedByPlayer()) return;

      // No Speed
      target->SetSpeed(0);
      player_vehicle->SetSpeed(0);
      // Same direction (if possible)
      {
        auto* player_rb = player_vehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
        auto* target_rb = target->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
        if (player_rb && target_rb) player_rb->SetRotation(target_rb->GetRotation());
      }
      // Same position
      player_vehicle->GetRigidBody()->SetPosition(target->GetRigidBody()->GetPosition());
      return true;
    }

   public:
    explicit TeleportToRandomCar() : IGameEffect(96) {}
  };
}  // namespace Extensions::Game::MW05::Effects
