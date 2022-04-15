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

namespace Extensions::Game::MW05::Modifiers {
  struct InputModifier : IGameplayModifier {
    bool mIgnoreInputEnabled;
    bool mIgnoreSteeringEnabled;
    bool mIgnoreBrakingEnabled;
    bool mInvertedSteeringEnabled;
    bool mInvertedSteeringRandomizerEnabled;

    bool IsSteeringAction(OpenMW::ActionRef action) {
      bool ret = false;
      ret |= action->mId == OpenMW::ActionData::ActionID::GAMEACTION_STEERLEFT;
      ret |= action->mId == OpenMW::ActionData::ActionID::GAMEACTION_STEERRIGHT;
      ret |= action->mId == OpenMW::ActionData::ActionID::GAMEACTION_TURNLEFT;
      ret |= action->mId == OpenMW::ActionData::ActionID::GAMEACTION_TURNRIGHT;

      return ret;
    }

   private:
    explicit InputModifier() :
        mIgnoreInputEnabled(false),
        mIgnoreSteeringEnabled(false),
        mIgnoreBrakingEnabled(false),
        mInvertedSteeringEnabled(false),
        mInvertedSteeringRandomizerEnabled(false) {}

   public:
    virtual void OnTick() override {
      if (!mInvertedSteeringRandomizerEnabled) return;

      __EXECUTE_EVERY_X_SECONDS__(Random::Get().Generate(2.0f, 5.0f));
      if (Random::Get().Generate(0, 1) == 1) mInvertedSteeringEnabled = !mInvertedSteeringEnabled;
    }

    void ParseAction(OpenMW::InputPlayer* input, OpenMW::ActionRef action) {
      if (mIgnoreInputEnabled) {
        input->ClearInput();
        std::memset(action, 0, sizeof(OpenMW::ActionData));
        return;
      }

      if (mInvertedSteeringEnabled) {
        input->mControls.mBanking          = -input->mControls.mBanking;
        input->mControls.mSteering         = -input->mControls.mSteering;
        input->mControls.mSteeringVertical = -input->mControls.mSteeringVertical;
        input->mControls.mStrafeVertical   = -input->mControls.mStrafeVertical;
        input->mControls.mStrafeHorizontal = -input->mControls.mStrafeHorizontal;

        switch (action->mId) {
          case OpenMW::ActionData::ActionID::GAMEACTION_STEERLEFT:
            action->mId = OpenMW::ActionData::ActionID::GAMEACTION_STEERRIGHT;
            break;
          case OpenMW::ActionData::ActionID::GAMEACTION_STEERRIGHT:
            action->mId = OpenMW::ActionData::ActionID::GAMEACTION_STEERLEFT;
            break;
          case OpenMW::ActionData::ActionID::GAMEACTION_TURNLEFT:
            action->mId = OpenMW::ActionData::ActionID::GAMEACTION_TURNRIGHT;
            break;
          case OpenMW::ActionData::ActionID::GAMEACTION_TURNRIGHT:
            action->mId = OpenMW::ActionData::ActionID::GAMEACTION_TURNLEFT;
            break;
        }
      }
      if (mIgnoreSteeringEnabled) {
        input->mControls.mBanking          = 0.0f;
        input->mControls.mSteering         = 0.0f;
        input->mControls.mSteeringVertical = 0.0f;
        input->mControls.mStrafeVertical   = 0.0f;
        input->mControls.mStrafeHorizontal = 0.0f;
        if (IsSteeringAction(action)) std::memset(action, 0, sizeof(OpenMW::ActionData));
      }
      if (mIgnoreBrakingEnabled) {
        if (action->mId == OpenMW::ActionData::ActionID::GAMEACTION_BRAKE) {
          bool reset_brakes = false;
          if (auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance()) reset_brakes = pvehicle->GetSpeed() > 0.1f;
          if (reset_brakes) {
            input->mControls.mBrake = 0.0f;
            std::memset(action, 0, sizeof(OpenMW::ActionData));
          }
        } else if (action->mId == OpenMW::ActionData::ActionID::GAMEACTION_HANDBRAKE) {
          input->mControls.mHandBrake = 0.0f;
          std::memset(action, 0, sizeof(OpenMW::ActionData));
        }
      }
    }

    void SetIgnoreInput(bool enabled) { mIgnoreInputEnabled = enabled; }
    void SetIgnoreSteering(bool enabled) { mIgnoreSteeringEnabled = enabled; }
    void SetIgnoreBraking(bool enabled) { mIgnoreBrakingEnabled = enabled; }
    void SetInvertedSteering(bool enabled) { mInvertedSteeringEnabled = enabled; }
    void SetInvertedSteeringRandomizer(bool enabled) { mInvertedSteeringRandomizerEnabled = enabled; }

    InputModifier(const InputModifier&) = delete;
    void operator=(const InputModifier&) = delete;

    static inline InputModifier& Get() {
      static InputModifier singleton;
      return singleton;
    }
  };
}  // namespace Extensions::Game::MW05::Modifiers
