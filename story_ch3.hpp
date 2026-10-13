// story_ch3.hpp - CHAPTER 3: LOWEST POINT, days 1-10 (Act 1: Level 18). Chapter 3 unlocks after Chapter 2 day 35.
#pragma once
static const char* STORY_CH3 = R"IL(
# ================================================================ CH3 DAY 1
script c3_1
title Down We Go
card CHAPTER 3|Lowest Point
bars on
scene inn amir dalia gabriel aya_n
cast amir 520
cast dalia 760
cast gabriel 960
cast aya_n 1160
say |A week after the concert. The Inn is quiet again. Everyone is packing for a trip nobody wants to name.
say Aya@aya_n|Provisions. Water. Almond water, because Prime insists. Four flashlights. One very small cake.
say Dalia|The cake is for emergencies.
say Gabriel|Cake isn't an emergency item.
say Dalia|Everything is an emergency item if you try hard enough.
anim dalia hop
say Aya@aya_n|Amir. The silver key. Do you have it?
say |It's in my pocket. It hums softly against my leg, as if it's counting down.
bars off
scene off
warp inn 900
npc dalia inn 1050
npc gabriel inn 1150
npc aya_n inn 1000
npc prime inn 1350
goal Take the elevator and press the button marked 18. First talk to Prime in the lobby.
await talk prime
say Prime|THE LIFT IS READY. THE BUTTON IS GREEN. MY BATTERIES ARE FULL. I HAVE PACKED A DUSTPAN.
say Prime|I HAVE PACKED TWO DUSTPANS. ONE FOR EMERGENCIES.
choose
> Is it going to be safe? => safe
> Let's go. => go
label safe
say Prime|NO. BUT WE WILL BE TOGETHER. IT IS THE SAME THING, MOSTLY.
label go
say Aya@aya_n|Come back. All of you. I'm keeping your rooms warm.
say Amir|We will.
goal Walk to the elevator and press 18.
await floor lvl18
bars on
scene elev amir dalia gabriel prime
fx shake
say |The lift groans like an old animal. The Inn's number slides past. Then a door I've never seen. Then a long dark stretch of numbers going backwards.
anim dalia hop
say Dalia|If this thing falls, I'm blaming Gabriel.
say Gabriel|Why me?
say Dalia|You brought the rope. Ropes are a bad sign.
fx shake
say |The display flickers and shows a symbol I can't read. Then it settles. "18".
fx fadeout
wait 40
bars off
scene off
warp lvl18 220
npc dalia lvl18 330
npc gabriel lvl18 420
npc prime lvl18 520
fx fadein
toast Level 18
say |Level 18. Dark teal walls, orange lights, pipes that hum a note I almost recognize. This isn't the Backrooms. This is somewhere the building keeps for itself.
say Amir|Stay close.
# VIGNETTE
bars on
scene room amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Someone left a snack on the stairs. A tiny miracle.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini whack 10
bars on
scene lobby amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |Someone left a snack on the stairs. A tiny miracle.
say Adam|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
bars on
scene outside amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The building hums. Somebody laughs two floors away.
say Prime|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
endday

# ================================================================ CH3 DAY 2
script c3_2
title Level 18
bars on
scene deep amir dalia gabriel
cast amir 600
cast dalia 800
cast gabriel 1000
say |Day 2 on Level 18. Time doesn't work the same here. Hunger does, though.
emote gabriel ...
say Gabriel|My watch says it's Tuesday. It also says it's Thursday.
say Dalia|Both could be true.
bars off
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
mini timing 6 4 Power_the_door 2
ifnot skipped powered
say |(The slots took pity on you and lit up on their own.)
label powered
fx shake
say |The door rumbles open. Behind it, something is running toward us. A flood of small, grey, dusty shapes. Dust wraiths. Hundreds of them.
mini fight 14 6 dust_wraiths
say Dalia|That was NOT in the brochure.
say Gabriel|There's no brochure.
say |Beyond the door, a faint orange glow. A campfire's worth of light, somewhere far ahead.
set l18_door 1
# VIGNETTE
bars on
scene inn amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |Someone left a snack on the stairs. A tiny miracle.
say Prime|Got a minute? Quick game.
bars off
scene off
mini whack 12
bars on
scene room amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The building hums. Somebody laughs two floors away.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini whack 10
bars on
scene lobby amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |A door opens by itself, then politely closes.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday

# ================================================================ CH3 DAY 3
script c3_3
title The Waystation
bars on
scene deep amir dalia gabriel prime
say |Day 3. We follow the orange glow down a long corridor. The pipes hum louder. Under the hum, a thin melody, like someone whistling a lullaby through their teeth.
say Prime|THERE IS A STRUCTURE AHEAD. IT IS... TIDY.
emote prime !
say Dalia|Tidy? Down here?
bars off
scene off
warp camp 300
npc dalia camp 420
npc gabriel camp 500
npc prime camp 600
clearitems
goal Walk into the camp. Pick up the 4 supplies left on the ground.
spawn supply camp 700
spawn supply camp 1100
spawn supply camp 1500
spawn supply camp 1900
await items 4
say |A small camp. A ring of stones. A kettle still warm. A row of neatly stacked crates labelled "FOR WHOEVER COMES NEXT".
say Gabriel|It's been used. Recently.
say Dalia|By who?
say |On the biggest crate, a note in handwriting that looks like mine: "Welcome. This is the Waystation. The kettle is hot. Don't trust the east corridor."
say Amir|...The kettle is hot.
say Gabriel|I hate this.
say Prime|I LIKE IT. IT IS VERY ORGANIZED.
mini catch 10 3 supplies 3
ifnot skipped caught
say |(Prime sorted the last crates into neat towers. They were not asked to.)
label caught
fx flash
say |Prime plants a tiny flag on the camp's central crate. "WAYSTATION: CLEANED BY PRIME". It's a charming, tilted flag.
say Dalia|We have a base.
say Amir|We have a base.
set camp_found 1
clearitems
# VIGNETTE
bars on
scene outside amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The lamp flickers once. A hello.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini lights 3
bars on
scene inn amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |The lamp flickers once. A hello.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini whack 12
bars on
scene room amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The building hums. Somebody laughs two floors away.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 10
bars on
scene lobby amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The lamp flickers once. A hello.
say Prime|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday

# ================================================================ CH3 DAY 4
script c3_4
title The Pipe Maze
bars on
scene deep amir kenzy
say |Day 4. Haydar joined us overnight via the old service lift. He's carrying a bag of wires, a map, and a face that says "I regret nothing".
say Haydar|Prime picked up a sound from the east. A rhythm. I mapped it. It's coming from the pipes, in a pattern.
say Amir|Pipes don't make patterns.
say Haydar|These ones do.
bars off
scene off
warp camp 600
npc kenzy camp 900
goal Talk to Haydar at the camp's map table.
await talk kenzy
say Haydar|The east corridor is a maze of old pipes. A hum drains your stamina. Grab bottled water and reach the green exit light.
say Haydar|I'd go with you, but my bag is heavy and I've made some questionable decisions.
mini maze 4 7
ifnot skipped through
say |(The pipes spat you out. A little bruised, a little dusty, a little offended.)
label through
say |You come out on the far side with four cool bottles and a dent in your elbow. The corridor behind you slides shut with a click.
say Haydar|And?
say Amir|It was a maze.
say Haydar|I KNEW IT. Put it on the map.
set pipes_done 1
# VIGNETTE
bars on
scene lobby amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |Someone left a snack on the stairs. A tiny miracle.
say Adam|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene outside amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |Someone left a snack on the stairs. A tiny miracle.
say Prime|Got a minute? Quick game.
bars off
scene off
mini lights 3
bars on
scene inn amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |A door opens by itself, then politely closes.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini whack 12
endday

# ================================================================ CH3 DAY 5
script c3_5
title The Furnace Door
bars on
scene deep amir dalia gabriel
say |Day 5. The east corridor ends in a round iron door the color of a dying ember. Heat rolls off it in waves. A sign: "FURNACE. DO NOT ENTER. WE MEAN IT. - THE MANAGEMENT".
say Dalia|Who's the management?
say Gabriel|Whoever wrote the sign. Which doesn't make me feel better.
say Amir|We have to go in.
say Gabriel|I'm aware.
bars off
scene off
warp furnace 300
npc dalia furnace 420
npc gabriel furnace 520
goal Cross the Furnace. Dodge the jets of flame.
mini dodge 24 4 2
ifnot skipped crossed
say |(A bot-shaped shadow tugged you out of a flame jet. You never saw it.)
label crossed
say |On the far side, a long ledge. Below it, an ocean of orange light, like the inside of a sleeping sun.
say Gabriel|That's the heart of the building, isn't it.
say Amir|I think it's the heart of something.
say Dalia|I don't like it. I want to hug it.
set furnace_seen 1
# VIGNETTE
bars on
scene room amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The lamp flickers once. A hello.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
bars on
scene lobby amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Someone left a snack on the stairs. A tiny miracle.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene outside amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Something small happens, and it matters more than it should.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini lights 3
endday

# ================================================================ CH3 DAY 6
script c3_6
title Wraith Hunters
bars on
scene deep amir prime dalia
say |Day 6. The camp is under attack. A low, grey wave of dust wraiths is climbing over the crates, drawn to the warm kettle.
say Prime|DUST DETECTED. A GREAT DEAL OF DUST. I TAKE PERSONAL OFFENSE.
emote prime !
say Dalia|We need a line! A lane! A... lane line!
fx shake
bars off
scene off
warp camp 800
npc prime camp 1000
npc dalia camp 700
goal Defend the Waystation!
mini defend 4 5 2
ifnot skipped held
say |(The bots rolled into the front lines. A few hats were lost in the fighting.)
label held
say |The last wraith pops. Grey drifts settle across the camp like tired snow.
say Dalia|Okay. Okay. We can do this.
say Prime|WE CAN. THE KETTLE IS STILL WARM.
set camp_held 1
# VIGNETTE
bars on
scene inn amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |The building hums. Somebody laughs two floors away.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
bars on
scene room amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The lamp flickers once. A hello.
say Adam|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
bars on
scene lobby amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The lamp flickers once. A hello.
say Prime|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene outside amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |A door opens by itself, then politely closes.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini lights 3
endday

# ================================================================ CH3 DAY 7
script c3_7
title Flooded Hall
bars on
scene deep amir gabriel bolt
say |Day 7. A corridor full of ankle-deep water. Ripples in a regular rhythm. Floating in the water, a fleet of little paper boats, each labelled with a name.
say Gabriel|Cute. Terrifying.
say Bolt|Beep! The water is cold! I love it!
emote bolt !
bars off
scene off
warp flood 300
npc gabriel flood 420
clearitems
goal Collect 3 paper boats floating in the Flooded Hall.
spawn boat flood 800
spawn boat flood 1500
spawn boat flood 2200
await items 3
say |Each boat has a name written in blue ink. Dalia. Gabriel. Amir. In the same handwriting as the camp note.
say Gabriel|It's mine. It says "bring the rope".
say Amir|Whoever's writing these knows us. Better than we know ourselves.
say |At the end of the hall, a flood gate. Behind it, a clatter. A dozen flooded Cleaning bots are floating in circles, stuck in an eddy.
mini roundup 8 45 3
ifnot skipped saved
say |(The eddy slowed down by itself. The bots drifted gently into Bolt's arms.)
label saved
say Bolt|They're SAFE! I have FRIENDS! SO MANY FRIENDS!
say Gabriel|They're strangers.
say Bolt|Friends I haven't met yet!
set flood_done 1
clearitems
# VIGNETTE
bars on
scene outside amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |Something small happens, and it matters more than it should.
say Prime|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |A door opens by itself, then politely closes.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
bars on
scene room amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Something small happens, and it matters more than it should.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
endday

# ================================================================ CH3 DAY 8
script c3_8
title Sofia's Echo
bars on
scene deep amir sofia
say |Day 8. Sofia came down in the middle of the night. Barefoot. She says the whole level is singing.
say Sofia|Everything here has a pitch. The pipes. The water. The walls. Even the dust.
say Amir|What's it singing?
say Sofia|A name.
bars off
scene off
warp camp 900
npc sofia camp 1200
goal Talk to Sofia at the campfire.
await talk sofia
say Sofia|The notes come in a sequence. If I play them back, the level answers. Watch. Then repeat.
mini simon 8 3 22
ifnot skipped played
say |(Sofia sang the rest. The walls answered.)
label played
fx flicker
say |A low note rings through the camp. From a crack in the wall, a faded brass nameplate slides out and clinks on the floor. Dalia picks it up.
say Dalia|"M-002 - DALIA". It's mine.
say Sofia|It's a key to something.
say Amir|Doors. There are doors.
set first_plate 1
# VIGNETTE
bars on
scene lobby amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The building hums. Somebody laughs two floors away.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
bars on
scene outside amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |The building hums. Somebody laughs two floors away.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |Something small happens, and it matters more than it should.
say Adam|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
endday

# ================================================================ CH3 DAY 9
script c3_9
title Static
bars on
scene deep amir kenzy prime
say |Day 9. Haydar's radio has been picking up a new signal. A voice, almost words. A rhythm, definitely music.
say Haydar|It's speaking. In a code I don't know. Prime, did you hear that?
say Prime|I HEARD A SEQUENCE. IT WAS IN FOUR PARTS. UP. RIGHT. DOWN. LEFT. IT SOUNDED... LONELY.
bars off
scene off
warp camp 1000
npc kenzy camp 1300
goal Talk to Haydar at the radio.
await talk kenzy
say Haydar|Match the signal. Each beat, a button. If you get it right, the radio tunes itself.
mini rhythm 30 5 120
ifnot skipped tuned
say |(The radio tuned itself. It was more sophisticated than it looked.)
label tuned
fx flicker
say |The static clears. A voice. Raspy, young, familiar. Not quite my voice. Not quite not.
say ???|"...If you're hearing this, you passed the furnace. Good. I'm sorry about the heat."
say ???|"The Archive is south of the Waystation. Everything you need is behind the doors. Don't go alone."
say Amir|That's me.
say Haydar|That is a very good impression of you.
say Amir|It isn't an impression.
set radio3 1
# VIGNETTE
bars on
scene room amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The building hums. Somebody laughs two floors away.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 10
bars on
scene lobby amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The building hums. Somebody laughs two floors away.
say Prime|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
bars on
scene outside amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |A door opens by itself, then politely closes.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The lamp flickers once. A hello.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
endday

# ================================================================ CH3 DAY 10
script c3_10
title Night at the Waystation
bars on
scene deep amir dalia gabriel prime
say |Day 10. Night. The camp fire is low. Dalia's wrapped in three blankets. Gabriel's sitting just outside the circle of light, watching the dark.
say Dalia|I can't sleep. Down here, even the quiet is loud.
say Gabriel|I'll keep watch.
say Amir|You always do.
say Gabriel|Someone has to.
bars off
scene off
warp camp 1000
npc dalia camp 1100
npc gabriel camp 1300
goal Talk to Dalia by the campfire.
await talk dalia
say Dalia|Can I tell you something dumb?
choose
> Always. => always
> Is it a joke? => joke
label joke
say Dalia|No. It's the opposite of a joke.
goto go
label always
say Dalia|Okay. Okay.
label go
say Dalia|I'm scared. I'm not scared of the dark. I'm scared that we get to the end of this and it turns out we were the dust.
say Amir|We're not the dust.
say Dalia|I know. But what if the building thinks we are.
choose
> The building loves us. => love
> Then we show it we're not. => show
label love
say Dalia|That's a very Amir thing to say. I'm keeping it.
goto go2
label show
say Dalia|That's a very Gabriel thing to say. I'm also keeping it.
label go2
say |A tiny sound from the dark. A slow, soft scraping. Something is on the ledge above the camp.
fx flicker
say Gabriel|Quiet. Everyone.
mini sneak 4 3 2
ifnot skipped passed
say |(Gabriel whispered "go" and you went. Somehow nobody woke the thing.)
label passed
say |Above the camp, a shape on the ledge. Not a wraith. A tall, thin silhouette against the orange glow. It watches. It raises one hand. Then it's gone.
say Amir|That wasn't a wraith.
say Gabriel|No. It wasn't.
set saw_shape 1
# VIGNETTE
bars on
scene inn amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The lamp flickers once. A hello.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini whack 12
bars on
scene room amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The building hums. Somebody laughs two floors away.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini whack 10
bars on
scene lobby amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Someone left a snack on the stairs. A tiny miracle.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday
)IL";
