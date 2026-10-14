ILOT14 WORLD  v0.5.0  (Nintendo Switch homebrew, C++ / SDL2 / libnx)

CONTROLS
  Left stick / D-pad   walk (menus: move)
  A                    talk / use / confirm
  B                    back
  +                    pause menu (save, settings, quit to title)
  Y (after failing a minigame)  skip it
  X (in Save Slots)    delete a slot (press twice)

FILES
  main.cpp        game loop, menus, test bot
  engine.hpp      saves, story VM, world logic
  render.hpp      all drawing (world, scenes, blueprint menus)
  mini.hpp        minigames (roundup, timing, fight, catch, maze, roof)
  data.hpp        FLOORS, ROOMS and CHARACTERS  <- edit names / colors here
  script.hpp      script parser + validator
  story_core.hpp  doors + objects text
  story_chats_a/b idle chat with options for every character
  story_days_1..4  days 1-5, 6-12, 13-21, 22-31

WRITING STORY (inside the R"IL( ... )IL" blocks)
  script day_7          start a script (days are day_1 .. day_31)
  title Name            day title card
  say Name|Text         dialogue.   say |Text = narration.   Name@key picks a character (Adam@adam_l3)
  choose                then lines:  > Option text => label
  label x / goto x      jump around
  set flag [n] / add flag n / if flag label / ifnot flag label / ifge flag n label / ifday n label
  scene bg char1 char2  cutscene. bg: room outside sunset night backrooms roof workshop hornet shop inn elev garage void
  scene off             back to walking
  goal Text             top-left objective
  await talk KEY        wait until you talk to that character
  await door ROOMID     wait for a door (e.g. SECRET, M-002)
  await use OBJ         wait for an object
  await floor KEY       wait until you reach a floor (lethal main common unc rare special teen roof lobby
                        ulobby park1 park2 shaft ctrl vent bots inn)
  await items N         wait until you carry N items
  spawn item floor x    drop a pickup.  obj id floor x Label  = interactable.  npc key floor x = move a character
  mini roundup 5 45 | timing 5 3 Label | fight 8 5 hornets | catch 10 3 coins | maze 3 1 | roof 1
  lock floor / unlock floor   elevator access
  fx flash|shake|fadeout|fadein|black|clear     wait N   card A|B   endday
  Idle chat: script chat_KEY (or chat_KEY_d12 for a day-12 only version).

TEST ON PC (needs SDL2):
  g++ -std=c++17 -O1 main.cpp -o ilot14 $(sdl2-config --cflags --libs)
  ./ilot14 --check      # validates every script
  SDL_VIDEODRIVER=dummy ./ilot14 --bot --nodraw --fast   # auto-plays all 31 days

SAVES: sdmc:/switch/Ilot14/  (3 slots + settings)

WHAT'S NEW IN v0.3.0
- Chapters: Ch1 = days 1-15, Ch2 = days 16-31, Ch3 locked until Day 31 is finished.
- Cutscenes (bars, walking, emotes) in Chapters 1, 2 and 3.
- Real animated elevator (doors, floor numbers, buttons).
- Dialogue auto-advances when finished (Settings > Auto-advance).
- Touch works in MENUS only. Tapping in-game shows "PLAY WITH JOY-CONS".
- Menu shortcuts: L/R chapter jump (Day Select), X random / Y reset (Customize), key repeat on D-pad.
- Customize your look, bot owners, "YOUR BOT" = Bolt.
- Old saves carry over (a .bak copy is made of each old save).

v0.4.0
- Chapter 1 = 31 days, Chapter 2 = 35 days, Chapter 3 = 40 days. All in ONE save slot; finishing a chapter continues into the next.
- Chapter 2 unlocks after Ch1 Day 31, Chapter 3 after Ch2 Day 35.
- New minigames: Memory Pads (simon), Sneak, Rhythm, Dodge arena, Defend lanes. Harder each chapter.
- More cutscenes. Touch warning is small, top-right.
- Saves from v0.2/v0.3 carry over (.bak copy kept).

v0.5.0
- Chapter 4 preview, longer days (ch2 and ch3 much longer), Reghaia outside area:
  cable car -> El Madania cinema ("Do you love cinema ?"), Etusa bus -> school ("Teachers got yo back").
- Amir / Dalia / Gabriel rooms open. Tansaouti lives on the Special floor (S-003).
- Badges list, redeem codes (lore + custom endings), X = "say something", custom beef with IYKYK.
- New touch minigames: Whack, Pairs, Lights, Slide, Popcorn, Quiz. Timing / roundup removed.
- Local co-op: everyone picks a character in CO-OP (P1 = Amir, pads 2-4 / keyboard I J K L U O).
- All characters redesigned, more customization, new UI.
- Halloween prank: don't tell Gabriel numbers.
- v0.5.0 beef is with Adam and Amyas (reason left unknown).
- Canon update: Haydar (S-002), all NST/Tansaouti residents live on Special floor, Adam surnames, chapter 4 = "Never".
- Kids (Alicia 5, Abdullah 6, Jalil 4) talk like kids. Amir is tsundere toward Amyas and Adam B. Gabriel x Dalia dynamic.
- Logo intro (tap/A to skip). Extra deep floors removed; Chapter 3 now uses only the canon underground floors.
- Chapter 3 rebuilt (40 days, plain goals, no hidden elevator button). Chapter 4 'Never' is a 6-day BETA. All on canon floors.
