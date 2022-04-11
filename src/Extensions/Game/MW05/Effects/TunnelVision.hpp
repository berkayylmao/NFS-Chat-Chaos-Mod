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
  class TunnelVision : public IGameEffect {
    std::vector<ImRect> mRectangles;

   protected:
    virtual bool _activate() noexcept override {
      const auto& size      = ImGui::GetIO().DisplaySize;
      float       square_px = size.y / 4.0f;
      mRectangles.clear();
      // top
      mRectangles.push_back(ImRect(0.0f, 0.0f, size.x, size.y / 2.0f - square_px / 2.0f));
      // left
      mRectangles.push_back(ImRect(0.0f, 0.0f, size.x / 2.0f - square_px / 2.0f, size.y));
      // right
      {
        float x = size.x / 2.0f + square_px / 2.0f;
        mRectangles.push_back(ImRect(x, 0.0f, size.x - x, size.y));
      }
      // bottom
      {
        float y = size.y / 2.0f + square_px / 2.0f;
        mRectangles.push_back(ImRect(0.0f, y, size.x, size.y - y));
      }

      return true;
    }

    virtual void _draw(const ImGuiViewport* viewport) noexcept override {
      static std::array<char, 20> window_name{};
      std::int32_t                window_id = 0;

      ImGui::WithColor _c1(ImGuiCol_WindowBg, IM_COL32_BLACK);
      for (const auto& rect : mRectangles) {
        window_name.fill(NULL);
        fmt::format_to_n(window_name.data(), window_name.max_size(), "##TunnelVision_{}", window_id++);

        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::SetNextWindowPos(viewport->Pos + rect.Min, ImGuiCond_Always);
        ImGui::SetNextWindowSize(rect.Max, ImGuiCond_Always);
        ImGui::Begin(window_name.data(), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::End();
      }
    };

   public:
    explicit TunnelVision() : IGameEffect(80) {}
  };
}  // namespace Extensions::Game::MW05::Effects
