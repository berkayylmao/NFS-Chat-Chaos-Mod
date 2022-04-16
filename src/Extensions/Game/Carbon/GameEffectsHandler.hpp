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
#include "Extensions/Game/Carbon/Effects/ThanosSnap.hpp"
#include "Extensions/Game/Carbon/Effects/IfYouCantBeatThemKillThem.hpp"
//#include "Extensions/Game/Carbon/Effects/EnterTheMatrix.hpp"
#include "Extensions/Game/Carbon/Effects/EARFQUAKE.hpp"
#include "Extensions/Game/Carbon/Effects/Sbinnala.hpp"
#include "Extensions/Game/Carbon/Effects/YouShouldHaveSaved.hpp"
//#include "Extensions/Game/Carbon/Effects/AYAYAAYAYA.hpp"
#include "Extensions/Game/Carbon/Effects/DoABarrelRoll.hpp"
//#include "Extensions/Game/Carbon/Effects/Chernobyl.hpp"
//#include "Extensions/Game/Carbon/Effects/RainbowRoad.hpp"
//#include "Extensions/Game/Carbon/Effects/MidnightClubRacing.hpp"
//#include "Extensions/Game/Carbon/Effects/Timeout.hpp"
//#include "Extensions/Game/Carbon/Effects/BluetoothController.hpp"
#include "Extensions/Game/Carbon/Effects/CruiseControl.hpp"
#include "Extensions/Game/Carbon/Effects/SchoolZone.hpp"
#include "Extensions/Game/Carbon/Effects/YouAreSafeThisTime.hpp"
//#include "Extensions/Game/Carbon/Effects/TheMagnumOpus.hpp"
//#include "Extensions/Game/Carbon/Effects/POVYouAreVolkswagenDuringEmissionTests.hpp"
#include "Extensions/Game/Carbon/Effects/DontLookBackInAnger.hpp"
#include "Extensions/Game/Carbon/Effects/PowerPointPresentation.hpp"
#include "Extensions/Game/Carbon/Effects/PotatoPC.hpp"
#include "Extensions/Game/Carbon/Effects/IntoTheVoid.hpp"
//#include "Extensions/Game/Carbon/Effects/CrossEyedRider.hpp"
#include "Extensions/Game/Carbon/Effects/JesusTakeTheWheel.hpp"
#include "Extensions/Game/Carbon/Effects/JumpToSafehouse.hpp"
#include "Extensions/Game/Carbon/Effects/JumpToCarLot.hpp"
/*#include "Extensions/Game/Carbon/Effects/FAK500.hpp"
#include "Extensions/Game/Carbon/Effects/Snitch.hpp"*/
#include "Extensions/Game/Carbon/Effects/TurnUpTheHeat.hpp"
#include "Extensions/Game/Carbon/Effects/TurnDownTheHeat.hpp"
//#include "Extensions/Game/Carbon/Effects/INeedSomeHelp.hpp"
#include "Extensions/Game/Carbon/Effects/SlotMachine.hpp"
//#include "Extensions/Game/Carbon/Effects/STONKS.hpp"
#include "Extensions/Game/Carbon/Effects/Magneto.hpp"
/*#include "Extensions/Game/Carbon/Effects/Superhot.hpp"
#include "Extensions/Game/Carbon/Effects/BrakesJustSlowYouDown.hpp"*/
#include "Extensions/Game/Carbon/Effects/ExperienceTheLag.hpp"
//#include "Extensions/Game/Carbon/Effects/AreYouAMinivanMom.hpp"
#include "Extensions/Game/Carbon/Effects/DesignatedDriver.hpp"
//#include "Extensions/Game/Carbon/Effects/FastAndFuriousNOS.hpp"
#include "Extensions/Game/Carbon/Effects/HowsYourCarRunning.hpp"
//#include "Extensions/Game/Carbon/Effects/GASGASGAS.hpp"
//#include "Extensions/Game/Carbon/Effects/CameraSwitcheroo.hpp"
//#include "Extensions/Game/Carbon/Effects/SuddentlyItsADragRace.hpp"
#include "Extensions/Game/Carbon/Effects/Teasing.hpp"
//#include "Extensions/Game/Carbon/Effects/DriveOrDie.hpp"
//#include "Extensions/Game/Carbon/Effects/LookMaNoHands.hpp"
#include "Extensions/Game/Carbon/Effects/WideCars.hpp"
#include "Extensions/Game/Carbon/Effects/RCCars.hpp"
#include "Extensions/Game/Carbon/Effects/JellyCars.hpp"
#include "Extensions/Game/Carbon/Effects/TheJavaExperience.hpp"
#include "Extensions/Game/Carbon/Effects/Flashbang.hpp"
//#include "Extensions/Game/Carbon/Effects/Impostor.hpp"
#include "Extensions/Game/Carbon/Effects/ToTheMoon.hpp"
#include "Extensions/Game/Carbon/Effects/PaperCars.hpp"
#include "Extensions/Game/Carbon/Effects/YoBroIsThatASupra.hpp"
//#include "Extensions/Game/Carbon/Effects/TankMode.hpp"
//#include "Extensions/Game/Carbon/Effects/DoILookBetterInThisDress.hpp"
#include "Extensions/Game/Carbon/Effects/AXEDeodorant.hpp"
#include "Extensions/Game/Carbon/Effects/SuperSeducer.hpp"
//#include "Extensions/Game/Carbon/Effects/HeavyCars.hpp"
//#include "Extensions/Game/Carbon/Effects/LightCars.hpp"
#include "Extensions/Game/Carbon/Effects/ThePSPExperience.hpp"
#include "Extensions/Game/Carbon/Effects/BlurPowerups.hpp"
#include "Extensions/Game/Carbon/Effects/EnjoyTheScenery.hpp"
//#include "Extensions/Game/Carbon/Effects/InsaneTraffic.hpp"
#include "Extensions/Game/Carbon/Effects/CrazyTaxi.hpp"
#include "Extensions/Game/Carbon/Effects/GigaRubberband.hpp"
//#include "Extensions/Game/Carbon/Effects/MegaRubberband.hpp"
//#include "Extensions/Game/Carbon/Effects/GuessWhosBack.hpp"
//#include "Extensions/Game/Carbon/Effects/YoureGoingTheWrongWay.hpp"
//#include "Extensions/Game/Carbon/Effects/BailMeOut.hpp"
#include "Extensions/Game/Carbon/Effects/BlackOut.hpp"
#include "Extensions/Game/Carbon/Effects/RKO.hpp"
//#include "Extensions/Game/Carbon/Effects/LightCops.hpp"
//#include "Extensions/Game/Carbon/Effects/HeavyCops.hpp"
//#include "Extensions/Game/Carbon/Effects/NeverBusted.hpp"
//#include "Extensions/Game/Carbon/Effects/StickShiftPro.hpp"
#include "Extensions/Game/Carbon/Effects/BopIt.hpp"
#include "Extensions/Game/Carbon/Effects/TunnelVision.hpp"
#include "Extensions/Game/Carbon/Effects/TallCars.hpp"
//#include "Extensions/Game/Carbon/Effects/ImTIREd.hpp"
//#include "Extensions/Game/Carbon/Effects/MaybeInvertedSteering.hpp"
//#include "Extensions/Game/Carbon/Effects/DeliveryBoy.hpp"
#include "Extensions/Game/Carbon/Effects/FlatCars.hpp"
#include "Extensions/Game/Carbon/Effects/ConvoyTime.hpp"
#include "Extensions/Game/Carbon/Effects/BIGCARS.hpp"
#include "Extensions/Game/Carbon/Effects/LimoCars.hpp"
#include "Extensions/Game/Carbon/Effects/FlippedCars.hpp"

// Modifiers
#include "Extensions/Game/Carbon/Modifiers/CarScaleModifier.hpp"

namespace Extensions::Game::Carbon {
  namespace details {
    namespace DisableResetForPlayer {
      static DWORD sExit = 0x705F20;

      static bool __declspec(naked) CodeCave() {
        __asm {
          push eax
          push ebx
          push edi
          push esi
          mov esi, ecx  // backup
          mov ebx, ecx
          sub ebx, 0x44
          mov ecx, [ebx+0x40]  // ecx: IVehicle*
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
        return reinterpret_cast<float(__cdecl*)(float, float, float)>(0x4010E0)(_unk, minHeatLevel, maxHeatLevel);
      }
    }  // namespace OverrideHeatLevelConstraints

    namespace DisableEffectsOnUnload {
      static DWORD sInnerCaveFn = 0x671660;

      static void __declspec(naked) CodeCave() {
        __asm {
          push esi
          mov esi,ecx
          call sInnerCaveFn
          mov eax, esi
          pop esi
          call IGameEffectsHandler::DeactivateActiveEffects
          retn 4
        }
      }
    }  // namespace DisableEffectsOnUnload
    namespace MainLoop {
      static void __cdecl CodeCave() {
        if (OpenCarbon::Variables::TheGameFlowManager == OpenCarbon::GameFlowState::Racing && !OpenCarbon::Variables::IsGameplayPaused &&
            !OpenCarbon::Variables::IsInNIS) {
          IGameEffectsHandler::RunActiveEffects();
          IGameEffectsHandler::RunDeactivateQueue();
          IGameEffectsHandler::RunActivateQueue();
        }
        IGameEffectsHandler::RunModifiers();
      }
    }  // namespace MainLoop
  }    // namespace details

  class GameEffectsHandler : public virtual IGameEffectsHandler {
   public:
    virtual void ClearGenericMessage() const noexcept override {}
    virtual void ShowActivationWarning(IGameEffect* effect) const noexcept override {
      if (!effect) return;
    }

    virtual void SetupEffects() const noexcept override {
      IGameEffectsHandler::RemoveAllEffects();
      IGameEffectsHandler::AddEffect(new Effects::ThanosSnap());
      IGameEffectsHandler::AddEffect(new Effects::IfYouCantBeatThemKillThem());
      // IGameEffectsHandler::AddEffect(new Effects::EnterTheMatrix());
      IGameEffectsHandler::AddEffect(new Effects::EARFQUAKE());
      IGameEffectsHandler::AddEffect(new Effects::Sbinnala());
      IGameEffectsHandler::AddEffect(new Effects::YouShouldHaveSaved());
      // IGameEffectsHandler::AddEffect(new Effects::AYAYAAYAYA());
      IGameEffectsHandler::AddEffect(new Effects::DoABarrelRoll());
      /*IGameEffectsHandler::AddEffect(new Effects::Chernobyl());
      IGameEffectsHandler::AddEffect(new Effects::RainbowRoad());
      IGameEffectsHandler::AddEffect(new Effects::MidnightClubRacing());
      IGameEffectsHandler::AddEffect(new Effects::Timeout());
      IGameEffectsHandler::AddEffect(new Effects::BluetoothController());*/
      IGameEffectsHandler::AddEffect(new Effects::CruiseControl());
      IGameEffectsHandler::AddEffect(new Effects::SchoolZone());
      IGameEffectsHandler::AddEffect(new Effects::YouAreSafeThisTime());
      /*IGameEffectsHandler::AddEffect(new Effects::TheMagnumOpus());
      IGameEffectsHandler::AddEffect(new Effects::POVYouAreVolkswagenDuringEmissionTests());*/
      IGameEffectsHandler::AddEffect(new Effects::DontLookBackInAnger());
      IGameEffectsHandler::AddEffect(new Effects::PowerPointPresentation());
      IGameEffectsHandler::AddEffect(new Effects::PotatoPC());
      IGameEffectsHandler::AddEffect(new Effects::IntoTheVoid());
      // IGameEffectsHandler::AddEffect(new Effects::CrossEyedRider());
      IGameEffectsHandler::AddEffect(new Effects::JesusTakeTheWheel());
      IGameEffectsHandler::AddEffect(new Effects::JumpToSafehouse());
      IGameEffectsHandler::AddEffect(new Effects::JumpToCarLot());
      /*IGameEffectsHandler::AddEffect(new Effects::FAK500());
      IGameEffectsHandler::AddEffect(new Effects::Snitch());*/
      IGameEffectsHandler::AddEffect(new Effects::TurnUpTheHeat());
      IGameEffectsHandler::AddEffect(new Effects::TurnDownTheHeat());
      // IGameEffectsHandler::AddEffect(new Effects::INeedSomeHelp());
      IGameEffectsHandler::AddEffect(new Effects::SlotMachine());
      // IGameEffectsHandler::AddEffect(new Effects::STONKS());
      IGameEffectsHandler::AddEffect(new Effects::Magneto());
      /* IGameEffectsHandler::AddEffect(new Effects::Superhot());
      IGameEffectsHandler::AddEffect(new Effects::BrakesJustSlowYouDown());*/
      IGameEffectsHandler::AddEffect(new Effects::ExperienceTheLag());
      // IGameEffectsHandler::AddEffect(new Effects::AreYouAMinivanMom());
      IGameEffectsHandler::AddEffect(new Effects::DesignatedDriver());
      // IGameEffectsHandler::AddEffect(new Effects::FastAndFuriousNOS());
      IGameEffectsHandler::AddEffect(new Effects::HowsYourCarRunning());
      /*IGameEffectsHandler::AddEffect(new Effects::GASGASGAS());
      IGameEffectsHandler::AddEffect(new Effects::CameraSwitcheroo());
      IGameEffectsHandler::AddEffect(new Effects::SuddentlyItsADragRace());*/
      IGameEffectsHandler::AddEffect(new Effects::Teasing());
      /*IGameEffectsHandler::AddEffect(new Effects::DriveOrDie());
      IGameEffectsHandler::AddEffect(new Effects::LookMaNoHands());*/
      IGameEffectsHandler::AddEffect(new Effects::WideCars());
      IGameEffectsHandler::AddEffect(new Effects::RCCars());
      IGameEffectsHandler::AddEffect(new Effects::JellyCars());
      IGameEffectsHandler::AddEffect(new Effects::TheJavaExperience());
      IGameEffectsHandler::AddEffect(new Effects::Flashbang());
      // IGameEffectsHandler::AddEffect(new Effects::Impostor());
      IGameEffectsHandler::AddEffect(new Effects::ToTheMoon());
      IGameEffectsHandler::AddEffect(new Effects::PaperCars());
      IGameEffectsHandler::AddEffect(new Effects::YoBroIsThatASupra());
      /*IGameEffectsHandler::AddEffect(new Effects::TankMode());
      IGameEffectsHandler::AddEffect(new Effects::DoILookBetterInThisDress());*/
      IGameEffectsHandler::AddEffect(new Effects::AXEDeodorant());
      IGameEffectsHandler::AddEffect(new Effects::SuperSeducer());
      /*IGameEffectsHandler::AddEffect(new Effects::HeavyCars());
      IGameEffectsHandler::AddEffect(new Effects::LightCars());*/
      IGameEffectsHandler::AddEffect(new Effects::ThePSPExperience());
      IGameEffectsHandler::AddEffect(new Effects::BlurPowerups());
      IGameEffectsHandler::AddEffect(new Effects::EnjoyTheScenery());
      // IGameEffectsHandler::AddEffect(new Effects::InsaneTraffic());
      IGameEffectsHandler::AddEffect(new Effects::CrazyTaxi());
      IGameEffectsHandler::AddEffect(new Effects::GigaRubberband());
      /* IGameEffectsHandler::AddEffect(new Effects::MegaRubberband());
      IGameEffectsHandler::AddEffect(new Effects::GuessWhosBack());
      IGameEffectsHandler::AddEffect(new Effects::YoureGoingTheWrongWay());
      IGameEffectsHandler::AddEffect(new Effects::BailMeOut());*/
      IGameEffectsHandler::AddEffect(new Effects::BlackOut());
      IGameEffectsHandler::AddEffect(new Effects::RKO());
      /*IGameEffectsHandler::AddEffect(new Effects::LightCops());
      IGameEffectsHandler::AddEffect(new Effects::HeavyCops());
      IGameEffectsHandler::AddEffect(new Effects::NeverBusted());
      IGameEffectsHandler::AddEffect(new Effects::StickShiftPro());*/
      IGameEffectsHandler::AddEffect(new Effects::BopIt());
      IGameEffectsHandler::AddEffect(new Effects::TunnelVision());
      IGameEffectsHandler::AddEffect(new Effects::TallCars());
      /*IGameEffectsHandler::AddEffect(new Effects::ImTIREd());
      IGameEffectsHandler::AddEffect(new Effects::MaybeInvertedSteering());
      IGameEffectsHandler::AddEffect(new Effects::DeliveryBoy());*/
      IGameEffectsHandler::AddEffect(new Effects::FlatCars());
      IGameEffectsHandler::AddEffect(new Effects::ConvoyTime());
      IGameEffectsHandler::AddEffect(new Effects::BIGCARS());
      IGameEffectsHandler::AddEffect(new Effects::LimoCars());
      IGameEffectsHandler::AddEffect(new Effects::FlippedCars());

      // Sort for config handler
      std::sort(std::begin(IGameEffectsHandler::g_AllEffects), std::end(IGameEffectsHandler::g_AllEffects),
                [](IGameEffect* l, IGameEffect* r) { return l->GetName() < r->GetName(); });
    }
    virtual void SetupModifiers() const noexcept override {
      IGameEffectsHandler::RemoveAllModifiers();
      IGameEffectsHandler::AddModifier(&Modifiers::CarScaleModifier::Get());
    }

    virtual void Init() const noexcept override {
      // Don't hide HUD on Look Back Cam (from ExOpts)
      {
        std::uintptr_t addr = 0x48686B;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint32_t));
        *reinterpret_cast<std::uint32_t*>(addr) = NULL;
        MemoryEditor::Get().LockMemory(addr);
      }
      // Disable reset for player
      {
        std::uintptr_t addr = 0x9E5C4C;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uintptr_t));
        *reinterpret_cast<std::uintptr_t*>(addr) = reinterpret_cast<std::uintptr_t>(&details::DisableResetForPlayer::CodeCave);
        MemoryEditor::Get().LockMemory(addr);
      }
      // Make game ignore FEManager::mPauseRequest
      {
        std::uintptr_t addr = 0x4A6300;
        MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint32_t));
        *reinterpret_cast<std::uint32_t*>(addr) = 0x90C3C031;
        MemoryEditor::Get().LockMemory(addr);
      }
      // Force change attribute values
      {
        OpenCarbon::Variables::Tweak_TrafficStopSpawning = false;

        // Force AITrafficManager::ComputeDensity() to 100
        {
          std::uintptr_t addr1 = 0xA9E640;
          std::uintptr_t addr2 = 0x422CC8;
          std::uintptr_t addr3 = 0x422CD5;
          std::uintptr_t addr4 = 0x422CE5;

          MemoryEditor::Get().UnlockMemory(addr1, sizeof(float));
          MemoryEditor::Get().UnlockMemory(addr2, sizeof(std::uint64_t));
          MemoryEditor::Get().UnlockMemory(addr3, sizeof(std::uint64_t));
          MemoryEditor::Get().UnlockMemory(addr4, sizeof(std::uint16_t));

          *reinterpret_cast<float*>(addr1)         = 100.0f;
          *reinterpret_cast<std::uint64_t*>(addr2) = 0x909090903AEBF18B;
          *reinterpret_cast<std::uint64_t*>(addr3) = 0x909090902DEBC085;
          *reinterpret_cast<std::uint16_t*>(addr4) = 0x1FEB;

          MemoryEditor::Get().LockMemory(addr1);
          MemoryEditor::Get().LockMemory(addr2);
          MemoryEditor::Get().LockMemory(addr3);
          MemoryEditor::Get().LockMemory(addr4);
        }

        // Set all traffic levels to max
        {
          std::uintptr_t addrs[] = {0x7A9E3C, 0x7A9E40, 0x7A9E44, 0x7A9E48};
          for (const auto& addr : addrs) {
            MemoryEditor::Get().UnlockMemory(addr, sizeof(std::uint8_t));
            *reinterpret_cast<std::uint8_t*>(addr) = 100ui8;
            MemoryEditor::Get().LockMemory(addr);
          }
        }

        std::thread([&] {
          OpenCarbon::Attrib::Database* db = nullptr;
          while (!db) {
            db = OpenCarbon::Attrib::Database::Get();
            std::this_thread::sleep_for(1s);
          }

          // trafficpattern
          {
            OpenCarbon::Attrib::Class* trafficpattern = nullptr;
            while (!trafficpattern) {
              trafficpattern = db->GetClass(OpenCarbon::Attrib::StringToKey("trafficpattern"));
              std::this_thread::sleep_for(1s);
            }

            auto collection_key = trafficpattern->GetFirstCollection();
            for (size_t _1 = 0; _1 < trafficpattern->GetNumCollections(); _1++) {
              auto* collection = trafficpattern->GetCollection(collection_key);
              // Decrease spawn time
              if (auto* var = collection->GetData<float>(OpenCarbon::Attrib::StringToKey("SpawnTime"))) *var = 0.01f;
              // Increase per-car values
              if (auto* var = collection->GetData<OpenCarbon::Attrib::Layouts::trafficpatternlayout::Vehicles>(OpenCarbon::Attrib::StringToKey("Vehicles"))) {
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
            OpenCarbon::Attrib::Class* gameplay = nullptr;
            while (!gameplay) {
              gameplay = db->GetClass(OpenCarbon::Attrib::StringToKey("gameplay"));
              std::this_thread::sleep_for(1s);
            }

            auto collection_key = gameplay->GetFirstCollection();
            for (size_t _1 = 0; _1 < gameplay->GetNumCollections(); _1++) {
              auto* collection = gameplay->GetCollection(collection_key);
              // Enable cops
              if (auto* var = collection->GetData<bool>(OpenCarbon::Attrib::StringToKey("CopsInRace"))) *var = true;
              // Incrase max heat level
              if (auto* var = collection->GetData<float>(OpenCarbon::Attrib::StringToKey("MaxHeatLevel"))) *var = 10.0f;
              // Increase traffic density
              if (auto* var = collection->GetData<float>(OpenCarbon::Attrib::StringToKey("ForceTrafficDensity"))) *var = 100.0f;
              // Increase traffic level
              if (auto* var = collection->GetData<float>(OpenCarbon::Attrib::StringToKey("TrafficLevel"))) *var = 100.0f;
              // next collection
              collection_key = gameplay->GetNextCollection(collection_key);
            }
          }
        }).detach();
      }
      // Start game status updaters
      { std::thread(OpenCarbon::GameStatusEx::details::statusUpdateThreadFn).detach(); }
      // Patches to make mw05 run the effect handler
      {
        MemoryEditor::Get().Make(MemoryEditor::MakeType::Call, 0x449A91, reinterpret_cast<std::uintptr_t>(&details::OverrideHeatLevelConstraints::CodeCave));
        MemoryEditor::Get().Make(MemoryEditor::MakeType::Jump, 0x67D9D0, reinterpret_cast<std::uintptr_t>(&details::DisableEffectsOnUnload::CodeCave));
        MemoryEditor::Get().Make(MemoryEditor::MakeType::Call, 0x6B795C, reinterpret_cast<std::uintptr_t>(&details::MainLoop::CodeCave));
      }
    }
  };
}  // namespace Extensions::Game::Carbon
