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
    parseStory(STORY_CH2A, "story_ch2a");
    parseStory(STORY_CH2B, "story_ch2b");
    parseStory(STORY_CH2C, "story_ch2c");
    parseStory(STORY_CH3, "story_ch3");
    parseStory(STORY_CH3B, "story_ch3b");
    parseStory(STORY_CH3C, "story_ch3c");
    parseStory(STORY_CH3D, "story_ch3d");
    parseStory(STORY_V5, "story_v5");
    parseStory(STORY_C3NEW, "story_c3new");
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
    else if (g.sel == 3 && in.hit(B_A)) { saveSettings(); g.mode = (Mode)back; g.sel = back == M_TITLE ? 8 : 4; return; }
    if (ch) saveSettings();
    if (in.hit(B_B)) { saveSettings(); g.mode = (Mode)back; g.sel = back == M_TITLE ? 8 : 4; }
}

static void enterPlayFromSlot(int s) {
    if (!readSlot(s)) { setMsg("That slot is empty."); return; }
    g.mode = M_PLAY;
    startDay(g.day);
}

static void updateMenus(const Input& in) {
    switch (g.mode) {
        case M_TITLE: {
            if (in.hit(B_UP)) g.sel = (g.sel + 9) % 10;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 10;
            if (in.hit(B_A)) {
                if (g.sel == 0) {
                    if (g.st.lastSlot > 0 && slotInfo(g.st.lastSlot).exists) enterPlayFromSlot(g.st.lastSlot);
                    else setMsg("No save yet - start a New Game.");
                } else if (g.sel == 1) { g.mode = M_NEWSLOT; g.sel = 0; g.quitConfirm = 0; }
                else if (g.sel == 2) { g.mode = M_SLOTS; g.sel = 0; g.quitConfirm = 0; }
                else if (g.sel == 3) {
                    g.mode = M_DAYSEL;
                    SlotInfo li = g.st.lastSlot > 0 ? slotInfo(g.st.lastSlot) : SlotInfo();
                    g.dsCh = li.exists && g.st.unl[li.chapter] ? li.chapter : 1;
                    g.sel = std::max(0, std::min(CH_LEN[g.dsCh] - 1, g.st.maxD[g.dsCh] - 1));
                    if (g.slot < 1) g.slot = g.st.lastSlot > 0 ? g.st.lastSlot : 1;
                }
                else if (g.sel == 4) { g.mode = M_CHAPTERS; g.sel = 0; }
                else if (g.sel == 5) { g.mode = M_COOP; g.sel = 3; }
                else if (g.sel == 6) { g.mode = M_CUSTOM; g.custSel = 0; }
                else if (g.sel == 7) { g.mode = M_EXTRAS; g.extSel = 0; }
                else if (g.sel == 8) { g.mode = M_SETTINGS; g.sel = 0; }
                else g.quit = true;
            }
        } break;
        case M_CHAPTERS: {
            if (in.hit(B_UP)) g.sel = (g.sel + 3) % 4;
            if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 4;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 4; }
            if (in.hit(B_A)) {
                int c = g.sel + 1;
                if (!g.st.unl[c]) setMsg(c == 2 ? "Locked. Finish Day 31 of Chapter 1 first." : c == 3 ? "Locked. Finish Day 35 of Chapter 2 first." : "Locked. Finish Day 40 of Chapter 3 first.");
                else {
                    g.mode = M_DAYSEL; g.dsCh = c; g.sel = std::max(0, std::min(CH_LEN[c] - 1, g.st.maxD[c] - 1));
                    if (g.slot < 1) g.slot = g.st.lastSlot > 0 ? g.st.lastSlot : 1;
                }
            }
        } break;
        case M_CUSTOM: case M_PCUSTOM: {
            g.custSpin++;
            int* f[] = {&APP.skin, &APP.hairStyle, &APP.hairCol, &APP.height, &APP.top, &APP.topCol, &APP.pants, &APP.shoes, &APP.eyes, &APP.acc, &APP.tag14};
            int mod[] = {8, 12, 12, 5, 9, 12, 8, 6, 4, 12, 2};
            if (in.hit(B_UP)) g.custSel = (g.custSel + 12) % 13;
            if (in.hit(B_DOWN)) g.custSel = (g.custSel + 1) % 13;
            bool back = in.hit(B_B);
            if (in.hit(B_Y)) { APP = Appear(); applyLook(); }
            if (in.hit(B_X)) { APP.skin = rand() % 8; APP.hairStyle = rand() % 12; APP.hairCol = rand() % 12; APP.height = rand() % 5; APP.top = rand() % 9; APP.topCol = rand() % 12; APP.pants = rand() % 8; APP.acc = rand() % 12; APP.shoes = rand() % 6; APP.eyes = rand() % 4; applyLook(); awardBadge("fashion"); }
            if (g.custSel < 11) {
                int d = (in.hit(B_RIGHT) || in.hit(B_A) ? 1 : 0) - (in.hit(B_LEFT) ? 1 : 0);
                if (d) { *f[g.custSel] = (*f[g.custSel] + d + mod[g.custSel]) % mod[g.custSel]; applyLook(); awardBadge("fashion"); }
            } else if (in.hit(B_A)) {
                if (g.custSel == 11) { APP = Appear(); applyLook(); } else back = true;
            }
            if (back) {
                saveSettings();
                if (g.mode == M_CUSTOM) { g.mode = M_TITLE; g.sel = 6; } else { g.mode = M_PAUSE; g.sel = 3; }
            }
        } break;
        case M_EXTRAS: {
            if (in.hit(B_UP)) g.extSel = (g.extSel + 2) % 3;
            if (in.hit(B_DOWN)) g.extSel = (g.extSel + 1) % 3;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 7; }
            if (in.hit(B_A)) {
                if (g.extSel == 0) { g.mode = M_REDEEM; g.kb = Kb(); g.redeemT = 0; }
                else if (g.extSel == 1) { g.mode = M_BADGES; g.badgeSel = 0; }
                else { g.mode = M_LORE; g.loreSel = 0; }
            }
        } break;
        case M_REDEEM: {
            if (g.redeemT > 0) g.redeemT--;
            g.kb.update(in);
            if (in.hit(B_B) && g.kb.text.empty()) { g.mode = M_EXTRAS; g.extSel = 0; break; }
            if (g.kb.done) {
                g.kb.done = false;
                std::string t = g.kb.text; for (auto& ch : t) ch = toupper(ch);
                while (!t.empty() && t.back() == ' ') t.pop_back();
                const CodeDef* hit = nullptr; for (int i = 0; i < NCODES; i++) if (t == CODE_LIST[i].code) hit = &CODE_LIST[i];
                if (!hit) g.redeemMsg = "That code doesn't work.";
                else if (U_LORE.count(hit->loreId)) g.redeemMsg = "Already redeemed.";
                else { unlockLore(hit->loreId); U_CODES.insert(hit->code); awardBadge("coder"); saveSettings(); g.redeemMsg = std::string("Unlocked: ") + LORE_LIST[loreIndex(hit->loreId)].title + "  (see Lore & Endings)"; }
                g.redeemT = 240; g.kb.text.clear();
            }
        } break;
        case M_BADGES: {
            if (in.hit(B_UP)) g.badgeSel = (g.badgeSel + NBADGES - 1) % NBADGES;
            if (in.hit(B_DOWN)) g.badgeSel = (g.badgeSel + 1) % NBADGES;
            if (in.hit(B_B)) { g.mode = M_EXTRAS; g.extSel = 1; }
        } break;
        case M_LORE: {
            int n = (int)loreEntries().size();
            if (n > 0) { if (in.hit(B_UP)) g.loreSel = (g.loreSel + n - 1) % n; if (in.hit(B_DOWN)) g.loreSel = (g.loreSel + 1) % n; }
            if (in.hit(B_B)) { g.mode = M_EXTRAS; g.extSel = 2; }
            if (in.hit(B_A) && n > 0) { g.mode = M_LOREVIEW; g.lorePage = 0; }
        } break;
        case M_LOREVIEW: {
            int pn = 1; { std::vector<std::string> es = loreEntries(); if (g.loreSel < (int)es.size()) pn = (int)pagesOf(LORE_LIST[loreIndex(es[g.loreSel])].pages).size(); }
            if (in.hit(B_A) || in.hit(B_RIGHT)) { if (g.lorePage + 1 < pn) g.lorePage++; else g.mode = M_LORE; }
            if (in.hit(B_LEFT) && g.lorePage > 0) g.lorePage--;
            if (in.hit(B_B)) g.mode = M_LORE;
        } break;
        case M_COOP: {
            std::vector<std::string> ls = coopList(); int N = (int)ls.size();
            if (in.hit(B_LEFT)) g.sel = (g.sel + 3) % 4;
            if (in.hit(B_RIGHT)) g.sel = (g.sel + 1) % 4;
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 5; }
            if (g.sel < 3) {
                if (in.hit(B_UP)) { g.coSel[g.sel] = (g.coSel[g.sel] + 1) % N; }
                if (in.hit(B_DOWN)) { g.coSel[g.sel] = (g.coSel[g.sel] + N - 1) % N; }
                if (in.hit(B_A)) { g.co[g.sel].on = !g.co[g.sel].on; if (g.co[g.sel].on) { g.co[g.sel].key = ls[g.coSel[g.sel] % N]; g.co[g.sel].floor.clear(); } }
            } else if (in.hit(B_A)) {
                bool any = false; for (int k = 0; k < 3; k++) if (g.co[k].on) any = true;
                if (!any) { setMsg("Nobody joined yet. Press A on another controller."); }
                else {
                    g.coopOn = true; G.coop = true; awardBadge("coop");
                    if (g.st.lastSlot > 0 && slotInfo(g.st.lastSlot).exists) enterPlayFromSlot(g.st.lastSlot); else newGame(1);
                }
            }
            // each other controller picks its own character
            for (int k = 0; k < 3; k++) {
                Input& ci = G.coIn[k];
                if (ci.hit(B_A)) { g.co[k].on = !g.co[k].on; if (g.co[k].on) { g.co[k].key = ls[g.coSel[k] % N]; g.co[k].floor.clear(); } }
                if (ci.hit(B_RIGHT) || ci.hit(B_LEFT)) { g.coSel[k] = (g.coSel[k] + (ci.hit(B_RIGHT) ? 1 : N - 1)) % N; if (g.co[k].on) g.co[k].key = ls[g.coSel[k] % N]; }
            }
            for (int k = 0; k < 3; k++) if (g.co[k].on) g.co[k].key = ls[g.coSel[k] % N];
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
            int len = CH_LEN[g.dsCh];
            if (in.hit(B_LEFT)) g.sel = std::max(0, g.sel - 1);
            if (in.hit(B_RIGHT)) g.sel = std::min(len - 1, g.sel + 1);
            if (in.hit(B_UP)) g.sel = std::max(0, g.sel - 8);
            if (in.hit(B_DOWN)) g.sel = std::min(len - 1, g.sel + 8);
            if (in.hit(B_L) && g.dsCh > 1) { g.dsCh--; g.sel = std::min(g.sel, CH_LEN[g.dsCh] - 1); }
            if (in.hit(B_R) && g.dsCh < 3 && g.st.unl[g.dsCh + 1]) { g.dsCh++; g.sel = std::min(g.sel, CH_LEN[g.dsCh] - 1); }
            if (in.hit(B_B)) { g.mode = M_TITLE; g.sel = 3; }
            if (in.hit(B_A)) {
                if (g.sel + 1 <= g.st.maxD[g.dsCh]) startDayFromSelect(g.dsCh, g.sel + 1);
                else setMsg("Not reached yet.");
            }
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
                else { g.coopOn = false; G.coop = false; g.mode = M_TITLE; g.sel = 0; if (g.mini) { delete g.mini; g.mini = nullptr; } g.stack.clear(); g.vs = V_NONE; }
            }
        } break;
        case M_ENDING: {
            g.cT++;
            if (g.cT > 120 && in.hit(B_A)) { g.mode = M_TITLE; g.sel = 0; if (g.endCh < 4) setMsg("Next chapter unlocked! Press Continue."); }
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
    if (!g.sceneOn && g.vs != V_MINI && !g.elevOpen) updateCoop();
    if (g.vs == V_RUN) vmRun();
    if (g.vs == V_AWAIT || g.vs == V_NONE) { if (g.fadePhase == 0) updateWorld(in); }
    else updateVM(in);
}

static u32 tapInject = 0;
static void handleTaps(const Input& in) {
    for (auto& t : in.taps) {
        if (g.mode == M_PLAY) {
            bool okTouch = (g.vs == V_MINI && g.mini && g.mini->touch) || g.vs == V_ASK;
            if (!okTouch) { g.touchWarn = 170; continue; }
            if (g.vs != V_ASK) continue;   // minis read taps themselves
        }
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
            case 6: if (g.mode == M_REDEEM || (g.mode == M_PLAY && g.vs == V_ASK)) { g.kb.r = hit->idx / 16; g.kb.c = hit->idx % 16; tapInject |= B_A; } break;
            case 5: if (g.mode == M_DAYSEL && g.st.unl[hit->idx]) { g.dsCh = hit->idx; g.sel = std::min(g.sel, CH_LEN[g.dsCh] - 1); } break;
        }
    }
}

static int introT = 0; static bool introOn = true;
static void update(const Input& in) {
    g.frame++;
    if (introOn) {
        introT++;
        bool skip = !in.taps.empty() || in.hit(B_A) || in.hit(B_B) || in.hit(B_PLUS) || in.hit(B_X) || in.hit(B_Y);
        if (skip && introT > 15) { introOn = false; }
        if (introT >= 270) introOn = false;
        return;
    }
    if (g.touchWarn > 0) g.touchWarn--;
    handleTaps(in);
    if (g.msgT > 0) g.msgT--;
    if (g.badgeToastT > 0) g.badgeToastT--;
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
    if (g.vs == V_ASK) drawAskOverlay();
    if (g.vs == V_SCARE) drawScare(g.scareT);
    if (g.fade > 0) rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, (int)(255 * std::min(1.0f, g.fade))));
    if (g.flash > 0) rect(0, 0, SCR_W, SCR_H, C(255, 255, 255, std::min(255, g.flash * 10)));
}

static void draw() {
    HITS.clear();
    if (introOn) { drawIntro(introT); return; }
    g_backBtn = g.mode != M_TITLE && g.mode != M_PLAY && g.mode != M_ENDING;
    switch (g.mode) {
        case M_TITLE: g_hint = "D-pad Move    A Select"; break;
        case M_SLOTS: g_hint = "A Load    X Delete    B Back"; break;
        case M_DAYSEL: g_hint = "D-pad Move    L/R Chapter    A Play    B Back"; break;
        case M_CHAPTERS: g_hint = "A Open    B Back"; break;
        case M_CUSTOM: case M_PCUSTOM: g_hint = "Left/Right Change    X Random    Y Reset    B Done"; break;
        case M_SETTINGS: case M_PSET: g_hint = "Left/Right Change    B Back"; break;
        case M_REG: g_hint = "Up/Down Scroll    L/R Page    B Back"; break;
        case M_EXTRAS: g_hint = "A Open    B Back"; break;
        case M_REDEEM: g_hint = "D-pad + A or tap keys    B Delete    + Send"; break;
        case M_BADGES: g_hint = "Up/Down Browse    B Back"; break;
        case M_LORE: g_hint = "Up/Down Browse    A Read    B Back"; break;
        case M_LOREVIEW: g_hint = "A Next page    B Back"; break;
        case M_COOP: g_hint = "Left/Right Move    A Join / Start    Up/Down Character    B Back"; break;
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
        case M_CUSTOM: case M_PCUSTOM: drawCustomize(); break;
        case M_REG: drawRegistry(); break;
        case M_EXTRAS: drawExtras(); break;
        case M_REDEEM: drawRedeem(); break;
        case M_BADGES: drawBadges(); break;
        case M_LORE: drawLore(); break;
        case M_LOREVIEW: drawLoreView(); break;
        case M_COOP: drawCoop(); if (g.msgT > 0) text(g.msg, 640, 626, 1.4f, C(255, 220, 120), 1); break;
    }
    scanlineOverlay();
    drawBadgeToast();
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
static int botFromDay = 1, botToDay = 99;
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
    if (g.vs == V_ASK) { g.kb.done = true; return; }
    if (g.vs == V_SCARE) { g.scareT = 999; return; }
    if (g.day != lastBotDay) {
        lastBotDay = g.day;
        fprintf(stderr, "[bot] day %d start (frame %ld)\n", g.day, g.playFrames);
        if (g.day > botToDay) { botDone = true; return; }
    }
    if (getenv("BOTDBG") && tick % 120 == 0) { auto it = g.npcs.find("anes"); fprintf(stderr, "[dbg] vs=%d floor=%s px=%.0f anes=%s/%.0f stuck=%d mode=%d fade=%d elev=%d\n", (int)g.vs, g.floorKey.c_str(), g.px, it != g.npcs.end() ? it->second.floor.c_str() : "?", it != g.npcs.end() ? it->second.x : -1.f, stuck, (int)g.mode, g.fadePhase, (int)g.elevOpen); }
    if (g.vs != V_CHOOSE) choiceTarget = -1;
    switch (g.vs) {
        case V_SAY: case V_CARD: case V_ENDDAY: press(B_A); break;
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
            if (c.a == "talk" && stuck > 300) tx += ((stuck / 300) % 3 - 1) * 55;   // a Cleaning bot may be blocking the prompt
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
    std::string miniArg; long maxFrames = -1; bool check = false, ai = false, fast = false; int startDay0 = 0, startCh = 1;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto next = [&]() { return i + 1 < argc ? std::string(argv[++i]) : std::string(); };
        if (a == "--check") check = true;
        else if (a == "--bot") BOT = true;
        else if (a == "--ai") ai = true;
        else if (a == "--nodraw") NODRAW = true;
        else if (a == "--nointro") introOn = false;
        else if (a == "--fast") fast = true;
        else if (a == "--from") botFromDay = atoi(next().c_str());
        else if (a == "--to") botToDay = atoi(next().c_str());
        else if (a == "--frames") maxFrames = atol(next().c_str());
        else if (a == "--shots") SHOT_DIR = next();
        else if (a == "--shot-at") { for (auto& s : splitStr(next(), ',')) SHOT_FRAMES.insert(atol(s.c_str())); }
        else if (a == "--shot-daystart") SHOT_DAYSTART = true;
        else if (a == "--mini") miniArg = next();
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
        if (startCh > 1 || botFromDay > 1 || startDay0) {
            int d = startDay0 ? startDay0 : botFromDay;
            if (startCh == 1) g.progressFlags.clear();
            for (int c = 1; c <= 3; c++) { g.st.unl[c] = true; g.st.maxD[c] = CH_LEN[c]; }
            startDayFromSelect(startCh, d);
        } else newGame(1);
    }
    if (!miniArg.empty()) {
        for (auto& c : miniArg) if (c == ',') c = ' ';
        g.mode = M_PLAY; g.mini = makeMini(words(miniArg)); g.vs = g.mini ? V_MINI : V_NONE;
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
        if (BOT) introOn = false;
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
        if (!miniArg.empty() && g.vs != V_MINI) { fprintf(stderr, "[mini] done after %ld frames won=%d\n", botFrames, F("won")); break; }
        if (maxFrames > 0 && botFrames >= maxFrames) break;
        if (!headless) { /* vsync handles pacing */ }
        else if (!fast && !NODRAW) { Uint32 dt = SDL_GetTicks() - t0; if (dt < 16) SDL_Delay(16 - dt); }
    }
    saveSettings();
    if (BOT) fprintf(stderr, "[bot] finished at day %d, %ld frames, flags=%s\n", g.day, botFrames, flagsStr(g.flags).c_str());
    SDL_Quit();
    return exitCode;
}
