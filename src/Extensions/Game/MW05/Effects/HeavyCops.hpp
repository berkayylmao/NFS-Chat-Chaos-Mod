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
#include "Extensions/Game/MW05/MW05.hpp"

namespace Extensions::Game::MW05::Effects {
  class HeavyCops : public IGameEffect {
    // WorldID, original mass
    std::unordered_map<std::uint32_t, float> mSavedMass;
    // WorldID, original mass
    std::unordered_map<std::uint32_t, float> mSavedCollisionMass;

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenMW::GameStatusEx::IsInPursuit(); }

    virtual bool _activate() noexcept override {
      mSavedMass.clear();
      mSavedCollisionMass.clear();
      return OpenMW::PVehicleEx::GetPlayerInstance() != nullptr;
    }
    virtual bool _deactivate() noexcept override {
      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        auto  id = pvehicle->GetWorldID();
        auto* rb = pvehicle->GetRigidBody();

        // Restore mass
        auto val = mSavedMass.find(id);
        if (val != std::cend(mSavedMass)) rb->SetMass(mSavedMass[id]);

        // Check if collision mass was backed up
        val = mSavedCollisionMass.find(id);
        if (val == std::cend(mSavedCollisionMass)) return;

        // Restore collision mass
        auto* rbvehicle = rb | OpenMW::RigidBodyEx::AsRBVehicle;
        if (rbvehicle) rbvehicle->mCollisionMass = mSavedCollisionMass[id];
      });

      return true;
    }
    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(1.0f);

      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        // Get values
        auto id  = pvehicle->GetWorldID();
        auto val = mSavedMass.find(id);
        if (val != std::cend(mSavedMass)) return;

        auto* ai = pvehicle->GetAIVehiclePtr() | OpenMW::AIVehicleEx::AsAIVehicleCopCar;
        if (!ai) return;

        auto* rb   = pvehicle->GetRigidBody();
        float mass = rb->GetMass();

        // Backup originals
        mSavedMass[pvehicle->GetWorldID()] = mass;
        auto* rbvehicle                    = rb | OpenMW::RigidBodyEx::AsRBVehicle;
        if (rbvehicle) mSavedCollisionMass[id] = rbvehicle->mCollisionMass;

        // Change values
        rb->SetMass(mass * 4.0f);
        if (rbvehicle) rbvehicle->mCollisionMass = mSavedCollisionMass[id] * 8.0f;
      });
    }

   public:
    explicit HeavyCops() : IGameEffect(76) {}
  };
}  // namespace Extensions::Game::MW05::Effects
