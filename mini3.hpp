// mini3.hpp - touch-friendly minigames: whack, pairs, lights, slide, popcorn, quiz
// Every one of these works with tap/touch, D-pad+A, or the stick. All of them play themselves when TEST_AI is on.
#pragma once

static const Col BOARD_BG = C(18, 28, 58);
static void boardBG(const std::string& title, const std::string& sub) {
    rect(0, 0, SCR_W, SCR_H, BOARD_BG);
    for (int x = 0; x < SCR_W; x += 40) rect(x, 0, 1, SCR_H, C(255, 255, 255, 14));
    for (int y = 0; y < SCR_H; y += 40) rect(0, y, SCR_W, 1, C(255, 255, 255, 14));
    rect(0, 0, SCR_W, 74, C(10, 16, 36)); rect(0, 72, SCR_W, 3, ORANGE);
    text(title, 36, 14, 2.4f, WHITE, 0, 4);
    text(sub, 36, 48, 1.2f, C(190, 210, 255), 0);
}
static bool tapIn(const Input& in, float x, float y, float w, float h) {
    for (auto& t : in.taps) if (t.first >= x && t.first <= x + w && t.second >= y && t.second <= y + h) return true;
    return false;
}

// ---------------------------------------------------------------- WHACK-A-BOT
struct Whack : Mini {
    struct H { int state = 0, t = 0; };   // 0 empty 1 bot 2 dust bomb
    H hs[12];
    int need, secs, lvl, hits, lives, timeLeft, spawnT, sel, flash;
    Whack(int n, int s, int l) : need(n), secs(s), lvl(l) {
        title = "Whack-a-Bot"; touch = true;
        hint = "Tap the Cleaning bots as they pop up. Don't tap the dust bombs! Hit " + std::to_string(n) + " bots in " + std::to_string(s) + " seconds. Touch, or D-pad + A.";
    }
    void reset() override { for (auto& h : hs) h = H(); hits = 0; lives = 3; timeLeft = secs * 60; spawnT = 20; sel = 5; flash = 0; }
    void cell(int i, float& x, float& y) { x = 220 + (i % 4) * 280; y = 250 + (i / 4) * 160; }
    void hitCell(int i) {
        if (hs[i].state == 1) { hits++; hs[i].state = 0; flash = 6; }
        else if (hs[i].state == 2) { lives--; hs[i].state = 0; flash = -8; }
    }
    void play(const Input& in) override {
        if (in.hit(B_LEFT)) sel = (sel / 4) * 4 + (sel % 4 + 3) % 4;
        if (in.hit(B_RIGHT)) sel = (sel / 4) * 4 + (sel % 4 + 1) % 4;
        if (in.hit(B_UP)) sel = (sel + 8) % 12;
        if (in.hit(B_DOWN)) sel = (sel + 4) % 12;
        if (in.hit(B_A)) hitCell(sel);
        for (auto& t : in.taps) for (int i = 0; i < 12; i++) { float x, y; cell(i, x, y); if (hypotf(t.first - x, t.second - y) < 70) { sel = i; hitCell(i); } }
        int dur = std::max(34, 78 - lvl * 9), gap = std::max(14, 38 - lvl * 5);
        if (--spawnT <= 0) {
            spawnT = gap + rnd() % gap;
            int i = rnd() % 12;
            if (hs[i].state == 0) { hs[i].state = (rnd() % 100 < 22 + lvl * 3) ? 2 : 1; hs[i].t = dur; }
        }
        for (int i = 0; i < 12; i++) {
            if (hs[i].state && TEST_AI && hs[i].state == 1 && hs[i].t < dur - 6) hitCell(i);
            if (hs[i].state && --hs[i].t <= 0) hs[i].state = 0;
        }
        if (flash > 0) flash--; else if (flash < 0) flash++;
        if (hits >= need) win("Squeaky clean!");
        else if (lives <= 0) lose("Too many dust bombs!");
        else if (--timeLeft <= 0) lose("Time's up!");
    }
    void drawPlay() override {
        boardBG("WHACK-A-BOT", "Bots " + std::to_string(hits) + "/" + std::to_string(need) + "    Time " + std::to_string(timeLeft / 60) + "    Lives " + std::string(lives > 0 ? lives : 0, '*'));
        for (int i = 0; i < 12; i++) {
            float x, y; cell(i, x, y);
            fillCircle(x, y + 18, 64, C(8, 12, 26)); fillCircle(x, y + 12, 58, C(30, 44, 86));
            if (hs[i].state == 1) { float r = std::min(1.0f, (float)(hs[i].t) / 12.0f); drawBot(x, y + 40 + (1 - r) * 40, C(120 + (i * 37) % 130, 190, 120 + (i * 53) % 130), phaseT, 1); }
            else if (hs[i].state == 2) { fillCircle(x, y, 34, C(60, 60, 66)); fillCircle(x - 10, y - 8, 8, C(220, 220, 230)); rect(x - 4, y - 46, 8, 14, C(200, 150, 60)); text("DUST", x, y + 6, 1.1f, C(255, 90, 90), 1); }
            if (i == sel) frameR(x - 68, y - 56, 136, 130, WHITE, 3);
        }
        if (flash > 0) rect(0, 74, SCR_W, SCR_H, C(120, 255, 190, 28)); else if (flash < 0) rect(0, 74, SCR_W, SCR_H, C(255, 60, 60, 40));
    }
};

// ---------------------------------------------------------------- PAIRS (memory cards)
struct Pairs : Mini {
    struct Card { int sym; bool up = false, done = false; };
    std::vector<Card> cs; int n, lives0, lives, a, b, wait, sel, cols;
    Pairs(int pairs, int l) : n(std::max(3, std::min(10, pairs))), lives0(l) {
        title = "Pairs"; touch = true;
        hint = "Flip two cards to find all " + std::to_string(n) + " matching pairs. You can miss " + std::to_string(l) + " times. Touch, or D-pad + A.";
    }
    void reset() override {
        cs.clear(); for (int i = 0; i < n; i++) { cs.push_back({i}); cs.push_back({i}); }
        for (int i = (int)cs.size() - 1; i > 0; i--) std::swap(cs[i], cs[rnd() % (i + 1)]);
        lives = lives0; a = b = -1; wait = 0; sel = 0; cols = n <= 4 ? 4 : (n <= 6 ? 4 : 5);
    }
    void pos(int i, float& x, float& y) {
        int rows = ((int)cs.size() + cols - 1) / cols;
        float cw = 150, ch = 150, gx = 20, gy = 18;
        float tw = cols * cw + (cols - 1) * gx, th = rows * ch + (rows - 1) * gy;
        x = 640 - tw / 2 + (i % cols) * (cw + gx); y = 110 + (680 - 110 - th) / 2 + (i / cols) * (ch + gy);
    }
    void flip(int i) {
        if (wait > 0 || cs[i].up || cs[i].done) return;
        cs[i].up = true;
        if (a < 0) a = i; else { b = i; wait = 44; }
    }
    void play(const Input& in) override {
        int N = (int)cs.size();
        if (in.hit(B_LEFT)) sel = (sel + N - 1) % N;
        if (in.hit(B_RIGHT)) sel = (sel + 1) % N;
        if (in.hit(B_UP)) sel = (sel + N - cols) % N;
        if (in.hit(B_DOWN)) sel = (sel + cols) % N;
        if (in.hit(B_A)) flip(sel);
        for (auto& t : in.taps) for (int i = 0; i < N; i++) { float x, y; pos(i, x, y); if (t.first >= x && t.first <= x + 150 && t.second >= y && t.second <= y + 150) { sel = i; flip(i); } }
        if (TEST_AI && wait == 0 && phaseT % 14 == 0) {
            if (a < 0) { for (int i = 0; i < N; i++) if (!cs[i].done && !cs[i].up) { flip(i); break; } }
            else { for (int i = 0; i < N; i++) if (i != a && !cs[i].done && !cs[i].up && cs[i].sym == cs[a].sym) { flip(i); break; } }
        }
        if (wait > 0 && --wait == 0) {
            if (cs[a].sym == cs[b].sym) { cs[a].done = cs[b].done = true; }
            else { cs[a].up = cs[b].up = false; lives--; }
            a = b = -1;
        }
        bool all = true; for (auto& c : cs) if (!c.done) all = false;
        if (all) win("Every pair found!");
        else if (lives < 0) lose("Out of tries!");
    }
    void drawPlay() override {
        boardBG("PAIRS", "Misses left: " + std::to_string(std::max(0, lives)));
        static const Col pc[10] = {C(255, 210, 80), C(120, 190, 255), C(255, 140, 120), C(255, 130, 220), C(130, 255, 130), C(190, 190, 200), C(250, 250, 250), C(150, 120, 220), C(255, 160, 60), C(90, 220, 220)};
        for (int i = 0; i < (int)cs.size(); i++) {
            float x, y; pos(i, x, y);
            if (cs[i].done) { rect(x, y, 150, 150, C(30, 90, 70, 160)); }
            if (cs[i].up || cs[i].done) { rect(x, y, 150, 150, C(240, 244, 255)); drawBot(x + 75, y + 112, pc[cs[i].sym], phaseT, 1); }
            else { rect(x, y, 150, 150, C(40, 60, 130)); frameR(x + 8, y + 8, 134, 134, C(120, 150, 230), 2); text("14", x + 75, y + 54, 3, C(120, 150, 230), 1); }
            if (i == sel) frameR(x - 4, y - 4, 158, 158, WHITE, 3);
        }
    }
};

// ---------------------------------------------------------------- LIGHTS (toggle puzzle)
struct Lights : Mini {
    int s, moves, maxMoves, sel; std::vector<int> g2, sol;
    Lights(int size, int extra) : s(std::max(3, std::min(5, size))), maxMoves(0) {
        title = "Light Switches"; touch = true; (void)extra;
        hint = "Tap a switch to flip it and its neighbours. Turn every light ON. Touch, or D-pad + A.";
    }
    void press(int i) { int x = i % s, y = i / s; auto f = [&](int xx, int yy) { if (xx >= 0 && yy >= 0 && xx < s && yy < s) g2[yy * s + xx] ^= 1; }; f(x, y); f(x - 1, y); f(x + 1, y); f(x, y - 1); f(x, y + 1); }
    void reset() override {
        g2.assign(s * s, 1); sol.clear(); moves = 0; sel = 0;
        int k = s + 2;
        std::vector<int> ps; for (int i = 0; i < s * s; i++) ps.push_back(i);
        for (int i = (int)ps.size() - 1; i > 0; i--) std::swap(ps[i], ps[rnd() % (i + 1)]);
        for (int i = 0; i < k; i++) { press(ps[i]); sol.push_back(ps[i]); }
        bool allOn = true; for (int v : g2) if (!v) allOn = false;
        if (allOn) { press(0); sol.push_back(0); }
        maxMoves = (int)sol.size() + 8;
    }
    void play(const Input& in) override {
        int N = s * s;
        if (in.hit(B_LEFT)) sel = (sel / s) * s + (sel % s + s - 1) % s;
        if (in.hit(B_RIGHT)) sel = (sel / s) * s + (sel % s + 1) % s;
        if (in.hit(B_UP)) sel = (sel + N - s) % N;
        if (in.hit(B_DOWN)) sel = (sel + s) % N;
        auto doPress = [&](int i) { press(i); moves++; };
        if (in.hit(B_A)) doPress(sel);
        float cell = 130, ox = 640 - s * cell / 2, oy = 410 - s * cell / 2;
        for (auto& t : in.taps) for (int i = 0; i < N; i++) { float x = ox + (i % s) * cell, y = oy + (i / s) * cell; if (t.first >= x && t.first < x + cell && t.second >= y && t.second < y + cell) { sel = i; doPress(i); } }
        if (TEST_AI && phaseT % 10 == 0 && !sol.empty()) { doPress(sol.back()); sol.pop_back(); }
        bool all = true; for (int v : g2) if (!v) all = false;
        if (all) win("Lights on!");
        else if (moves >= maxMoves) lose("Out of moves!");
    }
    void drawPlay() override {
        boardBG("LIGHT SWITCHES", "Moves " + std::to_string(moves) + " / " + std::to_string(maxMoves));
        float cell = 130, ox = 640 - s * cell / 2, oy = 410 - s * cell / 2;
        for (int i = 0; i < s * s; i++) {
            float x = ox + (i % s) * cell, y = oy + (i / s) * cell;
            bool on = g2[i] != 0;
            rect(x + 5, y + 5, cell - 10, cell - 10, on ? C(255, 210, 90) : C(30, 40, 80));
            if (on) fillCircle(x + cell / 2, y + cell / 2, 26, C(255, 245, 190)); else fillCircle(x + cell / 2, y + cell / 2, 18, C(18, 26, 56));
            if (i == sel) frameR(x + 2, y + 2, cell - 4, cell - 4, WHITE, 3);
        }
    }
};

// ---------------------------------------------------------------- SLIDE (3x3 sliding puzzle)
struct Slide : Mini {
    int t[9]; int blank; std::vector<int> hist; int timeLeft, secs;
    Slide(int s) : secs(s) { title = "Sliding Panel"; touch = true; hint = "Slide the panels back into order 1-8. Tap a panel next to the gap, or use the D-pad. " + std::to_string(s) + " seconds."; }
    bool mv(int dir) {   // dir: 0 up 1 down 2 left 3 right (moves the blank)
        int bx = blank % 3, by = blank / 3, nx = bx + (dir == 3) - (dir == 2), ny = by + (dir == 1) - (dir == 0);
        if (nx < 0 || ny < 0 || nx > 2 || ny > 2) return false;
        int ni = ny * 3 + nx; std::swap(t[blank], t[ni]); blank = ni; return true;
    }
    void reset() override {
        for (int i = 0; i < 9; i++) t[i] = i; blank = 8; hist.clear(); timeLeft = secs * 60;
        int last = -1;
        for (int k = 0; k < 40; k++) { int d = rnd() % 4; if (last >= 0 && d == (last ^ 1)) continue; if (mv(d)) { hist.push_back(d); last = d; } }
    }
    void play(const Input& in) override {
        // D-pad moves the panel the way you push it (so the gap moves the opposite way)
        if (in.hit(B_UP)) mv(1);
        if (in.hit(B_DOWN)) mv(0);
        if (in.hit(B_LEFT)) mv(3);
        if (in.hit(B_RIGHT)) mv(2);
        for (auto& tp : in.taps) for (int i = 0; i < 9; i++) {
            float x = 640 - 225 + (i % 3) * 150, y = 400 - 225 + (i / 3) * 150;
            if (tp.first >= x && tp.first < x + 150 && tp.second >= y && tp.second < y + 150 && t[i] != 8) {
                int bx = blank % 3, by = blank / 3, cx = i % 3, cy = i / 3;
                if (abs(bx - cx) + abs(by - cy) == 1) { if (cy < by) mv(0); else if (cy > by) mv(1); else if (cx < bx) mv(2); else mv(3); }
            }
        }
        if (TEST_AI && phaseT % 6 == 0 && !hist.empty()) { int d = hist.back(); hist.pop_back(); mv(d ^ 1); }
        bool ok = true; for (int i = 0; i < 9; i++) if (t[i] != i) ok = false;
        if (ok) win("Panel fixed!");
        else if (--timeLeft <= 0) lose("Time's up!");
    }
    void drawPlay() override {
        boardBG("SLIDING PANEL", "Time " + std::to_string(timeLeft / 60));
        for (int i = 0; i < 9; i++) {
            float x = 640 - 225 + (i % 3) * 150, y = 400 - 225 + (i / 3) * 150;
            if (t[i] == 8) { rect(x + 4, y + 4, 142, 142, C(10, 16, 36)); continue; }
            rect(x + 4, y + 4, 142, 142, C(60, 100, 200)); frameR(x + 4, y + 4, 142, 142, C(160, 190, 255), 3);
            text(std::to_string(t[i] + 1), x + 75, y + 40, 4.5f, WHITE, 1);
        }
    }
};

// ---------------------------------------------------------------- POPCORN (catch; touch moves the bucket)
struct Popcorn : Mini {
    struct K { float x, y, v; bool burnt; };
    std::vector<K> ks; float bx, tx; int caught, need, miss, missMax, spawnT, lvl;
    Popcorn(int n, int l, int level) : need(n), missMax(l), lvl(level) { title = "Popcorn Catch"; touch = true; hint = "Catch " + std::to_string(n) + " popcorn in the bucket. Skip the burnt ones! Move the stick, or tap where the bucket should go."; }
    void reset() override { ks.clear(); bx = tx = 640; caught = 0; miss = 0; spawnT = 20; }
    void play(const Input& in) override {
        for (auto& t : in.taps) tx = t.first;
        if (fabsf(in.ax) > 0.2f) tx = bx + in.ax * 60;
        if (TEST_AI) { float best = 1e9; for (auto& k : ks) if (!k.burnt && k.y > 120 && 700 - k.y < best) { best = 700 - k.y; tx = k.x; } }
        float d = tx - bx; bx += std::max(-12.0f, std::min(12.0f, d * 0.4f)); bx = std::max(80.0f, std::min(1200.0f, bx));
        if (--spawnT <= 0) { spawnT = std::max(14, 38 - lvl * 5) + rnd() % 14; ks.push_back({90 + rndf() * 1100, 80, 3.2f + lvl * 0.6f + rndf() * 1.2f, rnd() % 100 < 18 + lvl * 3}); }
        for (size_t i = 0; i < ks.size();) {
            ks[i].y += ks[i].v;
            if (ks[i].y > 600 && ks[i].y < 650 && fabsf(ks[i].x - bx) < 70) { if (ks[i].burnt) miss++; else caught++; ks.erase(ks.begin() + i); continue; }
            if (ks[i].y > 700) { if (!ks[i].burnt) miss++; ks.erase(ks.begin() + i); continue; }
            i++;
        }
        if (caught >= need) win("Popcorn secured!");
        else if (miss > missMax) lose("Too many dropped!");
    }
    void drawPlay() override {
        boardBG("POPCORN CATCH", "Caught " + std::to_string(caught) + "/" + std::to_string(need) + "    Mistakes left " + std::to_string(std::max(0, missMax - miss)));
        for (auto& k : ks) { if (k.burnt) { fillCircle(k.x, k.y, 18, C(40, 30, 30)); fillCircle(k.x - 4, k.y - 4, 6, C(90, 70, 60)); } else { fillCircle(k.x, k.y, 18, C(255, 245, 210)); fillCircle(k.x - 6, k.y - 5, 8, C(255, 230, 150)); } }
        rect(bx - 56, 610, 112, 74, C(220, 50, 60)); for (int i = 0; i < 4; i++) rect(bx - 56 + i * 28, 610, 14, 74, C(255, 255, 255));
        rect(bx - 62, 604, 124, 10, C(240, 240, 240));
    }
};

// ---------------------------------------------------------------- QUIZ (tap an answer)
struct QItem { const char* q; const char* a[3]; int right; };
static const QItem QUIZ_SCHOOL[] = {
    {"What is 7 x 8?", {"54", "56", "64"}, 1}, {"Capital city of Algeria?", {"Oran", "Algiers", "Annaba"}, 1}, {"Sea north of Algeria?", {"Mediterranean", "Red Sea", "Black Sea"}, 0},
    {"How do you say 'hello' in French?", {"Merci", "Bonjour", "Salut-pas"}, 1}, {"A triangle has how many sides?", {"3", "4", "5"}, 0}, {"H2O is...", {"Salt", "Water", "Sugar"}, 1},
    {"12 + 30 = ?", {"42", "32", "52"}, 0}, {"Planet we live on?", {"Mars", "Earth", "Venus"}, 1},
};
static const QItem QUIZ_CINEMA[] = {
    {"You hold a ticket. Where do you sit?", {"Row on your ticket", "On the screen", "In the projector"}, 0}, {"Popcorn is made from...", {"Rice", "Corn", "Beans"}, 1}, {"What does the director say before a scene?", {"Action!", "Dinner!", "Snack!"}, 0},
    {"The big white thing movies show on?", {"Screen", "Fridge", "Door"}, 0}, {"What do you do with your phone in a cinema?", {"Silence it", "Call everyone", "Throw it"}, 0}, {"Credits roll at the...", {"Start", "End", "Middle"}, 1},
    {"3D movies need...", {"Glasses", "Gloves", "Hats"}, 0}, {"Who stays for the post-credits scene?", {"Real fans", "Nobody", "Only popcorn"}, 0},
};
static const QItem QUIZ_ILOT[] = {
    {"What floor is the Lobby?", {"0", "5", "-8"}, 0}, {"Who owns Bolt?", {"Dalia", "Amir", "Gabriel"}, 1}, {"Which floor is Further Inn on?", {"Roof", "Bottom (-8)", "Main"}, 1},
    {"Prime is bot number...", {"00", "06", "99"}, 0}, {"Gabriel always carries a...", {"Rope", "Umbrella", "Guitar"}, 0}, {"Dalia's bot is called...", {"Mopsy", "Zed", "Grim"}, 0},
    {"Which floor does Amine live on?", {"Special", "Rare", "Teen"}, 0}, {"What colour is the 14 sign?", {"Orange", "Green", "Pink"}, 0},
};
struct Quiz : Mini {
    std::vector<QItem> qs; int need, idx, sel, right, fb, lastPick, topic; std::vector<int> perm;
    Quiz(int n, const std::string& topicName) : need(n) {
        title = topicName == "cinema" ? "Movie Quiz" : topicName == "school" ? "Pop Quiz" : "Îlot14 Quiz"; touch = true;
        topic = topicName == "cinema" ? 1 : topicName == "school" ? 0 : 2;
        hint = "Answer " + std::to_string(n) + " questions. Tap an answer, or D-pad + A. You need " + std::to_string((n * 6 + 9) / 10) + " right.";
    }
    void reset() override {
        const QItem* src = topic == 1 ? QUIZ_CINEMA : topic == 0 ? QUIZ_SCHOOL : QUIZ_ILOT;
        qs.assign(src, src + 8);
        for (int i = (int)qs.size() - 1; i > 0; i--) std::swap(qs[i], qs[rnd() % (i + 1)]);
        qs.resize(std::min<size_t>(qs.size(), (size_t)need)); idx = 0; sel = 0; right = 0; fb = 0; lastPick = -1;
    }
    void pick(int i) {
        if (fb > 0) return;
        lastPick = i; fb = 36;
        if (i == qs[idx].right) right++;
    }
    void play(const Input& in) override {
        if (fb > 0) {
            if (--fb == 0) {
                idx++;
                int total = (int)qs.size();
                if (idx >= total) { if (right >= (total * 6 + 9) / 10) win("Top of the class!"); else lose("Only " + std::to_string(right) + " right."); }
                lastPick = -1;
            }
            return;
        }
        if (in.hit(B_UP)) sel = (sel + 2) % 3;
        if (in.hit(B_DOWN)) sel = (sel + 1) % 3;
        if (in.hit(B_A)) pick(sel);
        for (auto& t : in.taps) for (int i = 0; i < 3; i++) if (t.first > 240 && t.first < 1040 && t.second > 300 + i * 110 && t.second < 390 + i * 110) { sel = i; pick(i); }
        if (TEST_AI && phaseT % 20 == 0) pick(qs[idx].right);
    }
    void drawPlay() override {
        boardBG(title, "Question " + std::to_string(std::min(idx + 1, (int)qs.size())) + " / " + std::to_string(qs.size()) + "    Right: " + std::to_string(right));
        if (idx >= (int)qs.size()) return;
        auto ls = wrapText(qs[idx].q, 40);
        for (size_t i = 0; i < ls.size(); i++) text(ls[i], 640, 150 + i * 44, 2.6f, WHITE, 1);
        for (int i = 0; i < 3; i++) {
            float y = 300 + i * 110;
            Col bg = C(40, 70, 150);
            if (fb > 0) { if (i == qs[idx].right) bg = C(40, 150, 90); else if (i == lastPick) bg = C(170, 50, 60); }
            rect(240, y, 800, 90, bg); frameR(240, y, 800, 90, i == sel && fb == 0 ? WHITE : C(150, 180, 255), i == sel ? 4 : 2);
            text(qs[idx].a[i], 640, y + 28, 2.4f, WHITE, 1);
        }
    }
};
