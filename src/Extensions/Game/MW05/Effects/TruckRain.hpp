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
  class TruckRain : public IGameEffect {
    std::vector<OpenMW::PVehicle*> mSpawnedTrucks;

   protected:
    virtual bool _activate() noexcept override {
      mSpawnedTrucks.clear();
      return true;
    }
    virtual void _activeTick() noexcept override {
      static float garbage_timer = 0.0f;
      static float spawn_timer   = 5.0f;
      garbage_timer += ImGui::GetIO().DeltaTime;
      spawn_timer += ImGui::GetIO().DeltaTime;

      if (garbage_timer > 10.0f) {
        for (auto it = std::begin(mSpawnedTrucks); it != std::end(mSpawnedTrucks);) {
          auto* pvehicle = *it | OpenMW::PVehicleEx::ValidatePVehicle;
          if (!pvehicle) {
            it++;
            continue;
          }

          pvehicle->Kill();
          it = mSpawnedTrucks.erase(it);
        }
        garbage_timer = 0.0f;
      }

      if (spawn_timer > 5.0f) {
        auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
        if (!pvehicle) return;

        OpenMW::UMath::Vector3 position = pvehicle->GetPosition();
        OpenMW::UMath::Vector3 direction;
        pvehicle->GetRigidBody()->GetForwardVector(direction);

        auto mult = std::max(20.0f, pvehicle->GetSpeed());
        position.x += direction.x * mult;
        position.y += direction.y * mult;
        position.z += 10.0f;
        direction.x *= -1.0f;

        auto* new_pvehicle = OpenMW::PVehicle::Construct(OpenMW::VehicleParams(OpenMW::DriverClass::None, OpenMW::Attrib::StringToKey("cs_semi"), direction,
                                                                               position, nullptr, OpenMW::eVehicleParamFlags::None)) |
                             OpenMW::PVehicleEx::ValidatePVehicle;
        if (!new_pvehicle) return;
        new_pvehicle->GetRigidBody()->SetMass(1000.0f);

        mSpawnedTrucks.push_back(new_pvehicle);
        spawn_timer = 0.0f;
      }
    }

   public:
    explicit TruckRain() : IGameEffect(90) {}
  };
}  // namespace Extensions::Game::MW05::Effects
