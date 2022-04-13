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
  class PowerPointPresentation : public IGameEffect {
    std::chrono::system_clock::time_point mTimeFrameStart;
    std::chrono::system_clock::time_point mTimeFrameEnd;

   protected:
    virtual bool _activate() noexcept override {
      mTimeFrameStart = std::chrono::system_clock::now();
      mTimeFrameEnd   = std::chrono::system_clock::now();

      return true;
    }

    virtual void _activeTick() noexcept override {
      mTimeFrameStart                                     = std::chrono::system_clock::now();
      std::chrono::duration<double, std::milli> work_time = mTimeFrameStart - mTimeFrameEnd;

      if (work_time.count() < 400.0) {
        std::chrono::duration<double, std::milli> delta_ms(400.0 - work_time.count());
        std::this_thread::sleep_for(delta_ms);
      }

      mTimeFrameEnd = std::chrono::system_clock::now();
    }

   public:
    explicit PowerPointPresentation() : IGameEffect(20) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
