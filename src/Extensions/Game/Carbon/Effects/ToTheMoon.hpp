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

namespace Extensions::Game::Carbon::Effects {
  class ToTheMoon : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      OpenCarbon::PVehicleEx::ForEachInstance([](OpenCarbon::PVehicle* pvehicle) {
        auto velocity = pvehicle->GetRigidBody()->GetLinearVelocity();
        pvehicle->GetRigidBody()->SetLinearVelocity(pvehicle->GetRigidBody()->GetLinearVelocity() + OpenCarbon::UMath::Vector3(0.0f, 0.0f, 80.0f));
      });
      return true;
    }

   public:
    explicit ToTheMoon() : IGameEffect(54) {}
  };
}  // namespace Extensions::Game::Carbon::Effects