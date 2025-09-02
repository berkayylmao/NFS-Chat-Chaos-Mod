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
  class AddTwoLaps : public IGameEffect {
   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override {
      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status) return false;
      if (race_status->mPlayMode != OpenMW::GRaceStatus::PlayMode::Racing) return false;

      if (auto* params = race_status->mRaceParms) {
        if (auto* record = params->mRaceRecord) {
          if (auto* collection = record->mCollection) {
            if (std::strstr(collection->GetLayout<OpenMW::Attrib::Layouts::gameplaylayout>()->CollectionName, "circuit")) return true;
          }
        }
      }
      return false;
    }

    virtual bool _activate() noexcept override {
      auto* race_status = OpenMW::GRaceStatus::Get();
      if (!race_status || race_status->mPlayMode != OpenMW::GRaceStatus::PlayMode::Racing) return false;

      if (auto* params = race_status->mRaceParms) {
        if (auto* record = params->mRaceRecord) {
          if (auto* collection = record->mCollection) {
            if (std::strstr(collection->GetLayout<OpenMW::Attrib::Layouts::gameplaylayout>()->CollectionName, "circuit")) {
              if (auto* p_num_laps = collection->GetData<std::int32_t>(OpenMW::Attrib::StringToKey("NumLaps"))) {
                if (*p_num_laps < 127) *p_num_laps += 2;
                return true;
              }
            }
          }
        }
      }
      return false;
    }

   public:
    explicit AddTwoLaps() : IGameEffect(132) {}
  };
}  // namespace Extensions::Game::MW05::Effects
