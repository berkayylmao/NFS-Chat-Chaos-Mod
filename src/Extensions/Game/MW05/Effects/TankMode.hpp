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
  class TankMode : public IGameEffect {
    float mSavedCollisionMass;

   protected:
    virtual bool _activate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      auto* rb = pvehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRBVehicle;
      if (!rb) return false;

      mSavedCollisionMass = rb->mCollisionMass;
      rb->SetCollisionMass(10000.0f);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      auto* rb = pvehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRBVehicle;
      if (!rb) return false;

      rb->SetCollisionMass(mSavedCollisionMass);
      return true;
    }

   public:
    explicit TankMode() : IGameEffect(57), mSavedCollisionMass(0.0f) {}
  };
}  // namespace Extensions::Game::MW05::Effects
