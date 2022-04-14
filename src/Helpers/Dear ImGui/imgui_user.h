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
#include <cstddef>  // size_t
#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui {
  class WithItemFlag {
    bool mIsFlagEnabled;

   public:
    WithItemFlag(ImGuiItemFlags option, bool enabled = true);
    ~WithItemFlag();

    operator bool();
  };
  class WithItemWidth {
    bool mIsWidthEnabled;

   public:
    WithItemWidth(float width, bool enabled = true);
    ~WithItemWidth();

    operator bool();
  };
  class WithColor {
    bool mIsStyleEnabled;

   public:
    WithColor(ImGuiCol color, ImU32 value, bool enabled = true);
    WithColor(ImGuiCol color, const ImVec4& value, bool enabled = true);
    ~WithColor();

    operator bool();
  };
  class WithStyle {
    bool mIsStyleEnabled;

   public:
    WithStyle(ImGuiStyleVar style, float value, bool enabled = true);
    WithStyle(ImGuiStyleVar style, const ImVec2& value, bool enabled = true);
    ~WithStyle();

    operator bool();
  };

  struct Rectangle {
    float x, y, width, height;

    float GetBottom() const;
    float GetRight() const;

    ImVec2 GetXY() const;
    ImVec2 GetWidthHeight() const;
    ImVec2 GetRightBottom() const;

    Rectangle();
    Rectangle(float x, float y, float width, float height);
  };

  IMGUI_API void LoadStyle();
  IMGUI_API void ShowNotice(const char* notice);
  IMGUI_API bool FullWidthButton(const char* str);
  IMGUI_API bool InputTextWithHintAlways(const char* label, const char* hint, char* buf, std::size_t buf_size, ImGuiInputTextFlags flags = 0,
                                         ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
}  // namespace ImGui
