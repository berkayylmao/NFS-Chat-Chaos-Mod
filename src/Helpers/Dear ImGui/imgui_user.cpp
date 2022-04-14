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

#include "imgui_user.h"
#include <cstdint>

namespace ImGui {
#pragma region WithItemFlag
  WithItemFlag::WithItemFlag(ImGuiItemFlags option, bool enabled) : mIsFlagEnabled(enabled) { ImGui::PushItemFlag(option, enabled); }
  WithItemFlag::~WithItemFlag() { ImGui::PopItemFlag(); }
  WithItemFlag::operator bool() { return mIsFlagEnabled; }
#pragma endregion
#pragma region WithItemWidth
  WithItemWidth::WithItemWidth(float width, bool enabled) : mIsWidthEnabled(enabled) {
    if (enabled) ImGui::PushItemWidth(width);
  }
  WithItemWidth::~WithItemWidth() {
    if (mIsWidthEnabled) ImGui::PopItemWidth();
  }
  WithItemWidth::operator bool() { return mIsWidthEnabled; }
#pragma endregion
#pragma region WithColor
  WithColor::WithColor(ImGuiCol color, ImU32 value, bool enabled) : mIsStyleEnabled(enabled) {
    if (enabled) ImGui::PushStyleColor(color, value);
  }
  WithColor::WithColor(ImGuiCol color, const ImVec4& value, bool enabled) : mIsStyleEnabled(enabled) {
    if (enabled) ImGui::PushStyleColor(color, value);
  }
  WithColor::~WithColor() {
    if (mIsStyleEnabled) ImGui::PopStyleColor();
  }
  WithColor::operator bool() { return mIsStyleEnabled; }
#pragma endregion
#pragma region WithStyle
  WithStyle::WithStyle(ImGuiStyleVar style, float value, bool enabled) : mIsStyleEnabled(enabled) {
    if (enabled) ImGui::PushStyleVar(style, value);
  }
  WithStyle::WithStyle(ImGuiStyleVar style, const ImVec2& value, bool enabled) : mIsStyleEnabled(enabled) {
    if (enabled) ImGui::PushStyleVar(style, value);
  }
  WithStyle::~WithStyle() {
    if (mIsStyleEnabled) ImGui::PopStyleVar();
  }
  WithStyle::operator bool() { return mIsStyleEnabled; }
#pragma endregion

#pragma region Rectangle
  float Rectangle::GetBottom() const { return y + height; }
  float Rectangle::GetRight() const { return x + width; }

  ImVec2 Rectangle::GetXY() const { return ImVec2(x, y); }
  ImVec2 Rectangle::GetWidthHeight() const { return ImVec2(width, height); }
  ImVec2 Rectangle::GetRightBottom() const { return ImVec2(GetRight(), GetBottom()); }

  Rectangle::Rectangle() : x(0.0f), y(0.0f), width(0.0f), height(0.0f) {}
  Rectangle::Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
#pragma endregion

  /// Misc.

  IMGUI_API void LoadStyle() {
    auto& style                    = ImGui::GetStyle();
    style.Alpha                    = 0.85f;
    style.WindowPadding            = ImVec2(10.0f, 10.0f);
    style.WindowRounding           = 1.0f;
    style.WindowBorderSize         = 0.0f;
    style.WindowMinSize            = ImVec2(450.0f, 200.0f);
    style.WindowTitleAlign         = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding            = 1.0f;
    style.ChildBorderSize          = 0.0f;
    style.PopupRounding            = 2.0f;
    style.PopupBorderSize          = 1.0f;
    style.FramePadding             = ImVec2(4.0f, 4.0f);
    style.FrameRounding            = 1.0f;
    style.FrameBorderSize          = 0.0f;
    style.TabRounding              = 1.0f;
    style.TabBorderSize            = 0.0f;
    style.ItemSpacing              = ImVec2(5.0f, 5.0f);
    style.ItemInnerSpacing         = ImVec2(5.0f, 5.0f);
    style.IndentSpacing            = 25.0f;
    style.ScrollbarSize            = 10.0f;
    style.ScrollbarRounding        = 1.0f;
    style.GrabMinSize              = 5.0f;
    style.GrabRounding             = 1.0f;
    style.ButtonTextAlign          = ImVec2(0.5f, 0.5f);
    style.CellPadding              = ImVec2(2.0f, 2.0f);
    style.AntiAliasedLines         = true;
    style.AntiAliasedFill          = true;

    style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.70f, 0.44f, 0.00f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.80f, 0.50f, 0.00f, 0.40f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.80f, 0.40f, 0.03f, 0.80f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.89f, 0.49f, 0.03f, 0.80f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.30f, 0.30f, 0.30f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.50f, 0.50f, 0.50f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.89f, 0.49f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.80f, 0.44f, 0.02f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.89f, 0.49f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.80f, 0.44f, 0.02f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(1.00f, 0.56f, 0.04f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.89f, 0.49f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(1.00f, 0.63f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(1.00f, 0.63f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(1.00f, 0.63f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Separator]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.80f, 0.50f, 0.00f, 0.40f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.90f, 0.60f, 0.00f, 0.80f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Tab]                   = ImVec4(0.89f, 0.49f, 0.03f, 0.50f);
    style.Colors[ImGuiCol_TabHovered]            = ImVec4(1.00f, 0.56f, 0.04f, 1.00f);
    style.Colors[ImGuiCol_TabActive]             = ImVec4(0.89f, 0.49f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.89f, 0.49f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.85f, 0.53f, 0.00f, 0.40f);
    style.Colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    style.Colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
  }
  IMGUI_API void ShowNotice(const char* notice) {
    WithStyle _s1(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
    WithStyle _s2(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    WithStyle _s3(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
    WithStyle _s4(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    WithStyle _s5(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));
    WithStyle _s6(ImGuiStyleVar_WindowRounding, 5.0f);

    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Size / 2.0f - ImGui::CalcTextSize(notice) / 2.0f);
    if (ImGui::Begin(notice, nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize))
      ImGui::TextUnformatted(notice);
    ImGui::End();
  }
  IMGUI_API bool FullWidthButton(const char* label) {
    const ImVec2 available_region = ImGui::GetContentRegionAvail();
    const ImVec2 label_size       = ImGui::CalcTextSize(label);
    const ImVec2 button_size      = label_size.x > available_region.x ? label_size + (ImGui::GetStyle().FramePadding * 2.0f) : available_region;
    return ImGui::Button(label, ImVec2(button_size.x, 0.0f));
  }
  IMGUI_API bool InputTextWithHintAlways(const char* label, const char* hint, char* buf, std::size_t buf_size, ImGuiInputTextFlags flags,
                                         ImGuiInputTextCallback callback, void* user_data) {
    ImGuiWindow* _window = GetCurrentWindow();
    if (_window->SkipItems) return false;

    const ImVec2 cursor          = ImGui::GetCursorPos();
    const bool   is_text_changed = ImGui::InputTextEx(label, nullptr, buf, static_cast<std::int32_t>(buf_size), ImVec2(0, 0), flags, callback, user_data);

    ImGui::SetCursorPosX(cursor.x + ImGui::GetItemRectSize().x - ImGui::CalcTextSize(hint).x - ImGui::GetStyle().FramePadding.x);
    ImGui::SetCursorPosY(cursor.y + ImGui::GetStyle().FramePadding.y);
    ImGui::TextDisabled(hint);

    return is_text_changed;
  }
}  // namespace ImGui
