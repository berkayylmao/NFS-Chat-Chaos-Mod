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
  class CarCollector : public IGameEffect {
    const OpenMW::UMath::Vector3          mCollectionZone = OpenMW::UMath::Vector3(20.0f, 20.0f, 20.0f);
    std::unordered_set<OpenMW::PVehicle*> mCollectedCars;

    bool IsInsideCollectionZone(const OpenMW::UMath::Vector3& player, const OpenMW::UMath::Vector3& other) {
      const auto min = player - mCollectionZone;
      const auto max = player + mCollectionZone;
      return other.x > min.x && other.x < max.x && other.y > min.y && other.y < max.y && other.z > min.z && other.z < max.z;
    }

   protected:
    virtual void _activeTick() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      auto* player_rb = player_vehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!player_rb) return;

      const auto&            player_pos = player_vehicle->GetPosition();
      OpenMW::UMath::Vector3 player_direction;
      player_rb->GetForwardVector(player_direction);

      // collect
      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) {
        if (pvehicle->IsPlayer() || pvehicle->IsOwnedByPlayer()) return;
        if (IsInsideCollectionZone(player_pos, pvehicle->GetPosition())) mCollectedCars.insert(pvehicle);
      });
      // display
      const auto amount = mCollectedCars.size();
      if (amount == 0) return;
      const float angle_per = 360.0f / amount;
      for (std::size_t _1 = 0; _1 < amount; _1++) {
        const float            mult = static_cast<float>(_1);
        OpenMW::UMath::Vector3 pos(
            // x
            player_pos.x + (mCollectionZone.x * std::cos(angle_per * mult)),
            // y
            player_pos.y + (mCollectionZone.y * std::sin(angle_per * mult)),
            // z
            player_pos.z);
        if (auto* pvehicle = *std::next(mCollectedCars.begin(), _1) | OpenMW::PVehicleEx::ValidatePVehicle) pvehicle->SetVehicleOnGround(pos, player_direction);
      }
    }

   public:
    explicit CarCollector() : IGameEffect(104) {}
  };
}  // namespace Extensions::Game::MW05::Effects
