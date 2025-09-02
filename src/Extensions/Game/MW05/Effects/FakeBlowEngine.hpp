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
#include "Extensions/Game/IFakeGameEffect.hpp"

namespace Extensions::Game::MW05::Effects {
  class FakeBlowEngine : public IFakeGameEffect {
   protected:
    virtual bool _onRevealed() noexcept override {
      auto* input = OpenMW::InputEx::GetPlayerInstance();
      if (input) {
        input->SetControlSteering(0.0f);
        input->SetControlBanking(0.0f);
        input->SetControlSteeringVertical(0.0f);
        input->SetControlHandBrake(0.0f);
        return true;
      }

      return false;
    }

    virtual bool _activate() noexcept override {
      if (OpenMW::GameStatusEx::SecondsSinceStartedRacing() < 5 && OpenMW::GameStatusEx::SecondsSinceStartedRoaming() < 5) return false;
      OpenMW::GenericMessageEx::DisplayMessage("Blown engine!");
      return true;
    }
    virtual void _activeTick() noexcept override {
      if (this->mHasRevealed) return;

      auto* input = OpenMW::InputEx::GetPlayerInstance();
      if (input) {
        input->SetControlSteering(-0.4f);
        input->SetControlBanking(-0.4f);
        input->SetControlSteeringVertical(-0.4f);
        input->SetControlHandBrake(1.0f);
        input->SetControlGas(0.0f);
        input->SetControlBrake(0.0f);
      }
    }

   public:
    explicit FakeBlowEngine() : IFakeGameEffect(119) {}
  };
}  // namespace Extensions::Game::MW05::Effects
