#pragma once
static const char* STORY_CH3B = R"IL(
# ================================================================ CH3 DAY 11
script c3_11
title The Archive Doors
bars on
scene deep amir dalia gabriel
say |Day 11. South of the Waystation, a corridor that wasn't there yesterday. At its end, a pair of doors, each three stories tall, covered in brass nameplates.
say Dalia|Every single plate has a name on it.
say Gabriel|Some of them have two.
bars off
scene off
warp ulobby 200
npc dalia ulobby 320
npc gabriel ulobby 420
obj archdoor ulobby 1500 Archive doors
goal Walk to the Archive doors at the east end and use them.
await use archdoor
mini timing 6 4 Open_the_Archive 3
ifnot skipped ok11
say |(The building pitied you and finished it for you.)
label ok11
say |The doors swing inward without a sound. Rows of shelves vanish into the dark. Every shelf is full of identical grey folders.
say Dalia|It's a library of us.
say Amir|Not us. Versions of us.
set archive_open 1
# VIGNETTE
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
bars on
scene room amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |Something small happens, and it matters more than it should.
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
say |A door opens by itself, then politely closes.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday

# ================================================================ CH3 DAY 12
script c3_12
title Folders
bars on
scene deep amir dalia kenzy
say |Day 12. The folders don't open. They don't tear. They don't burn. Haydar tried all three, and kept notes.
say Haydar|They respond to sound. Specifically, a sequence.
bars off
scene off
warp ulobby 300
npc kenzy ulobby 900
npc dalia ulobby 500
goal Talk to Haydar at the shelves.
await talk kenzy
mini simon 7 3 26
ifnot skipped ok12
say |(The building pitied you and finished it for you.)
label ok12
say |The folder pops open. Inside: a single photograph. A kid in an orange 14 hoodie, laughing, covered in flour.
say Dalia|That's Amine's papercraft day.
say Amir|That was Chapter 1.
say Haydar|Day 3, if you want to be precise.
say Amir|They've been watching.
say Dalia|Or remembering.
set folder1 1
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
mini lights 4
bars on
scene outside amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Someone left a snack on the stairs. A tiny miracle.
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
say |The lamp flickers once. A hello.
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
endday

# ================================================================ CH3 DAY 13
script c3_13
title Dust Library
bars on
scene deep amir gabriel bolt
say |Day 13. The Archive's lower stacks are crawling with dust wraiths. Bolt volunteers to be the first line of defence. Nobody asked him to.
bars off
scene off
warp ulobby 250
npc gabriel ulobby 350
clearitems
spawn page ulobby 700
spawn page ulobby 1100
spawn page ulobby 1600
spawn page ulobby 2100
goal Collect 4 loose pages from the lower stacks.
await items 4
clearitems
mini fight 14 6 dust_wraiths
ifnot skipped ok13
say |(The building pitied you and finished it for you.)
label ok13
say |The pages are numbered. 1, 2, 3 and 7. Someone tore out 4, 5 and 6.
say Gabriel|Missing pages is a plan, not an accident.
say Bolt|A plan with holes! Fun!
set pages1 1
# VIGNETTE
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
mini quiz 4 ilot14
bars on
scene lobby amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |The building hums. Somebody laughs two floors away.
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
endday

# ================================================================ CH3 DAY 14
script c3_14
title The Whispering Aisle
bars on
scene deep amir dalia
say |Day 14. Aisle K. The shelves whisper. Not words. Breathing, mostly. Dalia holds my sleeve and pretends she isn't.
bars off
scene off
warp ulobby 200
npc dalia ulobby 300
obj aisleK ulobby 1300 Aisle K
goal Walk to the end of Aisle K.
await use aisleK
mini sneak 4 3 2
ifnot skipped ok14
say |(The building pitied you and finished it for you.)
label ok14
say |At the end of the aisle, a desk. A lamp. A chair pulled out, still warm.
say Dalia|Somebody was just here.
say Amir|Somebody who knows how to leave before we arrive.
set aislek 1
# VIGNETTE
bars on
scene inn amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The building hums. Somebody laughs two floors away.
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
say |Something small happens, and it matters more than it should.
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

# ================================================================ CH3 DAY 15
script c3_15
title Name Tags
bars on
scene deep amir dalia gabriel prime
say |Day 15. Prime has been sorting nameplates by owner. He has a very serious voice for this.
say Prime|THIRTY-ONE PLATES FOR LEVEL ONE. THIRTY-FIVE FOR THE INN. FORTY FOR BELOW. ONE PLATE LEFT OVER.
bars off
scene off
warp ulobby 300
npc prime ulobby 600
npc dalia ulobby 420
goal Talk to Prime.
await talk prime
mini catch 12 3 nameplates 2
ifnot skipped ok15
say |(The building pitied you and finished it for you.)
label ok15
say |The leftover plate is blank except for a tiny engraved line: "Someone who stays."
say Dalia|That's a job description.
say Prime|IT IS A SHORT, LONELY ONE.
set plate_blank 1
# VIGNETTE
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
say |Someone left a snack on the stairs. A tiny miracle.
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
say |Something small happens, and it matters more than it should.
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
endday

# ================================================================ CH3 DAY 16
script c3_16
title The Reading Room
bars on
scene deep amir kenzy sofia
say |Day 16. A round room at the center of the Archive, with one reading table and thirty chairs. Sofia hums a single low note and the chairs all turn to face the same wall.
bars off
scene off
warp ulobby 300
npc sofia ulobby 800
npc kenzy ulobby 1000
goal Talk to Sofia.
await talk sofia
mini rhythm 28 5 120
ifnot skipped ok16
say |(The building pitied you and finished it for you.)
label ok16
say |The wall slides away. Behind it, a map of the whole building, drawn in ash. Every floor. Every door. And below Level 18, a floor that isn't labelled.
say Haydar|That's not on any plan I've seen.
say Sofia|It's the one that sings.
set map_ash 1
# VIGNETTE
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
say |The lamp flickers once. A hello.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
endday

# ================================================================ CH3 DAY 17
script c3_17
title Ash Maze
bars on
scene deep amir dalia gabriel
say |Day 17. The unlabelled floor connects to the Archive by a maze. A hedge of grey ribbons, taller than Gabriel.
bars off
scene off
warp ulobby 200
obj mazeexit ulobby 2000 Maze exit
goal Find your way through the ribbons to the far end.
await use mazeexit
mini maze 3 5
ifnot skipped ok17
say |(The building pitied you and finished it for you.)
label ok17
say |The ribbons part. A small circular room with a stone fountain. The water is black, and it moves when you move.
say Gabriel|I don't like fountains.
say Dalia|You don't like anything.
say Gabriel|Fountains most.
set fountain 1
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
mini whack 10
bars on
scene lobby amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Something small happens, and it matters more than it should.
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
say |A door opens by itself, then politely closes.
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

# ================================================================ CH3 DAY 18
script c3_18
title The Fountain
bars on
scene deep amir dalia
say |Day 18. The black water shows reflections. Not ours. The ones from the doors. Amir with a bandaged arm. Amir with a crown of paper. Amir alone on a roof, tiny against a big sky.
bars off
scene off
warp ulobby 200
npc dalia ulobby 300
obj fountain ulobby 1200 Black fountain
goal Walk to the fountain and look into the water.
await use fountain
mini timing 7 3 Steady_the_water 3
ifnot skipped ok18
say |(The building pitied you and finished it for you.)
label ok18
say |The water settles. For one second, every reflection looks up at me at once.
say Dalia|They know you're here.
say Amir|They've always known.
set fountain2 1
# VIGNETTE
bars on
scene inn amir gabriel
cast amir 300
cast gabriel 1100
walk gabriel 700 5 wait
emote gabriel !
anim gabriel wave
say |Someone left a snack on the stairs. A tiny miracle.
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
say |Something small happens, and it matters more than it should.
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
say |Something small happens, and it matters more than it should.
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
endday

# ================================================================ CH3 DAY 19
script c3_19
title Spilled Ink
bars on
scene deep amir sofia
say |Day 19. A cart of ink bottles has tipped over. The ink forms words on the floor, then sinks before anyone can read them.
bars off
scene off
warp ulobby 250
npc sofia ulobby 500
clearitems
spawn ink ulobby 600
spawn ink ulobby 900
spawn ink ulobby 1300
spawn ink ulobby 1700
spawn ink ulobby 2200
goal Collect 5 ink bottles before the words fade.
await items 5
clearitems
mini dodge 24 4 2
ifnot skipped ok19
say |(The building pitied you and finished it for you.)
label ok19
say |Through the ink, a sentence finally holds long enough to read: "The one who stays has to be asked."
say Sofia|Asked what?
say Amir|...Asked to stay.
set ink_words 1
# VIGNETTE
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
say |Something small happens, and it matters more than it should.
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
say |Something small happens, and it matters more than it should.
say Gabriel|Got a minute? Quick game.
bars off
scene off
mini popcorn 10 2 1
endday

# ================================================================ CH3 DAY 20
script c3_20
title Doors Within Doors
bars on
scene deep amir dalia gabriel
say |Day 20. A door inside a door inside a door. Each smaller, each plainer, each with the same brass plate: L-001 AMIR.
bars off
scene off
warp ulobby 250
npc gabriel ulobby 400
npc dalia ulobby 300
obj nestdoor ulobby 1800 Nested door
goal Walk to the nested doors.
await use nestdoor
mini defend 4 5 2
ifnot skipped ok20
say |(The building pitied you and finished it for you.)
label ok20
say |The last door is the size of a mailbox. Inside, a single sealed envelope.
say Gabriel|Do not open that.
say Amir|I'm going to open that.
say Dalia|Obviously.
say |"Come to the Echo Room. Come alone. Bring everyone."
set envelope 1
# VIGNETTE
bars on
scene lobby amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |A door opens by itself, then politely closes.
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
say |Something small happens, and it matters more than it should.
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
say |The building hums. Somebody laughs two floors away.
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
say |The lamp flickers once. A hello.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 10
endday

)IL";
