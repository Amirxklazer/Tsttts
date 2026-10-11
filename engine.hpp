// engine.hpp - game state, saves, script VM, world logic
#pragma once
#include "script.hpp"
#include <list>

#define VERSION "v0.2.0"

struct Settings { int textSpeed = 1; bool scanlines = true; int lastSlot = 0; int maxDay = 1; };
struct Npc { std::string floor; float baseX = 0, x = 0; bool visible = true; float phase = 0; int dir = 1; bool still = false; };
struct ItemSp { std::string key, floor; float x; };
struct ObjSp { std::string id, floor, label; float x; };
struct Toast { std::string t; int life; };

enum VS { V_NONE, V_RUN, V_SAY, V_CHOOSE, V_AWAIT, V_MINI, V_CARD, V_WAIT, V_ENDDAY };
enum Mode { M_TITLE, M_NEWSLOT, M_SLOTS, M_DAYSEL, M_SETTINGS, M_PLAY, M_PAUSE, M_PSET, M_ENDING };
struct Frame { Block* b; int pc; };

struct Game {
    Settings st;
    Mode mode = M_TITLE;
    int sel = 0, sel2 = 0, frame = 0;
    bool quit = false;
    std::string msg; int msgT = 0;
    // slot state
    int slot = 1, day = 1;
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
    // vm
    std::vector<Frame> stack;
    VS vs = V_NONE;
    std::string dWho, dKey; std::vector<std::string> dPages; int dPage = 0; float dShown = 0;
    std::vector<std::string> dChoices, dTargets; int dSel = 0;
    std::string cTitle, cSub; int cT = 0, waitT = 0;
    Mini* mini = nullptr;
    bool sceneOn = false; std::string sceneBg; std::vector<std::string> sceneChars;
    // fx
    int flash = 0, shake = 0; float fade = 0, fadeTarget = 0;
    int fadePhase = 0; std::string pendingFloor;
    int quitConfirm = 0;
} g;

static bool AUTOWIN = false;
static std::list<Block> TMPBLOCKS;

static int F(const std::string& k) { auto it = g.flags.find(k); return it == g.flags.end() ? 0 : it->second; }
static void setF(const std::string& k, int v) { g.flags[k] = v; }

static void toast(const std::string& t) {
    g.toasts.push_back({t, 170});
    if (g.toasts.size() > 4) g.toasts.erase(g.toasts.begin());
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

struct SlotInfo { bool exists = false; int day = 1; long frames = 0; };
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
    si.frames = atol(kv["frames"].c_str());
    return si;
}
static void saveSettings() {
    ensureDir();
    std::string s = "textspeed=" + std::to_string(g.st.textSpeed) + "\nscanlines=" + std::to_string(g.st.scanlines ? 1 : 0) +
                    "\nlastslot=" + std::to_string(g.st.lastSlot) + "\nmaxday=" + std::to_string(g.st.maxDay) + "\n";
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
    if (kv.count("maxday")) g.st.maxDay = std::max(1, std::min(31, atoi(kv["maxday"].c_str())));
    G.scanlines = g.st.scanlines;
    auto pr = parseKV(readFile(std::string(SAVE_DIR) + "progress.dat"));
    for (auto& kv2 : pr) if (kv2.first.size() > 1 && kv2.first[0] == 'd') g.progressFlags[atoi(kv2.first.c_str() + 1)] = kv2.second;
}
static void writeSlot(int s) {
    ensureDir();
    std::string t = "v=2\nday=" + std::to_string(g.day) + "\nframes=" + std::to_string(g.playFrames) + "\nflags=" + flagsStr(g.dayFlags) + "\n";
    writeFile(slotPath(s), t);
    g.st.lastSlot = s;
    saveSettings();
}
static bool readSlot(int s) {
    auto kv = parseKV(readFile(slotPath(s)));
    if (!kv.count("day")) return false;
    g.slot = s;
    g.day = std::max(1, std::min(31, atoi(kv["day"].c_str())));
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
            if (!found && c.isBot) { n.baseX = 620 + bi * 230; bi++; }
        }
        if (c.key == "amine" || c.key == "prime") n.visible = false;
        n.x = n.baseX;
        g.npcs[c.key] = n;
    }
}

static void resetWorld() {
    resetNpcs();
    g.items.clear(); g.objs.clear(); g.inv.clear(); g.toasts.clear(); g.goal.clear();
    g.sceneOn = false; g.elevOpen = false; g.flash = g.shake = 0; g.fade = 0; g.fadeTarget = 0; g.fadePhase = 0;
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
    g.dPage = 0; g.dShown = 0;
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

static void vmRun() {
    int guard = 0;
    while (g.vs == V_RUN) {
        if (++guard > 20000) { fprintf(stderr, "vm loop guard hit\n"); g.vs = V_NONE; return; }
        if (g.stack.empty()) { g.vs = V_NONE; return; }
        Frame& f = g.stack.back();
        if (f.pc >= (int)f.b->cmds.size()) { g.stack.pop_back(); continue; }
        Cmd& c = f.b->cmds[f.pc];
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
            case O_TITLE: f.pc++; g.cTitle = "DAY " + std::to_string(g.day); g.cSub = c.a; g.cT = 0; g.vs = V_CARD; return;
            case O_SCENE: {
                f.pc++;
                std::vector<std::string> w = words(c.a);
                if (w.empty() || w[0] == "off") g.sceneOn = false;
                else { g.sceneOn = true; g.sceneBg = w[0]; g.sceneChars.assign(w.begin() + 1, w.end()); }
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
            case O_ENDDAY:
                f.pc++;
                g.cTitle = "END OF DAY " + std::to_string(g.day);
                g.cSub = DAY_TITLE.count(g.day) ? DAY_TITLE[g.day] : "";
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
            } break;
            case O_WAIT: f.pc++; g.waitT = c.n; g.vs = V_WAIT; return;
            case O_TOAST: f.pc++; toast(c.a); break;
            case O_LOCK: setF("lock_" + c.a, 1); f.pc++; break;
            case O_UNLOCK: setF("lock_" + c.a, 0); f.pc++; break;
        }
    }
}

static bool awaitEvent(const std::string& type, const std::string& arg) {
    if (g.vs != V_AWAIT || g.stack.empty()) return false;
    Frame& f = g.stack.back();
    if (f.pc >= (int)f.b->cmds.size()) return false;
    Cmd& c = f.b->cmds[f.pc];
    if (c.op == O_AWAIT && c.a == type && c.b == arg) { f.pc++; g.vs = V_RUN; vmRun(); return true; }
    return false;
}

static void startDay(int d) {
    g.day = std::max(1, std::min(31, d));
    g.dayFlags = g.flags;
    if (g.day > g.st.maxDay) g.st.maxDay = g.day;
    g.progressFlags[g.day] = flagsStr(g.flags);
    saveProgress();
    writeSlot(g.slot);
    resetWorld();
    g.stack.clear();
    g.vs = V_RUN;
    if (g.mini) { delete g.mini; g.mini = nullptr; }
    vmPush("day_" + std::to_string(g.day));
    if (g.stack.empty()) { g.vs = V_NONE; toast("Missing script for this day"); return; }
    vmRun();
}

static void newGame(int slot) {
    g.slot = slot; g.flags.clear(); g.playFrames = 0;
    setF("lock_roof", 1);
    g.mode = M_PLAY;
    startDay(1);
}
static void startDayFromSelect(int d) {
    // restore flag snapshot of that day if we have one
    auto it = g.progressFlags.find(d);
    g.flags.clear();
    if (it != g.progressFlags.end()) parseFlags(it->second, g.flags);
    else setF("lock_roof", d >= 10 ? 0 : 1);
    if (d < 10) setF("lock_roof", 1);
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
    if (BLOCKS.count(a)) vmPush(a);
    else if (BLOCKS.count(b)) vmPush(b);
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
        g.elevOpen = true;
        std::vector<int> l = elevList();
        g.elevSel = 0;
        for (size_t i = 0; i < l.size(); i++) if (FLOORS[l[i]].key == g.floorKey) g.elevSel = (int)i;
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
                if (nextChoose || in.hit(B_A)) {
                    if (!last) { g.dPage++; g.dShown = 0; }
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
                if (g.day >= 31) { g.mode = M_ENDING; g.vs = V_NONE; g.stack.clear(); g.cT = 0; }
                else startDay(g.day + 1);
            }
        } break;
        case V_WAIT: {
            if (--g.waitT <= 0) { g.vs = V_RUN; vmRun(); }
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

static void updateWorld(const Input& in) {
    FloorDef* f = floorBy(g.floorKey);
    if (!f) return;
    // elevator menu
    if (g.elevOpen) {
        std::vector<int> l = elevList();
        if (in.hit(B_UP)) g.elevSel = std::max(0, g.elevSel - 1);
        if (in.hit(B_DOWN)) g.elevSel = std::min((int)l.size() - 1, g.elevSel + 1);
        if (in.hit(B_B)) g.elevOpen = false;
        if (in.hit(B_A)) {
            g.elevOpen = false;
            if (!l.empty() && FLOORS[l[g.elevSel]].key != g.floorKey) goFloor(FLOORS[l[g.elevSel]].key);
        }
        return;
    }
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
}

static void updateNpcs() {
    for (auto& kv : g.npcs) {
        Npc& n = kv.second;
        float s = n.still ? 0 : 26;
        float old = n.x;
        n.x = n.baseX + sinf(g.frame * 0.012f + n.phase) * s;
        if (n.x != old) n.dir = n.x > old ? 1 : -1;
    }
}
