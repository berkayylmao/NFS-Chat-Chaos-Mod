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
  class TurnUpTheHeat : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override {
      auto* ai = OpenCarbon::AIVehicleEx::GetPlayerInstance() | OpenCarbon::AIVehicleEx::AsAIVehicleHuman;
      if (!ai || !ai->GetPursuit()) return false;

      return ai->GetHeat() < 10.0f;
    }

    virtual bool _activate() noexcept override {
      auto* ai = OpenCarbon::AIVehicleEx::GetPlayerInstance() | OpenCarbon::AIVehicleEx::AsAIVehicleHuman;
      if (!ai) return false;

      ai->SetHeat(std::min(10.0f, ai->GetHeat() + 1.0f));
      return true;
    }

   public:
    explicit TurnUpTheHeat() : IGameEffect(29) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
