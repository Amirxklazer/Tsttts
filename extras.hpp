// extras.hpp - badges, redeem codes, lore / endings, on-screen keyboard
#pragma once
#include <set>

struct BadgeDef { const char* id; const char* name; const char* desc; };
static const BadgeDef BADGE_LIST[] = {
    {"welcome", "Welcome to the 14", "Start your first day in the building."},
    {"cinema", "Do you love cinema ?", "Take the cable car to El Madania and watch a movie."},
    {"teachers", "Teachers got yo back", "Take the Etusa bus to school and survive the day."},
    {"bus", "Etusa Regular", "Ride the Etusa bus."},
    {"cable", "Cable Car Cruiser", "Ride the cable car over Reghaia."},
    {"popcorn", "Popcorn Pro", "Catch every popcorn at the cinema."},
    {"neighbor", "Good Neighbor", "Open Amir's, Dalia's and Gabriel's rooms."},
    {"bolt", "Bolt's Human", "Chat with your own Cleaning bot."},
    {"fashion", "Fashion Week", "Change your look in the customizer."},
    {"coder", "Code Cracker", "Redeem your first code."},
    {"haunted", "Gabriel Doesn't Play", "Tell Gabriel the wrong number."},
    {"beef", "Beef Season", "Start the beef with Adam and Amyas."},
    {"coop", "Better Together", "Start a co-op game."},
    {"ch1", "Lost the Ash", "Finish Chapter 1."},
    {"ch2", "Further Than Far", "Finish Chapter 2."},
    {"ch3", "Lowest Point", "Finish Chapter 3."},
    {"ch4", "Never Again", "Finish Chapter 4."},
    {"ch5", "Safe Ascent", "Finish Chapter 5."},
    {"collector", "Lore Hound", "Unlock 5 lore or ending entries."},
};
static const int NBADGES = (int)(sizeof(BADGE_LIST) / sizeof(BADGE_LIST[0]));

struct LoreDef { const char* id; const char* kind; const char* title; const char* pages; };   // pages separated by '|'
static const LoreDef LORE_LIST[] = {
    {"l_building", "LORE", "The Building", "Îlot14 has fourteen floors if you count the ones that don't want to be counted.|The lobby is 0. Up is Roof. Down is a Parking, then a Parking, then something that hums.|Nobody remembers who built it. The elevator remembers, and it won't say."},
    {"l_reghaia", "LORE", "Reghaia", "East of Algiers, where the sea breeze smells like tar and oranges.|The 14 stands on a quiet block. From the roof you can see the lake, the road, and the cable car wires.|Everyone says it is just a town. The 14 says: not quite."},
    {"l_bolt", "LORE", "Bolt", "Bolt is a Cleaning bot(tm) model B-06. Top speed: 'whoosh'.|He was built to sweep. He chose to sprint.|His favorite thing in the world is Amir. His second favorite is stairs he is not allowed to take."},
    {"l_prime", "LORE", "Prime", "BOT-00. The first Cleaning bot. He belongs to the whole building.|For forty years he swept the same corridor, because nobody told him the corridor had ended.|His voice is in capitals because he never learned that quiet was an option."},
    {"l_gabriel", "LORE", "Gabriel & the Rope", "Gabriel always carries a rope.|Nobody has ever asked why. He answers: 'Someone has to.'|The rope has been used for: a cat, a banner, a bot, a door, and one very awkward elevator."},
    {"l_dalia", "LORE", "Dalia & Mopsy", "Dalia named her bot Mopsy after her first dog. Mopsy has never met the dog.|Mopsy is grumpy. Dalia is loud. Together they make exactly one normal person.|Dalia texts six times because five feels like not caring and seven feels like begging."},
    {"e_knock", "ENDING", "Three Knocks", "Three knocks. A pause. Three more.|Amir opens the door. Nobody is there. A note: 'Thank you for answering.'|The building hums a happy chord. Somewhere below, a lamp lights up.|ENDING: THE POLITE KNOCK"},
    {"e_ashes", "ENDING", "Ash Remembers", "The ash on the roof forms a name, then another, then everyone's.|The building has been keeping a list of everyone who ever stayed.|Amir is at the top. Then Dalia. Then Gabriel. Then Bolt, with a little spark next to his name.|ENDING: THE LIST"},
    {"e_october", "ENDING", "The Haunted 14", "It's October. The Roof is covered in paper bats.|Every resident dresses as another resident. Dalia is Gabriel. Gabriel refuses to be Dalia.|Prime dresses as a vacuum cleaner. Nobody can tell the difference. He is delighted.|ENDING: BEST COSTUME"},
    {"e_stay", "ENDING", "The One Who Stays (Alt)", "In another version, Amir leaves the Echo Room and takes the elevator up. Alone.|The building is quiet. The bots wait by the doors. Dalia still texts six times.|He comes back on Day 2. Of course he does.|ENDING: THE COMMUTE"},
    {"e_credits", "ENDING", "Credits Roll", "A cinema, a cable car and a very tired popcorn machine.|The credits are longer than the movie. Bolt reads every name.|ENDING: STAY FOR THE POST-CREDITS"},
    {"e_school", "ENDING", "Teachers Got Yo Back", "The Etusa bus is late. The teachers are not.|Mrs. Zerrouki writes 'Amir tried' on the board and underlines it twice.|Whatever happens next, someone in that building is on your side.|ENDING: BACK TO SCHOOL"},
    {"l_amyas", "LORE", "Amyas", "Amyas is nineteen, the oldest in the whole series. He works at the ice cream shop on the main road.|He is the brother of Dalia and Adam Bachouche. He says he is only 'partially nice' after his shift.|Amir has beef with him. Nobody knows why. Amyas pretends he doesn't either."},
    {"l_adamb", "LORE", "Adam Bachouche", "Adam Bachouche is seventeen. Brother of Amyas and Dalia. He runs everywhere and he is always 'about to stop'.|Amir is tsundere to him: it's not like he cares. He cares.|If you ask Adam, the beef is a misunderstanding. If you ask Amir, the beef is a misunderstanding too."},
    {"l_alicia", "LORE", "Alicia", "Alicia is five. She is Amir's little sister and the most powerful person on the Uncommon floor.|She believes cards, cake and big brothers should all be shared.|Her favorite word is 'again'."},
    {"l_jalil", "LORE", "Jalil", "Jalil is four. He is Arwa's little brother and an excellent artist of buses with legs.|His crayon collection has one color: green.|He says the green is for bots."},
    {"l_abdullah", "LORE", "Abdullah", "Abdullah is six. He is Anes's little brother, owner of a clipboard and a gold star.|He gives himself gold stars. Nobody has ever argued with this."},
    {"l_amine", "LORE", "Amine", "Amine is thirteen and lives on the Special floor. He is Amir's bestie.|He brings sandwiches to any adventure. He believes in Amir more than Amir believes in himself."},
    {"l_jilali", "LORE", "Jilali", "Jilali is twenty, the grown-up of the Rare floor. He repairs watches, even the ones that run backward.|The clock in the Rare hall strikes fourteen once. He swears it was the clock's idea."},
    {"l_nst", "LORE", "The Tansaoutis", "Aya, Adam and Sofia Tansaouti live on the Special floor. Their doors are NST-001, NST-002 and NST-003.|They work the night shift at the Further inn, where their shift never really ended.|The Inn's soup tastes like pennies. Nobody knows why they all love it."},
    {"l_nevers", "LORE", "The Nevers", "Fourteen signs appeared in the building, each starting with NEVER.|They were not threats. They were promises written by the building itself.|The fifteenth sign was blank on purpose. Amir wrote it."},
    {"l_teachers", "LORE", "The School", "Mrs. Zerrouki teaches Amir's class. Mr. Benali teaches the loud one. Principal Hadj has a very tidy office.|Nobody is ever late for school in Reghaia. Everybody is a little late for school in Reghaia."},
    {"l_etusa", "LORE", "Etusa", "The Etusa bus stops outside the 14 every day. It never arrives on time. It always arrives.|The driver knows every resident by their umbrella."},
    {"l_cable", "LORE", "The Cable Car", "The cable car climbs over Reghaia toward El Madania. From the cabin you can see the lake, the road and the 14.|The wires hum a different note in the wind."},
    {"l_rope", "LORE", "Gabriel's Rope", "Gabriel's rope has been used in many rescues and one very awkward elevator.|Nobody has ever seen him buy a new one."},
    {"e_never", "ENDING", "Never Stop Coming Home", "Fourteen signs, one blank. Amir wrote the last one.|NEVER STOP COMING HOME.|The whole building hummed, and every lamp lit.|ENDING: THE FIFTEENTH SIGN"},
    {"e_ascent", "ENDING", "The Safe Ascent", "A long rope. A long climb. Everyone together.|At the top, sunrise. At the bottom, a bus. In between, snacks.|ENDING: THE LONG WAY UP"},
    {"e_sunrise", "ENDING", "Sunrise Over Reghaia", "The lake turns gold. The cable car wires sing. The 14 hums, pleased.|Amir finally says it out loud: 'Welcome home.'|ENDING: SUNRISE"},
    {"e_scare", "ENDING", "Do Not Tell Gabriel Numbers", "A number was said. The game forgot how to be a game.|It's just a prank. A Halloween decoration. Amir is hanging by the ankle with a pumpkin mask on, not hurt, just dramatic.|Gabriel will never admit he laughed.|ENDING: JUMP SCARE"},
};
static const int NLORE = (int)(sizeof(LORE_LIST) / sizeof(LORE_LIST[0]));

struct CodeDef { const char* code; const char* loreId; };
static const CodeDef CODE_LIST[] = {
    {"ILOT14", "l_building"}, {"REGHAIA", "l_reghaia"}, {"BOLT", "l_bolt"}, {"PRIME", "l_prime"}, {"GABRIEL", "l_gabriel"}, {"DALIA", "l_dalia"},
    {"AMYAS", "l_amyas"}, {"ADAMB", "l_adamb"}, {"ALICIA", "l_alicia"}, {"JALIL", "l_jalil"}, {"ABDULLAH", "l_abdullah"}, {"AMINE", "l_amine"}, {"JILALI", "l_jilali"},
    {"TANSAOUTI", "l_nst"}, {"NEVER", "l_nevers"}, {"SCHOOL", "l_teachers"}, {"ETUSA", "l_etusa"}, {"CABLE", "l_cable"}, {"ROPE", "l_rope"},
    {"FIFTEEN", "e_never"}, {"ASCENT", "e_ascent"}, {"SUNRISE", "e_sunrise"},
    {"KNOCK", "e_knock"}, {"ASHES", "e_ashes"}, {"OCTOBER", "e_october"}, {"STAY", "e_stay"}, {"CINEMA", "e_credits"},
};
static const int NCODES = (int)(sizeof(CODE_LIST) / sizeof(CODE_LIST[0]));

static std::set<std::string> U_BADGES, U_LORE, U_CODES;

static int loreIndex(const std::string& id) { for (int i = 0; i < NLORE; i++) if (id == LORE_LIST[i].id) return i; return -1; }
static std::vector<std::string> loreEntries() {   // unlocked entries, in list order
    std::vector<std::string> v;
    for (int i = 0; i < NLORE; i++) if (U_LORE.count(LORE_LIST[i].id)) v.push_back(LORE_LIST[i].id);
    return v;
}
static std::vector<std::string> pagesOf(const std::string& s) {
    std::vector<std::string> v; std::string cur;
    for (char c : s) { if (c == '|') { v.push_back(cur); cur.clear(); } else cur += c; }
    v.push_back(cur);
    return v;
}
static std::string joinSet(const std::set<std::string>& s) { std::string o; for (auto& x : s) { if (!o.empty()) o += ","; o += x; } return o; }
static void splitInto(const std::string& s, std::set<std::string>& out) {
    out.clear(); std::string cur;
    for (char c : s) { if (c == ',') { if (!cur.empty()) out.insert(cur); cur.clear(); } else cur += c; }
    if (!cur.empty()) out.insert(cur);
}

// ---------------------------------------------------------------- on-screen keyboard (touch + D-pad)
struct Kb {
    std::string text;
    int r = 0, c = 0, maxLen = 14;
    bool done = false;
    static const char* ROW(int i) {
        static const char* rows[4] = {"1234567890", "QWERTYUIOP", "ASDFGHJKL.", "ZXCVBNM-_?"};
        return rows[i];
    }
    int rowLen(int r2) const { return r2 < 4 ? 10 : 3; }   // last row: SPACE DEL OK
    void press() {
        if (r < 4) { char ch = ROW(r)[c]; if ((int)text.size() < maxLen) text += ch; }
        else if (c == 0) { if ((int)text.size() < maxLen) text += ' '; }
        else if (c == 1) { if (!text.empty()) text.pop_back(); }
        else done = true;
    }
    void update(const Input& in) {
        if (in.hit(B_UP)) { r = (r + 4) % 5; if (c >= rowLen(r)) c = rowLen(r) - 1; }
        if (in.hit(B_DOWN)) { r = (r + 1) % 5; if (c >= rowLen(r)) c = rowLen(r) - 1; }
        if (in.hit(B_LEFT)) c = (c + rowLen(r) - 1) % rowLen(r);
        if (in.hit(B_RIGHT)) c = (c + 1) % rowLen(r);
        if (in.hit(B_A)) press();
        if (in.hit(B_B)) { if (!text.empty()) text.pop_back(); }
        if (in.hit(B_Y)) text.clear();
        if (in.hit(B_PLUS) || in.hit(B_X)) done = true;
    }
};
