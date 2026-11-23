// story_illit.hpp - v0.8.0: a random day in Chapter 1, Adam Chermatti calls you GLLIT, then the ILLIT-style stage cutscene.
// Replay it any time after you have seen it: hold L and press R in free roam.
#pragma once
static const char* STORY_ILLIT = R"IL(
script illit_event
bars on
fx fadeout
wait 20
scene room amir adam_l7
cast amir 480
cast adam_l7 980
fx fadein
say |A knock on the door. Too loud to be Bolt. Too cheerful to be Dalia.
emote adam_l7 !
say Adam Chermatti@adam_l7|YO! GLLIT! There you are!
anim amir tilt
emote amir ?
say Amir|...What did you just call me?
say Adam Chermatti@adam_l7|GLLIT. It's a whole thing. Look at you, standing there like you're about to drop a comeback.
say Amir|My name is Amir. Five letters. I'm not a group.
say Adam Chermatti@adam_l7|Tell that to the TV.
anim adam_l7 point
say |The TV in the corner flickers on by itself. Nobody touched it. Nobody ever does.
fx flash
wait 25
illit
fx fadeout
wait 30
fx fadein
say Amir|...Why did I just watch that whole thing?
anim adam_l7 shrug
say Adam Chermatti@adam_l7|Watch what? I just wanted to borrow your charger.
say Amir|You called me the wrong name AND you want my charger.
say Adam Chermatti@adam_l7|...Yes?
say Amir|Take it. And never say that name again.
say Adam Chermatti@adam_l7|No promises, GLLIT.
emote amir !
bars off
scene off

script illit_replay
fx fadeout
wait 20
scene room amir
cast amir 640
fx fadein
say |The TV in the corner flickers on by itself. Again.
illit
fx fadeout
wait 30
scene off
fx fadein
)IL";
