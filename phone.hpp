// phone.hpp - v0.7.0: "Your phone" - message and text the others
#pragma once
struct PhMsg { bool mine; std::string txt; };
static std::map<std::string, std::vector<PhMsg>> PH_MSG;
static std::set<std::string> PH_UNREAD;
static std::vector<std::string> PH_CONTACTS;
static int phView = 0;            // 0 contact list, 1 thread
static std::string phKey;         // open contact
static std::string phPendKey; static int phPendT = 0, phPendOpt = 0;
static long phLastDay = -1;

static void phSave() {
    ensureDir();
    std::string s = "#day " + std::to_string(phLastDay) + "\n";
    for (auto& kv : PH_MSG) {
        size_t st = kv.second.size() > 40 ? kv.second.size() - 40 : 0;
        for (size_t i = st; i < kv.second.size(); i++) s += kv.first + "\t" + (kv.second[i].mine ? "M" : "O") + "\t" + kv.second[i].txt + "\n";
    }
    for (auto& k : PH_UNREAD) s += "#unread " + k + "\n";
    FILE* f = fopen((std::string(SAVE_DIR) + "phone.dat").c_str(), "wb"); if (!f) return;
    fwrite(s.data(), 1, s.size(), f); fclose(f);
}
static void phLoad() {
    std::string s = readFile(std::string(SAVE_DIR) + "phone.dat");
    size_t p = 0;
    while (p < s.size()) {
        size_t e = s.find('\n', p); if (e == std::string::npos) e = s.size();
        std::string ln = s.substr(p, e - p); p = e + 1;
        if (ln.rfind("#day ", 0) == 0) { phLastDay = atol(ln.c_str() + 5); continue; }
        if (ln.rfind("#unread ", 0) == 0) { PH_UNREAD.insert(ln.substr(8)); continue; }
        size_t t1 = ln.find('\t'); if (t1 == std::string::npos) continue;
        size_t t2 = ln.find('\t', t1 + 1); if (t2 == std::string::npos) continue;
        PH_MSG[ln.substr(0, t1)].push_back({ln[t1 + 1] == 'M', ln.substr(t2 + 1)});
    }
}
static const char* PH_OPTS[5] = {"Hey!", "What are you doing?", "Wanna hang out?", "Tell me something fun.", "Good night!"};

static int phCat(const std::string& k) {
    if (k == "alicia" || k == "abdullah" || k == "jalil") return 0;
    if (k == "adam_uc" || k == "amira" || k == "maysanne" || k == "anes" || k == "iyad") return 1;
    if (k == "amyas" || k == "adam_t" || k == "lilian") return 3;
    if (k == "jilali" || k == "zerrouki" || k == "benali" || k == "hadj") return 4;
    return 2;
}
static void phBuildContacts() {
    PH_CONTACTS.clear();
    for (auto& c : CHARS) { if (c.isBot || c.key == "amir" || c.key == "amir_l4") continue; PH_CONTACTS.push_back(c.key); }
}
struct PhSpecial { const char* key; const char* r[5]; };
static const PhSpecial PH_SPECIAL[] = {
    {"dalia", {"Amir! Finally! Do you know what Gabriel did today? ...Never mind. Hi!", "Bossing Mopsy around. She's bossing me back. It's a partnership!", "YES! Roof! Bring snacks! And NOT Gabriel! ...Okay, he can come. Quietly.", "Mopsy sneezed and a dust bunny flew across the room. It looked offended!", "Night! Don't let Gabriel's rope get you! (He's fine. Probably.)"}},
    {"gabriel", {"Hey. I was just coiling the rope. Hi.", "Knots. Always knots. Is Dalia busy? Asking for the rope.", "Sure. Roof? ...Is Dalia coming? Just asking.", "A rope can hold fourteen kids. I tested it. Don't tell anyone how.", "Night. Tie your shoes before bed. It helps. I don't know why."}},
    {"amine", {"Amir! My bestie! What's up?", "Eating something that looks odd and tastes odd. It's mine. I'm proud.", "Always. You pick the place, I'll bring the snacks.", "I tried to whistle today. A bot whistled back. We're friends now.", "Night, bestie. Text me if you can't sleep."}},
    {"amyas", {"What.", "Scooping ice cream. Why do you care? Don't answer.", "Fine. One hour. Strawberry's on me. Don't make it weird.", "Nothing fun. ...Okay, a kid asked for ice cream with ketchup. I said no. It was a close call.", "Go to sleep, Amir. That's an order. I'm older."}},
    {"adam_t", {"Hey. Not that I was waiting for your text.", "Training for the stairs race. I'm winning. Don't ask me how I know.", "I guess. If there's nothing better to do. There isn't. Fine.", "I beat Dalia at tag. She says it was a draw. It was a draw. Barely.", "Night. Don't stay up reading. I know you."}},
    {"arwa", {"Hi Amir! Jalil's on top of the couch again. Hi from both of us.", "Babysitting a four-year-old king. He wants a crown. A bus-shaped one.", "Sure! Jalil comes too. He's a very small package of chaos.", "Jalil told me he wants to marry a bus. I said we'd discuss it later.", "Night! If you hear 'beep beep' at 3 AM, it's Jalil."}},
    {"jalil", {"HI! I'm a king! A bus king!", "I'm eating a crayon. It's not good. I'm brave!", "YES! Bus ride! I'm driving!", "Buses can fly. If they want to. They don't want to. Yet.", "Night night, big friend. Beep."}},
    {"alicia", {"Big brother! Hi hi hi!", "I'm drawing you a map! It has a star! The star is you!", "Yes yes yes! Can we get cake? A tiny cake? A tiny tiny cake?", "A bot told me bots dream of mops. Mopsy said no. I think she's lying.", "Night, big brother! Don't forget my goodnight hug tomorrow!"}},
    {"anes", {"Hi Amir! I taught a bot to whistle. Sort of.", "Sitting. I'm great at sitting. Abdullah's sitting too. It's a team.", "Okay! I'll bring Abdullah. And snacks. And a clipboard.", "Abdullah gave a stair a gold star and then yelled at it. It was a good day.", "Night! Tell the bots goodnight from me."}},
    {"abdullah", {"Hello. I'm the safety inspector. Everything is safe.", "Inspecting. Everything has a gold star except the broken stair. It has a sad face.", "Okay. But I have to bring my clipboard. It's the rule.", "Anes sat on a chair for two hours. I gave him a gold star. He's proud.", "Goodnight. The building is safe. I checked. Twice."}},
    {"prime", {"HELLO AMIR. I HAVE LEARNED TO TEXT. IT IS CAPITAL LETTERS ONLY.", "SWEEPING.", "I WILL BRING A MOP. FOR EMOTIONAL SUPPORT.", "THE BUILDING HUMS A FOUR-NOTE SONG. IT SOUNDS LIKE HOME.", "GOODNIGHT. THE LAMPS ARE ON. I AM WATCHING OVER YOU. NOT IN A CREEPY WAY."}},
};
static const char* PH_CAT[5][5][2] = {
    // 0 tiny kid
    {{"Hi hi hi!", "Heeey!"}, {"Playing! I'm a dinosaur!", "Drawing! With ALL the crayons!"}, {"Yes! Yes! Yes!", "Okay! Can I bring a toy?"}, {"I saw a bug! It was brave!", "I'm learning to hop on one foot!"}, {"Night night!", "Goodnight! Beep!"}},
    // 1 small kid
    {{"Hi Amir!", "Hey! What's up?"}, {"Reading a comic. It's good.", "Helping a bot with its homework. It's hard."}, {"Sure! Where?", "Okay! Give me five minutes!"}, {"A bot told me a joke. It was about mops. I didn't get it.", "I found a coin in the stairwell. I'm rich."}, {"Night!", "Goodnight, Amir!"}},
    // 2 kid
    {{"Hey Amir!", "Hi! What's up?"}, {"Not much. Hanging out on my floor.", "Doing homework. Or pretending to."}, {"Sure! Text me where.", "Yeah, why not? I'm free!"}, {"The elevator played music today. Nobody knows why.", "A bot waved at me. I waved back. Felt rude not to."}, {"Night!", "Goodnight. See you tomorrow!"}},
    // 3 teen
    {{"Hey.", "Yo. What's up?"}, {"Not much. You?", "Busy. Not too busy for you."}, {"Maybe. Text me the details.", "Sure. If it's not boring."}, {"Nothing fun. Okay, one thing. It was funny.", "The elevator got stuck. Everyone clapped when it moved."}, {"Night.", "Go to sleep."}},
    // 4 adult
    {{"Hello, Amir.", "Good to hear from you."}, {"Working. As always.", "Fixing something that was fixed yesterday."}, {"Perhaps later. Work first.", "I'd like that. Let me finish this."}, {"A watch has been ticking backward for ten years. Nobody noticed.", "The building was quiet today. That's a good sign."}, {"Good night, Amir.", "Sleep well."}},
};
static std::string phReply(const std::string& k, int opt) {
    for (auto& s : PH_SPECIAL) if (k == s.key) return s.r[opt];
    int c = phCat(k);
    size_t h = std::hash<std::string>()(k) + g.day + g.chapter;
    return PH_CAT[c][opt][h % 2];
}
static void phPushIncoming() {
    long dk = g.chapter * 1000L + g.day;
    if (dk == phLastDay) return; phLastDay = dk;
    if (PH_CONTACTS.empty()) phBuildContacts();
    if (PH_CONTACTS.empty()) return;
    std::string k = PH_CONTACTS[(g.chapter * 7 + g.day * 13) % PH_CONTACTS.size()];
    static const char* inc[3] = {"Hey Amir, are you around?", "Did you see the lights flicker? Weird day.", "Text me when you're free!"};
    CharDef* c = charBy(k); if (!c) return;
    std::string t = inc[(g.day + g.chapter) % 3];
    for (auto& s : PH_SPECIAL) if (k == s.key) t = s.r[0];
    PH_MSG[k].push_back({false, t}); PH_UNREAD.insert(k); phSave();
    toast("New text from " + c->name + "  (Y: phone)");
}
static void phOpen() { g.mode = M_PHONE; phView = 0; g.sel = 0; if (PH_CONTACTS.empty()) phBuildContacts(); }
static void phUpdate(const Input& in) {
    int n = (int)PH_CONTACTS.size();
    if (phPendT > 0 && --phPendT == 0) {
        PH_MSG[phPendKey].push_back({false, phReply(phPendKey, phPendOpt)});
        if (!(g.mode == M_PHONE && phView == 1 && phKey == phPendKey)) PH_UNREAD.insert(phPendKey);
        phPendKey.clear(); phSave();
    }
    if (phView == 0) {
        if (in.hit(B_UP)) g.sel = (g.sel + n - 1) % n;
        if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % n;
        if (in.hit(B_L)) g.sel = std::max(0, g.sel - 6);
        if (in.hit(B_R)) g.sel = std::min(n - 1, g.sel + 6);
        if (in.hit(B_A) && n) { phKey = PH_CONTACTS[g.sel]; phView = 1; PH_UNREAD.erase(phKey); g.sel = 0; }
        if (in.hit(B_B) || in.hit(B_Y)) g.mode = M_PLAY;
    } else {
        if (in.hit(B_UP)) g.sel = (g.sel + 4) % 5;
        if (in.hit(B_DOWN)) g.sel = (g.sel + 1) % 5;
        if (in.hit(B_A) && phPendKey.empty()) {
            PH_MSG[phKey].push_back({true, PH_OPTS[g.sel]});
            phPendKey = phKey; phPendOpt = g.sel; phPendT = 70; phSave();
        }
        if (in.hit(B_B)) { int i = 0; for (; i < n; i++) if (PH_CONTACTS[i] == phKey) break; phView = 0; g.sel = i % std::max(1, n); }
        PH_UNREAD.erase(phKey);
    }
}
static void drawPhone() {
    rect(0, 0, SCR_W, SCR_H, C(10, 12, 24));
    rect(380, 24, 520, 672, C(24, 26, 40)); frameR(380, 24, 520, 672, C(230, 230, 240), 4);
    rect(396, 60, 488, 600, C(240, 244, 250));
    rect(396, 60, 488, 46, C(60, 120, 210));
    CharDef* kc = phView == 1 ? charBy(phKey) : nullptr;
    text(phView == 0 ? "MESSAGES" : (kc ? kc->name : "?"), 640, 72, 1.8f, WHITE, 1, 2);
    int n = (int)PH_CONTACTS.size();
    if (phView == 0) {
        int vis = 9, top = std::max(0, std::min(n - vis, g.sel - 4));
        for (int r = 0; r < vis && top + r < n; r++) {
            int i = top + r; CharDef* c = charBy(PH_CONTACTS[i]); if (!c) continue;
            float y = 116 + r * 60; bool s = i == g.sel;
            rect(404, y, 472, 54, s ? C(190, 220, 255) : C(255, 255, 255)); frameR(404, y, 472, 54, s ? C(60, 120, 210) : C(210, 215, 225), 2);
            text(c->name, 424, y + 8, 1.6f, C(20, 30, 50));
            text(c->id, 424, y + 31, 1.0f, C(110, 120, 140));
            auto it = PH_MSG.find(c->key);
            if (it != PH_MSG.end() && !it->second.empty()) { std::string l = it->second.back().txt; if (l.size() > 20) l = l.substr(0, 20) + ".."; text(l, 868, y + 20, 1.0f, C(110, 120, 140), 2); }
            if (PH_UNREAD.count(c->key)) rect(852, y + 6, 14, 14, C(240, 60, 60));
            HITS.push_back({404, y, 472, 54, 0, i});
        }
        text("A Open   Up/Down   B Close", 640, 670, 1.0f, C(180, 185, 200), 1);
    } else {
        auto& msgs = PH_MSG[phKey];
        int shown = 0; float y = 118;
        size_t start = msgs.size() > 6 ? msgs.size() - 6 : 0;
        for (size_t i = start; i < msgs.size(); i++, shown++) {
            auto ls = wrapText(msgs[i].txt, 30);
            float h = 16 + ls.size() * 22;
            float x = msgs[i].mine ? 884 - 360 : 408;
            rect(x, y, 360, h, msgs[i].mine ? C(60, 120, 210) : C(220, 225, 235));
            for (size_t j = 0; j < ls.size(); j++) text(ls[j], x + 10, y + 8 + j * 22, 1.2f, msgs[i].mine ? WHITE : C(20, 30, 50));
            y += h + 8;
        }
        if (!phPendKey.empty() && phPendKey == phKey) { rect(408, y, 90, 30, C(220, 225, 235)); text(std::string(((g.frame / 12) % 3) + 1, '.') , 424, y + 4, 1.6f, C(90, 100, 120)); }
        for (int i = 0; i < 5; i++) {
            float oy = 520 + i * 28 - 0; bool s = i == g.sel;
            rect(404, oy - 2, 472, 26, s ? C(60, 120, 210) : C(225, 230, 240));
            text(PH_OPTS[i], 640, oy + 2, 1.2f, s ? WHITE : C(30, 40, 60), 1);
            HITS.push_back({404, oy - 2, 472, 26, 0, i});
        }
    }
}
