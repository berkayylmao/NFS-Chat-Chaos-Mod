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

namespace Extensions::Game::MW05::Effects {
  class Flashbang : public IGameEffect {
    // seconds
    const float mEffectDuration = 4.0f;
    float       mShownDuration;

   protected:
    virtual bool _activate() noexcept override {
      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::Flashbang);

      mShownDuration = 0.0f;
      return true;
    }

    virtual void _draw(const ImGuiViewport* viewport) noexcept override {
      if (this->GetElapsedTime() < 1950i64) return;
      if (mShownDuration > mEffectDuration) return;

      ImGui::WithColor _c1(ImGuiCol_WindowBg, IM_COL32_WHITE);

      ImGui::SetNextWindowBgAlpha(1.0f - mShownDuration / mEffectDuration);
      ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Always);
      ImGui::SetNextWindowSize(viewport->Size * 2.0f, ImGuiCond_Always);
      ImGui::Begin("##flashbang_effect_window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBringToFrontOnFocus);
      ImGui::End();

      mShownDuration += ImGui::GetIO().DeltaTime;
    };

   public:
    explicit Flashbang() : IGameEffect(52), mShownDuration(0.0f) {}
  };
}  // namespace Extensions::Game::MW05::Effects
