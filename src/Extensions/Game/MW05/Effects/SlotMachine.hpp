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
  class SlotMachine : public IGameEffect {
    std::vector<std::pair<OpenMW::Attrib::StringKey, OpenMW::CarType>> mAvailableCarsMap;

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override {
      return OpenMW::GameStatusEx::HasFinishedPrologue() && !OpenMW::GameStatusEx::IsInPursuit();
    }

    virtual bool _activate() noexcept override {
      if (mAvailableCarsMap.empty()) {
        mAvailableCarsMap = {{OpenMW::Attrib::StringToKey("911gt2"), OpenMW::CarType::PORSCHE911GT2},
                             {OpenMW::Attrib::StringToKey("911Turbo"), OpenMW::CarType::PORSCHE911TURBO},
                             {OpenMW::Attrib::StringToKey("997s"), OpenMW::CarType::PORSCHE997S},
                             {OpenMW::Attrib::StringToKey("a3"), OpenMW::CarType::A3},
                             {OpenMW::Attrib::StringToKey("a4"), OpenMW::CarType::A4},
                             {OpenMW::Attrib::StringToKey("bmwm3gtr"), OpenMW::CarType::BMWM3GTR},
                             {OpenMW::Attrib::StringToKey("bmwm3gtre46"), OpenMW::CarType::BMWM3GTRE46},
                             {OpenMW::Attrib::StringToKey("camaro"), OpenMW::CarType::CAMARO},
                             {OpenMW::Attrib::StringToKey("carreragt"), OpenMW::CarType::PORSCHECARRERAGT},
                             {OpenMW::Attrib::StringToKey("caymans"), OpenMW::CarType::CAYMANS},
                             {OpenMW::Attrib::StringToKey("clio"), OpenMW::CarType::CLIO},
                             {OpenMW::Attrib::StringToKey("clk500"), OpenMW::CarType::CLK500},
                             {OpenMW::Attrib::StringToKey("cobaltss"), OpenMW::CarType::COBALTSS},
                             {OpenMW::Attrib::StringToKey("corvette"), OpenMW::CarType::CORVETTE},
                             {OpenMW::Attrib::StringToKey("corvettec6r"), OpenMW::CarType::CORVETTEC6R},
                             {OpenMW::Attrib::StringToKey("cts"), OpenMW::CarType::CTS},
                             {OpenMW::Attrib::StringToKey("db9"), OpenMW::CarType::DB9},
                             {OpenMW::Attrib::StringToKey("eclipsegt"), OpenMW::CarType::ECLIPSEGT},
                             {OpenMW::Attrib::StringToKey("elise"), OpenMW::CarType::ELISE},
                             {OpenMW::Attrib::StringToKey("fordgt"), OpenMW::CarType::FORDGT},
                             {OpenMW::Attrib::StringToKey("gallardo"), OpenMW::CarType::GALLARDO},
                             {OpenMW::Attrib::StringToKey("gti"), OpenMW::CarType::GTI},
                             {OpenMW::Attrib::StringToKey("gto"), OpenMW::CarType::GTO},
                             {OpenMW::Attrib::StringToKey("imprezawrx"), OpenMW::CarType::IMPREZAWRX},
                             {OpenMW::Attrib::StringToKey("is300"), OpenMW::CarType::IS300},
                             {OpenMW::Attrib::StringToKey("lancerevo8"), OpenMW::CarType::LANCEREVO8},
                             {OpenMW::Attrib::StringToKey("monaro"), OpenMW::CarType::MONARO},
                             {OpenMW::Attrib::StringToKey("murcielago"), OpenMW::CarType::MURCIELAGO},
                             {OpenMW::Attrib::StringToKey("mustanggt"), OpenMW::CarType::MUSTANGGT},
                             {OpenMW::Attrib::StringToKey("punto"), OpenMW::CarType::PUNTO},
                             {OpenMW::Attrib::StringToKey("rx7"), OpenMW::CarType::RX7},
                             {OpenMW::Attrib::StringToKey("rx8"), OpenMW::CarType::RX8},
                             {OpenMW::Attrib::StringToKey("sl65"), OpenMW::CarType::SL65},
                             {OpenMW::Attrib::StringToKey("sl500"), OpenMW::CarType::SL500},
                             {OpenMW::Attrib::StringToKey("slr"), OpenMW::CarType::SLR},
                             {OpenMW::Attrib::StringToKey("supra"), OpenMW::CarType::SUPRA},
                             {OpenMW::Attrib::StringToKey("tt"), OpenMW::CarType::TT},
                             {OpenMW::Attrib::StringToKey("viper"), OpenMW::CarType::VIPER},
                             {OpenMW::Attrib::StringToKey("cs_semi"), OpenMW::CarType::SEMI},
                             {OpenMW::Attrib::StringToKey("cs_clio_trafpizza"), OpenMW::CarType::PIZZA},
                             {OpenMW::Attrib::StringToKey("cs_clio_traftaxi"), OpenMW::CarType::TAXI},
                             {OpenMW::Attrib::StringToKey("cs_cts_traf_minivan"), OpenMW::CarType::MINIVAN},
                             {OpenMW::Attrib::StringToKey("cs_cts_traffictruck"), OpenMW::CarType::PICKUPA},
                             {OpenMW::Attrib::StringToKey("cs_trafcement"), OpenMW::CarType::CEMTR},
                             {OpenMW::Attrib::StringToKey("cs_trafgarb"), OpenMW::CarType::GARB}};
      }
      // Get random car
      const auto& rnd = mAvailableCarsMap[Random::Get().Generate(0, mAvailableCarsMap.size() - 1)];

      auto instance = OpenMW::Attrib::Gen::pvehicle::TryGetInstance(rnd.first);
      if (!instance.mCollection) return false;

      // Install random parts
      OpenMW::RideInfo ride_info(rnd.second);
      ride_info.SetStockParts();
      ride_info.SetRandomPaint();
      ride_info.SetRandomParts();
      OpenMW::FECustomizationRecord customizations;
      customizations.WriteRideIntoRecord(&ride_info);
      customizations.mInstalledPhysics = OpenMW::PhysicsEx::GetRandomLevelPackage(instance);
      customizations.mTunings[0]       = OpenMW::Physics::Tunings(
                Random::Get().Generate(-1.0f, 1.0f), Random::Get().Generate(-1.0f, 1.0f), Random::Get().Generate(-1.0f, 1.0f), Random::Get().Generate(-1.0f, 1.0f),
                Random::Get().Generate(-1.0f, 1.0f), Random::Get().Generate(-1.0f, 1.0f), Random::Get().Generate(-1.0f, 1.0f));
      customizations.mActiveTuning = OpenMW::eCustomTuningType::Setting1;
      // Swap car
      if (!OpenMW::PVehicleEx::ChangePlayerVehicle(rnd.first, &customizations)) return false;

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::SlotMachine);
      return true;
    }

   public:
    explicit SlotMachine() : IGameEffect(32) {}
  };
}  // namespace Extensions::Game::MW05::Effects
