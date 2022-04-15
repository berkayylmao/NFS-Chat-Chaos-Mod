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
  class CruiseControl : public IGameEffect {
    float mSpeed;
    bool  mIsColliding;

    void updateIsColliding(OpenMW::PVehicle* pvehicle) {
      static float timer = 0.0f;

      bool is_colliding = pvehicle->IsCollidingWithSoftBarrier();

      auto* rb = pvehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (rb) {
        is_colliding |= rb->mData->GetStatusPrev(OpenMW::RigidBody::Volatile::Status::CollisionWorld);
        is_colliding |= rb->mData->GetStatusPrev(OpenMW::RigidBody::Volatile::Status::CollisionGround);
      }

      if (is_colliding) {
        mIsColliding = true;
      } else {
        timer += ImGui::GetIO().DeltaTime;
        if (timer > 1.0f) {
          mIsColliding = false;
          timer        = 0.0f;
        }
      }
    }

   protected:
    virtual bool _activate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      mSpeed = pvehicle->GetSpeed();
      return true;
    }
    virtual void _activeTick() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return;

      updateIsColliding(pvehicle);
      if (pvehicle->mWheelsOnGround == 4 && !mIsColliding) pvehicle->SetSpeed(mSpeed);
    }

   public:
    explicit CruiseControl() : IGameEffect(13), mSpeed(0), mIsColliding(false) {}
  };
}  // namespace Extensions::Game::MW05::Effects
