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

namespace Extensions::Game::Carbon::Effects {
  class SlotMachine : public IGameEffect {
    std::vector<std::pair<OpenCarbon::Attrib::StringKey, OpenCarbon::CarType>> mAvailableCarsMap;

   protected:
    virtual bool _specialCooldownConditionSatisfied() const noexcept override { return !OpenCarbon::GameStatusEx::IsInPursuit(); }

    virtual bool _activate() noexcept override {
      if (mAvailableCarsMap.empty()) {
        mAvailableCarsMap = {{OpenCarbon::Attrib::StringToKey("911turbo"), OpenCarbon::CarType::PORSCHE_911TURBO},
                             {OpenCarbon::Attrib::StringToKey("carreragt"), OpenCarbon::CarType::PORSCHE_CARRERAGT},
                             {OpenCarbon::Attrib::StringToKey("viper"), OpenCarbon::CarType::DODGE_VIPER},
                             {OpenCarbon::Attrib::StringToKey("rx8"), OpenCarbon::CarType::MAZDA_RX8},
                             {OpenCarbon::Attrib::StringToKey("mustangt"), OpenCarbon::CarType::FORD_MUSTANGGT},
                             {OpenCarbon::Attrib::StringToKey("camaro"), OpenCarbon::CarType::CHEVROLET_CAMARO},
                             {OpenCarbon::Attrib::StringToKey("gto"), OpenCarbon::CarType::PONTIAC_GTO},
                             {OpenCarbon::Attrib::StringToKey("slr"), OpenCarbon::CarType::MERCEDES_SLR},
                             {OpenCarbon::Attrib::StringToKey("997s"), OpenCarbon::CarType::PORSCHE_997S},
                             {OpenCarbon::Attrib::StringToKey("bmwm3gtre46"), OpenCarbon::CarType::BMW_BMWM3GTRE46},
                             {OpenCarbon::Attrib::StringToKey("is300"), OpenCarbon::CarType::LEXUS_IS300},
                             {OpenCarbon::Attrib::StringToKey("monaro"), OpenCarbon::CarType::HOLDEN_MONARO},
                             {OpenCarbon::Attrib::StringToKey("sl65"), OpenCarbon::CarType::PORSCHE_SL65},
                             {OpenCarbon::Attrib::StringToKey("elise"), OpenCarbon::CarType::LOTUS_ELISE},
                             {OpenCarbon::Attrib::StringToKey("fordgt"), OpenCarbon::CarType::FORD_FORDGT},
                             {OpenCarbon::Attrib::StringToKey("eclipsegt"), OpenCarbon::CarType::MITSUBISHI_ECLIPSEGT},
                             {OpenCarbon::Attrib::StringToKey("supra"), OpenCarbon::CarType::TOYOTA_SUPRA},
                             {OpenCarbon::Attrib::StringToKey("rx7"), OpenCarbon::CarType::MAZDA_RX7},
                             {OpenCarbon::Attrib::StringToKey("murcielago"), OpenCarbon::CarType::LAMBORGHINI_MURCIELAGO},
                             {OpenCarbon::Attrib::StringToKey("caymans"), OpenCarbon::CarType::PORSCHE_CAYMANS},
                             {OpenCarbon::Attrib::StringToKey("clk500"), OpenCarbon::CarType::MERCEDES_CLK500},
                             {OpenCarbon::Attrib::StringToKey("db9"), OpenCarbon::CarType::ASTONMARTIN_DB9},
                             {OpenCarbon::Attrib::StringToKey("gallardo"), OpenCarbon::CarType::LAMBORGHINI_GALLARDO},
                             {OpenCarbon::Attrib::StringToKey("clio"), OpenCarbon::CarType::RENAULT_CLIO},
                             {OpenCarbon::Attrib::StringToKey("eclipse"), OpenCarbon::CarType::MITSUBISHI_ECLIPSE},
                             {OpenCarbon::Attrib::StringToKey("lancerevo9"), OpenCarbon::CarType::MITSUBISHI_LANCEREVO9},
                             {OpenCarbon::Attrib::StringToKey("corolla"), OpenCarbon::CarType::TOYOTA_COROLLA},
                             {OpenCarbon::Attrib::StringToKey("cuda"), OpenCarbon::CarType::PLYMOUTH_CUDA},
                             {OpenCarbon::Attrib::StringToKey("300c"), OpenCarbon::CarType::CHRYSLER_300C},
                             {OpenCarbon::Attrib::StringToKey("mr2"), OpenCarbon::CarType::TOYOTA_MR2},
                             {OpenCarbon::Attrib::StringToKey("mazda3sport"), OpenCarbon::CarType::MAZDA_MAZDA3SPORT},
                             {OpenCarbon::Attrib::StringToKey("mustangshlbyn"), OpenCarbon::CarType::FORD_MUSTANGSHLBYN},
                             {OpenCarbon::Attrib::StringToKey("350z"), OpenCarbon::CarType::NISSAN_350Z},
                             {OpenCarbon::Attrib::StringToKey("240sx"), OpenCarbon::CarType::NISSAN_240SX},
                             {OpenCarbon::Attrib::StringToKey("g35"), OpenCarbon::CarType::INFINITI_G35},
                             {OpenCarbon::Attrib::StringToKey("skyline"), OpenCarbon::CarType::NISSAN_SKYLINE},
                             {OpenCarbon::Attrib::StringToKey("imprezawrxsti"), OpenCarbon::CarType::SUBARU_IMPREZAWRXSTI},
                             {OpenCarbon::Attrib::StringToKey("r32"), OpenCarbon::CarType::VOLKSWAGEN_R32},
                             {OpenCarbon::Attrib::StringToKey("charge69"), OpenCarbon::CarType::DODGE_CHARGER69},
                             {OpenCarbon::Attrib::StringToKey("997tt"), OpenCarbon::CarType::PORSCHE_997TT},
                             {OpenCarbon::Attrib::StringToKey("brera"), OpenCarbon::CarType::ALFAROMEO_BRERA},
                             {OpenCarbon::Attrib::StringToKey("997gt3rs"), OpenCarbon::CarType::PORSCHE_997GT3RS},
                             {OpenCarbon::Attrib::StringToKey("corvettez06"), OpenCarbon::CarType::CHEVROLET_CORVETTEZ06},
                             {OpenCarbon::Attrib::StringToKey("challengern"), OpenCarbon::CarType::DODGE_CHALLENGERN},
                             {OpenCarbon::Attrib::StringToKey("r8"), OpenCarbon::CarType::AUDI_R8},
                             {OpenCarbon::Attrib::StringToKey("challenger71"), OpenCarbon::CarType::DODGE_CHALLENGER71},
                             {OpenCarbon::Attrib::StringToKey("chevelle"), OpenCarbon::CarType::DODGE_CHEVELLE},
                             {OpenCarbon::Attrib::StringToKey("europa"), OpenCarbon::CarType::LOTUS_EUROPA},
                             {OpenCarbon::Attrib::StringToKey("mazdaspeed3"), OpenCarbon::CarType::MAZDA_MAZDASPEED3},
                             {OpenCarbon::Attrib::StringToKey("camaron"), OpenCarbon::CarType::CHEVROLET_CAMARON},
                             {OpenCarbon::Attrib::StringToKey("jaguarxk"), OpenCarbon::CarType::JAGUAR_JAGUARXK},
                             {OpenCarbon::Attrib::StringToKey("charger06"), OpenCarbon::CarType::DODGE_CHARGER06},
                             {OpenCarbon::Attrib::StringToKey("ccx"), OpenCarbon::CarType::KOENIGSEGG_CCX},
                             {OpenCarbon::Attrib::StringToKey("zonda"), OpenCarbon::CarType::PAGANI_ZONDA},
                             {OpenCarbon::Attrib::StringToKey("murcielago640"), OpenCarbon::CarType::LAMBORGHINI_MURCIELAGO640},
                             {OpenCarbon::Attrib::StringToKey("roadrunner"), OpenCarbon::CarType::PLYMOUTH_ROADRUNNER},
                             {OpenCarbon::Attrib::StringToKey("mustangshlbyo"), OpenCarbon::CarType::FORD_MUSTANGSHLBYO}};
      }
      // Get random car
      const auto& rnd = mAvailableCarsMap[Random::Get().Generate(0, mAvailableCarsMap.size() - 1)];

      auto instance = OpenCarbon::Attrib::Gen::pvehicle::TryGetInstance(rnd.first);
      if (!instance.mCollection) return false;

      // Install random parts
      OpenCarbon::RideInfo ride_info(rnd.second);
      ride_info.SetStockParts();
      ride_info.SetRandomPaint();
      ride_info.SetRandomParts();
      OpenCarbon::VehicleCustomizations customizations;
      customizations.ReadFrom(ride_info);
      // Swap car
      if (!OpenCarbon::PVehicleEx::ChangePlayerVehicle(rnd.first, &customizations)) return false;

      FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::SlotMachine);
      return true;
    }

   public:
    explicit SlotMachine() : IGameEffect(32) {}
  };
}  // namespace Extensions::Game::Carbon::Effects
