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
  class EARFQUAKE : public IGameEffect {
   protected:
    virtual bool _deactivate() noexcept override {
      if (XInputWrapper::Get().IsConnected()) return XInputWrapper::Get().StopRumble();
      return true;
    }
    virtual void _activeTick() noexcept override {
      // Shake player camera
      {
        static std::size_t frames = 30;
        if (frames++ == 30) {
          OpenSpeed::MW05::Game::ShakeCamera();
          frames = 0;
        }
      }
      // Shake all the cars
      {
        OpenMW::PVehicleEx::ForEachInstance([](OpenMW::PVehicle* pvehicle) {
          auto rnd_xyz    = Random::Get().Generate(1, 4);
          auto rnd_amount = Random::Get().Generate(-2.0f, 2.0f);
          auto velocity   = pvehicle->GetRigidBody()->GetLinearVelocity();
          if (rnd_xyz < 3)
            velocity.z += rnd_amount;
          else if (rnd_xyz == 3)
            velocity.x += rnd_amount * 2.0f;
          else
            velocity.y += rnd_amount * 2.0f;

          pvehicle->GetRigidBody()->SetLinearVelocity(velocity);
        });
      }
      // Vibrate controller
      XInputWrapper::Get().Rumble(Random::Get().Generate(0.0f, 1.0f), Random::Get().Generate(0.0f, 1.0f));
    }

   public:
    explicit EARFQUAKE() : IGameEffect(3) {}
  };
}  // namespace Extensions::Game::MW05::Effects
