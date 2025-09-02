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
  class CameraSwitcheroo : public IGameEffect {
    const std::uint32_t mMaxCameraIndex = 7;

    std::uint32_t                  mCurCameraIndex;
    OpenMW::ePlayerSettingsCameras mSavedCamera;

   protected:
    virtual bool _activate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      mSavedCamera    = db->GetPlayerSettings().CurCam;
      mCurCameraIndex = static_cast<std::uint32_t>(mSavedCamera);
      return true;
    }
    virtual bool _deactivate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      db->GetPlayerSettings().CurCam = mSavedCamera;
      return true;
    }

    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(0.5f);

      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return;

      if (++mCurCameraIndex > mMaxCameraIndex) mCurCameraIndex = 0;
      *reinterpret_cast<std::uint32_t*>(&db->GetPlayerSettings().CurCam) = mCurCameraIndex;
    }

   public:
    explicit CameraSwitcheroo() : IGameEffect(43), mCurCameraIndex(0), mSavedCamera(OpenMW::ePlayerSettingsCameras::Bumper) {}
  };
}  // namespace Extensions::Game::MW05::Effects
