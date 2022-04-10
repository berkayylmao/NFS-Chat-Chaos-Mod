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
#pragma warning(push, 0)
#include <filesystem>
#include <unordered_map>
#include <Winuser.h>  // MessageBox
// fmod
#include <fmod.hpp>
// fmt
#include "Helpers/fmt/format.h"
#pragma warning(pop)

class FMODWrapper {
 public:
  enum class SoundFX {
    FingerSnap,
    IfYouCantBeatThemKillThem,
    KEKW,
    SlotMachine,
    FAK,
    Dejavu,
    HowsYourCarRunning,
    MarioKartStarFX,
    TwoSecondsOfEarRape,
    WidePutin,
    MWJavaOST,
    Flashbang,
    YoBroIsThatASupra,
    DistortedMWSong,
    BlurBoltPowerUp,
    BlurBoostForwardPowerUp,
    BlurBoostBackwardPowerUp,
    BlurBargePowerUp,
    BlurPowerUpSwitch,
    GuessWhosBack
  };

 private:
  const std::unordered_map<const char*, SoundFX> mInternalInitializerMap = {{"fingersnap.mp3", SoundFX::FingerSnap},
                                                                            {"ifyoucantbeatthemkillthem.mp3", SoundFX::IfYouCantBeatThemKillThem},
                                                                            {"kekw.mp3", SoundFX::KEKW},
                                                                            {"slotmachine.mp3", SoundFX::SlotMachine},
                                                                            {"fak.mp3", SoundFX::FAK},
                                                                            {"dejavu.mp3", SoundFX::Dejavu},
                                                                            {"howsyourcarrunning.mp3", SoundFX::HowsYourCarRunning},
                                                                            {"mariokartstar.mp3", SoundFX::MarioKartStarFX},
                                                                            {"twosecondsofearrape.mp3", SoundFX::TwoSecondsOfEarRape},
                                                                            {"wideputin.mp3", SoundFX::WidePutin},
                                                                            {"mwjavaost.mp3", SoundFX::MWJavaOST},
                                                                            {"flashbang.mp3", SoundFX::Flashbang},
                                                                            {"yobroisthatasupra.mp3", SoundFX::YoBroIsThatASupra},
                                                                            {"distorted_mw_song.mp3", SoundFX::DistortedMWSong},
                                                                            {"blurboltpowerup.mp3", SoundFX::BlurBoltPowerUp},
                                                                            {"blurboostpowerupforward.mp3", SoundFX::BlurBoostForwardPowerUp},
                                                                            {"blurboostpowerupbackward.mp3", SoundFX::BlurBoostBackwardPowerUp},
                                                                            {"blurbargepowerup.mp3", SoundFX::BlurBargePowerUp},
                                                                            {"blurswitchpowerup.mp3", SoundFX::BlurPowerUpSwitch},
                                                                            {"guesswhosback.mp3", SoundFX::GuessWhosBack}};

 public:
  FMOD::System*                                     mFMODSystem;
  mutable std::unordered_map<SoundFX, FMOD::Sound*> mSoundFXMap;

  FMOD::Sound* GetSoundFX(SoundFX soundFX) const { return mSoundFXMap[soundFX]; }

  void PlaySoundFX(SoundFX soundFX) const {
    if (!mFMODSystem) return;
    if (auto* sound = mSoundFXMap[soundFX]) mFMODSystem->playSound(sound, nullptr, false, nullptr);
  }
  void PlaySoundFX(FMOD::Sound* pSoundFX) const {
    if (!mFMODSystem) return;
    if (!pSoundFX) return;
    mFMODSystem->playSound(pSoundFX, nullptr, false, nullptr);
  }

  void InitSoundFXMap(const std::filesystem::path& baseDir) {
    FMOD::Sound* dummy = nullptr;
    for (const auto& set : mInternalInitializerMap) {
      dummy = nullptr;

      try {
        if (mFMODSystem->createSound((baseDir / set.first).u8string().c_str(), FMOD_LOOP_OFF, 0, &dummy) != FMOD_OK)
          throw std::runtime_error(fmt::format("'{}' couldn't be loaded!", set.first));
      } catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "NFS Chat Chaos Mod - Error!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
      }
      mSoundFXMap[set.second] = dummy;
    }
  }

 private:
  FMODWrapper() {
    try {
      if (FMOD::System_Create(&mFMODSystem) != FMOD_OK) throw std::runtime_error("FMOD lib couldn't be initialized (System_Create)");
      std::uint32_t version;
      if (mFMODSystem->getVersion(&version) != FMOD_OK) throw std::runtime_error("FMOD lib couldn't be initialized (getVersion)");
      if (version < FMOD_VERSION) throw std::runtime_error(fmt::format("FMOD lib version {} doesn't match header version {}!", version, FMOD_VERSION));
      if (mFMODSystem->init(32, FMOD_INIT_NORMAL, nullptr) != FMOD_OK) throw std::runtime_error("FMOD lib couldn't be initialized (System Init)");
    } catch (const std::exception& e) {
      MessageBoxA(nullptr, e.what(), "NFS Chat Chaos Mod - Error!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
  }

 public:
  FMODWrapper(const FMODWrapper&) = delete;
  void operator=(const FMODWrapper&) = delete;

  static FMODWrapper& Get() {
    static FMODWrapper singleton;
    return singleton;
  }
};
