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
  class FastAndFuriousNOS : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      OpenMW::Physics::Tunings new_tunings;
      // Get current tuning (if exists)
      if (auto* tunings = pvehicle->GetTunings()) new_tunings = *tunings;
      // Update NOS tuning
      new_tunings.mNOS = 2.5f;
      // Apply tuning
      pvehicle->SetTunings(new_tunings);

      OpenMW::Variables::Tweak_InfiniteNOS = true;
      return true;
    }
    virtual bool _deactivate() noexcept override {
      OpenMW::Variables::Tweak_InfiniteNOS = false;
      return true;
    }

   public:
    explicit FastAndFuriousNOS() : IGameEffect(40) {}
  };
}  // namespace Extensions::Game::MW05::Effects