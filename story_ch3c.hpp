#pragma once
static const char* STORY_CH3C = R"IL(
# ================================================================ CH3 DAY 21
script c3_21
title The Echo Room
bars on
scene room amir dalia gabriel
say |Day 21. The Echo Room. A round white space where every sound comes back a heartbeat late. Dalia says "hello" and the room says "hello" and then "help."
bars off
scene off
warp echo 200
npc dalia echo 300
npc gabriel echo 400
goal Talk to Dalia.
await talk dalia
mini simon 9 3 22
ifnot skipped ok21
say |(The building pitied you and finished it for you.)
label ok21
say |The echoes line up. Eleven of them. Ten of them step out of the walls, each wearing my face and a different hoodie.
say Amir|Ten of me. Great.
say Gabriel|Which one is the real one?
say Amir|All of them. None of them. Pick one.
set echoes 1
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
mini quiz 4 ilot14
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
mini lights 4
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
mini lights 3
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
say |The lamp flickers once. A hello.
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
say |The lamp flickers once. A hello.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday

# ================================================================ CH3 DAY 22
script c3_22
title Ten Amirs
bars on
scene deep amir dalia
say |Day 22. The echoes don't attack. They just stand there, watching, like friends who aren't sure they're allowed to sit down.
bars off
scene off
warp echo 200
npc dalia echo 300
goal Talk to Dalia.
await talk dalia
mini catch 14 3 echoes 3
ifnot skipped ok22
say |(The building pitied you and finished it for you.)
label ok22
say |One of the echoes steps forward. Slightly older. A scar through his eyebrow.
say Echo|I was the first one. I was Day One. I stayed.
say Amir|Stayed where?
say Echo|Here. In the building. Waiting for somebody to come back for me.
set echo_first 1
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
mini pairs 4 5
bars on
scene room amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Something small happens, and it matters more than it should.
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
bars on
scene inn amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |A door opens by itself, then politely closes.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 12
endday

# ================================================================ CH3 DAY 23
script c3_23
title The Quiet Ones
bars on
scene deep amir amir_l4 prime
say |Day 23. The echoes sit around Prime in a circle. He is explaining dust. Slowly. With diagrams.
bars off
scene off
warp echo 200
npc prime echo 600
goal Talk to Prime.
await talk prime
mini roundup 10 45 3
ifnot skipped ok23
say |(The building pitied you and finished it for you.)
label ok23
say |Prime rounds up the last of the dust. The echoes applaud, a little late.
say Prime|THERE IS NOTHING I LOVE MORE THAN AN AUDIENCE.
say Echo|He's an excellent teacher.
set prime_class 1
# VIGNETTE
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
say |Someone left a snack on the stairs. A tiny miracle.
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
say |Someone left a snack on the stairs. A tiny miracle.
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
say |Something small happens, and it matters more than it should.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini lights 3
endday

# ================================================================ CH3 DAY 24
script c3_24
title The Wrong Floor
bars on
scene deep amir gabriel
say |Day 24. The Echo Room has a door we haven't opened. It's painted the color of the Backrooms wallpaper. Gabriel refuses to touch the handle.
bars off
scene off
warp echo 200
npc gabriel echo 350
obj wrongdoor echo 1500 Wallpaper door
goal Open the wallpaper door.
await use wrongdoor
mini maze 3 6
ifnot skipped ok24
say |(The building pitied you and finished it for you.)
label ok24
say |Behind it: a stretch of yellow carpet that is much too long. The building is showing us the way it used to be.
say Gabriel|Nope.
say Amir|You don't have to come.
say Gabriel|...I'm coming.
set wrongfloor 1
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
bars on
scene inn amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Something small happens, and it matters more than it should.
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
say |A door opens by itself, then politely closes.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
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
say |Something small happens, and it matters more than it should.
say Adam|Got a minute? Quick game.
bars off
scene off
mini lights 3
endday

# ================================================================ CH3 DAY 25
script c3_25
title Hum
bars on
scene deep amir sofia kenzy
say |Day 25. The hum is louder. The whole level vibrates at a pitch just below hearing.
bars off
scene off
warp echo 200
npc sofia echo 500
npc kenzy echo 700
goal Talk to Sofia.
await talk sofia
mini rhythm 34 4 130
ifnot skipped ok25
say |(The building pitied you and finished it for you.)
label ok25
say |The hum settles into a melody. It's a lullaby. It's the one the elevator plays in the morning.
say Sofia|It's been singing to you since Day One.
say Haydar|Since before that.
set lullaby 1
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
mini whack 10
bars on
scene lobby amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |The lamp flickers once. A hello.
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
say |The lamp flickers once. A hello.
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
say |A door opens by itself, then politely closes.
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
say |A door opens by itself, then politely closes.
say Prime|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
endday

# ================================================================ CH3 DAY 26
script c3_26
title Brass Tokens
bars on
scene deep amir dalia gabriel
say |Day 26. The tokens from Chapter 1 are warm in my pocket. They start to pulse in time with the hum.
bars off
scene off
warp echo 200
npc dalia echo 320
clearitems
spawn token echo 700
spawn token echo 1100
spawn token echo 1600
goal Collect 3 brass tokens that have rolled away.
await items 3
clearitems
mini dodge 28 4 3
ifnot skipped ok26
say |(The building pitied you and finished it for you.)
label ok26
say |Three tokens. Three slots in the wall. A seam of orange light appears around a door none of us noticed.
say Dalia|The lowest door.
say Gabriel|It's a staircase.
say Amir|Down.
set tokens3 1
# VIGNETTE
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
say |The building hums. Somebody laughs two floors away.
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
say |A door opens by itself, then politely closes.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
endday

# ================================================================ CH3 DAY 27
script c3_27
title The Last Stairs
bars on
scene deep amir dalia gabriel prime
say |Day 27. The staircase is a spiral. Each step has a nameplate. Some of them are scratched out.
bars off
scene off
warp echo 200
npc gabriel echo 350
npc dalia echo 300
npc prime echo 450
obj stairs echo 1700 Staircase
goal Walk to the top of the staircase and go down.
await use stairs
mini sneak 5 3 3
ifnot skipped ok27
say |(The building pitied you and finished it for you.)
label ok27
say |At the bottom, a door with no plate. Just a handprint, burnt into the wood.
say Prime|THE HAND IS HUMAN-SIZED.
say Amir|It's my size.
set stairs 1
# VIGNETTE
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
mini pairs 4 6
bars on
scene inn amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |The lamp flickers once. A hello.
say Prime|Got a minute? Quick game.
bars off
scene off
mini pairs 4 5
endday

# ================================================================ CH3 DAY 28
script c3_28
title Handprint
bars on
scene deep amir dalia
say |Day 28. I put my hand on the handprint. It fits. It's warm. It's been waiting.
bars off
scene off
warp echo 200
npc dalia echo 300
obj handprint echo 1400 Handprint door
goal Place your hand on the handprint.
await use handprint
mini timing 8 3 Hold_the_door 4
ifnot skipped ok28
say |(The building pitied you and finished it for you.)
label ok28
say |The door opens onto a room made entirely of dust. A floor, a ceiling, shapes of furniture. At the center, a throne made of vacuum cleaners.
say Dalia|That is the most terrible chair I've ever seen.
set dustroom 1
# VIGNETTE
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
say |Something small happens, and it matters more than it should.
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
say |A door opens by itself, then politely closes.
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
say |Someone left a snack on the stairs. A tiny miracle.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday

# ================================================================ CH3 DAY 29
script c3_29
title The Dust Queen
bars on
scene deep amir dalia gabriel prime
say |Day 29. She sits on the throne. A tall figure of grey and ash, wearing a crown of old bulbs.
say ???|I have kept this building clean for forty years. And you tracked mud into my kingdom.
bars off
scene off
warp echo 200
npc prime echo 350
npc dalia echo 250
npc gabriel echo 300
goal Talk to Prime.
await talk prime
mini fight 16 6 boss_Queen
ifnot skipped ok29
say |(The building pitied you and finished it for you.)
label ok29
say |The Queen crumbles to a drift of grey. Her crown rolls across the floor and stops against my shoe.
say Prime|SHE WAS A BOT. A VERY OLD ONE. THE FIRST OF MY LINE.
say Amir|She was cleaning.
say Prime|SHE WAS LONELY.
set queen_down 1
# VIGNETTE
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
say |Someone left a snack on the stairs. A tiny miracle.
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
say |The lamp flickers once. A hello.
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
endday

# ================================================================ CH3 DAY 30
script c3_30
title What the Dust Wanted
bars on
scene deep amir prime amir_l4
say |Day 30. The grey drifts rise and settle into the shape of a very small, very tired bot. Prime sits down next to it. He doesn't say anything for a long time.
bars off
scene off
warp echo 200
npc prime echo 400
goal Talk to Prime.
await talk prime
mini catch 16 3 dust_motes 3
ifnot skipped ok30
say |(The building pitied you and finished it for you.)
label ok30
say |The little bot opens one eye. It says a single word, which I'd swear was "home."
say Echo|They never wanted us gone. They wanted us to look.
say Amir|Look at what?
say Echo|At the floor. At the bottom. At what holds everything up.
set dust_wish 1
# VIGNETTE
bars on
scene inn amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |The building hums. Somebody laughs two floors away.
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
bars on
scene lobby amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |The lamp flickers once. A hello.
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
say |The lamp flickers once. A hello.
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
say |The building hums. Somebody laughs two floors away.
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
endday

)IL";
