// story_days_2.hpp - Days 6 to 12
#pragma once
static const char* STORY_DAYS_2 = R"IL(
# ================================================================ DAY 6
script day_6
title The Apology List
scene room amir
say |Day 6. A knock on my door at 8 AM. It's Adam, holding a sheet of paper and trying very hard not to vibrate.
scene off
npc adam_t lethal 640
goal Talk to Adam, who is waiting outside your room on the Lethal floor.
await talk adam_t
say Adam|Okay. Don't laugh. I made a list. Everyone I've ever bumped into, knocked over, or flattened. I'm apologizing to all of them.
say Amir|How long is the list?
say Adam|Three pages. Front and back. But I picked three people to start with. Anes, Alicia and Raceem. And I need someone to make sure I don't sprint.
choose
> I'll go with you. => with
> I'm not a babysitter. => no
label no
say Adam|Please? You're the only one I trust not to laugh. Also you're slow enough to keep me slow.
say Amir|That's not a compliment.
say Adam|It's a little bit of a compliment.
label with
say Adam|Great. Anes first. Common floor. Walk, don't run. Walk, don't run.
goal Visit Anes on the Common floor (C-001) and see if he accepts the apology.
await talk anes
say Adam|Hi, Anes. I... knocked over your coffee machine last spring. And your plant. And your cat. And your other plant.
say Anes|The cat is fine. The plant is fine. The coffee machine was a tragedy.
choose
> He's really sorry. => sorry
> Maybe buy him a new coffee machine? => buy
label sorry
say Anes|I can tell. Okay. Apology accepted. Signature's on the list.
goto next1
label buy
say Anes|A new one would be nice. I'll accept coffee beans. Good ones.
say Adam|Deal! I'll find the best beans in Reghaia!
label next1
say Adam|One down. Alicia, Uncommon floor!
goal Visit Alicia on the Uncommon floor (UC-001).
await talk alicia
say Adam|Alicia, I... sat on your cards once. All of them.
say Alicia|Fifty-two cards, ruined. I had to play with a bottle cap deck for a week.
choose
> It was an accident. => acc
> Why a bottle cap deck? => cap
label acc
say Alicia|Accidents have consequences. But fine. I forgive you. Sign.
goto next2
label cap
say Alicia|Iyad lent me his collection. It was a nightmare. We kept losing the Queen of Spades to the Number 14 cap.
label next2
say Adam|Two down! One to go. Raceem. Lethal floor.
goal Visit Raceem on the Lethal floor (L-002).
await talk raceem
say Adam|Raceem. I once crashed into you at the finish line of your race.
say Raceem|At my record attempt. I would have beaten Bolt.
choose
> You wouldn't have. => nope
> He's really trying. => try
label nope
set raceem_roast 1
say Raceem|Don't be rude. I would've been within three seconds. Four. Okay, seven.
goto signed
label try
say Raceem|Hmm. Okay. Apology accepted. I'll invite you to a rematch. You can't run, though. Only walk.
label signed
say |Three signatures. Adam holds the list over his head like a trophy and almost trips on his own shoelace.
say Adam|Walk, walk, walk. See? I'm learning!
say Adam|I'll finish the other names tomorrow. Thank you for going with me, Amir. Really.
goal Tell Dalia how it went (Main floor, M-002).
await talk dalia
say Dalia|I heard! Apology tour! My brother is doing a tour! Is the world ending?
say Amir|Your brother is a hurricane. A well-meaning hurricane.
say Dalia|That's exactly what he is. And Amyas is the weather report. Welcome to the Bachouche family.
endday

# ================================================================ DAY 7
script day_7
title The Elevator Hiccup
scene room amir
say |Day 7. The elevator dings and... skips my floor. It dings again and skips it twice.
say Amir|Hello? I'm right here.
scene off
toast The Rare and Special floors are cut off today.
lock rare
lock special
goal Find Youcef on the Main floor (M-005). He knows the elevator.
await talk youcef
say Youcef|Ah. You noticed. It's been like this since last night. It skips Rare and Special. Worse, it hums out of tune.
say Youcef|Something's wrong in the control room. Underground. Fifth floor down. Go look at the panel.
say Amir|Why me?
say Youcef|Because I'm lifting this toolbox. Also I like you.
choose
> Okay, I'll check. => ok
> What if the elevator eats me? => eat
label eat
say Youcef|It won't eat you. It might gently squeeze you. Don't take it personally.
label ok
say Youcef|The control room is on its own floor. Use the elevator panel there. The green buttons are friends. The red ones are not.
goal Go down to the Elevator control room.
await floor ctrl
say |The Elevator control room. Screens full of green lines. One of them is wavering like a nervous heartbeat.
say Amir|Okay panel. Talk to me.
goal Use the control panel in the middle of the room.
await use panel
say |A row of breakers. Each one flips on a beat. You have to hit them in rhythm.
mini timing 5 4 Reset_the_breakers
ifnot skipped fixed
say |(The panel sighs and fixes itself out of pity.)
label fixed
say |The green lines straighten. A tiny hum climbs to the right note. Somewhere above, a floor indicator blinks back to life.
unlock rare
unlock special
toast The Rare and Special floors are back.
say Amir|Fixed. I think.
say |A line of text blinks across the screen: "SHAFT 4: SOMETHING IS KNOCKING FROM BELOW."
say Amir|...I'm going to pretend I didn't read that.
goal Tell Youcef the elevator is fixed (Main floor).
await talk youcef
say Youcef|It sounds right again! Beautiful. I'll buy you a drink.
say Amir|Youcef, the screen said something was knocking. From below.
say Youcef|Pipes. Always pipes. Don't think about it. Go enjoy your evening.
endday

# ================================================================ DAY 8
script day_8
title Bot Rebellion
scene room amir
say |Day 8. Sweepy hums outside my door. It isn't the usual song. It's a slow, steady chant.
scene off
goal Go down to the 14 Cleaning bots parking. Something is up with the bots.
await floor bots
say |All the bots stand in a circle, facing the same dark corner. Their eyes blink in perfect unison.
goal Talk to Sweepy.
await talk sweepy
say Sweepy|Hello, Amir... We are... listening. We are listening to... a hum.
say Amir|What hum?
say Sweepy|From below. From the wall. It says... "Prime. Prime. Prime."
goal Talk to Zed. He's usually the voice of reason.
await talk zed
say Zed|Don't look at me. I'm not part of this. I heard it too. I told myself it was a vent.
say Zed|It's not a vent.
goal Talk to Grim.
await talk grim
say Grim|It sounds like loneliness. Like someone who cleaned the same floor for a thousand years.
say Grim|Sorry. I am... always like this.
say Amir|Okay. Okay. Bots. Everyone back to your pads. It's just a hum.
say |A few beeps. A few hesitations. A few bots wander away from the circle and straight toward the exit ramp.
mini roundup 6 40
ifnot skipped rounded
say |(The bots calmed down on their own. Mostly because they got tired of being stared at.)
label rounded
say |Six bots back on their pads, eyes blinking in all different patterns. Back to normal. Almost.
set heard_prime 1
say Sweepy|Thank you, Amir. The hum is quiet now. ...For now.
goal Tell Gabriel what you heard (Main floor, M-004).
await talk gabriel
say Gabriel|A hum that says "Prime"? Same word as yesterday?
say Amir|And the elevator screen said something was knocking from below.
say Gabriel|That's two. Two is a pattern. Let's keep our eyes open.
endday

# ================================================================ DAY 9
script day_9
title Dust Storm
scene room amir
say |Day 9. The hallway lights flicker and a thin layer of dust blows across the floor. Dustin screams from three rooms away.
scene off
goal Go to the Air ventilation systems floor and find out where the dust is coming from.
await floor vent
say |The ventilation floor. Giant fans, all spinning at once. A cloud of grey puffballs tumbles through the air.
say Amir|Those are... dust bunnies. Hundreds of dust bunnies.
npc bolt vent 900
npc dustin vent 700
goal Talk to Bolt, who is zooming around down here.
await talk bolt
say Bolt|HELLO AMIR! I got stuck in the fan! It was GREAT! I got spun around fifty times!
say Dustin|It was not great. It was horrifying. My eyes are full of fluff.
say Amir|Why is there so much dust all of a sudden?
say Bolt|Someone opened a hatch behind the fan! Big old hatch! Dust just poured out!
say Dustin|It's a haunted hatch. I'm not going anywhere near it.
choose
> We have to clean up. => clean
> We should seal that hatch. => seal
label clean
say Bolt|YES!! Cleaning is our JOB!
goto go
label seal
set vent_hatch 1
say Bolt|We'll tell Youcef! But first, the bunnies!
label go
say Dustin|Okay... okay... we can do this. I'll... I'll stand behind you. Way behind you.
mini catch 10 3 dust_bunnies
ifnot skipped caught
say |(The fans cough and clear the rest by themselves.)
label caught
say |The last bunny disappears into Bolt's front bin. The air clears. The hatch behind the fan stays shut, with a faint, regular knocking behind it.
say Dustin|Do you hear that?
say Amir|Pipes.
say Dustin|That's not pipes.
say Amir|...I know. Let's go upstairs.
endday

# ================================================================ DAY 10
script day_10
title Roof Access
scene room amir
say |Day 10. Dalia is at my door before I'm out of bed, holding a very sad-looking string.
scene off
npc dalia lethal 640
goal Talk to Dalia, who is waiting outside your room.
await talk dalia
say Dalia|My kite! My very favorite kite! It flew off the balcony last night and I think it's stuck on the roof antenna!
say Amir|The roof? Nobody goes to the roof.
say Dalia|Youcef has a key. I borrowed it. Don't tell Youcef.
say Dalia|Please. It was a birthday present.
choose
> Okay. I'll get it. => ok
> Why not go yourself? => why
label why
say Dalia|Because I'm afraid of heights. Don't make fun of me.
say Amir|I won't. I'll go.
label ok
say Dalia|Thank you! The key opens the roof door in the elevator. Be careful.
unlock roof
toast The Roof is now available in the elevator.
goal Take the elevator up to the Roof.
await floor roof
say |The roof. Wind, wide sky, and the whole of Reghaia stretching out in the distance. And, far away, a bright dot caught on the antenna.
say Amir|Wow. That's a view.
say |The path to the antenna is broken up by gaps and low ledges. Time to run.
mini roof 1
say |The kite hangs from the antenna by a single tangled string. You untangle it and tuck it under your arm.
ifge stars 3 manystars
say Amir|Got it. Now to bring it back.
goto back
label manystars
say Amir|Got it. And I found a handful of little stars on the way. Someone left them here. Weird.
set roof_stars_many 1
label back
goal Bring the kite to Dalia (Main floor, M-002).
await talk dalia
say Dalia|My kite! You actually got it! You went all the way up!
say Dalia|You are the best, Amir. I'm going to hug you. Hold still.
say Amir|I'm holding still.
say Dalia|Okay, hug complete. Now I owe you ten favors. Choose wisely.
endday

# ================================================================ DAY 11
script day_11
title Quiet Day
scene room amir
say |Day 11. A truly quiet morning. No bots. No hum. No hornets. Nothing is on fire. It's suspicious.
say Amir|I'm going to spend today the way normal people do. By talking to people. Slowly.
scene off
goal Pay visits: talk to Arwa on the Main floor (M-001).
await talk arwa
say Arwa|Oh, hi Amir. You look rested. That's rare.
choose
> How are you? => how
> Seen anything strange lately? => strange
label how
say Arwa|Reading. Always reading. The building has so many stories if you stop and listen.
goto next1
label strange
say Arwa|Only that the elevator hums in a minor key now. Youcef says it's fixed. I say it's thinking.
label next1
say Arwa|Go say hi to Iyad. He found a new key. He's very excited.
goal Talk to Iyad on the Common floor (C-005).
await talk iyad
say Iyad|AMIR! Look! A new key! I don't know what it opens, but it feels important!
choose
> Where did you find it? => find
> Keep it safe. => safe
label find
say Iyad|Behind the vending machine in the Underlobby. It was just lying there. Next to a note: "For when it knocks".
say Amir|...Iyad, that's weird.
say Iyad|I know! Isn't it great?
goto next2
label safe
say Iyad|I will. In a little box, with the other keys. And my backwards watch.
label next2
say Iyad|Amira's baking cookies upstairs. She needs a taster.
goal Talk to Amira on the Uncommon floor (UC-005).
await talk amira
say Amira|Amir! Just in time! Try one. Be honest.
say |The cookie is either perfect or a weapon. It crunches. It sparkles. Cardamom explodes in my mouth.
choose
> Perfect. => perfect
> It's a weapon. => weapon
label perfect
set amira_happy 1
say Amira|YES! Finally! A review that isn't "it built character". Thank you!
goto next3
label weapon
say Amira|A weapon! I'll take it! Weapons are expensive!
label next3
say Amira|Kenzy is on the Special floor. She... he... Kenzy! Kenzy said he picked up some weird signal. Go ask.
goal Talk to Kenzy on the Special floor (S-002).
await talk kenzy
say Kenzy|Oh! Amir! You came! Don't touch the wires. Okay. Listen to this.
say |A crackle. A burst of static. Then, very faint, almost a whisper: a slow, mechanical voice repeating a single word.
say Kenzy|"Prime". It's coming from underground. Strongest at the Parking 2 level.
say Amir|Prime again. Three times now.
say Kenzy|Four, counting the radio. I'm recording it. If it says something new, I'll tell you.
say Amir|Thanks, Kenzy. Don't unplug anything.
say Kenzy|No promises.
endday

# ================================================================ DAY 12
script day_12
title Ice Cream with Amyas
scene room amir
say |Day 12. Amyas sent a one-word text: "Shop." No emoji. No punctuation. Full intimidation.
scene off
goal Find Amyas on the Teen floor (T-001).
await talk amyas
say Amyas|You came. Good. Come on. We're going to the ice cream shop on the main road. My shift is starting.
say Amir|You're asking me to come with you?
say Amyas|I'm telling you. Different thing.
fx fadeout
wait 40
scene shop amir amyas
fx fadein
say |The ice cream shop on the main road. Cool air, pink-and-white awning, a neat row of tubs behind glass.
say Amyas|Okay. Rules. You stand there. You hold the cones. I'll scoop. If you drop one, you pay for it.
say Amir|That's illegal.
say Amyas|It's customer service.
choose
> Fine, I'll help. => help
> I'm just a customer. => cust
label cust
say Amyas|Customers pay. You're not paying. You're helping.
label help
say Amyas|First customer is coming in. Stay calm. Don't be weird.
scene off
mini catch 8 3 ice_cream_scoops
scene shop amir amyas
ifnot skipped scooped
say |(The scoops piled themselves into perfect cones while no one was looking.)
label scooped
say Amyas|Not bad. You're only about half useless.
say Amir|That's the nicest thing you've ever said to me.
say Amyas|Don't get used to it.
choose
> What's the story with you and Adam? => adam
> What's your favorite flavor? => flavor
label adam
say Amyas|He's my brother. He runs into things. I don't intervene. It builds character.
say Amyas|Dalia is our little sister, and she's the only one with sense. We don't talk about that.
goto fin
label flavor
set amyas_flavor 1
say Amyas|Pistachio. Don't tell anybody. If anyone asks, it's vanilla. A serious, grown-up vanilla.
label fin
say Amyas|Here. A free cone. Don't tell anyone I'm nice.
say Amir|Your secret's safe.
say Amyas|I know. Because I know where you live. Third door on Lethal.
say Amir|...Noted.
scene off
endday
)IL";
