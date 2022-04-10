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
  class GigaRubberband : public IGameEffect {
    OpenMW::PVehicle* mTargetPVehicle;

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenMW::GameStatusEx::IsRacing(); }

    virtual bool _activate() noexcept override {
      if (!OpenMW::GameStatusEx::IsRacing()) return false;

      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status) return false;

      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      OpenMW::GRacerInfo       player_racer_info;
      std::vector<std::size_t> available_ids;

      for (std::int32_t i = 0; i < race_status->mRacerCount; i++) {
        auto* handle = race_status->mRacerInfo[i].mhSimable;
        if (!handle) continue;

        const auto& racer = race_status->mRacerInfo[i];
        // Get available ids
        if (handle == player_vehicle->GetOwnerHandle())
          player_racer_info = race_status->mRacerInfo[i];
        else if (!racer.mKnockedOut && !racer.mBusted && !racer.mEngineBlown)
          available_ids.push_back(i);
      }

      // Shuffle available ids
      std::shuffle(available_ids.begin(), available_ids.end(), Random::Get().GetGenerator());
      auto& target_racer = race_status->mRacerInfo[available_ids[0]];

      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        if (pvehicle->GetOwnerHandle() == target_racer.mhSimable) mTargetPVehicle = pvehicle;
      });

      if (!mTargetPVehicle) return false;
      // Make sure target is ahead of player
      target_racer.mCheckpointsHitThisLap = player_racer_info.mCheckpointsHitThisLap;
      target_racer.mDistanceDriven        = player_racer_info.mDistanceDriven;
      target_racer.mDistToNextCheckpoint  = player_racer_info.mDistToNextCheckpoint;
      target_racer.mLapsCompleted         = player_racer_info.mLapsCompleted;
      target_racer.mPctLapComplete        = player_racer_info.mPctLapComplete;
      target_racer.mPctRaceComplete       = player_racer_info.mPctRaceComplete;
      target_racer.mPointTotal            = player_racer_info.mPointTotal;
      // Stop car
      mTargetPVehicle->ForceStopOn(OpenMW::IVehicle::ForceStopType::ForceStop);

      return true;
    }
    virtual bool _deactivate() noexcept override {
      if (!mTargetPVehicle) return true;
      mTargetPVehicle->ForceStopOff(OpenMW::IVehicle::ForceStopType::ForceStop);

      return true;
    }

    virtual void _activeTick() noexcept override {
      if (!OpenMW::GameStatusEx::IsRacing() || !(mTargetPVehicle | OpenMW::PVehicleEx::ValidatePVehicle)) return;

      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;
      auto* player_rb = player_vehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!player_rb) return;
      auto* target_rb = mTargetPVehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!target_rb) return;

      auto                   position = player_rb->GetPosition();
      const auto&            rotation = player_rb->GetRotation();
      OpenMW::UMath::Vector3 direction;
      player_rb->GetForwardVector(direction);

      position.x += direction.x * 10.0f;
      position.y += direction.y * 10.0f;

      target_rb->SetPosition(position);
      target_rb->SetRotation(rotation);
    }

   public:
    explicit GigaRubberband() : IGameEffect(68), mTargetPVehicle(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects
