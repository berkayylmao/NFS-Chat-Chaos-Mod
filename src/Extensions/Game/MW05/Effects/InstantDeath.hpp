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
  class InstantDeath : public IGameEffect {
    bool mKilled;

   protected:
    virtual void _activeTick() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return;
      auto* damage = pvehicle->mDamage;
      auto* rb     = pvehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;

      if (mKilled) {
        if (damage && !damage->IsDestroyed()) mKilled = false;
        if (mKilled) return;
      }

      bool kill = pvehicle->IsCollidingWithSoftBarrier();
      if (!kill) {
        if (rb) {
          kill |= rb->mData->GetStatusPrev(OpenMW::RigidBody::Volatile::Status::CollisionWorld);
          kill |= rb->mData->GetStatusPrev(OpenMW::RigidBody::Volatile::Status::CollisionObject);
          kill |= rb->mData->GetStatusPrev(OpenMW::RigidBody::Volatile::Status::CollisionGround);
        }
      }
      if (kill) {
        if (pvehicle->mDamage)
          pvehicle->mDamage->Destroy();
        else
          OpenMW::Game::BlowEngine(pvehicle);
        mKilled = true;
      }
    }

   public:
    explicit InstantDeath() : IGameEffect(133), mKilled(false) {}
  };
}  // namespace Extensions::Game::MW05::Effects
