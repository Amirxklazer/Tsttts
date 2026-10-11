// story_days_1.hpp - Days 1 to 5
#pragma once
static const char* STORY_DAYS_1 = R"IL(
# ================================================================ DAY 1
script day_1
title The Dalia Quest
card CHAPTER 1|Lost the Ash
toast Walk: stick / D-pad.   Talk / use: A.   Menu: +
bars on
scene room amir
cast amir 860
cast bolt -200
say |Day 1. Morning in the 14.
walk bolt 480 6 wait
emote bolt !
say Bolt|BEEP! Dalia texted six times! SIX! Amir, WAKE UP!
anim amir hop
say |Day 1. Morning in the 14. The elevator hums, a Cleaning bot beeps somewhere in the hall, and my phone says Dalia texted me six times.
say Amir|Six. Before breakfast.
walk bolt 1400 7
say Bolt|Follow me! Zoom zoom!
bars off
say |(Dalia lives in M-002 on the Main floor, one floor below mine. The elevator is at the left end of the hall.)
scene off
goal Take the elevator down to the Main floor and talk to Dalia (M-002).
await talk dalia
say Dalia|AMIR. Finally. Do you know how many times I texted you?
choose
> Six. I counted. => six
> I was asleep... => asleep
label six
say Dalia|Six, yes! And I would have sent seven if I wasn't busy panicking.
goto bots
label asleep
say Dalia|Asleep?! The whole building is awake! The bots got loose!
label bots
say Dalia|Mopsy ran off, and four other Cleaning bots with her. Some glitch, they all bolted for the parking.
say Dalia|Everyone owns one of those things, so everyone is going to ask where theirs went. And Mopsy is MINE.
choose
> Where do I look? => look
> Why me? => why
label why
say Dalia|Because you're fast, you're nice, and you owe me for the elevator thing.
say Amir|What elevator thing?
say Dalia|Exactly. Come on.
goto show
label look
say Dalia|Okay. First, don't tell ANYONE what I'm about to show you.
label show
say Dalia|See that dark panel next to my room? The one that looks like a wall with attitude?
set secret_known 1
say Dalia|That's the Stairway to Hell. It goes outside, to the parking lot. Gabriel went out that way to look.
say Amir|Why is it called the Stairway to Hell?
say Dalia|Nobody ever told me. It was just always called that. Go, please. I'll wait here.
goal Go through the secret door next to Dalia's room: the Stairway to Hell.
await door SECRET
say |The panel clicks, then scrapes open. Cold air, concrete dust, and a long dark stairway leading out.
set secret_open 1
fx fadeout
wait 40
warp out1 260
npc gabriel out1 900
fx fadein
toast Outside parking
say |The outside parking lot. Early sun, a few parked cars, and somebody in a dark jacket waving from the far end.
goal Find Gabriel in the outside parking lot.
await talk gabriel
say Gabriel|Amir. Took you long enough.
say Amir|Dalia said "bots". Plural. With feeling.
say Gabriel|Plural. They aren't out here though. They ran back inside and went down to their own parking.
say Gabriel|The 14 Cleaning bots parking. Basement, near the very bottom. I'll check the lobby. You take the basement.
choose
> Why do I get the basement? => base
> Fine. Any tips? => tips
label base
say Gabriel|Because you're the one who can sprint.
say Amir|That's not a skill. That's a punishment.
say Gabriel|Both can be true.
goto after
label tips
say Gabriel|They flee when you get close but they're slow to turn. Grab them, don't chase them.
label after
say Gabriel|Use the same door to get back inside. Go.
npc gabriel lobby 700
goal Go back inside through the Stairway door (the door at the left end of the parking).
await use backdoor
fx fadeout
wait 30
warp main 1100
fx fadein
toast Main floor
goal Take the elevator all the way down to the 14 Cleaning bots parking.
await floor bots
say |The 14 Cleaning bots parking. Rows of charging pads, half of them empty. Somewhere in the dark, five tiny beeps.
say Amir|Okay. Grab, don't chase. Grab, don't chase.
mini roundup 5 45
ifnot skipped won_ok
say |(You skipped ahead. The bots decided they wanted to come home anyway.)
label won_ok
say |Five bots, five blinking eyes, zero dignity. Mopsy tries to look innocent.
say Mopsy|It wasn't my idea. Zed started it.
say Zed|I would never. Fine, I would.
goal Go back up and tell Dalia on the Main floor.
await talk dalia
say Amir|Five bots. All present. Mopsy included.
say Dalia|AMIR!! You are officially my favorite person today. Do not tell Gabriel.
say Dalia|Gabriel texted me, by the way. He says one of the bots was muttering something in the lobby. "Prime is awake."
say Amir|Prime?
say Dalia|No idea. Probably a glitch. Probably.
choose
> Probably. => prob
> That sounds bad. => bad
label prob
say Dalia|Right? Let's not worry about it. Go eat something.
goto fin
label bad
set worried_prime 1
say Dalia|It's bad if we make it bad. We'll watch and see. Together.
label fin
say |(Thanks for playing the beginning of the story. More is coming...)
endday

# ================================================================ DAY 2
script day_2
title Hornets
bars on
scene room amir
cast amir 700
emote amir ?
anim amir shake
say |Day 2. Gabriel texted at 7:12: "Come to my room. Bring shoes you can run in."
say Amir|Never a good sign.
bars off
scene off
goal Go to Gabriel's room on the Main floor (M-004).
await talk gabriel
say Gabriel|Good. You came. Amine is waiting in the outside parking. I told him you'd meet him.
say Amir|Amine's HERE? In the 14? Since when?
say Gabriel|Since six this morning. He took the first bus from Îlot22. He brought snacks.
choose
> Let's go! => go
> Do I need to be scared? => scared
label scared
say Gabriel|Define scared.
say Amir|You said "bring shoes you can run in".
say Gabriel|Good shoes. That's all I said.
label go
goal Go outside through the Stairway to Hell door next to Dalia's room.
await door SECRET
fx fadeout
wait 30
warp out1 420
npc gabriel out1 650
npc amine out1 1100
fx fadein
toast Outside parking
say |Among the cars, a figure jumps up and down with both arms in the air like he's landing a plane.
goal Meet Amine in the outside parking.
await talk amine
say Amine|AMIIIIR! Finally! Do you know how long I waited?
choose
> Since six. => six
> Nice to see you too. => nice
label six
say Amine|SIX! And I brought snacks, and I ate half of them, and the rest are for you. It's a fair system.
goto go2
label nice
say Amine|Don't be nice at me, I came in on the first bus. I need dramatic greetings.
label go2
say Amine|Okay, plan. The old tree at the end of the lot. Perfect light. We take a picture. Three friends, one tree, zero consequences.
say Gabriel|Famous last words.
scene hornet amir amine gabriel
say Amine|Okay, stand there. Closer. A little to the left. Gabriel, stop looking like you hate this.
say Gabriel|I'm looking like I'm worried.
say Amine|Same thing! Okay, big smile on three. One, two...
say |Amine steps back for a better angle. His heel lands on a root. His elbow lands on a branch. The branch swings.
fx shake
say |Something brown and round, the size of a football, drops from the tree and bursts.
say Gabriel|Don't. Move.
say Amir|Is that...
say Gabriel|Hornets. A lot of hornets.
fx flash
say Amine|WHY DID I PICK THIS TREE?!
choose
> RUN! => run
> Everyone behind me! => brave
label run
say Gabriel|Running makes them chase you. Swat them off. Stay together.
goto fight
label brave
set amir_brave 1
say Amine|That's so heroic! Also, please be fast!
label fight
scene off
toast Press A to swing. Don't get stung!
mini fight 8 5 hornets
ifnot skipped hornet_ok
say |(You wave your arms and the hornets get bored. Technically it still counts.)
label hornet_ok
say |The last hornet buzzes off to complain to its family. The lot goes quiet. One of the cars has a nest-shaped dent in it.
say Amine|Is... is everyone alive?
say Gabriel|Everyone's alive. Amine's arm is a little puffy.
say Amine|It's FINE. It's a souvenir.
choose
> Let me see the arm. => arm
> You're going to be insufferable. => insuff
label arm
set amine_friend 1
say Amine|You're a real friend, Amir. Look, it's tiny. It's like a little volcano.
say Gabriel|Ice. Now. Then we eat the snacks.
goto fin
label insuff
say Amine|Already planning the story. "The day I fought a hornet nest and WON". Gabriel, you're in it. Amir, you're in it. The tree is a villain.
say Gabriel|The tree is innocent.
label fin
say Amine|Tomorrow, I want to do something safe. Something with paper. No trees. No wasps. No nests.
say Amir|Paper? Okay. Deal.
endday

# ================================================================ DAY 3
script day_3
title Papercraft Day
bars on
scene room amir
cast amir 700
anim amir bow
emote amir !
say |Day 3. My phone buzzes from under the pillow. A message from Amine, written entirely in capital letters.
say Amine|PAPERCRAFT DAY!! Bring: COFFEE (Anes, Common floor). PAPER ROLLS (Anais, Rare floor). GLUE (Uncommon floor). UHU STIC (Youcef, Main floor). PENS (Raceem, Lethal floor). RULERS (Lilian, Teen floor). Meet me at S-001!!
say Amir|Six things. Six floors. That's a quest.
bars off
scene off
clearitems
spawn coffee common 610
spawn paper_rolls rare 610
spawn glue unc 1210
spawn uhu_stic main 2110
spawn pens lethal 910
spawn rulers teen 1210
goal Collect 6 craft tools: coffee (Common), paper rolls (Rare), glue (Uncommon), UHU stic (Main), pens (Lethal), rulers (Teen).
toast Items are lying near each floor's doors. Walk over them.
await items 6
say Amir|Coffee, paper rolls, glue, UHU stic, pens, rulers. Check. I can barely see over the pile.
npc amine special 600
goal Carry everything to Amine on the Special floor (S-001).
await floor special
say |The Special floor. Amine's door is right ahead. I hold the whole stack in both arms. It's taller than my head.
say Amir|Amine! Door! Hold the door!
say Amine|I'm coming! Don't drop the glue! It's expensive!
npc adam_t special 2300
say ???|MOVE MOVE MOVE MOVE!!!
fx shake
say |Footsteps. Fast ones. Something is rounding the corner at full sprint.
say Amir|Wait, wh...
fx shake
fx flash
say Adam|SORRY AMIR!! I'M LATE FOR...!
say |Pens fly. Paper rolls fly. The coffee flies. I fly, face first, arms spread like a very confused eagle.
say |The floor has stopped being a floor.
fx black
wait 40
scene backrooms amir
fx fadein
say |Yellow wallpaper. Buzzing lights. A carpet that smells like wet cardboard.
say Amir|...That wasn't the Special floor.
card NOCLIP|Day 3 ends somewhere it shouldn't.
endday

# ================================================================ DAY 4
script day_4
title Backrooms
scene backrooms amir
say |Day 4. I didn't go to sleep. I woke up. In the same hallway. It hasn't changed. Neither has the hum.
say Amir|Okay. Okay okay okay. I fell through a floor. Normal day. Probably.
say |Somewhere ahead, a door glows a faint green. A few bottles of almond water sit on the carpet like breadcrumbs.
choose
> Grab the almond water, find the exit. => go
> Yell for help first. => yell
label yell
say Amir|HELLOOOOO?!
say |The hum gets louder. Far away, someone yells back. In my own voice. A second late.
say Amir|...Okay. Never doing that again.
label go
say |The lights flicker. The hallway turns left. Then right. Then, somehow, left again.
mini maze 3 1
ifnot skipped maze_ok
say |(The hum fades by itself. Maybe the Backrooms felt bad for you.)
label maze_ok
say |A door. A real door, with a handle. White light leaks around the edge. I push.
fx fadeout
wait 40
scene off
npc dalia lethal 640
npc gabriel lethal 740
npc amine lethal 840
npc adam_t lethal 940
warp lethal 560
fx fadein
toast Lethal floor
say |The Lethal floor. My own hallway. Carpet that actually smells like carpet. Four very worried faces.
goal Talk to Dalia, who is standing closest.
await talk dalia
say Dalia|AMIR!! Where WERE you?! We looked for a whole day!
say Amir|A day? I was gone for maybe an hour.
say Gabriel|You were gone for a day and a half. The whole floor was looking.
say Amine|I called your phone two hundred times! It rang in your room!
say Amir|My phone. Right. I left it on the bed.
choose
> Is Adam okay? => adam
> I fell into the Backrooms. => back
label adam
say Adam|Okay? I'm TERRIBLE. I was running to catch Amyas, I didn't see you, I'm so sorry, I looked everywhere!
goto talk
label back
say Gabriel|The what?
say Amir|It's... a yellow hallway. It hums. There were bottles of almond water. I'll explain later. I need to sit down.
label talk
say Dalia|Sit. We'll order food. No more disappearing.
say Amine|Tomorrow we make the papercraft. For REAL. In a room with a floor.
say Amir|Please. I want a floor.
endday

# ================================================================ DAY 5
script day_5
title The Papercraft
scene room amir
say |Day 5. A bowl of cereal, a glass of water, and a very firm intention to stay on solid ground.
scene off
npc amine special 600
goal Go to the Special floor and talk to Amine (S-001).
await talk amine
say Amine|You came! And you're still on the floor! That's a great sign!
say Amine|Okay. Everything I need is here. Paper, scissors, glue, a ruler. What are we building?
choose
> A model of the 14. => tower
> A Cleaning bot. => bot
> A rocket. => rocket
label tower
set craft_choice 1
say Amine|The whole building! Eight floors up, eight floors down. We'll need a LOT of paper.
goto build
label bot
set craft_choice 2
say Amine|A bot! A cute one! With antennas! Sweepy would be proud.
goto build
label rocket
set craft_choice 3
say Amine|A rocket! To escape the Backrooms next time! I love it.
label build
scene workshop amir amine
say Amine|Step one: cutting. Straight lines, steady hands. Wait for the line, then cut.
mini timing 5 4 Cut_the_paper
say Amine|Beautiful! Not a single wobble. Okay, step two: folding. Same rhythm. Sharp creases.
mini timing 6 4 Fold_the_creases
say Amine|Wow. You're a natural. Step three: the loose pieces. They're flying everywhere!
scene off
mini catch 8 3 paper_scraps
scene workshop amir amine
ifnot skipped crafted
say |(Some of the pieces assembled themselves with help from a very generous breeze.)
label crafted
say Amine|DONE! Look at that! It actually stands!
say Amir|It's... really good. We made that?
say Amine|We made that. You, me, and four hundred pieces of paper.
say |The little paper model sits on the desk, a bit crooked, proud of itself.
scene off
npc adam_t special 1100
say Adam|Hey... can I come in? I don't want to knock anything over.
say Amir|Come in. Slowly.
say Adam|I wanted to say sorry. For real this time. I'm... trying a new thing where I look before I run.
choose
> It's fine, Adam. => fine
> You owe me a coffee. => coffee
label fine
set adam_forgiven 1
say Adam|Really? Thanks. I owe you one. I owe you several. I'll keep a list.
goto fin
label coffee
set adam_forgiven 1
say Adam|DEAL. The best coffee. In a cup that doesn't fly.
label fin
say Amine|Okay! Tomorrow, we do nothing! We eat ice cream and sit around like legends.
say Amir|I like that plan.
endday
)IL";
