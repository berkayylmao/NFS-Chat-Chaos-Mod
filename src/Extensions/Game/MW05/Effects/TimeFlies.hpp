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
  class TimeFlies : public IGameEffect {
    float        mSkyBoxSpeedMultiplier;
    std::int32_t mTimeOfDaySpeedMultiplier;

   protected:
    virtual bool _activate() noexcept override {
      auto* tod = OpenMW::TimeOfDay::GetInstance();
      if (!tod) return false;

      mSkyBoxSpeedMultiplier    = tod->mSkyboxSpeedMultiplier;
      mTimeOfDaySpeedMultiplier = tod->mTimeOfDaySpeedMultiplier;

      tod->mSkyboxSpeedMultiplier *= 30.0f;
      tod->mTimeOfDaySpeedMultiplier *= 30;
      return true;
    }
    virtual bool _deactivate() noexcept override {
      auto* tod = OpenMW::TimeOfDay::GetInstance();
      if (!tod) return false;

      tod->mSkyboxSpeedMultiplier    = mSkyBoxSpeedMultiplier;
      tod->mTimeOfDaySpeedMultiplier = mTimeOfDaySpeedMultiplier;
      return true;
    }

   public:
    explicit TimeFlies() : IGameEffect(89), mSkyBoxSpeedMultiplier(0.0f), mTimeOfDaySpeedMultiplier(0) {}
  };
}  // namespace Extensions::Game::MW05::Effects
