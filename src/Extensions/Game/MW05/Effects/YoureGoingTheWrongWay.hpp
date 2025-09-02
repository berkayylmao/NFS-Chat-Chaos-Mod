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
  class YoureGoingTheWrongWay : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      auto* rb = pvehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!rb) return false;

      // Rotate the car around
      {
        auto rotation = rb->GetRotation();
        rotation.v0 *= -1.0f;
        rotation.v2 *= -1.0f;
        rb->SetRotation(rotation);
      }
      // Invert speed
      pvehicle->SetSpeed(pvehicle->GetSpeed());
      return true;
    }

   public:
    explicit YoureGoingTheWrongWay() : IGameEffect(71) {}
  };
}  // namespace Extensions::Game::MW05::Effects
