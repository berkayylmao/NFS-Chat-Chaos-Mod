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

namespace Extensions::DInput8 {
  namespace details {
    // [Dummy address, DetourInfo]
    static std::unordered_map<std::uintptr_t, std::unique_ptr<MemoryEditor::Editor::DetourInfo>> sDetourMap;

    static HRESULT __stdcall hkGetDeviceStateA(HINSTANCE hInstance, DWORD cbData, LPVOID lpvData) {
      HRESULT     ret    = DI_OK;
      auto* const device = reinterpret_cast<LPDIRECTINPUTDEVICE8A>(hInstance);
      const auto  dummy  = (*reinterpret_cast<std::uintptr_t**>(device))[10];
      if (const auto& detour = sDetourMap[dummy]) {
        detour->Undetour();
        ret = device->GetDeviceState(cbData, lpvData);
        detour->Detour();
      }

      if (cbData == sizeof(DIMOUSESTATE)) {
        if (ImGui::GetIO().WantCaptureMouse || ChaosMod::g_GameWindowLostFocus) {
          auto* const state = reinterpret_cast<DIMOUSESTATE*>(lpvData);
          ZeroMemory(state->rgbButtons, sizeof(state->rgbButtons));
        }
      } else if (cbData == sizeof(DIMOUSESTATE2)) {
        if (ImGui::GetIO().WantCaptureMouse || ChaosMod::g_GameWindowLostFocus) {
          auto* const state = reinterpret_cast<DIMOUSESTATE2*>(lpvData);
          ZeroMemory(state->rgbButtons, sizeof(state->rgbButtons));
        }
      } else if (cbData == 256) {  // keyboard
        if (ImGui::GetIO().WantCaptureKeyboard || ChaosMod::g_GameWindowLostFocus) ZeroMemory(lpvData, 256);
      }

      return ret;
    }
  }  // namespace details

  static inline void Init() {
    LPDIRECTINPUT8A di8 = nullptr;
    // Wait for DI8 device
    {
      auto** pdi8 = reinterpret_cast<LPDIRECTINPUT8A*>(OpenSpeed::GetInformationOfCurrentSpeedGame().ppDI8Device);
      while (di8 == nullptr) {
        di8 = *pdi8;
        std::this_thread::sleep_for(1s);
      }
    }

    di8->EnumDevices(
        DI8DEVCLASS_ALL,
        [](LPCDIDEVICEINSTANCEA lpddi, LPVOID pDI8) -> BOOL {
          LPDIRECTINPUTDEVICE8A device;
          reinterpret_cast<LPDIRECTINPUT8A>(pDI8)->CreateDevice(lpddi->guidInstance, &device, NULL);
          const auto* const vt_device = *reinterpret_cast<std::uintptr_t**>(device);

          if (!details::sDetourMap.count(vt_device[10]))
            details::sDetourMap[vt_device[10]] =
                std::move(MemoryEditor::Get().Detour(vt_device[9], reinterpret_cast<std::uintptr_t>(&details::hkGetDeviceStateA)));

          device->Release();
          return DIENUM_CONTINUE;
        },
        di8, DIEDFL_ATTACHEDONLY);
  }
}  // namespace Extensions::DInput8
