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
  class BouncyCastle : public IGameEffect {
   protected:
    virtual bool _deactivate() noexcept override {
      if (XInputWrapper::Get().IsConnected()) return XInputWrapper::Get().StopRumble();
      return true;
    }
    virtual void _activeTick() noexcept override {
      // Shake all the cars
      {
        OpenMW::PVehicleEx::ForEachInstance([](OpenMW::PVehicle* pvehicle) {
          if (pvehicle->mWheelsOnGround > 2)
            pvehicle->GetRigidBody()->SetLinearVelocity(pvehicle->GetRigidBody()->GetLinearVelocity() +
                                                        OpenMW::UMath::Vector3(0.0f, 0.0f, Random::Get().Generate(2.0f, 5.0f)));
        });
      }
      // Vibrate controller
      XInputWrapper::Get().Rumble(Random::Get().Generate(0.0f, 1.0f), Random::Get().Generate(0.0f, 1.0f));
    }

   public:
    explicit BouncyCastle() : IGameEffect(106) {}
  };
}  // namespace Extensions::Game::MW05::Effects
