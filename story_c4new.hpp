// generated c4
#pragma once
static const char* STORY_C4NEW = R"IL(
# ---- c4 DAY 1
script c4_1
title Never 1: The Lamp
card CHAPTER 4|Never
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
say |A sign hangs in the Lobby: NEVER 1 - NEVER LEAVE A LAMP OFF. Nobody put it there.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc prime lobby 900
goal Talk to Prime.
await talk prime
say Prime@prime|I DID NOT HANG THIS. I HAVE ONE ARM FOR HANGING. THE SIGN WAS HUNG BY A TALLER ARM.
say Prime@prime|The sign says 'never' fourteen times. We should find the other thirteen.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d1_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d1_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lobby 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
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
anim prime stomp
anim amir jump
say |Prime turns every lamp on. The Lobby glows like a tiny sun.
bars off
scene off
endday

# ---- c4 DAY 2
script c4_2
title Never 2: The Door
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
say |Taped to Dalia's door: NEVER 2 - NEVER SLAM A DOOR.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel look
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc dalia main 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|Who tapes things to MY door? I'm not mad! I'm... a little mad!
say Dalia@dalia|It's a game. The building talks. Dalia hates it and wants to win.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d2_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d2_b 1
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
say |Dalia closes her door softly. She is shaking with effort.
bars off
scene off
endday

# ---- c4 DAY 3
script c4_3
title Never 3: The Clock
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
say |Sign three sits in a clock case on the Rare floor: NEVER 3 - NEVER STOP THE CLOCK.
say Dalia@dalia|Ready when you are, Amir.
anim dalia wave
bars off
scene off
goal Take the elevator to the Rare floor.
await floor rare
npc jilali rare 900
goal Talk to Jilali.
await talk jilali
say Jilali@jilali|My clock stopped at 14:14. Then it started again. By itself.
say Jilali@jilali|The signs are not threats. They ask us to keep things going.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d3_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d3_b 1
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
anim jilali tilt
anim amir wave
say |The clock ticks along, calm as a cat.
bars off
scene off
endday

# ---- c4 DAY 4
script c4_4
title Never 4: Alone
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
say |Stuck to a pillar with a smiley sticker: NEVER 4 - NEVER GO ALONE.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shiver
bars off
scene off
goal Take the elevator to the Underlobby.
await floor ulobby
npc bolt ulobby 900
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|BEEP! IT HAS A SMILEY! IT SAYS NEVER GO ALONE! WE ARE NOT ALONE!
say Bolt@bolt|We have Dalia, Prime and a rope. That is plenty.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d4_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d4_b 1
label m1
mini pairs 4 6
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
mini balance 10
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
anim bolt shrug
anim amir shiver
say |Bolt rolls in a happy circle around the three of them.
bars off
scene off
endday

# ---- c4 DAY 5
script c4_5
title Never 5: Who Came First
bars on
scene hall amir dalia amine
cast amir 300
cast dalia 1100
cast amine 1250
walk amir 560 4
walk dalia 760 5
walk amine 930 5 wait
emote dalia !
anim amine laugh
say |Outside Amir's own door: NEVER 5 - NEVER FORGET WHO CAME FIRST.
say Dalia@dalia|Ready when you are, Amir.
anim dalia stomp
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc gabriel lethal 900
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|This one is for you. Whoever wrote the list knows your door and your name.
say Gabriel@gabriel|Nine signs are left. The list gets more personal with each one.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d5_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d5_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lethal 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
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
anim gabriel hop
anim amir stomp
say |Amir touches the sign. It is warm, like it just came out of an oven.
bars off
scene off
endday

# ---- c4 DAY 6
script c4_6
title Never 6: Dessert
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
say |On the Uncommon floor, on a cake stand: NEVER 6 - NEVER SKIP DESSERT.
say Dalia@dalia|Ready when you are, Amir.
anim dalia float
bars off
scene off
goal Take the elevator to the Uncommon floor.
await floor unc
npc alicia unc 900
goal Talk to Alicia.
await talk alicia
say Alicia@alicia|Big brother! A sign! It says dessert! I found the cake! It's pretend cake!
say Alicia@alicia|She did find a cake. It's a real one. It's from Amyas's shop. Somebody planned this.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d6_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d6_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp unc 600
spawn lamp unc 1200
spawn lamp unc 1800
goal Collect the 3 glowing lamps on the Uncommon floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 12
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
anim alicia dance
anim amir float
say |Alicia shares the cake with every bot. Prime saves a crumb for later.
bars off
scene off
endday

# ---- c4 DAY 7
script c4_7
title Never 7: Say Hello
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
say |On the Common floor, over a door: NEVER 7 - NEVER PASS SOMEONE WITHOUT SAYING HELLO.
say Dalia@dalia|Ready when you are, Amir.
anim dalia tilt
bars off
scene off
goal Take the elevator to the Common floor.
await floor common
npc anes common 900
goal Talk to Anes.
await talk anes
say Anes@anes|I said hello to the sign. It didn't say anything back. Rude. But I said it.
say Anes@anes|Iyad says hi to everyone. He says it is the oldest rule in the building.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d7_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d7_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia common 1400
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
anim anes cheer
anim amir tilt
say |The group says hello to every door. Every door seems pleased.
bars off
scene off
endday

# ---- c4 DAY 8
script c4_8
title Never 8: Secrets
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
say |Amine's door on the Special floor: NEVER 8 - NEVER KEEP A SECRET THAT HURTS.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shrug
bars off
scene off
goal Take the elevator to the Special floor.
await floor special
npc amine special 900
goal Talk to Amine.
await talk amine
say Amine@amine|Hey, Amir! I found a sign. It's about secrets. I don't have any. Okay, one. It's a surprise cake.
say Amine@amine|Don't worry. It's a good secret. Good secrets are allowed.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d8_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d8_b 1
label m1
mini tapcatch 12 3 dust
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
mini balance 12
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
anim amine nod
anim amir shrug
say |Amine promises not to keep any hurting secrets. He mostly keeps his promise.
bars off
scene off
endday

# ---- c4 DAY 9
script c4_9
title Never 9: Rust
bars on
scene garage amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shiver
say |In Parking 1, on a rusty pipe: NEVER 9 - NEVER LET RUST WIN.
say Dalia@dalia|Ready when you are, Amir.
anim dalia hop
bars off
scene off
goal Take the elevator to Parking 1.
await floor park1
npc mopsy park1 900
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|I was told there would be rust. There is rust. I'm furious and thrilled.
say Mopsy@mopsy|Mopsy attacks the rust like a tiny mop-wielding knight.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d9_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d9_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia park1 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia mopsy
cast amir 300
cast dalia 1200
cast mopsy 1100
walk amir 560 6
walk dalia 760 5
walk mopsy 900 4 wait
anim mopsy point
anim amir hop
say |The pipe shines. Mopsy pretends it was nothing.
bars off
scene off
endday

# ---- c4 DAY 10
script c4_10
title Never 10: Ice Cream
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
say |Taped to a freezer on the Teen floor: NEVER 10 - NEVER EAT ICE CREAM ALONE.
say Dalia@dalia|Ready when you are, Amir.
anim dalia dance
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc amyas teen 900
goal Talk to Amyas.
await talk amyas
say Amyas@amyas|Amir. You look terrible. Strawberry. Don't thank me.
say Amyas@amyas|I didn't write the list. But I like number ten. Eat.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d10_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d10_b 1
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
anim amyas laugh
anim amir dance
say |Amyas pretends not to see Amir grin. Adam Bachouche pretends not to see Amyas pretend.
bars off
scene off
endday

# ---- c4 DAY 11
script c4_11
title Never 11: Run
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
say |On the Teen floor stairs: NEVER 11 - NEVER WALK WHEN YOU CAN RUN.
say Dalia@dalia|Ready when you are, Amir.
anim dalia cheer
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc adam_t teen 900
goal Talk to Adam.
await talk adam_t
say Adam@adam_t|Hey, Amir! I'm not mad! I'm only here because someone has to keep an eye on you!
say Adam@adam_t|You can thank me later. Don't. It would be weird.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d11_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d11_b 1
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
anim adam_t jump
anim amir cheer
say |Adam sprints down the stairs. Amir pretends he doesn't want to follow. He follows.
bars off
scene off
endday

# ---- c4 DAY 12
script c4_12
title Never 12: Dust
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
say |In Parking 2, on a covered car: NEVER 12 - NEVER LET DUST HAVE THE LAST WORD.
say Dalia@dalia|Ready when you are, Amir.
anim dalia nod
bars off
scene off
goal Take the elevator to Parking 2.
await floor park2
npc sweepy park2 900
goal Talk to Sweepy.
await talk sweepy
say Sweepy@sweepy|The dust is thick here. It has opinions. I'm Sweepy and I disagree.
say Sweepy@sweepy|We clean it together. It's the only way dust learns.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d12_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d12_b 1
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
anim sweepy look
anim amir nod
say |The car shines. The dust sighs in defeat.
bars off
scene off
endday

# ---- c4 DAY 13
script c4_13
title Never 13: Soup
bars on
scene inn amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shrug
say |On a table at the Further inn: NEVER 13 - NEVER SERVE COLD SOUP.
say Dalia@dalia|Ready when you are, Amir.
anim dalia point
bars off
scene off
goal Take the elevator to the Further inn.
await floor inn
npc aya_n inn 900
goal Talk to Aya.
await talk aya_n
say Aya@aya_n|Soup! I made soup! It tastes like pennies! It has love too! Mostly pennies!
say Aya@aya_n|Sofia says the Inn has a rule: nobody leaves hungry. Not even the signs.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d13_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d13_b 1
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
anim aya_n wave
anim amir point
say |Everyone eats. Even Gabriel smiles. Dalia pretends she didn't see.
bars off
scene off
endday

# ---- c4 DAY 14
script c4_14
title Never 14: Leave
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
say |On the Roof, under the banner: NEVER 14 - NEVER LEAVE WITHOUT SAYING GOODBYE.
say Dalia@dalia|Ready when you are, Amir.
anim dalia laugh
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|I HAVE READ ALL THE SIGNS. THEY ARE NOT RULES. THEY ARE PROMISES.
say Prime@prime|Fourteen promises. One for each letter of 'Welcome to the 14'. Almost.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d14_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d14_b 1
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
scene roof amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime shiver
anim amir laugh
say |The wind lifts the banner. It waves goodbye to nobody and everybody.
bars off
scene off
endday

# ---- c4 DAY 15
script c4_15
title The Fifteenth Sign
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
say |In the Lobby a sign is blank. Under it, a pen. The pen is warm. The Fifteenth sign is empty on purpose.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc prime lobby 900
goal Talk to Prime.
await talk prime
say Prime@prime|THE SIGN HAS NO NEVER. IT WAITS FOR US TO WRITE IT. I DO NOT KNOW WHAT TO WRITE.
say Prime@prime|We have thirty days to think. Every resident gets one idea.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d15_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d15_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lobby 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
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
anim prime stomp
anim amir jump
say |Prime puts the pen in his tool tray. It rattles proudly.
bars off
scene off
endday

# ---- c4 DAY 16
script c4_16
title Jalil's Idea
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
say |Jalil sits on the Uncommon floor drawing a giant crayon sign.
say Dalia@dalia|Ready when you are, Amir.
anim dalia look
bars off
scene off
goal Take the elevator to the Uncommon floor.
await floor unc
npc jalil unc 900
goal Talk to Jalil.
await talk jalil
say Jalil@jalil|I want to write NEVER BE SAD! With a bus! And a monster! A nice monster!
say Jalil@jalil|He's four. His idea is not bad. It is just very green.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d16_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d16_b 1
label m1
mini slide 3
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
clearitems
spawn lamp unc 600
spawn lamp unc 1200
spawn lamp unc 1800
goal Collect the 3 glowing lamps on the Uncommon floor.
await items 3
say Dalia@dalia|Three! I counted! I'm the best counter!
clearitems
mini sort 12
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
anim jalil float
anim amir look
say |Jalil adds a second bus. The sign now has two buses and a monster.
bars off
scene off
endday

# ---- c4 DAY 17
script c4_17
title Abdullah's Idea
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
say |Abdullah has a clipboard. He is six and very serious about it.
say Dalia@dalia|Ready when you are, Amir.
anim dalia wave
bars off
scene off
goal Take the elevator to the Uncommon floor.
await floor unc
npc abdullah unc 900
goal Talk to Abdullah.
await talk abdullah
say Abdullah@abdullah|My idea is NEVER LOSE AT CARDS. It is a good rule. Please vote.
say Abdullah@abdullah|It's not a good rule. But it is honest.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d17_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d17_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia unc 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
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
anim abdullah tilt
anim amir wave
say |Abdullah puts a gold star next to his own idea. Nobody argues.
bars off
scene off
endday

# ---- c4 DAY 18
script c4_18
title Iyad's Idea
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
say |Iyad winds up a pocket watch and leans on the wall.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shiver
bars off
scene off
goal Take the elevator to the Common floor.
await floor common
npc iyad common 900
goal Talk to Iyad.
await talk iyad
say Iyad@iyad|NEVER BE LATE. I'm always late. That's why it's the best idea. It's aspirational.
say Iyad@iyad|He's ten. His watch runs backward. Everyone loves him anyway.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d18_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d18_b 1
label m1
mini tapcatch 12 3 dust
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
anim iyad shrug
anim amir shiver
say |Iyad runs off, late for a thing that hasn't started.
bars off
scene off
endday

# ---- c4 DAY 19
script c4_19
title Maysanne's Idea
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
say |Maysanne holds a notebook full of tiny drawings.
say Dalia@dalia|Ready when you are, Amir.
anim dalia stomp
bars off
scene off
goal Take the elevator to the Rare floor.
await floor rare
npc maysanne rare 900
goal Talk to Maysanne.
await talk maysanne
say Maysanne@maysanne|I think the rule should be NEVER STOP DRAWING. I draw everything. Look. This is a bot.
say Maysanne@maysanne|She is nine. The drawing is a very good bot.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d19_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d19_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia rare 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
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
anim maysanne hop
anim amir stomp
say |Maysanne gives Bolt a drawing. He keeps it forever.
bars off
scene off
endday

# ---- c4 DAY 20
script c4_20
title Arwa's Idea
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
say |Arwa leans on a wall on the Main floor, arms crossed, thinking.
say Dalia@dalia|Ready when you are, Amir.
anim dalia float
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc arwa main 900
goal Talk to Arwa.
await talk arwa
say Arwa@arwa|Never leave your little brother alone. That's mine. Jalil needs a babysitter and a bus.
say Arwa@arwa|It's a good rule. A little bossy. Typical.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d20_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d20_b 1
label m1
mini lights 4
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
anim arwa dance
anim amir float
say |Arwa winks at Dalia. Dalia sticks her tongue out.
bars off
scene off
endday

# ---- c4 DAY 21
script c4_21
title Youcef's Idea
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
say |Youcef holds a hammer, a pencil and a very squeaky chair.
say Dalia@dalia|Ready when you are, Amir.
anim dalia tilt
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc youcef main 900
goal Talk to Youcef.
await talk youcef
say Youcef@youcef|NEVER STOP BUILDING. That's the rule. Also: NEVER LOSE THE HAMMER.
say Youcef@youcef|He's twelve. He loses the hammer twice during the vote.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d21_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d21_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia main 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
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
anim youcef cheer
anim amir tilt
say |Youcef finds the hammer in his own pocket. He is unbearably smug.
bars off
scene off
endday

# ---- c4 DAY 22
script c4_22
title Raceem's Idea
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
say |Raceem rides a skateboard up the Lethal floor hall, then crashes into the wall. Politely.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shrug
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc raceem lethal 900
goal Talk to Raceem.
await talk raceem
say Raceem@raceem|Never stop moving! Never! That's mine! Oof.
say Raceem@raceem|Raceem likes fast ideas. Slow ones too, if they come with snacks.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d22_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d22_b 1
label m1
mini lights 3
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
mini sort 10
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
anim raceem nod
anim amir shrug
say |Raceem rolls away. He drops a sandwich. Bolt picks it up like a prize.
bars off
scene off
endday

# ---- c4 DAY 23
script c4_23
title Basmala's Idea
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
say |Basmala hands Amir a folded note, very formally.
say Dalia@dalia|Ready when you are, Amir.
anim dalia hop
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc basmala lethal 900
goal Talk to Basmala.
await talk basmala
say Basmala@basmala|I wrote down my rule. It's private. You can read it after the vote.
say Basmala@basmala|It's tradition. Notes first, votes second. Cake third.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d23_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d23_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lethal 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
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
anim basmala point
anim amir hop
say |The note says: 'NEVER STOP BEING A GOOD FRIEND.' Amir folds it carefully.
bars off
scene off
endday

# ---- c4 DAY 24
script c4_24
title Dania's Idea
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
say |Dania spreads three bags of markers across a table.
say Dalia@dalia|Ready when you are, Amir.
anim dalia dance
bars off
scene off
goal Take the elevator to the Common floor.
await floor common
npc dania common 900
goal Talk to Dania.
await talk dania
say Dania@dania|Mine is colorful! NEVER BE BORING! In every color! Look! A rainbow!
say Dania@dania|She is eleven. Her handwriting is a rainbow too.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d24_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d24_b 1
label m1
mini pairs 4 6
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
mini balance 10
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia dania
cast amir 300
cast dalia 1200
cast dania 1100
walk amir 560 6
walk dalia 760 5
walk dania 900 4 wait
anim dania laugh
anim amir dance
say |Dania draws a small sun on the sign. It looks great.
bars off
scene off
endday

# ---- c4 DAY 25
script c4_25
title Fares's Idea
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
say |Fares is on the floor with a robot kit and a wrench.
say Dalia@dalia|Ready when you are, Amir.
anim dalia cheer
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc fares lethal 900
goal Talk to Fares.
await talk fares
say Fares@fares|My rule is: NEVER GIVE UP ON A BOT. Even when it's smoking.
say Fares@fares|He's eleven and quietly the nicest person in the building.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d25_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d25_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lethal 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene hall amir dalia fares
cast amir 300
cast dalia 1200
cast fares 1100
walk amir 560 6
walk dalia 760 5
walk fares 900 4 wait
anim fares jump
anim amir cheer
say |Fares fixes a bot in under a minute. Everyone applauds. He blushes.
bars off
scene off
endday

# ---- c4 DAY 26
script c4_26
title Haydar's Idea
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel tilt
say |Haydar listens to a radio that is also a toaster.
say Dalia@dalia|Ready when you are, Amir.
anim dalia nod
bars off
scene off
goal Take the elevator to the Special floor.
await floor special
npc kenzy special 900
goal Talk to Haydar.
await talk kenzy
say Haydar@kenzy|Mine is NEVER MISS THE SIGNAL. I heard it the whole time. It was singing.
say Haydar@kenzy|He's eleven. The signal is a good one.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d26_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d26_b 1
label m1
mini slide 3
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
anim kenzy look
anim amir nod
say |The radio plays the building's four-note hum. Haydar hums along.
bars off
scene off
endday

# ---- c4 DAY 27
script c4_27
title Anais's Idea
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shrug
say |Anais is reading three books at once on the Rare floor.
say Dalia@dalia|Ready when you are, Amir.
anim dalia point
bars off
scene off
goal Take the elevator to the Rare floor.
await floor rare
npc anais rare 900
goal Talk to Anais.
await talk anais
say Anais@anais|Mine is NEVER STOP ASKING WHY. I asked why about the signs. They did not answer.
say Anais@anais|She's twelve and gloriously curious.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d27_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d27_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia rare 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
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
anim anais wave
anim amir point
say |Anais writes 'WHY' on a sticky note and sticks it on a sign.
bars off
scene off
endday

# ---- c4 DAY 28
script c4_28
title Vacca's Idea
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
say |Vacca sweeps Parking 1 so fast the dust applauds.
say Dalia@dalia|Ready when you are, Amir.
anim dalia laugh
bars off
scene off
goal Take the elevator to Parking 1.
await floor park1
npc vacca park1 900
goal Talk to Vacca.
await talk vacca
say Vacca@vacca|NEVER LEAVE A CORNER UNSWEPT. That's the rule. It is the only rule.
say Vacca@vacca|Bots have simple rules. Simple rules work.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d28_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d28_b 1
label m1
mini tapcatch 12 3 dust
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
mini balance 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia vacca
cast amir 300
cast dalia 1200
cast vacca 1100
walk amir 560 6
walk dalia 760 5
walk vacca 900 4 wait
anim vacca shiver
anim amir laugh
say |Vacca sweeps the last corner. A single leaf is saved.
bars off
scene off
endday

# ---- c4 DAY 29
script c4_29
title Sofia's Idea
bars on
scene inn amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel dance
say |Sofia sets a tiny key on a table at the Further inn.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator to the Further inn.
await floor inn
npc sofia inn 900
goal Talk to Sofia.
await talk sofia
say Sofia@sofia|My rule is NEVER LOCK A DOOR ON SOMEONE WHO'S COMING HOME.
say Sofia@sofia|It's quiet. It's good. It sounds like her.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d29_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d29_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia inn 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
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
anim sofia stomp
anim amir jump
say |Sofia leaves the Inn door unlocked. She smiles a little.
bars off
scene off
endday

# ---- c4 DAY 30
script c4_30
title Dalia's Big Idea
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
say |Dalia stands on a crate on the Main floor and announces her rule to nobody.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel look
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc dalia main 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|MY RULE IS: NEVER LET GABRIEL WIN! ...No. Fine. NEVER STOP BEING LOUD ABOUT WHAT YOU LOVE!
say Dalia@dalia|It's a good rule. A very Dalia rule. Gabriel is smiling at the wall.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d30_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d30_b 1
label m1
mini lights 4
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
mini popcorn 10 3 1
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
say |Gabriel writes it down so carefully it's almost a love letter. Almost.
bars off
scene off
endday

# ---- c4 DAY 31
script c4_31
title Gabriel's Idea
bars on
scene hall amir dalia amine
cast amir 300
cast dalia 1100
cast amine 1250
walk amir 560 4
walk dalia 760 5
walk amine 930 5 wait
emote dalia !
anim amine nod
say |Gabriel leans against the wall, rope over his shoulder.
say Dalia@dalia|Ready when you are, Amir.
anim dalia wave
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc gabriel main 900
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|Mine is NEVER LEAVE SOMEONE ON THE ROPE. Which means: you hold on. And so do I.
say Gabriel@gabriel|It sounds like a rule about ropes. It's not.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d31_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d31_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia main 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
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
anim gabriel tilt
anim amir wave
say |Gabriel ties his rope in a knot that reads 'hold on'. Dalia pretends not to read it.
bars off
scene off
endday

# ---- c4 DAY 32
script c4_32
title Bolt's Idea
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
say |Bolt zooms in a figure eight across the Lobby floor and slides into a wall.
say Dalia@dalia|Ready when you are, Amir.
anim dalia shiver
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc bolt lobby 900
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|NEVER STOP ZOOMING! NEVER! EVER! ALWAYS ZOOM!
say Bolt@bolt|It's the best rule. It has the most exclamation marks.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d32_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d32_b 1
label m1
mini lights 3
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
mini sort 10
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
anim bolt shrug
anim amir shiver
say |Bolt zooms in a perfect circle around everyone. Nobody is bored.
bars off
scene off
endday

# ---- c4 DAY 33
script c4_33
title The Bots Vote
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
say |The bots hold a secret vote in the 14 Cleaning bots parking. Mopsy bangs a spoon on a mug.
say Dalia@dalia|Ready when you are, Amir.
anim dalia stomp
bars off
scene off
goal Take the elevator to the 14 Cleaning bots parking.
await floor bots
npc mopsy bots 900
goal Talk to Mopsy.
await talk mopsy
say Mopsy@mopsy|The vote is open. Humans may attend. Humans may not speak. Except Dalia. She never stops anyway.
say Mopsy@mopsy|The bots vote with tiny beeps. Prime votes seventeen times.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d33_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d33_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia bots 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
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
say |The vote is a tie. A bot named Dustin breaks it with a sneeze.
bars off
scene off
endday

# ---- c4 DAY 34
script c4_34
title The Night Before
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
say |The night before the last sign. The Roof is quiet. Everyone is here, sitting in a circle.
say Dalia@dalia|Ready when you are, Amir.
anim dalia float
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc prime roof 900
goal Talk to Prime.
await talk prime
say Prime@prime|TOMORROW WE WRITE THE FIFTEENTH. I HAVE BEEN PRACTICING MY LETTERS. THEY ARE VERY SQUARE.
say Prime@prime|Don't be nervous. It's only the building's oldest promise.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d34_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d34_b 1
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
scene roof amir dalia prime
cast amir 300
cast dalia 1200
cast prime 1100
walk amir 560 6
walk dalia 760 5
walk prime 900 4 wait
anim prime dance
anim amir float
say |The banner flaps. The sky is the color of a sleeping orange.
bars off
scene off
endday

# ---- c4 DAY 35
script c4_35
title The Vote Cake
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
say |Alicia carries a cake with fifteen candles and a plastic bus on top.
say Dalia@dalia|Ready when you are, Amir.
anim dalia tilt
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc alicia lobby 900
goal Talk to Alicia.
await talk alicia
say Alicia@alicia|Big brother! It's the vote cake! It has a bus! Jalil insisted on the bus!
say Alicia@alicia|Fifteen candles. One for each sign. One of them is already lit.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d35_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d35_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lobby 1400
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
anim amir tilt
say |Alicia blows out the candle. The building cheers.
bars off
scene off
endday

# ---- c4 DAY 36
script c4_36
title The Argument
bars on
scene hall amir gabriel amine
cast amir 300
cast gabriel 1100
cast amine 1250
walk amir 560 4
walk gabriel 760 5
walk amine 930 5 wait
emote gabriel !
anim amine wave
say |Dalia and Gabriel argue about the wording while everyone else eats cake.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel shrug
bars off
scene off
goal Take the elevator to the Main floor.
await floor main
npc dalia main 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|It should be NEVER BE QUIET! No! NEVER LET GO! No! NEVER STOP! ...Okay, mine.
say Dalia@dalia|It doesn't matter. It matters. It always matters.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d36_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d36_b 1
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
scene hall amir gabriel dalia
cast amir 300
cast gabriel 1200
cast dalia 1100
walk amir 560 6
walk gabriel 760 5
walk dalia 900 4 wait
anim dalia nod
anim amir shrug
say |They both nod at the same time. Both pretend they didn't.
bars off
scene off
endday

# ---- c4 DAY 37
script c4_37
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
anim gabriel shiver
say |Amine knocks on Amir's door on the Lethal floor with a bag of snacks.
say Dalia@dalia|Ready when you are, Amir.
anim dalia hop
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc amine lethal 900
goal Talk to Amine.
await talk amine
say Amine@amine|I'm here for the final vote. As a witness. And as a friend. Mostly as a friend.
say Amine@amine|I believe in you. Whatever you write. I'll sign it.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d37_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d37_b 1
label m1
mini memo 4 5
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lethal 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 14
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
anim amine point
anim amir hop
say |Amine sits next to Amir. They don't say much. It's perfect.
bars off
scene off
endday

# ---- c4 DAY 38
script c4_38
title Lilian Tells a Story
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
say |Lilian sits on a stair, telling the younger kids a story about the building.
say Dalia@dalia|Ready when you are, Amir.
anim dalia dance
bars off
scene off
goal Take the elevator to the Teen floor.
await floor teen
npc lilian teen 900
goal Talk to Lilian.
await talk lilian
say Lilian@lilian|Long ago, the 14 had one rule: NEVER BE ALONE. Then it grew. Then it learned to count.
say Lilian@lilian|It's a story. It's also true. Don't tell her I said that.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d38_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d38_b 1
label m1
mini tapcatch 12 3 dust
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
mini balance 12
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
anim lilian laugh
anim amir dance
say |Lilian finishes and bows. The kids clap so hard the stairs tremble.
bars off
scene off
endday

# ---- c4 DAY 39
script c4_39
title The Last Page
bars on
scene inn amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel float
say |Adam Tansaouti opens an old ledger at the Further inn and finds the last page empty.
say Dalia@dalia|Ready when you are, Amir.
anim dalia cheer
bars off
scene off
goal Take the elevator to the Further inn.
await floor inn
npc tansaouti inn 900
goal Talk to Adam Tansaouti.
await talk tansaouti
say Adam Tansaouti@tansaouti|The Inn kept the first rule. It's on the first page: NEVER TURN SOMEONE AWAY.
say Adam Tansaouti@tansaouti|That rule is yours too, now. All of you.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d39_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d39_b 1
label m1
mini quiz 5 school
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia inn 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini whack 12
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene inn amir dalia tansaouti
cast amir 300
cast dalia 1200
cast tansaouti 1100
walk amir 560 6
walk dalia 760 5
walk tansaouti 900 4 wait
anim tansaouti jump
anim amir cheer
say |Adam Tansaouti closes the ledger gently. He looks lighter.
bars off
scene off
endday

# ---- c4 DAY 40
script c4_40
title Grim Has a Thought
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
say |Grim hides behind a pillar in Parking 2 with a tiny sign: BOO (sorry).
say Dalia@dalia|Ready when you are, Amir.
anim dalia nod
bars off
scene off
goal Take the elevator to Parking 2.
await floor park2
npc grim park2 900
goal Talk to Grim.
await talk grim
say Grim@grim|Sorry. I wanted to say my idea. It's NEVER BE SCARED OF A NAME. Mine is Grim. I'm very nice.
say Grim@grim|It's a good rule. It's quiet. It lives in a corner.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d40_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d40_b 1
label m1
mini lights 4
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
mini popcorn 10 3 1
ifnot skipped s2
say |(Nice. Everyone cheers.)
label s2
bars on
scene garage amir dalia grim
cast amir 300
cast dalia 1200
cast grim 1100
walk amir 560 6
walk dalia 760 5
walk grim 900 4 wait
anim grim look
anim amir nod
say |Grim waves a tiny flag with a heart on it. Everyone waves back.
bars off
scene off
endday

# ---- c4 DAY 41
script c4_41
title The Clock Strikes
bars on
scene hall amir dalia gabriel
cast amir 300
cast dalia 1100
cast gabriel 1250
walk amir 560 4
walk dalia 760 5
walk gabriel 930 5 wait
emote dalia !
anim gabriel shrug
say |The Rare floor clock strikes fourteen. It has never done that before.
say Dalia@dalia|Ready when you are, Amir.
anim dalia point
bars off
scene off
goal Take the elevator to the Rare floor.
await floor rare
npc jilali rare 900
goal Talk to Jilali.
await talk jilali
say Jilali@jilali|It never rang fourteen. It only goes to twelve. Today it learned a new number.
say Jilali@jilali|The building is trying to tell us something. It's saying: soon.
choose
> Let's do it. => a
> I'm not sure. => b
label a
say Amir|Okay. Together.
set c4_d41_a 1
goto m1
label b
say Dalia@dalia|Scared people watch where they walk. You're fine!
set c4_d41_b 1
label m1
mini whack 10
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia rare 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 7
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
anim jilali wave
anim amir point
say |The clock strikes the last chime. Fourteen. Everyone holds their breath.
bars off
scene off
endday

# ---- c4 DAY 42
script c4_42
title The Fifteenth Sign
bars on
scene roof amir dalia amine
cast amir 300
cast dalia 1100
cast amine 1250
walk amir 560 4
walk dalia 760 5
walk amine 930 5 wait
emote dalia !
anim amine hop
say |Everyone gathers on the Roof. The blank sign waits. Everyone holds a marker. Nobody speaks.
say Dalia@dalia|Ready when you are, Amir.
anim dalia laugh
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc gabriel roof 900
goal Talk to Gabriel.
await talk gabriel
say Gabriel@gabriel|Amir. It's yours to write. We'll all sign after.
say Gabriel@gabriel|Take your time. The building waits. It has waited for forty years.
choose
> Sounds fun. => a
> This is weird. => b
label a
say Dalia@dalia|It does! Gabriel, stop looking so serious!
set c4_d42_a 1
goto m1
label b
say Gabriel@gabriel|Weird is just new with a coat on.
set c4_d42_b 1
label m1
mini lights 3
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
mini sort 10
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
anim gabriel shiver
anim amir laugh
say |Amir writes: NEVER STOP COMING HOME. Everyone signs. The sign glows.
bars off
scene off
endday

# ---- c4 DAY 43
script c4_43
title The Building Answers
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
say |In the Lobby every lamp lights at once. The hum becomes a warm, rising chord.
say Dalia@dalia|Ready when you are, Amir.
anim dalia jump
bars off
scene off
goal Take the elevator to the Lobby.
await floor lobby
npc prime lobby 900
goal Talk to Prime.
await talk prime
say Prime@prime|THE BUILDING HAS ANSWERED. IT SAYS: THANK YOU. IT SAYS: WELCOME HOME. IT HAS NEVER SAID THAT BEFORE.
say Prime@prime|I HAVE SWEPT THIS FLOOR FOR FORTY YEARS. NOBODY EVER SAID THANK YOU. NOW THE FLOOR DID.
choose
> I'll lead. => a
> You go first. => b
label a
say Gabriel@gabriel|Okay. I'll watch your back. And hold the rope.
set c4_d43_a 1
goto m1
label b
say Dalia@dalia|Fine! I'm fearless! Mostly!
set c4_d43_b 1
label m1
mini quiz 4 ilot14
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Dalia.
npc dalia lobby 1400
await talk dalia
say Dalia@dalia|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini dash 12
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
anim prime stomp
anim amir jump
say |Prime cries oil. He insists it's dust. Everyone lets him.
bars off
scene off
endday

# ---- c4 DAY 44
script c4_44
title A Quiet Morning
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
say |A quiet morning on the Lethal floor. For once, no sign. Only the smell of toast.
say Dalia@dalia|Ready when you are, Amir.
anim dalia look
bars off
scene off
goal Take the elevator to the Lethal floor.
await floor lethal
npc bolt lethal 900
goal Talk to Bolt.
await talk bolt
say Bolt@bolt|BEEP! NO SIGN TODAY! I CHECKED EVERY DOOR! I ALSO FOUND TOAST!
say Bolt@bolt|Rest is allowed. Even for heroes. Especially for heroes.
choose
> What could go wrong? => a
> Let's be careful. => b
label a
say Dalia@dalia|Don't say that! The building listens!
set c4_d44_a 1
goto m1
label b
say Gabriel@gabriel|Careful is good. Careful finishes the day.
set c4_d44_b 1
label m1
mini pairs 4 6
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
mini balance 10
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
anim bolt float
anim amir look
say |Bolt shares his toast with three bots and a doorknob.
bars off
scene off
endday

# ---- c4 DAY 45
script c4_45
title Chapter Four, Finally
bars on
scene roof amir gabriel amine
cast amir 300
cast gabriel 1100
cast amine 1250
walk amir 560 4
walk gabriel 760 5
walk amine 930 5 wait
emote gabriel !
anim amine nod
say |The sun rises over Reghaia. The lake is gold. The cable car wires sing. Everyone is on the Roof.
say Gabriel@gabriel|Ready when you are, Amir.
anim gabriel wave
bars off
scene off
goal Take the elevator up to the Roof.
await floor roof
npc dalia roof 900
goal Talk to Dalia.
await talk dalia
say Dalia@dalia|We did it! We read every sign, wrote the last one, and I didn't scream even once!
say Dalia@dalia|You screamed three times. I counted. It was lovely.
choose
> Tell me more. => a
> Skip the talk. => b
label a
say Amir|Go on. I'm listening.
set c4_d45_a 1
goto m1
label b
say Dalia@dalia|Okay okay! Action time!
set c4_d45_b 1
label m1
mini popcorn 10 2 1
ifnot skipped s1
say |(Nice work! The hallway feels a little brighter.)
label s1
goal Talk to Gabriel.
npc gabriel roof 1400
await talk gabriel
say Gabriel@gabriel|That was fun. I think I found something.
say |It's a small clue. Nobody understands it yet.
mini stack 8
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
anim dalia tilt
anim amir wave
say |The whole group watches the sunrise. Nobody says Never. They say Always.
bars off
scene off
ending e_never
endday

)IL";