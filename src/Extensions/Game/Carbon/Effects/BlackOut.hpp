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
  class BlackOut : public IGameEffect {
    // seconds
    const float mEffectDuration = 0.99f;
    float       mShownDuration;

   protected:
    virtual bool _activate() noexcept override {
      mShownDuration                         = 0.0f;
      OpenCarbon::Variables::Tweak_GameSpeed = 100.0f;

      return true;
    }
    virtual bool _deactivate() noexcept override {
      OpenCarbon::Variables::Tweak_GameSpeed = 1.0f;
      return true;
    }

    virtual void _draw(const ImGuiViewport* viewport) noexcept override {
      if (mShownDuration > mEffectDuration) return;

      ImGui::WithColor _c1(ImGuiCol_WindowBg, IM_COL32_BLACK);

      ImGui::SetNextWindowBgAlpha(1.0f - mShownDuration / mEffectDuration);
      ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Always);
      ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Always);
      ImGui::Begin("##blackout_effect_window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs);
      ImGui::End();

      mShownDuration += ImGui::GetIO().DeltaTime;
    };

   public:
    explicit BlackOut() : IGameEffect(73), mShownDuration(0.0f) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
