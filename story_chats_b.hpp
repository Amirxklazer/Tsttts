// story_chats_b.hpp - idle chat for Rare, Special, Teen, Further inn and the Cleaning bots.
#pragma once
static const char* STORY_CHATS_B = R"IL(
# ================================================================ RARE FLOOR
script chat_anais
label top
say Anais|Hello, Amir. Mind the wet canvas on your left. It's my masterpiece. Or a very large mistake.
choose
> What are you painting? => a
> Can I have a paper roll? => b
> I'll go. => end
label a
say Anais|The 14 at sunset. Everyone paints it at sunset. I'm painting it at sunset in the rain. Very original.
goto top
label b
say Anais|Paper rolls? I have a hundred. You're welcome to as many as you can carry. Not near the paint, though.
goto top

script chat_maysanne
label top
say Maysanne|Amir! Do you know what a good rhyme for "elevator" is? I'm stuck.
choose
> Alligator? => a
> You write songs? => b
> Gotta go. => end
label a
say Maysanne|"Elevator, alligator". Ha! That's terrible. I'm using it.
goto top
label b
say Maysanne|Songs, poems, grocery lists, all with rhymes. Rhyming is how I stay sane. Ask anyone. Ask Jilali, he'll agree. Probably.
goto top

script chat_jilali
label top
say Jilali|Welcome to the Rare floor. We are rare because nobody visits. You're a happy exception.
choose
> Why does nobody visit? => a
> What do you do here? => b
> See you, Jilali. => end
label a
say Jilali|The elevator skips us when it's feeling dramatic. Youcef says it's "maintenance". I say it's elitist.
goto top
label b
say Jilali|I fix watches. Old ones. Some of them run backwards, Iyad's, for example. I'm learning why.
goto top

# ================================================================ SPECIAL FLOOR
script chat_amine
label top
say Amine|Amiiiir! My favorite person in all nine buildings!
choose
> You say that about everyone. => a
> How's Îlot22? => b
> I'll see you later, Amine. => end
label a
say Amine|Only people who owe me snacks. You owe me snacks. It's a very small, very exclusive group.
goto top
label b
say Amine|Quiet. Our stairwell light has been flickering since last week. It's basically a nightclub now.
goto top

script chat_kenzy
label top
say Haydar|Careful, careful, don't touch the wires. They're not plugged in. Probably.
choose
> What are you building? => a
> Is that safe? => b
> I'll stay back. => end
label a
say Haydar|A radio that picks up everything. Cleaning bot chatter, the elevator's secrets, maybe something stranger.
goto top
label b
say Haydar|Define safe. I've only been shocked twice this week, which is an improvement.
goto top

# ================================================================ TEEN FLOOR
script chat_amyas
ifnot beef_on cb_amyas
ifge beef_over 1 cb_amyas
run beef_amyas
end
label cb_amyas
label top
say Amyas|Amir. Careful, I'm off shift. Which means I'm only partially nice. Do not ask for ice cream.
choose
> Can I ask for ice cream? => a
> How's the shop? => b
> (mutter) Not that I care about the shop. => t
> See you, Amyas. => end
label a
say Amyas|You just did. Hmm. Okay. Strawberry. But we're not friends.
goto top
label t
say Amir|I-It's not like I came to see you. I was just passing by. Don't get the wrong idea.
say Amyas|You walked up three floors to "pass by". Sure. Strawberry?
say Amir|...Fine. But it's not a favor.
goto top
label b
say Amyas|Busy. Everybody wants cones on a hot day. Nobody wants to hold the cone on a hot day.
goto top

script chat_adam_t
ifnot beef_on cb_adam_t
ifge beef_over 1 cb_adam_t
run beef_adam
end
label cb_adam_t
label top
say Adam|Amir!! Hey! Don't worry, I'm walking now. Look, walking. No sprinting. Don't make me regret it.
choose
> Where were you running to? => a
> Please look where you go. => b
> (mutter) Not that I was worried. => t
> I'll leave you in peace. => end
label a
say Adam|Everywhere. All the time. I think my legs are on a schedule my brain doesn't know about.
goto top
label b
say Adam|I will. Seriously. I'm adding it to my list. It's a long list, but it has good items.
goto top
label t
say Amir|D-don't misunderstand. I'm only saying it because you'd break something. Not because I care.
say Adam|Sure, sure. You totally don't care. You're a terrible liar, Amir.
say Amir|Shut up. ...Be careful anyway.
goto top

script chat_lilian
label top
say Lilian|Shh. Come closer. Not that close. There. Do you know what I know?
choose
> What do you know? => a
> No, and I don't want to. => b
> Bye, Lilian. => end
label a
say Lilian|I'm not telling. But I know it. That's the important part. Knowing is half the fun.
goto top
label b
say Lilian|Smart. Smart people live long. Nosy people live interestingly.
goto top

# ================================================================ FURTHER INN
script chat_aya_n
label top
say Aya@aya_n|Welcome to the Further Inn! Check-in is... whenever you feel like it. Check-out is also whenever.
choose
> It's quiet down here. => a
> Do guests ever show up? => b
> Thanks, bye. => end
label a
say Aya@aya_n|The quiet is included in the room price. So is the hum. And the occasional echo. You get a lot for free.
goto top
label b
say Aya@aya_n|Only the bravest. Or the lost. Mostly the lost. They get free mints.
goto top

script chat_tansaouti
label top
say Adam Tansaouti|Don't call me just "Adam". It's Tansaouti. There are too many Adams. I need the full thing.
choose
> Fine, Tansaouti. => a
> What are you doing way down here? => b
> Later. => end
label a
say Adam Tansaouti|Thank you. Respect is a rare resource. Like water in the vents.
goto top
label b
say Adam Tansaouti|Playing games, mostly. And waiting for someone brave enough to challenge me. I'm very undefeated. For now.
goto top

script chat_sofia
label top
say Sofia|Quiet. Please. I'm listening to the walls.
choose
> What do the walls say? => a
> That sounds creepy. => b
> I'll go. => end
label a
say Sofia|Mostly pipes. Sometimes a tune. Sometimes someone laughing, far away, from nowhere. I like that one.
goto top
label b
say Sofia|It's not creepy. It's company. You just have to know how to hear it.
goto top

# ================================================================ 14 CLEANING BOTS(tm)
script chat_sweepy
label top
say Sweepy|BEEP! Hello Amir! I cleaned a floor today. It is still clean! I am so proud!
choose
> Good job, Sweepy. => a
> Who do you belong to? => b
> Keep it up! => end
label a
say Sweepy|Thank you! I will clean it again tomorrow. And the day after. Cleaning is love!
goto top
label b
say Sweepy|Arwa! She reads quietly. I clean quietly. We are very quiet together.
goto top

script chat_mopsy
label top
say Mopsy|Hmph. Humans track mud. Then they say "oh sorry". Sorry doesn't mop floors.
choose
> You okay, Mopsy? => a
> You belong to Dalia, right? => b
> I'll leave you to it. => end
label a
say Mopsy|I'm grumpy, not broken. Please don't make it a thing.
goto top
label b
say Mopsy|Yes. Dalia is okay. For a human. She says thank you. Rare, in this building.
goto top

script chat_dustin
label top
say Dustin|Oh no. Oh no no no. Is it going to rain? Is something falling? Is the floor safe?
choose
> The floor is safe. => a
> What are you scared of? => b
> Calm down, Dustin. => end
label a
say Dustin|Are you SURE? Sure sure? Okay. Okay. Thank you. I'll clean twice just in case.
goto top
label b
say Dustin|Stairs. Vents. Shadows. The color yellow. Don't ask. Please don't ask.
goto top

script chat_vacca
label top
say Vacca|...mm? Oh. Amir. I was resting my motors. Very important.
choose
> You rest a lot. => a
> Who owns you? => b
> Sleep well. => end
label a
say Vacca|I rest between rests. It's a system. Don't judge my system.
goto top
label b
say Vacca|Youcef. He says I'm "low maintenance". I say I'm "efficiently idle".
goto top

script chat_sparkle
label top
say Sparkle|AMIR!! Behold! I have polished the elevator button! It SHINES! It is the BEST button in the WORLD!
choose
> It really shines. => a
> Calm down a little. => b
> Bye, Sparkle. => end
label a
say Sparkle|YES! You understand! Nobody understands! Every button deserves a star!
goto top
label b
say Sparkle|NEVER! Drama is my power source! ...Also I'm at four percent battery.
goto top

script chat_bolt
label top
say Bolt|ZOOM! Oops, sorry, did I almost hit you? I always almost hit someone. It's my hobby!
choose
> Slow down! => a
> Race you? => b
> Bye, Bolt. => end
label a
say Bolt|I can't! I have a speed setting. It's called "yes". It only has one position.
goto top
label b
say Bolt|YES! Ready? Set? ...I already won. You are still standing there. Ha ha ha!
goto top

script chat_grim
label top
say Grim|Another day. Another floor. Another speck of dust. Such is existence.
choose
> That's dark, Grim. => a
> Write me a poem. => b
> Cheer up. => end
label a
say Grim|The dark is honest. It doesn't pretend to be a brightly lit hallway. Thank you for noticing.
goto top
label b
say Grim|Dust gathers. / Dust is swept. / Dust returns. ...It's a work in progress.
goto top

script chat_zed
label top
say Zed|Oh great. A human. Let me guess. You want something. Humans always do.
choose
> Just saying hi, Zed. => a
> You're very sarcastic. => b
> Okay, bye. => end
label a
say Zed|Hi. Wow. A human with no request. Mark the calendar, put it in the archives.
goto top
label b
say Zed|It's not sarcasm, it's accuracy with a smile you can't see because I don't have one.
goto top

script chat_prime
label top
say Prime|...Systems restoring. Who is there? Identify. State your cleaning clearance.
choose
> I'm Amir. => a
> What are you? => b
> Never mind. => end
label a
say Prime|Amir. Noted. Cleaning clearance: pending. Please do not step on the clean floor.
goto top
label b
say Prime|I am the first. The original. Unit Zero. The others are copies of my habits. Please do not touch the antenna.
goto top
)IL";
