ILOT14 WORLD  v0.2.0  (Nintendo Switch homebrew, C++ / SDL2 / libnx)

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
