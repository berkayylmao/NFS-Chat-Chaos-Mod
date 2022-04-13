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
  class ThanosSnap : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      auto        count_pvehicles = OpenCarbon::PVehicle::GetInstancesCount();
      std::size_t count_affected  = count_pvehicles / 2;
      const auto& idx_affected    = Random::Get().GenerateUniqueRange(count_affected, 0, count_pvehicles - 1);
      for (const auto& idx : idx_affected) {
        auto* pvehicle = OpenCarbon::PVehicle::GetInstance(idx) | OpenCarbon::PVehicleEx::ValidatePVehicle;
        if (!pvehicle) continue;

        pvehicle->Deactivate();
      }

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::FingerSnap);
      return true;
    }

   public:
    explicit ThanosSnap() : IGameEffect(0) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
