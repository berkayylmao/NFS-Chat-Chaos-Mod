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
#include <charconv>  // from_chars
#pragma warning(pop)

namespace Extensions::D3D9::Overlay {
  namespace details {
#pragma region SHARED CONSTANTS
    /// SHARED CONSTANTS

    constexpr char CONST_TWITCH_VOTE_PREFIX[] = "c";

    constexpr float CONST_UI_PAD_CONTENT = 5.0f;
    static ImVec2   sContentPadding      = ImVec2(CONST_UI_PAD_CONTENT, CONST_UI_PAD_CONTENT);

    constexpr float CONST_UI_PAD_SHADOW = 1.0f;
#pragma endregion

#pragma region EFFECTS DISPLAY
    //// EFFECTS DISPLAY

#pragma region Timer
    /// TIMER

    // Timer rectangle
    static ImGui::Rectangle timerRect;

    // Timer draw call
    static inline Shared::TimerResult DrawTimer(const ImGuiViewport* viewport) {
      const auto timer_status = Shared::g_ChaosTimerStatus;

      // Return if timer hasn't been started yet
      if (timer_status == Shared::TimerStatus::None) return Shared::TimerResult::None;

      // Current max point of the timer
      const float max_time = timer_status == Shared::TimerStatus::IdleTimer   ? ChaosMod::g_IdleTimerSeconds
                             : timer_status == Shared::TimerStatus::VoteTimer ? ChaosMod::g_VoteTimerSeconds
                                                                              : ChaosMod::g_ActivationTimerSeconds;

      // Persistent local storage for the timer
      static float seconds_passed = 0.0f;
      // Static format array
      static std::array<char, 4196> format_array{};

      // Step timer (in seconds)
      seconds_passed = ImClamp(seconds_passed + ImGui::GetIO().DeltaTime, 0.0f, max_time);

      // Remaining time
      const float seconds_left = max_time - seconds_passed;

      // Step timer status
      if (seconds_left <= 0.0f) {
        seconds_passed = 0.0f;

        if (timer_status == Shared::TimerStatus::IdleTimer)
          return Shared::TimerResult::IdleTimerCompleted;
        else if (timer_status == Shared::TimerStatus::VoteTimer)
          return Shared::TimerResult::VoteTimerCompleted;
        else
          return Shared::TimerResult::ActivationTimerCompleted;
      }

      // Timer colours
      static ImU32 timer_colour;
      static ImU32 timer_colour_bg;

      if (timer_status == Shared::TimerStatus::IdleTimer) {
        timer_colour    = IM_COL32(45, 115, 55, 100);
        timer_colour_bg = IM_COL32(20, 60, 25, 150);
      } else if (timer_status == Shared::TimerStatus::VoteTimer) {
        timer_colour    = IM_COL32(255, 80, 80, 100);
        timer_colour_bg = IM_COL32(120, 40, 40, 150);
      } else {
        timer_colour    = IM_COL32(15, 140, 180, 100);
        timer_colour_bg = IM_COL32(5, 70, 90, 150);
      }

      // Update timer rectangle
      timerRect = ImGui::Rectangle(ImGui::GetFontSize(), ImGui::GetFontSize(), ImGui::GetFontSize() * 10.0f, ImGui::GetFontSize() * 1.5f);

      // Draw timer
      ImGui::WithStyle _s1(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s2(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s3(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s4(ImGuiStyleVar_Alpha, 1.0f);

      ImGui::SetNextWindowBgAlpha(0.0f);
      ImGui::SetNextWindowSize(timerRect.GetRightBottom());
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::Begin("###EffectTimer", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav);
      {
        const ImVec2 cursor = ImGui::GetCursorScreenPos();
        const ImVec2 p_min  = cursor + timerRect.GetXY();
        const ImVec2 p_max  = cursor + timerRect.GetRightBottom();

        // Draw border for the timer
        ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, IM_COL32(0, 0, 0, 200));
        // Draw background for the timer
        ImGui::GetWindowDrawList()->AddRectFilled(p_min + sContentPadding, p_max - sContentPadding, timer_colour_bg);

        // Draw remaining time
        ImGui::GetWindowDrawList()->AddRectFilled(
            p_min + sContentPadding,
            p_min + ImVec2(ImClamp(timerRect.width * (seconds_left / max_time), sContentPadding.x, timerRect.width - sContentPadding.x),
                           timerRect.height - sContentPadding.y),
            timer_colour);

        // Draw remaining time (STRING)
        {
          format_array.fill(NULL);
          // Format into string
          fmt::format_to_n(format_array.data(), format_array.max_size(), "{:.0f}", seconds_left);

          // Center text
          const ImVec2 str_size = ImGui::CalcTextSize(format_array.data());
          const ImVec2 str_pos  = timerRect.GetXY() + (timerRect.GetWidthHeight() - str_size) / 2.0f;

          // Draw text
          ImGui::SetCursorPos(str_pos);
          ImGui::TextUnformatted(format_array.data());
        }
      }
      ImGui::End();

      return Shared::TimerResult::None;
    }
#pragma endregion
#pragma region Vote Bars
    /// VOTE BARS

    // Total votes received
    static std::size_t sVotesReceived = 0;

    // [Effect being voted, votes received]
    static std::unordered_map<Game::IGameEffect*, std::size_t> sEffectsBeingVoted;

    // Generate effects to be voted
    static inline void GenarateEffectsToBeVoted() {
      sEffectsBeingVoted.clear();

      const auto& effects = Game::IGameEffectsHandler::GetCompatibleRandomEffects(3);
      for (const auto& effect : effects) sEffectsBeingVoted[effect] = 0;
    }

    // Vote bar rectangle
    static ImGui::Rectangle sVoteBarRect;

    // Vote bar draw call
    static inline void DrawVoteBars(const ImGuiViewport* viewport) {
      if (sEffectsBeingVoted.size() != 3) return;

      // Vote bar colours
      static const ImU32 vote_bar_colour    = IM_COL32(255, 80, 80, 100);
      static const ImU32 vote_bar_colour_bg = IM_COL32(120, 40, 40, 150);
      // Static format array
      static std::array<char, 4196> format_array{};

      // Update vote bar rectangle
      sVoteBarRect = ImGui::Rectangle(timerRect.x, timerRect.GetBottom() + ImGui::GetFontSize() / 2.0f, timerRect.width, timerRect.height);

      ImGui::WithStyle _s1(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s2(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s3(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s4(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s5(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s6(ImGuiStyleVar_Alpha, 1.0f);

      ImGui::SetNextWindowBgAlpha(0.0f);
      ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, sVoteBarRect.GetBottom() * 3.0f));
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::Begin("##VoteBars", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav);
      {
        const ImVec2 cursor = ImGui::GetCursorScreenPos();

        for (std::size_t i = 0; i < 3; i++) {
          format_array.fill(NULL);

          const auto& it                 = std::next(std::cbegin(sEffectsBeingVoted), i);
          float       it_vote_percentage = 0.0f;

          const float  y_diff = (sVoteBarRect.height + ImGui::GetFontSize() / 2.0f) * i;
          const ImVec2 p_min  = cursor + ImVec2(sVoteBarRect.x, sVoteBarRect.y + y_diff);
          const ImVec2 p_max  = cursor + ImVec2(sVoteBarRect.GetRight(), sVoteBarRect.GetBottom() + y_diff);

          // Draw border
          ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, IM_COL32(0, 0, 0, 200));
          // Draw background
          ImGui::GetWindowDrawList()->AddRectFilled(p_min + sContentPadding, p_max - sContentPadding, vote_bar_colour_bg);

          // Draw received votes and their percentage (TEXT)
          {
            if (Shared::g_ChaosMode == Shared::ChaosMode::SinglePlayer) {
              auto rnd = Random::Get().Generate(0, 1) * Random::Get().Generate(0, 100);
              if (rnd > 98) {
                sEffectsBeingVoted[it->first]++;
                sVotesReceived++;
              }
            }

            // Draw received votes percentage
            if (sVotesReceived > 0) {
              // Calculate vote percentage
              it_vote_percentage = (static_cast<float>(it->second) / static_cast<float>(sVotesReceived));

              // Draw received votes percentage
              ImGui::GetWindowDrawList()->AddRectFilled(
                  p_min + sContentPadding,
                  p_min + ImVec2(ImClamp(sVoteBarRect.width * it_vote_percentage, sContentPadding.x, sVoteBarRect.width - sContentPadding.x),
                                 sVoteBarRect.height - sContentPadding.y),
                  vote_bar_colour);
            }

            it_vote_percentage *= 100.0f;

            // Format into string
            fmt::format_to_n(format_array.data(), format_array.max_size(), "{}. {:.0f}%", i + 1, it_vote_percentage);
            // Center text
            const ImVec2 str_size = ImGui::CalcTextSize(format_array.data());
            const ImVec2 str_pos  = ImVec2(sVoteBarRect.x, sVoteBarRect.y + y_diff) + (sVoteBarRect.GetWidthHeight() - str_size) / 2.0f;

            ImGui::SetCursorPos(str_pos);
            ImGui::TextUnformatted(format_array.data());
          }

          // Draw effect name
          if (Shared::g_ChaosMode == Shared::ChaosMode::TwitchChat) {
            // Format into string
            fmt::format_to_n(format_array.data(), format_array.max_size(), "{}{}: {}", CONST_TWITCH_VOTE_PREFIX, i + 1, it->first->GetName());

            // Center text
            const ImVec2 str_size = ImGui::CalcTextSize(format_array.data());
            const ImVec2 str_pos =
                ImVec2(sVoteBarRect.width + ImGui::GetFontSize() * 1.5f, sVoteBarRect.y + y_diff + (sVoteBarRect.height - str_size.y) / 2.0f);

            // Draw shadow
            {
              ImGui::WithColor _c1(ImGuiCol_Text, IM_COL32_BLACK);

              ImGui::SetCursorPos(str_pos - ImVec2(CONST_UI_PAD_SHADOW, 0.0f));
              ImGui::TextUnformatted(format_array.data());
              ImGui::SetCursorPos(str_pos - ImVec2(-CONST_UI_PAD_SHADOW, 0.0f));
              ImGui::TextUnformatted(format_array.data());
              ImGui::SetCursorPos(str_pos - ImVec2(0.0f, CONST_UI_PAD_SHADOW));
              ImGui::TextUnformatted(format_array.data());
              ImGui::SetCursorPos(str_pos - ImVec2(0.0f, -CONST_UI_PAD_SHADOW));
              ImGui::TextUnformatted(format_array.data());
            }

            ImGui::SetCursorPos(str_pos);
            ImGui::TextUnformatted(format_array.data());
          }
        }
      }
      ImGui::End();
    }
#pragma endregion
#pragma region Active Effects
    /// ACTIVE EFFECTS

    // Active effects draw call
    static inline void DrawActiveEffects(const ImGuiViewport* viewport) {
      auto              active_effects     = Game::IGameEffectsHandler::GetActiveEffects();
      const std::size_t num_active_effects = active_effects.size();
      if (num_active_effects == 0) return;

      // Static format array
      static std::array<char, 4196> format_array{};

      ImGui::WithStyle _s1(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
      ImGui::WithStyle _s2(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s3(ImGuiStyleVar_WindowMinSize, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s4(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s5(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0.0f, 0.0f));
      ImGui::WithStyle _s6(ImGuiStyleVar_WindowRounding, 5.0f);

      ImGui::SetNextWindowBgAlpha(0.4f);
      ImGui::SetNextWindowPos(viewport->Pos + ImVec2(sVoteBarRect.x, sVoteBarRect.GetBottom() * 2.0f));
      if (ImGui::Begin("##ActiveEffectsDisplay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize)) {
        const auto time_now = std::chrono::steady_clock::now();

        for (std::size_t i = 0; i < num_active_effects; i++) {
          format_array.fill(NULL);

          const auto cursor_screen = ImGui::GetCursorScreenPos();
          const auto cursor        = ImGui::GetCursorPos();

          const auto& effect              = active_effects[i];
          const auto& ms_since_activation = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - effect->GetTimeActivated());
          const auto  ms_elapsed          = effect->GetDuration() - ms_since_activation;
          if (ms_elapsed < 0ms) continue;

          const float remaining_percent   = static_cast<float>(ms_since_activation.count()) / static_cast<float>(effect->GetDuration().count());
          const float circle_timer_radius = ImGui::GetFontSize() / 1.35f;

          // Circle timer
          {
            const ImVec2 arc   = ImVec2(cursor_screen + ImVec2(8.0f + circle_timer_radius, 4.0f + circle_timer_radius));
            const float  a_min = IM_PI * 1.5f;
            const float  a_max = (IM_PI * -0.5f) + remaining_percent * (IM_PI * 2.0f);

            ImGui::GetWindowDrawList()->PathArcTo(arc - ImVec2(1.0f, -1.0f), circle_timer_radius, a_min, IM_PI * -0.5f);
            ImGui::GetWindowDrawList()->PathStroke(IM_COL32(0, 0, 0, 100), ImDrawFlags_None, 4.0f);
            ImGui::GetWindowDrawList()->PathArcTo(arc, circle_timer_radius, a_min, a_max);
            ImGui::GetWindowDrawList()->PathStroke(ImGui::GetColorU32(ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered)), ImDrawFlags_None, 4.0f);

            // Seconds inside circle
            {
              fmt::format_to_n(format_array.data(), format_array.max_size(), "{}", std::chrono::duration_cast<std::chrono::seconds>(ms_elapsed).count());

              const ImVec2 str_pos =
                  cursor + ImVec2(8.5f + circle_timer_radius, circle_timer_radius / 1.85f) - ImVec2(ImGui::CalcTextSize(format_array.data()).x / 2.0f, 0.0f);

              ImGui::SetCursorPos(str_pos);
              ImGui::TextUnformatted(format_array.data());
            }
          }

          // Effect info
          {
            const ImVec2 name_pos = cursor + ImVec2(circle_timer_radius * 3.0f, 0.0f);
            const float  wrap_pos = ImGui::GetFontSize() * 20.0f;
            ImGui::PushTextWrapPos(wrap_pos + CONST_UI_PAD_SHADOW);

            // Name
            {
              ImGui::SetCursorPos(name_pos);
              ImGui::TextUnformatted(active_effects[i]->GetName().c_str());
            }

            const ImVec2 desc_pos = ImVec2(name_pos.x, ImGui::GetCursorPosY());

            // Description
            {
              ImGui::WithStyle _s7(ImGuiStyleVar_Alpha, 0.75f);

              ImGui::SetCursorPos(desc_pos);
              ImGui::TextUnformatted(active_effects[i]->GetDescription().c_str());
            }

            ImGui::PopTextWrapPos();
          }
        }
      }
      ImGui::End();
    }
#pragma endregion
#pragma endregion
#pragma region TWITCH TALK
    /// TWITCH TALK

// Callbacks
#pragma region ReceivedMessage
    // Cached users list (to avoid multiple votes by same users)
    static std::vector<std::uint64_t> sTwitchVotedUserIds;

    // Users list mutex
    static std::mutex sTwitchVotedUserIdsMutex;

    // Update votes
    static void Callback_TwitchIRC_ReceivedMessage(TwitchIRC::TwitchMessage message) {
      static std::size_t sVotePrefixLen = strlen(CONST_TWITCH_VOTE_PREFIX);

      // Is a vote in progress?
      if (Shared::g_ChaosTimerStatus != Shared::TimerStatus::VoteTimer) return;

      // Is the message a valid vote?
      if (sVotePrefixLen == 0) {
        if (message.mContent.size() != 1) return;
      } else if (!message.mContent._Starts_with(CONST_TWITCH_VOTE_PREFIX) || message.mContent.size() != sVotePrefixLen + 1) {
        return;
      }

      // Lock voters list
      std::scoped_lock<std::mutex> _l(sTwitchVotedUserIdsMutex);

      // Has this user voted previously?
      if (std::find_if(std::cbegin(sTwitchVotedUserIds), std::cend(sTwitchVotedUserIds),
                       [&message](const std::uint64_t& id) { return id == message.mSender.mId; }) != std::cend(sTwitchVotedUserIds))
        return;

      // Parse string into vote id
      std::size_t vote_idx = 0;
      auto        result   = std::from_chars(message.mContent.c_str() + sVotePrefixLen, message.mContent.c_str() + sVotePrefixLen + 1, vote_idx);

      // Is the message a valid vote?
      if (result.ec != std::errc()) return;

      // Is the parsed vote id within range?
      if (vote_idx < 1 || vote_idx > 3) return;

      // Align vote id
      vote_idx--;

      // Register voter
      sTwitchVotedUserIds.push_back(message.mSender.mId);

      // Add vote
      sVotesReceived += message.mSender.mIsSubscriber ? 3 : 1;
      std::next(std::begin(sEffectsBeingVoted), vote_idx)->second += message.mSender.mIsSubscriber ? 3 : 1;
    }
#pragma endregion
#pragma region ConnectionResult
    // Update `TwitchTalkStatus` with result
    static void Callback_TwitchIRC_ConnectionResult(bool isConnected) { Shared::g_TwitchTalkStatus = {false, isConnected}; }
#pragma endregion
#pragma endregion

  }  // namespace details

  // Called every frame
  static inline void DrawEffectsDisplay(const ImGuiViewport* pMainViewport) {
    // Overlays
    for (const auto& effect : Game::IGameEffectsHandler::GetActiveEffects()) effect->Draw(pMainViewport);

    // Timer
    {
      // Draw timer
      const auto&               timer_result      = details::DrawTimer(pMainViewport);
      static Game::IGameEffect* sEffectToActivate = nullptr;

      // Init based on returns value of timer
      if (timer_result == Shared::TimerResult::IdleTimerCompleted) {
        // Generate effects
        details::GenarateEffectsToBeVoted();
        // Start vote
        Shared::g_ChaosTimerStatus = Shared::TimerStatus::VoteTimer;
      } else if (timer_result == Shared::TimerResult::VoteTimerCompleted) {
        if (details::sVotesReceived > 0) {
          std::vector<Game::IGameEffect*> vote_weight_vector;
          // Generate weight list
          for (const auto& pair : details::sEffectsBeingVoted) vote_weight_vector.insert(vote_weight_vector.begin(), pair.second, pair.first);
          // Shuffle the vector
          std::shuffle(vote_weight_vector.begin(), vote_weight_vector.end(), Random::Get().GetGenerator());
          // Mark effect
          sEffectToActivate = vote_weight_vector[0];
        }

        //  Clear lists
        details::sEffectsBeingVoted.clear();
        details::sTwitchVotedUserIds.clear();
        // Reset votes
        details::sVotesReceived = 0;

        if (sEffectToActivate) {
          if (sEffectToActivate->GetNeedsActivationWarning()) {
            // Warn user if needed
            ChaosMod::g_GameEffectsHandler->ShowActivationWarning(sEffectToActivate);
            // Continue timer
            Shared::g_ChaosTimerStatus = Shared::TimerStatus::ActivationTimer;
          } else {
            // Activate effect
            Game::IGameEffectsHandler::AddToActivateQueue(sEffectToActivate);
            // Clear effect
            sEffectToActivate = nullptr;
            // Reset timer
            Shared::g_ChaosTimerStatus = Shared::TimerStatus::IdleTimer;
          }
        } else {
          // Clear effect
          sEffectToActivate = nullptr;
          // Reset timer
          Shared::g_ChaosTimerStatus = Shared::TimerStatus::IdleTimer;
        }
      } else if (timer_result == Shared::TimerResult::ActivationTimerCompleted) {
        // Activate effect
        if (sEffectToActivate) Game::IGameEffectsHandler::AddToActivateQueue(sEffectToActivate);
        // Clear GenericMessage
        ChaosMod::g_GameEffectsHandler->ClearGenericMessage();
        // Clear effect
        sEffectToActivate = nullptr;
        // Reset timer
        Shared::g_ChaosTimerStatus = Shared::TimerStatus::IdleTimer;
      }
    }

    // Vote bars
    if (Shared::g_ChaosTimerStatus == Shared::TimerStatus::VoteTimer) details::DrawVoteBars(pMainViewport);

    // Active effects
    { details::DrawActiveEffects(pMainViewport); }
  }

  static inline void Init() { Shared::InitTwitchTalk(&details::Callback_TwitchIRC_ConnectionResult, &details::Callback_TwitchIRC_ReceivedMessage); }
}  // namespace Extensions::D3D9::Overlay
