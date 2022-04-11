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

namespace ChaosMod::DefaultConfigFile {
  constexpr char CONST_DEFAULT_CONFIG[] =
      "{\"Timers\":{\"IdleTimer\":5.0,\"VoteTimer\":20.0},\"Twitch\":{\"ChannelName\":\"\",\"Username\":\"\",\"UserOAuth\":\"\"},\"Effects\":[{\"Name\":"
      "\"Thanos Snap\",\"Description\":\"Removes half of all cars; sometimes including the player\'s. Perfectly balanced, as all things should "
      "be.\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"If You Can\'t Beat Them, Kill Them\",\"Description\":\"Blows the engine of all cars, except the "
      "player\'s\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Enter The Matrix\",\"Description\":\"Wireframe mode "
      "ConcernDoge\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":25,\"Duration\":40.0,\"IncompatibleWith\":[8,9,"
      "16]},{\"Name\":\"EARFQUAKE\",\"Description\":\"Shakes the ground, shakes the camera, shakes all the "
      "cars!\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":17,\"Duration\":30.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Sbinnala\",\"Description\":\"Pronto? Valteri? Sbinnala. (Makes the player car "
      "spin)\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"You Should Have Saved\",\"Description\":\"Crashes the "
      "game\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":true,\"Cooldown\":80,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"AYAYA AYAYA\",\"Description\":\"A Japanese girl reaches to the heaven each time you let go of the "
      "gas\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":40.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Do A Barrel Roll\",\"Description\":\"Do a 360 "
      "turn!\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Chernobyl\",\"Description\":\"Turns the environment to "
      "green\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[2,9]},{"
      "\"Name\":\"Rainbow Road\",\"Description\":\"Everyone likes some Mario Kart "
      "fun\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":60.0,\"IncompatibleWith\":[2,8]},{"
      "\"Name\":\"Midnight Club Racing\",\"Description\":\"Removes all barriers and minimap during races and enables GPS for "
      "checkpoints\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Timeout\",\"Description\":\"Disables "
      "controls\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":5.0,\"IncompatibleWith\":[42,46]},{"
      "\"Name\":\"Bluetooth Controller\",\"Description\":\"Makes input lag by 30 "
      "frames\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":12,\"Duration\":40.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Cruise Control\",\"Description\":\"YEEHAW\\n(Locks the velocity of the player\'s "
      "car)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":5,\"IncompatibleWith\":[14,47]},{"
      "\"Name\":\"School Zone\",\"Description\":\"Locks the speed of the all cars to "
      "30KM/"
      "H\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[13,47]},{"
      "\"Name\":\"You\'re Safe This Time\",\"Description\":\"Nothing "
      "happens\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":5,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Developer Mode\",\"Description\":\"Wireframe mode with a nuclear "
      "BMW\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":40.0,\"IncompatibleWith\":[2]},{"
      "\"Name\":\"The Magnum Opus\",\"Description\":\"Permanently installs maximum performance and Junkman parts to the player\'s "
      "car\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"POV: You\'re Volkswagen During Emission Tests\",\"Description\":\"Permanently uninstalls all parts from the player\'s "
      "car\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":42,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Don\'t Look Back In Anger\",\"Description\":\"Locks camera to look "
      "behind\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"PowerPoint Presentation\",\"Description\":\"2 frames per second "
      "Hhhehehe\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":19,\"Duration\":15.0,\"IncompatibleWith\":[21]},{"
      "\"Name\":\"Potato PC\",\"Description\":\"15 frames per second "
      "ResidentSleeper\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":13,\"Duration\":20.0,\"IncompatibleWith\":["
      "20]},{\"Name\":\"Into the Void\",\"Description\":\"Makes you fall into the "
      "void\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":25,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Cross-Eyed Rider\",\"Description\":\"Inverts "
      "steering\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":50.0,\"IncompatibleWith\":[83]},{"
      "\"Name\":\"Jesus Take the Wheel\",\"Description\":\"Forces the player\'s car to be controlled by "
      "AI\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":30.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Jump to "
      "Safehouse\",\"Description\":\"4House\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":10.0,"
      "\"IncompatibleWith\":[]},{\"Name\":\"Jump to Car Lot\",\"Description\":\"kuru1 kuru2 "
      "kuru3\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"FAK500\",\"Description\":\"Permanently changes the current car to a random, badly tuned "
      "CLK500\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Snitch\",\"Description\":\"Starts a pursuit with heat level "
      "10\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Turn Up the Heat\",\"Description\":\"Increase the heat level by "
      "1\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Turn Down the Heat\",\"Description\":\"Lower the heat level by "
      "1\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":0,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":\"I "
      "Need Some Help\",\"Description\":\"Adds $250k to the "
      "bank\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Slot Machine\",\"Description\":\"Gives the player a random car with random "
      "tuning\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16,67]},{"
      "\"Name\":\"S T O N K S\",\"Description\":\"Let chat invest a random amount of money and get or lose a random "
      "amount!\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Magneto\",\"Description\":\"Instantly teleport all cars to player\'s "
      "location\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Superhot\",\"Description\":\"Times moves only when you "
      "do\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":30.0,\"IncompatibleWith\":[39,73]},{"
      "\"Name\":\"Brakes Just Slow You Down\",\"Description\":\"Where we are going, we don\'t need "
      "brakes\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":90.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Experience the Lag\",\"Description\":\"Randomly locks frames, just as "
      "intended\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":25.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Are You a Minivan Mom?\",\"Description\":\"Mom\'s van just ain\'t build "
      "right\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Designated Driver\",\"Description\":\"More like designated to drink Kappa\\n(Random game speed every "
      "second)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":40.0,\"IncompatibleWith\":[35,73]},{"
      "\"Name\":\"Fast and Furious NOS\",\"Description\":\"Mega tuned infinite "
      "NOS!\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":1,\"Duration\":40.0,\"IncompatibleWith\":[42]},{"
      "\"Name\":\"How\'s Your Car Running?\",\"Description\":\"Sabotage the "
      "engine!\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"GAS GAS GAS\",\"Description\":\"Full throttle with NOS (Braking is "
      "disabled)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":35.0,\"IncompatibleWith\":[11,40,"
      "46]},{\"Name\":\"Camera Switcheroo\",\"Description\":\"Changes the camera every half a "
      "second\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":25.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Suddenly It\'s a Drag Race\",\"Description\":\"All cars use the drag racing "
      "system\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":true,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Teasing\",\"Description\":\"Free "
      "earrape\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":5,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Drive or Die\",\"Description\":\"If you let go off the gas, the engine "
      "blows\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":true,\"Cooldown\":16,\"Duration\":40.0,\"IncompatibleWith\":[11,16,42]},{"
      "\"Name\":\"Turn No More\",\"Description\":\"Locked "
      "steering\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":5.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Wide Cars\",\"Description\":\"IT\'S HIM "
      "widepeepoHappy\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[55]"
      "},{\"Name\":\"RC Cars\",\"Description\":\"Re-Volt\'s back baby "
      "R-)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Jelly "
      "Cars\",\"Description\":\"O_o\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,"
      "\"IncompatibleWith\":[]},{\"Name\":\"The Java Experience\",\"Description\":\"Java cures "
      "cancer\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[63]},{"
      "\"Name\":\"Flashbang\",\"Description\":\"Deploying "
      "flashbang!\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Impostor\",\"Description\":\"You vs "
      "You\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"To The Moon\",\"Description\":\"Diamond "
      "hands\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Paper Cars\",\"Description\":\"The car is there, you just have to look "
      "close\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[48]},{"
      "\"Name\":\"YO BRO IS THAT A SUPRA\",\"Description\":\"OH SHT THERES A SUPRA IN THE "
      "BACK\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Tank Mode\",\"Description\":\"Infinite collision "
      "mass\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[58,61,62,75,"
      "76]},{\"Name\":\"Do I Look Better In This Dress?\",\"Description\":\"There is no right answer :)\\n(Zero collision "
      "mass)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":30.0,\"IncompatibleWith\":[57,61,62,"
      "75,76]},{\"Name\":\"AXE Deodorant\",\"Description\":\"Nothing more repulsive than an AXE!\\n(Pushes everything away from "
      "you)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":60.0,\"IncompatibleWith\":[60]},{"
      "\"Name\":\"Super Seducer\",\"Description\":\"You sure know how to talk to girls.\\n(Pulls everything towards "
      "you)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":4,\"Duration\":60.0,\"IncompatibleWith\":[59]},{"
      "\"Name\":\"Heavy Cars\",\"Description\":\"2x heavier "
      "cars\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":30.0,\"IncompatibleWith\":[57,58,62,75,"
      "76]},{\"Name\":\"Light Cars\",\"Description\":\"2x lighter "
      "cars\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":30.0,\"IncompatibleWith\":[57,58,61,75,"
      "76]},{\"Name\":\"The PSP Experience\",\"Description\":\"The true open-world "
      "experience\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":30.0,\"IncompatibleWith\":[51]},{"
      "\"Name\":\"Blur Powerups\",\"Description\":\"The true racing "
      "experience\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Enjoy The Scenery\",\"Description\":\"It sure is lovely this time of the "
      "year\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":13,\"Duration\":20.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Insane Traffic\",\"Description\":\"Years of illegal street racing have made people of Rockport go "
      "insane\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Crazy Taxi\",\"Description\":\"Need a "
      "cab?\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16,32]},{"
      "\"Name\":\"Giga Rubberband\",\"Description\":\"He\'s always one step ahead of "
      "you\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":60.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Mega Rubberband\",\"Description\":\"You thought Earl was "
      "hard?\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":40.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Guess Who\'s Back\",\"Description\":\"Cross wants to have a talk with "
      "you\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"You\'re Going The Wrong Way\",\"Description\":\"DO U KNOW DA "
      "WAE??\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Bail Me Out\",\"Description\":\"Evades the current "
      "pursuit\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":2,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Black Out\",\"Description\":\"The New Year\'s stream was crazy, "
      "huh\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":1.0,\"IncompatibleWith\":[35,39]},{"
      "\"Name\":\"RKO\",\"Description\":\"WATCH OUT WATCH OUT WATCH "
      "OUT\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Light Cops\",\"Description\":\"1kg of Rockport "
      "cotton\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":30.0,\"IncompatibleWith\":[57,58,61,"
      "62,76]},{\"Name\":\"Heavy Cops\",\"Description\":\"1kg of Rockport "
      "steel\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":30.0,\"IncompatibleWith\":[57,58,61,"
      "62,75]},{\"Name\":\"Never Busted\",\"Description\":\"Rockport PD doesn\'t actually want "
      "you\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":12,\"Duration\":30.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Stick Shift Pro\",\"Description\":\"All cars change gears randomly every 2 seconds\\n(Also forced manual "
      "transmission)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":30.0,\"IncompatibleWith\":[]},"
      "{\"Name\":\"Bop It!\",\"Description\":\"The true Bop It "
      "gameplay\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":30.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Tunnel Vision\",\"Description\":\"You only need to look forward "
      "anyway\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":12,\"Duration\":45.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Tall Cars\",\"Description\":\"More headroom is always "
      "good\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"I\'m TIREd\",\"Description\":\"Get it? haHaa\\n(Blows the tires of all "
      "cars)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":24,\"Duration\":30.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Maybe Inverted Steering\",\"Description\":\"Inverts steering, but only "
      "sometimes\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":50.0,\"IncompatibleWith\":[23]}]}";
}