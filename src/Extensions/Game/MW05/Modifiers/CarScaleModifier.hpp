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
    static constexpr float CONST_STEP_VALUE      = 0.1f;

    const CarScaleVector sRCCarsScale    = CarScaleVector(0.5f, 0.5f, 0.5f);
    const CarScaleVector sBigCarsScale   = CarScaleVector(1.5f, 1.5f, 1.5f);
    const CarScaleVector sFlatCarsScale  = CarScaleVector(0.1f, CONST_NOT_USED_MARKER, CONST_NOT_USED_MARKER);
    const CarScaleVector sTallCarsScale  = CarScaleVector(3.0f, CONST_NOT_USED_MARKER, CONST_NOT_USED_MARKER);
    const CarScaleVector sLongCarsScale  = CarScaleVector(CONST_NOT_USED_MARKER, 2.0f, CONST_NOT_USED_MARKER);
    const CarScaleVector sWideCarsScale  = CarScaleVector(CONST_NOT_USED_MARKER, CONST_NOT_USED_MARKER, 4.0f);
    const CarScaleVector sPaperCarsScale = CarScaleVector(CONST_NOT_USED_MARKER, CONST_NOT_USED_MARKER, 0.1f);
    CarScaleVector       mJellyCarsScale;

    bool mRCCarsEnabled;
    bool mBigCarsEnabled;
    bool mFlatCarsEnabled;
    bool mTallCarsEnabled;
    bool mLongCarsEnabled;
    bool mWideCarsEnabled;
    bool mPaperCarsEnabled;
    bool mFlippedCarsEnabled;
    bool mJellyCarsEnabled;

    std::uint32_t mCountEnabled;

    inline void _inc(float& val, float max) {
      if (val < max) val += CONST_STEP_VALUE;
    }
    inline void _dec(float& val, float min) {
      if (val > min) val -= CONST_STEP_VALUE;
    }
    inline void _clamp(float& val, float clampVal) {
      _inc(val, clampVal);
      _dec(val, clampVal);
    }
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
    virtual void _onTick() {
      OpenMW::UMath::Matrix4& mat = OpenMW::Variables::CarScaleMatrix;

      float& x = mat.v2.x;
      float& y = mat.v0.y;
      float& z = mat.v1.z;

      float final_x = 1.0f;
      float final_y = 1.0f;
      float final_z = 1.0f;

      if (mRCCarsEnabled) {
        if (!mFlatCarsEnabled && !mTallCarsEnabled) _dec(x, sRCCarsScale.x);
        if (!mLongCarsEnabled) _dec(y, sRCCarsScale.y);
        if (!mWideCarsEnabled && !mPaperCarsEnabled) _dec(z, sRCCarsScale.z);

        final_x = sRCCarsScale.x;
        final_y = sRCCarsScale.y;
        final_z = sRCCarsScale.z;
      } else if (mBigCarsEnabled) {
        if (!mFlatCarsEnabled && !mTallCarsEnabled) _inc(x, sBigCarsScale.x);
        if (!mLongCarsEnabled) _inc(y, sBigCarsScale.y);
        if (!mWideCarsEnabled && !mPaperCarsEnabled) _inc(z, sBigCarsScale.z);

        final_x = sBigCarsScale.x;
        final_y = sBigCarsScale.y;
        final_z = sBigCarsScale.z;
      }

      if (mFlatCarsEnabled)
        _clamp(x, final_x * sFlatCarsScale.x);
      else if (mTallCarsEnabled)
        _clamp(x, final_x * sTallCarsScale.x);

      if (mLongCarsEnabled) _clamp(y, final_y * sLongCarsScale.y);

      if (mWideCarsEnabled)
        _clamp(z, final_z * sWideCarsScale.z);
      else if (mPaperCarsEnabled)
        _clamp(z, final_z * sPaperCarsScale.z);

      if (mJellyCarsEnabled) {
        _transformJelly();
        final_x = (x *= mJellyCarsScale.x);
        final_y = (y *= mJellyCarsScale.y);
        final_z = (z *= mJellyCarsScale.z);
      }

      if (mFlippedCarsEnabled) {
        y *= -1.0f;
        z *= -1.0f;
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

    void EnableBigCars() {
      mBigCarsEnabled = true;
      _incEnabled();
    }
    void DisableBigCars() {
      mBigCarsEnabled = false;
      _decEnabled();
    }

    void EnableFlatCars() {
      mFlatCarsEnabled = true;
      _incEnabled();
    }
    void DisableFlatCars() {
      mFlatCarsEnabled = false;
      _decEnabled();
    }

    void EnableTallCars() {
      mTallCarsEnabled = true;
      _incEnabled();
    }
    void DisableTallCars() {
      mTallCarsEnabled = false;
      _decEnabled();
    }

    void EnableLongCars() {
      mLongCarsEnabled = true;
      _incEnabled();
    }
    void DisableLongCars() {
      mLongCarsEnabled = false;
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

    void EnableFlippedCars() {
      mFlippedCarsEnabled = true;
      _incEnabled();
    }
    void DisableFlippedCars() {
      mFlippedCarsEnabled = false;
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

    void PushEnabled() { _incEnabled(); }
    void PopEnabled() { _decEnabled(); }

    virtual void OnTick() override {
      if (mCountEnabled > 0) _onTick();
    }

   private:
    explicit CarScaleModifier() :
        mCountEnabled(0),
        mRCCarsEnabled(false),
        mBigCarsEnabled(false),
        mFlatCarsEnabled(false),
        mTallCarsEnabled(false),
        mLongCarsEnabled(false),
        mWideCarsEnabled(false),
        mPaperCarsEnabled(false),
        mFlippedCarsEnabled(false),
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
