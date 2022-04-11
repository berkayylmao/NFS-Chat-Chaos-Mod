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
  class BopIt : public IGameEffect {
    enum class Mode : std::uint32_t { BopIt, TwistIt, PullIt, SpinIt };

   protected:
    virtual void _activeTick() noexcept override {
      __EXECUTE_EVERY_X_SECONDS__(1.5f);

      Mode rnd = static_cast<Mode>(Random::Get().Generate(static_cast<std::int32_t>(Mode::BopIt), static_cast<std::int32_t>(Mode::SpinIt)));

      OpenMW::PVehicleEx::ForEachInstance([=](OpenMW::PVehicle* pvehicle) {
        auto* rb = pvehicle->GetRigidBody();

        switch (rnd) {
          case Mode::BopIt:
            rb->SetLinearVelocity(rb->GetLinearVelocity() + OpenMW::UMath::Vector3(0.0f, 0.0f, -60.0f));
            FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::BopIt);
            break;
          case Mode::TwistIt:
            rb->SetAngularVelocity(rb->GetAngularVelocity() + OpenMW::UMath::Vector3(20.0f, 20.0f, 0.0f));
            FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::TwistIt);
            break;
          case Mode::PullIt:
            pvehicle->SetSpeed(std::min(-20.0f, -pvehicle->GetSpeed()));
            FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::PullIt);
            break;
          case Mode::SpinIt:
            rb->SetAngularVelocity(rb->GetAngularVelocity() + OpenMW::UMath::Vector3(0.0f, 0.0f, 20.0f));
            FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::SpinIt);
            break;
        }
      });
    }

   public:
    explicit BopIt() : IGameEffect(79) {}
  };
}  // namespace Extensions::Game::MW05::Effects
