// generated c5
#pragma once
static const char* STORY_C5NEW = R"IL(
# ---- c5 DAY 1
script c5_1
title The Rope
card CHAPTER 5|Safe Ascent
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel dance
say |A fresh morning on the Roof. A long rope runs down through the stairwell. A tag says: SAFE ASCENT - DAY 1.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|THE ELEVATOR WORKS AGAIN. BUT THE BUILDING WANTS A SAFE WAY UP FOR EVERYONE. EVEN THE SMALLEST. I HAVE A LIST.
say Prime@prime|The list has fourteen floors on it. Each floor needs one thing: light, a rail or a friend.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d1_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d1_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia roof 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime stomp
anim amir jump
say |Prime hands Amir a tiny clipboard. It feels official.
bars off
scene off
endday

# ---- c5 DAY 2
script c5_2
title The Inn Rail
bars on
scene inn amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel cheer
say |At the Further inn, the stair rail is loose. Sofia holds it up with her shoulder.
say Dalia@dalia|Ready when you are, Amir.
anim dalia look
bars off
scene off
goal Take the elevator to the Further inn.
await floor inn
npc sofia inn 900
goal Talk to Sofia.
await talk sofia
say Sofia@sofia|Oh good, you're here. The rail wobbles. Aya says it's haunted. It's not haunted. It's just old.
say Sofia@sofia|Adam Tansaouti has a toolbox. Aya has a snack. I have a plan. We need a hammer and a steady hand.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d2_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d2_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp inn 600
spawn lamp inn 1200
spawn lamp inn 1800
goal Collect the 3 glowing lamps on the Further inn.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia sofia
cast amir 300
cast dalia 1200
cast sofia 1100
walk amir 560 6
walk dalia 760 5
walk sofia 900 4 wait
anim sofia float
anim amir look
say |The rail stops wobbling. Aya cheers with her mouth full.
bars off
scene off
endday

# ---- c5 DAY 3
script c5_3
title Aya's Soup Test
bars on
scene inn amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel nod
say |Aya stirs a pot on the Inn stove. Steam rises like a little cloud.
say Dalia@dalia|Ready when you are, Amir.
anim dalia wave
bars off
scene off
goal Take the elevator to the Further inn.
await floor inn
npc aya_n inn 900
goal Talk to Aya.
await talk aya_n
say Aya@aya_n|I'm making soup for the climbers! It's for energy! Mostly for me! Taste it!
say Aya@aya_n|It tastes like pennies and kindness. It's the Inn's flavor.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d3_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d3_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia inn 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia aya_n
cast amir 300
cast dalia 1200
cast aya_n 1100
walk amir 560 6
walk dalia 760 5
walk aya_n 900 4 wait
anim aya_n tilt
anim amir wave
say |Aya ladles soup into little cups. Every climber gets one.
bars off
scene off
endday

# ---- c5 DAY 4
script c5_4
title Bots Check-in
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel point
say |The 14 Cleaning bots parking hums. Every bot is polishing something.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shiver
bars off
scene off
goal Take the elevator to the 14 Cleaning bots parking.
await floor bots
npc mopsy bots 900
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|I was told there would be dust. There is dust. It is a disgrace. I will fix it.
say Mopsy@mopsy|The bots will guard the stairs. Each one gets a floor. Mopsy picks the Main floor, obviously.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d4_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d4_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp bots 600
spawn lamp bots 1200
spawn lamp bots 1800
goal Collect the 3 glowing lamps on the 14 Cleaning bots parking.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia mopsy
cast amir 300
cast dalia 1200
cast mopsy 1100
walk amir 560 6
walk dalia 760 5
walk mopsy 900 4 wait
anim mopsy shrug
anim amir shiver
say |Mopsy salutes with a mop. Bolt copies her. Prime salutes both.
bars off
scene off
endday

# ---- c5 DAY 5
script c5_5
title Bolt Wants a Floor
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel laugh
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |Bolt zooms laps around a pillar. The pillar is dizzy.
say Dalia@dalia|Ready when you are, Amir.
anim dalia stomp
bars off
scene off
goal Take the elevator to the 14 Cleaning bots parking.
await floor bots
npc bolt bots 900
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|BEEP! I WANT THE LETHAL FLOOR! IT'S MY FLOOR! I'LL ZOOM ABOVE AND BELOW IT!
say Bolt@bolt|Okay. You may zoom. You may not crash into Prime.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d5_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d5_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia bots 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia bolt
cast amir 300
cast dalia 1200
cast bolt 1100
walk amir 560 6
walk dalia 760 5
walk bolt 900 4 wait
anim bolt hop
anim amir stomp
say |Bolt crashes into Prime. They both pretend it was planned.
bars off
scene off
endday

# ---- c5 DAY 6
script c5_6
title The Whistling Wind
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel jump
say |In the ventilation systems a thin whistle follows the group. Haydar listens with his radio.
say Dalia@dalia|Ready when you are, Amir.
anim dalia float
bars off
scene off
goal Take the elevator to the Air ventilation systems.
await floor vent
npc kenzy vent 900
goal Talk to Haydar.
await talk kenzy
say Haydar@kenzy|It's the same tune from before! The wind is humming! It's happy! Mostly happy!
say Haydar@kenzy|I told it to keep the air fresh. It wrote back. In whistles. I'm fine.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d6_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d6_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp vent 600
spawn lamp vent 1200
spawn lamp vent 1800
goal Collect the 3 glowing lamps on the Air ventilation systems.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia kenzy
cast amir 300
cast dalia 1200
cast kenzy 1100
walk amir 560 6
walk dalia 760 5
walk kenzy 900 4 wait
anim kenzy sway
anim amir float
say |The whistle softens into a lullaby. The vent smells like rain.
bars off
scene off
endday

# ---- c5 DAY 7
script c5_7
title Jilali's Gears
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel look
say |Jilali sits on an upturned crate fixing a stack of tiny gears.
say Dalia@dalia|Ready when you are, Amir.
anim dalia tilt
bars off
scene off
goal Take the elevator to the Air ventilation systems.
await floor vent
npc jilali vent 900
goal Talk to Jilali.
await talk jilali
say Jilali@jilali|These turn the fans. They were off by one tooth. One tooth! Forty years of wrong air!
say Jilali@jilali|Hold this. No, that. Yes. That one is a screw. I think.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d7_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d7_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia vent 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia jilali
cast amir 300
cast dalia 1200
cast jilali 1100
walk amir 560 6
walk dalia 760 5
walk jilali 900 4 wait
anim jilali bounce
anim amir tilt
say |The fans spin true. A cool breeze runs through the floor.
bars off
scene off
endday

# ---- c5 DAY 8
script c5_8
title The Control Room Lamp
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel wave
say |In the Elevator control room an old lamp flickers. It spells out nothing, but it tries.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shrug
bars off
scene off
goal Take the elevator to the Elevator control room.
await floor ctrl
npc prime ctrl 900
goal Talk to Prime.
await talk prime
say Prime@prime|THIS LAMP WAS THE FIRST LIGHT I SAW. I WOULD LIKE IT FIXED. IT WOULD MAKE ME VERY HAPPY.
say Prime@prime|I DO NOT CRY. THIS IS OIL.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d8_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d8_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp ctrl 600
spawn lamp ctrl 1200
spawn lamp ctrl 1800
goal Collect the 3 glowing lamps on the Elevator control room.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime clap
anim amir shrug
say |The lamp glows steady and warm. Prime stands very still for a minute.
bars off
scene off
endday

# ---- c5 DAY 9
script c5_9
title Youcef's Panel
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shiver
say |Youcef frowns at a panel with seventeen switches.
say Dalia@dalia|Ready when you are, Amir.
anim dalia hop
bars off
scene off
goal Take the elevator to the Elevator control room.
await floor ctrl
npc youcef ctrl 900
goal Talk to Youcef.
await talk youcef
say Youcef@youcef|NEVER FLIP THE RED ONE. I flipped the red one. It's fine! It's all fine! The lights blinked!
say Youcef@youcef|Okay. The red switch is the lamp. The blue one is the music. I think.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d9_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d9_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia ctrl 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia youcef
cast amir 300
cast dalia 1200
cast youcef 1100
walk amir 560 6
walk dalia 760 5
walk youcef 900 4 wait
anim youcef zoomies
anim amir hop
say |A tune plays through the building. Everybody pauses to listen.
bars off
scene off
endday

# ---- c5 DAY 10
script c5_10
title The Shaft Ladder
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel stomp
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |In the Elevator shaft a metal ladder runs up into the dark. Arwa tests the first rung.
say Dalia@dalia|Ready when you are, Amir.
anim dalia sway
bars off
scene off
goal Take the elevator to the Elevator shaft.
await floor shaft
npc arwa shaft 900
goal Talk to Arwa.
await talk arwa
say Arwa@arwa|Jalil keeps climbing it. He's four. He can't. He keeps trying. We need a gate.
say Arwa@arwa|I'll hold the gate. You hold the hammer. Amir, don't look so serious.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d10_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d10_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp shaft 600
spawn lamp shaft 1200
spawn lamp shaft 1800
goal Collect the 3 glowing lamps on the Elevator shaft.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia arwa
cast amir 300
cast dalia 1200
cast arwa 1100
walk amir 560 6
walk dalia 760 5
walk arwa 900 4 wait
anim arwa twirl
anim amir sway
say |The gate clicks shut. Jalil waves through the bars like a tiny prisoner.
bars off
scene off
endday

# ---- c5 DAY 11
script c5_11
title Jalil's Gate Guard
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel float
say |Jalil wears a paper crown and guards the new gate with a spoon.
say Dalia@dalia|Ready when you are, Amir.
anim dalia bounce
bars off
scene off
goal Take the elevator to the Elevator shaft.
await floor shaft
npc jalil shaft 900
goal Talk to Jalil.
await talk jalil
say Jalil@jalil|I'm the king of the stairs! Nobody climbs without my say! You may pass if you say please!
say Jalil@jalil|He is four. He is serious. The kingdom is a staircase.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d11_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d11_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia shaft 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia jalil
cast amir 300
cast dalia 1200
cast jalil 1100
walk amir 560 6
walk dalia 760 5
walk jalil 900 4 wait
anim jalil sneak
anim amir bounce
say |Jalil lets Amir pass with a royal nod. Gabriel bows lower.
bars off
scene off
endday

# ---- c5 DAY 12
script c5_12
title Parking 2 Is Clean
bars on
scene garage amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel tilt
say |Parking 2 is clear of dust sheets. Sweepy beams under a little flag.
say Dalia@dalia|Ready when you are, Amir.
anim dalia clap
bars off
scene off
goal Take the elevator to Parking 2.
await floor park2
npc sweepy park2 900
goal Talk to Sweepy.
await talk sweepy
say Sweepy@sweepy|I'm Sweepy and every floor shines! Even the corners! Even the corners that hate me!
say Sweepy@sweepy|The dust sheets are folded. The cars wait like sleepy animals.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d12_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d12_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp park2 600
spawn lamp park2 1200
spawn lamp park2 1800
goal Collect the 3 glowing lamps on Parking 2.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia sweepy
cast amir 300
cast dalia 1200
cast sweepy 1100
walk amir 560 6
walk dalia 760 5
walk sweepy 900 4 wait
anim sweepy dizzy
anim amir clap
say |Sweepy plants a tiny flag on every car. It's weirdly moving.
bars off
scene off
endday

# ---- c5 DAY 13
script c5_13
title Dania's Rainbow Rail
bars on
scene garage amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shrug
say |Dania unrolls a huge roll of colored tape across the Parking 1 rail.
say Dalia@dalia|Ready when you are, Amir.
anim dalia zoomies
bars off
scene off
goal Take the elevator to Parking 1.
await floor park1
npc dania park1 900
goal Talk to Dania.
await talk dania
say Dania@dania|Safe stairs should be PRETTY! Red for up! Blue for down! Green for brave! Look!
say Dania@dania|It's eleven-year-old logic. It works perfectly.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d13_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d13_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia park1 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia dania
cast amir 300
cast dalia 1200
cast dania 1100
walk amir 560 6
walk dalia 760 5
walk dania 900 4 wait
anim dania salute
anim amir zoomies
say |The rail glows like a rainbow. Even Gabriel nods in respect.
bars off
scene off
endday

# ---- c5 DAY 14
script c5_14
title Dustin's Fear
bars on
scene garage amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel hop
say |Dustin hides behind a barrel. It's yellow. He is terrified.
say Dalia@dalia|Ready when you are, Amir.
anim dalia twirl
bars off
scene off
goal Take the elevator to Parking 1.
await floor park1
npc dustin park1 900
goal Talk to Dustin.
await talk dustin
say Dustin@dustin|N-nothing's wrong! I'm not scared of the stairs! Or the yellow! Or you!
say Dustin@dustin|He's afraid of yellow. We can paint over the barrel. Or hug him. Probably both.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d14_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d14_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp park1 600
spawn lamp park1 1200
spawn lamp park1 1800
goal Collect the 3 glowing lamps on Parking 1.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia dustin
cast amir 300
cast dalia 1200
cast dustin 1100
walk amir 560 6
walk dalia 760 5
walk dustin 900 4 wait
anim dustin dance
anim amir twirl
say |Dustin lets Alicia hug him. He's still scared. He's less scared.
bars off
scene off
endday

# ---- c5 DAY 15
script c5_15
title Alicia's Stairs Map
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel sway
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |In the Underlobby Alicia draws a map of the stairs with a fat crayon.
say Dalia@dalia|Ready when you are, Amir.
anim dalia sneak
bars off
scene off
goal Take the elevator to the Underlobby.
await floor ulobby
npc alicia ulobby 900
goal Talk to Alicia.
await talk alicia
say Alicia@alicia|Big brother! I drew all the floors! I made the Roof a star! Look at the star! It's you!
say Alicia@alicia|She's five. The map is wrong. It's also perfect.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d15_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d15_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia ulobby 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia alicia
cast amir 300
cast dalia 1200
cast alicia 1100
walk amir 560 6
walk dalia 760 5
walk alicia 900 4 wait
anim alicia cheer
anim amir sneak
say |Amir keeps the crayon map in his pocket. He doesn't say why.
bars off
scene off
endday

# ---- c5 DAY 16
script c5_16
title Abdullah's Inspection
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel bounce
say |Abdullah, six, wears a tiny hard hat and carries a clipboard.
say Dalia@dalia|Ready when you are, Amir.
anim dalia dizzy
bars off
scene off
goal Take the elevator to the Underlobby.
await floor ulobby
npc abdullah ulobby 900
goal Talk to Abdullah.
await talk abdullah
say Abdullah@abdullah|I'm the safety inspector! I check every step! This one is fine! This one is fine! This one is... fine!
say Abdullah@abdullah|He is very serious. He does not know what a clipboard is for. He is ruthless.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d16_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d16_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp ulobby 600
spawn lamp ulobby 1200
spawn lamp ulobby 1800
goal Collect the 3 glowing lamps on the Underlobby.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia abdullah
cast amir 300
cast dalia 1200
cast abdullah 1100
walk amir 560 6
walk dalia 760 5
walk abdullah 900 4 wait
anim abdullah nod
anim amir dizzy
say |Abdullah gives every step a gold star. The staircase looks like a sticker book.
bars off
scene off
endday

# ---- c5 DAY 17
script c5_17
title Anes at the Lobby
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel clap
say |Anes sits on a bench, teaching a bot to whistle.
say Dalia@dalia|Ready when you are, Amir.
anim dalia salute
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc anes lobby 900
goal Talk to Anes.
await talk anes
say Anes@anes|It's hard. The bot has no lips. But we're making progress! He whistled once! A little!
say Anes@anes|Abdullah told me you're doing the safety thing. I want to help. I'm ten. I'm great at sitting.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d17_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d17_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lobby 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia anes
cast amir 300
cast dalia 1200
cast anes 1100
walk amir 560 6
walk dalia 760 5
walk anes 900 4 wait
anim anes point
anim amir salute
say |The bot whistles three notes. Anes gasps like it won the lottery.
bars off
scene off
endday

# ---- c5 DAY 18
script c5_18
title Iyad Is Late
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel zoomies
say |Iyad arrives at the Lobby running, out of breath, ten minutes after everyone.
say Dalia@dalia|Ready when you are, Amir.
anim dalia dance
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc iyad lobby 900
goal Talk to Iyad.
await talk iyad
say Iyad@iyad|Sorry! I'm late! I'm always late! It's a talent! Is the Ascent started? Did I miss the soup?
say Iyad@iyad|You're on time for the best part. The stairs are ready.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d18_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d18_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp lobby 600
spawn lamp lobby 1200
spawn lamp lobby 1800
goal Collect the 3 glowing lamps on the Lobby.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia iyad
cast amir 300
cast dalia 1200
cast iyad 1100
walk amir 560 6
walk dalia 760 5
walk iyad 900 4 wait
anim iyad laugh
anim amir dance
say |Iyad checks his watch. It says yesterday. He shrugs and joins the climb.
bars off
scene off
endday

# ---- c5 DAY 19
script c5_19
title Dalia Takes Charge
bars on
scene hall amir gabriel amine
cast amir 300
cast gabriel 1100
cast amine 1250
walk amir 560 4
walk gabriel 760 5
walk amine 930 5 wait
emote gabriel !
anim amine twirl
say |On the Common floor Dalia stands on a crate with a whistle she found.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel cheer
bars off
scene off
goal Take the elevator to the Common floor.
await floor common
npc dalia common 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|Okay everyone! LINE UP! Two by two! Kids in the middle! Gabriel, stop smiling!
say Dalia@dalia|I am not smiling! I'm... breathing happily!
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d19_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d19_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Gabriel.
npc gabriel common 1400
await talk gabriel
say Gabriel@gabriel|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir gabriel dalia
cast amir 300
cast gabriel 1200
cast dalia 1100
walk amir 560 6
walk gabriel 760 5
walk dalia 900 4 wait
anim dalia jump
anim amir cheer
say |The line forms. It's the neatest line the building has ever seen.
bars off
scene off
endday

# ---- c5 DAY 20
script c5_20
title The Knot
bars on
scene hall amir dalia amine
cast amir 300
cast dalia 1100
cast amine 1250
walk amir 560 4
walk dalia 760 5
walk amine 930 5 wait
emote dalia !
anim amine sneak
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |Gabriel ties a long safety rope along the Common floor stairs.
say Dalia@dalia|Ready when you are, Amir.
anim dalia nod
bars off
scene off
goal Take the elevator to the Common floor.
await floor common
npc gabriel common 900
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|It's a safe knot. It holds more than we do. Hold it. Both hands.
say Gabriel@gabriel|I tied it myself. Don't tell Dalia I did it for her. I mean, for everyone.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d20_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d20_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp common 600
spawn lamp common 1200
spawn lamp common 1800
goal Collect the 3 glowing lamps on the Common floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1200
cast gabriel 1100
walk amir 560 6
walk dalia 760 5
walk gabriel 900 4 wait
anim gabriel look
anim amir nod
say |The rope runs like a spine up the stairwell. Strong. Quiet.
bars off
scene off
endday

# ---- c5 DAY 21
script c5_21
title Maysanne Draws the Way
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel dizzy
say |Maysanne, nine, draws a bright arrow on every step of the Uncommon floor.
say Dalia@dalia|Ready when you are, Amir.
anim dalia point
bars off
scene off
goal Take the elevator to the Uncommon floor.
await floor unc
npc maysanne unc 900
goal Talk to Maysanne.
await talk maysanne
say Maysanne@maysanne|So nobody gets lost. An arrow. And a little face on every arrow. This one is shy.
say Maysanne@maysanne|Draw me one! Draw me one! Okay, it's a bot. It's a happy bot.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d21_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d21_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia unc 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia maysanne
cast amir 300
cast dalia 1200
cast maysanne 1100
walk amir 560 6
walk dalia 760 5
walk maysanne 900 4 wait
anim maysanne wave
anim amir point
say |The stairs are covered in arrows with faces. The faces smile at every foot.
bars off
scene off
endday

# ---- c5 DAY 22
script c5_22
title Anais Asks
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel salute
say |Anais reads a book while walking up the stairs and does not trip once.
say Dalia@dalia|Ready when you are, Amir.
anim dalia laugh
bars off
scene off
goal Take the elevator to the Rare floor.
await floor rare
npc anais rare 900
goal Talk to Anais.
await talk anais
say Anais@anais|Why does the building want a safe ascent? Not for us. For somebody who will come later. That's the only answer that makes sense.
say Anais@anais|I don't know who. But I think the building does. It's been waiting.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d22_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d22_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp rare 600
spawn lamp rare 1200
spawn lamp rare 1800
goal Collect the 3 glowing lamps on the Rare floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia anais
cast amir 300
cast dalia 1200
cast anais 1100
walk amir 560 6
walk dalia 760 5
walk anais 900 4 wait
anim anais shiver
anim amir laugh
say |Anais closes her book. She looks at the stairwell like it might answer.
bars off
scene off
endday

# ---- c5 DAY 23
script c5_23
title The Clock Knows
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel dance
say |Jilali taps the Rare floor clock. It chimes. It has never chimed on its own before.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator to the Rare floor.
await floor rare
npc jilali rare 900
goal Talk to Jilali.
await talk jilali
say Jilali@jilali|It's counting the steps. Don't ask me how. I'm a watch fixer, not a wizard.
say Jilali@jilali|Forty years of ticking. Now it counts. I'm choosing to believe in magic. Just today.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d23_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d23_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia rare 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia jilali
cast amir 300
cast dalia 1200
cast jilali 1100
walk amir 560 6
walk dalia 760 5
walk jilali 900 4 wait
anim jilali stomp
anim amir jump
say |The clock rings once for every step they climb. It's slightly annoying and totally lovely.
bars off
scene off
endday

# ---- c5 DAY 24
script c5_24
title Amine's Visit
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel cheer
say |Amine waits on the Special floor with a bag of snacks and a worried expression.
say Dalia@dalia|Ready when you are, Amir.
anim dalia look
bars off
scene off
goal Take the elevator to the Special floor.
await floor special
npc amine special 900
goal Talk to Amine.
await talk amine
say Amine@amine|Amir! I made peanut butter things. They look odd. They taste odd. They're mine.
say Amine@amine|I'm not good at the climbing part. But I can hold things. And hold you up. I mean, hold the stairs.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d24_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d24_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp special 600
spawn lamp special 1200
spawn lamp special 1800
goal Collect the 3 glowing lamps on the Special floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia amine
cast amir 300
cast dalia 1200
cast amine 1100
walk amir 560 6
walk dalia 760 5
walk amine 900 4 wait
anim amine float
anim amir look
say |Amine and Amir share a snack on the landing. It's the best landing.
bars off
scene off
endday

# ---- c5 DAY 25
script c5_25
title Adam's Story
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel nod
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |Adam Tansaouti sits on a Special floor step, polishing his shoes.
say Dalia@dalia|Ready when you are, Amir.
anim dalia wave
bars off
scene off
goal Take the elevator to the Special floor.
await floor special
npc tansaouti special 900
goal Talk to Adam Tansaouti.
await talk tansaouti
say Adam Tansaouti@tansaouti|The Inn and the Special floor share a staircase. I've counted the steps for years. There are two hundred and one.
say Adam Tansaouti@tansaouti|I made a tea for the climbers. It's nothing special. That's the special part.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d25_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d25_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia special 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia tansaouti
cast amir 300
cast dalia 1200
cast tansaouti 1100
walk amir 560 6
walk dalia 760 5
walk tansaouti 900 4 wait
anim tansaouti tilt
anim amir wave
say |He pours tea into tiny cups. It tastes like quiet.
bars off
scene off
endday

# ---- c5 DAY 26
script c5_26
title Arwa's Rope
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel point
say |On the Main floor Arwa checks the rope the way you check a sleeping baby.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shiver
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc arwa main 900
goal Talk to Arwa.
await talk arwa
say Arwa@arwa|Jalil needs a babysitter. The building needs a rail. I'll be both. I'm very good.
say Arwa@arwa|It's a lot. It's okay. I like a lot. Mostly.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d26_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d26_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp main 600
spawn lamp main 1200
spawn lamp main 1800
goal Collect the 3 glowing lamps on the Main floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia arwa
cast amir 300
cast dalia 1200
cast arwa 1100
walk amir 560 6
walk dalia 760 5
walk arwa 900 4 wait
anim arwa shrug
anim amir shiver
say |Arwa winks at Dalia. Dalia sticks her tongue out. They're best friends and enemies.
bars off
scene off
endday

# ---- c5 DAY 27
script c5_27
title Mopsy's Floor
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel laugh
say |Mopsy sweeps the Main floor like a tiny, furious storm.
say Dalia@dalia|Ready when you are, Amir.
anim dalia stomp
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc mopsy main 900
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|This is my floor. I'm furious about the dust. I'm also thrilled. Both are true.
say Mopsy@mopsy|If anyone steps on my clean spot, I will bite them. A little. With bristles.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d27_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d27_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia main 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia mopsy
cast amir 300
cast dalia 1200
cast mopsy 1100
walk amir 560 6
walk dalia 760 5
walk mopsy 900 4 wait
anim mopsy hop
anim amir stomp
say |The Main floor shines. Mopsy sits in the middle with a tiny crown made of lint.
bars off
scene off
endday

# ---- c5 DAY 28
script c5_28
title Raceem on the Lethal Floor
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel jump
say |Raceem rolls past on a skateboard, balancing a tray of cups.
say Dalia@dalia|Ready when you are, Amir.
anim dalia float
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc raceem lethal 900
goal Talk to Raceem.
await talk raceem
say Raceem@raceem|Climb faster! Climb faster! Wait, slower! Slower! I'm falling! I'm okay!
say Raceem@raceem|Raceem hits the wall softly. The tray lands perfectly. Nobody spills.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d28_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d28_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp lethal 600
spawn lamp lethal 1200
spawn lamp lethal 1800
goal Collect the 3 glowing lamps on the Lethal floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia raceem
cast amir 300
cast dalia 1200
cast raceem 1100
walk amir 560 6
walk dalia 760 5
walk raceem 900 4 wait
anim raceem sway
anim amir float
say |Raceem takes a bow. Bolt takes a bigger one.
bars off
scene off
endday

# ---- c5 DAY 29
script c5_29
title Basmala's Note
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel look
say |Basmala hands Amir a folded note with ceremonial solemnity.
say Dalia@dalia|Ready when you are, Amir.
anim dalia tilt
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc basmala lethal 900
goal Talk to Basmala.
await talk basmala
say Basmala@basmala|Read it on the Roof. Not before. It's important. It's also private. Both.
say Basmala@basmala|I wrote it twice. The first one was too long.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d29_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d29_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lethal 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia basmala
cast amir 300
cast dalia 1200
cast basmala 1100
walk amir 560 6
walk dalia 760 5
walk basmala 900 4 wait
anim basmala bounce
anim amir tilt
say |Amir tucks the note into his pocket. It's warm. It smells like pencils.
bars off
scene off
endday

# ---- c5 DAY 30
script c5_30
title Amyas Closes the Shop
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel wave
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |Amyas locks his ice-cream cart on the Teen floor and leans on the stairs.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shrug
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc amyas teen 900
goal Talk to Amyas.
await talk amyas
say Amyas@amyas|Amir. I'm going up with you. Don't say a word. Don't thank me. It's strawberry.
say Amyas@amyas|I'm nineteen. I'm the oldest. Somebody has to keep the youngest from being brave.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d30_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d30_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp teen 600
spawn lamp teen 1200
spawn lamp teen 1800
goal Collect the 3 glowing lamps on the Teen floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia amyas
cast amir 300
cast dalia 1200
cast amyas 1100
walk amir 560 6
walk dalia 760 5
walk amyas 900 4 wait
anim amyas clap
anim amir shrug
say |Amyas puts his hands in his pockets. His mouth twitches. It's almost a smile.
bars off
scene off
endday

# ---- c5 DAY 31
script c5_31
title Adam Bachouche's Climb
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shiver
say |Adam Bachouche paces on the Teen floor, fiddling with a flashlight.
say Dalia@dalia|Ready when you are, Amir.
anim dalia hop
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc adam_t teen 900
goal Talk to Adam.
await talk adam_t
say Adam@adam_t|Hey, Amir. I'm not here to help. I'm here because it's on my way. Don't read into it.
say Adam@adam_t|Fine. I'm helping. You're slow. Give me the clipboard.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d31_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d31_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia teen 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia adam_t
cast amir 300
cast dalia 1200
cast adam_t 1100
walk amir 560 6
walk dalia 760 5
walk adam_t 900 4 wait
anim adam_t zoomies
anim amir hop
say |He takes the clipboard and checks every step. Twice. He pretends it was an accident.
bars off
scene off
endday

# ---- c5 DAY 32
script c5_32
title Lilian Leads
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel stomp
say |Lilian leads a line of small kids up the Teen floor stairs, singing.
say Dalia@dalia|Ready when you are, Amir.
anim dalia sway
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc lilian teen 900
goal Talk to Lilian.
await talk lilian
say Lilian@lilian|One step, two steps, ten steps, a hundred! Count with me! The Roof is waiting!
say Lilian@lilian|I tell stories to keep them moving. The trick is to make the stairs the story.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d32_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d32_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp teen 600
spawn lamp teen 1200
spawn lamp teen 1800
goal Collect the 3 glowing lamps on the Teen floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia lilian
cast amir 300
cast dalia 1200
cast lilian 1100
walk amir 560 6
walk dalia 760 5
walk lilian 900 4 wait
anim lilian twirl
anim amir sway
say |The kids reach the top out of breath, delighted, asking for the sequel.
bars off
scene off
endday

# ---- c5 DAY 33
script c5_33
title The Last Rail
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel float
say |On the Roof a final rail stands unfinished. A single bolt lies on the ground.
say Dalia@dalia|Ready when you are, Amir.
anim dalia bounce
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|ONE BOLT. ONE RAIL. ONE SAFE ASCENT. I HAVE WAITED FORTY YEARS TO SAY THIS. HOLD THE BOLT. PLEASE.
say Prime@prime|Everyone gathers. Nobody speaks. Everyone holds a hand on the rail.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d33_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d33_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia roof 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime sneak
anim amir bounce
say |Amir turns the bolt. The rail clicks. The whole building exhales.
bars off
scene off
endday

# ---- c5 DAY 34
script c5_34
title Dalia's Speech
bars on
scene roof amir gabriel amine
cast amir 300
cast gabriel 1100
cast amine 1250
walk amir 560 4
walk gabriel 760 5
walk amine 930 5 wait
emote gabriel !
anim amine tilt
say |Dalia climbs onto a crate on the Roof with a paper speech.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel clap
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc dalia roof 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|Ladies, gentlemen, bots! We climbed! We carried! We didn't scream! Much! I love you all!
say Dalia@dalia|It's a good speech. It was too long. It was perfect.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d34_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d34_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp roof 600
spawn lamp roof 1200
spawn lamp roof 1800
goal Collect the 3 glowing lamps on the Roof.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir gabriel dalia
cast amir 300
cast gabriel 1200
cast dalia 1100
walk amir 560 6
walk gabriel 760 5
walk dalia 900 4 wait
anim dalia dizzy
anim amir clap
say |Dalia bows. Gabriel claps first. She pretends not to see.
bars off
scene off
endday

# ---- c5 DAY 35
script c5_35
title Gabriel's Quiet Moment
bars on
scene roof amir dalia amine
cast amir 300
cast dalia 1100
cast amine 1250
walk amir 560 4
walk dalia 760 5
walk amine 930 5 wait
emote dalia !
anim amine shrug
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |Gabriel sits at the edge of the Roof, rope coiled at his side.
say Dalia@dalia|Ready when you are, Amir.
anim dalia zoomies
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc gabriel roof 900
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|I tied every knot. They hold. That's all I wanted. That the knots hold.
say Gabriel@gabriel|Amir. Thanks for coming with me. All the way up. It's... a lot, for me.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d35_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d35_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia roof 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1200
cast gabriel 1100
walk amir 560 6
walk dalia 760 5
walk gabriel 900 4 wait
anim gabriel salute
anim amir zoomies
say |Gabriel looks at the lake. His shoulders drop an inch. It's a big inch.
bars off
scene off
endday

# ---- c5 DAY 36
script c5_36
title Amine's Gift
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel hop
say |Amine hands Amir a small badge shaped like a stair.
say Dalia@dalia|Ready when you are, Amir.
anim dalia twirl
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc amine roof 900
goal Talk to Amine.
await talk amine
say Amine@amine|I made it. It's rubbish. It's yours. It says SAFE ASCENT in my worst handwriting.
say Amine@amine|I'll make you another when you're famous. Don't forget me.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c5_d36_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c5_d36_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp roof 600
spawn lamp roof 1200
spawn lamp roof 1800
goal Collect the 3 glowing lamps on the Roof.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir dalia amine
cast amir 300
cast dalia 1200
cast amine 1100
walk amir 560 6
walk dalia 760 5
walk amine 900 4 wait
anim amine dance
anim amir twirl
say |Amir pins the badge to his jacket. It's crooked. It's perfect.
bars off
scene off
endday

# ---- c5 DAY 37
script c5_37
title The Staircase Cake
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel sway
say |Alicia carries a cake with a tiny staircase of icing and a plastic bus on top.
say Dalia@dalia|Ready when you are, Amir.
anim dalia sneak
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc alicia lobby 900
goal Talk to Alicia.
await talk alicia
say Alicia@alicia|Big brother! It's the staircase cake! Jalil insisted on the bus! It's a stair bus!
say Alicia@alicia|She's five. The cake is leaning. The cake is magnificent.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c5_d37_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c5_d37_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lobby 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia alicia
cast amir 300
cast dalia 1200
cast alicia 1100
walk amir 560 6
walk dalia 760 5
walk alicia 900 4 wait
anim alicia cheer
anim amir sneak
say |Alicia cuts the first slice and hands it to a bot. The bot beams.
bars off
scene off
endday

# ---- c5 DAY 38
script c5_38
title The Inn Door
bars on
scene inn amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel bounce
say |At the Further inn, Sofia leaves the door open and hangs a lantern.
say Dalia@dalia|Ready when you are, Amir.
anim dalia dizzy
bars off
scene off
goal Take the elevator to the Further inn.
await floor inn
npc sofia inn 900
goal Talk to Sofia.
await talk sofia
say Sofia@sofia|It stays unlocked. For anyone. Coming up or going down. That's the Inn's rule.
say Sofia@sofia|The Ascent is for everybody. Even the ones who come later. Even the ones who haven't yet.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c5_d38_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c5_d38_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp inn 600
spawn lamp inn 1200
spawn lamp inn 1800
goal Collect the 3 glowing lamps on the Further inn.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia sofia
cast amir 300
cast dalia 1200
cast sofia 1100
walk amir 560 6
walk dalia 760 5
walk sofia 900 4 wait
anim sofia nod
anim amir dizzy
say |Sofia closes her eyes for a breath. She's very happy.
bars off
scene off
endday

# ---- c5 DAY 39
script c5_39
title The Building Hums
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel clap
say |The Roof is full. Every light is on. The hum of the building becomes a long warm chord.
say Dalia@dalia|Ready when you are, Amir.
anim dalia salute
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|THE BUILDING SAYS THANK YOU. IT SAYS: SAFE. IT SAYS: HOME. THE ASCENT IS COMPLETE.
say Prime@prime|I SWEPT THESE STAIRS FOR FORTY YEARS. NOW SOMEONE SWEPT THEM WITH ME. IT WAS THE BEST.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c5_d39_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c5_d39_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia roof 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime point
anim amir salute
say |Prime cries oil. He insists it's dust. Everyone lets him.
bars off
scene off
endday

# ---- c5 DAY 40
script c5_40
title Safe Ascent, Finally
bars on
scene roof amir gabriel amine
cast amir 300
cast gabriel 1100
cast amine 1250
walk amir 560 4
walk gabriel 760 5
walk amine 930 5 wait
emote gabriel !
anim amine zoomies
zoom 1.4 40 0.6 0.5
wait 50
zoom 1 30
wait 30
say |The sun rises over Reghaia. The lake is gold. The wires sing. Everyone is on the Roof.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel dance
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc dalia roof 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|We did it! We climbed, we fixed, we built, and I only screamed four times!
say Dalia@dalia|You screamed six. I counted. It was lovely. Welcome home.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c5_d40_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c5_d40_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp roof 600
spawn lamp roof 1200
spawn lamp roof 1800
goal Collect the 3 glowing lamps on the Roof.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir gabriel dalia
cast amir 300
cast gabriel 1200
cast dalia 1100
walk amir 560 6
walk gabriel 760 5
walk dalia 900 4 wait
anim dalia laugh
anim amir dance
say |The whole group watches the sunrise. Nobody says goodbye. They say tomorrow.
bars off
scene off
ending e_ascent
endday

)IL";