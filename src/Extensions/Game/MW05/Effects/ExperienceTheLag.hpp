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
  class ExperienceTheLag : public IGameEffect {
    std::chrono::system_clock::time_point     mTimeFrameStart;
    std::chrono::system_clock::time_point     mTimeFrameEnd;
    std::chrono::duration<double, std::milli> mWorkTime;
    double                                    mWaitingTime;

   protected:
    virtual bool _activate() noexcept override {
      mTimeFrameStart = std::chrono::system_clock::now();
      mTimeFrameEnd   = std::chrono::system_clock::now();

      return true;
    }

    virtual void _activeTick() noexcept override {
      mTimeFrameStart = std::chrono::system_clock::now();
      mWorkTime += mTimeFrameStart - mTimeFrameEnd;

      if (mWorkTime.count() > mWaitingTime) {
        std::this_thread::sleep_for(std::chrono::milliseconds(Random::Get().Generate(200, 1600)));

        mWorkTime    = 0s;
        mWaitingTime = static_cast<double>(Random::Get().Generate(600.0f, 2400.0f));
      }

      mTimeFrameEnd = std::chrono::system_clock::now();
    }

   public:
    explicit ExperienceTheLag() : IGameEffect(37), mWorkTime(0s), mWaitingTime(0.0) {}
  };
}  // namespace Extensions::Game::MW05::Effects
