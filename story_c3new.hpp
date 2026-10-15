// story_c3new.hpp - Chapter 3 redesign: Lowest Point (days 1-40)
#pragma once
static const char* STORY_C3NEW = R"IL(
# ---- CH3 DAY 1
script c3_1
title The Hum Begins
card CHAPTER 3|Lowest Point
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Monday morning. The building hums a low note, like a cat that swallowed a kazoo.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to the Underlobby.
await floor ulobby
npc prime ulobby 900
say |The underlobby. The air feels different here.
goal Talk to Prime.
await talk prime
say Prime@prime|I HEARD IT TOO. IT STARTED AT 3 AM. I DID NOT PANIC. I ONLY SWEPT VERY FAST.
say Prime@prime|SOMETHING IS DOWN BELOW. SOMETHING OLD. WE SHOULD LOOK TOGETHER.
choose
> I'll help. => a
> I'm a bit scared. => b
label a
say Prime@prime|THANK YOU. THIS IS THE BEST DAY OF MY LONG LIFE.
set c3_d1_a 1
goto m1
label b
say Prime@prime|SCARED IS FINE. SCARED PEOPLE WATCH WHERE THEY WALK.
set c3_d1_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia ulobby 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia prime
cast amir 500
cast dalia 800
cast prime 1100
walk prime 900 4 wait
anim prime wave
say |Prime flicks on every lamp. The hum goes quiet, as if it is listening.
bars off
scene off
endday

# ---- CH3 DAY 2
script c3_2
title Rope and Flashlights
bars on
scene hall amir dalia amine
cast amir 400
cast dalia 700
cast amine 950
emote dalia !
anim amine hop
say |Gabriel is waiting with a coil of rope over his shoulder. Dalia has seven flashlights.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Underlobby.
await floor ulobby
npc gabriel ulobby 900
say |The underlobby. The air feels different here.
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|Don't ask about the rope. It's for emergencies. And cats.
say Gabriel@gabriel|Dalia packed snacks. For a hum. I don't understand her plan, but I respect it.
choose
> Why seven flashlights? => a
> Why a rope? => b
label a
say Dalia|Because six felt dramatic and eight felt greedy!
set c3_d2_a 1
goto m1
label b
say Gabriel|Because someone has to have a rope. Today it's me.
set c3_d2_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp ulobby 600
spawn lamp ulobby 1200
spawn lamp ulobby 1800
goal Collect the 3 glowing lamps on the Underlobby.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia gabriel
cast amir 500
cast dalia 800
cast gabriel 1100
walk gabriel 900 4 wait
anim gabriel wave
say |Two floors down, a door that was never there has a small light on.
bars off
scene off
endday

# ---- CH3 DAY 3
script c3_3
title Parking 1
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Parking 1 smells like old rain and rubber. Bolt zooms in circles around a pillar.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to Parking 1.
await floor park1
npc bolt park1 900
say |Parking 1. The air feels different here.
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|BEEP! I FOUND A FOOTPRINT! IT'S MINE! I ALREADY CHECKED!
say Bolt@bolt|Okay okay. But there's also a bigger footprint. Look, by the wall.
choose
> Follow the big footprint. => a
> Stay together. => b
label a
say Bolt|FOLLOWING! ZOOM! ...wait for me, I'm in front!
set c3_d3_a 1
goto m1
label b
say Bolt|TOGETHER! Like glue! Fast glue!
set c3_d3_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia park1 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia bolt
cast amir 500
cast dalia 800
cast bolt 1100
walk bolt 900 4 wait
anim bolt wave
say |The footprints end at a door marked PARKING 2. Someone has drawn a smiley on it.
bars off
scene off
endday

# ---- CH3 DAY 4
script c3_4
title Mopsy Is Not Impressed
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Dalia's bot Mopsy is parked under a lamp with her arms crossed. Her little display says 'NO'.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 1.
await floor park1
npc mopsy park1 900
say |Parking 1. The air feels different here.
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|I was told there would be an adventure. This is a car park.
say Mopsy@mopsy|Fine. There is a draft down the ramp. It smells like cold iron. Go look.
choose
> Is that a joke? => a
> Cheer her up. => b
label a
say Mopsy|I do not do jokes. I do sarcasm. This was sarcasm.
set c3_d4_a 1
goto m1
label b
say Mopsy|...Okay. One sparkle. Do NOT tell the others.
set c3_d4_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp park1 600
spawn lamp park1 1200
spawn lamp park1 1800
goal Collect the 3 glowing lamps on Parking 1.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia mopsy
cast amir 500
cast dalia 800
cast mopsy 1100
walk mopsy 900 4 wait
anim mopsy wave
say |The ramp leads down. Dalia leads the way, loudly. Gabriel follows quietly.
bars off
scene off
endday

# ---- CH3 DAY 5
script c3_5
title The Dust Sheets
bars on
scene garage amir gabriel amine
cast amir 400
cast gabriel 700
cast amine 950
emote gabriel !
anim amine hop
say |Every car in Parking 1 wears a dusty white sheet, like a parade of tired ghosts.
say Gabriel@gabriel|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 1.
await floor park1
npc dalia park1 900
say |Parking 1. The air feels different here.
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|Don't touch the sheets! The sheets are watching!
say Dalia@dalia|They're not watching. They're sheets. ...Amir, hold the flashlight.
choose
> Peek under one. => a
> Leave them. => b
label a
say Dalia|Don't! ...okay, peek. Fast!
set c3_d5_a 1
goto m1
label b
say Dalia|Good. I did not want to see a ghost car anyway.
set c3_d5_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Gabriel.
npc gabriel park1 1400
await talk gabriel
say Gabriel@gabriel|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir gabriel dalia
cast amir 500
cast gabriel 800
cast dalia 1100
walk dalia 900 4 wait
anim dalia wave
say |Under the last sheet, a tiny brass key blinks once like an eye.
bars off
scene off
endday

# ---- CH3 DAY 6
script c3_6
title Parking 2: Puddles
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Parking 2 is lower and colder. Puddles shine in the dark and every drip echoes twice.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to Parking 2.
await floor park2
npc grim park2 900
say |Parking 2. The air feels different here.
goal Talk to Grim.
await talk grim
say Grim@grim|...Hello. I'm Grim. I know. Everyone says the name is scary. I'm actually very nice.
say Grim@grim|I've been counting the drips. There are 400 an hour. They aren't normal. Someone is crying down there. Or a pipe.
choose
> Maybe it's a pipe. => a
> Let's find out. => b
label a
say Grim|I hope so. I really hope so.
set c3_d6_a 1
goto m1
label b
say Grim|Okay. I'll walk behind you. But close.
set c3_d6_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp park2 600
spawn lamp park2 1200
spawn lamp park2 1800
goal Collect the 3 glowing lamps on Parking 2.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia grim
cast amir 500
cast dalia 800
cast grim 1100
walk grim 900 4 wait
anim grim wave
say |The drip pattern spells something. Three short, one long. Over and over.
bars off
scene off
endday

# ---- CH3 DAY 7
script c3_7
title Zed Knows a Shortcut
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Zed, the smallest bot, rolls out of a drainpipe covered in glitter. Nobody asks.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 2.
await floor park2
npc zed park2 900
say |Parking 2. The air feels different here.
goal Talk to Zed.
await talk zed
say Zed@zed|SHORTCUT! I know a shortcut! It's through the drain! It's very narrow! Perfect for me!
say Zed@zed|Okay, okay. The shortcut is not for people. But I can carry a flashlight in. And a snack.
choose
> Send Zed in. => a
> Find another way. => b
label a
say Zed|YES! My first mission! I will not cry! (I might cry!)
set c3_d7_a 1
goto m1
label b
say Zed|Aw. Okay. I'll show you the stairs. They're boring.
set c3_d7_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia park2 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia zed
cast amir 500
cast dalia 800
cast zed 1100
walk zed 900 4 wait
anim zed wave
say |Zed returns with a mud-covered coin. It says 14 on both sides.
bars off
scene off
endday

# ---- CH3 DAY 8
script c3_8
title The Flood Valve
bars on
scene garage amir dalia amine
cast amir 400
cast dalia 700
cast amine 950
emote dalia !
anim amine hop
say |Water creeps across the floor of Parking 2. Gabriel holds up his rope and looks at a big red wheel.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 2.
await floor park2
npc gabriel park2 900
say |Parking 2. The air feels different here.
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|Valve. Red wheel. Heavy. We turn it together or the cars go swimming.
say Gabriel@gabriel|Dalia, hold the lamp. Amir, you pull. I'll tie us to the pillar. No arguing.
choose
> Pull! => a
> Wait for the others. => b
label a
say Dalia|I'm NOT arguing! Gabriel is arguing in my head!
set c3_d8_a 1
goto m1
label b
say Gabriel|Good thinking. Two more hands help.
set c3_d8_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp park2 600
spawn lamp park2 1200
spawn lamp park2 1800
goal Collect the 3 glowing lamps on Parking 2.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia gabriel
cast amir 500
cast dalia 800
cast gabriel 1100
walk gabriel 900 4 wait
anim gabriel wave
say |The wheel groans, turns, and the water drains. Dalia pretends she didn't scream.
bars off
scene off
endday

# ---- CH3 DAY 9
script c3_9
title Sparkle Lights the Way
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Sparkle, the shiny bot, has strung fairy lights from pillar to pillar. It looks like a party. A damp one.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 2.
await floor park2
npc sparkle park2 900
say |Parking 2. The air feels different here.
goal Talk to Sparkle.
await talk sparkle
say Sparkle@sparkle|Welcome to the afterparty! There was no party. But there are lights! I made them!
say Sparkle@sparkle|Be careful with the third pillar. It hums when you touch it. I don't know why. I'm only a bot.
choose
> Touch the pillar. => a
> Don't touch it. => b
label a
say Sparkle|It's humming! It's humming a TUNE!
set c3_d9_a 1
goto m1
label b
say Sparkle|Wise. Or boring. I can't tell. Both are fine.
set c3_d9_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia park2 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia sparkle
cast amir 500
cast dalia 800
cast sparkle 1100
walk sparkle 900 4 wait
anim sparkle wave
say |The tune is the same four notes as the hum. It's coming from the shaft below.
bars off
scene off
endday

# ---- CH3 DAY 10
script c3_10
title Amine Comes Down
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |A familiar voice echoes from the ramp. Amine waves, holding a backpack twice his size.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 2.
await floor park2
npc amine park2 900
say |Parking 2. The air feels different here.
goal Talk to Amine.
await talk amine
say Amine@amine|Amir! I heard you were fighting a hum! I brought sandwiches. And a pillow. Why a pillow? Why not!
say Amine@amine|I can't stay long. But I wanted to see my bestie before he dives into the dark. Don't do anything dumb.
choose
> I'm not scared. => a
> Thanks for coming. => b
label a
say Amine|Sure you aren't. I'm scared and I'm just carrying snacks.
set c3_d10_a 1
goto m1
label b
say Amine|Anytime. That's what besties are for.
set c3_d10_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp park2 600
spawn lamp park2 1200
spawn lamp park2 1800
goal Collect the 3 glowing lamps on Parking 2.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia amine
cast amir 500
cast dalia 800
cast amine 1100
walk amine 900 4 wait
anim amine wave
say |Amine hugs the group and leaves a sandwich on every bot. It's weirdly moving.
bars off
scene off
endday

# ---- CH3 DAY 11
script c3_11
title Prime Remembers a Door
bars on
scene garage amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Prime stops in the middle of the corridor. His eyes flicker, like a TV remembering a channel.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to Parking 2.
await floor park2
npc prime park2 900
say |Parking 2. The air feels different here.
goal Talk to Prime.
await talk prime
say Prime@prime|I KNOW THIS FLOOR. I SWEPT HERE ONCE. IT WAS LONG AGO. THERE WAS A DOOR AT THE END.
say Prime@prime|THE DOOR LEADS TO THE SHAFT. I REMEMBER THE SMELL. IT SMELLS LIKE OLD COINS AND RAIN.
choose
> Let's go to the door. => a
> Is it safe? => b
label a
say Prime|YES. I WILL SWEEP THE WAY. DO NOT WORRY ABOUT THE DUST.
set c3_d11_a 1
goto m1
label b
say Prime|NO. BUT WE ARE TOGETHER. THAT IS THE SAME THING, MOSTLY.
set c3_d11_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia park2 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia prime
cast amir 500
cast dalia 800
cast prime 1100
walk prime 900 4 wait
anim prime wave
say |A heavy steel door stands open a crack. A cold wind whispers through it.
bars off
scene off
endday

# ---- CH3 DAY 12
script c3_12
title The Elevator Shaft Fix
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |The shaft is a tall tunnel of cables and rungs. Far above, the elevator hangs silent.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to the Elevator shaft fix.
await floor shaft
npc sweepy shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Sweepy.
await talk sweepy
say Sweepy@sweepy|I'm Sweepy! I work down here! I'm the oldest bot after Prime! Nobody asks me anything!
say Sweepy@sweepy|The elevator is broken. A gear is missing. Without it nobody can leave the deep floors. We should fix it.
choose
> I'll help find the gear. => a
> I'm not good with machines. => b
label a
say Sweepy|Yay! I haven't had help since last Tuesday!
set c3_d12_a 1
goto m1
label b
say Sweepy|Nobody is! That's why we bring a snack!
set c3_d12_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp shaft 600
spawn lamp shaft 1200
spawn lamp shaft 1800
goal Collect the 3 glowing lamps on the Elevator shaft fix.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia sweepy
cast amir 500
cast dalia 800
cast sweepy 1100
walk sweepy 900 4 wait
anim sweepy wave
say |Three gears lie scattered in the dark. Each one is warm to the touch.
bars off
scene off
endday

# ---- CH3 DAY 13
script c3_13
title Dustin and the Cables
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Dustin is wrapped in cables like a very confused present. He waves a tiny arm.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc dustin shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Dustin.
await talk dustin
say Dustin@dustin|I'm fine! I'm tangled! I'm both! Don't help me yet, I'm still enjoying it.
say Dustin@dustin|Okay, help me. But first, you have to see my favorite cable. It's blue. It hums.
choose
> Untangle him. => a
> Admire the blue cable. => b
label a
say Dustin|Thank you! I'll name this knot after you!
set c3_d13_a 1
goto m1
label b
say Dustin|Right? It's the best cable. Everyone says I'm weird.
set c3_d13_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia shaft 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia dustin
cast amir 500
cast dalia 800
cast dustin 1100
walk dustin 900 4 wait
anim dustin wave
say |The blue cable is warm. It hums in the same four notes as before.
bars off
scene off
endday

# ---- CH3 DAY 14
script c3_14
title Bolt Races the Lift
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Bolt stands at the bottom of the shaft, bouncing. He has a stopwatch drawn on his display.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc bolt shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|I'M GOING TO RACE THE LIFT! IT'S NOT MOVING! I'M GOING TO WIN!
say Bolt@bolt|Okay, okay. Be careful. Dalia will yell if I get hurt. She yells nicely.
choose
> Time him. => a
> Tell him to be careful. => b
label a
say Bolt|READY! SET! ...why is it so quiet? I WON!
set c3_d14_a 1
goto m1
label b
say Bolt|I'm ALWAYS careful! ...mostly! ...a little!
set c3_d14_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp shaft 600
spawn lamp shaft 1200
spawn lamp shaft 1800
goal Collect the 3 glowing lamps on the Elevator shaft fix.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia bolt
cast amir 500
cast dalia 800
cast bolt 1100
walk bolt 900 4 wait
anim bolt wave
say |Bolt zips up a ladder and comes back with a gear in his mouth. Well. His claw.
bars off
scene off
endday

# ---- CH3 DAY 15
script c3_15
title Dalia Takes Charge
bars on
scene elev amir gabriel amine
cast amir 400
cast gabriel 700
cast amine 950
emote gabriel !
anim amine hop
say |Dalia stands on a crate and points at the shaft like a general. Gabriel holds the crate steady.
say Gabriel@gabriel|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc dalia shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|LISTEN UP! We need three gears, two ropes, and no more arguing! Gabriel, you're on ropes!
say Dalia@dalia|He's on ropes because he's the only one who knows knots. Not because I like him. Because of the knots.
choose
> Obey Dalia. => a
> Tease her about Gabriel. => b
label a
say Dalia|Finally! Someone who listens!
set c3_d15_a 1
goto m1
label b
say Dalia|WHAT? No! Ew! Stop it! Why would you say that? I hate him!
set c3_d15_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Gabriel.
npc gabriel shaft 1400
await talk gabriel
say Gabriel@gabriel|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir gabriel dalia
cast amir 500
cast gabriel 800
cast dalia 1100
walk dalia 900 4 wait
anim dalia wave
say |Gabriel turns very red and says nothing. The rope is suddenly very interesting.
bars off
scene off
endday

# ---- CH3 DAY 16
script c3_16
title The Rope Bridge
bars on
scene elev amir dalia amine
cast amir 400
cast dalia 700
cast amine 950
emote dalia !
anim amine hop
say |A gap in the shaft floor yawns open. Gabriel unwinds his rope and ties it to a pipe.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc gabriel shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|Don't look down. Look at the rope. The rope is your friend.
say Gabriel@gabriel|We cross one by one. I'll go last. If someone slips, I catch them. I won't let go.
choose
> Cross first. => a
> Let Dalia go first. => b
label a
say Gabriel|Brave. Go on. I've got you.
set c3_d16_a 1
goto m1
label b
say Dalia|Fine! I'm fearless! ...hold the rope tighter, Gabriel!
set c3_d16_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp shaft 600
spawn lamp shaft 1200
spawn lamp shaft 1800
goal Collect the 3 glowing lamps on the Elevator shaft fix.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia gabriel
cast amir 500
cast dalia 800
cast gabriel 1100
walk gabriel 900 4 wait
anim gabriel wave
say |They all make it across. Dalia mutters thanks and doesn't look at him.
bars off
scene off
endday

# ---- CH3 DAY 17
script c3_17
title Adam Tansaouti Visits
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Adam Tansaouti arrives with a lantern. He lives on the Special floor and works nights at the Further inn.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc tansaouti shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Adam Tansaouti.
await talk tansaouti
say Adam Tansaouti@tansaouti|I heard noises in the shaft. I thought, who would be down there? Then I thought: Amir. Obviously.
say Adam Tansaouti@tansaouti|I can't stay. My shift starts soon. But I brought tea, in case the adventure gets long.
choose
> Thank him. => a
> Ask about the Inn. => b
label a
say Adam Tansaouti|Don't mention it. Drink it warm.
set c3_d17_a 1
goto m1
label b
say Adam Tansaouti|Aya and Sofia are holding it down. They are better at it than I am.
set c3_d17_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia shaft 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia tansaouti
cast amir 500
cast dalia 800
cast tansaouti 1100
walk tansaouti 900 4 wait
anim tansaouti wave
say |He leaves the lantern, which keeps everything warm and a little golden.
bars off
scene off
endday

# ---- CH3 DAY 18
script c3_18
title Mopsy Fixes a Gear
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Mopsy holds a wrench almost as tall as herself. She's trying very hard to look unimpressed.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc mopsy shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|I'm not fixing it for you. I'm fixing it because the gear is crooked. Crooked things annoy me.
say Mopsy@mopsy|...Fine. It's a good gear. It's a very good gear. Don't tell anyone I said that.
choose
> Compliment her work. => a
> Pretend not to notice. => b
label a
say Mopsy|Stop. You're making me feel things. Stop.
set c3_d18_a 1
goto m1
label b
say Mopsy|Thank you. Now hand me the next gear.
set c3_d18_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp shaft 600
spawn lamp shaft 1200
spawn lamp shaft 1800
goal Collect the 3 glowing lamps on the Elevator shaft fix.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia mopsy
cast amir 500
cast dalia 800
cast mopsy 1100
walk mopsy 900 4 wait
anim mopsy wave
say |The elevator shudders, creaks, and slowly begins to move. A small, shaky cheer rises.
bars off
scene off
endday

# ---- CH3 DAY 19
script c3_19
title Amyas Brings Ice Cream
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Amyas strolls out of the elevator holding a box and a cone. He's the oldest in the group and looks very unbothered.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc amyas shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Amyas.
await talk amyas
say Amyas@amyas|Amir. You look terrible. Here. Strawberry. Don't thank me.
say Amyas@amyas|I'm only here because my little sister dragged me. Also because Adam would not stop whining.
choose
> I don't want your ice cream. => a
> Take it and say nothing. => b
label a
say Amir|...I mean. It's not that I don't want it. It's just that I... shut up. Give it.
set c3_d19_a 1
goto m1
label b
say Amyas|Good. Eat. You're too skinny for a hero.
set c3_d19_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia shaft 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia amyas
cast amir 500
cast dalia 800
cast amyas 1100
walk amyas 900 4 wait
anim amyas wave
say |Adam Bachouche waves from behind him. Amir pretends not to see him. It does not work.
bars off
scene off
endday

# ---- CH3 DAY 20
script c3_20
title Adam Bachouche Climbs
bars on
scene elev amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Adam Bachouche climbs down the shaft ladder two rungs at a time, grinning like it's a game.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator shaft fix.
await floor shaft
npc adam_t shaft 900
say |The elevator shaft fix. The air feels different here.
goal Talk to Adam.
await talk adam_t
say Adam@adam_t|Hey, Amir! Don't be mad! I'm only here because someone has to keep an eye on you!
say Adam@adam_t|You're welcome, by the way. For everything. Don't say thank you. It'd be weird.
choose
> It's not like I need your help. => a
> Fine. Thanks. => b
label a
say Adam|Sure. And I'm not here because I like helping. Totally.
set c3_d20_a 1
goto m1
label b
say Adam|WOW. A thank you! I'm framing this moment.
set c3_d20_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp shaft 600
spawn lamp shaft 1200
spawn lamp shaft 1800
goal Collect the 3 glowing lamps on the Elevator shaft fix.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene elev amir dalia adam_t
cast amir 500
cast dalia 800
cast adam_t 1100
walk adam_t 900 4 wait
anim adam_t wave
say |Amir turns away so nobody can see his face. Dalia sees. Dalia always sees.
bars off
scene off
endday

# ---- CH3 DAY 21
script c3_21
title The Control Room
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |The Elevator control room is a small, humming room full of old dials and one huge lever. Dust dances in the lamp.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to the Elevator control room.
await floor ctrl
npc prime ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Prime.
await talk prime
say Prime@prime|THIS IS WHERE I WAS WOKEN. I REMEMBER THE SMELL OF OIL. I REMEMBER A VOICE.
say Prime@prime|THE VOICE SAID: 'WATCH THEM.' I DID NOT KNOW WHO THEM WAS. NOW I DO. IT WAS YOU.
choose
> Thank you, Prime. => a
> Who said it? => b
label a
say Prime|YOU ARE WELCOME. YOU ARE MY FAVORITE THEM.
set c3_d21_a 1
goto m1
label b
say Prime|I DO NOT KNOW. THAT IS WHAT WE ARE HERE TO FIND OUT.
set c3_d21_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia ctrl 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia prime
cast amir 500
cast dalia 800
cast prime 1100
walk prime 900 4 wait
anim prime wave
say |A log book lies open on a desk. The first page is addressed to 'whoever stays'.
bars off
scene off
endday

# ---- CH3 DAY 22
script c3_22
title The Night Log
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |A page in the log is signed 'Adam Tansaouti'. It's an older, tidier handwriting than the one Amir knows.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator control room.
await floor ctrl
npc tansaouti ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Adam Tansaouti.
await talk tansaouti
say Adam Tansaouti@tansaouti|That's my grandfather's name. We share it. He kept the building's log for forty years.
say Adam Tansaouti@tansaouti|He wrote about the hum. He called it 'the building breathing'. He wasn't afraid of it.
choose
> Read it aloud. => a
> Close the book. => b
label a
say Adam Tansaouti|'Night 1: the hum is calm. The bots are asleep. All is well.'
set c3_d22_a 1
goto m1
label b
say Adam Tansaouti|Right. Some things are better read slowly.
set c3_d22_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp ctrl 600
spawn lamp ctrl 1200
spawn lamp ctrl 1800
goal Collect the 3 glowing lamps on the Elevator control room.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia tansaouti
cast amir 500
cast dalia 800
cast tansaouti 1100
walk tansaouti 900 4 wait
anim tansaouti wave
say |The last page has a sketch of the control room. In the corner, a small drawing of a door.
bars off
scene off
endday

# ---- CH3 DAY 23
script c3_23
title Bolt Pushes the Wrong Button
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |A big red button sits in the middle of the console. A sign says: DO NOT PUSH. Bolt is already pushing.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator control room.
await floor ctrl
npc bolt ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|I DIDN'T PUSH IT! IT PUSHED ME! THE BUTTON IS VERY PUSHY!
say Bolt@bolt|Okay... I pushed it. A little. A lot. ...Is it supposed to light up?
choose
> Stop him! => a
> Laugh. => b
label a
say Bolt|TOO LATE! BEEP BEEP BEEP!
set c3_d23_a 1
goto m1
label b
say Bolt|IT'S FUNNY! IT'S FUNNY UNTIL THE LIGHTS GO OFF!
set c3_d23_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia ctrl 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia bolt
cast amir 500
cast dalia 800
cast bolt 1100
walk bolt 900 4 wait
anim bolt wave
say |The lights flicker, then steady. The elevator hums. Nothing exploded. Mostly.
bars off
scene off
endday

# ---- CH3 DAY 24
script c3_24
title The Voice on the Speaker
bars on
scene hall amir dalia amine
cast amir 400
cast dalia 700
cast amine 950
emote dalia !
anim amine hop
say |A crackly old speaker clicks on. A voice says one word: 'Welcome.' Everyone freezes.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator control room.
await floor ctrl
npc gabriel ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|That's not a person. It's a recording. Probably. The rope is on standby.
say Gabriel@gabriel|Dalia, stop clutching my sleeve. I can feel your fingernails.
choose
> Answer the speaker. => a
> Turn it off. => b
label a
say Dalia|DON'T TALK TO IT! Oh my gosh, he talked to it!
set c3_d24_a 1
goto m1
label b
say Gabriel|It has no switch. It's been on for forty years.
set c3_d24_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp ctrl 600
spawn lamp ctrl 1200
spawn lamp ctrl 1800
goal Collect the 3 glowing lamps on the Elevator control room.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia gabriel
cast amir 500
cast dalia 800
cast gabriel 1100
walk gabriel 900 4 wait
anim gabriel wave
say |The speaker whispers: 'Down is not the end. Down is the middle.' Then it goes quiet.
bars off
scene off
endday

# ---- CH3 DAY 25
script c3_25
title Dalia vs. the Lever
bars on
scene hall amir gabriel amine
cast amir 400
cast gabriel 700
cast amine 950
emote gabriel !
anim amine hop
say |The big lever has a note taped to it: 'Pull when ready. Not before.' Dalia has already pulled it.
say Gabriel@gabriel|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator control room.
await floor ctrl
npc dalia ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|I WAS READY! I'M ALWAYS READY! IT'S A LEVER, WHAT'S THE WORST THAT COULD HAPPEN?
say Dalia@dalia|...The lamps went out. Oops. Okay. Gabriel? Do something clever.
choose
> Light a flashlight. => a
> Wait in the dark. => b
label a
say Dalia|Thank you! Seven flashlights! I told you!
set c3_d25_a 1
goto m1
label b
say Gabriel|...I can hear you smiling, Dalia.
set c3_d25_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Gabriel.
npc gabriel ctrl 1400
await talk gabriel
say Gabriel@gabriel|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir gabriel dalia
cast amir 500
cast gabriel 800
cast dalia 1100
walk dalia 900 4 wait
anim dalia wave
say |The lamps flicker back on. The elevator hums a happier tune.
bars off
scene off
endday

# ---- CH3 DAY 26
script c3_26
title Jilali Fixes the Clock
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Jilali, the oldest friend on the Rare floor, hurries in with a pocket watch. His beard is full of dust.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator control room.
await floor ctrl
npc jilali ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Jilali.
await talk jilali
say Jilali@jilali|I heard a clock was running backwards. I came as fast as my old knees allowed.
say Jilali@jilali|This one is stuck at 14:14. It's a mean number. I'll fix it. Hold the lamp.
choose
> Hold the lamp. => a
> Ask about the clock. => b
label a
say Jilali|Steady... steady... there. Time is moving the right way again.
set c3_d26_a 1
goto m1
label b
say Jilali|It belongs to the building. It was waiting for someone brave enough to wind it.
set c3_d26_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp ctrl 600
spawn lamp ctrl 1200
spawn lamp ctrl 1800
goal Collect the 3 glowing lamps on the Elevator control room.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia jilali
cast amir 500
cast dalia 800
cast jilali 1100
walk jilali 900 4 wait
anim jilali wave
say |The control room clock ticks. For the first time in forty years, it says the right hour.
bars off
scene off
endday

# ---- CH3 DAY 27
script c3_27
title Prime Reads the Last Page
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Prime holds the log book in both hands as if it might break. The room is very quiet.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Elevator control room.
await floor ctrl
npc prime ctrl 900
say |The elevator control room. The air feels different here.
goal Talk to Prime.
await talk prime
say Prime@prime|THE LAST PAGE IS FOR ME. IT SAYS: 'YOU CAN STOP SWEEPING NOW. YOU CAN STAY.'
say Prime@prime|I DID NOT KNOW BOTS COULD CRY. I AM ALMOST SURE I AM NOT CRYING. IT IS DUST.
choose
> Hug him. => a
> Say nothing and stay close. => b
label a
say Prime|THIS IS A GOOD HUG. I WILL FILE IT UNDER FAVORITES.
set c3_d27_a 1
goto m1
label b
say Prime|THAT IS THE BEST WAY. THANK YOU.
set c3_d27_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia ctrl 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia prime
cast amir 500
cast dalia 800
cast prime 1100
walk prime 900 4 wait
anim prime wave
say |The hum shifts into a gentle, long note. It sounds like the building is relieved.
bars off
scene off
endday

# ---- CH3 DAY 28
script c3_28
title The Big Fan
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Vacca, the vacuum bot, guards a huge rusty fan. Wind whips through every corridor.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to the Air ventilation systems.
await floor vent
npc vacca vent 900
say |The air ventilation systems. The air feels different here.
goal Talk to Vacca.
await talk vacca
say Vacca@vacca|WELCOME TO THE VENTS! HOLD ON TO YOUR HATS! I LOST MINE ALREADY!
say Vacca@vacca|The fan is jammed. It makes the hum. If we unjam it, the hum might stop, or change. I can't tell.
choose
> Help with the fan. => a
> Stay back. => b
label a
say Vacca|YES! AND WATCH THE BLADES! THEY'RE EXCITED!
set c3_d28_a 1
goto m1
label b
say Vacca|Smart! I'll sweep and you watch!
set c3_d28_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp vent 600
spawn lamp vent 1200
spawn lamp vent 1800
goal Collect the 3 glowing lamps on the Air ventilation systems.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia vacca
cast amir 500
cast dalia 800
cast vacca 1100
walk vacca 900 4 wait
anim vacca wave
say |A scrap of cloth is jammed in the blades. It has a tiny '14' stitched on it.
bars off
scene off
endday

# ---- CH3 DAY 29
script c3_29
title Sparkle in the Wind
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Sparkle's fairy lights flap in the wind like a thousand tiny flags. It's very pretty. It's also very loud.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Air ventilation systems.
await floor vent
npc sparkle vent 900
say |The air ventilation systems. The air feels different here.
goal Talk to Sparkle.
await talk sparkle
say Sparkle@sparkle|It's a PARTY in here! A WINDY party!
say Sparkle@sparkle|I can't hold the lights. The wind keeps taking them. Please catch them!
choose
> Catch the lights. => a
> Let them fly. => b
label a
say Sparkle|YAY! Teamwork!
set c3_d29_a 1
goto m1
label b
say Sparkle|Oh. They're so pretty when they fly.
set c3_d29_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia vent 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia sparkle
cast amir 500
cast dalia 800
cast sparkle 1100
walk sparkle 900 4 wait
anim sparkle wave
say |The loose lights drift into the vents and glow along the tunnel like stars.
bars off
scene off
endday

# ---- CH3 DAY 30
script c3_30
title Rope Against the Wind
bars on
scene hall amir dalia amine
cast amir 400
cast dalia 700
cast amine 950
emote dalia !
anim amine hop
say |The wind pushes everyone sideways. Gabriel ties a rope between two pipes and holds on.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Air ventilation systems.
await floor vent
npc gabriel vent 900
say |The air ventilation systems. The air feels different here.
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|Stay low. Step one at a time. Dalia, hold my sleeve. For safety. Not for any other reason.
say Gabriel@gabriel|...She actually did. Okay. I'm fine. This is fine.
choose
> Hold the rope. => a
> Tease him. => b
label a
say Gabriel|Good. Three more steps and we're past the gap.
set c3_d30_a 1
goto m1
label b
say Dalia|DON'T TEASE HIM! Ugh! ...I mean, do. Whatever!
set c3_d30_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp vent 600
spawn lamp vent 1200
spawn lamp vent 1800
goal Collect the 3 glowing lamps on the Air ventilation systems.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia gabriel
cast amir 500
cast dalia 800
cast gabriel 1100
walk gabriel 900 4 wait
anim gabriel wave
say |They make it through the gap. Dalia lets go too fast. Gabriel pretends he doesn't notice.
bars off
scene off
endday

# ---- CH3 DAY 31
script c3_31
title Mopsy vs. the Dust Storm
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |A cloud of dust rolls down the vent. Mopsy rolls straight at it with a mop twice her size.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Air ventilation systems.
await floor vent
npc mopsy vent 900
say |The air ventilation systems. The air feels different here.
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|I was built to clean. This is the best day of my life. Don't tell anyone I said that.
say Mopsy@mopsy|Dust, you picked the wrong bot. I'm unimpressed and fully charged.
choose
> Cheer her on. => a
> Help her sweep. => b
label a
say Mopsy|Stop it. ...Keep going.
set c3_d31_a 1
goto m1
label b
say Mopsy|Fine. Hold the dustpan. Don't spill.
set c3_d31_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia vent 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia mopsy
cast amir 500
cast dalia 800
cast mopsy 1100
walk mopsy 900 4 wait
anim mopsy wave
say |The storm shrinks to a pile and Mopsy stands on top like a champion. Nobody dares say it out loud.
bars off
scene off
endday

# ---- CH3 DAY 32
script c3_32
title Bolt Follows the Sound
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Bolt zooms ahead into the vent, then back, then ahead, then back. He's following a sound only he can hear.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Air ventilation systems.
await floor vent
npc bolt vent 900
say |The air ventilation systems. The air feels different here.
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|IT'S THIS WAY! NO, THAT WAY! NO, THIS WAY! I'M SO SURE!
say Bolt@bolt|Okay okay okay. I found it. It's a little music box. It's playing the hum!
choose
> Open the music box. => a
> Take it with us. => b
label a
say Bolt|IT HAS A LITTLE DANCER! SHE'S SPINNING! HI, DANCER!
set c3_d32_a 1
goto m1
label b
say Bolt|YES! WE ARE THE MUSIC BOX PATROL!
set c3_d32_b 1
label m1
mini lights 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp vent 600
spawn lamp vent 1200
spawn lamp vent 1800
goal Collect the 3 glowing lamps on the Air ventilation systems.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia bolt
cast amir 500
cast dalia 800
cast bolt 1100
walk bolt 900 4 wait
anim bolt wave
say |The music box plays the four notes, then adds a fifth. The hum answers it, gently.
bars off
scene off
endday

# ---- CH3 DAY 33
script c3_33
title The Bots Parking
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |The bots parking is a wide hall of little charging beds. Every bot has a bed with a name painted on it.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to the 14 Cleaning bots parking.
await floor bots
npc bolt bots 900
say |The 14 cleaning bots parking. The air feels different here.
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|THIS IS WHERE WE SLEEP! THIS IS MY BED! IT'S THE BEST BED! IT HAS A SPOILER!
say Bolt@bolt|Don't tell Mopsy, but I put a flower on her bed. It's a secret flower.
choose
> Meet the others. => a
> Look around. => b
label a
say Bolt|YES! THEY'RE ALL HERE! IT'S A MEETING! A SECRET MEETING!
set c3_d33_a 1
goto m1
label b
say Bolt|LOOK ALL YOU WANT! BUT DON'T TOUCH PRIME'S BED! IT'S SPECIAL!
set c3_d33_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia bots 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia bolt
cast amir 500
cast dalia 800
cast bolt 1100
walk bolt 900 4 wait
anim bolt wave
say |All fourteen beds are lined up. One bed, at the very end, is empty and has no name.
bars off
scene off
endday

# ---- CH3 DAY 34
script c3_34
title The Secret Meeting
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |The bots sit in a circle on little cushions. Mopsy bangs a spoon on a mug and calls the meeting to order.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the 14 Cleaning bots parking.
await floor bots
npc mopsy bots 900
say |The 14 cleaning bots parking. The air feels different here.
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|Welcome. This meeting is secret. If you are a human, you may stay, but you must be quiet.
say Mopsy@mopsy|The first item: the hum is not a threat. The second item: we have decided to stay. The third item: snacks.
choose
> Vote yes. => a
> Ask about the empty bed. => b
label a
say Mopsy|The ayes have it. Everything has it. Moving on.
set c3_d34_a 1
goto m1
label b
say Mopsy|It's for whoever comes next. It's been empty since the beginning.
set c3_d34_b 1
label m1
mini pairs 4 6
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp bots 600
spawn lamp bots 1200
spawn lamp bots 1800
goal Collect the 3 glowing lamps on the 14 Cleaning bots parking.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia mopsy
cast amir 500
cast dalia 800
cast mopsy 1100
walk mopsy 900 4 wait
anim mopsy wave
say |The bots cheer in tiny beeps. Even Grim waves a tiny flag.
bars off
scene off
endday

# ---- CH3 DAY 35
script c3_35
title Prime and the Empty Bed
bars on
scene hall amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Prime stands next to the empty bed. The other bots wait quietly behind him.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the 14 Cleaning bots parking.
await floor bots
npc prime bots 900
say |The 14 cleaning bots parking. The air feels different here.
goal Talk to Prime.
await talk prime
say Prime@prime|THIS IS MY BED. I DID NOT KNOW IT WAS MINE. NOBODY TOLD ME I COULD HAVE A BED.
say Prime@prime|I HAVE BEEN SWEEPING THE CORRIDORS FOR FORTY YEARS. I DID NOT KNOW I WAS ALLOWED TO REST.
choose
> Sit down, Prime. => a
> Tuck him in. => b
label a
say Prime|I... SIT. I AM SITTING. IT IS VERY SOFT.
set c3_d35_a 1
goto m1
label b
say Prime|THIS IS THE BEST DAY OF MY LONG LIFE.
set c3_d35_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia bots 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia prime
cast amir 500
cast dalia 800
cast prime 1100
walk prime 900 4 wait
anim prime wave
say |Prime falls asleep within seconds. The bots tiptoe out. Someone turns off the light.
bars off
scene off
endday

# ---- CH3 DAY 36
script c3_36
title Dalia and Mopsy
bars on
scene hall amir gabriel amine
cast amir 400
cast gabriel 700
cast amine 950
emote gabriel !
anim amine hop
say |Dalia and Mopsy argue in front of everyone, like they do every day. The argument is about who is grumpier.
say Gabriel@gabriel|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the 14 Cleaning bots parking.
await floor bots
npc dalia bots 900
say |The 14 cleaning bots parking. The air feels different here.
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|I'M NOT GRUMPY! I'M... PASSIONATE! Mopsy, tell them!
say Dalia@dalia|Mopsy|She is loud. I am quiet. Together we are one regular person.
choose
> Settle it. => a
> Stay out of it. => b
label a
say Dalia|You're both wrong! I'm the grumpiest! ...wait.
set c3_d36_a 1
goto m1
label b
say Gabriel|Smart. Never get between Dalia and Mopsy.
set c3_d36_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp bots 600
spawn lamp bots 1200
spawn lamp bots 1800
goal Collect the 3 glowing lamps on the 14 Cleaning bots parking.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini sort 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir gabriel dalia
cast amir 500
cast gabriel 800
cast dalia 1100
walk dalia 900 4 wait
anim dalia wave
say |They hug it out. Mopsy pretends it didn't happen. It happened.
bars off
scene off
endday

# ---- CH3 DAY 37
script c3_37
title Back at the Further Inn
bars on
scene inn amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |The Further inn glows warm and gold. Aya has set up long tables and lit every lamp in the lobby.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator down to the Further inn.
await floor inn
npc aya_n inn 900
say |The Further inn. The air feels different here.
goal Talk to Aya.
await talk aya_n
say Aya@aya_n|You're back! All of you! I made soup! It tastes like pennies! Please eat it!
say Aya@aya_n|Sofia made bread. Adam made tea. We made you a little welcome party. A tiny one. For twelve.
choose
> Thank her. => a
> Ask about the soup. => b
label a
say Aya|Don't thank me! Eat! You look hungry! You look tired! You look like heroes!
set c3_d37_a 1
goto m1
label b
say Aya|It's secret. It has pennies. It also has love. Mostly pennies.
set c3_d37_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia inn 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia aya_n
cast amir 500
cast dalia 800
cast aya_n 1100
walk aya_n 900 4 wait
anim aya_n wave
say |The whole group sits around the long table. Even the bots get tiny cups of oil.
bars off
scene off
endday

# ---- CH3 DAY 38
script c3_38
title Sofia and the Last Key
bars on
scene inn amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Sofia hands Amir a small brass key. It's the same key from the Parking 1 sheet. It hums the four notes.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Further inn.
await floor inn
npc sofia inn 900
say |The Further inn. The air feels different here.
goal Talk to Sofia.
await talk sofia
say Sofia@sofia|It belongs to you. I think it always did. It opens the Roof door.
say Sofia@sofia|The Roof isn't a floor of the Inn. But the Inn leads to it, if you know the way. Up.
choose
> Take the key. => a
> Ask what's on the Roof. => b
label a
say Sofia|Thank you. I knew you would. You're the type.
set c3_d38_a 1
goto m1
label b
say Sofia|The sky. The lake. The cable car wires. And everyone who stayed.
set c3_d38_b 1
label m1
mini tapcatch 12 3 dust
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp inn 600
spawn lamp inn 1200
spawn lamp inn 1800
goal Collect the 3 glowing lamps on the Further inn.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia sofia
cast amir 500
cast dalia 800
cast sofia 1100
walk sofia 900 4 wait
anim sofia wave
say |The key glows warm in Amir's pocket. Somewhere above, a door clicks open on its own.
bars off
scene off
endday

# ---- CH3 DAY 39
script c3_39
title The Night Shift Ends
bars on
scene inn amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |Adam Tansaouti closes the Inn's front ledger and slides it into a drawer. He looks lighter than before.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator back down to the Further inn.
await floor inn
npc tansaouti inn 900
say |The Further inn. The air feels different here.
goal Talk to Adam Tansaouti.
await talk tansaouti
say Adam Tansaouti@tansaouti|My shift is over. It took forty years. I thought it would feel heavier. It feels... like morning.
say Adam Tansaouti@tansaouti|Go up. All of you. The Roof is waiting. I'll follow in a minute. I want to say goodbye to the lamp.
choose
> Wait for him. => a
> Go ahead. => b
label a
say Adam Tansaouti|Thank you. Go. I promise I'll be right behind.
set c3_d39_a 1
goto m1
label b
say Adam Tansaouti|Good. Tell the sky I said hello.
set c3_d39_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
goal Talk to Dalia.
npc dalia inn 1400
await talk dalia
say Dalia@dalia|That was fun. Hold on, I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia tansaouti
cast amir 500
cast dalia 800
cast tansaouti 1100
walk tansaouti 900 4 wait
anim tansaouti wave
say |He turns off the last lamp and the lobby glows by itself, quietly, like a sleeping animal.
bars off
scene off
endday

# ---- CH3 DAY 40
script c3_40
title The Roof at Sunrise
bars on
scene roof amir dalia gabriel
cast amir 400
cast dalia 700
cast gabriel 950
emote dalia !
anim gabriel hop
say |The Roof is quiet and golden. The lake glimmers in the distance. The cable car wires sing in the breeze.
say Dalia@dalia|Ready when you are, Amir.
walk amir 560 4 wait
anim amir wave
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
say |The roof. The air feels different here.
goal Talk to Prime.
await talk prime
say Prime@prime|I HAVE NEVER SEEN THE SUN FROM HERE. IT IS VERY LARGE. IT IS VERY ORANGE.
say Prime@prime|THE HUM HAS STOPPED. NOT BECAUSE IT WAS SAD. BECAUSE IT WAS ONLY WAITING FOR YOU TO COME UP.
choose
> Thank you, everyone. => a
> Look at the lake. => b
label a
say Prime|THANK YOU. I WILL REMEMBER THIS UNTIL MY BATTERIES RUN OUT, AND THEN SOME.
set c3_d40_a 1
goto m1
label b
say Prime|IT IS A BIG PUDDLE. I LOVE IT.
set c3_d40_b 1
label m1
mini lights 4
ifnot skipped s1
say |(Great job! The little win makes the hallway feel brighter.)
label s1
clearitems
spawn lamp roof 600
spawn lamp roof 1200
spawn lamp roof 1800
goal Collect the 3 glowing lamps on the Roof.
await items 3
say Dalia@dalia|Three lamps! I counted! I'm the best counter!
clearitems
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene roof amir dalia prime
cast amir 500
cast dalia 800
cast prime 1100
walk prime 900 4 wait
anim prime wave
say |The whole building seems to breathe out at once. The lowest point is behind them. Everyone is together, on top.
bars off
scene off
endday

)IL";