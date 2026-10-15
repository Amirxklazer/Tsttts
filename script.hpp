// script.hpp - story script parser + validator. The story itself lives in story_*.hpp
#pragma once
#include "mini.hpp"

enum Op {
    O_SAY, O_CHOOSE, O_GOTO, O_SET, O_ADD, O_IF, O_IFNOT, O_IFGE, O_IFDAY, O_MINI, O_CARD, O_SCENE, O_GOAL,
    O_AWAIT, O_SPAWN, O_CLEARITEMS, O_WARP, O_ENDDAY, O_RUN, O_END, O_NPC, O_OBJ, O_DELOBJ, O_FX, O_WAIT,
    O_TITLE, O_TOAST, O_LOCK, O_UNLOCK,
    O_CAST, O_WALK, O_EMOTE, O_ANIM, O_BARS, O_NPCGO, O_PGO, O_FOCUS, O_ASK, O_IFSAY, O_BADGE, O_ENDING, O_SCARE, O_STAY, O_ZOOM
};

struct Cmd {
    Op op = O_END;
    std::string a, b, c;
    int n = 0;
    int line = 0;
    std::vector<std::pair<std::string, std::string>> opts;
};
struct Block {
    std::string name;
    std::vector<Cmd> cmds;
    std::map<std::string, int> labels;
};

static bool isAnimName(const std::string& n) { static const char* k[] = {"dance","nod","point","laugh","shiver","sit","look","stomp","float","jump","cheer","tilt","shrug","sway","bounce","clap","zoomies","twirl","sneak","dizzy","salute"}; for (auto x : k) if (n == x) return true; return false; }
static std::map<std::string, Block> BLOCKS;
static const int CH_LEN[6] = {0, 31, 35, 40, 45, 40};
static const char* CH_NAME[6] = {"", "Lost the Ash", "Further Inn", "Lowest Point", "Never", "Safe Ascent"};
static std::map<int, std::string> DAY_T[6];
static std::string dayTitleOf(int ch, int d) { auto it = DAY_T[ch].find(d); return it == DAY_T[ch].end() ? "" : it->second; }
static int pkKey(int ch, int d) { return ch == 1 ? d : ch * 100 + d; }
static int pkFinal(int ch) { return ch == 1 ? 32 : ch * 100 + 99; }
static std::vector<std::string> STORY_ERRORS;

static std::vector<std::string> words(const std::string& s) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == ' ' || c == '\t') { if (!cur.empty()) { out.push_back(cur); cur.clear(); } }
        else cur += c;
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

static void storyErr(const std::string& src, int line, const std::string& m) {
    STORY_ERRORS.push_back(src + ":" + std::to_string(line) + ": " + m);
}

static void parseStory(const std::string& text, const std::string& srcName) {
    static const std::map<std::string, Op> OPS = {
        {"say", O_SAY}, {"choose", O_CHOOSE}, {"goto", O_GOTO}, {"set", O_SET}, {"add", O_ADD}, {"if", O_IF},
        {"ifnot", O_IFNOT}, {"ifge", O_IFGE}, {"ifday", O_IFDAY}, {"mini", O_MINI}, {"card", O_CARD},
        {"scene", O_SCENE}, {"goal", O_GOAL}, {"await", O_AWAIT}, {"spawn", O_SPAWN}, {"clearitems", O_CLEARITEMS},
        {"warp", O_WARP}, {"endday", O_ENDDAY}, {"run", O_RUN}, {"end", O_END}, {"return", O_END}, {"npc", O_NPC},
        {"obj", O_OBJ}, {"delobj", O_DELOBJ}, {"fx", O_FX}, {"wait", O_WAIT}, {"title", O_TITLE}, {"toast", O_TOAST},
        {"lock", O_LOCK}, {"unlock", O_UNLOCK}, {"cast", O_CAST}, {"walk", O_WALK}, {"emote", O_EMOTE}, {"anim", O_ANIM},
        {"bars", O_BARS}, {"npcgo", O_NPCGO}, {"pgo", O_PGO}, {"focus", O_FOCUS}, {"zoom", O_ZOOM},
        {"ask", O_ASK}, {"ifsay", O_IFSAY}, {"badge", O_BADGE}, {"ending", O_ENDING}, {"scare", O_SCARE}, {"stay", O_STAY}};
    std::vector<std::string> lines = splitStr(text, '\n');
    Block* cur = nullptr;
    int ln = 0;
    for (auto& raw : lines) {
        ln++;
        std::string l = trim(raw);
        if (l.empty() || l[0] == '#') continue;
        if (l[0] == '>') {
            if (!cur || cur->cmds.empty() || cur->cmds.back().op != O_CHOOSE) { storyErr(srcName, ln, "option outside choose"); continue; }
            std::string body = trim(l.substr(1));
            size_t p = body.rfind("=>");
            if (p == std::string::npos) { storyErr(srcName, ln, "option needs =>"); continue; }
            cur->cmds.back().opts.push_back({trim(body.substr(0, p)), trim(body.substr(p + 2))});
            continue;
        }
        size_t sp = l.find(' ');
        std::string cmd = sp == std::string::npos ? l : l.substr(0, sp);
        std::string rest = sp == std::string::npos ? "" : trim(l.substr(sp + 1));
        for (auto& ch : cmd) ch = tolower(ch);
        if (cmd == "script") {
            if (BLOCKS.count(rest)) storyErr(srcName, ln, "duplicate script " + rest);
            BLOCKS[rest].name = rest;
            cur = &BLOCKS[rest];
            continue;
        }
        if (!cur) { storyErr(srcName, ln, "command outside script"); continue; }
        if (cmd == "label") { if (rest == "end") storyErr(srcName, ln, "label named 'end' is reserved (it ends the script)"); cur->labels[rest] = (int)cur->cmds.size(); continue; }
        auto it = OPS.find(cmd);
        if (it == OPS.end()) { storyErr(srcName, ln, "unknown command '" + cmd + "'"); continue; }
        Cmd c; c.op = it->second; c.line = ln;
        std::vector<std::string> w = words(rest);
        switch (c.op) {
            case O_SAY: {
                size_t p = rest.find('|');
                if (p == std::string::npos) { c.a = ""; c.b = rest; }
                else { c.a = trim(rest.substr(0, p)); c.b = trim(rest.substr(p + 1)); }
            } break;
            case O_CARD: {
                size_t p = rest.find('|');
                if (p == std::string::npos) { c.a = rest; } else { c.a = trim(rest.substr(0, p)); c.b = trim(rest.substr(p + 1)); }
            } break;
            case O_GOTO: c.a = rest; break;
            case O_SET: if (w.empty()) storyErr(srcName, ln, "set needs flag"); else { c.a = w[0]; c.n = w.size() > 1 ? atoi(w[1].c_str()) : 1; } break;
            case O_ADD: if (w.size() < 2) storyErr(srcName, ln, "add needs flag n"); else { c.a = w[0]; c.n = atoi(w[1].c_str()); } break;
            case O_IF: case O_IFNOT: if (w.size() < 2) storyErr(srcName, ln, "if needs flag label"); else { c.a = w[0]; c.b = w[1]; } break;
            case O_IFGE: if (w.size() < 3) storyErr(srcName, ln, "ifge needs flag n label"); else { c.a = w[0]; c.n = atoi(w[1].c_str()); c.b = w[2]; } break;
            case O_IFDAY: if (w.size() < 2) storyErr(srcName, ln, "ifday needs n label"); else { c.n = atoi(w[0].c_str()); c.b = w[1]; } break;
            case O_MINI: c.a = rest; break;
            case O_SCENE: c.a = rest; break;
            case O_GOAL: c.a = rest; break;
            case O_AWAIT: if (w.size() < 2) storyErr(srcName, ln, "await needs type arg"); else { c.a = w[0]; c.b = w[1]; if (w[0] == "items") c.n = atoi(w[1].c_str()); } break;
            case O_SPAWN: if (w.size() < 3) storyErr(srcName, ln, "spawn item floor x"); else { c.a = w[0]; c.b = w[1]; c.n = atoi(w[2].c_str()); } break;
            case O_WARP: if (w.empty()) storyErr(srcName, ln, "warp needs floor"); else { c.a = w[0]; c.n = w.size() > 1 ? atoi(w[1].c_str()) : -1; } break;
            case O_RUN: c.a = rest; break;
            case O_NPC: if (w.size() < 2) storyErr(srcName, ln, "npc key floor x | hide | show"); else { c.a = w[0]; c.b = w[1]; c.n = w.size() > 2 ? atoi(w[2].c_str()) : -1; } break;
            case O_OBJ: if (w.size() < 4) storyErr(srcName, ln, "obj id floor x label"); else {
                c.a = w[0]; c.b = w[1]; c.n = atoi(w[2].c_str());
                size_t p = rest.find(w[2]); c.c = trim(rest.substr(p + w[2].size()));
            } break;
            case O_DELOBJ: c.a = rest; break;
            case O_FX: c.a = rest; break;
            case O_WAIT: c.n = rest == "done" ? -1 : atoi(rest.c_str()); break;
            case O_CAST: if (w.size() < 2) storyErr(srcName, ln, "cast key x"); else { c.a = w[0]; c.n = atoi(w[1].c_str()); } break;
            case O_WALK: case O_NPCGO:
                if (w.size() < 2) storyErr(srcName, ln, "walk key x [speed] [wait]");
                else { c.a = w[0]; c.n = atoi(w[1].c_str()); c.b = w.size() > 2 && w[2] != "wait" ? w[2] : "4"; c.c = (w.back() == "wait") ? "wait" : ""; }
                break;
            case O_PGO:
                if (w.empty()) storyErr(srcName, ln, "pgo x [speed] [wait]");
                else { c.n = atoi(w[0].c_str()); c.b = w.size() > 1 && w[1] != "wait" ? w[1] : "4"; c.c = (w.back() == "wait") ? "wait" : ""; }
                break;
            case O_EMOTE: if (w.size() < 2) storyErr(srcName, ln, "emote key text"); else { c.a = w[0]; c.b = trim(rest.substr(w[0].size())); } break;
            case O_ANIM: if (w.size() < 2) storyErr(srcName, ln, "anim key kind"); else { c.a = w[0]; c.b = w[1]; } break;
            case O_BARS: c.a = rest; break;
            case O_FOCUS: c.a = rest; break;
            case O_ZOOM: c.a = rest; break;
            case O_TITLE: c.a = rest;
                if (cur->name.rfind("day_", 0) == 0) DAY_T[1][atoi(cur->name.c_str() + 4)] = rest;
                if (cur->name.rfind("c2_", 0) == 0) DAY_T[2][atoi(cur->name.c_str() + 3)] = rest;
                if (cur->name.rfind("c3_", 0) == 0) DAY_T[3][atoi(cur->name.c_str() + 3)] = rest;
                if (cur->name.rfind("c4_", 0) == 0) DAY_T[4][atoi(cur->name.c_str() + 3)] = rest;
                if (cur->name.rfind("c5_", 0) == 0) DAY_T[5][atoi(cur->name.c_str() + 3)] = rest;
                break;
            case O_TOAST: c.a = rest; break;
            case O_LOCK: case O_UNLOCK: c.a = rest; break;
            case O_ASK: c.a = rest; break;
            case O_IFSAY: if (w.size() < 2) storyErr(srcName, ln, "ifsay word label"); else { c.a = w[0]; for (auto& ch2 : c.a) ch2 = tolower(ch2); c.b = w[1]; } break;
            case O_BADGE: case O_ENDING: c.a = rest; break;
            default: break;
        }
        cur->cmds.push_back(c);
    }
}

// validate: labels, scripts, floors, characters
static void validateStory() {
    auto chk = [&](Block& b, Cmd& c, const std::string& lab) {
        if (lab == "end" || lab.empty()) return;
        if (!b.labels.count(lab)) storyErr(b.name, c.line, "missing label '" + lab + "'");
    };
    for (auto& kv : BLOCKS) {
        Block& b = kv.second;
        for (auto& c : b.cmds) {
            switch (c.op) {
                case O_GOTO: chk(b, c, c.a); break;
                case O_IF: case O_IFNOT: case O_IFGE: case O_IFDAY: case O_IFSAY: chk(b, c, c.b); break;
                case O_CHOOSE:
                    if (c.opts.empty()) storyErr(b.name, c.line, "choose with no options");
                    for (auto& o : c.opts) chk(b, c, o.second);
                    break;
                case O_RUN: if (!BLOCKS.count(c.a)) storyErr(b.name, c.line, "missing script '" + c.a + "'"); break;
                case O_WARP: if (!floorBy(c.a)) storyErr(b.name, c.line, "unknown floor " + c.a); break;
                case O_SPAWN: if (!floorBy(c.b)) storyErr(b.name, c.line, "unknown floor " + c.b); break;
                case O_OBJ: if (!floorBy(c.b)) storyErr(b.name, c.line, "unknown floor " + c.b); break;
                case O_LOCK: case O_UNLOCK: if (!floorBy(c.a)) storyErr(b.name, c.line, "unknown floor " + c.a); break;
                case O_CAST: case O_WALK: case O_EMOTE: case O_ANIM:
                    if (!charBy(c.a)) storyErr(b.name, c.line, "unknown character " + c.a);
                    if (c.op == O_ANIM && !isAnimName(c.b) && c.b != "hop" && c.b != "spin" && c.b != "fall" && c.b != "shake" && c.b != "wave" && c.b != "bow" && c.b != "rise")
                        storyErr(b.name, c.line, "bad anim " + c.b);
                    break;
                case O_NPCGO: if (!charBy(c.a)) storyErr(b.name, c.line, "unknown character " + c.a); break;
                case O_FOCUS: if (c.a != "off" && c.a != "player" && !charBy(c.a)) storyErr(b.name, c.line, "bad focus " + c.a); break;
                case O_NPC:
                    if (!charBy(c.a)) storyErr(b.name, c.line, "unknown character " + c.a);
                    else if (c.b != "hide" && c.b != "show" && c.b != "reset" && !floorBy(c.b)) storyErr(b.name, c.line, "unknown floor " + c.b);
                    break;
                case O_SCENE: {
                    std::vector<std::string> w = words(c.a);
                    for (size_t i = 1; i < w.size(); i++) if (!charBy(w[i])) storyErr(b.name, c.line, "unknown character in scene: " + w[i]);
                } break;
                case O_AWAIT:
                    if (c.a == "talk" && !charBy(c.b)) storyErr(b.name, c.line, "await talk unknown character " + c.b);
                    else if (c.a == "floor" && !floorBy(c.b)) storyErr(b.name, c.line, "await floor unknown " + c.b);
                    else if (c.a != "talk" && c.a != "floor" && c.a != "door" && c.a != "items" && c.a != "use") storyErr(b.name, c.line, "bad await type " + c.a);
                    break;
                case O_MINI: {
                    std::vector<std::string> w = words(c.a);
                    static const char* kinds[] = {"roundup", "timing", "fight", "catch", "maze", "roof", "simon", "sneak", "rhythm", "dodge", "defend", "whack", "pairs", "lights", "popcorn", "quiz", "tapcatch", "slide", "memo", "stack", "sort", "dash", "balance"};
                    bool ok = false; for (auto k : kinds) if (!w.empty() && w[0] == k) ok = true;
                    if (!ok) storyErr(b.name, c.line, "unknown minigame '" + c.a + "'");
                } break;
                default: break;
            }
        }
    }
    for (int ch = 1; ch <= 4; ch++)
        for (int d = 1; d <= CH_LEN[ch]; d++) {
            std::string n = std::string(ch == 1 ? "day_" : ch == 2 ? "c2_" : ch == 3 ? "c3_" : "c4_") + std::to_string(d);
            if (!BLOCKS.count(n)) STORY_ERRORS.push_back("missing script " + n);
        }
    for (auto& ch : CHARS)
        if (!BLOCKS.count("chat_" + ch.key)) STORY_ERRORS.push_back("note: no chat_" + ch.key + " (will use chat_default)");
}
