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
  class RainbowRoad : public IGameEffect {
    std::vector<OpenMW::TimeOfDayLightingEx::Backup> mBackup;

   protected:
    virtual bool _activate() noexcept override {
      bool needs_backup = mBackup.empty();
      OpenMW::TimeOfDayLightingEx::ForEach([&](OpenMW::Attrib::Collection* collection, OpenMW::Attrib::Layouts::timeofdaylightinglayout* layout) {
        if (needs_backup) mBackup.push_back(OpenMW::TimeOfDayLightingEx::Backup(collection));

        layout->FogDistanceScale   = 2.0f;
        layout->FogHazeColourScale = 0.0f;
        layout->FogSkyColourScale  = 5.0f;
        layout->EnvSkyBrightness   = 5.0f;
        if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("FogInLightScatter"))) *var = 150.0f;
        if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("FogSunFalloff"))) *var = 5.0f;
      });

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::MarioKartStarFX);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      for (const auto& backup : mBackup) backup.RestoreBackup();

      return true;
    }

    virtual void _activeTick() noexcept override {
      static std::size_t frames = 10;

      if (frames++ > 10) {
        OpenMW::Attrib::RGBA rnd(Random::Get().Generate(0.0f, 1.0f), Random::Get().Generate(0.0f, 1.0f), Random::Get().Generate(0.0f, 1.0f), 1.0f);
        OpenMW::TimeOfDayLightingEx::ForEach([&rnd](OpenMW::Attrib::Collection*, OpenMW::Attrib::Layouts::timeofdaylightinglayout* layout) {
          layout->SpecularColour = rnd;
          layout->DiffuseColour  = rnd;
          layout->FogSkyColour   = rnd;
        });

        frames = 0;
      }
    }

   public:
    explicit RainbowRoad() : IGameEffect(9) {}
  };
}  // namespace Extensions::Game::MW05::Effects
