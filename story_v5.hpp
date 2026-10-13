// story_v5.hpp - v0.5.0: Reghaia, cable car, cinema, Etusa bus + school, rooms, custom replies, the beef, Chapter 4 preview
#pragma once
static const char* STORY_V5 = R"IL(
# ================================================================ GOING OUTSIDE
script use_frontdoor
say |The front door. Outside is Reghaia, the main road, the bus stop, the cable car. Go out?
choose
> Step outside => go
> Not now => end
label go
fx fadeout
wait 30
warp reghaia 380
fx fadein
toast Reghaia
say |Sea air, tar, and somebody grilling something three streets away. The 14 stands behind me. The bus stop is to the right, the cable car station further down the road.

script use_p_home
say |Back to the 14?
choose
> Go inside => go
> Stay out here => end
label go
fx fadeout
wait 30
warp lobby 2050
fx fadein
toast Lobby

script use_p_kiosk
say |The kiosk guy slides me a bag of sunflower seeds without being asked.
say Kiosk guy|Amir. The usual. Don't tell Dalia I'm still giving you credit.
toast Sunflower seeds: +0 (they are free)

# ---------------------------------------------------------------- ETUSA BUS + SCHOOL
script use_p_busstop
say |The Etusa bus stop. Line 14 stops here. The sign says "school" in three languages and "late" in all of them.
choose
> Take the bus to school => go
> Not now => end
label go
set bus_passing 1
badge bus
bars on
scene outside amir
cast amir 300
say |The Etusa bus coughs around the corner. Doors hiss open. Amir climbs on with his backpack and exactly zero minutes of margin.
emote amir !
walk amir 1100 6 wait
fx shake
say |Every seat is taken. Everyone on the bus is staring at their phone. One kid stares at Amir's backpack. It has a patch: "14".
fx fadeout
wait 40
bars off
scene off
warp school 300
npc zerrouki school 900
npc benali school 1650
npc hadj school 2250
fx fadein
toast School
ifnot school_done first
say |Back at school. Everybody knows exactly how late you are.
end
label first
say |School. The bell rings. Mrs. Zerrouki is waiting at the classroom door with her arms crossed. The Principal is wandering the corridor looking for someone to blame.
goal Go to class (3B), then to the yard, then to the teachers' room.

script use_p_class
ifnot school_class cls
say |Class 3B is empty now. The board still says "AMIR TRIED" and it's underlined twice.
end
label cls
bars on
scene room amir zerrouki
cast amir 1100
cast zerrouki 300
walk zerrouki 760 5 wait
emote zerrouki !
say Mrs. Zerrouki|Amir. Eleven minutes late. Again.
anim amir bow
say Amir|The bus was... emotionally unavailable.
say Mrs. Zerrouki|Sit. Pop quiz. If you pass, I forget the bus.
bars off
scene off
mini quiz 5 school
ifnot skipped quizdone
say |(The quiz gave you a hint. It may have been Mrs. Zerrouki.)
label quizdone
say Mrs. Zerrouki|...Not bad. Not bad at all. You may sit.
set school_class 1
toast Class done. Next: the yard.

script use_p_yard
ifnot school_class noclass
ifnot school_yard yard
say |The yard. A deflated ball and a crowd of kids still talking about the dodgeball massacre.
end
label noclass
say |The yard. Mr. Benali is already blowing his whistle. Maybe I should go to class first, like a normal person.
end
label yard
bars on
scene outside amir benali
cast amir 400
cast benali 1500
walk benali 900 6 wait
emote benali !
say Mr. Benali|AMIR! DODGEBALL! Today you're the whole team!
anim benali spin
say Amir|That's not a team. That's a target.
bars off
scene off
mini dodge 22 4 1
ifnot skipped dodgeok
say |(Mr. Benali blew his whistle and called a dramatic timeout.)
label dodgeok
say Mr. Benali|That's the spirit. Go see the teachers' room. Bring your appetite.
set school_yard 1
toast Yard done. Last: the teachers' room.

script use_p_office
ifnot school_yard notyet
ifnot school_done sc
say |The teachers' room. A kettle, a plant, and nine teachers who all think they raised Amir.
end
label notyet
say |The teachers' room. The door is shut. Voices inside. I should finish class and the yard first.
end
label sc
bars on
scene room amir hadj zerrouki
cast amir 300
cast hadj 1450
cast zerrouki 1250
walk hadj 800 4 wait
emote hadj !
say Principal Hadj|Amir. Detention. A month. For being late, loud and... what is that on your backpack?
say Amir|It's a 14.
say Principal Hadj|It's a mess. Three weeks of detention. Starting-
walk zerrouki 600 6 wait
emote zerrouki !
say Mrs. Zerrouki|He passed my quiz.
cast benali 1400
walk benali 520 7 wait
say Mr. Benali|He took every dodgeball for the team.
emote hadj ...
say Principal Hadj|...Both of you?
anim zerrouki bow
anim benali hop
say Mrs. Zerrouki|Nobody touches this boy. The teachers got his back.
say Mr. Benali|ALL of us.
fx flash
say Principal Hadj|...Fine. No detention. But the bus gets a seatbelt.
say |Amir stands very still. Nobody has ever fought for him in a principal's office.
set school_done 1
badge teachers
ending e_school
toast BADGE: Teachers got yo back
bars off
scene off
fx confetti
say |A very small, very proud school-sized celebration happens in the teachers' room. Someone has a cake from the canteen. It's not a good cake. It's perfect.

script use_p_schoolexit
say |The bus stop outside school.
choose
> Take the bus home => go
> Stay at school => end
label go
fx fadeout
wait 30
warp reghaia 900
fx fadein
toast Reghaia

# ---------------------------------------------------------------- CABLE CAR + EL MADANIA + CINEMA
script use_p_cable
say |The cable car station. A little red cabin swings over the hill toward El Madania. The ticket window says "ONE WAY: 0 DZD (promotional week)".
choose
> Ride the cable car to El Madania => go
> Not now => end
label go
badge cable
bars on
scene sunset amir
cast amir 640
say |The cabin lifts off the platform with a gentle bump. Reghaia shrinks under the glass. The sea turns gold.
anim amir hop
emote amir wow
fx shake
say |Halfway up, the cabin sways. A kid in the next cabin waves. Amir waves back like a diplomat.
anim amir wave
say |The whole of the east of Algiers rolls past: the lake, the road, the 14 getting smaller until it looks like a toy.
fx fadeout
wait 40
bars off
scene off
warp madania 380
fx fadein
toast El Madania
say |El Madania. Hilltop air, old white buildings, and a cinema with a flickering marquee.

script use_p_cableback
say |The cable car back down to Reghaia.
choose
> Ride down => go
> Stay in El Madania => end
label go
fx fadeout
wait 30
warp reghaia 2300
fx fadein
toast Reghaia

script use_p_viewpoint
say |The viewpoint. Algiers below, the bay beyond it, and a line of ships waiting for something. For a second, nothing is chasing me. Nothing is knocking. It's lovely.

script use_p_cinemadoor
say |The cinema. The marquee says: "TONIGHT: THREE FILMS, ONE POPCORN MACHINE."
choose
> Go in => go
> Not now => end
label go
fx fadeout
wait 30
warp cinema 380
fx fadein
toast Cinema

script use_p_cinexit
fx fadeout
wait 30
warp madania 1500
fx fadein
toast El Madania

script use_p_ticket
ifnot ticket_bought buy
say |The ticket lady nods. You already have a ticket. The hall is to the east.
end
label buy
say Ticket lady|One ticket. Which film?
choose
> The Haunted Elevator (horror) => horror
> Bots in Space (animation) => anim
> Papercraft Detective (comedy) => comedy
label horror
set film 1
goto got
label anim
set film 2
goto got
label comedy
set film 3
label got
set ticket_bought 1
say Ticket lady|Row D, seat 14. Of course it is.
toast Ticket bought. Grab popcorn, then head to the hall.

script use_p_snack
say |The popcorn stand. The machine is old and hot and loud and it smells like heaven.
say Popcorn man|Catch the kernels in the bucket, and the popcorn is on the house. No burnt ones, though.
choose
> Easy mode (3 mistakes allowed) => easy
> Perfect popcorn (no mistakes) => perfect
label easy
mini popcorn 10 3 1
ifnot skipped easyok
say |(The popcorn machine took pity on you.)
label easyok
set popcorn 1
say Popcorn man|Free popcorn! Don't spill it on the seat.
end
label perfect
mini popcorn 10 0 2
ifnot skipped perfok
say |(Skipped. The popcorn man noticed.)
end
label perfok
set popcorn 1
badge popcorn
say Popcorn man|PERFECT! You're hired. Not really. Here's a large popcorn.
toast BADGE: Popcorn Pro

script use_p_hall
ifnot ticket_bought noticket
bars on
scene night amir
cast amir 640
say |Row D, seat 14. The lights go down. The whole hall smells like butter and old velvet.
fx dark
ifnot film f1
say |(Nothing yet. A trailer plays about a talking bot who sells insurance.)
label f1
if film f2
goto story
label f2
label story
fx lights
say |The screen flickers on.
ifge film 2 notf1
say |THE HAUNTED ELEVATOR. A building that has too many floors. A boy who hears three knocks. A door he can't open. It's almost too familiar.
emote amir ...
say Amir|...I think I know this plot.
goto endfilm
label notf1
ifge film 3 notf2
say |BOTS IN SPACE. A tiny Cleaning bot flies to the moon to find the one dust bunny that got away. There is a lot of crying, and not only from the bots.
emote amir <3
goto endfilm
label notf2
say |PAPERCRAFT DETECTIVE. A detective solves a mystery with scissors, glue and a surprising amount of tape. He finds the thief. It was the cat. It's always the cat.
anim amir hop
label endfilm
fx flash
say |The credits roll. Amir stays for the post-credits scene, because he is the kind of person who does.
say Amir|...Do I love cinema?
choose
> Yes. I love cinema. => yes
> It was okay. => ok
label yes
say Amir|I love cinema.
goto done
label ok
say Amir|It was good. Maybe I do love it. A little.
label done
set cinema_seen 1
badge cinema
ending e_credits
toast BADGE: Do you love cinema ?
bars off
scene off
end
label noticket
say |The hall is guarded by an usher with a flashlight. "Ticket, please." I should buy one at the desk first.

# ---------------------------------------------------------------- ROOMS (Amir, Dalia, Gabriel)
script door_L-001
say |My room. Open the door?
choose
> Go in => go
> Not now => end
label go
fx fadeout
wait 30
warp room_amir 240
set seen_room_amir 1
fx fadein
toast Amir's room
ifnot seen_room_dalia chk
ifnot seen_room_gabriel chk
badge neighbor
label chk

script door_M-002
say |Dalia's door. There's a handwritten sign: "KNOCK. THEN KNOCK AGAIN. THEN WAIT."
choose
> Knock three times => go
> Walk away => end
label go
say Dalia|COME IN! WAIT! DON'T LOOK AT THE BOARD! OKAY LOOK AT IT!
fx fadeout
wait 30
warp room_dalia 240
npc dalia room_dalia 800
npc mopsy room_dalia 520
set seen_room_dalia 1
fx fadein
toast Dalia's room
ifnot seen_room_amir chk
ifnot seen_room_gabriel chk
badge neighbor
label chk

script door_M-004
say |Gabriel's door. A neat sign: "KNOCK ONCE. IF IT'S NOT URGENT, DON'T."
choose
> Knock once => go
> Walk away => end
label go
say Gabriel|...Come in. But don't touch the rope.
fx fadeout
wait 30
warp room_gabriel 240
npc gabriel room_gabriel 900
npc zed room_gabriel 1300
set seen_room_gabriel 1
fx fadein
toast Gabriel's room
ifnot seen_room_amir chk
ifnot seen_room_dalia chk
badge neighbor
label chk

script use_p_exit_amir
fx fadeout
wait 30
warp lethal 600
fx fadein

script use_p_exit_dalia
fx fadeout
wait 30
warp main 600
fx fadein

script use_p_exit_gabriel
fx fadeout
wait 30
warp main 1500
fx fadein

script use_p_amir_bed
say |My bed. Orange sheets, a pillow with a dent in the shape of Bolt, who is NOT allowed on the bed.
say Amir|Not now. I have a building to save.

script use_p_amir_desk
say |My desk. A pile of papercraft, a half-finished model of the 14, and a mug that says "WORLD'S OKAYEST RESIDENT".
say |There's a little puzzle on the desk: a light-board Amine gave me.
mini lights 3
toast You solved the desk puzzle.

script use_p_amir_wall
say |The wall of photos. Dalia mid-sneeze. Gabriel holding a rope. Amine covered in glue. Bolt blurry, because he never holds still.
say |At the center, a photo of all of us on the roof on Îlot14 Day. Everyone is laughing. Nobody noticed me taking it.

script use_p_dalia_bed
say |Mopsy's charging spot. A cushion, a tiny blanket, and a sign that says "MOPSY'S HOUSE. NO DUST ALLOWED. (DUST: GABRIEL.)"

script use_p_dalia_phone
say |Dalia's phone, face-up. Six drafts, all addressed to me. The first says "hi". The sixth says "AMIR CALL ME". Nothing in between. She's thorough.

script use_p_dalia_board
say |The plan board. Sticky notes, red string, a map of the 14 with a pin in every floor. A note in the corner: "THINGS TO FIX: EVERYTHING."
mini pairs 4 6
toast You sorted the sticky notes.

script use_p_gab_rope
say |A neat coil of rope on a hook. It's very, very well kept.
say Gabriel|Don't touch it.
say Amir|I wasn't.
say Gabriel|You were thinking about it.

script use_p_gab_shelf
say |Gabriel's shelf: a flashlight, three tapes, a rubber duck, a book on knots, and a framed photo of a cat I've never seen him mention.

script use_p_gab_zed
say |Zed's corner. A little cushion, a spare cable, and a hand-lettered sign: "I DON'T CARE."
say |Zed beeps once. It sounds suspiciously like "I do."

# ---------------------------------------------------------------- GABRIEL IN HIS ROOM (type a number...)
script chatroom_gabriel
say Gabriel|You're in my room. That's a bold choice.
choose
> Chat normally => chat
> Tell him a number => num
> Leave him alone => end
label chat
say Gabriel|The rope is not a topic.
say Amir|I didn't say anything.
say Gabriel|You were about to.
end
label num
say Gabriel|A number? Fine. Say it. Slowly.
run reply_gabriel
end

script reply_gabriel
ask TELL GABRIEL A NUMBER
ifsay 86969 scare
ifsay iykyk beef
ifsay adam beef
ifsay amyas beef
ifsay 69 nice
ifsay 14 fourteen
ifsay 42 fortytwo
say Gabriel|...That's not a number I know. Okay. Moving on.
end
label nice
say Gabriel|No. Absolutely not. Delete that.
end
label fourteen
say Gabriel|Fourteen. The only good number. Carry on.
end
label fortytwo
say Gabriel|The answer to everything. Don't make it weird.
end
label beef
run beef_start
end
label scare
say Gabriel|...What did you just say?
emote gabriel ...
say Gabriel|Don't. Don't say that to me.
scare
say Gabriel|...It's October. I told you not to say numbers in October.
say Amir|It's just a prank, right? The pumpkin and everything?
say Gabriel|Yes. The pumpkin is the scary part. I'm going to pretend that didn't happen.
ending e_scare
badge haunted

# ---------------------------------------------------------------- SAY SOMETHING TO ANYONE (press X near a person)
script reply_default
ask SAY SOMETHING
ifsay iykyk beef
ifsay adam beef
ifsay amyas beef
ifsay 86969 weird
ifsay hello hi
ifsay hi hi
ifsay bolt bolt
ifsay prime prime
ifsay pizza pizza
ifsay cinema cinema
ifsay school school
ifsay code code
say |They blink at you for a moment, then nod slowly. "...Right. Okay."
end
label hi
say |They wave back. "Hey. Good to see you."
end
label bolt
say |"Is that your bot? The loud one? The one who runs into doors?" ...He's the best.
end
label prime
say |"Prime? The old bot? He talks in capitals. Be nice to him, he's lonely."
end
label pizza
say |"Pizza? Now? You're making me hungry."
end
label cinema
say |"Cinema? Take the cable car to El Madania. There's a place with a popcorn machine that sounds like a jet engine."
end
label school
say |"School? Take the Etusa bus from the stop outside. Don't be late."
end
label code
say |"Codes? Try Extras on the main menu. Rumor has it the building talks if you say the right word."
end
label weird
say |They freeze. Slowly, they take a step away from you. "...Please don't say that near Gabriel."
end
label beef
run beef_start

# ---------------------------------------------------------------- THE BEEF (Adam + Amyas, reason unknown)
script beef_start
ifnot beef_on b1
say |Everyone within earshot stops talking. A very long second passes. "...You're really still on that?"
end
label b1
set beef_on 1
badge beef
npc adam_t teen 900
npc amyas teen 1100
say |The word hangs in the air. Everyone nearby goes very quiet. Somewhere far below, a motorcycle engine revs once.
say Amir|IYKYK. If you know, you know.
say |Nobody says what it is about. Not even Amir.
toast The beef is on. Find Adam and Amyas on the Teen floor.
goal Go to the Teen floor and talk to Adam.

script beef_adam
ifnot beef_on n0
ifnot beef_done0 st0
say Adam|We're good. Don't make it weird.
end
label n0
say Adam|Hey. Everything good? You look like you're about to say something.
end
label st0
say Adam|...You said it. Out loud. In front of the building.
say Amir|I said it. You know why.
say Adam|Do I? ...Fine. If you want to settle this, let's settle this.
choose
> Settle it. (fight) => fight
> Not yet. => end
label fight
mini fight 12 6 adam
ifnot skipped f0
say |(Adam stepped back and let you win. He is bad at throwing fights.)
label f0
say Adam|...Okay. That's one. Go see Amyas.
set beef_done0 1
goal Talk to Amyas for round two.
end

script beef_amyas
ifnot beef_on n0
ifnot beef_done0 w0
ifnot beef_done1 st1
say Amyas|We're good. Don't make it weird.
end
label n0
say Amyas|Ice cream later? I'm off at five.
end
label w0
say Amyas|Adam first. Those are the rules. I just made them up.
end
label st1
say Amyas|Round two. Dodge. If you can.
choose
> Dodge it. => d
> Not yet. => end
label d
mini dodge 28 4 3
ifnot skipped d1
say |(The bullets of dust went around you. Amyas looks offended.)
label d1
say Amyas|...That's two. You win. Okay. I'm out.
say Amir|IYKYK?
say Amyas|IYKYK.
set beef_done1 1
set beef_over 1
toast The beef is over. (Or is it?)
ending e_knock

# ---------------------------------------------------------------- CHAPTER 4 PREVIEW (TBD)
script c4_1
title Preview: Never
card CHAPTER 4|NEVER
bars on
scene roof amir dalia gabriel bolt
cast amir 320
cast dalia 1500
cast gabriel 1600
cast bolt 1700
walk dalia 640 5
walk gabriel 820 5
walk bolt 980 7 wait
say |A new morning on the Roof. The banner still says WELCOME BACK. Something under it is different.
emote bolt !
say Bolt|BEEP! There's a NEW DOOR on the Roof! It wasn't here yesterday!
say Dalia|There's no door on the Roof. There's never been a door on the Roof.
fx shake
say Gabriel|...There is now.
anim amir shake
say |A grey door has grown out of the water tank. A nameplate. Brass. It reads: "C-4".
bars off
scene off
warp roof 700
npc dalia roof 900
npc gabriel roof 1100
goal Talk to Dalia on the Roof.
await talk dalia
say Dalia|I counted. It's the fifteenth floor. The building has a fifteenth floor now.
say Amir|The 14... has fifteen?
set c4_door 1
endday

script c4_2
title Preview: The Fifteenth
bars on
scene roof amir gabriel
cast amir 400
cast gabriel 1500
walk gabriel 760 4 wait
say Gabriel|I tried the door. It's locked. The lock is shaped like a handprint. Yours.
say |It's the second time a door has wanted my hand.
bars off
scene off
warp roof 900
npc gabriel roof 1050
goal Talk to Gabriel.
await talk gabriel
say Gabriel|If you open it... it might be the end. Or the middle. I don't know which.
mini quiz 5 ilot14
say |The handprint glows. Behind the door, a hum. Not the building's. Something older.
set c4_hand 1
endday

script c4_3
title Preview: Coming Soon
bars on
scene night amir dalia gabriel bolt prime
say |Night on the Roof. Everyone gathers. Bolt falls asleep on Amir's shoe. Prime stands guard, very proud.
say Dalia|Whatever's up there, we do it together.
say Prime|TOGETHER. AND WITH A KETTLE.
say Amir|Together.
fx flash
bars off
scene off
card TO BE CONTINUED|Chapter 4 is a preview. More soon.
endday
)IL";
