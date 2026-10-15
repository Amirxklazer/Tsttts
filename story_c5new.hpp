// generated c5
#pragma once
static const char* STORY_C5NEW = R"IL(
# ---- c5 DAY 1
script c5_1
title Safe Ascent: The Rope
card CHAPTER 5|Safe Ascent (PREVIEW)
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
zoom 1.5 50 0.6 0.5
emote dalia !
anim gabriel dance
wait 60
zoom 1 40
wait 40
say |A fresh morning. A long rope runs from the Roof down through the stairwell. A tag on it says: SAFE ASCENT - PART 1.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|I HAVE BEEN TOLD TO TELL YOU: THIS IS A PREVIEW. THE REAL CLIMB IS STILL BEING BUILT.
say Prime@prime|Gabriel tested the rope. It holds. It is also suspiciously soft.
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
say |The rope sways gently. It feels like an invitation.
bars off
scene off
endday

# ---- c5 DAY 2
script c5_2
title Safe Ascent: The Stairs
bars on
scene hall amir gabriel amine
cast amir 300
cast gabriel 1100
cast amine 1250
walk amir 560 4
walk gabriel 760 5
walk amine 930 5 wait
emote gabriel !
anim amine cheer
say |Dalia counts the stairs aloud. She loses count at 140 and starts again.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel look
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc dalia main 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|FOURTEEN FLOORS! FIFTEEN WITH THE ROOF! AND I'M ONLY A LITTLE TIRED!
say Dalia@dalia|We climb together. Nobody climbs alone. That's the rule.
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
spawn lamp main 600
spawn lamp main 1200
spawn lamp main 1800
goal Collect the 3 glowing lamps on the Main floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 10
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
anim dalia float
anim amir look
say |The group sits on a landing and shares water. It's the best water.
bars off
scene off
endday

# ---- c5 DAY 3
script c5_3
title Safe Ascent: The Signal
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
say |Haydar's radio crackles. A voice sings: climb, climb, climb.
say Dalia@dalia|Ready when you are, Amir.
anim dalia wave
bars off
scene off
goal Take the elevator to the Special floor.
await floor special
npc kenzy special 900
goal Talk to Haydar.
await talk kenzy
say Haydar@kenzy|It's the building! It's pointing us up! I'm very sure! Fairly sure! Mostly!
say Haydar@kenzy|Whatever it is, it sounds kind.
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
npc dalia special 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
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
anim kenzy tilt
anim amir wave
say |The radio plays one soft note and goes quiet.
bars off
scene off
endday

# ---- c5 DAY 4
script c5_4
title Safe Ascent: Ice Cream Stop
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
say |Amyas has set up a tiny cart on the Teen floor landing.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shiver
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc amyas teen 900
goal Talk to Amyas.
await talk amyas
say Amyas@amyas|Climbing is hard. Ice cream helps. Don't argue. Strawberry.
say Amyas@amyas|I'm not being nice. It's a business decision.
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
spawn lamp teen 600
spawn lamp teen 1200
spawn lamp teen 1800
goal Collect the 3 glowing lamps on the Teen floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini balance 10
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
anim amyas shrug
anim amir shiver
say |Amir takes the cone. He says nothing. He smiles. It's a small, private one.
bars off
scene off
endday

# ---- c5 DAY 5
script c5_5
title Safe Ascent: Race
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
say |Adam Bachouche challenges everyone to a race up the last flight.
say Dalia@dalia|Ready when you are, Amir.
anim dalia stomp
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc adam_t teen 900
goal Talk to Adam.
await talk adam_t
say Adam@adam_t|Last one to the Roof is a rotten bot! Ready? Set? Amir, you're slow!
say Adam@adam_t|I am NOT slow! It's a strategy!
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
npc dalia teen 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
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
anim adam_t hop
anim amir stomp
say |Amir wins by a nose. Adam demands a rematch. He gets one. Then another.
bars off
scene off
endday

# ---- c5 DAY 6
script c5_6
title Safe Ascent: To Be Continued
bars on
scene roof amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel jump
say |The Roof at sunset. Everyone sits in a circle. A note on the rope says: THIS IS A PREVIEW. THE ASCENT CONTINUES.
say Dalia@dalia|Ready when you are, Amir.
anim dalia float
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|THANK YOU FOR CLIMBING THIS FAR. THE REST OF THE JOURNEY IS STILL BEING WRITTEN. I WILL SWEEP THE STAIRS UNTIL IT IS READY.
say Prime@prime|Chapter 5 is a preview. More is coming.
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
scene roof amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime dance
anim amir float
say |The lake glows. The wires hum. The building listens.
bars off
scene off
ending e_ascent
endday

)IL";