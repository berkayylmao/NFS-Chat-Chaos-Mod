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
  class SuperSeducer : public IGameEffect {
    const OpenMW::UMath::Vector3 mPassiveZone    = OpenMW::UMath::Vector3(10.0f, 10.0f, 10.0f);
    const OpenMW::UMath::Vector3 mAttractionZone = OpenMW::UMath::Vector3(100.0f, 100.0f, 100.0f);

    bool IsInsidePassiveZone(const OpenMW::UMath::Vector3& player, const OpenMW::UMath::Vector3& other) {
      const auto min = player - mPassiveZone;
      const auto max = player + mPassiveZone;
      return other.x > min.x && other.x < max.x && other.y > min.y && other.y < max.y && other.z > min.z && other.z < max.z;
    }
    bool IsInsideAttractionZone(const OpenMW::UMath::Vector3& player, const OpenMW::UMath::Vector3& other) {
      const auto min = player - mAttractionZone;
      const auto max = player + mAttractionZone;
      return other.x > min.x && other.x < max.x && other.y > min.y && other.y < max.y && other.z > min.z && other.z < max.z;
    }

   protected:
    virtual void _activeTick() noexcept override {
      OpenMW::PVehicle* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      auto* player_rb = player_vehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!player_rb || !player_rb->mData.mRef || !*player_rb->mData.mRef) return;

      auto        player_rb_idx = player_rb->mData->index;
      const auto& player_pos    = player_rb->GetPosition();
      auto        player_speed  = std::abs(player_vehicle->GetSpeed());

      OpenMW::RigidBodyEx::ForEachInstance([=](OpenMW::RigidBody::Volatile* rv) {
        if (rv->index == player_rb_idx) return;

        const auto& pos = rv->position;
        if (IsInsideAttractionZone(player_pos, pos) && !IsInsidePassiveZone(player_pos, pos)) {
          const auto v = (player_pos - pos).Normalize();
          const auto f = std::max(20.0f, player_speed);

          rv->linearVelocity = v * f;
        }
      });
    }

   public:
    explicit SuperSeducer() : IGameEffect(60) {}
  };
}  // namespace Extensions::Game::MW05::Effects
