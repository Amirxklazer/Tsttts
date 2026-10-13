#pragma once
static const char* STORY_CH3D = R"IL(
# ================================================================ CH3 DAY 31
script c3_31
title Under the Floor
bars on
scene deep amir dalia gabriel
say |Day 31. A trapdoor under the throne. Inside, a long ladder. Warm air, the smell of old paper and ozone.
bars off
scene off
warp ulobby 200
npc dalia ulobby 300
npc gabriel ulobby 350
obj trapdoor ulobby 1900 Trapdoor
goal Climb down the trapdoor.
await use trapdoor
mini maze 4 7
ifnot skipped ok31
say |(The building pitied you and finished it for you.)
label ok31
say |At the bottom, the building's heartbeat. A huge machine of brass and glass, ticking like a clock the size of a house.
say Dalia|That's the elevator's heart.
say Gabriel|That's the building's heart.
set heart 1
# VIGNETTE
bars on
scene outside amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Someone left a snack on the stairs. A tiny miracle.
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
bars on
scene room amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The building hums. Somebody laughs two floors away.
say Prime|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
bars on
scene lobby amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The building hums. Somebody laughs two floors away.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene outside amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The building hums. Somebody laughs two floors away.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini lights 3
endday

# ================================================================ CH3 DAY 32
script c3_32
title Gears
bars on
scene deep amir kenzy gabriel
say |Day 32. The heart is out of sync. Gears grind. A pressure gauge twitches in the red.
bars off
scene off
warp ulobby 200
npc kenzy ulobby 800
goal Talk to Haydar at the control cage.
await talk kenzy
mini timing 9 3 Tune_the_gears 4
ifnot skipped ok32
say |(The building pitied you and finished it for you.)
label ok32
say |The gears lock into rhythm. The floor stops shaking. Somewhere above us, a hundred doors close softly at the same time.
say Haydar|Everything is a clock if you listen to it long enough.
set gears 1
# VIGNETTE
bars on
scene lobby amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |A door opens by itself, then politely closes.
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
say |Something small happens, and it matters more than it should.
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
say |The building hums. Somebody laughs two floors away.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
bars on
scene room amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Something small happens, and it matters more than it should.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
bars on
scene lobby amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The lamp flickers once. A hello.
say Adam|Got a minute? Quick game.
bars off
scene off
mini lights 4
endday

# ================================================================ CH3 DAY 33
script c3_33
title The Lamp Run
bars on
scene deep amir dalia gabriel bolt
say |Day 33. The heart needs light. Dozens of emergency lamps have gone out across Level 18, and Bolt has the map.
bars off
scene off
warp shaft 250
npc bolt shaft 350
clearitems
spawn lamp shaft 500
spawn lamp shaft 900
spawn lamp shaft 1300
spawn lamp shaft 1800
spawn lamp shaft 2300
spawn lamp shaft 2800
goal Relight 6 lamps along Level 18.
await items 6
clearitems
mini dodge 30 4 4
ifnot skipped ok33
say |(The building pitied you and finished it for you.)
label ok33
say |The last lamp catches. All the way down the pipes, orange light spreads like warm honey.
say Bolt|BEEP! I LIT THE WHOLE BUILDING!
say Dalia|You lit five lamps.
say Bolt|And I SUPERVISED the rest!
set lamps 1
# VIGNETTE
bars on
scene room amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Someone left a snack on the stairs. A tiny miracle.
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
say |Something small happens, and it matters more than it should.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
bars on
scene outside amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |Something small happens, and it matters more than it should.
say Adam|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The building hums. Somebody laughs two floors away.
say Prime|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
bars on
scene room amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Someone left a snack on the stairs. A tiny miracle.
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
say |A door opens by itself, then politely closes.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini lights 4
endday

# ================================================================ CH3 DAY 34
script c3_34
title Everyone Comes Down
bars on
scene deep amir dalia gabriel prime
say |Day 34. A line of familiar faces walks out of the grey door in Parking 2. Amine with snacks. Aya with a lamp. Youcef pulling a cart of batteries. They heard the knocking too.
bars off
scene off
warp bots 300
npc dalia bots 450
npc gabriel bots 520
goal Talk to Dalia.
await talk dalia
mini defend 5 6 3
ifnot skipped ok34
say |(The building pitied you and finished it for you.)
label ok34
say |The camp is crowded. Loud. Warm. A fiddle tune from somewhere. For the first time, Level 18 feels like a place with people in it.
say Dalia|They came!
say Amir|They came.
set everyone 1
# VIGNETTE
bars on
scene inn amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The lamp flickers once. A hello.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 12
bars on
scene room amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The lamp flickers once. A hello.
say Prime|Got a minute? Quick game.
bars off
scene off
mini whack 10
bars on
scene lobby amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The building hums. Somebody laughs two floors away.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
bars on
scene outside amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Something small happens, and it matters more than it should.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Something small happens, and it matters more than it should.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
endday

# ================================================================ CH3 DAY 35
script c3_35
title Final Plans
bars on
scene deep amir dalia gabriel kenzy prime
say |Day 35. Haydar spreads a map across the table. A circle in the middle of the heart. A line from there to every door.
bars off
scene off
warp bots 300
npc kenzy bots 600
npc prime bots 700
goal Talk to Haydar.
await talk kenzy
mini simon 10 3 20
ifnot skipped ok35
say |(The building pitied you and finished it for you.)
label ok35
say |The map folds itself. Every line leads back to one place: the Echo Room.
say Haydar|One last door. One last question.
say Gabriel|Which is?
say Amir|Whether I stay.
set plan 1
# VIGNETTE
bars on
scene outside amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The building hums. Somebody laughs two floors away.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini lights 3
bars on
scene inn amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |A door opens by itself, then politely closes.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini whack 12
bars on
scene room amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |The lamp flickers once. A hello.
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
say |The building hums. Somebody laughs two floors away.
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
say |The lamp flickers once. A hello.
say Prime|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
endday

# ================================================================ CH3 DAY 36
script c3_36
title The Hours Before
bars on
scene deep amir dalia
say |Day 36. A quiet day. Dalia fixes my hoodie sleeve. Gabriel sharpens a rope. Prime is polishing the kettle.
bars off
scene off
warp bots 300
npc dalia bots 450
goal Talk to Dalia.
await talk dalia
mini rhythm 40 4 140
ifnot skipped ok36
say |(The building pitied you and finished it for you.)
label ok36
say |Somebody started singing. Then everybody. The whole camp, swaying a little, a half-beat late. The echo of it comes back from the walls and joins in.
say Dalia|Stay with us.
say Amir|I'm not going anywhere.
say Dalia|That's what worries me.
set hours 1
# VIGNETTE
bars on
scene lobby amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |Something small happens, and it matters more than it should.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene outside amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |Someone left a snack on the stairs. A tiny miracle.
say Adam|Got a minute? Quick game.
bars off
scene off
mini lights 3
bars on
scene inn amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |A door opens by itself, then politely closes.
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
say |The lamp flickers once. A hello.
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
say |A door opens by itself, then politely closes.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
endday

# ================================================================ CH3 DAY 37
script c3_37
title Door of Doors
bars on
scene deep amir dalia gabriel prime
say |Day 37. The Echo Room. The ten Amirs stand in a line, each holding a lit lamp.
bars off
scene off
warp ctrl 200
npc dalia ctrl 300
npc gabriel ctrl 350
npc prime ctrl 400
obj finaldoor ctrl 1700 The last door
goal Walk to the last door.
await use finaldoor
mini sneak 6 3 4
ifnot skipped ok37
say |(The building pitied you and finished it for you.)
label ok37
say |The door isn't locked. It's waiting.
say Echo|Whoever goes through it has to decide.
say Amir|Decide what?
say Echo|Whether to be the one who stays, or the one who leaves.
set lastdoor 1
# VIGNETTE
bars on
scene room amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |A door opens by itself, then politely closes.
say Prime|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
bars on
scene lobby amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The lamp flickers once. A hello.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene outside amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Someone left a snack on the stairs. A tiny miracle.
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
say |A door opens by itself, then politely closes.
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
say |Something small happens, and it matters more than it should.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 10
endday

# ================================================================ CH3 DAY 38
script c3_38
title The Shade
bars on
scene deep amir dalia gabriel prime
say |Day 38. Through the door: a long white corridor. At the end, a figure that is not an echo, not a bot, not a man. A hole in the shape of Amir, with the ash of every day I've lived swirling inside.
say Shade|I'm what's left over. Every choice you didn't make. Every door you didn't open.
bars off
scene off
warp ctrl 200
npc prime ctrl 350
npc dalia ctrl 250
npc gabriel ctrl 300
goal Talk to Prime.
await talk prime
mini fight 22 7 boss_Shade
ifnot skipped ok38
say |(The building pitied you and finished it for you.)
label ok38
say |The Shade folds in on itself. Not defeated. Heard.
say Shade|I only wanted to be asked.
say Amir|Stay with us.
say Shade|...Okay.
set shade 1
# VIGNETTE
bars on
scene inn amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The building hums. Somebody laughs two floors away.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
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
mini quiz 4 ilot14
bars on
scene lobby amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The lamp flickers once. A hello.
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
say |The building hums. Somebody laughs two floors away.
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

# ================================================================ CH3 DAY 39
script c3_39
title Going Up
bars on
scene deep amir dalia gabriel prime
say |Day 39. The heart restarts. The long lift, the one older than the building, hums back to life. We load everything. Bots, friends, ten Amirs, one piano. Somehow.
bars off
scene off
warp shaft 250
npc dalia shaft 350
npc gabriel shaft 400
npc prime shaft 450
obj biglift shaft 2600 Old lift
goal Walk to the old lift and go up.
await use biglift
mini dodge 34 4 5
ifnot skipped ok39
say |(The building pitied you and finished it for you.)
label ok39
say |The numbers over the door count up. 17. 16. 15. All the way to the Roof.
say Dalia|We're going home.
say Amir|We're going up.
set going_up 1
# VIGNETTE
bars on
scene outside amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The lamp flickers once. A hello.
say Adam|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |A door opens by itself, then politely closes.
say Prime|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
bars on
scene room amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Someone left a snack on the stairs. A tiny miracle.
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
say |Something small happens, and it matters more than it should.
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
say |The building hums. Somebody laughs two floors away.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini lights 3
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
mini whack 12
endday

# ================================================================ CH3 DAY 40
script c3_40
title The One Who Stays
bars on
scene deep amir dalia gabriel prime
say |Day 40. The Roof. Sunrise. Every resident, every bot, every echo. A banner reads "LOST OF ASHES - WELCOME BACK."
bars off
scene off
warp roof 300
npc dalia roof 450
npc gabriel roof 520
npc prime roof 600
goal Talk to Dalia.
await talk dalia
mini rhythm 48 4 150
ifnot skipped ok40
say |(The building pitied you and finished it for you.)
label ok40
say |The final chord rings out. The ash lifts off the roof in a slow, golden spiral.
say Dalia|So. Do you stay?
say Amir|I stay. If you'll have me.
say Dalia|Obviously.
set stays 1
# VIGNETTE
bars on
scene lobby amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Someone left a snack on the stairs. A tiny miracle.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
bars on
scene outside amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Something small happens, and it matters more than it should.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini pairs 4 6
bars on
scene inn amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |A door opens by itself, then politely closes.
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
say |A door opens by itself, then politely closes.
say Prime|Got a minute? Quick game.
bars off
scene off
mini lights 4
endday

)IL";
