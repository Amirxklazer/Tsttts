// story_ch2b.hpp - CHAPTER 2: FURTHER INN, days 10-19 (Act 2: The Ledger)
#pragma once
static const char* STORY_CH2B = R"IL(
# ================================================================ CH2 DAY 10
script c2_10
title Coffee Machine Crisis
bars on
scene room amir
cast amir 700
cast bolt -200
walk bolt 520 6 wait
emote bolt ...
say Bolt|Anes called. His coffee machine escaped.
say Amir|Machines don't escape.
say Bolt|This one has legs. He added legs. We don't ask why.
bars off
scene off
clearitems
npc anes common 700
goal Go to the Common floor and talk to Anes (C-001).
await talk anes
say Anes|It left through the window. It was fine yesterday. We talked. I said "thanks for the espresso" and it winked.
say Amir|Winked how? It's a machine.
say Anes|With a little light. Look, I need three things: the machine, the cups, and the beans. They all ran in different directions.
say |Across the Common floor, a bubbling sound. Coffee beans are pouring down the hall like gold rain.
mini catch 12 3 coffee_beans 2
ifnot skipped beans
say |(Anes found a bag in the corner. He called it "emergency beans" and wept.)
label beans
say |At the end of the hall, a small machine on spidery legs sits under a plant, trembling. Anes picks it up like a baby.
say Anes|It's okay. It's okay. You're home.
choose
> Maybe don't give it legs next time. => legs
> It's kind of cute. => cute
label legs
say Anes|It's a coffee machine. It deserves to see the world.
goto fin
label cute
say Anes|Right?! Thank you!
label fin
say Anes|I owe you one coffee. Or twelve. Come back anytime.
# VIGNETTE
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
say |A door opens by itself, then politely closes.
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
endday

# ================================================================ CH2 DAY 11
script c2_11
title Ink and Ash
bars on
scene inn amir kenzy sofia
say |Day 11. Haydar has set up a table in the Inn lobby covered in wires, notebooks and what looks like a very sad radio.
say Haydar|The ink in the ledger isn't ink. It's ash and water. Someone wrote it with the ash from something burned.
say Sofia|It sounds like a pattern. Under the page. A rhythm.
say Haydar|My radio can pick it up. If we tap it back, it might answer.
say Amir|Answer who?
say Haydar|I don't know. That's the fun part.
bars off
scene off
warp inn 700
npc kenzy inn 1100
npc sofia inn 1300
goal Talk to Haydar at the lobby table.
await talk kenzy
say Haydar|Press each button when its light hits the line. My radio hears your taps. Don't stop, even if you miss.
mini rhythm 24 6 115
ifnot skipped tapped
say |(Haydar tapped the rest. His timing was better than yours. He didn't say anything. His eyebrow did.)
label tapped
fx flicker
say |The radio crackles. A faint voice, so far away. Words in the hiss: "...Amir... below... Room... zero..."
say Haydar|It said your name.
say Sofia|It said it twice.
say Amir|Okay. I'm going to sit down now.
set radio_heard 1
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
mini lights 4
endday

# ================================================================ CH2 DAY 12
script c2_12
title The Locked Wing
bars on
scene inn amir tansaouti
cast amir 640
cast tansaouti 1050
say |Day 12. At the east end of the Inn, behind a heavy velvet curtain, a corridor nobody mentioned.
say Tansaouti@tansaouti|This is the Locked Wing. Rooms 2 through 20. They haven't been opened in my time.
say Amir|Your time is long.
say Tansaouti@tansaouti|It's felt long. But the keys are all gone, so I only know what they sound like.
bars off
scene off
warp inn 1900
npc tansaouti inn 2050
goal Talk to Tansaouti by the curtain.
await talk tansaouti
say Tansaouti@tansaouti|The door isn't locked. It's just... easy to get lost behind. The corridor shifts when you aren't looking.
say Tansaouti@tansaouti|Find the green exit light on the other side. And bring back whatever you find. Three bottles of water, if you can. It gets thirsty.
mini maze 3 4
ifnot skipped through
say |(The corridor spat you out at the end. It seemed almost sorry.)
label through
say |You come out on the Inn lobby side with three cold bottles of water and one slightly smug bot sticker on your jacket.
say Tansaouti@tansaouti|You made it. That's the first time anyone has since... a long while.
say Amir|What's in the Wing?
say Tansaouti@tansaouti|Rooms. Empty. Except one door at the very end, with no number. That's what the corridor protects.
set found_nodoor 1
# VIGNETTE
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
mini pairs 4 6
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
mini pairs 4 5
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
mini quiz 4 ilot14
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
mini lights 4
endday

# ================================================================ CH2 DAY 13
script c2_13
title Piano Duet
bars on
scene inn amir sofia
say |Day 13. The piano's been waiting for days. Sofia says it keeps playing the same first four notes, like it's holding its breath.
say Sofia|Today's the full song. All of it. I need someone to remember with me.
say Amir|I can't play piano.
say Sofia|You don't have to. You just have to press the right glowing key at the right moment.
bars off
scene off
warp inn 700
npc sofia inn 1100
goal Talk to Sofia at the piano.
await talk sofia
say Sofia|It's longer today. Seven notes. Watch first. Then repeat.
mini simon 7 3 28
ifnot skipped played
say |(The piano finished the tune alone. It was gentle about it.)
label played
fx flash
say |The last note rings and fades. Behind the wall, something clicks. A small brass panel pops open beside the keys.
say Sofia|A key. A brass key. It says "2".
say Amir|The Locked Wing.
say Sofia|The piano wanted us to have it.
set key2 1
# VIGNETTE
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
mini popcorn 10 2 1
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
mini pairs 4 6
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
mini pairs 4 5
endday

# ================================================================ CH2 DAY 14
script c2_14
title Bot Parade
bars on
scene garage amir dalia bolt
cast amir 500
cast dalia 800
cast bolt 1100
say |Day 14. Dalia has organized a parade. Forty Cleaning bots, all in party hats, marching through the Inn lobby to introduce them to the guests.
say Dalia|Everybody pick a bot! Mine is Mopsy!
say Bolt|Mine is... me!
emote bolt !
say Amir|Bolt, you ARE a bot.
say Bolt|And a good one!
bars off
scene off
warp inn 700
clearitems
goal Round up the bots for the parade at the Inn lobby.
mini roundup 8 40 2
ifnot skipped paraded
say |(The bots lined up by themselves. A little too perfectly.)
label paraded
fx confetti
say |Forty bots march in a long, clanking line through the lobby. Tiny flags. A drum made from a pot. Dustin hides under a sofa because there's yellow tape somewhere.
say Aya@aya_n|This is the best thing that has ever happened in the Further Inn.
say Dalia|Even better than the piano?
say Aya@aya_n|The piano is a ghost. It doesn't count.
choose
> Join the parade. => join
> Watch from the lobby. => watch
label join
say |I march behind Bolt. We hit every wall.
say Bolt|ZOOM! BONK! ZOOM! BONK!
goto fin
label watch
say |I lean on the front desk. A little bot rolls up and hands me a tiny paper flag.
label fin
say |At the end of the parade, the Room 1 door cracks open. The grey-coated guest watches, motionless. He tips his hat. Then he closes the door.
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
mini whack 10
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
mini popcorn 10 2 1
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
mini pairs 4 6
endday

# ================================================================ CH2 DAY 15
script c2_15
title Moth Season
bars on
scene inn amir aya_n
cast amir 600
say |Day 15. The moths are back. Not hundreds. Thousands. They've formed a cloud above the Inn's chandelier that spells "NO".
say Aya@aya_n|The moths have opinions now.
say Amir|They're chewing the carpets.
say Aya@aya_n|They're chewing everything. They read the ledger. They want the page.
bars off
scene off
warp inn 500
npc aya_n inn 900
goal Talk to Aya.
await talk aya_n
say Aya@aya_n|Swat them. Please. Gently. They're still guests technically.
mini fight 16 6 moths
ifnot skipped fought
say |(The moths dispersed after sniffing your jacket and deciding it was boring.)
label fought
say |The last moth settles on the front desk. It lays one tiny, perfect letter in the dust with its wing: "B".
say Aya@aya_n|B. For what?
say Amir|For "below"?
say Aya@aya_n|Or "bored". Or "bring snacks". Moths are vague.
# VIGNETTE
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
endday

# ================================================================ CH2 DAY 16
script c2_16
title Tansaouti's Past
bars on
scene inn amir tansaouti
cast amir 700
cast tansaouti 1050
say |Day 16. Tansaouti is sitting alone behind the front desk, polishing a brass nameplate. It says nothing. It's blank.
say Amir|Are you okay?
say Tansaouti@tansaouti|I was supposed to remember something today. I can't. I only remember the feeling of forgetting.
bars off
scene off
warp inn 700
npc tansaouti inn 1050
goal Talk to Tansaouti at the front desk.
await talk tansaouti
say Tansaouti@tansaouti|There was a person. A long time ago. Who checked in and never checked out. They gave me this plate. It had a name on it. I've scrubbed it blank over the years.
choose
> Maybe it wasn't a person. Maybe it was the Inn. => inn
> What do you remember about them? => person
label inn
say Tansaouti@tansaouti|...That's a thought I hadn't had.
goto go
label person
say Tansaouti@tansaouti|A hat. A laugh. A way of leaving doors open. Not much.
label go
say Tansaouti@tansaouti|Tonight the guest in Room 1 will walk the halls. I want to see if he's the one. Come with me.
say |Midnight. The corridors are dark and the lamps hum too loud. We need to follow the grey coat without being seen.
mini sneak 3 3 2
ifnot skipped followed
say |(You followed for a while, then lost him. Tansaouti found him at the stairs.)
label followed
say |At the foot of the old stairs, the grey coat stops. He doesn't turn. He just says, in a voice made of dust:
say ???|Soon.
say |And he walks down into a wall that wasn't a stairwell a second ago, and is gone.
say Tansaouti@tansaouti|...He wasn't the one. But he knows the one.
set coat_gone 1
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
mini lights 3
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
mini whack 12
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
mini whack 10
endday

# ================================================================ CH2 DAY 17
script c2_17
title The Key Ring
bars on
scene inn amir sofia dalia
say |Day 17. Sofia found a brass key ring in the piano. Eleven hooks, three keys. Eight missing.
say Dalia|We find the keys! Like a treasure hunt!
say Sofia|They're not lost. They're hidden. By someone.
say Amir|By who?
say Sofia|By someone who wanted us to look.
bars off
scene off
clearitems
warp inn 500
goal Find 3 hidden keys in the Inn: look near the lobby, the lounge and the stairs.
spawn key inn 700
spawn key inn 1500
spawn key inn 2000
await items 3
say Amir|Three keys. Three keys that definitely weren't here yesterday.
say Dalia|Brass. Warm. Humming.
mini timing 6 4 Turn_the_keys 3
ifnot skipped turned
say |(The keys turned themselves. Dalia took credit anyway.)
label turned
say |Three clicks. A soft rumble under the carpet. A hidden panel at the foot of the stairs swings open to a narrow, dusty tunnel.
say Dalia|That is the coolest thing I've ever seen.
say Sofia|It leads down. We'll go in tomorrow.
set tunnel_open 1
clearitems
# VIGNETTE
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
mini whack 12
endday

# ================================================================ CH2 DAY 18
script c2_18
title Steam Down Below
bars on
scene inn amir gabriel
cast amir 640
cast gabriel 1000
say |Day 18. A boiler room behind the hidden panel. Rusted pipes. Steam hissing through gaps. Gabriel is already there, holding his rope.
say Gabriel|I didn't come to help. I came to hold the rope.
say Amir|Of course you did.
say Gabriel|If you fall, I'll feel useful.
bars off
scene off
warp inn 2000
npc gabriel inn 2150
goal Walk to the boiler door and talk to Gabriel.
await talk gabriel
say Gabriel|The boiler room is rigged. The pipes burst on a schedule. Run through, dodge the steam, don't touch anything hot.
say Gabriel|Honestly? I'd rather have bees.
mini dodge 20 4 1
ifnot skipped through
say |(You came out with singed sleeves and a new respect for pipe maintenance.)
label through
say |On the far wall, behind a curtain of steam, a brass plate. No number. Just a keyhole shaped like a small hand.
say Gabriel|That's the door Tansaouti talked about.
say Amir|It's the door at the end of the Locked Wing. But from the other side.
say Gabriel|So the Inn has two doors to the same room?
say Amir|Or one door that's everywhere.
set boiler_door 1
# VIGNETTE
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
mini quiz 4 ilot14
bars on
scene room amir bolt
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
mini lights 3
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
mini whack 12
endday

# ================================================================ CH2 DAY 19
script c2_19
title The Knock Answers
bars on
scene inn amir dalia gabriel sofia
say |Day 19. Midnight. The lobby is lit by every lamp in the Inn. Haydar's radio hums on the front desk.
say Sofia|It's coming. Three knocks. A pause. Three more.
say Dalia|What if we knock back?
say Gabriel|That's the stupidest idea I've ever heard.
say Dalia|And?
say Gabriel|...And I'm in.
emote amir !
bars off
scene off
warp inn 900
npc dalia inn 1100
npc gabriel inn 1250
npc sofia inn 1400
goal Gather at the floor where the knocks come from: the middle of the lobby. Talk to Sofia.
await talk sofia
say Sofia|Knock the same way it knocks. Three. Pause. Three. On the beat. Don't rush.
mini rhythm 24 5 110
ifnot skipped knocked
say |(Dalia knocked the rest. Her knocks were a bit rude.)
label knocked
fx shake
say |Silence. Then, from under the floor, a single answering knock. Slow. Heavy. Patient.
fx flicker
say |And then something slides across the lobby floor, from the wall to Amir's feet. A key. Black. Cold. With a tag.
say Amir|"For Room 000. Come down."
say Dalia|It knows us.
say Gabriel|It knows YOU.
say Sofia|It knew us all along.
set black_key 1
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
mini pairs 4 5
bars on
scene inn amir prime
cast amir 300
cast prime 1100
walk prime 700 5 wait
emote prime !
anim prime wave
say |Something small happens, and it matters more than it should.
say Prime|Got a minute? Quick game.
bars off
scene off
mini quiz 4 ilot14
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
mini lights 4
endday
)IL";
