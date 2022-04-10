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
  class AYAYAAYAYA : public IGameEffect {
    std::vector<FMOD::Sound*> mMoans          = {};
    std::vector<std::int32_t> mMoanOrder      = {0, 1, 2, 3, 4, 5, 6};
    std::int32_t              mCurrentMoanIdx = 0;

    void shuffleMoanOrder() { std::shuffle(mMoanOrder.begin(), mMoanOrder.end(), Random::Get().GetGenerator()); }

   protected:
    virtual void _activeTick() noexcept override {
      static std::size_t frames = 0;

      auto* input = OpenMW::InputEx::GetPlayerInstance() | OpenMW::InputEx::AsInputPlayer;
      if (!input) return;

      if (frames++ > 20 && input->GetControls().mGas < 0.3f) {
        if (mCurrentMoanIdx == 6) {
          shuffleMoanOrder();
          mCurrentMoanIdx = 0;
        }
        FMODWrapper::Get().PlaySoundFX(mMoans[mMoanOrder[mCurrentMoanIdx++]]);
        frames = 0;
      }
    }

   public:
    explicit AYAYAAYAYA() : IGameEffect(6) {
      shuffleMoanOrder();

      FMOD::Sound* _dummyPtr = nullptr;
      // Load anime moans
      for (std::int32_t i = 1; i <= 7; i++) {
        FMODWrapper::Get().mFMODSystem->createSound((ChaosMod::GetSoundFXDirectory() / fmt::format("animegirl{}.mp3", i)).u8string().c_str(), FMOD_LOOP_OFF, 0,
                                                    &_dummyPtr);
        mMoans.push_back(_dummyPtr);

        _dummyPtr = nullptr;
      }
    }
  };
}  // namespace Extensions::Game::MW05::Effects
