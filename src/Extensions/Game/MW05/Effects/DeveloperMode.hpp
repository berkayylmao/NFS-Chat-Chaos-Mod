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
  class DeveloperMode : public IGameEffect {
    OpenMW::Attrib::StringKey     mSavedVehicleKey;
    OpenMW::FECustomizationRecord mSavedCustomizations;

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return !OpenMW::GameStatusEx::IsInPursuit(); }

    virtual bool _activate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;
      // Save player car
      {
        mSavedVehicleKey = OpenMW::Attrib::StringToKey(pvehicle->GetVehicleName());
        if (auto* customizations = pvehicle->GetCustomizations()) mSavedCustomizations = *customizations;
      }
      // Change car
      if (!OpenMW::PVehicleEx::ChangePlayerVehicle(OpenMW::Attrib::StringToKey("speedtest"), nullptr)) return false;
      // Enable wireframe mode
      ChaosMod::GetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      // Change back to player vehicle
      OpenMW::PVehicleEx::ChangePlayerVehicle(mSavedVehicleKey, &mSavedCustomizations);
      // Disable wireframe mode
      ChaosMod::GetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
      return true;
    }

   public:
    explicit DeveloperMode() : IGameEffect(16), mSavedVehicleKey(0), mSavedCustomizations() {}
  };
}  // namespace Extensions::Game::MW05::Effects
