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
#include "Extensions/Game/IFakeGameEffect.hpp"

namespace Extensions::Game::MW05::Effects {
  class FakeTeleportToOldBridge : public IFakeGameEffect {
    bool                   mSaved;
    OpenMW::UMath::Vector3 mSavedPosition;
    OpenMW::UMath::Vector3 mSavedDirection;
    OpenMW::UMath::Vector3 mSavedAngularVelocity;
    OpenMW::UMath::Vector3 mSavedLinearVelocity;

   protected:
    virtual bool _onRevealed() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      if (!pvehicle->SetVehicleOnGround(mSavedPosition, mSavedDirection)) return false;
      pvehicle->GetRigidBody()->SetAngularVelocity(mSavedAngularVelocity);
      pvehicle->GetRigidBody()->SetLinearVelocity(mSavedLinearVelocity);
      mSaved = false;
      return true;
    }

    virtual bool _activate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      if (!mSaved) {
        auto* rb       = pvehicle->GetRigidBody();
        mSavedPosition = rb->GetPosition();
        rb->GetForwardVector(mSavedDirection);
        mSavedAngularVelocity = rb->GetAngularVelocity();
        mSavedLinearVelocity  = rb->GetLinearVelocity();
        mSaved                = true;
      }

      if (!pvehicle->SetVehicleOnGround(OpenMW::UMath::Vector3(-961.0f, -2646.0f, 210.0f), OpenMW::UMath::Vector3(-0.81f, 0.52f, 0.22f))) return false;
      pvehicle->SetSpeed(100.0f);
      return true;
    }

   public:
    explicit FakeTeleportToOldBridge() : IFakeGameEffect(115), mSaved(false) {}
  };
}  // namespace Extensions::Game::MW05::Effects
