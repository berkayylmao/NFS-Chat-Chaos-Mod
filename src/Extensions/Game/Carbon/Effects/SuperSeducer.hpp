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
  class SuperSeducer : public IGameEffect {
    const OpenCarbon::UMath::Vector3 mPassiveZone    = OpenCarbon::UMath::Vector3(10.0f, 10.0f, 10.0f);
    const OpenCarbon::UMath::Vector3 mAttractionZone = OpenCarbon::UMath::Vector3(60.0f, 60.0f, 60.0f);

    bool IsInsidePassiveZone(const OpenCarbon::UMath::Vector3& player, const OpenCarbon::UMath::Vector3& other) {
      const auto min = player - mPassiveZone;
      const auto max = player + mPassiveZone;
      return other.x > min.x && other.x < max.x && other.y > min.y && other.y < max.y && other.z > min.z && other.z < max.z;
    }
    bool IsInsideAttractionZone(const OpenCarbon::UMath::Vector3& player, const OpenCarbon::UMath::Vector3& other) {
      const auto min = player - mAttractionZone;
      const auto max = player + mAttractionZone;
      return other.x > min.x && other.x < max.x && other.y > min.y && other.y < max.y && other.z > min.z && other.z < max.z;
    }

   protected:
    virtual void _activeTick() noexcept override {
      OpenCarbon::PVehicle* player_vehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      const auto& player_pos = player_vehicle->GetRigidBody()->GetPosition();

      OpenCarbon::PVehicleEx::ForEachInstance([=](OpenCarbon::PVehicle* pvehicle) {
        if (pvehicle->IsPlayer() || pvehicle->IsOwnedByPlayer()) return;

        const auto& pos = pvehicle->GetRigidBody()->GetPosition();
        if (IsInsideAttractionZone(player_pos, pos) && !IsInsidePassiveZone(player_pos, pos)) {
          const auto v = (player_pos - pos).Normalize();

          pvehicle->GetRigidBody()->SetLinearVelocity(OpenCarbon::UMath::Vector3(
              // x
              v.x * 25.0f,
              // y
              v.y * 25.0f,
              // z
              v.z * 10.0f));
        }
      });
    }

   public:
    explicit SuperSeducer() : IGameEffect(60) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
