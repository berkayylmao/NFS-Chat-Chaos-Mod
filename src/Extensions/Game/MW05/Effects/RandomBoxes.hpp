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
  class RandomBoxes : public IGameEffect {
    static constexpr float sBoxSize = 128.0f;
    std::vector<ImRect>    mBoxes;

    void generateBoxes() {
      __EXECUTE_EVERY_X_SECONDS__(5.0f);
      mBoxes.clear();

      const auto& screen_size            = ImGui::GetIO().DisplaySize;
      auto        max_boxes_horizontally = static_cast<std::size_t>(screen_size.x / sBoxSize);
      auto        max_boxes_vertically   = static_cast<std::size_t>((screen_size.y * 2.0f) / sBoxSize);
      std::size_t box_amount             = max_boxes_horizontally * max_boxes_vertically;
      for (size_t i = 0; i < box_amount; i++) {
        if (Random::Get().Generate(0, 1) == 0) continue;
        std::size_t box_idx_horizontal = i % max_boxes_horizontally;
        std::size_t box_idx_vertical   = i % max_boxes_vertically;

        ImVec2 box_pos = ImVec2(
            // x
            box_idx_horizontal * sBoxSize,
            // y
            box_idx_vertical * sBoxSize);
        mBoxes.push_back(ImRect(box_pos, box_pos + ImVec2(sBoxSize, sBoxSize)));
      }
    }

   protected:
    virtual void _draw(const ImGuiViewport* viewport) noexcept override {
      generateBoxes();

      ImGui::WithStyle _s1(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s2(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s3(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s4(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s5(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s6(ImGuiStyleVar_WindowRounding, 0.0f);

      ImGui::SetNextWindowBgAlpha(0.0f);
      ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Always);
      ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Always);
      ImGui::Begin("##randomboxeseffectwindow", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBringToFrontOnFocus);
      for (const auto& box : mBoxes) ImGui::GetWindowDrawList()->AddRectFilled(box.Min, box.Max, IM_COL32_BLACK);
      ImGui::End();
    };

   public:
    explicit RandomBoxes() : IGameEffect(105) {}
  };
}  // namespace Extensions::Game::MW05::Effects
