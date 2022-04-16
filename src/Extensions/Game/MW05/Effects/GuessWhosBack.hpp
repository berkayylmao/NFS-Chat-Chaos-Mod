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
  class GuessWhosBack : public IGameEffect {
    OpenMW::PVehicle* mSpawned;

   protected:
    virtual bool _activate() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      auto                   position = player_vehicle->GetPosition();
      OpenMW::UMath::Vector3 direction;
      player_vehicle->GetRigidBody()->GetForwardVector(direction);

      position.x -= direction.x * 10.0f;
      position.y -= direction.y * 10.0f;

      OpenMW::Variables::TheOneCopManager->LockoutCops(false);
      // Create cross
      mSpawned = OpenMW::PVehicle::Construct(OpenMW::VehicleParams(OpenMW::DriverClass::Cop, OpenMW::Attrib::StringToKey("copsport"), direction, position,
                                                                   nullptr, OpenMW::eVehicleParamFlags::SnapToGround));
      if (!mSpawned) return false;
      if (!mSpawned->SetVehicleOnGround(position, direction)) {
        mSpawned->Kill();
        return false;
      }

      if (auto* ai_cop = mSpawned->GetAIVehiclePtr() | OpenMW::AIVehicleEx::AsAIVehicleCopCar)
        ai_cop->StartPursuit(OpenMW::AITarget::Construct(player_vehicle), player_vehicle);
      OpenMW::Variables::TheOneCopManager->PursueAtHeatLevel(10);

      auto* ai = player_vehicle->GetAIVehiclePtr() | OpenMW::AIVehicleEx::AsAIVehicleHuman;
      if (ai && ai->GetPursuit()) ai->GetPursuit()->AddVehicle(mSpawned);

      mSpawned->SetSpeed(200.0f);
      mSpawned->GetRigidBody()->SetMass(10000.0f);
      if (auto* damage = mSpawned->mDamage) damage->Destroy();

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::GuessWhosBack);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      if (mSpawned | OpenMW::PVehicleEx::ValidatePVehicle) mSpawned->Kill();
      return true;
    }

   public:
    explicit GuessWhosBack() : IGameEffect(70), mSpawned(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects
