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
  class ThePSPExperience : public IGameEffect {
    std::chrono::system_clock::time_point mTimeFrameStart;
    std::chrono::system_clock::time_point mTimeFrameEnd;

   protected:
    virtual bool _activate() noexcept override {
      mTimeFrameStart = std::chrono::system_clock::now();
      mTimeFrameEnd   = std::chrono::system_clock::now();

      OpenMW::Variables::ForceCarLOD         = OpenMW::CARPART_LOD::D;
      OpenMW::Variables::ForceTireLOD        = OpenMW::CARPART_LOD::D;
      OpenMW::Variables::DrawCarShadow       = false;
      OpenMW::Variables::DrawCarsReflections = false;
      OpenMW::Variables::DrawLightFlares     = false;

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::DistortedMWSong);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      OpenMW::Variables::ForceCarLOD         = OpenMW::CARPART_LOD::OFF;
      OpenMW::Variables::ForceTireLOD        = OpenMW::CARPART_LOD::OFF;
      OpenMW::Variables::DrawCarShadow       = true;
      OpenMW::Variables::DrawCarsReflections = true;
      OpenMW::Variables::DrawLightFlares     = true;
      return true;
    }
    virtual void _activeTick() noexcept override {
      mTimeFrameStart                                     = std::chrono::system_clock::now();
      std::chrono::duration<double, std::milli> work_time = mTimeFrameStart - mTimeFrameEnd;

      if (work_time.count() < 50.0) {
        std::chrono::duration<double, std::milli> delta_ms(50.0 - work_time.count());
        std::this_thread::sleep_for(delta_ms);
      }

      mTimeFrameEnd = std::chrono::system_clock::now();
    }

   public:
    explicit ThePSPExperience() : IGameEffect(63) {}
  };
}  // namespace Extensions::Game::MW05::Effects
