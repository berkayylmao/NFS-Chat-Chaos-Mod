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
#pragma warning(push, 0)  // disable any warnings from OpenSpeed

#include <OpenSpeed/Game.MW05/MW05.h>
#include <OpenSpeed/Game.MW05/Extensions.h>
#include <OpenSpeed/Game.MW05/Types/Attrib.h>
#include <OpenSpeed/Game.MW05/Types/Attrib/Gen/gameplay.h>
#include <OpenSpeed/Game.MW05/Types/Attrib/Gen/timeofdaylighting.h>
#include <OpenSpeed/Game.MW05/Types/Attrib/Layouts/gameplaylayout.h>
#include <OpenSpeed/Game.MW05/Types/Attrib/Layouts/timeofdaylightinglayout.h>
#include <OpenSpeed/Game.MW05/Types/AICopManager.h>
#include <OpenSpeed/Game.MW05/Types/AIPursuit.h>
#include <OpenSpeed/Game.MW05/Types/AITarget.h>
#include <OpenSpeed/Game.MW05/Types/CarPart.h>
#include <OpenSpeed/Game.MW05/Types/cFrontendDatabase.h>
#include <OpenSpeed/Game.MW05/Types/FEngHud.h>
#include <OpenSpeed/Game.MW05/Types/Game.h>
#include <OpenSpeed/Game.MW05/Types/GenericMessage.h>
#include <OpenSpeed/Game.MW05/Types/GPS.h>
#include <OpenSpeed/Game.MW05/Types/GRaceParameters.h>
#include <OpenSpeed/Game.MW05/Types/GRacerInfo.h>
#include <OpenSpeed/Game.MW05/Types/GRaceStatus.h>
#include <OpenSpeed/Game.MW05/Types/GTrigger.h>
#include <OpenSpeed/Game.MW05/Types/IAudible.h>
#include <OpenSpeed/Game.MW05/Types/IDamageable.h>
#include <OpenSpeed/Game.MW05/Types/IEngine.h>
#include <OpenSpeed/Game.MW05/Types/InputPlayer.h>
#include <OpenSpeed/Game.MW05/Types/ITransmission.h>
#include <OpenSpeed/Game.MW05/Types/LocalPlayer.h>
#include <OpenSpeed/Game.MW05/Types/Physics.h>
#include <OpenSpeed/Game.MW05/Types/PVehicle.h>
#include <OpenSpeed/Game.MW05/Types/ResetCar.h>
#include <OpenSpeed/Game.MW05/Types/RBVehicle.h>
#include "OpenSpeed/Game.MW05/Types/RideInfo.h"
#include <OpenSpeed/Game.MW05/Types/TimeOfDay.h>

namespace OpenMW = OpenSpeed::MW05;

#pragma warning(pop)  // restore warnings
