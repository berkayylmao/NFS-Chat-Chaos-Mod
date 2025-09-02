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
  class GigaRubberband : public IGameEffect {
    OpenMW::GRacerInfo* mPlayerRacerInfo;
    OpenMW::PVehicle*   mTargetPVehicle;
    OpenMW::GRacerInfo* mTargetRacerInfo;

    void makeTargetAheadOfPlayer() {
      mTargetRacerInfo->mCheckpointsHitThisLap = mPlayerRacerInfo->mCheckpointsHitThisLap;
      mTargetRacerInfo->mDistanceDriven        = mPlayerRacerInfo->mDistanceDriven + 100.0f;
      mTargetRacerInfo->mDistToNextCheckpoint  = std::max(0.0f, mPlayerRacerInfo->mDistToNextCheckpoint - 100.0f);
      mTargetRacerInfo->mLapsCompleted         = mPlayerRacerInfo->mLapsCompleted;
      mTargetRacerInfo->mPctLapComplete        = std::min(100.0f, mPlayerRacerInfo->mPctLapComplete);
      mTargetRacerInfo->mPctRaceComplete       = std::min(100.0f, mPlayerRacerInfo->mPctRaceComplete);
      mTargetRacerInfo->mPointTotal            = mPlayerRacerInfo->mPointTotal + 100;
    }

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenMW::GameStatusEx::IsRacing(); }

    virtual bool _activate() noexcept override {
      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status) return false;
      if (race_status->mPlayMode != OpenMW::GRaceStatus::PlayMode::Racing) return false;

      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      std::vector<std::size_t> available_ids;

      for (std::int32_t i = 0; i < race_status->mRacerCount; i++) {
        auto* handle = race_status->mRacerInfo[i].mhSimable;
        if (!handle) continue;

        const auto& racer = race_status->mRacerInfo[i];
        // Get available ids
        if (handle == player_vehicle->GetOwnerHandle())
          mPlayerRacerInfo = &race_status->mRacerInfo[i];
        else if (!racer.mKnockedOut && !racer.mBusted && !racer.mEngineBlown)
          available_ids.push_back(i);
      }
      if (!mPlayerRacerInfo) return false;
      if (available_ids.size() == 0) return false;

      // Shuffle available ids
      std::shuffle(available_ids.begin(), available_ids.end(), Random::Get().GetGenerator());
      mTargetRacerInfo = &race_status->mRacerInfo[available_ids[0]];
      if (!mTargetRacerInfo) return false;

      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        if (pvehicle->GetOwnerHandle() == mTargetRacerInfo->mhSimable) mTargetPVehicle = pvehicle;
      });

      if (!mTargetPVehicle) return false;
      makeTargetAheadOfPlayer();
      mTargetRacerInfo->mBusted      = false;
      mTargetRacerInfo->mDNF         = false;
      mTargetRacerInfo->mEngineBlown = false;
      mTargetRacerInfo->mKnockedOut  = false;
      mTargetRacerInfo->mTotalled    = false;

      return true;
    }

    virtual void _activeTick() noexcept override {
      if (!OpenMW::GameStatusEx::IsRacing() || !(mTargetPVehicle | OpenMW::PVehicleEx::ValidatePVehicle)) return;

      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;
      auto* player_rb = player_vehicle->GetRigidBody() | OpenMW::RigidBodyEx::AsRigidBody;
      if (!player_rb) return;

      OpenMW::UMath::Vector3 position = player_rb->GetPosition();
      OpenMW::UMath::Vector3 direction;
      player_rb->GetForwardVector(direction);

      position.x += direction.x * 10.0f;
      position.y += direction.y * 10.0f;
      mTargetPVehicle->SetVehicleOnGround(position, direction);
      makeTargetAheadOfPlayer();
    }

   public:
    explicit GigaRubberband() : IGameEffect(68), mPlayerRacerInfo(nullptr), mTargetPVehicle(nullptr), mTargetRacerInfo(nullptr) {}
  };
}  // namespace Extensions::Game::MW05::Effects
