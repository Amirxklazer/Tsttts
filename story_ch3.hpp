// story_ch3.hpp - CHAPTER 3: LOWEST POINT (unlocks after Day 31). Three short days: c3_1, c3_2, c3_3.
#pragma once
static const char* STORY_CH3 = R"IL(
# ================================================================ CHAPTER 3 - DAY 1
script c3_1
title Down We Go
card CHAPTER 3|Lowest Point
bars on
scene room amir
cast amir 860
cast bolt -200
say |A week after Îlot14 Day. The banner is still on the roof. The bots are still wearing party hats. And the knocking is back.
walk bolt 470 7 wait
emote bolt !
say Bolt|ZOOM! It's coming from BELOW! Way below! Below the below!
say Amir|Below Parking 2.
say Bolt|Below EVERYTHING!
anim amir shake
say |Three knocks. A pause. Three more. This time it's not asking. It's counting down.
bars off
scene off
goal Take the elevator down to Parking 2. Dalia and Gabriel are waiting at the grey door.
npc dalia park2 1750
npc gabriel park2 1650
await floor park2
say Dalia|You heard it too. Of course you did.
say Gabriel|Prime said something yesterday. Through the old speaker. Three words.
choose
> What did he say? => what
> Let's just go. => go
label what
say Gabriel|"Level eighteen. Lowest."
say Dalia|Lowest point.
label go
goal Open the grey door at the east end of Parking 2.
obj greydoor park2 1900 Grey door
await use greydoor
fx fadeout
wait 40
warp cradle 220
npc dalia cradle 330
npc gabriel cradle 420
ifnot prime_free noprime
npc prime cradle 640
label noprime
fx fadein
toast Service Corridor 0
say |The Backrooms don't hum here anymore. Prime fixed the wallpaper. One wall at a time. The carpet even smells like carpet now.
obj lift cradle 1500 Old service lift
goal Walk to the old service lift at the end of the corridor and use it.
await use lift
bars on
scene elev amir dalia gabriel
fx shake
say |The lift is older than the building. Maybe older than the idea of the building. It groans as the doors close.
anim dalia hop
say Dalia|If this thing falls, I'm blaming Gabriel.
say Gabriel|Why me?
say Dalia|You brought the rope. Ropes are a bad sign.
fx shake
say |The numbers above the door go backwards. 17. 18. Then the display flickers and shows a symbol I can't read.
fx fadeout
wait 40
bars off
scene off
warp lvl18 220
npc dalia lvl18 330
npc gabriel lvl18 420
ifnot prime_free noprime2
npc prime lvl18 520
label noprime2
fx fadein
toast Level 18
say |Level 18. Dark teal walls, orange lights, pipes that hum a note I almost recognize. This isn't the Backrooms. This is somewhere the building keeps for itself.
say Amir|Stay close.
endday

# ================================================================ CHAPTER 3 - DAY 2
script c3_2
title Level 18
scene deep amir dalia gabriel
say |Day 2 on Level 18. Time doesn't work the same here. Hunger does, though.
scene off
warp lvl18 220
npc dalia lvl18 330
npc gabriel lvl18 420
clearitems
spawn fuse lvl18 600
spawn fuse lvl18 1300
spawn fuse lvl18 2000
goal Find 3 fuses in the pipes of Level 18. Walk over them.
await items 3
say Gabriel|Three fuses. The big door at the end needs them.
obj bigdoor lvl18 2500 Sealed door
goal Walk to the sealed door at the east end of Level 18 and use it.
await use bigdoor
say |Three fuse slots, each blinking amber. Each slot needs a perfectly timed push.
mini timing 6 4 Power_the_door
ifnot skipped powered
say |(The slots took pity on you and lit up on their own.)
label powered
fx shake
say |The door rumbles open. Behind it, something is running toward us. A flood of small, grey, dusty shapes. Dust wraiths. Hundreds of them.
mini fight 14 6 dust_wraiths
say Dalia|That was NOT in the brochure.
say Gabriel|There's no brochure.
say |Beyond the door, a long hall leads to a round chamber. In its center, a tall door of black glass. A faint orange light spills around its edges.
set l18_door 1
endday

# ================================================================ CHAPTER 3 - DAY 3
script c3_3
title The Door With a Name
scene deep amir dalia gabriel
say |Day 3. The black door. Ash drifts across the floor of the round chamber like slow snow, though there's no wind.
scene off
warp lvl18 2500
npc dalia lvl18 2400
npc gabriel lvl18 2350
obj blackdoor lvl18 2750 Black glass door
goal Examine the black glass door.
await use blackdoor
bars on
scene deep amir dalia gabriel
say |A nameplate on the door. Brass. Polished. Someone has been taking care of it. It reads:
fx flicker
say |"L-001 - AMIR."
emote amir !!
say Dalia|That's... your room number.
say Gabriel|That's your name.
say Amir|I live on the Lethal floor. I know where my door is.
say |The ash lifts off the floor and swirls around the nameplate. Behind the glass, a shape stands very still. It has my silhouette.
choose
> Open it. => open
> Not yet. We need a plan. => wait
label wait
say Gabriel|That's the first smart thing anyone's said today.
say Dalia|But we're going to open it eventually, aren't we.
say Amir|...Eventually.
goto fin
label open
set opened_door 1
say Amir|If it has my name on it, it's mine to open.
say |The glass doesn't break. It simply isn't there anymore. A cold wind of ash blows past us, and the shape steps forward.
label fin
fx flash
card TO BE CONTINUED|Chapter 3 of the Lost of Ashes story.
bars off
scene off
endday
)IL";
