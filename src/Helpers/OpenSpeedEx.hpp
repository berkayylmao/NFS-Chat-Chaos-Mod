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
#include "Helpers/Random.hpp"
#include "Extensions/Game/MW05/MW05.hpp"
#include "Extensions/Game/Carbon/Carbon.hpp"
#pragma warning(push)
#pragma warning(disable : 4505)  // Unreferenced local function has been removed

namespace OpenSpeed {
  namespace MW05 {
    namespace EAXSound {
      static inline void** g_pEAXSound = reinterpret_cast<void**>(0x911FA8);

      static void ReStartRace(bool is321 = false) {
        if (*g_pEAXSound) reinterpret_cast<void(__thiscall*)(void*, bool)>(0x4C2170)(*g_pEAXSound, is321);
      }
    }  // namespace EAXSound

    namespace FEDatabaseEx {
      static void ChangeCarData(OpenSpeed::MW05::FECarRecord* record, Attrib::StringKey vehicleKey, FECustomizationRecord* customization = nullptr) {
        if (!record) return;

        auto* db = cFrontEndDatabase::Get();
        if (!db) return;

        record->mVehicleKey = record->mFEKey = vehicleKey;
        db->GetCareerSettings().CurrentCar   = record->mHandle;
        if (customization) {
          if (auto* db_customization = db->GetUserProfile()->mPlayersCarStable.GetCustomizationRecordByHandle(record->mCustomization)) {
            customization->mHandle = db_customization->mHandle;
            *db_customization      = *customization;
          }
        }
      }
    }  // namespace FEDatabaseEx

    namespace GameStatusEx {
      namespace details {
        static bool                  sFinishedPrologue;
        static bool                  sInPursuit;
        static GRaceStatus::PlayMode sPlayMode;
        static bool                  sProcessedPlayMode;

        static std::chrono::time_point<std::chrono::steady_clock> sPursuitTP{};
        static std::chrono::time_point<std::chrono::steady_clock> sRoamingTP{};
        static std::chrono::time_point<std::chrono::steady_clock> sRaceTP{};

        static void prologueUpdateThreadFn() {
          sFinishedPrologue = false;

          for (;;) {
            std::this_thread::sleep_for(1s);

            auto* db = cFrontEndDatabase::Get();
            if (!db) continue;

            if (auto* profile = db->GetUserProfile()) {
              if (profile->mPlayersCarStable.CareerRecords[0].mHandle != 0xFF) {
                sFinishedPrologue = true;
                break;
              }
            }
          }
        }
        static void statusUpdateThreadFn() {
          for (;;) {
            std::this_thread::sleep_for(1s);

            auto* race_status = GRaceStatus::Get();
            if (!race_status) {
              sInPursuit = sProcessedPlayMode = false;
              continue;
            }

            if (!sProcessedPlayMode) {
              if (race_status->mPlayMode == GRaceStatus::PlayMode::Roaming)
                sRoamingTP = std::chrono::steady_clock::now();
              else
                sRaceTP = std::chrono::steady_clock::now();

              sPlayMode          = race_status->mPlayMode;
              sProcessedPlayMode = true;
            } else {
              if (race_status->mPlayMode != sPlayMode) sProcessedPlayMode = false;
            }

            auto* pvehicle = PVehicleEx::GetPlayerInstance();
            if (!pvehicle) {
              sInPursuit = false;
              continue;
            }
            auto* ai = pvehicle->GetAIVehiclePtr();
            if (!ai) {
              sInPursuit = false;
              continue;
            }

            if (ai->GetPursuit() && !sInPursuit) {
              sPursuitTP = std::chrono::steady_clock::now();
              sInPursuit = true;
            } else if (!ai->GetPursuit() && sInPursuit) {
              sPursuitTP = {};
              sInPursuit = false;
            }
          }
        }
      }  // namespace details

      static bool HasFinishedPrologue() { return details::sFinishedPrologue; }
      static bool IsInPursuit() { return details::sInPursuit; }
      static bool IsRacing() { return details::sProcessedPlayMode && details::sPlayMode == GRaceStatus::PlayMode::Racing; }
      static bool IsRoaming() { return details::sProcessedPlayMode && details::sPlayMode == GRaceStatus::PlayMode::Roaming; }

      static std::int64_t MillisecondsSinceStartedPursuit() {
        if (!IsInPursuit()) return 0;
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - details::sPursuitTP).count();
      }

      static std::int64_t MillisecondsSinceStartedRacing() {
        if (!IsRacing()) return 0;
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - details::sRaceTP).count();
      }

      static std::int64_t MillisecondsSinceStartedRoaming() {
        if (!IsRoaming()) return 0;
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - details::sRoamingTP).count();
      }

      static std::int64_t SecondsSinceStartedPursuit() {
        if (!IsInPursuit()) return 0;
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - details::sPursuitTP).count();
      }

      static std::int64_t SecondsSinceStartedRacing() {
        if (!IsRacing()) return 0;
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - details::sRaceTP).count();
      }

      static std::int64_t SecondsSinceStartedRoaming() {
        if (!IsRoaming()) return 0;
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - details::sRoamingTP).count();
      }
    }  // namespace GameStatusEx

    namespace GenericMessageEx {
      static bool DisplayMessage(const std::string& text, IGenericMessage::FEngTypes messageType = IGenericMessage::FEngTypes::Type1,
                                 const std::string& iconName = "", bool hideMessages = false) {
        auto* player = PlayerEx::GetPlayerInstance();
        if (!player) return false;

        auto* hud = static_cast<FEngHud*>(player->GetHud());
        if (!hud) return false;

        auto* generic_message = static_cast<GenericMessage*>(hud->_mInterfaces.Find<IGenericMessage>());
        if (!generic_message) return false;

        std::uint32_t icon_hash = 0;
        if (iconName.length() > 0) icon_hash = OpenSpeed::MW05::Game::bStringHash(iconName.c_str());

        generic_message->RequestGenericMessage(
            text.c_str(), hideMessages, static_cast<Attrib::StringKey>(messageType), icon_hash,
            static_cast<Attrib::StringKey>(icon_hash ? IGenericMessage::IconDisplayTypes::ShowIcon : IGenericMessage::IconDisplayTypes::HideIcon),
            GenericMessage::Priority::Priority1);
        return true;
      }
    }  // namespace GenericMessageEx

    namespace PhysicsEx {
      static Physics::Upgrades::Package GetMaxLevelPackage(const Attrib::Gen::pvehicle& instance) {
        Physics::Upgrades::Package ret;
        // Tires
        ret.mTires = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Tires);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Tires)) ret.mJunkman |= JunkmanParts::Tires;
        // Brakes
        ret.mBrakes = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Brakes);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Brakes)) ret.mJunkman |= JunkmanParts::Brakes;
        // Chassis
        ret.mChassis = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Chassis);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Chassis)) ret.mJunkman |= JunkmanParts::Chassis;
        // Transmission
        ret.mTransmission = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Transmission);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Transmission)) ret.mJunkman |= JunkmanParts::Transmission;
        // Engine
        ret.mEngine = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Engine);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Engine)) ret.mJunkman |= JunkmanParts::Engine;
        // Induction
        ret.mInduction = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Induction);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Induction)) ret.mJunkman |= JunkmanParts::Induction;
        // NOS
        ret.mNOS = Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::NOS);
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::NOS)) ret.mJunkman |= JunkmanParts::NOS;

        return ret;
      }

      static Physics::Upgrades::Package GetRandomLevelPackage(const Attrib::Gen::pvehicle& instance) {
        Physics::Upgrades::Package ret;
        // Tires
        ret.mTires = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Tires))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Tires) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::Tires;
        // Brakes
        ret.mBrakes = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Brakes))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Brakes) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::Brakes;
        // Chassis
        ret.mChassis = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Chassis))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Chassis) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::Chassis;
        // Transmission
        ret.mTransmission = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Transmission))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Transmission) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::Transmission;
        // Engine
        ret.mEngine = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Engine))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Engine) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::Engine;
        // Induction
        ret.mInduction = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::Induction))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::Induction) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::Induction;
        // NOS
        ret.mNOS = static_cast<eCareerUpgradeLevels>(
            Random::Get().Generate(0, static_cast<std::int32_t>(Physics::Upgrades::Package::GetMaxLevel(instance, Physics::Upgrades::Type::NOS))));
        if (Physics::Upgrades::Package::CanInstallJunkman(instance, Physics::Upgrades::Type::NOS) && Random::Get().Generate(0, 1) == 1)
          ret.mJunkman |= JunkmanParts::NOS;

        return ret;
      }
    }  // namespace PhysicsEx

    namespace PVehicleEx {
      static bool ChangePlayerVehicle(Attrib::StringKey vehicleKey, FECustomizationRecord* customizations) {
        if (vehicleKey == 0) return false;
        if (GameStatusEx::SecondsSinceStartedRacing() < 2 && GameStatusEx::SecondsSinceStartedRoaming() < 2) return false;

        auto* pvehicle = PVehicleEx::GetPlayerInstance();
        if (!pvehicle) return false;

        auto* player = PlayerEx::GetPlayerInstance();
        if (!player) return false;

        auto* hud = static_cast<FEngHud*>(player->GetHud());
        if (!hud && (!hud->pSpeedometer || !hud->pTachometer || !hud->pTachometerDrag)) return false;

        if (!PVehicleEx::ChangePVehicleInto(pvehicle, vehicleKey, customizations).WasSuccessful) return false;

        if (GameStatusEx::IsRacing()) GenericMessageEx::DisplayMessage("Leaderboard will be fixed shortly");

        EAXSound::ReStartRace();
        return true;
      }
    }  // namespace PVehicleEx

    namespace TimeOfDayEx {
      struct Backup {
        TimeOfDay mBackup;

        bool RestoreBackup() const {
          auto* time_of_day = TimeOfDay::GetInstance();
          if (!time_of_day) return false;

          time_of_day->mSkyboxSpeedMultiplier    = mBackup.mSkyboxSpeedMultiplier;
          time_of_day->mTimeOfDaySpeedMultiplier = mBackup.mTimeOfDaySpeedMultiplier;
          time_of_day->mSunOrbitAxis.x           = mBackup.mSunOrbitAxis.x;
          time_of_day->mSunOrbitAxis.y           = mBackup.mSunOrbitAxis.y;
          return true;
        }

        static Backup CreateBackup(TimeOfDay* timeOfDay) {
          Backup ret;
          ret.mBackup = *timeOfDay;

          return ret;
        }
      };
    }  // namespace TimeOfDayEx
    namespace TimeOfDayLightingEx {
      struct Backup {
        std::uint32_t                            LightingKey;
        Attrib::Layouts::timeofdaylightinglayout LightingData;
        float                                    FogInLightScatter;
        float                                    FogSunFalloff;

        bool RestoreBackup() const {
          auto* lighting = Attrib::FindCollection("timeofdaylighting", this->LightingKey);
          if (!lighting) return false;

          *lighting->GetLayout<Attrib::Layouts::timeofdaylightinglayout>() = this->LightingData;
          if (auto* var = lighting->GetData<float>(Attrib::StringToKey("FogInLightScatter"))) *var = this->FogInLightScatter;
          if (auto* var = lighting->GetData<float>(Attrib::StringToKey("FogSunFalloff"))) *var = this->FogSunFalloff;
          return true;
        }

        Backup() : LightingKey(0), FogInLightScatter(0.0f), FogSunFalloff(0.0f) {}

        static Backup CreateBackup(Attrib::Collection* collection) {
          Backup ret;
          ret.LightingKey  = collection->mKey;
          ret.LightingData = *collection->GetLayout<Attrib::Layouts::timeofdaylightinglayout>();
          if (auto* var = collection->GetData<float>(Attrib::StringToKey("FogInLightScatter"))) ret.FogInLightScatter = *var;
          if (auto* var = collection->GetData<float>(Attrib::StringToKey("FogSunFalloff"))) ret.FogSunFalloff = *var;

          return ret;
        }
      };

      static void ForEach(const std::function<void(Attrib::Collection* c, Attrib::Layouts::timeofdaylightinglayout* p)>& fn) {
        for (std::uint32_t name : {0x94ABDFF0u, 0x919B6689u, 0xA01A3942u, 0x0E1C797Cu, Attrib::StringToKey("overcast"), Attrib::StringToKey("dusk_overcast"),
                                   Attrib::StringToKey("sunny"), Attrib::StringToKey("dusk_sunny")}) {
          auto* lighting = Attrib::FindCollection("timeofdaylighting", name);
          if (lighting) fn(lighting, lighting->GetLayout<Attrib::Layouts::timeofdaylightinglayout>());
        }
      }
    }  // namespace TimeOfDayLightingEx
  }    // namespace MW05
  namespace Carbon {
    namespace GameStatusEx {
      namespace details {
        static bool                  sInPursuit;
        static GRaceStatus::PlayMode sPlayMode;
        static bool                  sProcessedPlayMode;

        static std::chrono::time_point<std::chrono::steady_clock> sPursuitTP{};
        static std::chrono::time_point<std::chrono::steady_clock> sRoamingTP{};
        static std::chrono::time_point<std::chrono::steady_clock> sRaceTP{};

        static void statusUpdateThreadFn() {
          sInPursuit = sProcessedPlayMode = false;

          for (;;) {
            std::this_thread::sleep_for(1s);

            auto* race_status = GRaceStatus::Get();
            if (!race_status) {
              sInPursuit = sProcessedPlayMode = false;
              continue;
            }

            if (!sProcessedPlayMode) {
              if (race_status->mPlayMode == GRaceStatus::PlayMode::Roaming)
                sRoamingTP = std::chrono::steady_clock::now();
              else
                sRaceTP = std::chrono::steady_clock::now();

              sPlayMode          = race_status->mPlayMode;
              sProcessedPlayMode = true;
            } else {
              if (race_status->mPlayMode != sPlayMode) sProcessedPlayMode = false;
            }

            auto* pvehicle = PVehicleEx::GetPlayerInstance();
            if (!pvehicle) {
              sInPursuit = false;
              continue;
            }
            auto* ai = pvehicle->GetAIVehiclePtr();
            if (!ai) {
              sInPursuit = false;
              continue;
            }

            if (ai->GetPursuit() && !sInPursuit) {
              sPursuitTP = std::chrono::steady_clock::now();
              sInPursuit = true;
            } else if (!ai->GetPursuit() && sInPursuit) {
              sPursuitTP = {};
              sInPursuit = false;
            }
          }
        }
      }  // namespace details

      static bool IsInPursuit() { return details::sInPursuit; }
      static bool IsRacing() { return details::sProcessedPlayMode && details::sPlayMode == GRaceStatus::PlayMode::Racing; }
      static bool IsRoaming() { return details::sProcessedPlayMode && details::sPlayMode == GRaceStatus::PlayMode::Roaming; }

      static std::int64_t MillisecondsSinceStartedPursuit() {
        if (!IsInPursuit()) return 0;
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - details::sPursuitTP).count();
      }

      static std::int64_t MillisecondsSinceStartedRacing() {
        if (!IsRacing()) return 0;
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - details::sRaceTP).count();
      }

      static std::int64_t MillisecondsSinceStartedRoaming() {
        if (!IsRoaming()) return 0;
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - details::sRoamingTP).count();
      }

      static std::int64_t SecondsSinceStartedPursuit() {
        if (!IsInPursuit()) return 0;
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - details::sPursuitTP).count();
      }

      static std::int64_t SecondsSinceStartedRacing() {
        if (!IsRacing()) return 0;
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - details::sRaceTP).count();
      }

      static std::int64_t SecondsSinceStartedRoaming() {
        if (!IsRoaming()) return 0;
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - details::sRoamingTP).count();
      }
    }  // namespace GameStatusEx
    namespace EAXSound {
      static inline void** g_pEAXSound = reinterpret_cast<void**>(0xA8BA38);

      static void ReStartRace(bool is321 = false) {
        if (*g_pEAXSound) reinterpret_cast<void(__thiscall*)(void*, bool)>(0x516910)(*g_pEAXSound, is321);
      }
    }  // namespace EAXSound

    namespace PVehicleEx {
      static bool ChangePlayerVehicle(Attrib::Gen::pvehicle& instance, VehicleCustomizations* customizations) {
        auto* pvehicle = PVehicleEx::GetPlayerInstance();
        if (!pvehicle) return false;

        if (!PVehicleEx::ChangePVehicleInto(pvehicle, instance, customizations).WasSuccessful) return false;

        auto* race_status = GRaceStatus::Get();
        EAXSound::ReStartRace(race_status ? race_status->mRacerCount == 0 : false);

        return true;
      }
      static bool ChangePlayerVehicle(Attrib::StringKey vehicleKey, VehicleCustomizations* customizations) {
        if (vehicleKey == 0) return false;

        auto instance = Attrib::Gen::pvehicle::TryGetInstance(vehicleKey);
        if (!instance.mCollection) return false;

        return ChangePlayerVehicle(instance, customizations);
      }
    }  // namespace PVehicleEx
  }    // namespace Carbon
}  // namespace OpenSpeed

#pragma warning(pop)