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
      "\"Name\":\"Enter The "
      "Matrix\",\"Description\":\"ConcernDoge\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":25,\"Duration\":40.0,"
      "\"IncompatibleWith\":[8,9,16]},{\"Name\":\"EARFQUAKE\",\"Description\":\"Shakes the ground, shakes the camera, shakes all the "
      "cars!\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":17,\"Duration\":30.0,\"IncompatibleWith\":[106]},{"
      "\"Name\":\"Sbinnala\",\"Description\":\"Pronto? Valteri? Sbinnala.\\n(Makes all cars "
      "spin)\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":10.0,\"IncompatibleWith\":[101]},{"
      "\"Name\":\"You Should Have Saved\",\"Description\":\"Crashes the "
      "game\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":true,\"Cooldown\":80,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"AYAYA AYAYA\",\"Description\":\"A Japanese girl reaches to the heaven each time you let go of the "
      "gas\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":40.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Do A Barrel Roll\",\"Description\":\"Do a 360 "
      "turn!\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":10.0,\"IncompatibleWith\":[101]},{"
      "\"Name\":\"Chernobyl\",\"Description\":\"Turns the environment to "
      "green\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[2,9]},{"
      "\"Name\":\"Rainbow Road\",\"Description\":\"Everyone likes some Mario Kart "
      "fun\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":60.0,\"IncompatibleWith\":[2,8]},{"
      "\"Name\":\"Midnight Club Racing\",\"Description\":\"Removes all barriers and minimap during races and enables GPS for "
      "checkpoints\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Timeout\",\"Description\":\"Disables "
      "controls\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":5.0,\"IncompatibleWith\":[46]},{"
      "\"Name\":\"Bluetooth Controller\",\"Description\":\"Makes input lag by 30 "
      "frames\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":12,\"Duration\":40.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Cruise Control\",\"Description\":\"Just sit back and enjoy the ride\\n(Locks player\'s "
      "speed)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":50.0,\"IncompatibleWith\":[14,47,101]"
      "},{\"Name\":\"School Zone\",\"Description\":\"Limits the speed of all cars to "
      "30KM/"
      "H\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[13,47,101]},{"
      "\"Name\":\"You\'re Safe This Time\",\"Description\":\"Nothing "
      "happens\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":5,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Developer Mode\",\"Description\":\"Wireframe mode with a nuclear "
      "BMW\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":40.0,\"IncompatibleWith\":[2]},{"
      "\"Name\":\"The Magnum Opus\",\"Description\":\"Permanently installs maximum performance and Junkman parts to the player\'s "
      "car\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"POV: You\'re Volkswagen During Emission Tests\",\"Description\":\"Permanently uninstalls all parts from the player\'s "
      "car\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":42,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Don\'t Look Back In Anger\",\"Description\":\"Locks camera to look "
      "behind\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[94]},{"
      "\"Name\":\"PowerPoint Presentation\",\"Description\":\"2 frames per second "
      "Hhhehehe\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":19,\"Duration\":15.0,\"IncompatibleWith\":[21]},{"
      "\"Name\":\"Potato PC\",\"Description\":\"15 frames per second "
      "ResidentSleeper\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":13,\"Duration\":20.0,\"IncompatibleWith\":["
      "20]},{\"Name\":\"Into The Void\",\"Description\":\"Makes you fall into the "
      "void\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":25,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Cross-Eyed Rider\",\"Description\":\"Inverts "
      "steering\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":50.0,\"IncompatibleWith\":[83]},{"
      "\"Name\":\"Jesus Take the Wheel\",\"Description\":\"Forces the player\'s car to be controlled by "
      "AI\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":30.0,\"IncompatibleWith\":[92]},{\"Name\":"
      "\"Jump To "
      "Safehouse\",\"Description\":\"4House\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":10.0,"
      "\"IncompatibleWith\":[]},{\"Name\":\"Jump To Car Lot\",\"Description\":\"kuru1 kuru2 "
      "kuru3\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"FAK500\",\"Description\":\"Permanently changes the current car to a random, badly tuned "
      "CLK500\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Snitch\",\"Description\":\"Starts a pursuit with heat level "
      "10\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Turn Up The Heat\",\"Description\":\"Increases the heat level by "
      "1\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Turn Down The Heat\",\"Description\":\"Lowers the heat level by "
      "1\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":0,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":\"I "
      "Need Some Help\",\"Description\":\"Adds $250k to the "
      "bank\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Slot Machine\",\"Description\":\"Gives the player a random car with random "
      "tuning\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16,67]},{"
      "\"Name\":\"S T O N K S\",\"Description\":\"Let chat invest a random amount of money and get or lose a random "
      "amount!\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Magneto\",\"Description\":\"Instantly teleports all cars to the "
      "player\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Superhot\",\"Description\":\"Times moves only when you "
      "do\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":30.0,\"IncompatibleWith\":[39,73,92]},{"
      "\"Name\":\"Brakes Just Slow You Down\",\"Description\":\"Where we are going, we don\'t need "
      "brakes\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":90.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Experience The Lag\",\"Description\":\"Randomly locks frames, just as "
      "intended\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":25.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Are You A Minivan Mom?\",\"Description\":\"Mom\'s van just ain\'t build right\\n(Bad "
      "tuning)\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Designated Driver\",\"Description\":\"More like designated to drink Kappa\\n(Random game speed every "
      "second)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":40.0,\"IncompatibleWith\":[35,73,92]}"
      ",{\"Name\":\"Fast And Furious NOS\",\"Description\":\"Too soon "
      "junior\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":1,\"Duration\":40.0,\"IncompatibleWith\":[42]},{"
      "\"Name\":\"How\'s Your Car Running?\",\"Description\":\"Sabotages player\'s "
      "engine\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"GAS GAS GAS\",\"Description\":\"Full throttle with NOS (Braking is "
      "disabled)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":35.0,\"IncompatibleWith\":[40,46]},"
      "{\"Name\":\"Camera Switcheroo\",\"Description\":\"Changes the camera every half a "
      "second\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":25.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Suddenly It\'s A Drag Race\",\"Description\":\"All cars use the drag racing "
      "system\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":true,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[16,101]},{"
      "\"Name\":\"Teasing\",\"Description\":\"Free "
      "earrape\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":5,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Drive Or Die\",\"Description\":\"If you let go off the gas, the engine "
      "blows\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":true,\"Cooldown\":16,\"Duration\":40.0,\"IncompatibleWith\":[11,16,42]},{"
      "\"Name\":\"Look Ma No Hands\",\"Description\":\"No "
      "steering\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":5.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Wide Cars\",\"Description\":\"IT\'S HIM "
      "widepeepoHappy\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[55]"
      "},{\"Name\":\"RC Cars\",\"Description\":\"Re-Volt\'s back baby "
      "R-)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[93]},{"
      "\"Name\":\"Jelly "
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
      "you)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":60.0,\"IncompatibleWith\":[60,68,87]},{"
      "\"Name\":\"Super Seducer\",\"Description\":\"You sure know how to talk to girls.\\n(Pulls everything towards "
      "you)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":4,\"Duration\":60.0,\"IncompatibleWith\":[59,68,87]},{"
      "\"Name\":\"Heavy Cars\",\"Description\":\"2x heavier "
      "cars\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":30.0,\"IncompatibleWith\":[57,58,62,75,"
      "76]},{\"Name\":\"Light Cars\",\"Description\":\"2x lighter "
      "cars\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":30.0,\"IncompatibleWith\":[57,58,61,75,"
      "76]},{\"Name\":\"The PSP Experience\",\"Description\":\"COMPRESS THOSE "
      "PIXELS!\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":30.0,\"IncompatibleWith\":[51]},{"
      "\"Name\":\"Blur Powerups\",\"Description\":\"The true arcade "
      "experience\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Enjoy The Scenery\",\"Description\":\"It sure is lovely this time of the "
      "year\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":13,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Insane Traffic\",\"Description\":\"Years of illegal street racing have made people of Rockport go "
      "insane\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":10,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Crazy Taxi\",\"Description\":\"Need a "
      "cab?\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"Giga Rubberband\",\"Description\":\"He\'s always one step ahead of "
      "you\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":60.0,\"IncompatibleWith\":[59,60,87,103]"
      "},{\"Name\":\"Mega Rubberband\",\"Description\":\"You thought Earl was "
      "hard?\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":40.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Guess Who\'s Back\",\"Description\":\"Cross wants to have a talk with "
      "you\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"You\'re Going The Wrong Way\",\"Description\":\"DO U KNOW DA "
      "WAE??\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Bail Me Out\",\"Description\":\"Evades the current "
      "pursuit\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":2,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Black Out\",\"Description\":\"The New Year\'s stream was crazy, "
      "huh\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":1.0,\"IncompatibleWith\":[35,39]},{"
      "\"Name\":\"RKO\",\"Description\":\"WATCH OUT WATCH OUT WATCH "
      "OUT\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":10.0,\"IncompatibleWith\":[101]},{"
      "\"Name\":\"Light Cops\",\"Description\":\"1kg of Rockport "
      "cotton\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":30.0,\"IncompatibleWith\":[57,58,61,"
      "62,76]},{\"Name\":\"Heavy Cops\",\"Description\":\"1kg of Rockport "
      "steel\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":11,\"Duration\":30.0,\"IncompatibleWith\":[57,58,61,"
      "62,75]},{\"Name\":\"Never Busted\",\"Description\":\"Rockport PD doesn\'t actually want "
      "you\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":12,\"Duration\":30.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Stick Shift Pro\",\"Description\":\"All cars change gears randomly every 2 seconds\\n(Also forced manual "
      "transmission)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":14,\"Duration\":30.0,\"IncompatibleWith\":[]},"
      "{\"Name\":\"Bop It!\",\"Description\":\"The way Bop It was meant to be "
      "played\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":20,\"Duration\":30.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Tunnel Vision\",\"Description\":\"You only need to look forward "
      "anyway\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":12,\"Duration\":45.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Tall Cars\",\"Description\":\"More headroom is always "
      "good\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[86]},{"
      "\"Name\":\"I\'m TIREd\",\"Description\":\"Get it? haHaa\\n(Blows the tires "
      "randomly)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":24,\"Duration\":30.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Maybe Inverted Steering\",\"Description\":\"Inverts steering, but only "
      "sometimes\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":50.0,\"IncompatibleWith\":[23]},{"
      "\"Name\":\"Delivery Boy\",\"Description\":\"Domino\'s needs an extra "
      "hand\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":15,\"Duration\":10.0,\"IncompatibleWith\":[16]},{"
      "\"Name\":\"!elnosabe\",\"Description\":\"PepeLaugh Broadcaster seems to be not acquainted with vital intelligence..\\nPepeLaugh Broadcaster seems to be "
      "not acquainted with vital intelligence..\\nPepeLaugh Broadcaster seems to be not acquainted with vital intelligence..\\n(Increases lap "
      "amount)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":30,\"Duration\":5.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Flat Cars\",\"Description\":\"Cross really did step on you "
      "huh\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[81]},{"
      "\"Name\":\"Convoy Time\",\"Description\":\"Line up boys\\n(Creates a convoy behind the "
      "player)\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":5,\"Duration\":45.0,\"IncompatibleWith\":[59,60,68,"
      "103]},{\"Name\":\"Invisible Cars\",\"Description\":\"I\'m sorry Crock, I\'m afraid I can\'t render that "
      "car\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Time Flies\",\"Description\":\"Hope you\'re having "
      "fun!\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":30.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Truck Rain\",\"Description\":\"Heavy rain "
      "today\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Teleport To Old Bridge\",\"Description\":\"So is the game finished now or "
      "what?\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":16,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"BIG CARS\",\"Description\":\"BIG "
      "CHONGUS\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[49]},{"
      "\"Name\":\"Limo Cars\",\"Description\":\"Hey, I\'d like a 6-inch sub "
      "please\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Flipped Cars\",\"Description\":\"Just like the last time Uncle Crock had his truck "
      "towed\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":3,\"Duration\":60.0,\"IncompatibleWith\":[19]},{"
      "\"Name\":\"Pepega Truck\",\"Description\":\"Did you think he forgot about "
      "you?\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Teleport To Random Car\",\"Description\":\"What\'s he doing over "
      "there?\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Teleport To Random Cop\",\"Description\":\"It\'s important to visit your "
      "elderlies\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Teleport To Random Racer\",\"Description\":\"Remember: they are what you are racing "
      "against\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Pop All Tires\",\"Description\":\"Instantly pops all the tires in the "
      "game\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{\"Name\":"
      "\"Pop A Random Tire\",\"Description\":\"Pops a random tire of the "
      "player\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Spin To Win\",\"Description\":\"Makes all cars spin around "
      "borpaSpin\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":15.0,\"IncompatibleWith\":[13,14,"
      "44]},{\"Name\":\"Get Back Here\",\"Description\":\"Pulls the player car "
      "backwards\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Blind\",\"Description\":\"I can\'t see "
      "anything\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":5.0,\"IncompatibleWith\":[73]},{"
      "\"Name\":\"Graviton\",\"Description\":\"Everything flings towards you every other "
      "second\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":9,\"Duration\":60.0,\"IncompatibleWith\":[68,87]},{"
      "\"Name\":\"Random Boxes\",\"Description\":\"Blocks parts of the screen "
      "randomly\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":45.0,\"IncompatibleWith\":[]},{"
      "\"Name\":\"Bouncy Castle\",\"Description\":\"Inflatable Rockport City "
      "gameplay\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":6,\"Duration\":60.0,\"IncompatibleWith\":[3]},{"
      "\"Name\":\"GoPro FOV\",\"Description\":\"It\'s just like in the "
      "commercials\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[108]},"
      "{\"Name\":\"4:3 Stretched\",\"Description\":\"Time to go start a pro CS:GO "
      "career\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[107]},{"
      "\"Name\":\"A Good Sense Of Speed\",\"Description\":\"Finally, a good racing "
      "game\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[111]},{"
      "\"Name\":\"The Upside Down\",\"Description\":\"Stranger Things getting even "
      "stranger\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[111]},{"
      "\"Name\":\"Warp Drive\",\"Description\":\"Kerbal \'Speed\' "
      "Program\",\"IsEnabled\":true,\"IsStatusEffect\":false,\"NeedsActivationWarning\":false,\"Cooldown\":7,\"Duration\":60.0,\"IncompatibleWith\":[109,110]},"
      "{\"Name\":\"Pimp My Ride\",\"Description\":\"You\'ve officially been "
      "pimped\",\"IsEnabled\":true,\"IsStatusEffect\":true,\"NeedsActivationWarning\":false,\"Cooldown\":8,\"Duration\":10.0,\"IncompatibleWith\":[]}]}"
      "}";
}
