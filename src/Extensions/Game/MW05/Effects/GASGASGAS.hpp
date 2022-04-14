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
  class GASGASGAS : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      auto* input = OpenMW::InputEx::GetPlayerInstance() | OpenMW::InputEx::AsInputPlayer;
      if (!input) return false;

      input->ClearInput();

      OpenMW::Variables::Tweak_InfiniteNOS = true;
      return true;
    }
    virtual bool _deactivate() noexcept override {
      auto* input = OpenMW::InputEx::GetPlayerInstance() | OpenMW::InputEx::AsInputPlayer;
      if (!input) return false;

      input->SetControlGas(0.0f);
      input->SetControlNOS(false);

      OpenMW::Variables::Tweak_InfiniteNOS = false;
      return true;
    }

    virtual void _activeTick() noexcept override {
      auto* player_vehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!player_vehicle) return;

      auto* input = player_vehicle->mInput | OpenMW::InputEx::AsInputPlayer;
      if (!input) return;

      float steering = input->GetControls().mSteering;
      input->ClearInput();
      auto& controls      = input->GetControls();
      controls.mBrake     = 0.0f;
      controls.mHandBrake = 0.0f;
      controls.mGas       = 1.0f;
      controls.mNOS       = true;
      controls.mSteering  = steering;
    }

   public:
    explicit GASGASGAS() : IGameEffect(42) {}
  };
}  // namespace Extensions::Game::MW05::Effects
