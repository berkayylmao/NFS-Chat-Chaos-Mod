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
#include <cassert>
#include <cstddef>  // size_t
#include <cstdint>  // integer types
#include <random>
#include <vector>
#pragma warning(pop)

class Random {
  std::mt19937 mRNGEngine;

  Random() : mRNGEngine(std::random_device{}()) {
    std::array<std::uint32_t, std::mt19937::state_size> data;
    std::random_device                                  rd;
    // seed rngengine
    std::generate(std::begin(data), std::end(data), std::ref(rd));
    std::seed_seq seed(std::begin(data), std::end(data));
    mRNGEngine.seed(seed);
  }

 public:
  std::mt19937& GetGenerator() { return mRNGEngine; }
  std::int32_t  Generate(std::int32_t min, std::int32_t max) { return std::uniform_int_distribution<std::int32_t>(min, max)(GetGenerator()); }
  float         Generate(float min, float max) { return std::uniform_real_distribution<float>(min, std::nextafter(max, FLT_MAX))(GetGenerator()); }

  std::vector<std::int32_t> GenerateUniqueRange(std::size_t amount, std::int32_t min, std::int32_t max) {
    assert(std::abs(max - min) >= static_cast<std::int32_t>(amount) && "Unique range requested with incorrect arguments!!");

    std::vector<std::int32_t> possible_values;
    for (std::int32_t i = min; i <= max; i++) possible_values.push_back(i);
    std::shuffle(possible_values.begin(), possible_values.end(), GetGenerator());

    return std::vector<std::int32_t>(possible_values.cbegin(), possible_values.cbegin() + amount);
  }

  Random(const Random&) = delete;
  void operator=(const Random&) = delete;

  static inline Random& Get() {
    static Random singleton;
    return singleton;
  }
};
