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
  class STONKS : public IGameEffect {
    std::vector<std::string> mInvestmentOptions;

   protected:
    virtual bool _activate() noexcept override {
      auto* db = OpenMW::cFrontEndDatabase::Get();
      if (!db) return false;

      auto        amount = Random::Get().Generate(-500000, 750000);
      const auto& type   = mInvestmentOptions[Random::Get().Generate(0, mInvestmentOptions.size() - 1)];
      // Take or give money
      db->GetCareerSettings().AwardCash(amount);
      // Announce
      if (amount < 0) {
        OpenMW::GenericMessageEx::DisplayMessage(fmt::format("Chat invested in {}\n and lost {}", type, std::abs(amount)),
                                                 OpenMW::IGenericMessage::FEngTypes::Type3);
      } else if (amount > 0) {
        OpenMW::GenericMessageEx::DisplayMessage(fmt::format("Chat invested in {}\n and won {}", type, amount), OpenMW::IGenericMessage::FEngTypes::Type4);
      } else {
        OpenMW::GenericMessageEx::DisplayMessage(fmt::format("Chat invested in {}\n but didn't win or lose anything", type, amount),
                                                 OpenMW::IGenericMessage::FEngTypes::Type4);
      }

      return true;
    }

   public:
    explicit STONKS() : IGameEffect(33) {
      mInvestmentOptions = {"Turkish Lira", "NFTs", "MADMONQ", "Dogecoin", "Rockport PD", "#FreeRazor Fund", "Instant Gaming"};
    }
  };
}  // namespace Extensions::Game::MW05::Effects
