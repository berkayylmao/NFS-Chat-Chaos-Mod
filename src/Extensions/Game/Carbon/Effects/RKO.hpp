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
  class RKO : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      OpenCarbon::PVehicleEx::ForEachInstance([=](OpenCarbon::PVehicle* pvehicle) {
        if (auto* rb = pvehicle->GetRigidBody()) {
          OpenCarbon::UMath::Vector3 direction;
          rb->GetForwardVector(direction);
          // generate flip data
          {
            if (std::abs(direction.x) > std::abs(direction.y))
              while (direction.y < 50.0f && direction.y > -50.0f) direction.y *= 2.0f;
            else
              while (direction.x < 50.0f && direction.x > -50.0f) direction.x *= 2.0f;
            direction.z = 0.0f;
          }

          rb->SetAngularVelocity(rb->GetAngularVelocity() + direction);
        }
      });
      return true;
    }

   public:
    explicit RKO() : IGameEffect(74) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
