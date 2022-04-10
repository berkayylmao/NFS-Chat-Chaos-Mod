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
  class AXEDeodorant : public IGameEffect {
    const OpenMW::UMath::Vector3 mDangerZone = OpenMW::UMath::Vector3(30.0f, 30.0f, 30.0f);

   protected:
    virtual void _activeTick() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      const auto& player_pos      = player_vehicle->GetRigidBody()->GetPosition();
      const auto  danger_zone_min = player_pos - mDangerZone;
      const auto  danger_zone_max = player_pos + mDangerZone;

      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) {
        if (pvehicle->IsPlayer() || pvehicle->IsOwnedByPlayer()) return;

        const auto& pos = pvehicle->GetRigidBody()->GetPosition();
        if (pos.x > danger_zone_min.x && pos.x < danger_zone_max.x && pos.y > danger_zone_min.y && pos.y < danger_zone_max.y && pos.z > danger_zone_min.z &&
            pos.z < danger_zone_max.z) {
          const auto v = (player_pos - pos).Normalize();

          pvehicle->GetRigidBody()->SetLinearVelocity(OpenMW::UMath::Vector3(
              // x
              v.x * -40.0f,
              // y
              v.y * -40.0f,
              // z
              0.0f));
        }
      });
    }

   public:
    explicit AXEDeodorant() : IGameEffect(59) {}
  };
}  // namespace Extensions::Game::MW05::Effects
