// engine.hpp - game state, saves, script VM, world logic
#pragma once
#include "script.hpp"
#include "extras.hpp"
#include <list>

#define VERSION "v0.5.0"

struct Settings { int textSpeed = 1; int autoAdv = 2; bool scanlines = true; int lastSlot = 0; int maxD[5] = {0, 1, 0, 0, 0}; bool unl[5] = {true, true, false, false, false}; };
struct Npc { std::string floor; float baseX = 0, x = 0; bool visible = true; float phase = 0; int dir = 1; bool still = false; float goal = -1, spd = 4; };
struct Actor { std::string key; float x = 640, tx = 640, spd = 4; int dir = 1, anim = 0, animT = 0, emoteT = 0; std::string animName, emote; bool walking = false; };
struct Particle { float x, y, vx, vy; int life, maxlife; Col c; int type; };
struct ItemSp { std::string key, floor; float x; };
struct ObjSp { std::string id, floor, label; float x; };
struct Toast { std::string t; int life; };

enum VS { V_NONE, V_RUN, V_SAY, V_CHOOSE, V_AWAIT, V_MINI, V_CARD, V_WAIT, V_ENDDAY, V_ASK, V_SCARE };
enum Mode { M_TITLE, M_NEWSLOT, M_SLOTS, M_DAYSEL, M_SETTINGS, M_PLAY, M_PAUSE, M_PSET, M_ENDING, M_CHAPTERS, M_CHSLOT, M_CUSTOM, M_PCUSTOM, M_REG, M_EXTRAS, M_REDEEM, M_BADGES, M_LORE, M_LOREVIEW, M_COOP };
struct Frame { Block* b; int pc; };
struct CoPlayer { bool on = false; std::string key, em; float x = 400; int dir = 1, walk = 0, pad = 1, emoteT = 0; bool moving = false; std::string floor; };

struct Game {
    Settings st;
    Mode mode = M_TITLE;
    int sel = 0, sel2 = 0, frame = 0;
    bool quit = false;
    std::string msg; int msgT = 0;
    // slot state
    int slot = 1, day = 1, chapter = 1;
    std::map<std::string, int> flags, dayFlags;
    long playFrames = 0;
    std::map<int, std::string> progressFlags;
    // world
    std::string floorKey = "lethal";
    float px = 500; int pdir = 1, walk = 0; bool moving = false;
    std::vector<std::string> inv;
    std::map<std::string, Npc> npcs;
    std::vector<ItemSp> items;
    std::vector<ObjSp> objs;
    std::vector<Toast> toasts;
    std::string goal;
    int banner = 0; std::string bannerText;
    bool elevOpen = false; int elevSel = 0;
    int elevPhase = 0, elevT = 0, elevFrom = 0, elevTo = 0, elevCur = 0; float elevDoor = 1; std::vector<int> elevPath;
    int dWait = 0, touchWarn = 0;
    // vm
    std::vector<Frame> stack;
    VS vs = V_NONE;
    std::string dWho, dKey; std::vector<std::string> dPages; int dPage = 0; float dShown = 0;
    std::vector<std::string> dChoices, dTargets; int dSel = 0;
    std::string cTitle, cSub; int cT = 0, waitT = 0;
    Mini* mini = nullptr;
    bool sceneOn = false; std::string sceneBg; std::vector<std::string> sceneChars;
    std::vector<Actor> actors; std::vector<Particle> parts;
    float bars = 0; bool barsOn = false; bool rain = false; int fwT = 0, flickerT = 0, beesT = 0; float dark = 0;
    std::string focusKey; float pgoal = -1, pspd = 4;
    int regScroll = 0, custSel = 0, custSpin = 0, dsCh = 1, endCh = 1;
    // fx
    int flash = 0, shake = 0; float fade = 0, fadeTarget = 0;
    int fadePhase = 0; std::string pendingFloor;
    int quitConfirm = 0;
    // extras
    Kb kb; std::string askText, askPrompt; int scareT = 0;
    int extSel = 0, loreSel = 0, lorePage = 0, badgeSel = 0, redeemT = 0; std::string redeemMsg;
    CoPlayer co[3]; int coSel[3] = {0, 0, 0}; int coStage = 0; bool coopOn = false;
    int badgeToastT = 0; std::string badgeToast;
} g;

static bool AUTOWIN = false;
static std::list<Block> TMPBLOCKS;

static int F(const std::string& k) { auto it = g.flags.find(k); return it == g.flags.end() ? 0 : it->second; }
static void setF(const std::string& k, int v) { g.flags[k] = v; }

static void toast(const std::string& t) {
    g.toasts.push_back({t, 170});
    if (g.toasts.size() > 4) g.toasts.erase(g.toasts.begin());
}

static void saveSettings();
static void awardBadge(const std::string& id) {
    if (U_BADGES.count(id)) return;
    for (int i = 0; i < NBADGES; i++) if (id == BADGE_LIST[i].id) {
        U_BADGES.insert(id);
        g.badgeToast = BADGE_LIST[i].name; g.badgeToastT = 260;
        saveSettings();
        return;
    }
}
static bool unlockLore(const std::string& id) {
    if (U_LORE.count(id) || loreIndex(id) < 0) return false;
    U_LORE.insert(id);
    if (U_LORE.size() >= 5) awardBadge("collector");
    return true;
}

// ------------------------------------------------------------ saves
static std::string flagsStr(const std::map<std::string, int>& m) {
    std::string s;
    for (auto& kv : m) { if (kv.second == 0) continue; if (!s.empty()) s += ","; s += kv.first + ":" + std::to_string(kv.second); }
    return s;
}
static void parseFlags(const std::string& s, std::map<std::string, int>& m) {
    m.clear();
    for (auto& p : splitStr(s, ',')) {
        size_t c = p.find(':');
        if (c == std::string::npos) continue;
        m[p.substr(0, c)] = atoi(p.c_str() + c + 1);
    }
}
static std::string slotPath(int s) { return std::string(SAVE_DIR) + "save" + std::to_string(s) + ".dat"; }

struct SlotInfo { bool exists = false; int day = 1, chapter = 1; long frames = 0; };
static std::map<std::string, std::string> parseKV(const std::string& txt) {
    std::map<std::string, std::string> kv;
    for (auto& l : splitStr(txt, '\n')) {
        size_t e = l.find('=');
        if (e == std::string::npos) continue;
        kv[trim(l.substr(0, e))] = trim(l.substr(e + 1));
    }
    return kv;
}
static SlotInfo slotInfo(int s) {
    SlotInfo si;
    std::string t = readFile(slotPath(s));
    if (t.empty()) return si;
    auto kv = parseKV(t);
    si.exists = kv.count("day") > 0;
    si.day = atoi(kv["day"].c_str());
    si.chapter = kv.count("chapter") ? std::max(1, atoi(kv["chapter"].c_str())) : 1;
    si.frames = atol(kv["frames"].c_str());
    return si;
}
static std::string appearStr() {
    char b[96];
    snprintf(b, sizeof b, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", APP.skin, APP.hairStyle, APP.hairCol, APP.height, APP.top, APP.topCol, APP.pants, APP.acc, APP.tag14, APP.shoes, APP.eyes);
    return b;
}
static void applyLook() { CharDef* c = charBy("amir"); if (c) c->look = lookFromAppear(APP); }
static void saveSettings() {
    ensureDir();
    std::string s = "textspeed=" + std::to_string(g.st.textSpeed) + "\nscanlines=" + std::to_string(g.st.scanlines ? 1 : 0) +
                    "\nlastslot=" + std::to_string(g.st.lastSlot) + "\nmaxday=" + std::to_string(g.st.maxD[1]) +
                    "\nmax2=" + std::to_string(g.st.maxD[2]) + "\nmax3=" + std::to_string(g.st.maxD[3]) +
                    "\nunl2=" + std::to_string(g.st.unl[2] ? 1 : 0) + "\nunl3=" + std::to_string(g.st.unl[3] ? 1 : 0) +
                    "\nmax4=" + std::to_string(g.st.maxD[4]) + "\nunl4=" + std::to_string(g.st.unl[4] ? 1 : 0) +
                    "\nbadges=" + joinSet(U_BADGES) + "\nlore=" + joinSet(U_LORE) + "\ncodes=" + joinSet(U_CODES) +
                    "\nauto=" + std::to_string(g.st.autoAdv) + "\nlook=" + appearStr() + "\n";
    writeFile(std::string(SAVE_DIR) + "settings.cfg", s);
}
static void saveProgress() {
    ensureDir();
    std::string s;
    for (auto& kv : g.progressFlags) s += "d" + std::to_string(kv.first) + "=" + kv.second + "\n";
    writeFile(std::string(SAVE_DIR) + "progress.dat", s);
}
static void loadSettings() {
    auto kv = parseKV(readFile(std::string(SAVE_DIR) + "settings.cfg"));
    if (kv.count("textspeed")) g.st.textSpeed = std::max(0, std::min(3, atoi(kv["textspeed"].c_str())));
    if (kv.count("scanlines")) g.st.scanlines = atoi(kv["scanlines"].c_str()) != 0;
    if (kv.count("lastslot")) g.st.lastSlot = atoi(kv["lastslot"].c_str());
    if (kv.count("maxday")) g.st.maxD[1] = std::max(1, std::min(31, atoi(kv["maxday"].c_str())));
    if (kv.count("max2")) g.st.maxD[2] = std::max(0, std::min(35, atoi(kv["max2"].c_str())));
    if (kv.count("max3")) g.st.maxD[3] = std::max(0, std::min(40, atoi(kv["max3"].c_str())));
    if (kv.count("unl2")) g.st.unl[2] = atoi(kv["unl2"].c_str()) != 0;
    else if (kv.count("ch3")) g.st.unl[2] = atoi(kv["ch3"].c_str()) != 0;   // v0.3.0 settings: "ch3" meant "finished Day 31"
    if (kv.count("unl3")) g.st.unl[3] = atoi(kv["unl3"].c_str()) != 0;
    if (kv.count("max4")) g.st.maxD[4] = std::max(0, std::min(CH_LEN[4], atoi(kv["max4"].c_str())));
    if (kv.count("unl4")) g.st.unl[4] = atoi(kv["unl4"].c_str()) != 0;
    if (kv.count("badges")) splitInto(kv["badges"], U_BADGES);
    if (kv.count("lore")) splitInto(kv["lore"], U_LORE);
    if (kv.count("codes")) splitInto(kv["codes"], U_CODES);
    if (g.st.unl[4] && g.st.maxD[4] < 1) g.st.maxD[4] = 1;
    if (g.st.unl[2] && g.st.maxD[2] < 1) g.st.maxD[2] = 1;
    if (g.st.unl[3] && g.st.maxD[3] < 1) g.st.maxD[3] = 1;
    if (kv.count("auto")) g.st.autoAdv = std::max(0, std::min(3, atoi(kv["auto"].c_str())));
    if (kv.count("look")) {
        std::vector<std::string> p = splitStr(kv["look"], ',');
        int* f[] = {&APP.skin, &APP.hairStyle, &APP.hairCol, &APP.height, &APP.top, &APP.topCol, &APP.pants, &APP.acc, &APP.tag14, &APP.shoes, &APP.eyes};
        for (size_t i = 0; i < p.size() && i < 11; i++) *f[i] = std::max(0, atoi(p[i].c_str()));
        APP.skin %= 8; APP.hairStyle %= 12; APP.hairCol %= 12; APP.height %= 5; APP.top %= 9; APP.topCol %= 12; APP.pants %= 8; APP.acc %= 12; APP.tag14 %= 2; APP.shoes %= 6; APP.eyes %= 4;
    }
    applyLook();
    G.scanlines = g.st.scanlines;
    auto pr = parseKV(readFile(std::string(SAVE_DIR) + "progress.dat"));
    for (auto& kv2 : pr) if (kv2.first.size() > 1 && kv2.first[0] == 'd') g.progressFlags[atoi(kv2.first.c_str() + 1)] = kv2.second;
}
static void writeSlot(int s) {
    ensureDir();
    std::string t = "v=3\nchapter=" + std::to_string(g.chapter) + "\nday=" + std::to_string(g.day) + "\nframes=" + std::to_string(g.playFrames) + "\nflags=" + flagsStr(g.dayFlags) + "\n";
    writeFile(slotPath(s), t);
    g.st.lastSlot = s;
    saveSettings();
}
static bool readSlot(int s) {
    std::string raw = readFile(slotPath(s));
    auto kv = parseKV(raw);
    if (!kv.count("day")) return false;
    // older save (v0.2.0 or older): keep a backup copy once, then it is upgraded on the next save
    int ver = kv.count("v") ? atoi(kv["v"].c_str()) : 1;
    if (ver < 3) {
        std::string bak = std::string(SAVE_DIR) + "save" + std::to_string(s) + ".v" + std::to_string(ver) + ".bak";
        if (readFile(bak).empty()) writeFile(bak, raw);
    }
    g.slot = s;
    g.chapter = kv.count("chapter") ? std::max(1, std::min(4, atoi(kv["chapter"].c_str()))) : 1;
    g.day = std::max(1, std::min(CH_LEN[g.chapter], atoi(kv["day"].c_str())));
    g.playFrames = atol(kv["frames"].c_str());
    parseFlags(kv["flags"], g.flags);
    return true;
}

// ------------------------------------------------------------ world helpers
static float doorX(const FloorDef& f, int i) { return f.roomX(i) + 70; }

static void resetNpcs() {
    g.npcs.clear();
    std::map<std::string, int> botIdx;
    int bi = 0;
    for (auto& c : CHARS) {
        if (c.key == "amir") continue;
        Npc n; n.floor = c.floor; n.visible = true; n.phase = (float)(rnd() % 628) / 100.0f;
        FloorDef* f = floorBy(c.floor);
        n.baseX = 600;
        if (f) {
            bool found = false;
            for (size_t i = 0; i < f->rooms.size(); i++) if (f->rooms[i].key == c.key) { n.baseX = doorX(*f, (int)i); found = true; }
            if (!found && c.isBot) {
                if (c.key.rfind("bot_", 0) == 0) {
                    // roaming bot of a resident: wander near the owner's door
                    std::string ok = c.key.substr(4); n.baseX = 700;
                    for (size_t i = 0; i < f->rooms.size(); i++) if (f->rooms[i].key == ok) n.baseX = doorX(*f, (int)i) + 120;
                } else { n.baseX = 620 + bi * 230; bi++; }
            }
        }
        if (c.key == "amine" || c.key == "prime") n.visible = false;
        if (c.key == "bolt" && false) n.visible = false;
        n.x = n.baseX;
        g.npcs[c.key] = n;
    }
}

static void resetWorld() {
    resetNpcs();
    g.items.clear(); g.objs.clear(); g.inv.clear(); g.toasts.clear(); g.goal.clear();
    g.sceneOn = false; g.elevOpen = false; g.flash = g.shake = 0; g.fade = 0; g.fadeTarget = 0; g.fadePhase = 0;
    g.actors.clear(); g.parts.clear(); g.bars = 0; g.barsOn = false; g.rain = false; g.fwT = 0; g.flickerT = 0; g.beesT = 0; g.dark = 0;
    g.focusKey.clear(); g.pgoal = -1;
    g.floorKey = "lethal";
    FloorDef* f = floorBy("lethal");
    g.px = doorX(*f, 0) + 120;
    g.pdir = 1; g.banner = 0;
    TMPBLOCKS.clear();
}

// ------------------------------------------------------------ VM
static Block* findBlock(const std::string& n) { auto it = BLOCKS.find(n); return it == BLOCKS.end() ? nullptr : &it->second; }

static void vmPush(const std::string& name) {
    Block* b = findBlock(name);
    if (!b) { fprintf(stderr, "missing script %s\n", name.c_str()); return; }
    g.stack.push_back({b, 0});
    g.vs = V_RUN;
}
static void pushSay(const std::string& who, const std::string& text) {
    TMPBLOCKS.emplace_back();
    Block& b = TMPBLOCKS.back();
    Cmd c; c.op = O_SAY; c.a = who; c.b = text;
    b.cmds.push_back(c);
    g.stack.push_back({&b, 0});
    g.vs = V_RUN;
}

static void startSay(const std::string& who, const std::string& text) {
    size_t at = who.find('@');
    if (at != std::string::npos) { g.dWho = who.substr(0, at); g.dKey = who.substr(at + 1); }
    else { g.dWho = who; g.dKey.clear(); }
    std::vector<std::string> lines = wrapText(text, 68);
    g.dPages.clear();
    for (size_t i = 0; i < lines.size(); i += 3) {
        std::string p;
        for (size_t k = i; k < std::min(lines.size(), i + 3); k++) { if (k > i) p += "\n"; p += lines[k]; }
        g.dPages.push_back(p);
    }
    g.dPage = 0; g.dShown = 0; g.dWait = 0;
    g.vs = V_SAY;
}

static bool awaitOk(const Cmd& c) {
    if (c.a == "floor") return g.floorKey == c.b;
    if (c.a == "items") return (int)g.inv.size() >= c.n;
    return false;
}

static void vmGoto(const std::string& label) {
    if (g.stack.empty()) return;
    Frame& f = g.stack.back();
    if (label == "end") { g.stack.pop_back(); return; }
    auto it = f.b->labels.find(label);
    if (it == f.b->labels.end()) { fprintf(stderr, "bad label %s in %s\n", label.c_str(), f.b->name.c_str()); g.stack.pop_back(); return; }
    f.pc = it->second;
}

static void startDay(int d);

static Actor* actorBy(const std::string& k) { for (auto& a : g.actors) if (a.key == k) return &a; return nullptr; }
static float defaultStageX(size_t i, size_t n) { return n == 1 ? 640.0f : n == 2 ? (i == 0 ? 420.0f : 860.0f) : (280.0f + i * 360.0f); }
static Actor& ensureActor(const std::string& k) {
    Actor* a = actorBy(k);
    if (a) return *a;
    Actor n; n.key = k; g.actors.push_back(n); return g.actors.back();
}
static void spawnBurst(float x, float y, int n, Col c, int type = 0) {
    for (int i = 0; i < n; i++) {
        float a = rndf() * 6.2832f, sp = 1.5f + rndf() * 5.0f;
        g.parts.push_back({x, y, cosf(a) * sp, sinf(a) * sp, 50 + (int)(rnd() % 40), 90, c, type});
    }
}
static bool anyWalking() {
    for (auto& a : g.actors) if (a.walking) return true;
    for (auto& kv : g.npcs) if (kv.second.goal >= 0) return true;
    return g.pgoal >= 0;
}
static std::string blockName(int d) { return (g.chapter == 1 ? "day_" : g.chapter == 2 ? "c2_" : g.chapter == 3 ? "c3_" : "c4_") + std::to_string(d); }
static int lastDay() { return CH_LEN[g.chapter]; }
static std::string dayTitle(int d) { return dayTitleOf(g.chapter, d); }

static void vmRun() {
    int guard = 0;
    while (g.vs == V_RUN) {
        if (++guard > 20000) { fprintf(stderr, "vm loop guard hit\n"); g.vs = V_NONE; return; }
        if (g.stack.empty()) { g.vs = V_NONE; return; }
        Frame& f = g.stack.back();
        if (f.pc >= (int)f.b->cmds.size()) { g.stack.pop_back(); continue; }
        Cmd& c = f.b->cmds[f.pc];
        if (getenv("BOTTRACE")) fprintf(stderr, "[vm] %s:%d op=%d line=%d a=%.30s\n", f.b->name.c_str(), f.pc, (int)c.op, c.line, c.a.c_str());
        switch (c.op) {
            case O_SAY: f.pc++; startSay(c.a, c.b); return;
            case O_CHOOSE:
                g.dChoices.clear(); g.dTargets.clear();
                for (auto& o : c.opts) { g.dChoices.push_back(o.first); g.dTargets.push_back(o.second); }
                g.dSel = 0; g.vs = V_CHOOSE; return;
            case O_GOTO: vmGoto(c.a); break;
            case O_SET: setF(c.a, c.n); f.pc++; break;
            case O_ADD: setF(c.a, F(c.a) + c.n); f.pc++; break;
            case O_IF: if (F(c.a) != 0) vmGoto(c.b); else f.pc++; break;
            case O_IFNOT: if (F(c.a) == 0) vmGoto(c.b); else f.pc++; break;
            case O_IFGE: if (F(c.a) >= c.n) vmGoto(c.b); else f.pc++; break;
            case O_IFDAY: if (g.day >= c.n) vmGoto(c.b); else f.pc++; break;
            case O_MINI: {
                f.pc++;
                std::vector<std::string> w = words(c.a);
                Mini* m = makeMini(w);
                if (!m) { setF("won", 1); break; }
                if (AUTOWIN) { delete m; setF("won", 1); setF("skipped", 0); break; }
                g.mini = m; g.vs = V_MINI; return;
            }
            case O_CARD: f.pc++; g.cTitle = c.a; g.cSub = c.b; g.cT = 0; g.vs = V_CARD; return;
            case O_TITLE: f.pc++; g.cTitle = (g.chapter > 1 ? "CHAPTER " + std::to_string(g.chapter) + " - DAY " : std::string("DAY ")) + std::to_string(g.day); g.cSub = c.a; g.cT = 0; g.vs = V_CARD; return;
            case O_SCENE: {
                f.pc++;
                std::vector<std::string> w = words(c.a);
                if (w.empty() || w[0] == "off") { g.sceneOn = false; g.actors.clear(); g.barsOn = false; g.rain = false; g.fwT = 0; g.beesT = 0; g.parts.clear(); }
                else {
                    g.sceneOn = true; g.sceneBg = w[0]; g.sceneChars.assign(w.begin() + 1, w.end());
                    g.actors.clear();
                    for (size_t i = 0; i < g.sceneChars.size(); i++) {
                        Actor a; a.key = g.sceneChars[i]; a.x = a.tx = defaultStageX(i, g.sceneChars.size());
                        a.dir = (i == 0 || (g.sceneChars.size() == 3 && i == 1)) ? 1 : -1;
                        g.actors.push_back(a);
                    }
                }
            } break;
            case O_GOAL: g.goal = c.a; f.pc++; break;
            case O_AWAIT:
                g.sceneOn = false;
                if (awaitOk(c)) { f.pc++; break; }
                g.vs = V_AWAIT; return;
            case O_SPAWN: g.items.push_back({c.a, c.b, (float)c.n}); f.pc++; break;
            case O_CLEARITEMS: g.items.clear(); g.inv.clear(); f.pc++; break;
            case O_WARP: {
                FloorDef* fl = floorBy(c.a);
                g.floorKey = c.a;
                g.px = c.n >= 0 ? (float)c.n : (fl ? fl->elevX + 90 : 300);
                f.pc++;
            } break;
            case O_BADGE: awardBadge(c.a); f.pc++; break;
            case O_ENDING: { if (unlockLore(c.a)) { int li = loreIndex(c.a); toast(std::string("Unlocked: ") + (li >= 0 ? LORE_LIST[li].title : c.a.c_str())); } f.pc++; } break;
            case O_ASK: f.pc++; if (AUTOWIN) { g.askText.clear(); break; } g.askPrompt = c.a; g.kb = Kb(); g.askText.clear(); g.vs = V_ASK; return;
            case O_IFSAY: if (g.askText.find(c.a) != std::string::npos) vmGoto(c.b); else f.pc++; break;
            case O_SCARE: f.pc++; if (AUTOWIN) break; awardBadge("haunted"); unlockLore("e_scare"); g.scareT = 0; g.vs = V_SCARE; return;
            case O_STAY: f.pc++; break;
            case O_ENDDAY:
                f.pc++;
                g.cTitle = "END OF DAY " + std::to_string(g.day);
                g.cSub = dayTitle(g.day);
                g.cT = 0; g.vs = V_ENDDAY; return;
            case O_RUN: {
                f.pc++;
                Block* nb = findBlock(c.a);
                if (nb) g.stack.push_back({nb, 0});
            } break;
            case O_END: g.stack.pop_back(); break;
            case O_NPC: {
                f.pc++;
                auto it = g.npcs.find(c.a);
                if (it == g.npcs.end()) break;
                Npc& n = it->second;
                if (c.b == "hide") n.visible = false;
                else if (c.b == "show") n.visible = true;
                else if (c.b == "reset") { resetNpcs(); }
                else { n.floor = c.b; if (c.n >= 0) n.baseX = (float)c.n; n.visible = true; n.x = n.baseX; }
            } break;
            case O_OBJ: {
                f.pc++;
                for (size_t i = 0; i < g.objs.size(); i++) if (g.objs[i].id == c.a) { g.objs.erase(g.objs.begin() + i); break; }
                g.objs.push_back({c.a, c.b, c.c, (float)c.n});
            } break;
            case O_DELOBJ: {
                f.pc++;
                for (size_t i = 0; i < g.objs.size(); i++) if (g.objs[i].id == c.a) { g.objs.erase(g.objs.begin() + i); break; }
            } break;
            case O_FX: {
                f.pc++;
                if (c.a == "flash") g.flash = 28;
                else if (c.a == "shake") g.shake = 40;
                else if (c.a == "fadeout") g.fadeTarget = 1;
                else if (c.a == "fadein") g.fadeTarget = 0;
                else if (c.a == "black") { g.fade = 1; g.fadeTarget = 1; }
                else if (c.a == "clear") { g.fade = 0; g.fadeTarget = 0; }
                else if (c.a == "rain") g.rain = true;
                else if (c.a == "rainoff") g.rain = false;
                else if (c.a == "fireworks") g.fwT = 420;
                else if (c.a == "confetti") { for (int i = 0; i < 160; i++) g.parts.push_back({rndf() * 1280, -rndf() * 300, (rndf() - 0.5f) * 2, 2 + rndf() * 3, 260, 260, C(rndi(80, 255), rndi(80, 255), rndi(80, 255)), 1}); }
                else if (c.a == "lightning") { g.flash = 20; g.shake = 22; }
                else if (c.a == "flicker") g.flickerT = 100;
                else if (c.a == "dark") g.dark = 0.82f;
                else if (c.a == "lights") g.dark = 0;
                else if (c.a == "hornets") g.beesT = 600;
                else if (c.a == "beesoff") g.beesT = 0;
                else if (c.a == "burst") spawnBurst(640, 300, 70, ORANGE, 2);
            } break;
            case O_WAIT: f.pc++; g.waitT = c.n; if (c.n == 0) break; g.vs = V_WAIT; return;
            case O_CAST: {
                f.pc++;
                Actor& a = ensureActor(c.a); a.x = a.tx = (float)c.n; a.walking = false;
                if (!g.sceneOn) g.sceneOn = true;
            } break;
            case O_WALK: {
                f.pc++;
                Actor& a = ensureActor(c.a); a.tx = (float)c.n; a.spd = (float)atof(c.b.c_str()); a.walking = fabsf(a.tx - a.x) > 1;
                if (a.walking) a.dir = a.tx > a.x ? 1 : -1;
                if (c.c == "wait") { g.waitT = -1; g.vs = V_WAIT; return; }
            } break;
            case O_EMOTE: { f.pc++; Actor* a = actorBy(c.a); if (a) { a->emote = c.b; a->emoteT = 110; } } break;
            case O_ANIM: { f.pc++; Actor* a = actorBy(c.a); if (a) { a->animName = c.b; a->animT = c.b == "fall" ? 70 : 50; } } break;
            case O_BARS: f.pc++; g.barsOn = c.a == "on"; break;
            case O_NPCGO: {
                f.pc++;
                auto it = g.npcs.find(c.a);
                if (it != g.npcs.end()) { it->second.goal = (float)c.n; it->second.spd = (float)atof(c.b.c_str()); it->second.visible = true; }
                if (c.c == "wait") { g.waitT = -1; g.vs = V_WAIT; return; }
            } break;
            case O_PGO: {
                f.pc++; g.pgoal = (float)c.n; g.pspd = (float)atof(c.b.c_str());
                if (c.c == "wait") { g.waitT = -1; g.vs = V_WAIT; return; }
            } break;
            case O_FOCUS: f.pc++; g.focusKey = (c.a == "off" || c.a == "player") ? "" : c.a; break;
            case O_TOAST: f.pc++; toast(c.a); break;
            case O_LOCK: setF("lock_" + c.a, 1); f.pc++; break;
            case O_UNLOCK: setF("lock_" + c.a, 0); f.pc++; break;
        }
    }
}

static bool awaitEvent(const std::string& type, const std::string& arg) {
    if (getenv("BOTDBG")) { fprintf(stderr, "[await] %s %s vs=%d stack=%zu top=%s pc=%d\n", type.c_str(), arg.c_str(), (int)g.vs, g.stack.size(), g.stack.empty() ? "-" : g.stack.back().b->name.c_str(), g.stack.empty() ? -1 : g.stack.back().pc); }
    if (g.vs != V_AWAIT || g.stack.empty()) return false;
    Frame& f = g.stack.back();
    if (f.pc >= (int)f.b->cmds.size()) return false;
    Cmd& c = f.b->cmds[f.pc];
    if (c.op == O_AWAIT && c.a == type && c.b == arg) { f.pc++; g.vs = V_RUN; vmRun(); return true; }
    return false;
}

static void startDay(int d) {
    g.day = std::max(1, std::min(lastDay(), d));
    g.dayFlags = g.flags;
    if (g.day > g.st.maxD[g.chapter]) g.st.maxD[g.chapter] = g.day;
    g.progressFlags[pkKey(g.chapter, g.day)] = flagsStr(g.flags);
    saveProgress();
    writeSlot(g.slot);
    resetWorld();
    g.stack.clear();
    g.vs = V_RUN;
    if (g.mini) { delete g.mini; g.mini = nullptr; }
    vmPush(blockName(g.day));
    if (g.stack.empty()) { g.vs = V_NONE; toast("Missing script for this day"); return; }
    vmRun();
}

static void newGame(int slot) {
    g.slot = slot; g.chapter = 1; g.flags.clear(); g.playFrames = 0;
    setF("lock_roof", 1);
    g.mode = M_PLAY;
    startDay(1);
}
static void startDayFromSelect(int ch, int d) {
    // restore flag snapshot of that day if we have one; otherwise carry the finished state of the chapter before
    g.chapter = ch;
    g.flags.clear();
    auto it = g.progressFlags.find(pkKey(ch, d));
    if (it != g.progressFlags.end()) parseFlags(it->second, g.flags);
    else if (ch > 1 && (it = g.progressFlags.find(pkFinal(ch - 1))) != g.progressFlags.end()) { parseFlags(it->second, g.flags); g.flags.erase("won"); g.flags.erase("skipped"); }
    if (ch == 1) setF("lock_roof", d >= 10 ? 0 : 1);
    else setF("lock_roof", 0);
    if (ch == 1 && d < 10) setF("lock_roof", 1);
    if (g.slot < 1) g.slot = 1;
    g.mode = M_PLAY;
    startDay(d);
}

// ------------------------------------------------------------ interactions
struct Target { int kind = -1; std::string id; float x = 0; std::string label; };

static std::vector<ObjSp> builtinObjs(const std::string& fl) {
    std::vector<ObjSp> v;
    if (fl == "out1") v.push_back({"backdoor", "out1", "Stairway door", 130});
    if (fl == "lobby") { v.push_back({"reception", "lobby", "Reception desk", 1000}); v.push_back({"frontdoor", "lobby", "Front door", 2150}); }
    if (fl == "ctrl") v.push_back({"panel", "ctrl", "Control panel", 1150});
    if (fl == "shaft") v.push_back({"shaftgap", "shaft", "Shaft opening", 1250});
    if (fl == "vent") v.push_back({"fan", "vent", "Big fan", 1500});
    if (fl == "ulobby") v.push_back({"vending", "ulobby", "Vending machine", 900});
    if (fl == "roof") { v.push_back({"edge", "roof", "Roof edge", 1500}); v.push_back({"tank", "roof", "Water tank", 800}); }
    if (fl == "park1") v.push_back({"car1", "park1", "Parked car", 1500});
    if (fl == "park2") v.push_back({"car2", "park2", "Parked car", 1500});
    if (fl == "reghaia") {
        v.push_back({"p_home", "reghaia", "Îlot14 front door", 260});
        v.push_back({"p_busstop", "reghaia", "Etusa bus stop", 900});
        v.push_back({"p_cable", "reghaia", "Cable car station", 2300});
        v.push_back({"p_kiosk", "reghaia", "Kiosk", 1600});
    }
    if (fl == "madania") {
        v.push_back({"p_cableback", "madania", "Cable car (back to Reghaia)", 260});
        v.push_back({"p_cinemadoor", "madania", "Cinema entrance", 1500});
        v.push_back({"p_viewpoint", "madania", "Viewpoint", 2200});
    }
    if (fl == "cinema") {
        v.push_back({"p_cinexit", "cinema", "Exit to El Madania", 200});
        v.push_back({"p_ticket", "cinema", "Ticket desk", 800});
        v.push_back({"p_snack", "cinema", "Popcorn stand", 1300});
        v.push_back({"p_hall", "cinema", "Screening hall", 1900});
    }
    if (fl == "school") {
        v.push_back({"p_schoolexit", "school", "Etusa bus stop", 200});
        v.push_back({"p_class", "school", "Classroom door", 900});
        v.push_back({"p_yard", "school", "School yard", 1600});
        v.push_back({"p_office", "school", "Teachers' room", 2200});
    }
    if (fl == "room_amir") { v.push_back({"p_exit_amir", fl, "Door (leave)", 160}); v.push_back({"p_amir_bed", fl, "Bed", 500}); v.push_back({"p_amir_desk", fl, "Desk", 900}); v.push_back({"p_amir_wall", fl, "Wall of photos", 1300}); }
    if (fl == "room_dalia") { v.push_back({"p_exit_dalia", fl, "Door (leave)", 160}); v.push_back({"p_dalia_bed", fl, "Mopsy's charging spot", 500}); v.push_back({"p_dalia_phone", fl, "Phone (6 unsent texts)", 900}); v.push_back({"p_dalia_board", fl, "Plan board", 1300}); }
    if (fl == "room_gabriel") { v.push_back({"p_exit_gabriel", fl, "Door (leave)", 160}); v.push_back({"p_gab_rope", fl, "Coil of rope", 520}); v.push_back({"p_gab_shelf", fl, "Shelf", 1000}); v.push_back({"p_gab_zed", fl, "Zed's corner", 1300}); }
    return v;
}

static Target nearestTarget() {
    Target best; float bd = 1e9;
    FloorDef* f = floorBy(g.floorKey);
    if (!f) return best;
    auto consider = [&](int kind, const std::string& id, float x, const std::string& label, float range) {
        float d = fabsf(x - g.px);
        if (d < range && d < bd) { bd = d; best.kind = kind; best.id = id; best.x = x; best.label = label; }
    };
    for (auto& kv : g.npcs) {
        const Npc& n = kv.second;
        if (!n.visible || n.floor != g.floorKey) continue;
        CharDef* c = charBy(kv.first);
        consider(0, kv.first, n.x, c ? "Talk to " + c->name : "Talk", 85);
    }
    for (size_t i = 0; i < f->rooms.size(); i++) {
        const Room& r = f->rooms[i];
        std::string lab = r.secret ? "Examine door" : "Door " + r.id;
        consider(1, r.id, doorX(*f, (int)i), lab, 75);
    }
    if (f->inElevator) consider(2, "elevator", f->elevX, "Elevator", 80);
    for (auto& o : builtinObjs(g.floorKey)) consider(3, o.id, o.x, o.label, 85);
    for (auto& o : g.objs) if (o.floor == g.floorKey) consider(3, o.id, o.x, o.label, 85);
    return best;
}

static void startChat(const std::string& key) {
    setF("talk_" + key, F("talk_" + key) + 1);
    std::string a = "chat_" + key + "_d" + std::to_string(g.day), b = "chat_" + key;
    if (g.floorKey == "room_" + key && BLOCKS.count("chatroom_" + key)) vmPush("chatroom_" + key);
    else if (BLOCKS.count(a)) vmPush(a);
    else if (BLOCKS.count(b)) vmPush(b);
    else if (charBy(key) && charBy(key)->isBot && botOf(key)) {
        const BotInfo* bi = botOf(key);
        TMPBLOCKS.emplace_back();
        Block& b = TMPBLOCKS.back();
        auto add = [&](const std::string& who, const std::string& t) { Cmd c; c.op = O_SAY; c.a = who; c.b = t; b.cmds.push_back(c); };
        add(bi->name, "Beep! I'm " + bi->name + ". I'm " + bi->personality + ".");
        CharDef* oc = charBy(bi->ownerKey);
        if (bi->ownerKey == "amir") add(bi->name, "I'm YOURS, Amir! Best owner in the whole 14!");
        else if (oc) add(bi->name, "I belong to " + oc->name + " (" + oc->id + ").");
        else add(bi->name, "I belong to the whole building.");
        g.stack.push_back({&b, 0});
        g.vs = V_RUN;
    }
    else {
        static const char* gen[] = {"Hey Amir.", "Busy day, huh?", "The 14 never sleeps.", "Say hi to the bots for me.", "I'm good. You?", "Careful with the elevator."};
        CharDef* c = charBy(key);
        pushSay(c ? c->name : "", gen[rnd() % 6]);
    }
}
static void startDoorScript(const std::string& id) {
    std::string n = "door_" + id;
    if (BLOCKS.count(n)) { vmPush(n); return; }
    FloorDef* f = floorBy(g.floorKey);
    std::string txt = "Door.";
    if (f) for (auto& r : f->rooms) if (r.id == id) {
        if (r.key.empty()) txt = id + " - empty room. Nobody lives here.";
        else if (r.key == "amir") txt = "My room. Nothing to do in here right now.";
        else txt = id + " - " + r.name + "'s room. The door is closed.";
    }
    pushSay("", txt);
}
static void startUseScript(const std::string& id) {
    std::string n = "use_" + id;
    if (BLOCKS.count(n)) { vmPush(n); return; }
    pushSay("", "Nothing interesting here.");
}

static bool floorUnlocked(const FloorDef& f) { return f.inElevator && F("lock_" + f.key) == 0; }

static std::vector<int> elevList() {
    std::vector<int> v;
    for (size_t i = 0; i < FLOORS.size(); i++) if (floorUnlocked(FLOORS[i])) v.push_back((int)i);
    return v;
}

static void doInteract(const Target& t) {
    if (t.kind == 0) { if (!awaitEvent("talk", t.id)) startChat(t.id); }
    else if (t.kind == 1) { if (!awaitEvent("door", t.id)) startDoorScript(t.id); }
    else if (t.kind == 2) {
        g.elevOpen = true; g.elevPhase = 0; g.elevT = 0; g.elevDoor = 1; g.elevPath.clear();
        std::vector<int> l = elevList();
        g.elevSel = 0;
        for (size_t i = 0; i < l.size(); i++) if (FLOORS[l[i]].key == g.floorKey) g.elevSel = (int)i;
        g.elevFrom = g.elevCur = l.empty() ? 0 : l[g.elevSel];
    }
    else if (t.kind == 3) { if (!awaitEvent("use", t.id)) startUseScript(t.id); }
    vmRun();
}

static void goFloor(const std::string& key) {
    g.pendingFloor = key; g.fadePhase = 1;
}

// ------------------------------------------------------------ per-frame update (play)
static void updateFades() {
    if (g.fadePhase == 1) {
        g.fade += 0.12f;
        if (g.fade >= 1) {
            g.fade = 1;
            g.floorKey = g.pendingFloor;
            FloorDef* f = floorBy(g.floorKey);
            if (f) { g.px = f->elevX + 8; g.bannerText = f->name; g.banner = 140; }
            g.fadePhase = 2;
        }
    } else if (g.fadePhase == 2) {
        g.fade -= 0.12f;
        if (g.fade <= 0) { g.fade = 0; g.fadePhase = 0; }
    } else {
        if (g.fade < g.fadeTarget) g.fade = std::min(g.fadeTarget, g.fade + 0.04f);
        else if (g.fade > g.fadeTarget) g.fade = std::max(g.fadeTarget, g.fade - 0.04f);
    }
    if (g.flash > 0) g.flash--;
    if (g.shake > 0) g.shake--;
    if (g.banner > 0) g.banner--;
    for (size_t i = 0; i < g.toasts.size();) { if (--g.toasts[i].life <= 0) g.toasts.erase(g.toasts.begin() + i); else i++; }
}

static float typeSpeed() {
    switch (g.st.textSpeed) { case 0: return 0.5f; case 1: return 1.1f; case 2: return 2.4f; default: return 999; }
}
static int pageLen(const std::string& p) { return utf8len(p); }

// returns true if the world (walking) should be active
static void updateVM(const Input& in) {
    switch (g.vs) {
        case V_SAY: {
            const std::string& page = g.dPages[g.dPage];
            int len = pageLen(page);
            if (g.dShown < len) {
                g.dShown += typeSpeed();
                if (in.hit(B_A)) g.dShown = (float)len;
            } else {
                bool last = g.dPage + 1 >= (int)g.dPages.size();
                bool nextChoose = false;
                if (last && !g.stack.empty()) {
                    Frame& f = g.stack.back();
                    if (f.pc < (int)f.b->cmds.size() && f.b->cmds[f.pc].op == O_CHOOSE) nextChoose = true;
                }
                g.dWait++;
                static const float mult[4] = {0, 1.7f, 1.0f, 0.55f};
                bool autoGo = g.st.autoAdv > 0 && g.dWait >= (int)((55 + len * 1.4f) * mult[g.st.autoAdv]);
                if (nextChoose || autoGo || in.hit(B_A)) {
                    if (!last) { g.dPage++; g.dShown = 0; g.dWait = 0; }
                    else { g.vs = V_RUN; vmRun(); }
                }
            }
        } break;
        case V_CHOOSE: {
            if (in.hit(B_UP)) g.dSel = (g.dSel + (int)g.dChoices.size() - 1) % (int)g.dChoices.size();
            if (in.hit(B_DOWN)) g.dSel = (g.dSel + 1) % (int)g.dChoices.size();
            if (in.hit(B_A)) {
                std::string t = g.dTargets[g.dSel];
                g.vs = V_RUN;
                vmGoto(t);
                vmRun();
            }
        } break;
        case V_CARD: {
            g.cT++;
            if ((g.cT > 40 && in.hit(B_A)) || g.cT > 260) { g.vs = V_RUN; vmRun(); }
        } break;
        case V_ENDDAY: {
            g.cT++;
            if ((g.cT > 60 && in.hit(B_A)) || g.cT > 260) {
                if (g.day >= lastDay()) {
                    g.mode = M_ENDING; g.vs = V_NONE; g.stack.clear(); g.cT = 0;
                    g.endCh = g.chapter; awardBadge("ch" + std::to_string(g.chapter)); if (g.chapter == 3) { g.st.unl[4] = true; if (g.st.maxD[4] < 1) g.st.maxD[4] = 1; }
                    g.progressFlags[pkFinal(g.chapter)] = flagsStr(g.flags); saveProgress();   // final state of this chapter
                    if (g.chapter < 4) {
                        // same save slot continues straight into the next chapter
                        int nx = g.chapter + 1;
                        g.st.unl[nx] = true; if (g.st.maxD[nx] < 1) g.st.maxD[nx] = 1;
                        g.flags.erase("won"); g.flags.erase("skipped");
                        g.dayFlags = g.flags; g.chapter = nx; g.day = 1; g.playFrames = g.playFrames;
                        writeSlot(g.slot);
                    }
                    saveSettings();
                } else startDay(g.day + 1);
            }
        } break;
        case V_ASK: {
            g.kb.update(in);
            if (g.kb.done) {
                std::string t = g.kb.text; for (auto& ch : t) ch = tolower(ch);
                g.askText = t; g.vs = V_RUN; vmRun();
            }
        } break;
        case V_SCARE: {
            g.scareT++;
            if (g.scareT > 560) { g.vs = V_RUN; vmRun(); }
        } break;
        case V_WAIT: {
            if (g.waitT < 0) { if (!anyWalking()) { g.vs = V_RUN; vmRun(); } }
            else if (--g.waitT <= 0) { g.vs = V_RUN; vmRun(); }
        } break;
        case V_MINI: {
            g.mini->update(in);
            if (g.mini->finished) {
                setF("won", g.mini->won ? 1 : 0);
                setF("skipped", g.mini->skipped ? 1 : 0);
                setF("stars", g_miniStars);
                delete g.mini; g.mini = nullptr;
                g.vs = V_RUN; vmRun();
            }
        } break;
        default: break;
    }
}

static void elevFinish(bool moved) {
    g.elevOpen = false;
    if (!moved) return;
    FloorDef* f = floorBy(FLOORS[g.elevTo].key);
    g.floorKey = FLOORS[g.elevTo].key;
    if (f) { g.px = f->elevX + 90; g.pdir = 1; g.bannerText = f->name; g.banner = 140; }
}
// phases: 0 doors open (origin) 1 closing 2 choose floor 3 riding 4 ding 5 opening (destination) 6 hold 7 leaving (open to origin)
static void updateElevator(const Input& in) {
    std::vector<int> l = elevList();
    int n = (int)l.size();
    g.elevT++;
    switch (g.elevPhase) {
        case 0: g.elevDoor = 1; if (g.elevT > 16 || in.hit(B_A)) { g.elevPhase = 1; g.elevT = 0; } break;
        case 1: g.elevDoor = std::max(0.0f, 1.0f - g.elevT / 26.0f); if (g.elevDoor <= 0) { g.elevPhase = 2; g.elevT = 0; } break;
        case 2: {
            g.elevDoor = 0;
            if (in.hit(B_UP) && g.elevSel - 2 >= 0) g.elevSel -= 2;
            if (in.hit(B_DOWN) && g.elevSel + 2 < n) g.elevSel += 2;
            if (in.hit(B_LEFT) && g.elevSel > 0) g.elevSel--;
            if (in.hit(B_RIGHT) && g.elevSel + 1 < n) g.elevSel++;
            if (in.hit(B_B)) { g.elevPhase = 7; g.elevT = 0; }
            else if (in.hit(B_A) && n > 0) {
                int target = l[g.elevSel];
                if (target == g.elevFrom) { g.elevPhase = 7; g.elevT = 0; break; }
                int pf = 0, pt = g.elevSel;
                for (int i = 0; i < n; i++) if (l[i] == g.elevFrom) pf = i;
                g.elevPath.clear();
                for (int i = pf; i != pt; i += (pt > pf ? 1 : -1)) g.elevPath.push_back(l[i]);
                g.elevPath.push_back(l[pt]);
                g.elevTo = target; g.elevPhase = 3; g.elevT = 0;
            }
        } break;
        case 3: {
            const int fpf = 12;
            int idx = std::min((int)g.elevPath.size() - 1, g.elevT / fpf);
            g.elevCur = g.elevPath[idx];
            if (g.elevT >= ((int)g.elevPath.size() - 1) * fpf + 28) { g.elevCur = g.elevTo; g.elevPhase = 4; g.elevT = 0; }
        } break;
        case 4: if (g.elevT > 22) { g.elevPhase = 5; g.elevT = 0; } break;
        case 5: g.elevDoor = std::min(1.0f, g.elevT / 40.0f); if (g.elevDoor >= 1) { g.elevPhase = 6; g.elevT = 0; } break;
        case 6: if (g.elevT > 22 || in.hit(B_A)) elevFinish(true); break;
        case 7: g.elevDoor = std::min(1.0f, g.elevT / 28.0f); if (g.elevDoor >= 1 && g.elevT > 34) elevFinish(false); break;
    }
}
static void updateCoop() {
    if (!g.coopOn) return;
    FloorDef* f = floorBy(g.floorKey); if (!f) return;
    float camX = std::max(0.0f, std::min(f->width - SCR_W, g.px - 640));
    for (int k = 0; k < 3; k++) {
        CoPlayer& c = g.co[k]; if (!c.on) continue;
        Input& ci = G.coIn[k];
        if (c.floor != g.floorKey) { c.floor = g.floorKey; c.x = g.px + (k % 2 ? -1 : 1) * (80 + 60 * k); }
        c.moving = fabsf(ci.ax) > 0.2f;
        if (c.moving) { c.x += ci.ax * 5.2f; c.dir = ci.ax > 0 ? 1 : -1; c.walk++; }
        c.x = std::max(std::max(70.0f, camX + 50), std::min(std::min(f->width - 70, camX + SCR_W - 50), c.x));
        if (c.emoteT > 0) c.emoteT--;
        static const char* em[] = {"!", "...", "<3", "haha", "?", "hi!"};
        if (ci.hit(B_A)) { c.em = em[rnd() % 6]; c.emoteT = 90; }
        if (ci.hit(B_B)) { c.em = "wave"; c.emoteT = 70; }
    }
}

static void startSayCustom(const std::string& key) {
    TMPBLOCKS.emplace_back();
    Block& b = TMPBLOCKS.back();
    CharDef* c = charBy(key);
    Cmd a; a.op = O_ASK; a.a = "SAY SOMETHING TO " + (c ? c->name : std::string("THEM")); b.cmds.push_back(a);
    Cmd r; r.op = O_RUN; r.a = BLOCKS.count("reply_" + key) ? "reply_" + key : "reply_default"; b.cmds.push_back(r);
    g.stack.push_back({&b, 0}); g.vs = V_RUN;
    vmRun();
}

static void updateWorld(const Input& in) {
    FloorDef* f = floorBy(g.floorKey);
    if (!f) return;
    // elevator ride (full screen interior)
    if (g.elevOpen) { updateElevator(in); return; }
    float mx = in.ax;
    g.moving = fabsf(mx) > 0.2f;
    if (g.moving) { g.px += mx * 5.4f; g.pdir = mx > 0 ? 1 : -1; g.walk++; }
    g.px = std::max(70.0f, std::min(f->width - 70, g.px));
    // items auto pickup
    for (size_t i = 0; i < g.items.size();) {
        if (g.items[i].floor == g.floorKey && fabsf(g.items[i].x - g.px) < 40) {
            g.inv.push_back(g.items[i].key);
            toast("Picked up: " + prettyItem(g.items[i].key));
            g.items.erase(g.items.begin() + i);
        } else i++;
    }
    if (g.vs == V_AWAIT && !g.stack.empty()) {
        Frame& fr = g.stack.back();
        if (fr.pc < (int)fr.b->cmds.size() && awaitOk(fr.b->cmds[fr.pc])) { fr.pc++; g.vs = V_RUN; vmRun(); return; }
    }
    if (in.hit(B_A)) {
        Target t = nearestTarget();
        if (t.kind >= 0) doInteract(t);
    }
    if (in.hit(B_X) && g.vs == V_NONE) {
        Target t = nearestTarget();
        if (t.kind == 0) startSayCustom(t.id);
    }
}

static void updateNpcs() {
    for (auto& kv : g.npcs) {
        Npc& n = kv.second;
        float s = (n.still || n.goal >= 0) ? 0 : 26;
        float old = n.x;
        if (n.goal >= 0) {
            float d = n.goal - n.baseX;
            if (fabsf(d) <= n.spd) { n.baseX = n.goal; n.goal = -1; } else n.baseX += (d > 0 ? n.spd : -n.spd);
            n.x = n.baseX;
        } else n.x = n.baseX + sinf(g.frame * 0.012f + n.phase) * s;
        if (n.x != old) n.dir = n.x > old ? 1 : -1;
    }
}
static void updateActors() {
    for (auto& a : g.actors) {
        if (a.walking) {
            float d = a.tx - a.x;
            if (fabsf(d) <= a.spd) { a.x = a.tx; a.walking = false; } else { a.x += d > 0 ? a.spd : -a.spd; a.dir = d > 0 ? 1 : -1; }
        }
        if (a.animT > 0 && --a.animT == 0) a.animName.clear();
        if (a.emoteT > 0) a.emoteT--;
    }
    if (g.pgoal >= 0) {
        float d = g.pgoal - g.px;
        if (fabsf(d) <= g.pspd) { g.px = g.pgoal; g.pgoal = -1; g.moving = false; }
        else { g.px += d > 0 ? g.pspd : -g.pspd; g.pdir = d > 0 ? 1 : -1; g.moving = true; g.walk++; }
    }
    // bars
    float tgt = g.barsOn ? 1.0f : 0.0f;
    if (g.bars < tgt) g.bars = std::min(tgt, g.bars + 0.06f); else if (g.bars > tgt) g.bars = std::max(tgt, g.bars - 0.06f);
    // weather / fireworks / bees
    if (g.rain) for (int i = 0; i < 4; i++) g.parts.push_back({rndf() * 1380, -10, -3, 20 + rndf() * 6, 40, 40, C(190, 210, 255, 150), 3});
    if (g.fwT > 0) {
        g.fwT--;
        if (g.fwT % 34 == 0) {
            float x = 200 + rndf() * 880, y = 120 + rndf() * 230;
            Col cs[] = {ORANGE, C(255, 255, 255), C(90, 170, 255), C(255, 90, 160), C(255, 230, 90)};
            spawnBurst(x, y, 46, cs[rnd() % 5], 2);
            g.flash = std::max(g.flash, 4);
        }
    }
    if (g.beesT > 0) {
        g.beesT--;
        if (g.beesT % 6 == 0) g.parts.push_back({-10.0f, 120.0f + rndf() * 480, 4 + rndf() * 3, (rndf() - 0.5f) * 3, 320, 320, C(250, 210, 30), 4});
    }
    if (g.flickerT > 0) g.flickerT--;
    for (size_t i = 0; i < g.parts.size();) {
        Particle& p = g.parts[i];
        p.x += p.vx; p.y += p.vy;
        if (p.type == 2) { p.vy += 0.08f; p.vx *= 0.985f; }
        if (p.type == 1) { p.vx += (rndf() - 0.5f) * 0.3f; }
        if (p.type == 4) { p.vy += (rndf() - 0.5f) * 0.8f; p.x += sinf(g.frame * 0.4f + p.y) * 1.5f; }
        if (--p.life <= 0 || p.y > 760 || p.x > 1380) g.parts.erase(g.parts.begin() + i); else i++;
    }
}
