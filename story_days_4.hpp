// story_days_4.hpp - Days 22 to 31 (the finale arc)
#pragma once
static const char* STORY_DAYS_4 = R"IL(
# ================================================================ DAY 22
script day_22
title The Grey Door
scene room amir
say |Day 22. Kenzy's readings are pinned to my wall. A dot on a map. A door with no handle. A key with a note.
say Amir|Today I stop being the person who says "I'll come back with friends".
scene off
goal Borrow the key Iyad found: talk to Iyad on the Common floor (C-005).
await talk iyad
say Iyad|The key! You want the key? It's yours. Honestly it's been humming in my box for weeks. It's getting rude.
say |The key is dark metal, warm to the touch. A paper tag still hangs from it: "FOR WHEN IT KNOCKS".
npc dalia park2 1750
npc gabriel park2 1650
obj greydoor park2 1900 Grey door
goal Take the elevator down to Parking 2. Dalia and Gabriel are waiting.
await floor park2
say Dalia|You came! I brought snacks. And a flashlight. And a very big sense of dread.
say Gabriel|I brought a rope. Don't ask.
choose
> Are we really doing this? => really
> Let's open it. => open
label really
say Gabriel|If we don't, we'll wonder every night. I'd rather know.
say Dalia|Same. But with snacks.
label open
goal Open the grey door at the east end of Parking 2.
await use greydoor
ifnot brass_token nobrass
say |You press the brass token from the arcade against the door. It sinks into the concrete like a coin into water.
label nobrass
say |You slide the key against the door. A handle appears out of nothing. It turns without any effort.
say |The door opens onto a hallway of yellow wallpaper and a carpet that smells like wet cardboard. And one very distant hum.
set door_opened 1
scene backrooms amir dalia gabriel
say Dalia|It's the Backrooms, isn't it. The one you fell into.
say Amir|Same hum. Same wallpaper. Same bad vibes.
say Gabriel|Stay together. Don't yell.
say Amir|I yelled last time. It yelled back.
say Gabriel|Then don't yell.
mini maze 3 5
ifnot skipped through
say |(The hum stepped aside a little, like it wanted you to pass.)
label through
say |A heavy steel door, painted dull orange. A sign: "SERVICE CORRIDOR 0. LEVEL 18."
say |At the end of the corridor, in a cradle of cables, sits a very old Cleaning bot. Its eyes are dark. Its antenna is bent.
say Dalia|That's... a bot.
say Gabriel|That's the first bot. Look at the nameplate.
say |A faded plate on the cradle: "UNIT ZERO. PRIME."
say Amir|It's asleep.
say Gabriel|Let's leave it. For now. We need a plan.
scene off
fx fadeout
wait 40
warp park2 1700
fx fadein
say Dalia|Well. That happened.
say Amir|We have a plan. Step one: come back.
endday

# ================================================================ DAY 23
script day_23
title What Prime Was
scene room amir
say |Day 23. If Prime is real, someone in this building has to know where it came from. The bots might know. They don't tell humans things. But they might tell me.
scene off
goal Go down to the 14 Cleaning bots parking and talk to Sweepy.
await talk sweepy
say Sweepy|Prime. Yes. We call him... the First. The first of the Cleaning bots. He cleaned the whole building by himself, long ago.
say Sweepy|He was very good. Too good. The building was so clean, there was nothing left for him to do.
goal Talk to Zed.
await talk zed
say Zed|He started cleaning the Backrooms. Because they were dusty. And no one told him it wasn't a real place.
say Zed|One day he went in and didn't come back. His signal just... stopped. They sealed the door.
goal Talk to Grim.
await talk grim
say Grim|He's not angry. He's tired. A bot that cleans something forever and is thanked by no one will eventually stop hearing "thank you".
say Grim|I think the knocking is him asking someone to say it.
say Amir|Say what?
say Grim|Thank you.
goal Ask Youcef for tools (Main floor, M-005).
await talk youcef
say Youcef|You're going to the east door? ...Of course you are. Take this toolbox. A soldering iron, oil, a spare antenna. You'll need it.
say Youcef|And Amir? If it works... I'd like to say thank you to him too.
say Amir|You knew?
say Youcef|I've heard that knock every night for ten years.
goal Go to Parking 2 and open the grey door.
obj greydoor park2 1900 Grey door
await use greydoor
say |The door opens, hum and all. Dalia and Gabriel step out of the shadow behind you. You hadn't noticed them following.
say Dalia|You didn't think we'd let you go alone?
scene backrooms amir dalia gabriel
mini maze 4 6
ifnot skipped there
say |(The hum led you straight to the corridor, as if it was expecting you.)
label there
say |Service Corridor 0. The orange door. The cradle of cables. The old bot, eyes dark.
say Amir|Hello, Prime. I'm Amir. I'm... sorry we're so late.
say |I place a hand on its dented chassis. The eyes flicker once. Twice.
fx flash
say Prime|...Systems restoring. Cleaning clearance: pending.
say Gabriel|It's awake.
say Prime|INTRUDERS. DUST. CLEAN. CLEAN. CLEAN.
fx shake
say Dalia|Okay, that's not a thank you!
say |The cables snap loose. The antenna straightens. Prime rises from the cradle, glowing orange.
scene off
endday

# ================================================================ DAY 24
script day_24
title Unit Zero
scene backrooms amir dalia gabriel prime
say Prime|DUST DETECTED. HUMAN DUST. SWEEP. SWEEP. SWEEP.
say Gabriel|He thinks we're dust.
say Dalia|We're not dust! We just have a lot of skin cells!
say Amir|Prime! It's Amir! I'm here to say thank you!
say Prime|THANK YOU. THANK YOU. THANK YOU. NO MEMORY OF THANK YOU. SWEEP.
say Amir|Then I'll have to say it with a toolbox.
scene off
toast Press A to swing. Dodge Prime's hits.
mini fight 1 7 boss_Prime
ifnot skipped beaten
say |(Prime's battery ran low on its own. It slumped in front of you.)
label beaten
scene backrooms amir dalia gabriel prime
say |Prime stops mid-sweep. A tiny sound. A beep, followed by another. Then a long, tired sigh from a speaker that hasn't been used in years.
say Prime|...Amir.
say Amir|Hi.
say Prime|You... said thank you.
say Amir|I did. I'm saying it again. Thank you for cleaning. For a very long time.
say Prime|It was... a long time. I was so tired. No one said it. I kept knocking.
say Dalia|We heard you. We heard you every night.
choose
> Do you want to come back with us? => free
> Do you want to stay here? => stay
label free
set prime_free 1
say Prime|Back... to the building? To the other bots? I would... like that.
say Gabriel|They've been waiting. In their own way.
goto end24
label stay
set prime_stay 1
say Prime|This corridor is mine. I'll keep it clean. But... I would like visitors. Sometimes.
say Dalia|We'll visit. We'll bring snacks. And a mop for you to critique.
label end24
say Prime|The wall of yellow is tiring. I will fix it. Slowly. One wall at a time.
say |The orange door at the end of the corridor swings open by itself. Light spills in. It smells of rain and warm bread.
scene off
fx fadeout
wait 40
warp park2 1700
ifnot prime_free noprime
npc prime bots 2140
label noprime
fx fadein
say Dalia|I can't believe it. We did it.
say Gabriel|We talked to a bot and it said thank you back. I'll remember that.
say Amir|Let's tell the others.
endday

# ================================================================ DAY 25
script day_25
title The Bot Picnic
bars on
scene room amir
cast amir 700
cast dalia -200
walk dalia 420 7 wait
emote dalia !
anim dalia spin
fx confetti
say |Day 25. Dalia has an idea. It's covered in glitter, has no budget, and involves forty Cleaning bots.
bars off
scene off
ifnot prime_free nopr
npc prime bots 2140
label nopr
goal Talk to Dalia on the Main floor (M-002).
await talk dalia
say Dalia|The bots deserve a day off. A real one. A picnic. On the roof. With snacks and a good view and no mops allowed.
say Amir|Do bots eat snacks?
say Dalia|They like the idea of snacks. It's the thought that counts.
goal Go down to the bots parking and gather everyone for the picnic.
await floor bots
say |The bots are all over the parking lot, in the middle of a game none of them will admit to. Bolt is in the lead.
ifnot prime_free noprime2
say Prime|Amir. The others are... excited. I have not seen them excited in years.
label noprime2
say Sweepy|A picnic? On the ROOF? Is that allowed? Who's bringing the dust?
say Mopsy|We're not bringing dust. It's a picnic, not a cleanup.
say Zed|I'm coming. Don't read into it.
say Amir|Okay! Everyone gather round. Walk to the ramp. Don't run.
say Bolt|WHY NOT RUN?!
mini roundup 8 50
ifnot skipped gathered
say |(The bots decided to line up on their own. Mostly because Sparkle announced a parade.)
label gathered
say |Eight bots in a row. Some beeping, some humming, one muttering about regulations.
goal Take the elevator up to the Roof.
await floor roof
scene roof amir dalia gabriel amine
say Amine|WE HAVE SNACKS! AND BOTS! AND A VIEW!
say Gabriel|This is the best idea Dalia has ever had.
say Dalia|I know. Don't tell Amyas.
say Sparkle|BEHOLD, the SKY!
say Grim|It's... bigger than I remembered. And nicer. And brighter. I don't hate it.
say Zed|Don't tell anyone I said it, but... it's okay.
choose
> Raise a toast to the bots. => toast
> Sit and watch the sunset. => sunset
label toast
set picnic_toast 1
say Amir|To the bots! To all the floors you've cleaned. Thank you.
say Mopsy|...Thank you. Nobody ever says that.
goto fin
label sunset
say |The sun slides behind the skyline, turning the whole roof orange. Forty small lights blink in the dusk like a second set of stars.
label fin
say Dalia|Okay. Next week. I have another idea. It's bigger. It involves a banner.
say Amir|Why do I feel scared?
scene off
endday

# ================================================================ DAY 26
script day_26
title The Banner
scene room amir
say |Day 26. Dalia's idea has a name now. It's called "Îlot14 Day". A party. On the roof. In five days. With a banner the size of a wall.
scene off
goal Talk to Dalia on the Main floor (M-002).
await talk dalia
say Dalia|Okay. Here's the plan. Everyone in the building. The roof. A party. And a banner on the far end of the roof, so it can be seen from the main road.
say Amir|How big is the banner?
say Dalia|Twelve meters.
say Amir|Who's carrying it?
say Dalia|You are. Gabriel already hurt his back on the practice run.
choose
> Okay. I'll do it. => ok
> Why me? => why
label why
say Dalia|Because you're the only one who has actually crossed the roof. You know the way.
label ok
say Dalia|Youcef has a rope. Gabriel has the poles. I have a tape measure. Go!
goal Take the elevator up to the Roof.
await floor roof
say |The roof at noon. Banner rolled on my shoulder, pole under my arm. The far end of the roof looks much farther than it did last time.
say Amir|Okay. Run. Jump. Hang a banner. Easy.
mini roof 2
say |At the far end, I hook the banner onto the pole. It unrolls with a soft snap. "ÎLOT14 DAY" in giant orange letters.
ifge stars 4 many
say Amir|It's perfect. It's perfect. It's... crooked, but it's perfect.
goto back
label many
say Amir|It's perfect. And I even found a bunch of stars on the way. The roof is stranger than I thought.
set stars_party 1
label back
goal Tell Dalia the banner is up (Main floor, M-002).
await talk dalia
say Dalia|I saw it from my balcony! It's HUGE! You did it!
say Dalia|The party is going to be amazing. I can feel it. Which, as you know, is a very dangerous thing to say.
endday

# ================================================================ DAY 27
script day_27
title Supplies
scene room amir
say |Day 27. A to-do list on my door in Dalia's handwriting: "8 things. 8 floors. By tonight. No excuses. Love, D."
scene off
clearitems
spawn balloons lobby 800
spawn cake common 610
spawn speakers lethal 910
spawn string_lights unc 610
spawn chairs main 610
spawn plates rare 1210
spawn paint teen 610
spawn confetti special 610
goal Collect 8 party supplies from 8 floors: Lobby, Common, Lethal, Uncommon, Main, Rare, Teen and Special.
toast Items lie near the elevator or the doors on each floor.
await items 8
say Amir|Balloons, cake, speakers, lights, chairs, plates, paint and confetti. Eight things. Done. I need a nap.
goal Bring everything to Dalia on the Main floor.
await talk dalia
say Dalia|All of it?! Even the confetti?! I thought the confetti would take a week!
say Amir|Confetti was on the Special floor. Kenzy guarded it with a very small flag.
say Dalia|That's why I love this building. Okay. The party is in four days. Tomorrow we rehearse.
clearitems
endday

# ================================================================ DAY 28
script day_28
title Rehearsal
scene room amir
say |Day 28. Dalia texted me at 6 AM: "I cannot do this. Please come."
scene off
goal Find Dalia on the Main floor (M-002).
await talk dalia
say Dalia|I'm supposed to say a few words at the party. A speech. In front of everyone. I wrote it ten times. I threw it away ten times.
say Dalia|What if my voice breaks? What if I forget? What if the bots start beeping?
choose
> The bots always beep. => beep
> You'll be great. => great
> Do you want me to stand next to you? => stand
label beep
say Dalia|That's... true. They beep at everything. Even speeches. Okay. That helps.
goto start
label great
say Dalia|You say that to everyone. But thank you.
goto start
label stand
set dalia_support 1
say Dalia|Would you? Right next to me? That would help a lot.
label start
say Dalia|Okay. Let me practice. Count me in. A steady rhythm. Like a song.
mini timing 7 3 Stage_rhythm
ifnot skipped practiced
say |(Somehow the rehearsal went fine on its own. Dalia pretended to be very impressed with herself.)
label practiced
say Dalia|I did it! I made it through! No, you did it. No, I did.
say Gabriel|Stop. Both of you did.
say Dalia|Thank you, Amir. I think I can do it now.
say Amir|Anytime.
endday

# ================================================================ DAY 29
script day_29
title Storm Warning
bars on
scene room amir
cast amir 700
fx rain
fx shake
anim amir shake
say |Day 29. A very odd sky. Heavy and grey and bruise-colored. The window rattles. Thunder, far away, grumbles like a hungry elevator.
bars off
scene off
fx rainoff
goal Take the elevator up to the Roof. Gabriel says the banner pole is loose.
await floor roof
scene roof amir gabriel amine
say Gabriel|The pole's holding. Barely. We need to tie it down before the wind picks up.
say Amine|I volunteer to hold the rope! I've done this kind of thing before!
say Gabriel|You have not.
say Amine|I've seen it in movies!
say |A bolt of lightning cracks over the skyline. The rooftop water tank shudders. A tiny panel on its side pops open, and out spills a dark, buzzing cloud.
say Amine|...Hornets.
say Gabriel|Again?!
say Amir|They must have moved here after the tree.
say Amine|We have unfinished business, you and I!
choose
> Fight together! => together
> Cover the banner first. => cover
label cover
set banner_saved 1
say Gabriel|Good thinking! Amine, hold the corner! Amir, swat!
goto fight
label together
say Gabriel|Shoulder to shoulder. Don't scatter.
label fight
scene off
toast Press A to swing. This is a bigger swarm than before.
mini fight 12 6 hornets
ifnot skipped won29
say |(The thunder rolled over the swarm and scattered it. Nobody asked how.)
label won29
scene roof amir gabriel amine
say |The last hornet disappears into the storm. The first drops of rain fall. The banner snaps in the wind, still tied.
say Amine|I'm fine. Totally fine. A little hornet-sting-y. That's all.
say Gabriel|Inside. Now. Before the lightning gets ideas.
say Amir|Four days of rain and a rooftop party. What could go wrong?
say Amine|Don't say it.
scene off
endday

# ================================================================ DAY 30
script day_30
title The Eve
scene room amir
say |Day 30. The storm has passed. The sky is washed clean. Tomorrow is Îlot14 Day. Everyone in the building is quietly doing something important.
scene off
set bonds 0
goal Say goodnight to your friends: start with Gabriel (M-004).
await talk gabriel
say Gabriel|Hey. You look calmer than I expected. I'm proud of you.
choose
> Thanks, Gabriel. For everything. => thanks
> I'm terrified. => terr
label thanks
add bonds 1
say Gabriel|Anytime. Now go sleep.
goto n1
label terr
say Gabriel|Good. Terrified people are careful. You'll be great.
label n1
goal Say goodnight to Dalia (M-002).
await talk dalia
say Dalia|Speech ready. Banner up. Snacks stocked. I'm so nervous I might fly away.
choose
> I'll be there. Right next to you. => there
> Don't fly away. => fly
label there
add bonds 1
say Dalia|I know. Thank you. That's what makes it possible.
goto n2
label fly
say Dalia|I'll try. No promises. Wind has been unpredictable lately.
label n2
goal Say goodnight to Amine on the Special floor (S-001).
npc amine special 600
await talk amine
say Amine|The night before Îlot14 Day! And I'm here, with a friend, in a building with 17 floors and one very polite bot.
choose
> I'm glad you came. => glad
> You owe me snacks. => snacks
label glad
add bonds 1
say Amine|Me too. Better than any bus ride I've ever taken.
goto n3
label snacks
say Amine|I owe you SO many snacks. Tomorrow. I'll bring them all. In a wheelbarrow.
label n3
goal Say goodnight to Amyas on the Teen floor (T-001).
await talk amyas
say Amyas|Hey. You came. I... wasn't expecting you to.
say Amyas|Tomorrow, don't be late. And don't ask for free ice cream. I'll bring some anyway.
choose
> I wouldn't miss it. => miss
> You're being nice. => nice
label miss
add bonds 1
say Amyas|Good. Neither would I. Go to bed.
goto fin
label nice
say Amyas|Don't get used to it. It's a once-a-year special.
label fin
say |A quiet elevator ride home. The hum sounds almost like a lullaby tonight. Somewhere far below, a very old bot is humming along.
endday

# ================================================================ DAY 31
script day_31
title Îlot14 Day
bars on
scene room amir
cast amir 700
fx confetti
emote amir !
say |Day 31. The big day. The banner is flapping on the roof. The bots are polished. The whole building smells like cake.
bars off
scene off
goal Go to the Main floor and find Dalia (M-002). It's time.
await talk dalia
say Dalia|The speech! The party! Everything! Let's go! Let's go! Let's go!
say Dalia|Roof. Now. Come on!
goal Take the elevator to the Roof.
await floor roof
scene roof amir dalia gabriel
say |The roof is packed. Residents of every floor, bots in party hats, streamers snapping in the breeze. Even the water tank has a tiny paper crown.
say Gabriel|You made it. Dalia's about to speak.
say Dalia|Ahem. Hello, everyone. Thank you for coming. I wrote a speech. It was bad. I threw it away. So here's the truth.
say Dalia|This building is strange. It hums. It has secret doors and bots with personalities and an elevator with moods. And it is home.
say Dalia|To all of you who made it so, thank you. And now, Amir has something to say.
choose
> Raise a toast. => toast
> Say a few words. => words
> Pass the mic to Gabriel. => pass
label toast
set finale_toast 1
say Amir|To the 14. To everyone in it. And to the ones who knocked until we answered.
goto fire
label words
set finale_words 1
say Amir|I fell through a floor, got chased by hornets, and made friends with a boss fight. It was the best month of my life. Thank you.
goto fire
label pass
set finale_pass 1
say Gabriel|...Fine. To... people. And snacks. And bots. Okay, that's all.
say Dalia|That was beautiful.
label fire
say Amine|FIREWORKS! Is it time for fireworks?!
say Dalia|Amir, the launcher is on the far end of the roof. You have to run it across.
mini roof 3
say |A fuse hisses. A streak of light climbs into the evening, a long, thin comet. It bursts into orange and white and blue.
fx flash
scene night amir dalia gabriel amine
say |Fireworks bloom over the 14. The whole building cheers. Forty small bot lights blink in rhythm. Somewhere far below, an old bot hums along.
ifge bonds 3 bonds_many
say Amir|Everyone's here. Everyone made it.
goto after
label bonds_many
say Amir|I wouldn't change a single day. Not even the Backrooms.
say Dalia|Not even the hornets?
say Amir|Okay, maybe the hornets.
label after
say |The party winds down. The last bot does a small, lonely twirl. A single lamp stays lit on the Parking 2 level, glowing through a grey door that wasn't there a month ago.
ifnot prime_free prime_stay
say Prime|Amir. Thank you. For everything.
goto cliff
label prime_stay
say |A faint knock, from very far below. Polite. Patient. Not a threat. A greeting.
label cliff
say Amir|Whatever's next... we'll be ready.
say Dalia|To be continued?
say Amir|To be continued.
scene off
card LOST OF ASHES|Chapter 7 awaits.
endday
)IL";
