// story_ch2a.hpp - CHAPTER 2: FURTHER INN, days 1-9 (Act 1: Opening the Inn)
#pragma once
static const char* STORY_CH2A = R"IL(
# ================================================================ CH2 DAY 1
script c2_1
title The Reopening Plan
card CHAPTER 2|Further Inn
bars on
scene room amir
cast amir 800
cast bolt -200
fx lights
say |A week after Îlot14 Day. The banner is still on the roof. Nobody wants to take it down.
walk bolt 520 6 wait
emote bolt !
say Bolt|BEEP! Sofia called! The Inn is getting GUESTS! Real ones! Maybe!
anim amir hop
say Amir|Guests? At the Further Inn? That elevator hasn't even stopped there properly in years.
say Bolt|Then WE bring the stuff! Zoom zoom zoom!
walk bolt 1500 8
bars off
scene off
clearitems
goal Collect Inn supplies: fresh sheets (Common), a lamp (Rare), tea (Uncommon) and a bell (Main).
spawn sheets common 700
spawn lamp rare 900
spawn tea unc 1400
spawn bell main 1700
await items 4
say Amir|Sheets, lamp, tea, bell. The four things every hotel needs. And a miracle.
goal Take the elevator down to the Further Inn.
await floor inn
npc aya_n inn 900
say |The Inn glows like a lantern at the bottom of a well. Someone has already swept the carpet, and someone else has already un-swept it.
goal Talk to Aya at NST-001.
await talk aya_n
say Aya@aya_n|You brought everything! Okay. Okay okay okay. Here's the situation.
say Aya@aya_n|Three nights ago, a reservation slid under the front desk. Handwritten. Forty guests. Arrival: "soon".
say Amir|From who?
say Aya@aya_n|It's signed "The Knock".
choose
> That's not creepy at all. => creepy
> Then we'd better make it nice. => nice
label creepy
say Aya@aya_n|Right? That's why I need you. Creepy things are better with company.
goto catch
label nice
say Aya@aya_n|That's the spirit. A haunted hotel is still a hotel.
label catch
say Aya@aya_n|Help me catch the laundry. The bots rigged the laundry chute and it's... enthusiastic.
mini catch 8 3 clean_towels
ifnot skipped caught
say |(Aya caught the rest herself, muttering.)
label caught
say Aya@aya_n|The Further Inn is officially in reopening mode. Come back tomorrow. Bring friends. Bring bots.
set inn_open 1
clearitems
endday

# ================================================================ CH2 DAY 2
script c2_2
title Room Service
bars on
scene inn amir tansaouti
cast amir 700
cast tansaouti 1000
say |Day 2. The Inn at dawn, or what passes for dawn down here. A brass lamp flickers when it likes you.
emote tansaouti ...
say Tansaouti@tansaouti|You're the one who brought a bell. Good. I've missed the sound of a bell.
anim tansaouti bow
say Tansaouti@tansaouti|I'm the night porter. Adam Tansaouti. My shift never ended. I just stopped being told.
say Amir|That sounds lonely.
say Tansaouti@tansaouti|It was quiet. Different thing.
bars off
scene off
warp inn 700
npc tansaouti inn 1000
goal Talk to Tansaouti about the luggage carts.
await talk tansaouti
say Tansaouti@tansaouti|The luggage carts have gone rogue. Eight of them. They think they're Cleaning bots.
say Amir|Why would they think that?
say Tansaouti@tansaouti|Someone gave them googly eyes.
say |Behind the front desk, a dozen carts rattle in a circle. One is wearing a party hat.
mini roundup 7 45 2
ifnot skipped rounded
say |(The carts calmed down by themselves, embarrassed.)
label rounded
say Tansaouti@tansaouti|Eight carts home. Eight carts dignified. Well done.
choose
> Do you want help with the rooms? => rooms
> Who gave them googly eyes? => eyes
label eyes
say Tansaouti@tansaouti|...Dalia. Mostly Dalia.
goto fin
label rooms
say Tansaouti@tansaouti|Tomorrow. There's a piano that needs a favor. It's picky.
label fin
say Tansaouti@tansaouti|Go home. Sleep. The Inn will keep.
endday

# ================================================================ CH2 DAY 3
script c2_3
title The Piano on Tuesdays
bars on
scene inn amir sofia
cast amir 660
cast sofia 1050
say |Day 3. Sofia is standing very still in the middle of the lobby, head tilted. She doesn't look at me.
say Sofia|Shh. It's warming up.
emote sofia ~
say |From somewhere behind the wall, one soft note. Then another. Then nothing.
say Sofia|The ghost piano. It plays on Tuesdays. Today is Tuesday.
say Amir|Is it?
say Sofia|It is down here.
bars off
scene off
warp inn 700
npc sofia inn 1050
goal Talk to Sofia in the Inn lobby.
await talk sofia
say Sofia|It plays a little tune, then it waits for someone to play it back. Nobody has, for years.
say Sofia|If you repeat it, it keeps going. If you get it wrong, it sulks.
choose
> Why me? => why
> Okay. I'll try. => try
label why
say Sofia|Because you knocked back once. It remembers.
label try
say |A white piano sits in the lounge, lid already open, keys moving by themselves. Four of them glow: up, right, down, left.
mini simon 5 3 34
ifnot skipped played
say |(The piano forgave you. It played the last notes alone.)
label played
fx flash
say |The piano swells. A warm, slightly out-of-tune waltz fills the Inn. Every lamp brightens a notch.
say Sofia|It's happy. I didn't know it could be.
say Sofia|It asked me to tell you one thing. "Four floors deeper than the floor you thought was last."
say Amir|...What does that mean?
say Sofia|I don't know. It's a piano.
endday

# ================================================================ CH2 DAY 4
script c2_4
title Fix the Lift
bars on
scene room amir
cast amir 700
emote amir ...
say |Day 4. Youcef's text, 6:50 AM: "Elevator's skipping the Inn. Again. Come to the control room."
say Amir|At 6:50. In the morning.
say |On the wall, the elevator indicator blinks. It passes the Inn's number without stopping. Like it's embarrassed.
bars off
scene off
clearitems
npc youcef ctrl 900
goal Go down to the Elevator control room and talk to Youcef.
await floor ctrl
await talk youcef
say Youcef|Okay. The Inn's call button is dead. Contact corroded. Replacement bolts are in the shaft. Four of them.
say Youcef|The shaft's a mess. Don't lean over anything.
goal Go to Elevator shaft fix and find 4 bolts.
spawn bolt shaft 500
spawn bolt shaft 950
spawn bolt shaft 1500
spawn bolt shaft 1900
await items 4
say Amir|Four bolts. The shaft wind is trying to take my hat.
say Amir|I'm not wearing a hat.
say |The wind is very committed.
clearitems
goal Return to the control room and use the panel.
await floor ctrl
await use panel
say Youcef|Okay. Calibrate it. When the light hits green, hit the button. Be precise, it's picky.
mini timing 5 4 Inn_call_button 2
ifnot skipped calibrated
say |(Youcef pressed it for you. He sighed so loudly the panel fogged up.)
label calibrated
fx flash
say |Somewhere above, a soft chime. The elevator indicator jumps and stops on the Inn.
say Youcef|Done. The Inn is back on the map.
say Youcef|Not that I did anything. You did it. I just talked.
endday

# ================================================================ CH2 DAY 5
script c2_5
title The First Guest
bars on
scene inn amir aya_n dalia gabriel
say |Day 5. The whole crew is in the Inn lobby, dressed like a mismatched staff photo. Dalia's wearing a bellhop hat three sizes too big.
say Dalia|I'm the concierge today. Hi. Welcome. I'm Dalia and I will be your concierge. I mean, host. I mean, Dalia.
say Gabriel|She's been practicing for an hour.
say Aya@aya_n|Everyone positions! If the Knock keeps its word, a guest arrives today.
emote dalia !
say |Somewhere in the walls, three knocks. A pause. Three more. A bell above the front door rings by itself.
fx flicker
bars off
scene off
warp inn 600
npc aya_n inn 900
npc dalia inn 1100
npc gabriel inn 1000
goal Stand by the front desk. Talk to Aya.
await talk aya_n
say Aya@aya_n|Someone's coming up the old stairs from the shaft side. Quick, go meet them with the luggage cart!
spawn bag inn 1500
spawn bag inn 1700
spawn bag inn 2000
goal Pick up the 3 bags that came with the guest.
await items 3
bars on
scene inn amir aya_n dalia
say |A tall figure in a long grey coat stands in the doorway. Dust on the shoulders. A hat tilted forward. A very old brass key in one hand.
say ???|Reservation. Under "the Knock".
say Aya@aya_n|Room one. Welcome to the Further Inn, sir.
say ???|I'm no sir. I'm just early.
choose
> Can I take your coat? => coat
> What's your name? => name
label coat
say ???|No. Thank you. The coat stays.
goto after
label name
say ???|Names are heavy. I'll tell you when I check out.
label after
say |He walks past us to Room 1, tips the hat to a lamp, and closes the door softly.
say Dalia|Okay. That was either the best or worst start for a hotel.
say Gabriel|Both. It's always both.
bars off
scene off
set guest_one 1
clearitems
endday

# ================================================================ CH2 DAY 6
script c2_6
title Lamplight
bars on
scene inn amir sofia aya_n
cast amir 600
say |Day 6. The Inn's lamps flicker in a slow, uneven pulse. Sofia says the lamps remember a beat. Aya says that's weird. Sofia says so is the whole Inn.
say Sofia|If we hit the beat, the lamps wake up. If we don't, the lamps get embarrassed.
say Aya@aya_n|Lamps do not get embarrassed.
say Sofia|These ones do.
bars off
scene off
warp inn 600
npc sofia inn 1000
goal Talk to Sofia at the lamp stand.
await talk sofia
say Sofia|Four lamps. Four buttons. Hit each one when it passes the line. Don't think too hard. Feel it.
mini rhythm 18 6 100
ifnot skipped lit
say |(The lamps lit anyway. Sofia hummed with them, pretending not to notice.)
label lit
fx flash
say |All the lamps in the lobby bloom to warm gold, one after another, in rhythm.
say Sofia|Listen. The hum changed. It's not scary anymore. It sounds like... a lullaby.
say Amir|Or like a really big refrigerator.
say Sofia|You can't ruin this for me.
endday

# ================================================================ CH2 DAY 7
script c2_7
title The Ledger
bars on
scene inn amir aya_n
cast amir 700
say |Day 7. Aya spent the night cleaning behind the front desk and found a ledger. Leather, cracked, tied with string.
say Aya@aya_n|Look at the names. Everyone who ever checked in.
say Amir|There are a lot.
say Aya@aya_n|Look closer. Page 14.
bars off
scene off
warp inn 700
npc aya_n inn 900
goal Talk to Aya about the ledger.
await talk aya_n
say |The ink is old and slanted. Names, room numbers, dates. Midway down page 14: "L-001. AMIR. Room 000."
say Amir|That's... my room number. But with a different floor.
say Aya@aya_n|Dated tonight. Written today. With a pen from this lobby.
say Amir|I didn't write that.
say Aya@aya_n|I know. You'd have misspelled "reservation".
choose
> We should check all the names. => check
> Maybe it's a prank. => prank
label prank
say Aya@aya_n|Moths don't prank. And look at that.
goto moths
label check
say Aya@aya_n|Agreed. Starting with the thing that's chewing the ledger.
label moths
say |A cloud of grey dust moths swarms out of the ledger's spine. Hundreds of them. They are VERY hungry for paper.
mini fight 10 5 dust_moths
ifnot skipped fought
say |(The moths gave up after a while and went for a lamp instead.)
label fought
say Aya@aya_n|Saved. Mostly. There's a hole where the date should be.
say Amir|Which date?
say Aya@aya_n|The one next to your name.
set saw_ledger 1
endday

# ================================================================ CH2 DAY 8
script c2_8
title Night Shift
bars on
scene inn amir sofia tansaouti
cast amir 600
say |Day 8. After midnight. The Inn is asleep. Even the lamps are dim, as if they've pulled blankets up.
say Sofia|The missing page is in the east office. We have to get it without waking the guest in Room 1.
say Tansaouti@tansaouti|I'll take the corridor. Sofia listens. You walk.
say Amir|Why me?
say Tansaouti@tansaouti|You have the quietest shoes.
bars off
scene off
warp inn 300
npc sofia inn 800
npc tansaouti inn 1300
goal Sneak east through the hallway to the office. Stay out of the lamplight sweeps.
mini sneak 3 3 1
ifnot skipped through
say |(Sofia slid the page under the door. Quietly. Annoyingly well.)
label through
say |The office is small and dusty. On the desk, a single torn page. The missing date. It reads:
fx flicker
say |"Check-in: the day the Inn remembers its name."
say Sofia|Its name?
say Tansaouti@tansaouti|It had one. Before it was a Further Inn. Before it was a hotel.
say Amir|Which was?
say Tansaouti@tansaouti|I don't remember. That's the problem.
set saw_page 1
endday

# ================================================================ CH2 DAY 9
script c2_9
title Matching Names
bars on
scene room amir
cast amir 700
cast dalia -200
walk dalia 480 7 wait
emote dalia !
say Dalia|Amir! I made a map! Every resident! Every room number! Every name in the ledger! Matched!
say Amir|Matched how?
say Dalia|With string. And glitter. A lot of glitter.
say |A bulletin board is covered in red string, photos, notes and a blob of gold glitter in the shape of a question mark.
say Dalia|Eleven names in the ledger match someone in the building. Four don't. Two are... you. Twice.
bars off
scene off
clearitems
goal Ask three residents if their name was ever in an old hotel book: Anes (Common), Anais (Rare), Youcef (Main).
await talk anes
say Anes|A hotel book? I once signed a coffee order that way. Does that count?
await talk anais
say Anais|I've never stayed in a hotel. I once stayed in a tent that pretended to be one.
await talk youcef
say Youcef|Hotel? No. But the elevator logs include a booking from "Room 000" going back thirty years.
say Amir|Thirty years?
say Youcef|The building is thirty-one. It's older than it should be. I'm not saying anything. I'm saying numbers.
say Amir|Thanks. I think.
goal Meet Dalia on the Main floor.
await talk dalia
say Dalia|So? What did the string tell you?
say Amir|That Room 000 has been in the building longer than I have.
say Dalia|Oh. Oh no. I love this.
mini timing 6 4 Sort_the_ledger 2
ifnot skipped sorted
say |(Dalia sorted the last cards herself and gave herself a medal.)
label sorted
say Dalia|We find that room. I don't know how, I don't know when. But we find it.
set matched_names 1
endday
)IL";
