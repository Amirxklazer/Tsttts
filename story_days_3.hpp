// story_days_3.hpp - Days 13 to 21
#pragma once
static const char* STORY_DAYS_3 = R"IL(
# ================================================================ DAY 13
script day_13
title Lilian's Map
scene room amir
say |Day 13. A folded piece of paper slides under my door at dawn. On the front, in careful handwriting: "T-003. Come alone."
scene off
goal Find Lilian on the Teen floor (T-003).
await talk lilian
say Lilian|You came alone. Good. Walk with me. Not that close.
say Lilian|I draw things. Buildings, mostly. But when I drew the 14 from memory, I got something wrong. Look.
say |She unrolls a hand-drawn map. Every floor is there, up and down. But at the very bottom, below Parking 2, there's a shaded rectangle with a single label: "NOT ON THE PLAN".
choose
> It could be a mistake. => mistake
> Where is it? => where
label mistake
say Lilian|I don't make mistakes on maps. I make them on people. Sorry, that sounded worse out loud.
goto go
label where
say Lilian|East wall of Parking 2. Behind the last pillar. There's a door. Grey. No handle. I don't go near it.
label go
say Lilian|Ask Arwa. She reads about the plans. Then ask Youcef. Then ask yourself if you really want to know.
goal Ask Arwa about the building plans (Main floor, M-001).
await talk arwa
say Arwa|Plans? Of course. I have the original blueprints. Let me see...
say Arwa|Hm. That's odd. The 14 has seventeen levels on every copy I've seen. But the load calculations add up to eighteen.
say Amir|Eighteen?
say Arwa|One floor of weight with no floor to put it on. An extra level, below everything.
goal Ask Youcef about the east wall of Parking 2 (Main floor, M-005).
await talk youcef
say Youcef|The east wall? Nobody goes there. We sealed that door a long time ago. Before I started.
say Youcef|Why do you ask? ...Never mind. Don't tell me. I don't want to know.
goal Go down to Parking 2 and look at the east wall.
obj greydoor park2 1900 Grey door
await floor park2
say |Parking 2. Concrete pillars, a few dusty cars, and the faint smell of old rain.
goal Examine the grey door at the east end of Parking 2.
await use greydoor
say |A flat grey door, no handle, no lock, no hinges. Just a faint outline in the concrete. I press my hand against it.
say |It hums. A long, patient note, like the hum in the Backrooms.
set greydoor_seen 1
say Amir|...Okay. That's a door. And it knows I'm here.
say |Something behind it knocks once. Politely.
say Amir|I'll... come back. With friends. And probably a snack.
endday

# ================================================================ DAY 14
script day_14
title OL-007
scene room amir
say |Day 14. I wake up to someone pushing a sticky note under my door. It reads: "OL-007. Story time. Bring pizza."
scene off
goal Visit Fares at OL-007 on the Lethal floor.
await talk fares
say Fares|You brought pizza?
choose
> I didn't. => nopizza
> I'll get you some. => getpizza
label nopizza
say Fares|Shameful. Okay, I'll tell the story anyway. But with one less ending.
goto story
label getpizza
say Fares|I like your optimism. Okay, story time.
label story
say Fares|Long ago, in a place far from here, there was a floor above Lethal. A floor called "Over Lethal".
say Fares|People there were so quiet, you could hear the dust fall. When the elevator changed its mind, the floor vanished. Only the room number remained: OL-007.
say Fares|And that's why Adam always gets my pizza. Because he lives at L-007, and the L is for Lethal, and the O is for... nothing at all.
choose
> That's a good story. => good
> Is any of that true? => true
label good
set fares_ending 1
say Fares|Thank you. It had three endings. I only told you the cool one.
goto react
label true
set fares_ending 2
say Fares|It's true that the plate says OL. Everything else is a gift.
label react
say Fares|Now, a test. If you can hit a button faster than I can, I'll tell you the third ending. Deal?
choose
> Deal. => deal
> No thanks. => nodeal
label nodeal
say Fares|Coward. Fine. You'll never know.
say Fares|...But the third ending is that the floor comes back. Someday. When someone knocks.
goto fin
label deal
say Fares|Ready? Hit it when the marker's green. Don't blink.
mini timing 6 3 Reaction_test
ifnot skipped passed
say |(The marker slowed down out of kindness.)
label passed
say Fares|Faster than me. Annoying. Okay, the third ending. The floor comes back. Someday. When someone knocks.
say Amir|...You said "when someone knocks."
say Fares|I did. Funny, that.
label fin
say Amir|Fares, have you heard knocking?
say Fares|I hear everything. It's a gift and a curse. Mostly a gift. Don't tell Adam.
endday

# ================================================================ DAY 15
script day_15
title Blackout
scene room amir
say |Day 15. The lights go out at breakfast. All of them. The elevator hums on emergency power. Somewhere downstairs, Dustin screams.
scene off
clearitems
spawn battery lobby 800
spawn battery main 700
spawn battery lethal 2110
spawn battery common 1900
goal Find 4 batteries for the emergency lamps: Lobby, Main, Lethal and Common floors.
toast Batteries are lying near the elevator on some floors.
await items 4
say Amir|Four batteries. Now where does the power come from?
say Youcef|Control room! The main switch! The batteries kick-start the backup!
goal Go down to the Elevator control room.
await floor ctrl
say |The control room is dark, lit only by a few emergency strips. The panel glows a nervous orange.
goal Use the control panel.
await use panel
say |You slot the batteries in. The panel starts counting down from ten. At zero, you have to hit the main switch exactly on the beat.
mini timing 5 4 Restart_the_power
ifnot skipped restored
say |(The power came back by itself, a little embarrassed.)
label restored
say |Light floods the room. Screens blink, fans spin, a distant cheer comes from every floor.
say |On the main screen, a single line blinks twice: "POWER SURGE FROM LEVEL 18. SOURCE: UNKNOWN."
say Amir|...Level eighteen.
say Youcef|The what? Never mind. I didn't see that.
clearitems
goal Go up and check on Dalia (Main floor, M-002).
await talk dalia
say Dalia|The lights are back! You did that?! I want to say thank you with a hug, but I already used the hug this week.
say Amir|It's fine. Save the hug.
say Dalia|I'm saving it. For emergencies.
endday

# ================================================================ DAY 16
script day_16
title The Welcome Basket
scene room amir
say |Day 16. A card on my door, in handwriting I don't recognize: "The Further Inn welcomes you. Bring a welcome basket. We forgot how."
scene off
clearitems
spawn towel common 610
spawn mints unc 610
spawn soap main 610
goal Collect 3 things for the basket: towel (Common), mints (Uncommon), soap (Main).
await items 3
say Amir|Towel, mints, soap. A basket in the making. Now, the Further Inn. All the way at the bottom.
goal Take the elevator down to the Further Inn.
await floor inn
say |The Further Inn. Warm lamplight, old wallpaper, and a faint humming under everything. It smells like fresh sheets and distant rain.
goal Talk to Aya at NST-001.
await talk aya_n
say Aya@aya_n|A welcome basket! You remembered! Nobody remembers!
say Aya@aya_n|The Further Inn used to host so many guests. Then the elevator stopped coming down this far, and the guests stopped coming. We keep the lamps on, just in case.
choose
> I'll visit more often. => visit
> Does anyone live down here? => live
label visit
say Aya@aya_n|You say that now. We'll see. You're welcome any time.
goto next
label live
say Aya@aya_n|Me, Sofia, and Tansaouti. Plus a few ghosts, I think. Friendly ones. One of them only plays piano on Tuesdays.
label next
say Aya@aya_n|Go say hi to Sofia. She's been listening to the walls again. She'll want to tell you something.
goal Talk to Sofia at NST-003.
await talk sofia
say Sofia|Amir. You brought a basket. How sweet. Listen. Do you hear it?
say |The hum is louder here. Under the hum, so quiet I almost miss it, a regular knocking. Three knocks. A pause. Three more.
say Sofia|It's been getting closer. Every night. I've counted. It's coming up from below the floor.
say Amir|Below the Further Inn? There's nothing below the Further Inn.
say Sofia|That's what I thought.
clearitems
endday

# ================================================================ DAY 17
script day_17
title Sofia's Radio
scene room amir
say |Day 17. A message from Kenzy: "Bring me to Sofia. I have a radio. She has ears. Together, magic."
scene off
npc kenzy inn 1400
goal Go down to the Further Inn and find Sofia (NST-003).
await floor inn
say |Kenzy is already there, hunched over a homemade radio the size of a toaster, with wires coming out like spaghetti.
goal Talk to Sofia.
await talk sofia
say Sofia|Kenzy says he can tune in to what the walls are saying. I can tell him if it's right. We need you to hold the antenna still.
say Kenzy|Hold it here. Gently. No sneezing. Okay, Sofia, say when.
say Sofia|Now. Slowly. A little left. A little left. Stop.
say Kenzy|It needs to be tuned by rhythm. When the signal pulses, press!
mini timing 5 4 Tune_the_radio
ifnot skipped tuned
say |(The radio tuned itself after a few gentle taps.)
label tuned
say |A burst of static, then a clear, quiet voice: slow, mechanical, as if reading from a very old manual.
say ???|CLEANING UNIT ZERO. STATUS: SEALED. SEEKING VISITOR. DOOR: PARKING 2, EAST. KEY: MISPLACED.
say Sofia|It's looking for a key.
say Amir|Iyad found a key behind a vending machine. With a note that said "for when it knocks".
say Kenzy|That can't be a coincidence.
say Amir|It's not. I think it's an invitation.
set key_known 1
say Sofia|Then we should answer. Carefully.
endday

# ================================================================ DAY 18
script day_18
title Tansaouti's Challenge
scene room amir
say |Day 18. A note, taped to the elevator button: "Tansaouti challenges you. Further Inn. Noon. Bring coins."
scene off
goal Go down to the Further Inn and find Adam Tansaouti (NST-002).
await floor inn
goal Talk to Adam Tansaouti.
await talk tansaouti
say Adam Tansaouti|Ah, the challenger. Finally. I've been waiting all week for someone brave.
say Amir|Brave? I was told to bring coins.
say Adam Tansaouti|Coins are a symbol. You'll see.
say |He leads you to a dusty arcade machine in the corner of the lobby. A single coin slot blinks. A sign above it reads: "HIGH SCORE: ADAM T. 1,000,000."
choose
> I'll beat that. => beat
> A million? Seriously? => million
label million
say Adam Tansaouti|It's a very serious million. It took me two years.
goto start
label beat
say Adam Tansaouti|Confidence. I like it. Let's see how long it lasts.
label start
say Adam Tansaouti|Catch the coins. Avoid the junk. Three misses and you're out. Ready?
mini catch 12 3 coins
ifnot skipped passed
say |(The machine glitched and awarded you the points. It felt bad about the one-million thing.)
label passed
say Adam Tansaouti|...Hm. Not bad. Not a million. But not bad.
say Adam Tansaouti|Okay. I owe you respect. Here, it's yours. It's not much. Just the thing the machine gives you when you lose.
say |He hands you a little brass token with a 14 stamped on it. On the back, in tiny letters: "Level 18".
say Amir|Where did you get this?
say Adam Tansaouti|From the machine. It was already in the slot. Years ago. It never worked in any lock. Maybe it will in one of yours.
set brass_token 1
endday

# ================================================================ DAY 19
script day_19
title Game Night
scene room amir
say |Day 19. Alicia texted: "GAME NIGHT. UC floor. Seven o'clock. No excuses. Abdullah is not allowed to count."
scene off
goal Go to the Uncommon floor and talk to Alicia (UC-001).
await talk alicia
say Alicia|You made it! We have three rounds. Buzzer round, trivia round, and a surprise round. Abdullah wanted to call it "Round of Excellence".
choose
> I'll take the buzzer. => buzzer
> Where's Abdullah? => abd
label abd
say Alicia|Getting snacks. And probably counting something.
label buzzer
say Alicia|Round one: the buzzer. You have to hit it on the beat. Jalil's in charge of the rules. He made them up.
goal Talk to Jalil (UC-003) and start round one.
await talk jalil
say Jalil|Rules! Rule one: be fast. Rule two: be correct. Rule three: if Abdullah says he knows the answer, he doesn't.
mini timing 5 3 Buzzer_round
ifnot skipped r1
say |(The buzzer pressed itself. Jalil pretended not to see.)
label r1
say Jalil|Wow. Okay. Nine points. That's... a lot. I'm writing it down.
goal Talk to Abdullah (UC-002) for round two.
await talk abdullah
say Abdullah|Round two! Trivia! I wrote the questions, so I get a handicap.
say Alicia|You wrote them wrong on purpose.
say Abdullah|I wrote them right. You just don't know the answers.
say |A flurry of trivia cards starts flying through the air. Alicia throws them from across the room.
mini catch 8 3 trivia_cards
ifnot skipped r2
say |(The cards landed on their own. Abdullah claimed it as strategy.)
label r2
say Abdullah|Winner! No, wait, me. No, you. Okay, you.
goal Talk to Alicia for the surprise round (UC-001).
await talk alicia
say Alicia|Final round. The surprise. It's... nothing. We eat pistachios and say our favorite things about the week.
choose
> Favorite thing: ice cream with Amyas. => ice
> Favorite thing: the papercraft. => craft
> Favorite thing: surviving. => surv
label ice
say Alicia|Amyas is nice to you? Wild. I'm jealous. Next time bring me one.
goto fin
label craft
say Alicia|A paper model of the 14? I want one. Abdullah, make a note.
goto fin
label surv
say Alicia|That's the best answer. Wise choice. Have a pistachio.
label fin
say |The night ends with five people asleep in a pile of cards and pistachio shells. Somebody puts a blanket on me. I don't even see who.
endday

# ================================================================ DAY 20
script day_20
title The Paint Fight
scene room amir
say |Day 20. A message from Anais, written in all-caps and splattered with something wet: "HELP. THE PAINT IS ALIVE."
say Amir|...What?
scene off
goal Go to the Rare floor and talk to Anais (R-001).
await talk anais
say Anais|It was an experiment! A new kind of paint! It's supposed to keep its shape! Instead it's... moving!
say Maysanne|It keeps rhyming. It says "blue, true, who are you?"
say Jilali|It stole my watch.
say Amir|Paint stole your watch?
say Jilali|It's very polite about it.
choose
> We have to stop it. => stop
> Can we keep it? => keep
label keep
say Anais|NO. It's already eaten a brush. And Jilali's pen.
label stop
say Anais|Hit it with water! Or a towel! Or a metaphor! Whatever works!
say |Blobs of living paint bounce around the room, leaving rainbow trails on the walls. They look... cheerful.
say Amir|Okay. Swat them. Carefully. We don't want more mess.
mini fight 10 5 paint_blobs
ifnot skipped cleaned
say |(The paint got tired and settled into a very modern mural.)
label cleaned
say |The last blob pops with a squeak. The room is soaked in colors that were never meant to meet.
say Anais|It's... beautiful. Disastrous. But beautiful.
say Maysanne|I'll write a poem about it. "Color, color, everywhere, none of it was meant to be there."
say Jilali|I found my watch. It's running forwards again. That's new.
say Amir|Good. Because backwards watches are starting to worry me.
endday

# ================================================================ DAY 21
script day_21
title Science Fair
scene room amir
say |Day 21. A flyer taped to my door: "SPECIAL FLOOR SCIENCE FAIR. ONE EXHIBIT. NO REFUNDS."
scene off
goal Go to the Special floor and talk to Kenzy (S-002).
await talk kenzy
say Kenzy|The only exhibit is mine. Look, I built a Prime detector. It's the radio from the Further Inn plus a bit of copper plus a lot of hope.
say Amir|Does it work?
say Kenzy|It will. If you hold the antenna and I tune the dial. Very important: don't sneeze.
choose
> I never sneeze. => nosneeze
> I'm already sneezing. => sneeze
label sneeze
say Kenzy|Fantastic. A real test of character. Hold your nose.
label nosneeze
say |Kenzy lifts a wobbly antenna from a pile of cables. The detector clicks and hums and tries to be professional.
say Kenzy|When the green light flashes, press it. Hit it on the beat. We want a clean signal.
mini timing 6 3 Calibrate_the_antenna
ifnot skipped cal
say |(The detector self-calibrated while pretending to be a science fair project.)
label cal
say |A dial spins. A needle settles. A map flickers on a small screen: the 14, floor by floor, and a single blinking dot at the east end of Parking 2.
say Kenzy|There. That's the source. Directly behind the grey door. And it's getting stronger.
say Amir|Prime.
say Kenzy|Prime. Do you want to tell the others, or should I?
choose
> I'll tell them. => tell
> Let's tell them together. => together
label tell
say Kenzy|Good. I'll make a copy of the readings for you. Keep them somewhere safe.
goto fin
label together
set kenzy_friend 1
say Kenzy|Together. I like that. Better than science fairs alone.
label fin
say Kenzy|Tomorrow, I'll bring the readings to the group. You bring the courage.
say Amir|I'm bringing snacks. Courage is optional.
endday
)IL";
