// story_ch2c.hpp - CHAPTER 2: FURTHER INN, days 20-35 (Act 3: Down Below, Act 4: Check-In)
#pragma once
static const char* STORY_CH2C = R"IL(
# ================================================================ CH2 DAY 20
script c2_20
title Room 000
bars on
scene inn amir dalia gabriel sofia
say |Day 20. The black key is cold in my hand. It's heavier than a key should be.
say Dalia|We go together. All of us.
say Gabriel|I'll bring the rope.
say Sofia|I'll bring my ears.
say Amir|I'll bring... the key.
bars off
scene off
warp inn 1900
npc dalia inn 1750
npc gabriel inn 1850
npc sofia inn 1650
obj nodoor inn 2150 Door without a number
goal Walk to the door at the end of the Locked Wing and use it.
await use nodoor
say |The brass keyhole is shaped like a small hand. I press the black key to it. It fits. It turns without a sound.
fx flash
say |Behind the door, a narrow room. Single bed. One chair. A lamp. A window with a view of... a hallway. The same hallway.
say Dalia|That's my room back home. No wait, it's yours.
say Amir|It's L-001. It's my room. But with the walls painted a different color.
fx shake
say |The floor shifts. A trapdoor under the rug slides open. A narrow stairwell, spiraling down. A faint orange glow.
say Gabriel|Yeah. I'm tying the rope to something.
set room0_open 1
# VIGNETTE
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
mini pairs 4 6
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
mini pairs 4 5
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
mini quiz 4 ilot14
endday

# ================================================================ CH2 DAY 21
script c2_21
title The Stairwell
bars on
scene deep amir dalia gabriel
say |Day 21. The spiral stairs go down. And down. Pipes along the wall hum a slow, steady note. Rust flakes fall like orange snow.
say Gabriel|How many floors have we gone?
say Dalia|I stopped counting at "too many".
bars off
scene off
warp room0 400
npc dalia room0 520
npc gabriel room0 640
goal Walk through the stairwell. Dodge the falling debris.
mini dodge 22 4 2
ifnot skipped down
say |(Something caught you by the collar and set you gently on the stairs. You didn't see what.)
label down
say |A landing. A long hallway of brass doors, each with a small number. All numbers read "0".
say Dalia|These are all Room 000.
say Gabriel|Yes. I'm getting a headache.
say Amir|Look. One of them is open.
set stairwell_done 1
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
mini popcorn 10 2 1
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
mini pairs 4 6
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
mini pairs 4 5
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
mini quiz 4 ilot14
endday

# ================================================================ CH2 DAY 22
script c2_22
title Prime Again
bars on
scene deep amir prime dalia
say |Day 22. At the end of the hall, a small orange light blinks. A familiar beep. A familiar, very proud sweep.
say Prime|DUST DETECTED. NO. WAIT. FRIENDS DETECTED. WELCOME. I WAS TIDYING.
emote prime !
say Dalia|Prime! What are you doing down here?
say Prime|THE CALLING. I RECEIVED A MESSAGE: "SWEEP THE FLOORS BELOW THE FLOORS."
bars off
scene off
warp room0 600
npc prime room0 900
goal Talk to Prime.
await talk prime
say Prime|THE INN WAS BUILT ON A FLOOR THAT WAS BUILT ON A FLOOR THAT WAS BUILT ON A FLOOR. I HAVE SWEPT EIGHT SO FAR.
say Prime|THE LOWER ONES ARE NOT FINISHED. THEY ARE... SHIFTING.
choose
> Can you show us the shortcut? => short
> Is it dangerous? => danger
label danger
say Prime|THERE IS DUST. THERE IS ALWAYS DUST. THE QUESTION IS WHETHER THE DUST HAS OPINIONS.
goto go
label short
say Prime|FOLLOW MY BEEPS. DO NOT TOUCH THE WALLS. THE WALLS ARE SUBJECT TO CHANGE.
label go
mini maze 3 7
ifnot skipped through
say |(Prime scooped everyone up in a very small dustpan and delivered them to the exit. It was undignified.)
label through
say Prime|WE ARE AT THE FLOOR OF THE KNOCKING. IT IS NEAR. THE DUST HERE IS... TIRED.
say Amir|Tired of what?
say Prime|OF WAITING.
set prime_guide 1
# VIGNETTE
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
mini whack 10
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
mini popcorn 10 2 1
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
mini pairs 4 6
endday

# ================================================================ CH2 DAY 23
script c2_23
title Echoes in the Wall
bars on
scene deep amir sofia
cast amir 700
cast sofia 1000
say |Day 23. Sofia has stopped. She's pressing her ear against the wall of the hallway, eyes closed, shoulders tight.
say Sofia|There are voices. In the pipes. In the walls. Dozens of them.
say Amir|What are they saying?
say Sofia|Names. They're saying names. Everyone's names. And a place. "Level eighteen."
bars off
scene off
warp room0 800
npc sofia room0 1100
goal Talk to Sofia.
await talk sofia
say Sofia|I can hear the order they say them in. Repeat it with me. It might open a way forward.
mini simon 8 3 24
ifnot skipped heard
say |(Sofia whispered the last names to you, one at a time.)
label heard
fx flicker
say |The wall ahead of us slides open. Behind it, a narrow service lift, rusted, humming.
say Sofia|That goes down. Way down.
say Amir|Not today. Today we find out who lives behind the knocks.
set voices_heard 1
# VIGNETTE
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
mini whack 12
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
mini whack 10
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
mini popcorn 10 2 1
endday

# ================================================================ CH2 DAY 24
script c2_24
title The Warden
bars on
scene deep amir dalia gabriel prime
say |Day 24. A wide round room. Chains on the ceiling. A shape in the center, tall and made of dust and rusted bells. It turns its head.
say ???|NOT ALLOWED.
say Gabriel|Okay, I'm no longer holding the rope. I'm hiding behind it.
say ???|I AM THE WARDEN OF THE INN'S LOWEST DOOR. NO ONE CHECKS OUT.
say Prime|DUST DETECTED. LOTS OF IT. IT IS... RUDE.
emote dalia !
bars off
scene off
warp room0 1200
npc dalia room0 1000
npc gabriel room0 900
npc prime room0 1100
goal Fight the Warden.
mini fight 18 7 boss_Warden
ifnot skipped beaten
say |(The Warden stumbled and sat down. It looked tired.)
label beaten
fx flash
say |The Warden's chest cracks, and a swirl of rusted bells scatter across the floor. It slumps. A voice, small and relieved, comes out:
say Warden|...Thank you. I've been holding that door for such a long time.
say Amir|Who are you?
say Warden|I was the first guest. The first night porter. I forgot to leave.
say Gabriel|...Tansaouti?
say Warden|His great-great-whatever. The Inn keeps its porters. Even after.
set warden_beaten 1
# VIGNETTE
bars on
scene lobby amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |A door opens by itself, then politely closes.
say Adam|Got a minute? Quick game.
bars off
scene off
mini lights 3
bars on
scene outside amir prime
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
mini whack 10
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
mini popcorn 10 2 1
endday

# ================================================================ CH2 DAY 25
script c2_25
title Aftermath Picnic
bars on
scene inn amir dalia gabriel amine
cast amir 600
cast dalia 800
cast gabriel 1000
cast amine 1200
say |Day 25. Dalia declares a picnic. In the Inn. On the carpet. Under chandeliers. With sandwiches.
say Dalia|We beat a boss. We deserve a picnic.
say Amine|I brought snacks! And a blanket! And a second blanket! And paper hats!
emote amine !
say Gabriel|Why paper hats?
say Amine|Because you can't have a picnic without hats. That's science.
bars off
scene off
warp inn 600
npc dalia inn 900
npc amine inn 1100
goal Help catch the picnic food rolling off the table: talk to Amine.
await talk amine
say Amine|Bolt tripped over the blanket. The food is... everywhere.
mini catch 10 3 sandwiches 3
ifnot skipped picnic
say |(Amine caught the rest with a basket and a heroic leap.)
label picnic
fx confetti
say |The picnic is a mess. A beautiful, crumb-covered, joyful mess. Bots eat a cookie. A ghost piano plays a polka.
say Dalia|Today is a good day.
say Amir|It really is.
say Gabriel|I'm saying it once. This is nice.
say Amine|He said it! Everybody write down the date!
# VIGNETTE
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
mini lights 4
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
mini lights 3
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
mini whack 12
endday

# ================================================================ CH2 DAY 26
script c2_26
title A Letter From Below
bars on
scene inn amir aya_n
cast amir 700
cast aya_n 1000
say |Day 26. A white envelope on the front desk. No stamp. No return address. Aya holds it like it might bite.
say Aya@aya_n|It's addressed to "A. L-001, in the Inn, who's reading this".
say Amir|That's a lot of address for one envelope.
say Aya@aya_n|Open it. I dare you. No, I don't. Open it.
bars off
scene off
warp inn 800
npc aya_n inn 1000
goal Talk to Aya and read the letter.
await talk aya_n
say |The letter, on thin yellow paper, in handwriting that looks like mine after a bad dream.
say |"Dear Amir. If you're reading this, you found the room. Good. I couldn't. I tried for a long time. The door was always one floor lower than I could reach."
say |"Don't be afraid of the knocking. It isn't a threat. It's a hand on a door that won't open from this side."
say |"Be careful of the ash. It remembers things you don't. - A."
choose
> Who wrote this? => who
> Whoever it is, they're me. => me
label who
say Aya@aya_n|It looks like your handwriting.
goto fin
label me
say Aya@aya_n|Or someone who's been practicing your handwriting for a very long time.
label fin
say Amir|It's not a threat. It's a plea.
say Aya@aya_n|Then we'd better answer it.
set letter_read 1
# VIGNETTE
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
mini quiz 4 ilot14
bars on
scene room amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |A door opens by itself, then politely closes.
say Adam|Got a minute? Quick game.
bars off
scene off
mini lights 4
bars on
scene lobby amir prime
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
endday

# ================================================================ CH2 DAY 27
script c2_27
title Gabriel's Rope
bars on
scene deep amir gabriel
cast amir 600
cast gabriel 900
say |Day 27. The way down is a broken bridge over a dark gap. A rope is stretched across, tied to a rusty hook.
say Gabriel|This is why I carry a rope. I've been waiting for this day for years.
say Amir|You said you didn't know why you carried it.
say Gabriel|I lied. I always knew. I just didn't want to say it out loud.
anim gabriel bow
bars off
scene off
warp room0 1700
npc gabriel room0 1900
goal Talk to Gabriel at the broken bridge.
await talk gabriel
say Gabriel|I tie it. You walk. Hit each step when it lights up. If you miss, the plank drops.
mini timing 7 3 Cross_the_bridge 3
ifnot skipped crossed
say |(Gabriel tossed you the last length of rope and pulled you across. His arms shook. He said nothing.)
label crossed
say |On the far side, you both sit on the ground, breathing hard.
say Amir|You didn't have to hold the rope that tight.
say Gabriel|I did. Because it was you.
say Amir|...Thanks.
say Gabriel|Don't say anything. Don't make it weird.
set bridge_done 1
# VIGNETTE
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
mini pairs 4 5
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
mini quiz 4 ilot14
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
mini lights 4
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
mini lights 3
endday

# ================================================================ CH2 DAY 28
script c2_28
title Dust Storm
bars on
scene inn amir aya_n dalia gabriel
say |Day 28. The lamps all flicker at once. A whistle in the pipes. A wall of grey dust rolls across the Inn's lobby, wiping the carpet clean.
say Aya@aya_n|It's a dust surge! They're coming from the vents!
say Dalia|Dust wraiths! Dust WRAITHS!
say Gabriel|What are those?
say Dalia|I don't know. It sounded right.
fx shake
bars off
scene off
warp inn 500
npc aya_n inn 700
goal Hold the line! Defend the lamp core from the dust.
mini defend 3 5 1
ifnot skipped held
say |(The bots stood in front of the lamps. Bolt took the hardest hits.)
label held
fx flash
say |The last wraith pops like a soap bubble. Grey dust rains down. Every lamp in the lobby is still lit.
say Aya@aya_n|You held the line.
say Amir|I'd rather not hold it again.
say Aya@aya_n|You will.
set storm_held 1
# VIGNETTE
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
mini pairs 4 6
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
mini pairs 4 5
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
mini quiz 4 ilot14
endday

# ================================================================ CH2 DAY 29
script c2_29
title The Lamps Go Out
bars on
scene inn amir sofia tansaouti
say |Day 29. A morning that isn't. The lamps are all out. The Inn is a cave. Somewhere above, a faint ding as the elevator tries to reach us and fails.
say Sofia|Somebody cut the lamp circuit.
say Tansaouti@tansaouti|Or the dust ate it.
say Amir|We need to relight them. All four. In the dark. With no one noticing.
say Sofia|I can hear where the shadows are. Follow me.
fx dark
bars off
scene off
warp inn 300
npc sofia inn 700
goal Sneak through the dark Inn and relight the lamps. Don't stay in the beams.
mini sneak 4 3 2
ifnot skipped lit
say |(Sofia led you to every lamp with her eyes closed. You tried not to be impressed.)
label lit
fx lights
fx flash
say |The lamps catch, one after another. Warm gold, soft pink, the color of old photographs. The Inn breathes out.
say Sofia|I heard it sigh.
say Tansaouti@tansaouti|It's been waiting a long time to be lit again.
set lamps_lit 1
# VIGNETTE
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
mini popcorn 10 2 1
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
mini pairs 4 6
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
mini pairs 4 5
endday

# ================================================================ CH2 DAY 30
script c2_30
title Everyone Helps
bars on
scene room amir
cast amir 700
cast dalia -200
walk dalia 480 8 wait
say Dalia|Amir! Big news. Everyone in the building wants to help the Inn!
say Amir|Everyone?
say Dalia|Everyone! Even the ones you don't like!
emote dalia !
say |Dalia hands me a list. Names. Floors. Items. Doors to knock on. It's three pages long.
bars off
scene off
clearitems
goal Collect help from each floor: a blanket (Teen), a chair (Lethal), snacks (Special), a poster (Uncommon) and a rug (Rare).
spawn blanket teen 700
spawn chair lethal 900
spawn snacks special 1200
spawn poster unc 1500
spawn rug rare 1800
await items 5
say |A whole building's worth of small, kind things. Everyone says "for the Inn!" like it's a family member.
goal Take everything to the Further Inn.
await floor inn
say |At the Inn, bots unload everything into the lobby in a long, noisy line.
mini roundup 10 45 3
ifnot skipped unloaded
say |(Bolt rounded up the last few bots by hugging them.)
label unloaded
say Aya@aya_n|The Inn has never had this many guests.
say Amir|They're not guests.
say Aya@aya_n|No. They're residents.
set everyone_helped 1
clearitems
# VIGNETTE
bars on
scene inn amir dalia
cast amir 300
cast dalia 1100
walk dalia 700 5 wait
emote dalia !
anim dalia wave
say |Someone left a snack on the stairs. A tiny miracle.
say Dalia|Got a minute? Quick game.
bars off
scene off
mini whack 10
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
mini popcorn 10 2 1
bars on
scene lobby amir bolt
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
mini pairs 4 5
endday

# ================================================================ CH2 DAY 31
script c2_31
title The Rehearsal
bars on
scene inn amir sofia dalia
say |Day 31. The Inn is putting on a concert. Not a big one. A small one. For the Inn itself. For everyone who made it open.
say Sofia|I wrote it. I wrote it in my head. I need you to play the parts I can't.
say Dalia|I'm on triangle.
say Sofia|There isn't a triangle part.
say Dalia|Then I'm writing one.
bars off
scene off
warp inn 700
npc sofia inn 1100
npc dalia inn 900
goal Talk to Sofia at the piano.
await talk sofia
say Sofia|Rehearsal one. Hit every note on the beat. If you can, I'll let Dalia play her triangle.
mini rhythm 30 5 130
ifnot skipped rehearsed
say |(The Inn played the missing notes. It sounded better than you.)
label rehearsed
fx flash
say |The piano swells. The lamps pulse. Bots dance in a clumsy circle.
say Dalia|AM I ON TRIANGLE?
say Sofia|Yes. One note. At the end.
say Dalia|I'm going to be incredible.
# VIGNETTE
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
mini whack 12
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
mini whack 10
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
mini popcorn 10 2 1
endday

# ================================================================ CH2 DAY 32
script c2_32
title Concert at the Inn
bars on
scene inn amir sofia aya_n dalia gabriel
say |Day 32. The Inn's lobby is full. Residents from every floor. Bots in bow ties. Lamps arranged in a half circle. Chairs from every room.
say Aya@aya_n|Ladies, gentlemen, bots and ghosts. Welcome to the Further Inn's first concert.
say Sofia|Please be kind to the piano. It's nervous.
emote sofia ~
fx confetti
bars off
scene off
warp inn 800
npc sofia inn 1100
goal Take the stage: talk to Sofia.
await talk sofia
say Sofia|It's the whole song. Don't think. Just play.
mini rhythm 36 4 140
ifnot skipped played
say |(The piano played the rest on its own. Nobody noticed. Everyone applauded.)
label played
fx fireworks
fx confetti
say |The final chord rolls through the Inn. The lamps flare gold. The ghost piano holds the last note until the Inn itself seems to hum in harmony.
say Dalia|TRIANGLE!
say |One tiny ding. Everyone laughs.
say Aya@aya_n|Welcome home, Inn.
say Sofia|Welcome home, everyone.
set concert_done 1
# VIGNETTE
bars on
scene lobby amir prime
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
mini whack 12
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
mini whack 10
endday

# ================================================================ CH2 DAY 33
script c2_33
title The Last Key
bars on
scene deep amir dalia gabriel prime
say |Day 33. Under the Warden's round room, behind a collapsed shelf, a lever. Rusted. Tall. And labeled in Prime's very neat handwriting: "DO NOT PULL YET".
say Prime|I WAS SPEAKING TO MYSELF.
say Gabriel|You labeled a lever to yourself?
say Prime|IT IS A VERY IMPORTANT LEVER.
bars off
scene off
warp room0 1300
npc prime room0 1500
npc dalia room0 1400
npc gabriel room0 1600
goal Talk to Prime at the lever.
await talk prime
say Prime|THE LEVER OPENS THE LOWEST DOOR. BUT THE WAY IS SHAKING. THE WALLS ARE LOOSE.
say Prime|PULL, THEN RUN.
mini dodge 28 4 3
ifnot skipped ran
say |(Prime carried you the last fifty meters. It didn't comment. It was a very good dustpan.)
label ran
fx shake
say |Behind you, the lever clunks. A low note rolls through the whole Inn, up through the floor, through the elevator shaft, all the way to the roof.
say Dalia|Did the whole building hear that?
say Gabriel|The whole Reghaia heard that.
set last_key 1
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
mini lights 4
bars on
scene lobby amir bolt
cast amir 300
cast bolt 1100
walk bolt 700 5 wait
emote bolt !
anim bolt wave
say |A door opens by itself, then politely closes.
say Bolt|Got a minute? Quick game.
bars off
scene off
mini lights 3
bars on
scene outside amir adam_t
cast amir 300
cast adam_t 1100
walk adam_t 700 5 wait
emote adam_t !
anim adam_t wave
say |The building hums. Somebody laughs two floors away.
say Adam|Got a minute? Quick game.
bars off
scene off
mini whack 12
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
mini whack 10
endday

# ================================================================ CH2 DAY 34
script c2_34
title Button 18
bars on
scene elev amir prime dalia
say |Day 34. Prime's rebuilt the elevator panel. A new brass plate is bolted in next to the Inn button. A single number: 18.
say Prime|I FIXED THE ELEVATOR. IT NOW GOES TO LEVEL EIGHTEEN.
say Dalia|There's a Level 18?!
say Prime|THERE HAS ALWAYS BEEN A LEVEL EIGHTEEN. I MERELY GAVE IT A BUTTON.
say Amir|Why now?
say Prime|BECAUSE IT KNOCKED.
fx shake
say |A warning light flares. Something heavy is rolling up the elevator shaft toward the Inn.
bars off
scene off
warp inn 500
npc prime inn 700
npc dalia inn 900
goal Defend the elevator doors!
mini defend 4 5 2
ifnot skipped held
say |(The bots plugged the doors with their bodies. It worked, somehow.)
label held
say |The last wraith pops. The doors close. The button glows soft green.
say Prime|THE LIFT IS READY.
say Dalia|Ready for what?
say Prime|FOR THE KNOCK TO COME UP. OR FOR US TO GO DOWN.
set button18 1
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
mini quiz 4 ilot14
bars on
scene room amir prime
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
mini lights 3
endday

# ================================================================ CH2 DAY 35
script c2_35
title Check-In
bars on
scene inn amir aya_n tansaouti sofia
say |Day 35. The Further Inn is full. The lamps are warm. The piano plays something low and gentle. The grey-coated guest from Room 1 finally steps out.
say ???|It's time.
say Aya@aya_n|Time for what?
say ???|To check out.
emote aya_n !
say |He takes off his hat. Underneath, a face that's nobody's and everybody's. Dust and brass and a very old smile.
say ???|I'm the Inn. I've been waiting for someone to ask my name.
choose
> What's your name? => name
> Thank you for having us. => thanks
label thanks
say ???|Thank you for staying.
goto after
label name
say Inn|Further. They call me Further. Because I'm always a little further than anyone expects.
label after
say Inn|You lit my lamps. You played my piano. You answered my knocks. Not one guest has done all three.
say Inn|I have a last key for you, Amir. The one that isn't brass or black.
say |He places a small silver key in my palm. It's warm, and it's humming.
say Inn|The lift to Level 18 will take you. But it's a long way down. Take your friends. Take your bots. Take the piano, if it'll come.
say Aya@aya_n|You're leaving?
say Inn|I'm not leaving. I'm the floor. You'll feel me under your feet the whole way.
fx flash
bars off
scene off
set inn_open 2
card TO BE CONTINUED|Chapter 3: Lowest Point is now open.
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
mini pairs 4 5
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
mini quiz 4 ilot14
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
mini lights 4
endday
)IL";
