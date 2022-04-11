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
// Menu
#include "D3D9.Menu.hpp"
// Overlay
#include "D3D9.Overlay.hpp"

#pragma warning(push, 0)
// Dear ImGui
#include "Helpers/Dear ImGui/misc/fonts/OpenSans-SemiBold.hpp"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Logo sprite
#include "Extensions/D3D9/Videos/MainMenuLogoSprite.hpp"
#pragma warning(pop)

namespace Extensions::D3D9 {
  namespace details {
    /// CONSTANTS

    constexpr static char CONST_UI_TITLE[]        = "NFS Chat Chaos Mod";
    constexpr static char CONST_UI_TITLE_MAIN[]   = "Main";
    constexpr static char CONST_UI_TITLE_TWITCH[] = "Twitch";
    constexpr static char CONST_UI_TITLE_CONFIG[] = "Configuration";
    constexpr static char CONST_UI_TITLE_ABOUT[]  = "About";

    /// FIELDS

    static bool sIsMenuVisible = true;

    // Logo Loop
    static std::uint8_t       sLogoFrame = 0;
    static LPDIRECT3DTEXTURE9 sLogoSprite;

    /// HOOKS

    static void __stdcall BeginScene(LPDIRECT3DDEVICE9) {
      ImGui_ImplDX9_NewFrame();
      ImGui_ImplWin32_NewFrame();
      ImGui::NewFrame();

      ImGui::GetIO().FontGlobalScale = std::max(0.9f, ImGui::GetIO().DisplaySize.y / 1080.0f);  // 1080p as base
    }
    static void __stdcall EndScene(LPDIRECT3DDEVICE9) {
      if (!ImGui::GetCurrentContext()->WithinFrameScope) return;
      const ImGuiViewport* viewport         = ImGui::GetMainViewport();
      const bool           is_chaos_running = Shared::IsChaosRunning();

      Overlay::DrawEffectsDisplay(viewport);

      if (sIsMenuVisible) {
        ImGui::SetNextWindowPos(viewport->Pos + ImVec2(8.0f, 8.0f), ImGuiCond_Once);
        if (ImGui::Begin(CONST_UI_TITLE, &sIsMenuVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
          if (ImGui::BeginTabBar("##NFS_CHAT_CHAOS_TABBAR", ImGuiTabBarFlags_FittingPolicyResizeDown)) {
            // Main Tab
            if (ImGui::BeginTabItem(CONST_UI_TITLE_MAIN)) {
              // Logo
              {
                static float frames = 0.0f;
                frames += 24.0f / ImGui::GetIO().Framerate;
                if (frames >= 1.0f) {
                  sLogoFrame++;
                  frames = 0.0f;
                }
                if (sLogoFrame == 24) sLogoFrame = 0;

                ImVec2 uv_min = ImVec2((1200.0f * sLogoFrame) / 28800.0f, 0.0f);
                ImVec2 uv_max = ImVec2(uv_min.x + (1200.0f / 28800.0f), 1.0f);
                ImGui::Image(sLogoSprite, ImVec2{600.0f, 250.0f}, uv_min, uv_max);
              }

              if (is_chaos_running) {
                ImGui::WithStyle    _s1(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                ImGui::WithItemFlag _f1(ImGuiItemFlags_Disabled);
                ImGui::Button("chaos is ensuing", ImVec2{600.0f, 0.0f});
              } else {
                {
                  ImGui::WithColor _c1(ImGuiCol_Button, IM_COL32(0, 125, 200, 255));
                  ImGui::WithColor _c2(ImGuiCol_ButtonHovered, IM_COL32(0, 150, 2225, 255));
                  ImGui::WithColor _c3(ImGuiCol_ButtonActive, IM_COL32(0, 100, 175, 255));
                  if (ImGui::Button("Start Single-Player Chaos", ImVec2{600.0f, 0.0f})) Shared::StartChaos(false);
                }
                if (ImGui::Button("Start Twitch Chat Chaos", ImVec2{600.0f, 0.0f})) Shared::StartChaos(true);
              }
              ImGui::EndTabItem();
            }
            // Twitch Tab
            if (!Shared::IsChaosRunning() && ImGui::BeginTabItem(CONST_UI_TITLE_TWITCH)) {
              Menu::DrawTwitch();
              ImGui::EndTabItem();
            }
            // Config Tab
            if (ImGui::BeginTabItem(CONST_UI_TITLE_CONFIG)) {
              Menu::DrawConfig();
              ImGui::EndTabItem();
            }
            // About Tab
            if (ImGui::BeginTabItem(CONST_UI_TITLE_ABOUT)) {
              Menu::DrawAbout();
              ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
          }
        }
        ImGui::End();
      } else {
        const auto  text_size    = ImGui::CalcTextSize(CONST_UI_TITLE) * 0.8f;
        const auto& display_size = ImGui::GetIO().DisplaySize;

        ImGui::WithStyle _s1(ImGuiStyleVar_FramePadding, {5.0f, 0.0f});
        ImGui::WithStyle _s2(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::SetNextWindowContentSize({text_size.y, text_size.x});
        ImGui::SetNextWindowPos(viewport->Pos + ImVec2(display_size.x - text_size.x - 210.0f, display_size.y - text_size.y));
        if (ImGui::Begin("###MainMenuToggle", nullptr,
                         ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize)) {
          ImGui::SetWindowFontScale(0.8f);

          ImGui::WithColor _c1(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button) - ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
          ImGui::WithColor _c2(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered) - ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
          ImGui::WithColor _c3(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive) - ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
          ImGui::WithColor _c4(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text) - ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
          sIsMenuVisible = ImGui::Button(CONST_UI_TITLE);
        }
        ImGui::End();
      }

      ImGui::GetIO().MouseDrawCursor = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
      ImGui::Render();
      ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
    static void __stdcall BeforeReset(LPDIRECT3DDEVICE9, void*) {
      if (sLogoSprite) sLogoSprite->Release();
      ImGui_ImplDX9_InvalidateDeviceObjects();
    }
    static void __stdcall AfterReset(LPDIRECT3DDEVICE9 pDevice, void*) {
      D3DXCreateTextureFromFileInMemory(pDevice, Videos::MainMenuLogoSprite_data, Videos::MainMenuLogoSprite_size, &details::sLogoSprite);
      ImGui_ImplDX9_CreateDeviceObjects();
    }

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
      if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return TRUE;
      if ((uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) && ChaosMod::g_GameWindowLostFocus) return TRUE;

      if (uMsg == WM_KEYUP && wParam == VK_INSERT && (!ImGui::GetIO().WantCaptureKeyboard || !ImGui::GetIO().WantTextInput)) sIsMenuVisible = !sIsMenuVisible;

      return MirrorHook::WndProc::g_constIgnoreThisReturn;
    }
  }  // namespace details

  // Will block
  static inline void Init() {
    LPDIRECT3DDEVICE9 d3d = ChaosMod::GetD3D9Device();

    // Set up MirrorHook
    while (MirrorHook::Init(MirrorHook::Framework::D3D9, &d3d) != MirrorHook::Result::Successful) std::this_thread::sleep_for(1s);

    // Load main menu logo
    { D3DXCreateTextureFromFileInMemory(d3d, Videos::MainMenuLogoSprite_data, Videos::MainMenuLogoSprite_size, &details::sLogoSprite); }

    // Set Up Dear ImGui
    {
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();

      auto& io = ImGui::GetIO();

      io.ConfigWindowsResizeFromEdges = false;
      io.Fonts->AddFontFromMemoryCompressedTTF(ImGui::Fonts::OpenSans::SemiBold_compressed_data, ImGui::Fonts::OpenSans::SemiBold_compressed_size, 28.0f);
      io.FontDefault = NULL;
      io.IniFilename = NULL;
      ImGui::LoadStyle();

      ImGui_ImplWin32_Init(MirrorHook::WndProc::GetWindowHandle());
      ImGui_ImplDX9_Init(d3d);
    }
    // Set up Menu
    Menu::Init();
    // Set up Overlay
    Overlay::Init();

    // Hook via MirrorHook
    {
      MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::BeginScene, &details::BeginScene);
      MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::EndScene, &details::EndScene);
      MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::BeforeReset, &details::BeforeReset);
      MirrorHook::D3D9::AddExtension(MirrorHook::D3D9::Type::AfterReset, &details::AfterReset);

      MirrorHook::WndProc::AddExtension(&details::WndProc);
    }
  }
}  // namespace Extensions::D3D9
