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
#include <algorithm>
#include <cassert>
#include <cstddef>  // size_t
#include <cstdint>  // integer types
#include <deque>
#include <mutex>
#include <vector>
#pragma warning(pop)
// Random
#include "Helpers/Random.hpp"
// Effects & Modifiers base
#include "Extensions/Game/IGameEffect.hpp"
#include "Extensions/Game/IGameplayModifier.hpp"

namespace Extensions::Game {
  class IGameEffectsHandler {
   protected:
    // All initialized gameplay modifiers
    static inline std::vector<IGameplayModifier*> g_AllModifiers;
    // All initialized effects
    static inline std::vector<IGameEffect*> g_AllEffects;
    // Currently activated effects
    static inline std::deque<IGameEffect*> g_ActiveEffects;
    // Effects waiting to be activated
    static inline std::deque<IGameEffect*> g_ActivateQueue;
    // Effects waiting to be deactivated
    static inline std::deque<IGameEffect*> g_DeactivateQueue;
    // Mutex for handling queues
    static inline std::recursive_mutex g_MutexQueue;

   public:
#pragma region Queue helper functions(STATIC)
    static void AddToActivateQueue(IGameEffect* effect) {
      std::scoped_lock _l(g_MutexQueue);

      if (std::find(std::cbegin(g_ActivateQueue), std::cend(g_ActivateQueue), effect) == std::cend(g_ActivateQueue)) {
        effect->SetStatus(IGameEffect::Status::InActivateQueue);
        g_ActivateQueue.push_back(effect);
      }
    }
    static void AddToDeactivateQueue(IGameEffect* effect) {
      std::scoped_lock _l(g_MutexQueue);

      if (std::find(std::cbegin(g_DeactivateQueue), std::cend(g_DeactivateQueue), effect) == std::cend(g_DeactivateQueue)) {
        effect->SetStatus(IGameEffect::Status::InDeactivateQueue);
        g_DeactivateQueue.push_back(effect);
      }
    }
#pragma endregion
#pragma region Effect cooldowns(STATIC)
    static inline void DecreaseEffectCooldowns() {
      for (const auto& effect : g_AllEffects)
        if (effect->GetStatus() == IGameEffect::Status::Inactive) effect->DecreaseRemainingCooldown();
    }
#pragma endregion
#pragma region Effect activation / deactivation(STATIC)
    static void RunActivateQueue() {
      std::scoped_lock _l(g_MutexQueue);

      for (auto it = std::begin(g_ActivateQueue); it != std::end(g_ActivateQueue);) {
        const auto& effect = *it;
        if (effect->GetStatus() != IGameEffect::Status::InActivateQueue) {
          it = g_ActivateQueue.erase(it);
          continue;
        }

#if defined(_DEBUG)
        OutputDebugStringA(fmt::format("IGameEffectsHandler: Activating '{}'\n", effect->GetName()).c_str());
#endif
        if (effect->Activate()) {
#if defined(_DEBUG)
          OutputDebugStringA(fmt::format("IGameEffectsHandler: Activated '{}'\n", effect->GetName()).c_str());
#endif
          // Manage cooldowns
          DecreaseEffectCooldowns();
          effect->ResetRemainingCooldown();

          // Manage lists
          g_ActiveEffects.push_back(effect);
          it = g_ActivateQueue.erase(it);
        } else {
          it++;
        }
      }
    }
    static void RunDeactivateQueue() {
      std::scoped_lock _l(g_MutexQueue);
      // Deactivate expired effects
      for (const auto& effect : g_ActiveEffects)
        if (effect->GetRemainingTime() < 0) AddToDeactivateQueue(effect);

      // Do deactive queue
      for (auto it = std::begin(g_DeactivateQueue); it != std::end(g_DeactivateQueue);) {
        const auto& effect = *it;
        if (effect->GetStatus() != IGameEffect::Status::InDeactivateQueue) {
          it = g_ActivateQueue.erase(it);
          continue;
        }

#if defined(_DEBUG)
        OutputDebugStringA(fmt::format("IGameEffectsHandler: Deactivating '{}'\n", effect->GetName()).c_str());
#endif
        if (effect->Deactivate()) {
#if defined(_DEBUG)
          OutputDebugStringA(fmt::format("IGameEffectsHandler: Deactivated '{}'\n", effect->GetName()).c_str());
#endif
          // Manage lists
          g_ActiveEffects.erase(std::remove(std::begin(g_ActiveEffects), std::end(g_ActiveEffects), effect), std::end(g_ActiveEffects));
          it = g_DeactivateQueue.erase(it);
        } else {
          it++;
        }
      }
    }

    // Resets activate queue and then force runs deactivate queue
    static void DeactivateActiveEffects() {
      std::scoped_lock _l(g_MutexQueue);
      // Add to queue
      {
        g_ActivateQueue.clear();
        for (const auto& effect : g_ActiveEffects) AddToDeactivateQueue(effect);
      }
      // Force run queue
      RunDeactivateQueue();
    }
#pragma endregion
#pragma region Active effects tick(STATIC)
    static void RunActiveEffects() {
      std::scoped_lock _l(g_MutexQueue);
      for (const auto& effect : g_ActiveEffects) effect->ActiveTick();
    }
#pragma endregion
#pragma region Modifiers tick(STATIC)
    static void RunModifiers() {
      std::scoped_lock _l(g_MutexQueue);
      for (const auto& modifier : g_AllModifiers) modifier->OnTick();
    }
#pragma endregion
#pragma region Manage g_AllEffects(STATIC)
    static inline std::vector<IGameEffect*>& GetAllEffects() { return g_AllEffects; }
    static inline void                       AddEffect(IGameEffect* effect) { g_AllEffects.push_back(effect); }
    static inline void                       RemoveAllEffects() {
      std::scoped_lock _l(g_MutexQueue);

      g_ActiveEffects.clear();
      g_ActivateQueue.clear();
      g_DeactivateQueue.clear();
      g_AllEffects.clear();
    }

    // Will block until random effects are generated
    static inline std::vector<IGameEffect*> GetCompatibleRandomEffects(std::size_t amount) {
      std::scoped_lock _l(g_MutexQueue);

      std::vector<std::size_t> available_idx;
      // generate available effect indices
      {
        std::size_t max_idx = g_AllEffects.size();
        for (std::size_t idx = 0; idx < max_idx; idx++) {
          const auto& effect = g_AllEffects[idx];
          if (!effect->GetIsEnabled()) continue;
          if (effect->GetStatus() != IGameEffect::Status::Inactive) continue;
          if (effect->GetRemainingCooldown() > 0) continue;

          bool is_compatible = true;
          for (const auto& _activeEffect : g_ActiveEffects) is_compatible &= _activeEffect->IsCompatibleWith(effect->GetIndex());
          if (is_compatible) available_idx.push_back(idx);
        }
        // there aren't enough effects that satisfy the vote criteria, so just keep going
        if (available_idx.size() < amount) {
          DecreaseEffectCooldowns();
          return GetCompatibleRandomEffects(amount);
        }
      }
      // shuffle the ids
      std::shuffle(available_idx.begin(), available_idx.end(), Random::Get().GetGenerator());
      // get effects and return
      std::vector<IGameEffect*> ret(amount);
      for (std::size_t idx = 0; idx < amount; idx++) ret[idx] = g_AllEffects[available_idx[idx]];
      return ret;
    }
#pragma endregion
#pragma region Manage g_AllModifiers(STATIC)
    static inline std::vector<IGameplayModifier*>& GetAllModifiers() { return g_AllModifiers; }
    static inline void                             AddModifier(IGameplayModifier* modifier) { g_AllModifiers.push_back(modifier); }
    static inline void                             RemoveAllModifiers() {
      std::scoped_lock _l(g_MutexQueue);
      g_AllModifiers.clear();
    }
#pragma endregion
#pragma region Manage g_ActiveEffects(STATIC)
    static inline std::deque<IGameEffect*> GetActiveEffects() { return g_ActiveEffects; }
#pragma endregion

    virtual void ClearGenericMessage() const noexcept                      = 0;
    virtual void ShowActivationWarning(IGameEffect* effect) const noexcept = 0;
    virtual void SetupEffects() const noexcept                             = 0;
    virtual void SetupModifiers() const noexcept                           = 0;
    virtual void Init() const noexcept                                     = 0;

    IGameEffectsHandler()                           = default;
    IGameEffectsHandler(const IGameEffectsHandler&) = delete;
    void operator=(const IGameEffectsHandler&) = delete;

    virtual ~IGameEffectsHandler() {
      g_ActiveEffects.clear();
      g_ActivateQueue.clear();
      g_DeactivateQueue.clear();
      for (auto* _effect : g_AllEffects) delete _effect;
      g_AllEffects.clear();
    }
  };
}  // namespace Extensions::Game
