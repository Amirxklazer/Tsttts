// story_core.hpp - shared scripts: doors, objects. See README.txt for the script commands.
#pragma once
static const char* STORY_CORE = R"IL(
# ---------------------------------------------------------------- doors
script door_SECRET
ifnot secret_open closed
say |The Stairway to Hell. It leads outside, to the parking lot.
choose
> Go outside => go
> Not now => end
label go
fx fadeout
wait 30
warp out1 260
fx fadein
toast Outside parking
end
label closed
say |Just a dark panel in the wall next to Dalia's room. Probably nothing.


# ---------------------------------------------------------------- objects
script use_backdoor
say |Back inside through the Stairway to Hell door?
choose
> Go back inside => go
> Stay outside => end
label go
fx fadeout
wait 30
warp main 1100
fx fadein
toast Main floor

script use_reception
say |The reception desk. A bell, a pile of mail for the Îlot14 residents, and a sticky note that says "BE NICE TO THE BOTS".

script use_panel
say |The elevator control panel. Rows of green lights. One of them is blinking like it wants to tell me something.

script use_shaftgap
say |The elevator shaft opening. Wind, dust, and a long way down. I step back.

script use_fan
say |A huge ventilation fan. It hums a note I can almost sing along with.

script use_vending
say |The vending machine. It sells snacks, drinks, and one almond water that has clearly been there since the Stone Age.

script use_edge
say |The edge of the roof. The whole of Reghaia is down there. I step back, because I'm not an idiot.

script use_tank
say |The water tank. Someone drew a tiny 14 on it with a marker. I know who. I won't say.

script use_car1
say |A parked car. Dusty. Somebody wrote "wash me" on the window and somebody else wrote "no".

script use_car2
say |Another parked car. A Cleaning bot sticker on the bumper says "I stop for dust".
)IL";
