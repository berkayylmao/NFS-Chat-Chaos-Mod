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
  class EnterTheMatrix : public IGameEffect {
    OpenMW::TimeOfDayEx::Backup                      mBackup;
    std::vector<OpenMW::TimeOfDayLightingEx::Backup> mBackupLighting;

   protected:
    virtual bool _activate() noexcept override {
      auto* tod = OpenMW::TimeOfDay::GetInstance();
      if (!tod) return false;

      mBackup = OpenMW::TimeOfDayEx::Backup::CreateBackup(tod);
      mBackupLighting.clear();

      tod->mSkyboxSpeedMultiplier    = 0.0f;
      tod->mTimeOfDaySpeedMultiplier = 0;
      tod->mTimeOfDayValue           = 0.1f;
      tod->mSunOrbitAxis.x           = 190.0f;
      tod->mSunOrbitAxis.y           = -20.0f;

      OpenMW::TimeOfDayLightingEx::ForEach([&](OpenMW::Attrib::Collection* collection, OpenMW::Attrib::Layouts::timeofdaylightinglayout* layout) {
        mBackupLighting.push_back(OpenMW::TimeOfDayLightingEx::Backup::CreateBackup(collection));

        layout->SpecularColour         = OpenMW::Attrib::RGBA(0.0f, 1.0f, 0.0f, 1.0f);
        layout->DiffuseColour          = OpenMW::Attrib::RGBA(0.1f, 0.4f, 0.05f, 1.0f);
        layout->AmbientColour          = OpenMW::Attrib::RGBA(0.1f, 0.4f, 0.05f, 1.0f);
        layout->FogHazeColour          = OpenMW::Attrib::RGBA(0.6f, 1.0f, 0.6f, 1.0f);
        layout->FixedFunctionSkyColour = OpenMW::Attrib::RGBA(0.0f, 1.0f, 0.0f, 1.0f);
        layout->FogSkyColour           = OpenMW::Attrib::RGBA(0.0f, 1.0f, 0.0f, 1.0f);
        layout->FogDistanceScale       = 30.0f;
        layout->FogHazeColourScale     = 10.0f;
        layout->FogSkyColourScale      = 5.0f;
        layout->EnvSkyBrightness       = 10.0f;
        layout->CarSpecScale           = 100.0f;
        if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("FogInLightScatter"))) *var = 15.0f;
        if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("FogSunFalloff"))) *var = 1.0f;
      });

      ChaosMod::GetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      mBackup.RestoreBackup();
      for (const auto& backup : mBackupLighting) backup.RestoreBackup();

      ChaosMod::GetD3D9Device()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
      return true;
    }

   public:
    explicit EnterTheMatrix() : IGameEffect(2) {}
  };
}  // namespace Extensions::Game::MW05::Effects
