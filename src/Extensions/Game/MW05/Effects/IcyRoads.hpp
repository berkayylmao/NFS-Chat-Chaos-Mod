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
  class IcyRoads : public IGameEffect {
    std::vector<OpenMW::SimSurfaceEx::Backup> mBackup;

   protected:
    virtual bool _activate() noexcept override {
      bool needs_backup = mBackup.empty();
      OpenMW::SimSurfaceEx::ForEach([&](OpenMW::Attrib::Collection* collection, OpenMW::Attrib::Layouts::simsurfacelayout* layout) {
        if (needs_backup) mBackup.push_back(OpenMW::SimSurfaceEx::Backup(collection));
        layout->DRIVE_GRIP         = 0.35f;
        layout->LATERAL_GRIP       = 0.15f;
        layout->ROLLING_RESISTANCE = 0.1f;
      });

      return true;
    }
    virtual bool _deactivate() noexcept override {
      for (const auto& backup : mBackup) backup.RestoreBackup();
      return true;
    }

   public:
    explicit IcyRoads() : IGameEffect(129) {}
  };
}  // namespace Extensions::Game::MW05::Effects
