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
  struct CarScaleModifier : IGameplayModifier {
    struct CarScaleVector {
      float x, y, z;
      explicit CarScaleVector(float x, float y, float z) : x(x), y(y), z(z) {}
    };

   protected:
    static constexpr float CONST_NOT_USED_MARKER = -123.456f;

    const CarScaleVector sRCCarsScale    = CarScaleVector(0.4f, 0.4f, 0.4f);
    const CarScaleVector sWideCarsScale  = CarScaleVector(CONST_NOT_USED_MARKER, CONST_NOT_USED_MARKER, 4.0f);
    const CarScaleVector sPaperCarsScale = CarScaleVector(CONST_NOT_USED_MARKER, CONST_NOT_USED_MARKER, 0.001f);
    CarScaleVector       mJellyCarsScale;

    bool mRCCarsEnabled;
    bool mWideCarsEnabled;
    bool mPaperCarsEnabled;
    bool mReversedCarsEnabled;
    bool mJellyCarsEnabled;

    std::uint32_t mCountEnabled;

    void _transformJelly() {
      static bool sLengthIncreasing = false;
      static bool sWidthIncreasing  = false;
      static bool sHeightIncreasing = false;
      static auto sFnDoScale        = [](float& val, bool& inc, const float factor, const float max) {
        if (inc) {
          val += factor;
          inc = val < max;
        } else {
          val -= factor;
          inc = val < 0.5f;
        }
      };

      sFnDoScale(mJellyCarsScale.y, sLengthIncreasing, 0.02f, 1.5f);
      sFnDoScale(mJellyCarsScale.z, sWidthIncreasing, 0.075f, 3.0f);
      sFnDoScale(mJellyCarsScale.x, sHeightIncreasing, 0.04f, 2.0f);
    }

    virtual void _onEnabled() { OpenMW::Variables::DrawLightFlares = false; }
    virtual void _onDisabled() {
      OpenMW::Variables::DrawLightFlares = true;
      // Default values
      OpenMW::Variables::CarScaleMatrix.GetField().v0.y = 1.0f;
      OpenMW::Variables::CarScaleMatrix.GetField().v1.z = 1.0f;
      OpenMW::Variables::CarScaleMatrix.GetField().v2.x = 1.0f;
    }
    virtual void _onTick() {  // Default values
      OpenMW::Variables::CarScaleMatrix.GetField().v0.y = 1.0f;
      OpenMW::Variables::CarScaleMatrix.GetField().v1.z = 1.0f;
      OpenMW::Variables::CarScaleMatrix.GetField().v2.x = 1.0f;

      if (mRCCarsEnabled) {
        OpenMW::Variables::CarScaleMatrix.GetField().v0.y = sRCCarsScale.y;
        OpenMW::Variables::CarScaleMatrix.GetField().v1.z = sRCCarsScale.z;
        OpenMW::Variables::CarScaleMatrix.GetField().v2.x = sRCCarsScale.x;
      }

      if (mWideCarsEnabled)
        OpenMW::Variables::CarScaleMatrix.GetField().v1.z = sWideCarsScale.z;
      else if (mPaperCarsEnabled)
        OpenMW::Variables::CarScaleMatrix.GetField().v1.z = sPaperCarsScale.z;

      if (mJellyCarsEnabled) {
        _transformJelly();
        OpenMW::Variables::CarScaleMatrix.GetField().v0.y *= mJellyCarsScale.y;
        OpenMW::Variables::CarScaleMatrix.GetField().v1.z *= mJellyCarsScale.z;
        OpenMW::Variables::CarScaleMatrix.GetField().v2.x *= mJellyCarsScale.x;
      }

      if (mReversedCarsEnabled) {
        OpenMW::Variables::CarScaleMatrix.GetField().v0.y *= -1.0f;
        OpenMW::Variables::CarScaleMatrix.GetField().v1.z *= -1.0f;
      }
    }

    void _incEnabled() {
      mCountEnabled += 1;
      _onEnabled();
    }
    void _decEnabled() {
      if (mCountEnabled > 0) mCountEnabled -= 1;
      if (mCountEnabled == 0) _onDisabled();
    }

   public:
    void EnableRCCars() {
      mRCCarsEnabled = true;
      _incEnabled();
    }
    void DisableRCCars() {
      mRCCarsEnabled = false;
      _decEnabled();
    }

    void EnableWideCars() {
      mWideCarsEnabled = true;
      _incEnabled();
    }
    void DisableWideCars() {
      mWideCarsEnabled = false;
      _decEnabled();
    }

    void EnablePaperCars() {
      mPaperCarsEnabled = true;
      _incEnabled();
    }
    void DisablePaperCars() {
      mPaperCarsEnabled = false;
      _decEnabled();
    }

    void EnableReversedCars() {
      mReversedCarsEnabled = true;
      _incEnabled();
    }
    void DisableReversedCars() {
      mReversedCarsEnabled = false;
      _decEnabled();
    }

    void EnableJellyCars() {
      mJellyCarsScale   = CarScaleVector(1.0f, 1.0f, 1.0f);
      mJellyCarsEnabled = true;
      _incEnabled();
    }
    void DisableJellyCars() {
      mJellyCarsEnabled = false;
      _decEnabled();
    }
    auto& GetJellyCarsScale() { return mJellyCarsScale; }

    virtual void OnTick() override {
      if (mCountEnabled > 0) _onTick();
    }

   private:
    CarScaleModifier() :
        mCountEnabled(0),
        mRCCarsEnabled(false),
        mWideCarsEnabled(false),
        mPaperCarsEnabled(false),
        mReversedCarsEnabled(false),
        mJellyCarsEnabled(false),
        mJellyCarsScale(CarScaleVector(1.0f, 1.0f, 1.0f)) {}

   public:
    CarScaleModifier(const CarScaleModifier&) = delete;
    void operator=(const CarScaleModifier&) = delete;

    static inline CarScaleModifier& Get() {
      static CarScaleModifier singleton;
      return singleton;
    }
  };
}  // namespace Extensions::Game::MW05::Modifiers
