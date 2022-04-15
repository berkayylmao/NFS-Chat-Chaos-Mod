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
#pragma warning(push, 0)
#include <chrono>
#include <cstdint>  // integer types
#include <string>
// Dear ImGui
#include "Helpers/Dear ImGui/imgui.h"
#pragma warning(pop)
// Config
#include "Helpers/Config.hpp"

namespace Extensions::Game {
  class IGameEffect {
   public:
    enum class Status : std::uint8_t { NotReady, Inactive, Active, InDeactivateQueue, InActivateQueue };

   protected:
    // Index
    const std::uint32_t mIndex;

    // Enabled
    bool mIsEnabled;

    // Name
    const std::string mName;

    // Description
    const std::string mDescription;

    // Active status
    Status mStatus;

    // Activation time point
    std::chrono::time_point<std::chrono::steady_clock> mTimeActivated;

    // Cooldown (the number of effects needed to be activated before this effect is available)
    std::uint32_t mCooldown;

    // Remaining cooldown (remaining number of effects needed to be activated before this effect is available)
    std::uint32_t mRemainingCooldown;

    // Duration (in seconds)
    std::chrono::milliseconds mDuration;

    // Whether the effect only needs to be activated
    const bool mIsStatusEffect;

    // Activation warning (a 2 second warning before activation to have user be ready for the effect)
    const bool mNeedsActivationWarning;

    // Incompatibles list
    std::vector<std::uint32_t> mIncompatibleIndices;

    /// Virtual member functions

    // Only called from IGameEffectsHandler when appropriate
    virtual bool _activate() noexcept { return true; }

    // Only called from IGameEffectsHandler when appropriate
    virtual bool _deactivate() noexcept { return true; }

    // Only called if active from game's main loop
    virtual void _activeTick() noexcept {};

    // Only called if active from D3D9.Base
    virtual void _draw(const ImGuiViewport*) noexcept {};

    // Only called when remaining cooldown is requested
    virtual bool _specialCooldownConditionSatisfied() const noexcept { return true; }

   public:
    /// Info

    inline std::uint32_t      GetIndex() const { return mIndex; }
    inline bool               GetIsEnabled() const { return mIsEnabled; }
    inline const std::string& GetName() const { return mName; }
    inline const std::string& GetDescription() const { return mDescription; }
    inline bool               GetIsStatusEffect() const { return mIsStatusEffect; }
    inline bool               GetNeedsActivationWarning() const { return mNeedsActivationWarning; }

    /// Status

    inline Status GetStatus() const { return mStatus; }
    inline void   SetStatus(Status status) { mStatus = status; }

    /// Activation

    bool Activate() {
#if defined(_DEBUG)
      OutputDebugStringA(fmt::format("IGameEffect: '{}'->Activate() was called\n", GetName()).c_str());
#endif
      if (GetStatus() == Status::InActivateQueue && _activate()) {
#if defined(_DEBUG)
        OutputDebugStringA(fmt::format("IGameEffect: '{}' successfully activated\n", GetName()).c_str());
#endif

        mTimeActivated = std::chrono::steady_clock::now();
        SetStatus(Status::Active);
        return true;
      }
      return false;
    }
    bool Deactivate() {
#if defined(_DEBUG)
      OutputDebugStringA(fmt::format("IGameEffect: '{}'->Deactivate() was called\n", GetName()).c_str());
#endif
      if (GetStatus() == Status::InDeactivateQueue && _deactivate()) {
#if defined(_DEBUG)
        OutputDebugStringA(fmt::format("IGameEffect: '{}' successfully deactivated\n", GetName()).c_str());
#endif

        SetStatus(Status::Inactive);
        return true;
      }
      return false;
    }

    /// Active tick

    inline void ActiveTick() {
      if (GetStatus() == Status::Active) _activeTick();
    }

    /// Effect overlay

    inline void Draw(const ImGuiViewport* pMainViewport) {
      if (GetStatus() != Status::Active) return;

      if (this->GetElapsedTime() < 2000) {
        float alpha = 1.0f - (static_cast<float>(this->GetElapsedTime()) / 2000.0f);

        ImGui::WithStyle _s1(ImGuiStyleVar_Alpha, alpha);
        ImGui::SetNextWindowBgAlpha(alpha);
        ImGui::ShowNotice(this->GetName().c_str());
      }

      _draw(pMainViewport);
    }

    /// Limits

    // Cooldown (the number of effects needed to be activated before this effect is available)
    inline std::uint32_t GetCooldown() const { return mCooldown; }

    // Remaining cooldown (remaining number of effects needed to be activated before this effect is available)
    inline std::uint32_t GetRemainingCooldown() const {
      if (_specialCooldownConditionSatisfied()) return mRemainingCooldown;
      return 2578;
    }
    inline void DecreaseRemainingCooldown() {
      if (mRemainingCooldown > 0) mRemainingCooldown--;
    }
    inline void ResetRemainingCooldown() { mRemainingCooldown = mCooldown; }

    // Duration (in seconds)
    inline const auto& GetDuration() const { return mDuration; }

    // Compatibility
    bool IsCompatibleWith(std::uint32_t otherEffectIndex) const {
      return std::find(mIncompatibleIndices.cbegin(), mIncompatibleIndices.cend(), otherEffectIndex) == mIncompatibleIndices.cend();
    }

    /// Time

    inline const auto& GetTimeActivated() const { return mTimeActivated; }

    // Milliseconds
    std::int64_t GetElapsedTime() const {
      auto elapsed = std::chrono::steady_clock::now() - mTimeActivated;
      return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    // Milliseconds
    std::int64_t GetRemainingTime() const {
      auto elapsed = std::chrono::steady_clock::now() - mTimeActivated;
      return std::chrono::duration_cast<std::chrono::milliseconds>((mDuration - elapsed)).count();
    }

    /// Config handler

    inline auto& GetIsEnabledRef() { return mIsEnabled; }
    inline auto& GetCooldownRef() { return mCooldown; }
    inline auto& GetDurationRef() { return mDuration; }

    /// ctor

    explicit IGameEffect(std::uint32_t effectIndex) :
        mIndex(effectIndex),
        mIsEnabled(Config::Get()["Effects"][effectIndex]["IsEnabled"].GetBool()),
        mName(std::move(Config::Get()["Effects"][effectIndex]["Name"].Get<std::string>())),
        mDescription(std::move(Config::Get()["Effects"][effectIndex]["Description"].Get<std::string>())),
        mStatus(Status::Inactive),
        mCooldown(Config::Get()["Effects"][effectIndex]["Cooldown"].GetUint()),
        mDuration(std::move(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::duration<double>(Config::Get()["Effects"][effectIndex]["Duration"].GetDouble())))),
        mIsStatusEffect(Config::Get()["Effects"][effectIndex]["IsStatusEffect"].GetBool()),
        mNeedsActivationWarning(Config::Get()["Effects"][effectIndex]["NeedsActivationWarning"].GetBool()) {
      // Refresh cooldown
      mRemainingCooldown = mCooldown;
      // Add incompatible indices
      {
        const auto& node = Config::Get()["Effects"][effectIndex]["IncompatibleWith"];
        auto*       it   = node.Begin();
        while (it != node.End()) mIncompatibleIndices.push_back((it++)->GetUint());
      }
    }

    virtual ~IGameEffect() { this->SetStatus(Status::NotReady); }
  };
}  // namespace Extensions::Game
