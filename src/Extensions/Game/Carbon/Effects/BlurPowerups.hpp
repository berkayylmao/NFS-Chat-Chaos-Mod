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
// Images
#include "Extensions/D3D9/Images/BlurBargePowerUpIcon.hpp"
#include "Extensions/D3D9/Images/BlurBoltPowerUpIcon.hpp"
#include "Extensions/D3D9/Images/BlurBoostPowerUpIcon.hpp"
#include "Extensions/D3D9/Images/BlurShieldPowerUpIcon.hpp"

namespace Extensions::Game::Carbon::Effects {
  class BlurPowerups : public IGameEffect {
    //              //
    // PowerUp Base //
    //              //

    enum class PowerUpType : std::uint8_t { Bolt, Boost, Barge };

    struct IPowerUp {
     private:
      float mLockedSeconds;

     protected:
      enum class Direction : std::uint8_t { Forward, Backward };

     public:
      bool               mActivationLocked;
      LPDIRECT3DTEXTURE9 mIconTexture;

      virtual bool OnActivate() { return true; }
      virtual bool OnActivateBackwards() { return true; }
      virtual void OnTick() {
        if (mActivationLocked) {
          mLockedSeconds += ImGui::GetIO().DeltaTime;
          if (mLockedSeconds > 1.0f) {
            mActivationLocked = false;
            mLockedSeconds    = 0.0f;
          }
        }
      }
      virtual void DoCleanUp() {}

      IPowerUp() : mLockedSeconds(0.0f), mActivationLocked(false), mIconTexture(nullptr) {}
    };

    //              //
    // Bolt PowerUp //
    //              //

    class BoltPowerUp : public IPowerUp {
      std::unordered_map<OpenCarbon::PVehicle*, float> mSpawnedBolts;

      void createTexture() {
        while (!mIconTexture) {
          std::this_thread::sleep_for(1s);

          auto* d3d = ChaosMod::GetD3D9Device();
          if (!d3d) continue;

          D3DXCreateTextureFromFileInMemory(d3d, D3D9::Images::BlurBoltPowerUpIcon_data, D3D9::Images::BlurBoltPowerUpIcon_size, &this->mIconTexture);
        }
      }
      bool sendBolt(Direction boltDirection) {
        if (mActivationLocked) return false;

        auto instance = OpenCarbon::Attrib::Gen::pvehicle::TryGetInstance("traftaxi");
        if (!instance.mCollection) return false;

        auto* pvehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
        if (!pvehicle) return false;

        OpenCarbon::UMath::Vector3 position = pvehicle->GetPosition();
        OpenCarbon::UMath::Vector3 direction;
        pvehicle->GetRigidBody()->GetForwardVector(direction);

        if (boltDirection == Direction::Forward) {
          position.x += direction.x * 2.0f;
          position.y += direction.y * 2.0f;
        } else {
          position.x -= direction.x * 2.0f;
          position.y -= direction.y * 2.0f;

          direction.x *= -1.0f;
          direction.y *= -1.0f;
        }

        // Create new PVehicle
        auto* new_pvehicle = OpenCarbon::PVehicle::Construct(OpenCarbon::VehicleParams(OpenCarbon::DriverClass::None, instance, direction, position, nullptr)) |
                             OpenCarbon::PVehicleEx::ValidatePVehicle;
        if (!new_pvehicle) return false;
        new_pvehicle->SetSpeed(200.0f);
        new_pvehicle->GetRigidBody()->SetMass(1000.0f);

        mActivationLocked           = true;
        mSpawnedBolts[new_pvehicle] = 0.0f;
        FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::BlurBoltPowerUp);
        return true;
      }

     public:
      virtual bool OnActivate() override { return sendBolt(Direction::Forward); }
      virtual bool OnActivateBackwards() override { return sendBolt(Direction::Backward); }
      virtual void DoCleanUp() override {
        // Collect garbage (used bolts)
        for (auto it = std::begin(mSpawnedBolts); it != std::end(mSpawnedBolts);) {
          auto* pvehicle = it->first | OpenCarbon::PVehicleEx::ValidatePVehicle;
          if (!pvehicle) {
            it++;
            continue;
          }
          // check for collision
          if (auto* col = pvehicle->mCollisionBody) {
            if (col->HasHadCollision() || col->HasHadObjectCollision() || col->HasHadWorldCollision()) {
              pvehicle->Kill();
              it = mSpawnedBolts.erase(it);
              continue;
            }
          }
          // check for time alive
          it->second += pvehicle->GetOnScreenTime() + pvehicle->GetOffScreenTime();
          if (it->second > 5.0f) {
            pvehicle->Kill();
            it = mSpawnedBolts.erase(it);
            continue;
          }

          it++;
        }
      }

      void ClearList() { mSpawnedBolts.clear(); }

      BoltPowerUp() : IPowerUp() { std::thread(&BoltPowerUp::createTexture, this).detach(); }
    };

    //               //
    // Boost PowerUp //
    //               //

    class BoostPowerUp : public IPowerUp {
      bool mNeedToSuperBoostPlayer;

      void createTexture() {
        while (!mIconTexture) {
          std::this_thread::sleep_for(1s);

          auto* d3d = ChaosMod::GetD3D9Device();
          if (!d3d) continue;

          D3DXCreateTextureFromFileInMemory(d3d, D3D9::Images::BlurBoostPowerUpIcon_data, D3D9::Images::BlurBoostPowerUpIcon_size, &this->mIconTexture);
        }
      }
      bool doBoost(Direction direction) {
        if (mActivationLocked) return false;

        auto* pvehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
        if (!pvehicle) return false;

        if (direction == Direction::Forward) {
          pvehicle->SetSpeed(std::max(40.0f, std::min(90.0f, pvehicle->GetSpeed() * 2.0f)));
          FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::BlurBoostForwardPowerUp);
        } else {
          pvehicle->SetSpeed(4.0f);  // 15km/h
          mNeedToSuperBoostPlayer = true;
          FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::BlurBoostBackwardPowerUp);
        }

        mActivationLocked = true;
        return true;
      }

     public:
      virtual bool OnActivate() override { return doBoost(Direction::Forward); }
      virtual bool OnActivateBackwards() override { return doBoost(Direction::Backward); }

      virtual void OnTick() override {
        this->IPowerUp::OnTick();

        if (!mNeedToSuperBoostPlayer) return;
        __EXECUTE_EVERY_X_SECONDS__(1.25f);

        auto* pvehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
        if (!pvehicle) return;

        pvehicle->SetSpeed(80.0f);  // 288 km/h
        mNeedToSuperBoostPlayer = false;
      }

      BoostPowerUp() : IPowerUp(), mNeedToSuperBoostPlayer(false) { std::thread(&BoostPowerUp::createTexture, this).detach(); }
    };

    //               //
    // Barge PowerUp //
    //               //

    class BargePowerUp : public IPowerUp {
      void createTexture() {
        while (!mIconTexture) {
          std::this_thread::sleep_for(1s);

          auto* d3d = ChaosMod::GetD3D9Device();
          if (!d3d) continue;

          D3DXCreateTextureFromFileInMemory(d3d, D3D9::Images::BlurBargePowerUpIcon_data, D3D9::Images::BlurBargePowerUpIcon_size, &this->mIconTexture);
        }
      }
      bool pushObjectsAway(float radius = 80.0f, float force = 60.0f) {
        if (mActivationLocked) return false;

        auto* player_pvehicle = OpenCarbon::PVehicleEx::GetPlayerInstance();
        if (!player_pvehicle) return false;

        const auto& player_pos      = player_pvehicle->GetPosition();
        const auto  danger_zone_min = player_pos - OpenCarbon::UMath::Vector3(radius, radius, radius);
        const auto  danger_zone_max = player_pos + OpenCarbon::UMath::Vector3(radius, radius, radius);

        OpenCarbon::PVehicleEx::ForEachInstance([=](OpenCarbon::PVehicle* pvehicle) {
          if (pvehicle->IsPlayer()) return;

          const auto& pos = pvehicle->GetPosition();
          if (pos.x > danger_zone_min.x && pos.x < danger_zone_max.x && pos.y > danger_zone_min.y && pos.y < danger_zone_max.y && pos.z > danger_zone_min.z &&
              pos.z < danger_zone_max.z) {
            const auto v = (player_pos - pos).Normalize();

            pvehicle->GetRigidBody()->SetLinearVelocity(OpenCarbon::UMath::Vector3(
                // x
                v.x * -force,
                // y
                v.y * -force,
                // z
                0.0f));
          }
        });

        mActivationLocked = true;
        OpenSpeed::Carbon::Game::ShakeCamera();
        FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::BlurBargePowerUp);
        return true;
      }

     public:
      virtual bool OnActivate() override { return pushObjectsAway(); }
      virtual bool OnActivateBackwards() override { return pushObjectsAway(); }

      BargePowerUp() : IPowerUp() { std::thread(&BargePowerUp::createTexture, this).detach(); }
    };

    PowerUpType  mActivePowerUp;
    BoltPowerUp  mBoltPowerUp;
    BoostPowerUp mBoostPowerUp;
    BargePowerUp mBargePowerUp;

    void cleanup() {
      __EXECUTE_EVERY_X_SECONDS__(0.25f);

      mBoltPowerUp.DoCleanUp();
      mBargePowerUp.DoCleanUp();
      mBoostPowerUp.DoCleanUp();
    }

    ImVec2 mPowerupIconSize;

   protected:
    virtual bool _activate() noexcept override {
      mBoltPowerUp.ClearList();
      return true;
    }

    // Model
    virtual void _activeTick() noexcept override {
      this->cleanup();

      IPowerUp* active_powerup = nullptr;
      switch (mActivePowerUp) {
        case PowerUpType::Bolt:
          active_powerup = &mBoltPowerUp;
          break;
        case PowerUpType::Boost:
          active_powerup = &mBoostPowerUp;
          break;
        case PowerUpType::Barge:
          active_powerup = &mBargePowerUp;
          break;
      }

      active_powerup->OnTick();

      const auto& xinput = XInputWrapper::Get();
      if (xinput.IsConnected()) {
        if (xinput.GetKeyState(XINPUT_GAMEPAD_A) == XInputWrapper::KeyStatus::Up) active_powerup->OnActivate();
        if (xinput.GetLeftStick().y < -0.8f) active_powerup->OnActivateBackwards();
        if (xinput.GetKeyState(XINPUT_GAMEPAD_RIGHT_SHOULDER) == XInputWrapper::KeyStatus::Up) {
          switch (mActivePowerUp) {
            case PowerUpType::Bolt:
              mActivePowerUp = PowerUpType::Boost;
              break;
            case PowerUpType::Boost:
              mActivePowerUp = PowerUpType::Barge;
              break;
            case PowerUpType::Barge:
              mActivePowerUp = PowerUpType::Bolt;
              break;
          }
          FMODWrapper::Get().PlaySoundFX(FMODWrapper::SoundFX::BlurPowerUpSwitch);
        }
      }
    }

    // View
    virtual void _draw(const ImGuiViewport* viewport) noexcept override {
      ImGui::SetNextWindowBgAlpha(0.0f);
      ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Always);
      ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Always);
      ImGui::Begin("##BlurPowerUpBar", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration);
      {
        // Bolt
        {
          ImGui::SetCursorPosY(viewport->Size.y - ImGui::GetFontSize() - mPowerupIconSize.y);
          //                        CENTER OF SCREEN     -        HALF OF IMAGE        -         PADDING        -  IMAGE
          ImGui::SetCursorPosX((viewport->Size.x / 2.0f) - (mPowerupIconSize.x / 2.0f) - (ImGui::GetFontSize()) - mPowerupIconSize.x);
          ImGui::Image(mBoltPowerUp.mIconTexture, mPowerupIconSize, ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f),
                       ImVec4(1.0f, 1.0f, 1.0f, mActivePowerUp == PowerUpType::Bolt ? 1.0f : 0.33f));
        }
        // Boost
        {
          ImGui::SetCursorPosY(viewport->Size.y - ImGui::GetFontSize() - mPowerupIconSize.y);
          //                        CENTER OF SCREEN     -        HALF OF IMAGE
          ImGui::SetCursorPosX((viewport->Size.x / 2.0f) - (mPowerupIconSize.x / 2.0f));
          ImGui::Image(mBoostPowerUp.mIconTexture, mPowerupIconSize, ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f),
                       ImVec4(1.0f, 1.0f, 1.0f, mActivePowerUp == PowerUpType::Boost ? 1.0f : 0.33f));
        }
        // Barge
        {
          ImGui::SetCursorPosY(viewport->Size.y - ImGui::GetFontSize() - mPowerupIconSize.y);
          //                        CENTER OF SCREEN     +        HALF OF IMAGE        +         PADDING
          ImGui::SetCursorPosX((viewport->Size.x / 2.0f) + (mPowerupIconSize.x / 2.0f) + (ImGui::GetFontSize()));
          ImGui::Image(mBargePowerUp.mIconTexture, mPowerupIconSize, ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f),
                       ImVec4(1.0f, 1.0f, 1.0f, mActivePowerUp == PowerUpType::Barge ? 1.0f : 0.33f));
        }
      }
      ImGui::End();
    }

   public:
    explicit BlurPowerups() : IGameEffect(64), mActivePowerUp(PowerUpType::Boost) {
      mPowerupIconSize = ImVec2(140.0f, 100.0f) * ImGui::GetIO().FontGlobalScale;
    }
  };
}  // namespace Extensions::Game::Carbon::Effects
