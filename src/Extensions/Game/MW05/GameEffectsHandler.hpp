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
// Effects
#include "Extensions/Game/MW05/Effects/ThanosSnap.hpp"
#include "Extensions/Game/MW05/Effects/IfYouCantBeatThemKillThem.hpp"
#include "Extensions/Game/MW05/Effects/EnterTheMatrix.hpp"
#include "Extensions/Game/MW05/Effects/EARFQUAKE.hpp"
#include "Extensions/Game/MW05/Effects/Sbinnala.hpp"
#include "Extensions/Game/MW05/Effects/YouShouldHaveSaved.hpp"
#include "Extensions/Game/MW05/Effects/AYAYAAYAYA.hpp"
#include "Extensions/Game/MW05/Effects/DoABarrelRoll.hpp"
#include "Extensions/Game/MW05/Effects/Chernobyl.hpp"
#include "Extensions/Game/MW05/Effects/RainbowRoad.hpp"
#include "Extensions/Game/MW05/Effects/MidnightClubRacing.hpp"
#include "Extensions/Game/MW05/Effects/Timeout.hpp"
#include "Extensions/Game/MW05/Effects/BluetoothController.hpp"
#include "Extensions/Game/MW05/Effects/CruiseControl.hpp"
#include "Extensions/Game/MW05/Effects/SchoolZone.hpp"
#include "Extensions/Game/MW05/Effects/YouAreSafeThisTime.hpp"
#include "Extensions/Game/MW05/Effects/DeveloperMode.hpp"
#include "Extensions/Game/MW05/Effects/TheMagnumOpus.hpp"
#include "Extensions/Game/MW05/Effects/POVYouAreVolkswagenDuringEmissionTests.hpp"
#include "Extensions/Game/MW05/Effects/DontLookBackInAnger.hpp"
#include "Extensions/Game/MW05/Effects/PowerPointPresentation.hpp"
#include "Extensions/Game/MW05/Effects/PotatoPC.hpp"
#include "Extensions/Game/MW05/Effects/IntoTheVoid.hpp"
#include "Extensions/Game/MW05/Effects/CrossEyedRider.hpp"
#include "Extensions/Game/MW05/Effects/JesusTakeTheWheel.hpp"
#include "Extensions/Game/MW05/Effects/JumpToSafehouse.hpp"
#include "Extensions/Game/MW05/Effects/JumpToCarLot.hpp"
#include "Extensions/Game/MW05/Effects/FAK500.hpp"
#include "Extensions/Game/MW05/Effects/Snitch.hpp"
#include "Extensions/Game/MW05/Effects/TurnUpTheHeat.hpp"
#include "Extensions/Game/MW05/Effects/TurnDownTheHeat.hpp"
#include "Extensions/Game/MW05/Effects/INeedSomeHelp.hpp"
#include "Extensions/Game/MW05/Effects/SlotMachine.hpp"
#include "Extensions/Game/MW05/Effects/STONKS.hpp"
#include "Extensions/Game/MW05/Effects/Magneto.hpp"
#include "Extensions/Game/MW05/Effects/Superhot.hpp"
#include "Extensions/Game/MW05/Effects/BrakesJustSlowYouDown.hpp"
#include "Extensions/Game/MW05/Effects/ExperienceTheLag.hpp"
#include "Extensions/Game/MW05/Effects/AreYouAMinivanMom.hpp"
#include "Extensions/Game/MW05/Effects/DesignatedDriver.hpp"
#include "Extensions/Game/MW05/Effects/FastAndFuriousNOS.hpp"
#include "Extensions/Game/MW05/Effects/HowsYourCarRunning.hpp"
#include "Extensions/Game/MW05/Effects/GASGASGAS.hpp"
#include "Extensions/Game/MW05/Effects/CameraSwitcheroo.hpp"
#include "Extensions/Game/MW05/Effects/SuddentlyItsADragRace.hpp"
#include "Extensions/Game/MW05/Effects/Teasing.hpp"
#include "Extensions/Game/MW05/Effects/DriveOrDie.hpp"
#include "Extensions/Game/MW05/Effects/LookMaNoHands.hpp"
#include "Extensions/Game/MW05/Effects/WideCars.hpp"
#include "Extensions/Game/MW05/Effects/RCCars.hpp"
#include "Extensions/Game/MW05/Effects/JellyCars.hpp"
#include "Extensions/Game/MW05/Effects/TheJavaExperience.hpp"
#include "Extensions/Game/MW05/Effects/Flashbang.hpp"
#include "Extensions/Game/MW05/Effects/Impostor.hpp"
#include "Extensions/Game/MW05/Effects/ToTheMoon.hpp"
#include "Extensions/Game/MW05/Effects/PaperCars.hpp"
#include "Extensions/Game/MW05/Effects/YoBroIsThatASupra.hpp"
#include "Extensions/Game/MW05/Effects/TankMode.hpp"
#include "Extensions/Game/MW05/Effects/DoILookBetterInThisDress.hpp"
#include "Extensions/Game/MW05/Effects/AXEDeodorant.hpp"
#include "Extensions/Game/MW05/Effects/SuperSeducer.hpp"
#include "Extensions/Game/MW05/Effects/HeavyCars.hpp"
#include "Extensions/Game/MW05/Effects/LightCars.hpp"
#include "Extensions/Game/MW05/Effects/ThePSPExperience.hpp"
#include "Extensions/Game/MW05/Effects/BlurPowerups.hpp"
#include "Extensions/Game/MW05/Effects/EnjoyTheScenery.hpp"
#include "Extensions/Game/MW05/Effects/InsaneTraffic.hpp"
#include "Extensions/Game/MW05/Effects/CrazyTaxi.hpp"
#include "Extensions/Game/MW05/Effects/GigaRubberband.hpp"
#include "Extensions/Game/MW05/Effects/MegaRubberband.hpp"
#include "Extensions/Game/MW05/Effects/GuessWhosBack.hpp"
#include "Extensions/Game/MW05/Effects/YoureGoingTheWrongWay.hpp"
#include "Extensions/Game/MW05/Effects/BailMeOut.hpp"
#include "Extensions/Game/MW05/Effects/BlackOut.hpp"
#include "Extensions/Game/MW05/Effects/RKO.hpp"
#include "Extensions/Game/MW05/Effects/LightCops.hpp"
#include "Extensions/Game/MW05/Effects/HeavyCops.hpp"
#include "Extensions/Game/MW05/Effects/NeverBusted.hpp"
#include "Extensions/Game/MW05/Effects/StickShiftPro.hpp"
#include "Extensions/Game/MW05/Effects/BopIt.hpp"
#include "Extensions/Game/MW05/Effects/TunnelVision.hpp"
#include "Extensions/Game/MW05/Effects/TallCars.hpp"
#include "Extensions/Game/MW05/Effects/ImTIREd.hpp"
#include "Extensions/Game/MW05/Effects/MaybeInvertedSteering.hpp"
#include "Extensions/Game/MW05/Effects/DeliveryBoy.hpp"
#include "Extensions/Game/MW05/Effects/ElNoSabe.hpp"
#include "Extensions/Game/MW05/Effects/FlatCars.hpp"

// Modifiers
#include "Extensions/Game/MW05/Modifiers/CarScaleModifier.hpp"

namespace Extensions::Game::MW05 {
#pragma warning(push)
#pragma warning(disable : 4740)  // warning C4740: flow in or out of inline asm code suppresses global optimization
  namespace details {
    // https://github.com/ExOptsTeam/NFSMWExOpts/blob/e3c3494a848d0ebc6fa2aed482de21248272be8a/NFSMWExtraOptions/dllmain.cpp#L494
    namespace CarSkinFix {
      static DWORD sExit1 = 0x747F3F;
      static DWORD sExit2 = 0x747F2B;

      void __declspec(naked) CodeCave() {
        _asm {
          cmp edi, 1
          jl caveexit2
          cmp edi, 4
          jg fixskinid

          caveexit:
            mov esi,ecx
            mov byte ptr ds: [esi+07], 1
            jmp sExit1

          fixskinid:  // swap around DUMMY_SKIN/WHEEL2,3 and 4
            sub edi, 03
            cmp edi, 04
            jg fixskinid
            jmp caveexit

          caveexit2:
            jmp sExit2
        }
      }
    }  // namespace CarSkinFix
    namespace DisableEffectsOnUnload {
      static void __cdecl CodeCave() {
        IGameEffectsHandler::DeactivateActiveEffects();
        OpenSpeed::MW05::Game::BeginGameFlowUnloadTrack();
      }
    }  // namespace DisableEffectsOnUnload
    namespace DisableResetForPlayer {
      static DWORD sExit = 0x6B08C0;

      static bool __declspec(naked) CodeCave() {
        __asm {
          push eax
          push ebx
          push edi
          push esi
          mov esi, ecx  // backup
          mov ebx, ecx
          sub ebx, 0x4C
          mov ecx, [ebx+0x48]  // ecx: IVehicle*
          test ecx, ecx
          jz go_to_gamecode

          mov ebx, [ecx]  
          mov eax, [ebx+0x8]
          call eax  // IVehicle::GetSimable()
          mov edi, eax  // edi: ISimable*
          test edi, edi
          jz go_to_gamecode
          
          mov ecx, edi
          mov ebx, [edi]
          mov eax, [ebx+0x28]
          call eax  // IsPlayer()
          test al, al
          jz go_to_gamecode
          
          mov ecx, edi
          mov ebx, [edi]
          mov eax, [ebx+0x24]
          call eax  // IsOwnedByPlayer()
          test al, al
          jz go_to_gamecode
          
          mov ecx, esi
          pop esi
          pop edi
          pop ebx
          pop eax
          xor eax,eax
          retn 4
          
          go_to_gamecode:
          mov ecx, esi
          pop esi
          pop edi
          pop ebx
          pop eax
          jmp sExit
        }
      }
    }  // namespace DisableResetForPlayer
    namespace OverrideHeatLevelConstraints {
      static float __cdecl CodeCave(float _unk, float minHeatLevel, float maxHeatLevel) {
        minHeatLevel = 1.0f;
        maxHeatLevel = 10.0f;

        // unknown function that does math inside AIPursuit::OnTask
        return reinterpret_cast<float(__cdecl*)(float, float, float)>(0x402060)(_unk, minHeatLevel, maxHeatLevel);
      }
    }  // namespace OverrideHeatLevelConstraints

    namespace MainLoop {
      static void __cdecl CodeCave() {
        if (OpenSpeed::MW05::Variables::TheGameFlowManager == OpenSpeed::MW05::GameFlowState::Racing && !OpenSpeed::MW05::Variables::IsFadeScreenOn &&
            !OpenSpeed::MW05::Variables::IsInNIS) {
          IGameEffectsHandler::RunActiveEffects();
          IGameEffectsHandler::RunDeactivateQueue();
          IGameEffectsHandler::RunActivateQueue();
        }
        IGameEffectsHandler::RunModifiers();
      }
    }  // namespace MainLoop
  }    // namespace details
#pragma warning(pop)

  class GameEffectsHandler : public virtual IGameEffectsHandler {
   public:
    virtual void ClearGenericMessage() const noexcept override {
      OpenSpeed::MW05::GenericMessageEx::DisplayMessage("", OpenSpeed::MW05::IGenericMessage::FEngTypes::Type5, "", true);
    }
    virtual void ShowActivationWarning(IGameEffect* effect) const noexcept override {
      if (!effect) return;
      OpenSpeed::MW05::GenericMessageEx::DisplayMessage(fmt::format("`{}`\r\nimminent!", effect->GetName()),
                                                        OpenSpeed::MW05::IGenericMessage::FEngTypes::Type5);
    }

    virtual void SetupEffects() const noexcept override {
      IGameEffectsHandler::RemoveAllEffects();
      IGameEffectsHandler::AddEffect(new Effects::ThanosSnap());
      IGameEffectsHandler::AddEffect(new Effects::IfYouCantBeatThemKillThem());
      IGameEffectsHandler::AddEffect(new Effects::EnterTheMatrix());
      IGameEffectsHandler::AddEffect(new Effects::EARFQUAKE());
      IGameEffectsHandler::AddEffect(new Effects::Sbinnala());
      IGameEffectsHandler::AddEffect(new Effects::YouShouldHaveSaved());
      IGameEffectsHandler::AddEffect(new Effects::AYAYAAYAYA());
      IGameEffectsHandler::AddEffect(new Effects::DoABarrelRoll());
      IGameEffectsHandler::AddEffect(new Effects::Chernobyl());
      IGameEffectsHandler::AddEffect(new Effects::RainbowRoad());
      IGameEffectsHandler::AddEffect(new Effects::MidnightClubRacing());
      IGameEffectsHandler::AddEffect(new Effects::Timeout());
      IGameEffectsHandler::AddEffect(new Effects::BluetoothController());
      IGameEffectsHandler::AddEffect(new Effects::CruiseControl());
      IGameEffectsHandler::AddEffect(new Effects::SchoolZone());
      IGameEffectsHandler::AddEffect(new Effects::YouAreSafeThisTime());
      IGameEffectsHandler::AddEffect(new Effects::DeveloperMode());
      IGameEffectsHandler::AddEffect(new Effects::TheMagnumOpus());
      IGameEffectsHandler::AddEffect(new Effects::POVYouAreVolkswagenDuringEmissionTests());
      IGameEffectsHandler::AddEffect(new Effects::DontLookBackInAnger());
      IGameEffectsHandler::AddEffect(new Effects::PowerPointPresentation());
      IGameEffectsHandler::AddEffect(new Effects::PotatoPC());
      IGameEffectsHandler::AddEffect(new Effects::IntoTheVoid());
      IGameEffectsHandler::AddEffect(new Effects::CrossEyedRider());
      IGameEffectsHandler::AddEffect(new Effects::JesusTakeTheWheel());
      IGameEffectsHandler::AddEffect(new Effects::JumpToSafehouse());
      IGameEffectsHandler::AddEffect(new Effects::JumpToCarLot());
      IGameEffectsHandler::AddEffect(new Effects::FAK500());
      IGameEffectsHandler::AddEffect(new Effects::Snitch());
      IGameEffectsHandler::AddEffect(new Effects::TurnUpTheHeat());
      IGameEffectsHandler::AddEffect(new Effects::TurnDownTheHeat());
      IGameEffectsHandler::AddEffect(new Effects::INeedSomeHelp());
      IGameEffectsHandler::AddEffect(new Effects::SlotMachine());
      IGameEffectsHandler::AddEffect(new Effects::STONKS());
      IGameEffectsHandler::AddEffect(new Effects::Magneto());
      IGameEffectsHandler::AddEffect(new Effects::Superhot());
      IGameEffectsHandler::AddEffect(new Effects::BrakesJustSlowYouDown());
      IGameEffectsHandler::AddEffect(new Effects::ExperienceTheLag());
      IGameEffectsHandler::AddEffect(new Effects::AreYouAMinivanMom());
      IGameEffectsHandler::AddEffect(new Effects::DesignatedDriver());
      IGameEffectsHandler::AddEffect(new Effects::FastAndFuriousNOS());
      IGameEffectsHandler::AddEffect(new Effects::HowsYourCarRunning());
      IGameEffectsHandler::AddEffect(new Effects::GASGASGAS());
      IGameEffectsHandler::AddEffect(new Effects::CameraSwitcheroo());
      IGameEffectsHandler::AddEffect(new Effects::SuddentlyItsADragRace());
      IGameEffectsHandler::AddEffect(new Effects::Teasing());
      IGameEffectsHandler::AddEffect(new Effects::DriveOrDie());
      IGameEffectsHandler::AddEffect(new Effects::LookMaNoHands());
      IGameEffectsHandler::AddEffect(new Effects::WideCars());
      IGameEffectsHandler::AddEffect(new Effects::RCCars());
      IGameEffectsHandler::AddEffect(new Effects::JellyCars());
      IGameEffectsHandler::AddEffect(new Effects::TheJavaExperience());
      IGameEffectsHandler::AddEffect(new Effects::Flashbang());
      IGameEffectsHandler::AddEffect(new Effects::Impostor());
      IGameEffectsHandler::AddEffect(new Effects::ToTheMoon());
      IGameEffectsHandler::AddEffect(new Effects::PaperCars());
      IGameEffectsHandler::AddEffect(new Effects::YoBroIsThatASupra());
      IGameEffectsHandler::AddEffect(new Effects::TankMode());
      IGameEffectsHandler::AddEffect(new Effects::DoILookBetterInThisDress());
      IGameEffectsHandler::AddEffect(new Effects::AXEDeodorant());
      IGameEffectsHandler::AddEffect(new Effects::SuperSeducer());
      IGameEffectsHandler::AddEffect(new Effects::HeavyCars());
      IGameEffectsHandler::AddEffect(new Effects::LightCars());
      IGameEffectsHandler::AddEffect(new Effects::ThePSPExperience());
      IGameEffectsHandler::AddEffect(new Effects::BlurPowerups());
      IGameEffectsHandler::AddEffect(new Effects::EnjoyTheScenery());
      IGameEffectsHandler::AddEffect(new Effects::InsaneTraffic());
      IGameEffectsHandler::AddEffect(new Effects::CrazyTaxi());
      IGameEffectsHandler::AddEffect(new Effects::GigaRubberband());
      IGameEffectsHandler::AddEffect(new Effects::MegaRubberband());
      IGameEffectsHandler::AddEffect(new Effects::GuessWhosBack());
      IGameEffectsHandler::AddEffect(new Effects::YoureGoingTheWrongWay());
      IGameEffectsHandler::AddEffect(new Effects::BailMeOut());
      IGameEffectsHandler::AddEffect(new Effects::BlackOut());
      IGameEffectsHandler::AddEffect(new Effects::RKO());
      IGameEffectsHandler::AddEffect(new Effects::LightCops());
      IGameEffectsHandler::AddEffect(new Effects::HeavyCops());
      IGameEffectsHandler::AddEffect(new Effects::NeverBusted());
      IGameEffectsHandler::AddEffect(new Effects::StickShiftPro());
      IGameEffectsHandler::AddEffect(new Effects::BopIt());
      IGameEffectsHandler::AddEffect(new Effects::TunnelVision());
      IGameEffectsHandler::AddEffect(new Effects::TallCars());
      IGameEffectsHandler::AddEffect(new Effects::ImTIREd());
      IGameEffectsHandler::AddEffect(new Effects::MaybeInvertedSteering());
      IGameEffectsHandler::AddEffect(new Effects::DeliveryBoy());
      IGameEffectsHandler::AddEffect(new Effects::ElNoSabe());
      IGameEffectsHandler::AddEffect(new Effects::FlatCars());

      // Sort for config handler
      std::sort(std::begin(IGameEffectsHandler::g_AllEffects), std::end(IGameEffectsHandler::g_AllEffects),
                [](IGameEffect* l, IGameEffect* r) { return l->GetName() < r->GetName(); });
    }
    virtual void SetupModifiers() const noexcept override {
      IGameEffectsHandler::RemoveAllModifiers();
      IGameEffectsHandler::AddModifier(&Modifiers::CarScaleModifier::Get());
    }

    virtual void Init() const noexcept override {
      // Car skin fix (for PVehicle spawning during races) (from ExOpts)
      {
        std::uintptr_t addr = 0x75D2B6;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint8_t));
        *reinterpret_cast<std::uint8_t*>(addr) = 0x10;
        MemoryEditor::Get().LockMemory(addr);

        MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x747F19, reinterpret_cast<std::uintptr_t>(&details::CarSkinFix::CodeCave));
        MemoryEditor::Get().Make(MemoryEditor::MakeType::NOP, 0x73B324, 0x73B328);
      }
      // Don't hide HUD on Look Back Cam (from ExOpts)
      {
        std::uintptr_t addr = 0x4741DB;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint32_t));
        *reinterpret_cast<std::uint32_t*>(addr) = NULL;
        MemoryEditor::Get().LockMemory(addr);
      }
      /// Force enable game moment camera
      {
        // force settings to be only set to 'On'
        std::uintptr_t addr = 0x5100AE;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint64_t));
        *reinterpret_cast<std::uint64_t*>(addr) = 0x90909000000001BA;
        MemoryEditor::Get().LockMemory(addr);

        // force set the value to 'On'
        std::thread([&] {
          auto* db = OpenSpeed::MW05::cFrontEndDatabase::Get();
          while (!db) {
            db = OpenSpeed::MW05::cFrontEndDatabase::Get();
            std::this_thread::sleep_for(1s);
          }

          db->GetGameplaySettings().JumpCam = true;
        }).detach();
      }
      // Make game ignore FEManager::mPauseRequest
      {
        std::uintptr_t addr = 0x525B3E;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint32_t));
        *reinterpret_cast<std::uint32_t*>(addr) = 0x90C3C031;
        MemoryEditor::Get().LockMemory(addr);
      }
      // Disable reset for player
      {
        std::uintptr_t addr = 0x8ABA18;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uintptr_t));
        *reinterpret_cast<std::uintptr_t*>(addr) = reinterpret_cast<std::uintptr_t>(&details::DisableResetForPlayer::CodeCave);
        MemoryEditor::Get().LockMemory(addr);
      }
      // Force change attribute values
      {
        // Force AITrafficManager::ComputeDensity() to 100
        {
          std::uintptr_t addr1 = 0x926090;
          std::uintptr_t addr2 = 0x41EC31;
          std::uintptr_t addr3 = 0x41EC3A;

          MemoryEditor::Get().UnlockMemory(addr1, sizeof(float));
          MemoryEditor::Get().UnlockMemory(addr2, sizeof(std::uint16_t));
          MemoryEditor::Get().UnlockMemory(addr3, sizeof(std::uint16_t));

          *reinterpret_cast<float*>(addr1)         = 100.0f;
          *reinterpret_cast<std::uint16_t*>(addr2) = 0x22EB;
          *reinterpret_cast<std::uint16_t*>(addr3) = 0x19EB;

          MemoryEditor::Get().LockMemory(addr1);
          MemoryEditor::Get().LockMemory(addr2);
          MemoryEditor::Get().LockMemory(addr3);
        }

        // Set all traffic levels to max
        {
          std::uintptr_t addrs[] = {0x56DD92, 0x56DD96, 0x56DD9A, 0x56DD9E};
          for (const auto& addr : addrs) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint8_t));
            *reinterpret_cast<std::uint8_t*>(addr) = 100ui8;
            MemoryEditor::Get().LockMemory(addr);
          }
        }

        std::thread([&] {
          OpenMW::Attrib::Database* db = nullptr;
          while (!db) {
            db = OpenMW::Attrib::Database::Get();
            std::this_thread::sleep_for(1s);
          }

          // trafficpattern
          {
            OpenMW::Attrib::Class* trafficpattern = nullptr;
            while (!trafficpattern) {
              trafficpattern = db->GetClass(OpenMW::Attrib::StringToKey("trafficpattern"));
              std::this_thread::sleep_for(1s);
            }

            auto collection_key = trafficpattern->GetFirstCollection();
            for (size_t _1 = 0; _1 < trafficpattern->GetNumCollections(); _1++) {
              auto* collection = trafficpattern->GetCollection(collection_key);
              // Decrease spawn time
              if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("SpawnTime"))) *var = 0.01f;
              // Increase per-car values
              if (auto* var = collection->GetData<OpenMW::Attrib::Layouts::trafficpatternlayout::Vehicles>(OpenMW::Attrib::StringToKey("Vehicles"))) {
                std::size_t count = static_cast<std::size_t>(*reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(var) - 0x8));
                for (size_t _2 = 0; _2 < count; _2++) {
                  var->mMaxInstances = 100;
                  var->mRate         = 100.0f;
                  var++;
                }
              }
              // next collection
              collection_key = trafficpattern->GetNextCollection(collection_key);
            }
          }

          // gameplay
          {
            OpenMW::Attrib::Class* gameplay = nullptr;
            while (!gameplay) {
              gameplay = db->GetClass(OpenMW::Attrib::StringToKey("gameplay"));
              std::this_thread::sleep_for(1s);
            }

            auto collection_key = gameplay->GetFirstCollection();
            for (size_t _1 = 0; _1 < gameplay->GetNumCollections(); _1++) {
              auto* collection = gameplay->GetCollection(collection_key);
              // Enable cops
              if (auto* var = collection->GetData<bool>(OpenMW::Attrib::StringToKey("CopsInRace"))) *var = true;
              // Incrase max heat level
              if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("MaxHeatLevel"))) *var = 10.0f;
              // Increase traffic density
              if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("ForceTrafficDensity"))) *var = 100.0f;
              // Increase traffic level
              if (auto* var = collection->GetData<float>(OpenMW::Attrib::StringToKey("TrafficLevel"))) *var = 100.0f;
              // next collection
              collection_key = gameplay->GetNextCollection(collection_key);
            }
          }
        }).detach();
      }
      // Start game updaters
      {
        std::thread(OpenMW::GameStatusEx::details::prologueUpdateThreadFn).detach();
        std::thread(OpenMW::GameStatusEx::details::statusUpdateThreadFn).detach();
      }
      // Patches to make mw05 run the effect handler
      {
        MemoryEditor::Get().Make(MemoryEditor::MakeType::Call, 0x443DD9, reinterpret_cast<std::uintptr_t>(&details::OverrideHeatLevelConstraints::CodeCave));
        MemoryEditor::Get().Make(MemoryEditor::MakeType::Call, 0x6242AF, reinterpret_cast<std::uintptr_t>(&details::DisableEffectsOnUnload::CodeCave));
        MemoryEditor::Get().Make(MemoryEditor::MakeType::Call, 0x663D35, reinterpret_cast<std::uintptr_t>(&details::MainLoop::CodeCave));
      }
    }
  };
}  // namespace Extensions::Game::MW05
