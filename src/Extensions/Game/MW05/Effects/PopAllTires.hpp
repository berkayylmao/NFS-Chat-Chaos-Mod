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
  class PopAllTires : public IGameEffect {
   protected:
    virtual bool _activate() noexcept override {
      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) {
        auto* damage = pvehicle->mDamage | OpenMW::DamageableEx::AsDamageRacer;
        if (!damage) damage = pvehicle->mDamage | OpenMW::DamageableEx::AsDamageDragster;
        if (!damage) return;

        damage->Puncture(OpenMW::eTireIdx::FrontLeft);
        damage->Puncture(OpenMW::eTireIdx::FrontRight);
        damage->Puncture(OpenMW::eTireIdx::RearLeft);
        damage->Puncture(OpenMW::eTireIdx::RearRight);
      });
      return true;
    }

   public:
    explicit PopAllTires() : IGameEffect(99) {}
  };
}  // namespace Extensions::Game::MW05::Effects
