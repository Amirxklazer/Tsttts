// Ilot14 World - Nintendo Switch homebrew (SDL2 + libnx). Also builds on PC for testing.
#include "story.hpp"
#include "render.hpp"
#ifdef __SWITCH__
#include <switch.h>
#endif

// ---------------------------------------------------------------- story loading
static void loadStory() {
    parseStory(STORY_CORE, "story_core");
    parseStory(STORY_CHATS_A, "story_chats_a");
    parseStory(STORY_CHATS_B, "story_chats_b");
    parseStory(STORY_DAYS_1, "story_days_1");
    parseStory(STORY_DAYS_2, "story_days_2");
    parseStory(STORY_DAYS_3, "story_days_3");
    parseStory(STORY_DAYS_4, "story_days_4");
    parseStory(STORY_CH3, "story_ch3");
    validateStory();
}

// ---------------------------------------------------------------- menus
static void setMsg(const std::string& m) { g.msg = m; g.msgT = 180; }

static void settingsInput(const Input& in, int back) {
    if (in.hit(B_UP)) g.sel = (g.sel + 3) % 4;
    if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 4;
    bool ch = false;
    int d = (in.hit(B_A) || in.hit(B_RIGHT) ? 1 : 0) - (in.hit(B_LEFT) ? 1 : 0);
    if (g.sel == 0 && d) { g.st.textSpeed = (g.st.textSpeed + d + 4) % 4; ch = true; }
    else if (g.sel == 1 && d) { g.st.autoAdv = (g.st.autoAdv + d + 4) % 4; ch = true; }
    else if (g.sel == 2 && d) { g.st.scanlines = !g.st.scanlines; G.scanlines = g.st.scanlines; ch = true; }
    else if (g.sel == 3 && in.hit(B_A)) { saveSettings(); g.mode = (Mode)back; g.sel = back == M_TITLE ? 6 : 4; return; }
    if (ch) saveSettings();
    if (in.hit(B_B)) { saveSettings(); g.mode = (Mode)back; g.sel = back == M_TITLE ? 6 : 4; }
}

static void enterPlayFromSlot(int s) {
    if (!readSlot(s)) { setMsg("That slot is empty."); return; }
    g.mode = M_PLAY;
    startDay(g.day);
}

static void updateMenus(const Input& in) {
    switch (g.mode) {
        case M_TITLE: {
            if (in.hit(B_UP)) g.sel = (g.sel + 7) % 8;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 8;
            if (in.hit(B_A)) {
                if (g.sel == 0) {
                    if (g.st.lastSlot > 0 && slotInfo(g.st.lastSlot).exists) enterPlayFromSlot(g.st.lastSlot);
                    else setMsg("No save yet - start a New Game.");
                } else if (g.sel == 1) { g.mode = M_NEWSLOT; g.sel = 0; g.quitConfirm = 0; }
                else if (g.sel == 2) { g.mode = M_SLOTS; g.sel = 0; g.quitConfirm = 0; }
                else if (g.sel == 3) { g.mode = M_DAYSEL; g.sel = std::max(0, g.st.maxDay - 1); if (g.slot < 1) g.slot = g.st.lastSlot > 0 ? g.st.lastSlot : 1; }
                else if (g.sel == 4) { g.mode = M_CHAPTERS; g.sel = 0; }
                else if (g.sel == 5) { g.mode = M_CUSTOM; g.custSel = 0; }
                else if (g.sel == 6) { g.mode = M_SETTINGS; g.sel = 0; }
                else g.quit = true;
            }
        } break;
        case M_CHAPTERS: {
            if (in.hit(B_UP)) g.sel = (g.sel + 2) % 3;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 3;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 4; }
            if (in.hit(B_A)) {
                if (g.sel == 0) { g.mode = M_NEWSLOT; g.sel = 0; g.quitConfirm = 0; }
                else if (g.sel == 1) {
                    if (g.st.maxDay < 16) setMsg("Locked. Reach Day 16 in Chapter 1 first.");
                    else { g.mode = M_DAYSEL; g.sel = 15; if (g.slot < 1) g.slot = g.st.lastSlot > 0 ? g.st.lastSlot : 1; }
                }
                else if (!g.st.ch3) setMsg("Locked. Finish Day 31 of Chapter 1 first.");
                else { g.mode = M_CHSLOT; g.sel = 0; g.quitConfirm = 0; }
            }
        } break;
        case M_CHSLOT: {
            if (in.hit(B_UP)) g.sel = (g.sel + 2) % 3;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 3;
            if (in.hit(B_B)) { g.mode = M_CHAPTERS; g.sel = 2; }
            if (in.hit(B_A)) {
                int sl = g.sel + 1;
                if (slotInfo(sl).exists && g.quitConfirm != sl) { g.quitConfirm = sl; setMsg("Slot used. Press A again to overwrite."); }
                else startChapter3(sl);
            }
        } break;
        case M_CUSTOM: case M_PCUSTOM: {
            g.custSpin++;
            int* f[] = {&APP.skin, &APP.hairStyle, &APP.hairCol, &APP.height, &APP.top, &APP.topCol, &APP.pants, &APP.acc, &APP.tag14};
            int mod[] = {8, 7, 8, 5, 4, 12, 8, 5, 2};
            if (in.hit(B_UP)) g.custSel = (g.custSel + 10) % 11;
            if (in.hit(B_DOWN)) g.custSel = (g.custSel + 1) % 11;
            bool back = in.hit(B_B);
            if (in.hit(B_Y)) { APP = Appear(); applyLook(); }
            if (in.hit(B_X)) { APP.skin = rand() % 8; APP.hairStyle = rand() % 7; APP.hairCol = rand() % 8; APP.height = rand() % 5; APP.top = rand() % 4; APP.topCol = rand() % 12; APP.pants = rand() % 8; APP.acc = rand() % 5; applyLook(); }
            if (g.custSel < 9) {
                int d = (in.hit(B_RIGHT) || in.hit(B_A) ? 1 : 0) - (in.hit(B_LEFT) ? 1 : 0);
                if (d) { *f[g.custSel] = (*f[g.custSel] + d + mod[g.custSel]) % mod[g.custSel]; applyLook(); }
            } else if (in.hit(B_A)) {
                if (g.custSel == 9) { APP = Appear(); applyLook(); } else back = true;
            }
            if (back) {
                saveSettings();
                if (g.mode == M_CUSTOM) { g.mode = M_TITLE; g.sel = 5; } else { g.mode = M_PAUSE; g.sel = 3; }
            }
        } break;
        case M_REG: {
            if (in.hit(B_UP)) g.regScroll--;
            if (in.hit(B_DOWN)) g.regScroll++;
            if (in.hit(B_L)) g.regScroll -= 6;
            if (in.hit(B_R)) g.regScroll += 6;
            if (in.drag != 0) g.regScroll -= (int)(in.drag / 28);
            if (in.hit(B_B) || in.hit(B_A)) { g.mode = M_PAUSE; g.sel = 2; }
        } break;
        case M_NEWSLOT: {
            if (in.hit(B_UP)) g.sel = (g.sel + 2) % 3;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 3;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 1; }
            if (in.hit(B_A)) {
                int s = g.sel + 1;
                if (slotInfo(s).exists && g.quitConfirm != s) { g.quitConfirm = s; setMsg("Slot used. Press A again to overwrite."); }
                else newGame(s);
            }
        } break;
        case M_SLOTS: {
            if (in.hit(B_UP)) g.sel = (g.sel + 2) % 3;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 3;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 2; }
            if (in.hit(B_A)) enterPlayFromSlot(g.sel + 1);
            if (in.hit(B_X)) {
                int s = g.sel + 1;
                if (!slotInfo(s).exists) break;
                if (g.quitConfirm != -s) { g.quitConfirm = -s; setMsg("Press X again to delete slot " + std::to_string(s)); }
                else { remove(slotPath(s).c_str()); g.quitConfirm = 0; setMsg("Slot deleted."); }
            }
        } break;
        case M_DAYSEL: {
            if (in.hit(B_LEFT)) g.sel = std::max(0, g.sel - 1);
            if (in.hit(B_RIGHT)) g.sel = std::min(30, g.sel + 1);
            if (in.hit(B_UP)) g.sel = std::max(0, g.sel - 8);
            if (in.hit(B_DOWN)) g.sel = std::min(30, g.sel + 8);
            if (in.hit(B_L)) g.sel = g.sel > 15 ? 15 : 0;
            if (in.hit(B_R)) g.sel = g.sel < 15 ? 15 : 30;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 3; }
            if (in.hit(B_A) && g.sel + 1 <= g.st.maxDay) startDayFromSelect(g.sel + 1);
        } break;
        case M_SETTINGS: settingsInput(in, M_TITLE); break;
        case M_PSET: settingsInput(in, M_PAUSE); break;
        case M_PAUSE: {
            if (in.hit(B_UP)) g.sel = (g.sel + 5) % 6;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 6;
            if (in.hit(B_B) || in.hit(B_PLUS)) { g.mode = M_PLAY; break; }
            if (in.hit(B_A)) {
                if (g.sel == 0) g.mode = M_PLAY;
                else if (g.sel == 1) { writeSlot(g.slot); setMsg("Saved to slot " + std::to_string(g.slot)); }
                else if (g.sel == 2) { g.mode = M_REG; g.regScroll = 0; }
                else if (g.sel == 3) { g.mode = M_PCUSTOM; g.custSel = 0; }
                else if (g.sel == 4) { g.mode = M_PSET; g.sel = 0; }
                else { g.mode = M_TITLE; g.sel = 0; if (g.mini) { delete g.mini; g.mini = nullptr; } g.stack.clear(); g.vs = V_NONE; }
            }
        } break;
        case M_ENDING: {
            g.cT++;
            if (g.cT > 120 && in.hit(B_A)) { g.mode = M_TITLE; g.sel = g.chapter == 1 ? 4 : 0; if (g.chapter == 1) setMsg("Chapter 3 unlocked! Open Chapters."); }
        } break;
        default: break;
    }
}

static void updatePlay(const Input& in) {
    if (in.hit(B_PLUS) && !g.elevOpen) { g.mode = M_PAUSE; g.sel = 0; return; }
    g.playFrames++;
    updateFades();
    updateNpcs();
    updateActors();
    if (g.vs == V_RUN) vmRun();
    if (g.vs == V_AWAIT || g.vs == V_NONE) { if (g.fadePhase == 0) updateWorld(in); }
    else updateVM(in);
}

static u32 tapInject = 0;
static void handleTaps(const Input& in) {
    for (auto& t : in.taps) {
        if (g.mode == M_PLAY) { g.touchWarn = 170; continue; }
        if (g.mode == M_ENDING) { tapInject |= B_A; continue; }
        const Hit* hit = nullptr;
        for (auto& h : HITS) if (t.first >= h.x && t.first <= h.x + h.w && t.second >= h.y && t.second <= h.y + h.h) hit = &h;
        if (!hit) continue;
        int& sel = (g.mode == M_CUSTOM || g.mode == M_PCUSTOM) ? g.custSel : g.sel;
        switch (hit->kind) {
            case 0: sel = hit->idx; tapInject |= B_A; break;
            case 1: break;
            case 2: tapInject |= B_B; break;
            case 3: sel = hit->idx; tapInject |= B_LEFT; break;
            case 4: sel = hit->idx; tapInject |= B_RIGHT; break;
        }
    }
}

static void update(const Input& in) {
    g.frame++;
    if (g.touchWarn > 0) g.touchWarn--;
    handleTaps(in);
    if (g.msgT > 0) g.msgT--;
    if (g.mode == M_PLAY) updatePlay(in);
    else updateMenus(in);
}

// ---------------------------------------------------------------- draw
static void drawPlay() {
    if (g.vs == V_MINI && g.mini) g.mini->draw();
    else if (g.vs == V_CARD) drawCardScreen(g.cTitle, g.cSub, g.cT, false);
    else if (g.vs == V_ENDDAY) drawCardScreen(g.cTitle, g.cSub, g.cT, true);
    else {
        if (g.elevOpen) drawElevatorScene();
        else {
            if (g.sceneOn) drawScene(); else drawWorld();
            drawFX();
            if (!g.barsOn || g.bars < 0.5f) drawHUD();
            drawDialog();
        }
    }
    if (g.fade > 0) rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, (int)(255 * std::min(1.0f, g.fade))));
    if (g.flash > 0) rect(0, 0, SCR_W, SCR_H, C(255, 255, 255, std::min(255, g.flash * 10)));
}

static void draw() {
    HITS.clear();
    g_backBtn = g.mode != M_TITLE && g.mode != M_PLAY && g.mode != M_ENDING;
    switch (g.mode) {
        case M_TITLE: g_hint = "D-pad Move    A Select"; break;
        case M_SLOTS: g_hint = "A Load    X Delete    B Back"; break;
        case M_DAYSEL: g_hint = "D-pad Move    L/R Chapter    A Play    B Back"; break;
        case M_CHAPTERS: g_hint = "A Open    B Back"; break;
        case M_CUSTOM: case M_PCUSTOM: g_hint = "Left/Right Change    X Random    Y Reset    B Done"; break;
        case M_SETTINGS: case M_PSET: g_hint = "Left/Right Change    B Back"; break;
        case M_REG: g_hint = "Up/Down Scroll    L/R Page    B Back"; break;
        case M_PAUSE: g_hint = "A Select    B Resume"; break;
        default: g_hint = "A Select    B Back"; break;
    }
    switch (g.mode) {
        case M_TITLE: drawTitleMenu(); break;
        case M_NEWSLOT: drawSlotList("NEW GAME", "Pick a slot for your save."); if (g.msgT > 0) text(g.msg, 110, 625, 1.4f, C(255, 220, 120)); break;
        case M_SLOTS: drawSlotList("SAVE SLOTS", "A: load    X: delete"); if (g.msgT > 0) text(g.msg, 110, 625, 1.4f, C(255, 220, 120)); break;
        case M_DAYSEL: drawDaySelect(); break;
        case M_SETTINGS: case M_PSET: drawSettings(); break;
        case M_PLAY: drawPlay(); break;
        case M_PAUSE: drawPlay(); drawPause(); break;
        case M_ENDING: drawEnding(); break;
        case M_CHAPTERS: drawChapters(); break;
        case M_CHSLOT: drawSlotList("CHAPTER 3", "Pick a slot for Chapter 3."); if (g.msgT > 0) text(g.msg, 110, 625, 1.4f, C(255, 220, 120)); break;
        case M_CUSTOM: case M_PCUSTOM: drawCustomize(); break;
        case M_REG: drawRegistry(); break;
    }
    scanlineOverlay();
    drawTouchWarn();
}

// ---------------------------------------------------------------- test bot / CLI
static bool BOT = false, NODRAW = false;
static std::string SHOT_DIR;
static std::set<long> SHOT_FRAMES;
static bool SHOT_DAYSTART = false;
static std::map<long, std::pair<float, float>> TAPS;
static std::map<long, std::pair<u32, int>> SEQ; // frame -> (button, length)
static long botFrames = 0;
static int botFromDay = 1, botToDay = 31;
static int lastBotDay = 0;
static bool botDone = false;
static long stuck = 0; static int stuckPc = -1; static std::string stuckName;

static void shot(const std::string& name) {
    if (SHOT_DIR.empty()) return;
    SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat(0, SCR_W, SCR_H, 32, SDL_PIXELFORMAT_ARGB8888);
    SDL_RenderReadPixels(G.ren, nullptr, SDL_PIXELFORMAT_ARGB8888, s->pixels, s->pitch);
    SDL_SaveBMP(s, (SHOT_DIR + "/" + name + ".bmp").c_str());
    SDL_FreeSurface(s);
}

static u32 btnFrom(const std::string& n) {
    if (n == "A") return B_A; if (n == "B") return B_B; if (n == "X") return B_X; if (n == "Y") return B_Y;
    if (n == "UP") return B_UP; if (n == "DOWN") return B_DOWN; if (n == "LEFT") return B_LEFT; if (n == "RIGHT") return B_RIGHT;
    if (n == "PLUS") return B_PLUS; return 0;
}

static void teleport(const std::string& fl, float x) { g.floorKey = fl; g.px = x; g.elevOpen = false; g.fadePhase = 0; g.fade = 0; }

static void botThink() {
    static int tick = 0; tick++;
    static int choiceTarget = -1;
    auto press = [&](u32 b) { if (tick % 6 < 3) G.inject |= b; };
    if (g.mode == M_ENDING) { press(B_A); if (g.cT > 130 && tick % 6 == 0) botDone = true; return; }
    if (g.mode != M_PLAY) { botDone = true; return; }
    if (g.day != lastBotDay) {
        lastBotDay = g.day;
        fprintf(stderr, "[bot] day %d start (frame %ld)\n", g.day, g.playFrames);
        if (g.day > botToDay) { botDone = true; return; }
    }
    if (g.vs != V_CHOOSE) choiceTarget = -1;
    switch (g.vs) {
        case V_SAY: case V_CARD: case V_ENDDAY: press(B_A); stuck = 0; break;
        case V_CHOOSE:
            if (choiceTarget < 0) choiceTarget = (int)(rnd() % g.dChoices.size());
            if (g.dSel < choiceTarget) press(B_DOWN); else press(B_A);
            break;
        case V_AWAIT: {
            if (g.stack.empty()) break;
            Frame& fr = g.stack.back();
            if (fr.pc >= (int)fr.b->cmds.size()) break;
            Cmd& c = fr.b->cmds[fr.pc];
            if (c.op != O_AWAIT) break;
            // stuck detection
            if (stuckPc == fr.pc && stuckName == fr.b->name) stuck++; else { stuckPc = fr.pc; stuckName = fr.b->name; stuck = 0; }
            std::string tf; float tx = 0; bool needA = true;
            if (c.a == "talk") { auto it = g.npcs.find(c.b); if (it != g.npcs.end()) { tf = it->second.floor; tx = it->second.x; } }
            else if (c.a == "door") {
                for (auto& f : FLOORS) for (size_t i = 0; i < f.rooms.size(); i++) if (f.rooms[i].id == c.b) { tf = f.key; tx = doorX(f, (int)i); }
            } else if (c.a == "use") {
                for (auto& o : g.objs) if (o.id == c.b) { tf = o.floor; tx = o.x; }
                for (auto& f : FLOORS) for (auto& o : builtinObjs(f.key)) if (o.id == c.b) { tf = o.floor; tx = o.x; }
            } else if (c.a == "items") {
                needA = false;
                if (!g.items.empty()) {
                    // nearest on current floor first
                    ItemSp* best = &g.items[0];
                    for (auto& it : g.items) if (it.floor == g.floorKey) { best = &it; break; }
                    tf = best->floor; tx = best->x;
                }
            } else if (c.a == "floor") { needA = false; tf = c.b; tx = 0; }
            if (tf.empty()) { fprintf(stderr, "[bot] cannot resolve await %s %s in %s\n", c.a.c_str(), c.b.c_str(), fr.b->name.c_str()); botDone = true; return; }
            if (stuck > 3500) {
                fprintf(stderr, "[bot] STUCK at await %s %s in %s -> teleport\n", c.a.c_str(), c.b.c_str(), fr.b->name.c_str());
                teleport(tf, tx > 0 ? tx : 300); stuck = 0; break;
            }
            if (g.elevOpen) {
                std::vector<int> l = elevList(); int want = -1;
                for (size_t i = 0; i < l.size(); i++) if (FLOORS[l[i]].key == tf) want = (int)i;
                if (want < 0) { g.elevOpen = false; fprintf(stderr, "[bot] floor %s not in elevator -> teleport\n", tf.c_str()); teleport(tf, tx > 0 ? tx : 300); break; }
                if (g.elevPhase == 2) { g.elevSel = want; press(B_A); }
                break;
            }
            if (g.fadePhase != 0) break;
            if (g.floorKey != tf) {
                FloorDef* f = floorBy(g.floorKey);
                if (!f || !f->inElevator) { teleport(tf, tx > 0 ? tx : 300); break; }
                float dx = f->elevX - g.px;
                if (fabsf(dx) > 20) G.inject |= (dx > 0 ? B_RIGHT : B_LEFT);
                else press(B_A);
                break;
            }
            float dx = tx - g.px;
            float stop = needA ? 30.0f : 12.0f;
            if (c.a == "floor") break;
            if (fabsf(dx) > stop) G.inject |= (dx > 0 ? B_RIGHT : B_LEFT);
            else if (needA) press(B_A);
        } break;
        default: break;
    }
}

static void applySeq() {
    for (auto& kv : SEQ) if (botFrames >= kv.first && botFrames < kv.first + kv.second.second) G.inject |= kv.second.first;
}

int main(int argc, char** argv) {
    long maxFrames = -1; bool check = false, ai = false, fast = false; int startDay0 = 0, startCh = 1;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() { return i + 1 < argc ? std::string(argv[++i]) : std::string(); };
        if (a == "--check") check = true;
        else if (a == "--bot") BOT = true;
        else if (a == "--ai") ai = true;
        else if (a == "--nodraw") NODRAW = true;
        else if (a == "--fast") fast = true;
        else if (a == "--from") botFromDay = atoi(next().c_str());
        else if (a == "--to") botToDay = atoi(next().c_str());
        else if (a == "--frames") maxFrames = atol(next().c_str());
        else if (a == "--shots") SHOT_DIR = next();
        else if (a == "--shot-at") { for (auto& s : splitStr(next(), ',')) SHOT_FRAMES.insert(atol(s.c_str())); }
        else if (a == "--shot-daystart") SHOT_DAYSTART = true;
        else if (a == "--tap") { for (auto& s : splitStr(next(), ',')) { auto p = splitStr(s, ':'); if (p.size() >= 3) TAPS[atol(p[0].c_str())] = {(float)atof(p[1].c_str()), (float)atof(p[2].c_str())}; } }
        else if (a == "--seq") { for (auto& s : splitStr(next(), ',')) { auto p = splitStr(s, ':'); if (p.size() >= 2) SEQ[atol(p[0].c_str())] = {btnFrom(p[1]), p.size() > 2 ? atoi(p[2].c_str()) : 3}; } }
        else if (a == "--seed") rngState = (u32)atol(next().c_str()) | 1;
        else if (a == "--day") startDay0 = atoi(next().c_str());
        else if (a == "--autowin") AUTOWIN = true;
        else if (a == "--ch") startCh = atoi(next().c_str());
    }
    buildData();
    loadStory();
    if (check) {
        int errs = 0;
        for (auto& e : STORY_ERRORS) { if (e.rfind("note:", 0) == 0) continue; fprintf(stderr, "%s\n", e.c_str()); errs++; }
        size_t cmds = 0; for (auto& kv : BLOCKS) cmds += kv.second.cmds.size();
        printf("scripts: %zu, commands: %zu, errors: %d\n", BLOCKS.size(), cmds, errs);
        return errs ? 1 : 0;
    }
    for (auto& e : STORY_ERRORS) if (e.rfind("note:", 0) != 0) fprintf(stderr, "STORY ERROR: %s\n", e.c_str());
    bool headless = BOT || getenv("SDL_VIDEODRIVER") != nullptr;
    if (!gfxInit(headless)) return 1;
    ensureDir();
    loadSettings();
    if (ai) TEST_AI = true;
    if (BOT && !ai) AUTOWIN = true;
    if (BOT || startDay0) {
        g.slot = 1;
        g.flags.clear(); setF("lock_roof", 1);
        g.mode = M_PLAY;
        if (startCh == 3) { g.st.ch3 = true; startChapter3(1); }
        else if (botFromDay > 1 || startDay0) {
            int d = startDay0 ? startDay0 : botFromDay;
            g.progressFlags.clear();
            g.st.maxDay = 31;
            startDayFromSelect(d);
        } else newGame(1);
    }
    Input in;
    int exitCode = 0;
#ifdef __SWITCH__
    while (appletMainLoop() && !g.quit && !in.quit) {
#else
    while (!g.quit && !in.quit) {
#endif
        Uint32 t0 = SDL_GetTicks();
        G.inject = tapInject; tapInject = 0;
        if (BOT) botThink();
        applySeq();
        botFrames++;
        { auto it = TAPS.find(botFrames); if (it != TAPS.end()) G.taps.push_back(it->second); }
        pollInput(in);
        update(in);
        bool wantShot = SHOT_FRAMES.count(botFrames) > 0;
        if (!NODRAW || wantShot) {
            SDL_SetRenderDrawColor(G.ren, 0, 0, 0, 255);
            SDL_RenderClear(G.ren);
            draw();
            if (wantShot) shot("f" + std::to_string(botFrames));
            SDL_RenderPresent(G.ren);
        }
        if (BOT && botDone) break;
        if (maxFrames > 0 && botFrames >= maxFrames) break;
        if (!headless) { /* vsync handles pacing */ }
        else if (!fast && !NODRAW) { Uint32 dt = SDL_GetTicks() - t0; if (dt < 16) SDL_Delay(16 - dt); }
    }
    saveSettings();
    if (BOT) fprintf(stderr, "[bot] finished at day %d, %ld frames, flags=%s\n", g.day, botFrames, flagsStr(g.flags).c_str());
    SDL_Quit();
    return exitCode;
}
