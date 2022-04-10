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

namespace Extensions::WndProc::WindowedModeImprovements {
  namespace details {
    static LRESULT CALLBACK WndProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam) {
      switch (uMsg) {
        case WM_SYSCOMMAND:  // Disable ALT  menu
          if ((wParam & 0xFFF0) == SC_KEYMENU) return TRUE;
          break;
        case WM_SETCURSOR:  // Disable Windows cursor on window
          if (LOWORD(lParam) == HTCLIENT) {
            SetCursor(NULL);
            return TRUE;
          }
          break;
      }
      return MirrorHook::WndProc::g_constIgnoreThisReturn;
    }
  }  // namespace details

  static inline void Init() { MirrorHook::WndProc::AddExtension(&details::WndProc); }
}  // namespace Extensions::WndProc::WindowedModeImprovements
