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

// ---------------- player appearance (customizer) ----------------
struct Appear { int skin = 2, hairStyle = 0, hairCol = 0, height = 2, top = 0, topCol = 0, pants = 0, acc = 0, tag14 = 1, shoes = 0, eyes = 0; };
static Appear APP;
static const Col SKIN_C[8] = {{255, 224, 196, 255}, {240, 200, 160, 255}, {222, 170, 125, 255}, {200, 150, 105, 255}, {170, 120, 82, 255}, {135, 90, 60, 255}, {100, 66, 44, 255}, {80, 52, 36, 255}};
static const Col HAIR_C[12] = {{25, 18, 14, 255}, {60, 38, 25, 255}, {110, 70, 35, 255}, {190, 150, 70, 255}, {210, 210, 210, 255}, {170, 50, 40, 255}, {60, 90, 200, 255}, {249, 115, 22, 255}, {90, 200, 170, 255}, {200, 90, 200, 255}, {240, 120, 150, 255}, {255, 255, 255, 255}};
static const Col TOP_C[12] = {{249, 115, 22, 255}, {235, 235, 235, 255}, {30, 30, 36, 255}, {200, 50, 50, 255}, {60, 120, 210, 255}, {60, 170, 90, 255}, {240, 200, 60, 255}, {150, 80, 190, 255}, {100, 100, 110, 255}, {240, 130, 170, 255}, {30, 150, 160, 255}, {120, 80, 50, 255}};
static const Col PANT_C[8] = {{35, 38, 55, 255}, {30, 30, 30, 255}, {70, 90, 140, 255}, {110, 90, 60, 255}, {90, 90, 96, 255}, {60, 100, 70, 255}, {150, 60, 60, 255}, {230, 230, 230, 255}};
static const float HEIGHT_V[5] = {0.84f, 0.92f, 1.0f, 1.08f, 1.16f};
static const char* HEIGHT_N[5] = {"SHORT", "SMALL", "AVERAGE", "TALL", "TALLER"};
static const char* HAIR_N[12] = {"SHORT", "LONG", "BUZZ", "CURLY", "SPIKY", "PONYTAIL", "BUN", "SIDE SWEPT", "TWIN TAILS", "MOHAWK", "MESSY", "STRAIGHT"};
static const char* TOP_N[9] = {"T-SHIRT", "HOODIE", "JACKET", "STRIPED", "VEST", "OVERALLS", "LONG COAT", "TRACKSUIT", "LOGO TEE"};
static const char* ACC_N[12] = {"NONE", "GLASSES", "CAP", "HEADPHONES", "SCARF", "BEANIE", "HEADBAND", "BOW TIE", "EYEPATCH", "CROWN", "BANDANA", "GOGGLES"};
static const char* EYES_N[4] = {"NORMAL", "CALM", "SLEEPY", "WIDE"};
static const Col SHOE_C[6] = {{30, 30, 30, 255}, {235, 235, 235, 255}, {200, 50, 50, 255}, {60, 120, 210, 255}, {249, 115, 22, 255}, {90, 60, 40, 255}};
static const char* SKIN_N[8] = {"PALE", "LIGHT", "SAND", "TAN", "BROWN", "DEEP", "DARK", "DARKER"};

static Look lookFromAppear(const Appear& a) {
    Look l;
    l.skin = SKIN_C[a.skin % 8]; l.hair = HAIR_C[a.hairCol % 12]; l.shirt = TOP_C[a.topCol % 12]; l.pants = PANT_C[a.pants % 8];
    l.hairStyle = a.hairStyle % 12; l.h = HEIGHT_V[a.height % 5]; l.tag14 = a.tag14 != 0; l.topStyle = a.top % 9; l.acc = a.acc % 12; l.shoes = SHOE_C[a.shoes % 6]; l.eyes = a.eyes % 4; l.trim = a.acc == 5 || a.acc == 6 ? mix(l.shirt, WHITE, 0.4f) : WHITE;
    return l;
}

// ---------------- Cleaning bots(tm): everyone owns one ----------------
struct BotInfo { std::string botKey, name, ownerKey, personality; bool named; };
static std::vector<BotInfo> BOTS;

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
static Look DL(Col shirt, Col hair, Col skin, int style, float h, Col pants, int top, int acc, int eyes, Col shoes, Col trim = C(255, 255, 255)) {
    Look l = LK(shirt, hair, skin, style, h, pants); l.topStyle = top; l.acc = acc; l.eyes = eyes; l.shoes = shoes; l.trim = trim; return l;
}
static void addChar(const char* key, const char* id, const char* name, const char* floor, Look l, bool bot = false) {
    CharDef c; c.key = key; c.id = id; c.name = name; c.floor = floor; c.look = l; c.isBot = bot;
    CHARS.push_back(c);
}

static FloorDef* floorBy(const std::string& k);
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
        {{"S-001", "Amine", "amine"}, {"S-002", "Haydar", "kenzy"}, {"NST-001", "Aya", "aya_n"}, {"NST-002", "Adam Tansaouti", "tansaouti"}, {"NST-003", "Sofia", "sofia"}});
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
        {{"NST-001", "Aya", "aya_n"}, {"NST-003", "Sofia", "sofia"}});
    // extra non-elevator places
    addFloor("out1", "Outside parking", "outside", 0, C(110, 150, 200), C(255, 255, 255), {}, false);
    addFloor("reghaia", "Reghaia", "outside", 0, C(110, 150, 200), C(255, 255, 255), {}, false);
    addFloor("madania", "El Madania", "outside", 0, C(150, 170, 200), C(255, 230, 160), {}, false);
    addFloor("cinema", "Cinema", "cinema", 0, C(60, 20, 40), C(255, 200, 80), {}, false);
    addFloor("school", "School", "school", 0, C(200, 190, 150), C(60, 120, 90), {}, false);
    addFloor("room_amir", "Amir's room (L-001)", "roomint", 0, C(70, 80, 120), C(255, 140, 60), {}, false);
    addFloor("room_dalia", "Dalia's room (M-002)", "roomint", 0, C(90, 120, 170), C(255, 230, 240), {}, false);
    addFloor("room_gabriel", "Gabriel's room (M-004)", "roomint", 0, C(52, 54, 62), C(200, 200, 215), {}, false);
    floorBy("shaft")->width = 3000; floorBy("vent")->width = 2800; floorBy("park2")->width = 2800; floorBy("ulobby")->width = 2600; floorBy("bots")->width = 2600; floorBy("inn")->width = 2600;
    floorBy("reghaia")->width = 3200; floorBy("madania")->width = 2800; floorBy("cinema")->width = 2200; floorBy("school")->width = 2600;
    floorBy("room_amir")->width = 1700; floorBy("room_dalia")->width = 1700; floorBy("room_gabriel")->width = 1700;

    Col dk = C(30, 22, 18);
    // Main
    addChar("arwa", "M-001", "Arwa", "main", DL(C(190, 90, 160), C(35, 22, 18), C(224, 172, 130), 11, 1.0f, C(60, 50, 90), 6, 6, 0, C(120, 60, 100), C(255, 220, 240)));
    addChar("dalia", "M-002", "Dalia", "main", DL(C(80, 160, 235), C(70, 35, 25), C(236, 190, 150), 8, 0.95f, C(40, 50, 90), 1, 10, 3, C(255, 255, 255), C(255, 255, 255)));
    addChar("dania", "M-003", "Dania", "main", DL(C(120, 200, 120), C(95, 55, 30), C(226, 176, 136), 6, 0.98f, C(80, 100, 70), 5, 1, 2, C(110, 80, 50), C(255, 255, 255)));
    addChar("gabriel", "M-004", "Gabriel", "main", DL(C(70, 70, 82), C(30, 20, 15), C(215, 165, 120), 10, 1.08f, C(30, 30, 36), 2, 11, 1, C(20, 20, 20), C(200, 200, 210)));
    addChar("youcef", "M-005", "Youcef", "main", DL(C(205, 175, 60), C(20, 20, 20), C(205, 150, 105), 2, 1.1f, C(70, 70, 60), 4, 7, 0, C(40, 30, 20), C(255, 255, 255)));
    // Lethal
    Look pl = DL(ORANGE, C(25, 18, 14), C(222, 170, 125), 0, 1.0f, C(35, 38, 55), 1, 0, 0, C(235, 235, 235)); pl.tag14 = true;
    addChar("amir", "L-001", "Amir", "lethal", pl);
    addChar("raceem", "L-002", "Raceem", "lethal", DL(C(160, 60, 60), C(20, 20, 20), C(212, 162, 118), 9, 1.02f, C(30, 30, 30), 7, 3, 0, C(255, 255, 255), C(255, 255, 255)));
    addChar("adam_l3", "L-003", "Adam", "lethal", DL(C(70, 110, 175), C(40, 25, 20), C(220, 170, 128), 7, 1.0f, C(50, 60, 90), 1, 0, 0, C(240, 240, 240), C(255, 255, 255)));
    addChar("amir_l4", "L-004", "Amir", "lethal", DL(C(90, 155, 150), C(60, 38, 25), C(215, 165, 122), 3, 0.97f, C(60, 70, 60), 8, 5, 2, C(30, 30, 30), C(255, 255, 255)));
    addChar("aya_l", "L-005", "Aya", "lethal", DL(C(235, 150, 205), C(35, 22, 18), C(230, 182, 142), 5, 0.97f, C(240, 230, 240), 3, 6, 0, C(255, 255, 255), C(255, 255, 255)));
    addChar("basmala", "L-006", "Basmala", "lethal", DL(C(240, 205, 120), C(45, 28, 20), C(226, 178, 138), 1, 1.0f, C(100, 80, 60), 6, 1, 1, C(70, 50, 40), C(120, 90, 50)));
    addChar("adam_l7", "L-007", "Adam Chermatti", "lethal", DL(C(115, 95, 155), C(25, 20, 20), C(208, 158, 112), 4, 1.03f, C(40, 40, 60), 7, 2, 0, C(30, 30, 30), C(255, 255, 255)));
    addChar("fares", "OL-007", "Fares", "lethal", DL(C(35, 35, 40), C(15, 15, 15), C(205, 155, 110), 0, 1.12f, C(30, 30, 35), 6, 8, 1, C(20, 20, 20), C(180, 40, 40)));
    // Common
    addChar("anes", "C-001", "Anes", "common", DL(C(235, 235, 235), C(35, 25, 20), C(224, 175, 135), 0, 1.0f, C(90, 60, 40), 5, 0, 2, C(60, 40, 30), C(255, 255, 255)));
    addChar("iyad", "C-005", "Iyad", "common", DL(C(140, 200, 235), C(30, 22, 18), C(214, 164, 120), 10, 0.93f, C(60, 80, 110), 8, 11, 0, C(255, 255, 255), C(255, 255, 255)));
    // Uncommon
    addChar("alicia", "UC-001", "Alicia", "unc", DL(C(220, 90, 90), C(120, 70, 35), C(238, 196, 160), 11, 1.0f, C(200, 200, 210), 1, 5, 0, C(255, 255, 255), C(255, 180, 180)));
    addChar("abdullah", "UC-002", "Abdullah", "unc", DL(C(80, 150, 90), C(20, 18, 18), C(206, 156, 110), 2, 1.06f, C(60, 60, 60), 4, 0, 3, C(30, 30, 30), C(255, 255, 255)));
    addChar("jalil", "UC-003", "Jalil", "unc", DL(C(90, 90, 200), C(28, 20, 18), C(210, 160, 116), 3, 1.0f, C(40, 40, 80), 7, 3, 0, C(255, 255, 255), C(255, 255, 255)));
    addChar("adam_uc", "UC-004", "Adam Abdellani", "unc", DL(C(200, 140, 70), C(30, 22, 20), C(218, 168, 126), 7, 0.98f, C(70, 60, 50), 2, 0, 1, C(60, 40, 30), C(255, 255, 255)));
    addChar("amira", "UC-005", "Amira", "unc", DL(C(235, 120, 150), C(40, 25, 20), C(228, 180, 140), 6, 0.96f, C(250, 240, 245), 6, 6, 0, C(255, 150, 170), C(255, 255, 255)));
    // Rare
    addChar("anais", "R-001", "Anais", "rare", DL(C(255, 245, 190), C(150, 90, 40), C(240, 198, 165), 5, 0.99f, C(90, 110, 150), 5, 0, 2, C(255, 255, 255), C(255, 255, 255)));
    addChar("maysanne", "R-002", "Maysanne", "rare", DL(C(150, 100, 200), C(25, 15, 15), C(222, 174, 134), 11, 1.0f, C(30, 30, 40), 6, 9, 0, C(40, 20, 60), C(255, 230, 120)));
    addChar("jilali", "R-003", "Jilali", "rare", DL(C(60, 130, 130), C(35, 28, 25), C(205, 155, 112), 2, 1.08f, C(50, 50, 50), 4, 1, 1, C(30, 30, 30), C(255, 255, 255)));
    // Special
    addChar("amine", "S-001", "Amine", "special", DL(C(250, 215, 80), C(30, 22, 18), C(218, 168, 125), 10, 1.0f, C(60, 60, 90), 8, 11, 3, C(255, 255, 255), C(60, 60, 60)));
    addChar("kenzy", "S-002", "Haydar", "special", DL(C(120, 220, 170), C(20, 18, 18), C(208, 158, 114), 0, 0.98f, C(40, 50, 60), 7, 3, 0, C(30, 30, 30), C(255, 255, 255)));
    // Teen
    addChar("amyas", "T-001", "Amyas", "teen", DL(C(255, 165, 195), C(35, 22, 18), C(228, 180, 140), 8, 1.08f, C(70, 70, 120), 1, 10, 3, C(255, 255, 255), C(255, 255, 255)));
    addChar("adam_t", "T-002", "Adam Bachouche", "teen", DL(C(60, 205, 205), C(25, 20, 18), C(216, 166, 124), 9, 1.0f, C(40, 40, 60), 7, 2, 0, C(255, 200, 80), C(255, 255, 255)));
    addChar("lilian", "T-003", "Lilian", "teen", DL(C(210, 210, 90), C(40, 28, 22), C(222, 172, 130), 5, 0.95f, C(90, 90, 150), 5, 0, 0, C(255, 255, 255), C(255, 255, 255)));
    // Further inn
    addChar("aya_n", "NST-001", "Aya", "special", DL(C(255, 190, 140), C(30, 20, 18), C(232, 184, 145), 6, 1.0f, C(90, 60, 50), 4, 0, 1, C(80, 50, 40), C(255, 255, 255)));
    addChar("tansaouti", "NST-002", "Adam Tansaouti", "special", DL(C(120, 160, 90), C(30, 20, 20), C(210, 160, 116), 7, 1.06f, C(50, 70, 50), 6, 7, 1, C(30, 25, 20), C(220, 200, 120)));
    addChar("sofia", "NST-003", "Sofia", "special", DL(C(180, 120, 220), C(120, 60, 30), C(238, 194, 158), 11, 0.98f, C(70, 40, 90), 6, 6, 1, C(255, 255, 255), C(255, 230, 150)));
    // new in v0.5: the rival and the school staff
    addChar("zerrouki", "SCH-01", "Mrs. Zerrouki", "school", DL(C(140, 60, 90), C(60, 40, 40), C(224, 176, 136), 6, 1.0f, C(60, 40, 60), 6, 1, 0, C(60, 40, 40), C(255, 230, 240)));
    addChar("benali", "SCH-02", "Mr. Benali", "school", DL(C(40, 120, 180), C(20, 20, 20), C(205, 155, 110), 2, 1.12f, C(30, 60, 100), 7, 6, 3, C(255, 255, 255), C(255, 255, 255)));
    addChar("hadj", "SCH-03", "Principal Hadj", "school", DL(C(70, 70, 76), C(200, 200, 200), C(215, 165, 120), 0, 1.04f, C(50, 50, 56), 2, 7, 1, C(30, 30, 30), C(255, 255, 255)));
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

    // ---- bot registry. The first 8 are the named bots in the bots parking. Edit owners here.
    BOTS.clear();
    BOTS.push_back({"sweepy", "Sweepy", "arwa", "cheerful and proud of every clean floor", true});
    BOTS.push_back({"mopsy", "Mopsy", "dalia", "grumpy but loyal", true});
    BOTS.push_back({"dustin", "Dustin", "dania", "nervous, scared of stairs and the color yellow", true});
    BOTS.push_back({"vacca", "Vacca", "youcef", "sleepy, efficiently idle", true});
    BOTS.push_back({"sparkle", "Sparkle", "aya_l", "dramatic, loves shiny buttons", true});
    BOTS.push_back({"bolt", "Bolt", "amir", "hyper, fast, almost hits everyone", true});
    BOTS.push_back({"grim", "Grim", "basmala", "gloomy poet, secretly sweet", true});
    BOTS.push_back({"zed", "Zed", "gabriel", "sarcastic, pretends not to care", true});
    BOTS.push_back({"prime", "Prime", "", "the first Cleaning bot, belongs to the whole building", true});
    // everyone else owns a bot too. They roam their owner's floor.
    static const char* gn[] = {"Pip", "Tiny", "Nova", "Dot", "Rusty", "Buzz", "Mochi", "Gizmo", "Ember", "Ziggy", "Pebble", "Waffles", "Sprocket", "Clank", "Biscuit", "Moxie", "Toast", "Pixel", "Noodle", "Widget", "Bubbles", "Cinder", "Fizz", "Olive", "Peanut"};
    static const char* gp[] = {"curious, pokes everything", "shy, hides behind plants", "chatty, never stops beeping", "lazy, takes naps on pads", "brave, chases the dust bunnies", "tidy, hates crumbs", "playful, loves a game of tag", "serious, sweeps in straight lines", "cheeky, hides socks", "gentle, hums lullabies"};
    static const Col gc[] = {C(255, 170, 90), C(150, 200, 255), C(255, 220, 120), C(170, 255, 170), C(220, 170, 255), C(255, 160, 190), C(160, 240, 230), C(240, 240, 140)};
    int gi = 0;
    std::vector<CharDef> extra;
    for (auto& c : CHARS) {
        if (c.isBot || c.key == "amir") continue;
        bool has = false;
        for (auto& b : BOTS) if (b.ownerKey == c.key) has = true;
        if (has) continue;
        std::string bk = "bot_" + c.key;
        BOTS.push_back({bk, gn[gi % 25], c.key, gp[(gi * 3) % 10], false});
        CharDef b; b.key = bk; b.id = "BOT-" + c.id; b.name = gn[gi % 25]; b.floor = c.floor; b.isBot = true;
        b.look = LK(gc[gi % 8], C(0, 0, 0), C(0, 0, 0));
        extra.push_back(b);
        gi++;
    }
    for (auto& b : extra) CHARS.push_back(b);
}

static const BotInfo* botOf(const std::string& botKey) { for (auto& b : BOTS) if (b.botKey == botKey) return &b; return nullptr; }
static const BotInfo* botOwnedBy(const std::string& ownerKey) { for (auto& b : BOTS) if (b.ownerKey == ownerKey) return &b; return nullptr; }
static Look playerLook() { CharDef* c = nullptr; for (auto& x : CHARS) if (x.key == "amir") { c = &x; break; } if (c) return c->look; return lookFromAppear(APP); }

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
