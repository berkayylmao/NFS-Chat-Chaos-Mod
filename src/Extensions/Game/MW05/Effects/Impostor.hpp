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
  class Impostor : public IGameEffect {
    struct SwapInfo {
      std::int32_t                mRacerIdx;
      const char*                 pRacerName;
      OpenMW::PVehicle*           mPVehicle;
      OpenMW::UTL::COM::IUnknown* mOwner;
      OpenMW::UMath::Vector3      mPosition;

      void Clear() {
        mRacerIdx  = -1;
        pRacerName = nullptr;
        mPVehicle  = nullptr;
        mOwner     = nullptr;
        mPosition  = OpenMW::UMath::Vector3();
      }
      bool IsValid() { return mPVehicle != nullptr; }

      SwapInfo() : mRacerIdx(-1), pRacerName(nullptr), mPVehicle(nullptr), mOwner(nullptr), mPosition() {}
    };

    SwapInfo mPlayerSwapInfo;
    SwapInfo mTargetSwapInfo;

    void _doSwap(OpenMW::GRaceStatus* raceStatus) {
      // detach both
      mTargetSwapInfo.mPVehicle->Detach(mTargetSwapInfo.mOwner);
      mPlayerSwapInfo.mPVehicle->Detach(mPlayerSwapInfo.mOwner);

      // attach ai
      mPlayerSwapInfo.mPVehicle->Attach(mTargetSwapInfo.mOwner);
      // attach player
      mTargetSwapInfo.mPVehicle->Attach(mPlayerSwapInfo.mOwner);

      mPlayerSwapInfo.mPVehicle->SetDriverClass(OpenMW::DriverClass::Racer);
      mTargetSwapInfo.mPVehicle->SetDriverClass(OpenMW::DriverClass::Human);

      // update leaderboard for ai car
      raceStatus->mRacerInfo[mPlayerSwapInfo.mRacerIdx].mName     = mTargetSwapInfo.pRacerName;
      raceStatus->mRacerInfo[mPlayerSwapInfo.mRacerIdx].mhSimable = mPlayerSwapInfo.mPVehicle->GetOwnerHandle();

      // update leaderboard for player
      raceStatus->mRacerInfo[mTargetSwapInfo.mRacerIdx].mName     = mPlayerSwapInfo.pRacerName;
      raceStatus->mRacerInfo[mTargetSwapInfo.mRacerIdx].mhSimable = mTargetSwapInfo.mPVehicle->GetOwnerHandle();

      // tp back
      mPlayerSwapInfo.mPVehicle->GetRigidBody()->SetPosition(mPlayerSwapInfo.mPosition);

      OpenMW::GenericMessageEx::DisplayMessage("Leaderboard will be fixed shortly");
      OpenMW::EAXSound::ReStartRace();
    }

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override {
      if (!OpenMW::GameStatusEx::HasFinishedPrologue()) return false;

      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status) return false;

      return race_status->mPlayMode == OpenMW::GRaceStatus::PlayMode::Racing && race_status->mRacerCount > 1;
    }

    virtual bool _activate() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      auto* player = OpenMW::IPlayer::GetPlayer();
      if (!player) return false;

      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status) return false;

      // Get needed info
      if (!mPlayerSwapInfo.IsValid() || !mTargetSwapInfo.IsValid()) {
        OpenMW::HSIMABLE__*      ai_handle = nullptr;
        std::vector<std::size_t> available_ids;

        for (std::int32_t i = 0; i < race_status->mRacerCount; i++) {
          auto* handle = race_status->mRacerInfo[i].mhSimable;
          if (!handle) continue;

          const auto& racer = race_status->mRacerInfo[i];
          // Get available ids
          if (handle != player_vehicle->GetOwnerHandle() && !racer.mKnockedOut && !racer.mBusted && !racer.mEngineBlown) available_ids.push_back(i);

          // Get player info
          if (handle == player_vehicle->GetOwnerHandle()) {
            mPlayerSwapInfo.mRacerIdx  = i;
            mPlayerSwapInfo.pRacerName = race_status->mRacerInfo[i].mName;
            mPlayerSwapInfo.mPVehicle  = player_vehicle;
            mPlayerSwapInfo.mOwner     = player;
            mPlayerSwapInfo.mPosition  = player_vehicle->GetRigidBody()->GetPosition();
          }
        }

        // Shuffle available ids
        std::shuffle(available_ids.begin(), available_ids.end(), Random::Get().GetGenerator());
        mTargetSwapInfo.mRacerIdx  = available_ids[0];
        ai_handle                  = race_status->mRacerInfo[mTargetSwapInfo.mRacerIdx].mhSimable;
        mTargetSwapInfo.pRacerName = race_status->mRacerInfo[mTargetSwapInfo.mRacerIdx].mName;

        OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
          if (pvehicle->GetOwnerHandle() == ai_handle) {
            mTargetSwapInfo.mPVehicle = pvehicle;
            mTargetSwapInfo.mOwner    = pvehicle->GetSimable();
            mTargetSwapInfo.mPosition = pvehicle->GetRigidBody()->GetPosition();
          }
        });

        // Teleport player car to make sure game loads destination
        mPlayerSwapInfo.mPVehicle->GetRigidBody()->SetPosition(mTargetSwapInfo.mPosition);
      }
      // Check if info is valid
      if (!mPlayerSwapInfo.IsValid() || !mTargetSwapInfo.IsValid()) return false;

      if (mTargetSwapInfo.mPVehicle->mRenderable && mTargetSwapInfo.mPVehicle->mRenderable->InView()) {
        _doSwap(race_status);
        return true;
      }
      return false;
    }
    virtual bool _deactivate() noexcept override {
      mPlayerSwapInfo.Clear();
      mTargetSwapInfo.Clear();

      return true;
    }

   public:
    explicit Impostor() : IGameEffect(53) {}
  };
}  // namespace Extensions::Game::MW05::Effects