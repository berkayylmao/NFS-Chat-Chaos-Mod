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
#include <cstdint>  // integer types
#include <fstream>
#include <filesystem>
#include <libloaderapi.h>  // GetModuleFileName
#include <WinUser.h>       // MessageBox

// rapidJSON
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#pragma warning(pop)

#include "Helpers/DefaultConfigFile.hpp"

class Config {
  // File paths

  constexpr static char CONST_CONFIG_FILENAME[]    = "Config.json";
  constexpr static char CONST_CONFIG_FOLDER_NAME[] = "ChatChaosMod";

 protected:
  std::filesystem::path mConfigFolderPath;
  std::filesystem::path mConfigFilePath;

  rapidjson::Document mConfigDocument;

 public:
  const auto& GetConfigFolderPath() const { return mConfigFolderPath; }
  void        Save() const {
    try {
      std::filesystem::create_directories(mConfigFolderPath);
      {
        std::ofstream                                      ofs(mConfigFilePath, std::ios_base::binary);
        rapidjson::OStreamWrapper                          osw(ofs);
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> w(osw);
        w.SetIndent(' ', 2);
        mConfigDocument.Accept(w);
      }
    } catch (const std::runtime_error& e) {
      MessageBoxA(nullptr, e.what(), "NFS Chat Chaos Mod - Error!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
  }

  rapidjson::Value& operator[](const char* const szConfigName) { return mConfigDocument[szConfigName]; }

 private:
  void Load() {
    try {
      if (!std::filesystem::exists(mConfigFilePath)) {
        mConfigDocument.Parse(ChaosMod::DefaultConfigFile::CONST_DEFAULT_CONFIG);
        Save();
      } else {
        std::ifstream             ifs(mConfigFilePath, std::ios_base::binary);
        rapidjson::IStreamWrapper isw(ifs);
        mConfigDocument.ParseStream(isw);

        // TODO: check for 'ConfigFileVersion'
      }
    } catch (const std::runtime_error& e) {
      MessageBoxA(nullptr, e.what(), "NFS Chat Chaos Mod - Error!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
  }

  Config() {
    std::wstring str_path(2048, 0);
    GetModuleFileNameW(NULL, &str_path[0], 2047);
    std::filesystem::path path(str_path);

    mConfigFolderPath = path.parent_path() / CONST_CONFIG_FOLDER_NAME;
    mConfigFilePath   = mConfigFolderPath / CONST_CONFIG_FILENAME;
    Load();
  }

 public:
  Config(const Config&) = delete;
  void operator=(const Config&) = delete;

  static Config& Get() {
    static Config singleton;
    return singleton;
  }
};
