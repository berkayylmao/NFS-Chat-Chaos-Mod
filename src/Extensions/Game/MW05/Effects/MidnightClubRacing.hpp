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
  class MidnightClubRacing : public IGameEffect {
    OpenMW::eMiniMapModes mBackupMiniMapMode;

   protected:
    virtual bool _activate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      auto& settings     = db->GetOptionsSettings().GetGameplaySettings();
      mBackupMiniMapMode = settings.RacingMiniMapMode;

      settings.RacingMiniMapMode = OpenMW::eMiniMapModes::Off;

      return true;
    }

    virtual bool _deactivate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      db->GetOptionsSettings().GetGameplaySettings().RacingMiniMapMode = mBackupMiniMapMode;
      OpenSpeed::MW05::Game::DisengageGPS();

      return true;
    }

    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(1.0f);

      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status || race_status->mPlayMode != OpenMW::GRaceStatus::PlayMode::Racing) return;

      OpenMW::GRaceStatus::DisableBarriers();

      if (auto* gps = OpenMW::GPS::Get())
        if (gps->mState == OpenMW::eGPSState::Down) OpenSpeed::MW05::Game::NavigatePlayerTo(race_status->mNextCheckpoint, nullptr);

      if (auto* params = race_status->mRaceParms) {
        if (auto* record = params->mRaceRecord) {
          if (auto* collection = record->mCollection) {
            if (auto* p_visible = collection->GetData<bool>(OpenMW::Attrib::StringToKey("CheckpointsVisible"))) {
              *p_visible = true;
            }
          }
        }
      }
    }

   public:
    explicit MidnightClubRacing() : IGameEffect(10), mBackupMiniMapMode(OpenMW::eMiniMapModes::Static) {}
  };
}  // namespace Extensions::Game::MW05::Effects
