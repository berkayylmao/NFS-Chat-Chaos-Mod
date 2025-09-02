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

namespace Extensions::Game::Carbon::Effects {
  class DesignatedDriver : public IGameEffect {
    float mTargetSpeed;

   protected:
    virtual bool _deactivate() noexcept override {
      OpenCarbon::Variables::Tweak_GameSpeed = 1.0f;
      return true;
    }

    virtual void _activeTick() noexcept override {
      if (OpenCarbon::Variables::Tweak_GameSpeed < mTargetSpeed)
        OpenCarbon::Variables::Tweak_GameSpeed += 0.05f;
      else
        OpenCarbon::Variables::Tweak_GameSpeed -= 0.05f;

      __EXECUTE_EVERY_X_SECONDS__(1.0f);
      mTargetSpeed = Random::Get().Generate(0.1f, 2.0f);
    }

   public:
    explicit DesignatedDriver() : IGameEffect(39), mTargetSpeed(1.0f) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
