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
#include "Extensions/Game/MW05/Modifiers/CarScaleModifier.hpp"

namespace Extensions::Game::MW05::Effects {
  class ImTIREd : public IGameEffect {
    bool             mFixDamage;
    OpenMW::eTireIdx mTireToBlow;

   protected:
    virtual bool _activate() noexcept override {
      mFixDamage  = false;
      mTireToBlow = OpenMW::eTireIdx::FrontLeft;
      return true;
    }
    virtual bool _deactivate() noexcept override {
      auto* pvehicle = OpenMW::PVehicleEx::GetPlayerInstance();
      if (!pvehicle) return false;

      auto* damageable = pvehicle->mDamage | OpenMW::DamageableEx::AsDamageRacer;
      if (!damageable) return false;

      damageable->ResetDamage();
      return true;
    }

    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(1.0f);

      OpenMW::PVehicleEx::ForEachInstance([&](OpenMW::PVehicle* pvehicle) {
        auto* damageable = pvehicle->mDamage | OpenMW::DamageableEx::AsDamageRacer;
        if (!damageable) return;

        if (mFixDamage) {
          damageable->ResetDamage();
          mFixDamage = false;
        } else {
          mTireToBlow = static_cast<OpenMW::eTireIdx>(static_cast<std::uint32_t>(mTireToBlow) + 1);
          damageable->Puncture(mTireToBlow);

          if (mTireToBlow == OpenMW::eTireIdx::RearLeft) {
            mFixDamage  = true;
            mTireToBlow = OpenMW::eTireIdx::FrontLeft;
          }
        }
      });
    }

   public:
    explicit ImTIREd() : IGameEffect(82), mFixDamage(false), mTireToBlow(OpenMW::eTireIdx::FrontLeft) {}
  };
}  // namespace Extensions::Game::MW05::Effects
