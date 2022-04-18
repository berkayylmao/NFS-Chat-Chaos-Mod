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
// Shared
#include "Shared.hpp"

#pragma warning(push, 0)
#include <shellapi.h>  // ShellExecute
#pragma warning(pop)

namespace Extensions::D3D9::Menu {
  namespace details {
#pragma region TABS
#pragma region Twitch(TAB)
    /// TWITCH TAB

    // Constants

    static constexpr char CONST_UI_TWITCH_DISCONNECT[]       = "Disconnect";
    static constexpr char CONST_UI_TWITCH_CONNECT[]          = "Connect to Twitch";
    static constexpr char CONST_UI_TWITCH_CONNECTING[]       = "Connecting to Twitch...";
    static constexpr char CONST_UI_TWITCH_CONNECTED_FORMAT[] = "Connected to channel '{}' as '{}'.";
    static constexpr char CONST_UI_TWITCH_TEST_CONNECTION[]  = "Test connection";
    static constexpr char CONST_UI_TWITCH_CHANNEL_NAME[]     = "Channel name";
    static constexpr char CONST_UI_TWITCH_USERNAME[]         = "Username";
    static constexpr char CONST_UI_TWITCH_USER_OAUTH[]       = "User OAuth";

    // OAuth variables

    static inline std::array<char, 128> sChannelName{};
    static inline std::array<char, 128> sUsername{};
    static inline std::array<char, 128> sUserOAuth{};

    // Tab content
    static inline void DrawTwitchTabContent() {
      // Disable all controls and show 'Connecting' text, if a connection event is in progress
      ImGui::WithStyle    _s1(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f, Shared::g_TwitchTalkStatus.first);
      ImGui::WithItemFlag _f1(ImGuiItemFlags_Disabled, Shared::g_TwitchTalkStatus.first);
      if (Shared::g_TwitchTalkStatus.first) ImGui::Text(CONST_UI_TWITCH_CONNECTING);

      if (Shared::g_TwitchTalkStatus.second) {  // User has already connected to Twitch
        {
          ImGui::WithItemFlag _f2(ImGuiItemFlags_Disabled);
          ImGui::WithStyle    _s2(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
          ImGui::FullWidthButton(fmt::format(CONST_UI_TWITCH_CONNECTED_FORMAT, sChannelName.data(), sUsername.data()).c_str());
        }
        if (ImGui::FullWidthButton(CONST_UI_TWITCH_TEST_CONNECTION)) Shared::g_TwitchTalk->SendMessageToChannel(fmt::format("Hello @{}!", sChannelName.data()));

        ImGui::Separator();

        if (ImGui::FullWidthButton(CONST_UI_TWITCH_DISCONNECT)) {  // Disconnect
          Shared::g_TwitchTalkStatus = {false, false};
          Shared::g_TwitchTalk->StopTalk();
        }
      } else {  // User has not connected to Twitch
        ImGui::WithItemWidth _w(-1.0f);
        ImGui::InputTextWithHintAlways("###InputChannelName", CONST_UI_TWITCH_CHANNEL_NAME, sChannelName.data(), sChannelName.max_size(),
                                       ImGuiInputTextFlags_CallbackCharFilter, [](ImGuiInputTextCallbackData* data) -> std::int32_t {
                                         if (data->EventChar) data->EventChar = std::tolower(data->EventChar);
                                         return 0;
                                       });
        ImGui::InputTextWithHintAlways("###InputUsername", CONST_UI_TWITCH_USERNAME, sUsername.data(), sUsername.max_size(),
                                       ImGuiInputTextFlags_CallbackCharFilter, [](ImGuiInputTextCallbackData* data) -> std::int32_t {
                                         if (data->EventChar) data->EventChar = std::tolower(data->EventChar);
                                         return 0;
                                       });
        ImGui::InputTextWithHintAlways("###InputUserOAuth", CONST_UI_TWITCH_USER_OAUTH, sUserOAuth.data(), sUserOAuth.max_size(),
                                       ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);

        if (ImGui::FullWidthButton(CONST_UI_TWITCH_CONNECT)) {
          // Attempt connection
          {
            Shared::g_TwitchTalkStatus = {true, false};
            Shared::g_TwitchTalk->StartTalk(sChannelName.data(), sUsername.data(), sUserOAuth.data());
          }

          // Save login information to Config
          {
            Config::Get()["Twitch"]["ChannelName"].SetString(sChannelName.data(), strnlen_s(sChannelName.data(), sChannelName.max_size()));
            Config::Get()["Twitch"]["Username"].SetString(sUsername.data(), strnlen_s(sUsername.data(), sUsername.max_size()));
            Config::Get()["Twitch"]["UserOAuth"].SetString(sUserOAuth.data(), strnlen_s(sUserOAuth.data(), sUserOAuth.max_size()));

            Config::Get().Save();
          }
        }
      }
    }
#pragma endregion
#pragma region Effects(TAB)
    /// EFFECTS TAB

    // Constants

    static constexpr char CONST_UI_CONFIG_HEADER_ENABLED[]  = "E";
    static constexpr char CONST_UI_CONFIG_HEADER_NAME[]     = "Name";
    static constexpr char CONST_UI_CONFIG_HEADER_COOLDOWN[] = "Cooldown";
    static constexpr char CONST_UI_CONFIG_HEADER_DURATION[] = "Duration (seconds)";
    static constexpr char CONST_UI_CONFIG_INFO_ENABLED[]    = "Whether the effect is enabled.";
    static constexpr char CONST_UI_CONFIG_INFO_NAME[]       = "Name of the effect. Hovering over the respective '[?]' marks shows description of the effect.";
    static constexpr char CONST_UI_CONFIG_INFO_COOLDOWN[] =
        "Cooldown of the effect. Note that this is PER ACTIVATED EFFECT!!, not per voting cycle. For example, a "
        "cooldown of '3' means 'allow for voting after 3 effects are activated'.";
    static constexpr char CONST_UI_CONFIG_INFO_DURATION[] =
        "Duration of the effect in seconds. If the effect isn't continuous (e.g., 'Magneto'), this will only show "
        "'Status effect'.";

    // Seed
    static inline std::array<char, 65> sSeed{};

    // Tab Content
    static inline void DrawEffectsTabContent() {
      if (ImGui::BeginTable(
              "EffectsTable", 4,
              ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_ScrollY,
              ImVec2(ImGui::GetFontSize() * 30.0f, ImGui::GetFontSize() * 20.0f))) {
        // Set up columns
        {
          ImGui::TableSetupColumn(CONST_UI_CONFIG_HEADER_ENABLED, ImGuiTableColumnFlags_NoSort, 0.1f);
          ImGui::TableSetupColumn(CONST_UI_CONFIG_HEADER_NAME, ImGuiTableColumnFlags_NoSort, 1.0f);
          ImGui::TableSetupColumn(CONST_UI_CONFIG_HEADER_COOLDOWN, ImGuiTableColumnFlags_NoSort, 0.5f);
          ImGui::TableSetupColumn(CONST_UI_CONFIG_HEADER_DURATION, ImGuiTableColumnFlags_NoSort, 0.5f);
          ImGui::TableSetupScrollFreeze(0, 2);
          ImGui::TableHeadersRow();
        }
        // Set up info row
        {
          ImGui::TableNextRow();

          // IsEnabled info
          {
            ImGui::TableSetColumnIndex(0);
            // Display information marker
            ImGui::TextDisabled("[?]");
            if (ImGui::IsItemHovered()) {
              ImGui::BeginTooltip();
              ImGui::PushTextWrapPos(ImGui::GetFontSize() * 20.0f);
              ImGui::TextUnformatted(CONST_UI_CONFIG_INFO_ENABLED);
              ImGui::PopTextWrapPos();
              ImGui::EndTooltip();
            }
          }
          // Name info
          {
            ImGui::TableSetColumnIndex(1);
            // Display information marker
            ImGui::TextDisabled("[?] Info");
            if (ImGui::IsItemHovered()) {
              ImGui::BeginTooltip();
              ImGui::PushTextWrapPos(ImGui::GetFontSize() * 20.0f);
              ImGui::TextUnformatted(CONST_UI_CONFIG_INFO_NAME);
              ImGui::PopTextWrapPos();
              ImGui::EndTooltip();
            }
          }
          // Cooldown info
          {
            ImGui::TableSetColumnIndex(2);
            // Display information marker
            ImGui::TextDisabled("[?] Info");
            if (ImGui::IsItemHovered()) {
              ImGui::BeginTooltip();
              ImGui::PushTextWrapPos(ImGui::GetFontSize() * 20.0f);
              ImGui::TextUnformatted(CONST_UI_CONFIG_INFO_COOLDOWN);
              ImGui::PopTextWrapPos();
              ImGui::EndTooltip();
            }
          }
          // Duration info
          {
            ImGui::TableSetColumnIndex(3);
            // Display information marker
            ImGui::TextDisabled("[?] Info");
            if (ImGui::IsItemHovered()) {
              ImGui::BeginTooltip();
              ImGui::PushTextWrapPos(ImGui::GetFontSize() * 20.0f);
              ImGui::TextUnformatted(CONST_UI_CONFIG_INFO_DURATION);
              ImGui::PopTextWrapPos();
              ImGui::EndTooltip();
            }
          }
        }

        for (auto* ptr : Extensions::Game::IGameEffectsHandler::GetAllEffects()) {
          ImGui::TableNextRow();

          // Effect IsEnabled
          {
            ImGui::TableSetColumnIndex(0);

            ImGui::PushID(ptr->GetIndex() + 1);
            ImGui::Checkbox("", &ptr->GetIsEnabledRef());
            if (ImGui::IsItemDeactivatedAfterEdit()) {
              Config::Get()["Effects"][ptr->GetIndex()]["IsEnabled"].SetBool(ptr->GetIsEnabled());
              Config::Get().Save();
            }
            ImGui::PopID();
          }

          // Effect name
          {
            ImGui::TableSetColumnIndex(1);

            ImGui::AlignTextToFramePadding();
            // Display information marker
            ImGui::TextDisabled("[?]");
            if (ImGui::IsItemHovered()) {
              ImGui::BeginTooltip();
              ImGui::PushTextWrapPos(ImGui::GetFontSize() * 20.0f);
              ImGui::TextUnformatted(ptr->GetDescription().c_str());
              ImGui::PopTextWrapPos();
              ImGui::EndTooltip();
            }
            ImGui::SameLine();
            ImGui::TextWrapped(ptr->GetName().c_str());
          }

          // Effect cooldown
          {
            static const char format[] = "%u";

            ImGui::TableSetColumnIndex(2);

            ImGui::PushID((ptr->GetIndex() + 1) * -1);
            ImGui::PushItemWidth(-FLT_MIN);
            ImGui::InputScalar("", ImGuiDataType_U32, &ptr->GetCooldownRef(), nullptr, nullptr, format, ImGuiInputTextFlags_CharsDecimal);
            if (ImGui::IsItemDeactivatedAfterEdit()) {
              ptr->GetCooldownRef() = std::clamp(ptr->GetCooldown(), 0u, 999u);
              Config::Get()["Effects"][ptr->GetIndex()]["Cooldown"].SetUint(ptr->GetCooldown());
              Config::Get().Save();
            }
            ImGui::PopID();
          }

          // Effect duration
          {
            static const char _format[] = "%.1f";
            double            val       = std::chrono::duration<double>(ptr->GetDuration()).count();

            ImGui::TableSetColumnIndex(3);

            if (ptr->GetIsStatusEffect()) {
              ImGui::AlignTextToFramePadding();
              ImGui::TextUnformatted("Status effect");
            } else {
              ImGui::PushID((ptr->GetIndex() + 1) * -10);
              ImGui::PushItemWidth(-FLT_MIN);
              ImGui::InputScalar("", ImGuiDataType_Double, &val, nullptr, nullptr, _format, ImGuiInputTextFlags_CharsDecimal);
              if (ImGui::IsItemDeactivatedAfterEdit()) {
                val                   = std::clamp(val, 1.0, 900.0);
                ptr->GetDurationRef() = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(val));
                Config::Get()["Effects"][ptr->GetIndex()]["Duration"].SetDouble(val);
                Config::Get().Save();
              }
              ImGui::PopID();
            }
          }
        }

        ImGui::EndTable();
      }
    }
#pragma endregion
#pragma region About(TAB)
    /// ABOUT TAB

    // Constants

    static constexpr char CONST_UI_ABOUT_GITHUB[]         = "https://github.com/berkayylmao/NFS-Chat-Chaos-Mod/";
    static constexpr char CONST_UI_ABOUT_GITHUB_RELEASE[] = "https://github.com/berkayylmao/NFS-Chat-Chaos-Mod/releases/latest";
    static constexpr char CONST_UI_ABOUT_PAYPAL[]         = "https://www.paypal.com/donate/?hosted_button_id=TFCVT5CTKDGB6";
    static constexpr char CONST_UI_ABOUT_KOFI[]           = "https://ko-fi.com/berkayylmao";
    static constexpr char CONST_UI_ABOUT_PATREON[]        = "https://www.patreon.com/berkayylmao";

    // Tab content
    static inline void DrawAboutTabContent() {
      ImGui::TextUnformatted("NFS Chat Chaos Mod v" __MOD_VERSION_STR__ "\nCopyright (C) berkayylmao");

      // GitHub
      {
        ImGui::TextUnformatted("Stay up to date with the latest version from ");
        ImGui::SameLine(0.0f, 0.0f);
        if (ImGui::SmallButton("GitHub")) ShellExecuteA(NULL, NULL, details::CONST_UI_ABOUT_GITHUB_RELEASE, NULL, NULL, SW_SHOW);
        ImGui::SameLine(0.0f, 0.0f);
        ImGui::TextUnformatted(".");
      }

      // Donation
      {
        ImGui::Separator();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 30.0f);
        ImGui::TextUnformatted(
            "Making and maintaining a mod like this requires a lot of time and energy. If you enjoyed this mod, please "
            "consider donating!");
        ImGui::PopTextWrapPos();
        if (ImGui::SmallButton("PayPal: paypal.com/donate/?hosted_button_id=TFCVT5CTKDGB6"))
          ShellExecuteA(NULL, NULL, details::CONST_UI_ABOUT_PAYPAL, NULL, NULL, SW_SHOW);
        if (ImGui::SmallButton("Ko-Fi: ko-fi.com/berkayylmao")) ShellExecuteA(NULL, NULL, details::CONST_UI_ABOUT_KOFI, NULL, NULL, SW_SHOW);
        if (ImGui::SmallButton("Patreon: patreon.com/berkayylmao")) ShellExecuteA(NULL, NULL, details::CONST_UI_ABOUT_PATREON, NULL, NULL, SW_SHOW);
      }

      // Compatibility
      {
        ImGui::Separator();
        ImGui::TextUnformatted("Compatibility:");
        ImGui::Indent();
        {
          ImGui::BulletText("This mod is compatible with multiple games! Simply install it the same way.");
          ImGui::BulletText("If you wish to keep your settings, copy the folder `ChatChaosMod` too!");
          ImGui::BulletText("Compatible with the following games:");
          ImGui::Indent();
          {
            ImGui::BulletText("NFS Most Wanted v1.3 (English RELOADED)");
            ImGui::BulletText("NFS Carbon Collector's Edition v1.4 (English RELOADED)");
          }
          ImGui::Unindent();
        }
        ImGui::Unindent();
      }
    }
#pragma endregion
#pragma endregion
  }  // namespace details

  // Called when user has Twitch tab active
  static inline void DrawTwitch() { details::DrawTwitchTabContent(); }

  // Called when user has Configuration tab active
  static inline void DrawConfig() {
    if (ImGui::BeginTabBar("###ConfigTabBar", ImGuiTabBarFlags_FittingPolicyResizeDown)) {
      if (ImGui::BeginTabItem("Core")) {
        ImGui::TextUnformatted("Idle timer (before votes):  ");
        ImGui::SameLine();
        const float _offsetX = ImGui::GetCursorPosX();
        {
          ImGui::SliderFloat("##IdleTimerSlider", &ChaosMod::g_IdleTimerSeconds, 1.0f, 120.0f, "%.1f");
          if (ImGui::IsItemDeactivatedAfterEdit()) {
            if (Shared::IsChaosRunning()) Shared::g_ChaosTimerStatus = Shared::TimerStatus::IdleTimer;
            Config::Get()["Timers"]["IdleTimer"].SetFloat(ChaosMod::g_IdleTimerSeconds);
            Config::Get().Save();
          }
        }
        ImGui::TextUnformatted("Vote timer (during votes): ");
        {
          ImGui::SameLine();
          ImGui::SetCursorPosX(_offsetX);
          ImGui::SliderFloat("##VoteTimerSlider", &ChaosMod::g_VoteTimerSeconds, 1.0f, 120.0f, "%.1f");
          if (ImGui::IsItemDeactivatedAfterEdit()) {
            if (Shared::IsChaosRunning()) Shared::g_ChaosTimerStatus = Shared::TimerStatus::IdleTimer;
            Config::Get()["Timers"]["VoteTimer"].SetFloat(ChaosMod::g_VoteTimerSeconds);
            Config::Get().Save();
          }
        }
        ImGui::TextUnformatted("Seed: ");
        {
          ImGui::SameLine();
          ImGui::SetCursorPosX(_offsetX);
          ImGui::BeginDisabled();
          ImGui::InputTextWithHint("##ChaosSeedInput", "(leave blank for random)", details::sSeed.data(), details::sSeed.max_size() - 1);
          if (ImGui::IsItemDeactivatedAfterEdit()) {
            Config::Get()["Seed"].SetString(details::sSeed.data(), strnlen_s(details::sSeed.data(), details::sSeed.max_size()));
            Config::Get().Save();
          }
          ImGui::EndDisabled();
        }

        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("Effects")) {
        details::DrawEffectsTabContent();
        ImGui::EndTabItem();
      }

#ifdef _DEBUG
      if (ImGui::BeginTabItem("Debug")) {
        if (ImGui::BeginTabBar("##DebugTabBar")) {
          if (ImGui::BeginTabItem("Effects")) {
            for (auto& _eff : Extensions::Game::IGameEffectsHandler::GetAllEffects()) {
              if (ImGui::Button(_eff->GetName().c_str())) {
                Extensions::Game::IGameEffectsHandler::AddToActivateQueue(_eff);
                Extensions::Game::IGameEffectsHandler::RunActivateQueue();
              }
            }

            ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
        }
        ImGui::EndTabItem();
      }
#endif

      ImGui::EndTabBar();
    }
  }

  // Called when user has About tab active
  static inline void DrawAbout() { details::DrawAboutTabContent(); }

  static inline void Init() {
    // Load core values from Config
    {
      ChaosMod::g_IdleTimerSeconds = Config::Get()["Timers"]["IdleTimer"].GetFloat();
      ChaosMod::g_VoteTimerSeconds = Config::Get()["Timers"]["VoteTimer"].GetFloat();

      const auto& seed = Config::Get()["Seed"].Get<std::string>();
      std::copy(std::begin(seed), std::end(seed), std::begin(details::sSeed));
    }
    // Load saved Twitch login information from Config
    {
      const auto& channel_name = Config::Get()["Twitch"]["ChannelName"].Get<std::string>();
      const auto& username     = Config::Get()["Twitch"]["Username"].Get<std::string>();
      const auto& user_oauth   = Config::Get()["Twitch"]["UserOAuth"].Get<std::string>();

      std::copy(std::begin(channel_name), std::end(channel_name), std::begin(details::sChannelName));
      std::copy(std::begin(username), std::end(username), std::begin(details::sUsername));
      std::copy(std::begin(user_oauth), std::end(user_oauth), std::begin(details::sUserOAuth));
    }
  }
}  // namespace Extensions::D3D9::Menu
