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
  class IfYouCantBeatThemKillThem : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override {
      return OpenCarbon::GameStatusEx::SecondsSinceStartedRacing() > 5 || OpenCarbon::GameStatusEx::SecondsSinceStartedPursuit() > 5;
    }

    virtual bool _activate() noexcept override {
      OpenCarbon::PVehicleEx::ForEachInstance([](OpenCarbon::PVehicle* pvehicle) {
        if (!pvehicle->IsPlayer() && !pvehicle->IsOwnedByPlayer()) OpenCarbon::Game::BlowEngine(pvehicle);
      });

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::IfYouCantBeatThemKillThem);
      return true;
    }

   public:
    explicit IfYouCantBeatThemKillThem() : IGameEffect(1) {}
  };
}  // namespace Extensions::Game::Carbon::Effects