// story_chats_a.hpp - idle chat (with options) for Main, Lethal, Common and Uncommon characters.
// A chat script is started when you press A next to someone who is not part of the current quest.
// Edit freely. "=> end" leaves the chat. "ifday N label" jumps when the story is on day N or later.
#pragma once
static const char* STORY_CHATS_A = R"IL(
# ================================================================ MAIN FLOOR
script chat_arwa
label top
say Arwa|Oh, hi Amir. Careful with your voice, the walls on Main are thin.
choose
> What are you reading? => a
> Do you hear the bots at night? => b
> Bye, Arwa. => end
label a
ifday 12 a2
say Arwa|A book about old buildings. Did you know the 14 was designed to look like a stack of drawers? Everything has a place.
goto top
label a2
say Arwa|A book about building plans. I keep finding rooms on the drawings that aren't on any floor. Strange, right?
goto top
label b
say Arwa|Every night. Sweepy hums a little song while he cleans. I pretend I'm asleep so he doesn't get shy.
goto top

script chat_dalia
label top
say Dalia|Amir! You look like you need a snack. Or a plan. Or both.
choose
> How's your day? => a
> Any gossip? => b
> What's with the secret door? => c
> See you. => end
label a
ifday 16 a2
say Dalia|Busy! Everybody on this floor needs me for something. It's flattering and exhausting.
goto top
label a2
say Dalia|Better now. Things have been strange lately, but strange with friends is almost fun.
goto top
label b
say Dalia|Ok ok. I heard Raceem lost a race to a Cleaning bot. Bot didn't even know it was racing.
goto top
label c
ifnot secret_open cx
say Dalia|The Stairway to Hell? Keep it quiet. If the whole building knew, they'd put a lock on it, and then where would we escape?
goto top
label cx
say Dalia|What door? I don't see a door. Nothing to see here. Ha.
goto top

script chat_dania
label top
say Dania|Hey! Perfect timing, I need a spotter. Or a witness. Either works.
choose
> What are you training for? => a
> Can I try? => b
> Maybe later. => end
label a
say Dania|Nothing! That's the best part. I run the stairs because they're there. 14 floors up, 14 floors back.
goto top
label b
say Dania|Sure. Two laps around the Main hall. Winner gets bragging rights and a cold drink.
say Amir|And the loser?
say Dania|Gets to carry the cold drinks. Come on!
goto top

script chat_gabriel
label top
say Gabriel|Hey. Don't touch my headphones, they're on the desk for a reason.
choose
> What are you listening to? => a
> You're calm about everything. => b
> Catch you later. => end
label a
say Gabriel|Old stuff. Slow drums, one guitar. It helps me think. And helps me ignore Youcef's hammering.
goto top
label b
ifday 22 b2
say Gabriel|Panic doesn't fix anything. Panic plus a plan fixes things. Slowly, but it does.
goto top
label b2
say Gabriel|After the Backrooms, I don't panic anymore. I save it for emergencies. Like the elevator.
goto top

script chat_youcef
label top
say Youcef|Mind the toolbox. If you trip on it, it's your fault, I put a sign.
choose
> What are you fixing? => a
> Can you fix my elevator luck? => b
> Never mind, bye. => end
label a
ifday 7 a2
say Youcef|The usual. A squeaky hinge, a flickering light, a Cleaning bot that thinks it's a ceiling fan.
goto top
label a2
say Youcef|The elevator, mostly. It has a mood. I'm learning its moods. It's like a cranky cat.
goto top
label b
say Youcef|I can fix hinges, bulbs, and pipes. Luck, no. Luck is above my pay grade.
goto top

# ================================================================ LETHAL FLOOR
script chat_raceem
label top
say Raceem|Amir. Hold on, I'm timing something. ...Okay, thirty-one seconds. New record.
choose
> Timing what? => a
> Is it fast? => b
> Bye. => end
label a
say Raceem|Me, walking from my room to the elevator and back. The shortcut through the bots' corner saves four steps.
goto top
label b
say Raceem|Fast enough to beat a Cleaning bot. Barely. Bolt is an unfair opponent.
goto top

script chat_adam_l3
label top
say Adam@adam_l3|Oh. Hi. If you're looking for the other Adam, he's on Teen. I'm the quiet one.
choose
> How many Adams live here? => a
> What do you do all day? => b
> OK, bye. => end
label a
say Adam@adam_l3|Five, last I counted. It's a lot. We have a group chat. It's chaos. Mostly memes.
goto top
label b
say Adam@adam_l3|Draw. Mostly buildings. This one, in boxes. You wouldn't believe how many windows it has.
goto top

script chat_amir_l4
label top
say Amir@amir_l4|Oh no, another one of me. Hi, Amir.
choose
> Hi, Amir. => a
> Which of us is the cool one? => b
> Bye. => end
label a
say Amir@amir_l4|People keep delivering your mail to me. I keep delivering it to you. Mail tennis.
goto top
label b
say Amir@amir_l4|Obviously me. I have a plant. You have... what do you have? A bot?
say Amir|A very good bot.
say Amir@amir_l4|Fair.
goto top

script chat_aya_l
label top
say Aya@aya_l|Amir! Look, look, look. I taught my bot a trick.
choose
> What trick? => a
> Is it dangerous? => b
> Later, Aya. => end
label a
say Aya@aya_l|It spins. It also hums. It also falls over. We're working on the third part.
goto top
label b
say Aya@aya_l|Only to socks. Don't leave socks around it. It gets competitive.
goto top

script chat_basmala
label top
say Basmala|Shh. Okay, you can talk. I'm just counting stairs in my head.
choose
> Why count stairs? => a
> You seem peaceful. => b
> Bye. => end
label a
say Basmala|Because the building always lies about how many there are. Eight, twelve, fifteen... it changes.
goto top
label b
say Basmala|I like quiet mornings. And the smell of warm bread from somewhere on Common. Don't ask me where.
goto top

script chat_adam_l7
label top
say Adam@adam_l7|Hey Amir. My room's L-007, Fares is OL-007. Everyone confuses us. Mail, pizza, everything.
choose
> Does Fares get your pizza? => a
> What's OL stand for? => b
> Later. => end
label a
say Adam@adam_l7|Every time. I've started leaving a note: "Not yours, Fares." He thinks it's a game.
goto top
label b
say Adam@adam_l7|No clue. Ask Fares. Actually, don't. He'll tell you a story with three endings.
goto top

script chat_fares
label top
say Fares|OL-007. Over Lethal. Or Out of Lethal. Or Old Lamp. Depends on the day.
choose
> Which is it? => a
> Why the dark clothes? => b
> I'll leave you alone. => end
label a
say Fares|The truth? Somebody typed it wrong on the door plate, and I liked it too much to fix it.
goto top
label b
say Fares|Dark clothes hide pizza sauce. Practical fashion.
goto top

# ================================================================ COMMON FLOOR
script chat_anes
label top
say Anes|Mornin'. Or afternoon. Coffee's on, if you want some. It's strong enough to open doors.
choose
> What's in the coffee? => a
> You're always so calm. => b
> Thanks, bye. => end
label a
say Anes|Secret. Cardamom, patience, and a bit of luck. The luck runs out around Thursday.
goto top
label b
say Anes|The Common floor is the common-sense floor. We don't rush. We sip.
goto top

script chat_iyad
label top
say Iyad|Hey, Amir. Don't mind the mess, it's organized chaos. I know where everything is. Mostly.
choose
> What do you collect? => a
> Any good stories? => b
> See you. => end
label a
say Iyad|Bottle caps, old keys, one very confused watch. The watch runs backwards, I'm pretty sure it's a clue to something.
goto top
label b
say Iyad|Once a Cleaning bot swept my key collection into a bag and returned it sorted by size. Best day of my life.
goto top

# ================================================================ UNCOMMON FLOOR
script chat_alicia
label top
say Alicia|Amir! Perfect. We need a fourth for cards. Abdullah is cheating again.
choose
> Cheating how? => a
> I'm not good at cards. => b
> Later! => end
label a
say Alicia|He counts out loud. Then pretends he didn't. Then wins. It's infuriating.
goto top
label b
say Alicia|That's fine, nobody is. We just yell a lot and eat pistachios.
goto top

script chat_abdullah
label top
say Abdullah|I'm not cheating. I'm calculating. There's a difference.
choose
> That's cheating. => a
> Teach me. => b
> Bye. => end
label a
say Abdullah|It's strategy! Also Alicia hides cards in her sleeve. Don't tell her I told you.
goto top
label b
say Abdullah|Lesson one: smile when you lose. Lesson two: smile louder when you win. Lesson three: pistachios.
goto top

script chat_jalil
label top
say Jalil|Oh, Amir. Do me a favor, tell me what color this wall is. I've been staring at it for ten minutes.
choose
> Beige? => a
> Why are you staring at it? => b
> I'll leave you to it. => end
label a
say Jalil|BEIGE. Ha. I knew it. Alicia says it's "ivory". There's a difference apparently. I'm out of my depth.
goto top
label b
say Jalil|I'm designing a mural. In my head. It has a moon, a bus, and a very confident bot.
goto top

script chat_adam_uc
label top
say Adam@adam_uc|Hey. Don't worry, I'm not the one who knocks things over. That's T-002.
choose
> I met T-002. At full speed. => a
> How's Uncommon floor? => b
> Bye. => end
label a
say Adam@adam_uc|Ha, yeah. You've been introduced. Everyone gets introduced eventually.
goto top
label b
say Adam@adam_uc|Neither common nor rare, just right in the middle. We like it. The elevator stops here more than anywhere.
goto top

script chat_amira
label top
say Amira|Oh good, a friendly face. I need a taste tester. Don't say no.
choose
> What did you make? => a
> Is it safe? => b
> Maybe later. => end
label a
say Amira|Cardamom cookies. They are either perfect or a weapon, I haven't figured out which.
goto top
label b
say Amira|Mostly. Gabriel survived the last batch. He said it "built character".
goto top
)IL";
