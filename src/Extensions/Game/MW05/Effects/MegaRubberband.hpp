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
  class MegaRubberband : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return OpenMW::GameStatusEx::IsRacing(); }

    virtual bool _deactivate() noexcept override {
      if (!OpenMW::GameStatusEx::IsRacing()) return true;

      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        if (pvehicle->IsPlayer() || pvehicle->IsOwnedByPlayer()) return;

        auto* ai = pvehicle->GetAIVehiclePtr() | OpenMW::AIVehicleEx::AsAIVehicleRacecar;
        if (!ai) return;

        ai->fBaseSkill = 0.0f;
        ai->fGlueSkill = 0.0f;
        ai->fGlueTimer = 10.0f;
      });

      return true;
    }
    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(1.0f);
      if (!OpenMW::GameStatusEx::IsRacing()) return;

      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        if (pvehicle->IsPlayer() || pvehicle->IsOwnedByPlayer()) return;

        auto* ai = pvehicle->GetAIVehiclePtr() | OpenMW::AIVehicleEx::AsAIVehicleRacecar;
        if (!ai) return;

        ai->fBaseSkill = 10000.0f;
        ai->fGlueSkill = 10000.0f;
        ai->fGlueTimer = 0.1f;
      });
    }

   public:
    explicit MegaRubberband() : IGameEffect(69) {}
  };
}  // namespace Extensions::Game::MW05::Effects
