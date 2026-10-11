// data.hpp - floors, characters, items. Edit names / colors / rooms here.
#pragma once
#include "core.hpp"

struct Room {
    std::string id;    // sign text, e.g. "M-002"
    std::string name;  // sign name
    std::string key;   // character key living here ("" = nobody)
    bool secret = false;
};

struct FloorDef {
    std::string key, name, theme;
    int level;               // 8 = roof ... 0 = lobby ... -8 = further inn
    Col wall, trim;
    std::vector<Room> rooms;
    bool inElevator = true;
    float width = 2400;
    float elevX = 130;
    float roomX(size_t i) const { return 430 + i * 300; }
};

struct CharDef {
    std::string key, id, name, floor;
    Look look;
    bool isBot = false;
};

static std::vector<FloorDef> FLOORS;
static std::vector<CharDef> CHARS;

static Look LK(Col shirt, Col hair, Col skin, int style = 0, float h = 1.0f, Col pants = C(55, 60, 85)) {
    Look l; l.shirt = shirt; l.hair = hair; l.skin = skin; l.pants = pants; l.hairStyle = style; l.h = h; l.tag14 = false;
    return l;
}

static void addFloor(const char* key, const char* name, const char* theme, int level, Col wall, Col trim, std::vector<Room> rooms, bool inElev = true) {
    FloorDef f;
    f.key = key; f.name = name; f.theme = theme; f.level = level; f.wall = wall; f.trim = trim;
    f.rooms = rooms; f.inElevator = inElev;
    f.width = std::max<float>(2400, 430 + rooms.size() * 300 + 260);
    FLOORS.push_back(f);
}
static void addChar(const char* key, const char* id, const char* name, const char* floor, Look l, bool bot = false) {
    CharDef c; c.key = key; c.id = id; c.name = name; c.floor = floor; c.look = l; c.isBot = bot;
    CHARS.push_back(c);
}

static void buildData() {
    FLOORS.clear(); CHARS.clear();
    // top -> bottom. level numbers: Lobby = 0
    addFloor("roof", "Roof", "roof", 8, C(40, 60, 110), C(255, 200, 80), {});
    addFloor("teen", "Teen floor", "hall", 7, C(86, 170, 190), C(255, 230, 120),
        {{"T-001", "Amyas", "amyas"}, {"T-002", "Adam", "adam_t"}, {"T-003", "Lilian", "lilian"}});
    addFloor("lethal", "Lethal floor", "hall", 6, C(120, 40, 55), C(255, 110, 60),
        {{"L-001", "Amir", "amir"}, {"L-002", "Raceem", "raceem"}, {"L-003", "Adam", "adam_l3"}, {"L-004", "Amir", "amir_l4"},
         {"L-005", "Aya", "aya_l"}, {"L-006", "Basmala", "basmala"}, {"L-007", "Adam", "adam_l7"}, {"OL-007", "Fares", "fares"}});
    addFloor("main", "Main floor", "hall", 5, C(70, 90, 150), C(250, 250, 250),
        {{"M-001", "Arwa", "arwa"}, {"M-002", "Dalia", "dalia"}, {"SECRET", "Stairway to Hell", "", true},
         {"M-003", "Dania", "dania"}, {"M-004", "Gabriel", "gabriel"}, {"M-005", "Youcef", "youcef"}});
    addFloor("special", "Special floor", "hall", 4, C(110, 70, 150), C(255, 215, 90),
        {{"S-001", "Amine", "amine"}, {"S-002", "Kenzy", "kenzy"}});
    addFloor("rare", "Rare floor", "hall", 3, C(40, 120, 110), C(255, 235, 170),
        {{"R-001", "Anais", "anais"}, {"R-002", "Maysanne", "maysanne"}, {"R-003", "Jilali", "jilali"}});
    addFloor("unc", "Uncommon floor", "hall", 2, C(190, 130, 60), C(255, 250, 220),
        {{"UC-001", "Alicia", "alicia"}, {"UC-002", "Abdullah", "abdullah"}, {"UC-003", "Jalil", "jalil"},
         {"UC-004", "Adam", "adam_uc"}, {"UC-005", "Amira", "amira"}});
    addFloor("common", "Common floor", "hall", 1, C(120, 140, 110), C(240, 240, 230),
        {{"C-001", "Anes", "anes"}, {"C-002", "(empty)", ""}, {"C-003", "(empty)", ""}, {"C-004", "(empty)", ""}, {"C-005", "Iyad", "iyad"}});
    addFloor("lobby", "Lobby", "lobby", 0, C(200, 190, 170), C(249, 115, 22), {});
    addFloor("ulobby", "Underlobby", "under", -1, C(95, 100, 115), C(120, 200, 255), {});
    addFloor("park1", "Parking 1", "parking", -2, C(90, 90, 96), C(255, 220, 60), {});
    addFloor("park2", "Parking 2", "parking", -3, C(80, 84, 92), C(255, 160, 60), {});
    addFloor("shaft", "Elevator shaft fix", "shaft", -4, C(70, 72, 78), C(255, 210, 40), {});
    addFloor("ctrl", "Elevator control room", "ctrl", -5, C(40, 55, 70), C(90, 255, 160), {});
    addFloor("vent", "Air ventilation systems", "vent", -6, C(75, 95, 100), C(170, 230, 255), {});
    addFloor("bots", "14 Cleaning bots\xE2\x84\xA2 parking", "botpark", -7, C(60, 75, 95), C(120, 255, 220), {});
    addFloor("inn", "Further inn", "inn", -8, C(150, 60, 70), C(255, 215, 120),
        {{"NST-001", "Aya", "aya_n"}, {"NST-002", "Adam Tansaouti", "tansaouti"}, {"NST-003", "Sofia", "sofia"}});
    // extra non-elevator places
    addFloor("out1", "Outside parking", "outside", 0, C(110, 150, 200), C(255, 255, 255), {}, false);

    Col dk = C(30, 22, 18);
    // Main
    addChar("arwa", "M-001", "Arwa", "main", LK(C(190, 90, 160), dk, C(224, 172, 130), 1));
    addChar("dalia", "M-002", "Dalia", "main", LK(C(80, 160, 235), C(70, 35, 25), C(236, 190, 150), 1, 0.95f));
    addChar("dania", "M-003", "Dania", "main", LK(C(120, 200, 120), C(95, 55, 30), C(226, 176, 136), 1));
    addChar("gabriel", "M-004", "Gabriel", "main", LK(C(70, 70, 82), C(30, 20, 15), C(215, 165, 120), 0, 1.05f));
    addChar("youcef", "M-005", "Youcef", "main", LK(C(205, 175, 60), C(20, 20, 20), C(205, 150, 105), 2, 1.08f, C(70, 70, 60)));
    // Lethal
    Look pl = LK(ORANGE, C(25, 18, 14), C(222, 170, 125), 0, 1.0f, C(35, 38, 55)); pl.tag14 = true;
    addChar("amir", "L-001", "Amir", "lethal", pl);
    addChar("raceem", "L-002", "Raceem", "lethal", LK(C(160, 60, 60), C(20, 20, 20), C(212, 162, 118), 2));
    addChar("adam_l3", "L-003", "Adam", "lethal", LK(C(70, 110, 175), C(40, 25, 20), C(220, 170, 128), 0));
    addChar("amir_l4", "L-004", "Amir", "lethal", LK(C(90, 155, 150), C(60, 38, 25), C(215, 165, 122), 3));
    addChar("aya_l", "L-005", "Aya", "lethal", LK(C(235, 150, 205), C(35, 22, 18), C(230, 182, 142), 1, 0.97f));
    addChar("basmala", "L-006", "Basmala", "lethal", LK(C(240, 205, 120), C(45, 28, 20), C(226, 178, 138), 1));
    addChar("adam_l7", "L-007", "Adam", "lethal", LK(C(115, 95, 155), C(25, 20, 20), C(208, 158, 112), 0));
    addChar("fares", "OL-007", "Fares", "lethal", LK(C(35, 35, 40), C(15, 15, 15), C(205, 155, 110), 3, 1.1f, C(30, 30, 35)));
    // Common
    addChar("anes", "C-001", "Anes", "common", LK(C(235, 235, 235), C(35, 25, 20), C(224, 175, 135), 0));
    addChar("iyad", "C-005", "Iyad", "common", LK(C(140, 200, 235), C(30, 22, 18), C(214, 164, 120), 0));
    // Uncommon
    addChar("alicia", "UC-001", "Alicia", "unc", LK(C(220, 90, 90), C(120, 70, 35), C(238, 196, 160), 1));
    addChar("abdullah", "UC-002", "Abdullah", "unc", LK(C(80, 150, 90), C(20, 18, 18), C(206, 156, 110), 0, 1.04f));
    addChar("jalil", "UC-003", "Jalil", "unc", LK(C(90, 90, 200), C(28, 20, 18), C(210, 160, 116), 3));
    addChar("adam_uc", "UC-004", "Adam", "unc", LK(C(200, 140, 70), C(30, 22, 20), C(218, 168, 126), 0));
    addChar("amira", "UC-005", "Amira", "unc", LK(C(235, 120, 150), C(40, 25, 20), C(228, 180, 140), 1));
    // Rare
    addChar("anais", "R-001", "Anais", "rare", LK(C(255, 245, 190), C(150, 90, 40), C(240, 198, 165), 1));
    addChar("maysanne", "R-002", "Maysanne", "rare", LK(C(150, 100, 200), C(25, 15, 15), C(222, 174, 134), 1));
    addChar("jilali", "R-003", "Jilali", "rare", LK(C(60, 130, 130), C(35, 28, 25), C(205, 155, 112), 2, 1.06f));
    // Special
    addChar("amine", "S-001", "Amine", "special", LK(C(250, 215, 80), C(30, 22, 18), C(218, 168, 125), 0));
    addChar("kenzy", "S-002", "Kenzy", "special", LK(C(120, 220, 170), C(20, 18, 18), C(208, 158, 114), 0, 0.98f));
    // Teen
    addChar("amyas", "T-001", "Amyas", "teen", LK(C(255, 165, 195), C(35, 22, 18), C(228, 180, 140), 0, 1.1f));
    addChar("adam_t", "T-002", "Adam", "teen", LK(C(60, 205, 205), C(25, 20, 18), C(216, 166, 124), 3, 1.0f));
    addChar("lilian", "T-003", "Lilian", "teen", LK(C(210, 210, 90), C(40, 28, 22), C(222, 172, 130), 0, 0.96f));
    // Further inn
    addChar("aya_n", "NST-001", "Aya", "inn", LK(C(255, 190, 140), C(30, 20, 18), C(232, 184, 145), 1));
    addChar("tansaouti", "NST-002", "Adam Tansaouti", "inn", LK(C(120, 160, 90), C(30, 20, 20), C(210, 160, 116), 0, 1.04f));
    addChar("sofia", "NST-003", "Sofia", "inn", LK(C(180, 120, 220), C(120, 60, 30), C(238, 194, 158), 1));
    // 14 Cleaning bots(tm): everyone owns one, every bot has a personality
    addChar("sweepy", "BOT-01", "Sweepy", "bots", LK(C(255, 210, 80), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("mopsy", "BOT-02", "Mopsy", "bots", LK(C(120, 190, 255), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("dustin", "BOT-03", "Dustin", "bots", LK(C(190, 190, 200), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("vacca", "BOT-04", "Vacca", "bots", LK(C(255, 140, 120), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("sparkle", "BOT-05", "Sparkle", "bots", LK(C(255, 130, 220), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("bolt", "BOT-06", "Bolt", "bots", LK(C(130, 255, 130), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("grim", "BOT-07", "Grim", "bots", LK(C(110, 90, 160), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("zed", "BOT-08", "Zed", "bots", LK(C(255, 255, 255), C(0, 0, 0), C(0, 0, 0)), true);
    addChar("prime", "BOT-00", "Prime", "bots", LK(C(255, 120, 30), C(0, 0, 0), C(0, 0, 0)), true);
}

static FloorDef* floorBy(const std::string& k) {
    for (auto& f : FLOORS) if (f.key == k) return &f;
    return nullptr;
}
static int floorIdx(const std::string& k) {
    for (size_t i = 0; i < FLOORS.size(); i++) if (FLOORS[i].key == k) return (int)i;
    return -1;
}
static CharDef* charBy(const std::string& k) {
    for (auto& c : CHARS) if (c.key == k) return &c;
    return nullptr;
}
static CharDef* charByName(const std::string& n) {
    for (auto& c : CHARS) if (c.name == n) return &c;
    return nullptr;
}
static std::string prettyItem(const std::string& k) {
    std::string s = k;
    for (auto& c : s) if (c == '_') c = ' ';
    return s;
}
