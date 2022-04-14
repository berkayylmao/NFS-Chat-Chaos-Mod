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
  class GigaRubberband : public IGameEffect {
    OpenCarbon::PVehicle* mTargetPVehicle;

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenCarbon::GameStatusEx::IsRacing(); }

    virtual bool _activate() noexcept override {
      if (!OpenCarbon::GameStatusEx::IsRacing()) return false;

      auto* race_status = OpenCarbon::GRaceStatus::Get();
      if (!race_status) return false;

      auto* player_vehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return false;

      OpenCarbon::GRacerInfo   player_racer_info;
      std::vector<std::size_t> available_ids;

      for (std::int32_t i = 0; i < race_status->mRacerCount; i++) {
        auto* handle = race_status->mRacerInfo[i].mhSimable;
        if (!handle) continue;

        // Get available ids
        if (handle == player_vehicle->GetOwnerHandle())
          player_racer_info = race_status->mRacerInfo[i];
        else
          available_ids.push_back(i);
      }

      // Shuffle available ids
      std::shuffle(available_ids.begin(), available_ids.end(), Random::Get().GetGenerator());
      auto& target_racer = race_status->mRacerInfo[available_ids[0]];

      OpenCarbon::PVehicleEx::ForEachInstance([&](OpenCarbon::PVehicle* pvehicle) {
        if (pvehicle->GetOwnerHandle() == target_racer.mhSimable) mTargetPVehicle = pvehicle;
      });

      if (!mTargetPVehicle) return false;
      // Stop car
      mTargetPVehicle->ForceStopOn(OpenCarbon::IVehicle::ForceStopType::ForceStop);

      return true;
    }
    virtual bool _deactivate() noexcept override {
      if (!mTargetPVehicle) return true;
      mTargetPVehicle->ForceStopOff(OpenCarbon::IVehicle::ForceStopType::ForceStop);

      return true;
    }

    virtual void _activeTick() noexcept override {
      if (!OpenCarbon::GameStatusEx::IsRacing() || !(mTargetPVehicle | OpenCarbon::PVehicleEx::ValidatePVehicle)) return;

      auto* player_vehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;
      auto* player_rb = player_vehicle->GetRigidBody();
      if (!player_rb) return;
      auto* target_rb = mTargetPVehicle->GetRigidBody();
      if (!target_rb) return;

      auto                       position = player_rb->GetPosition();
      OpenCarbon::UMath::Vector3 direction;
      player_rb->GetForwardVector(direction);

      position.x += direction.x * 10.0f;
      position.y += direction.y * 10.0f;

      target_rb->SetPosition(position);
    }

   public:
    explicit GigaRubberband() : IGameEffect(68), mTargetPVehicle(nullptr) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
