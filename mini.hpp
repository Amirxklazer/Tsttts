// mini.hpp - minigames: roundup, timing, fight, catch, maze (backrooms), roof (platformer)
#pragma once
#include "data.hpp"

static bool TEST_AI = false;      // test mode: minigames play themselves
static int g_miniStars = 0;       // result extras (roof stars etc.)

struct Mini {
    std::string title = "Minigame", hint = "";
    int phase = 0;        // 0 intro, 1 play, 2 result
    int phaseT = 0;
    bool won = false, ended = false, finished = false, skipped = false;
    std::string resultMsg;
    virtual ~Mini() {}
    virtual void reset() = 0;
    virtual void play(const Input& in) = 0;
    virtual void drawPlay() = 0;

    void win(const std::string& m = "Nice work!") { ended = true; won = true; resultMsg = m; }
    void lose(const std::string& m = "Not this time...") { ended = true; won = false; resultMsg = m; }

    void update(const Input& in) {
        phaseT++;
        if (phase == 0) {
            if (in.hit(B_A) || (TEST_AI && phaseT > 5)) { phase = 1; phaseT = 0; ended = false; reset(); }
        } else if (phase == 1) {
            play(in);
            if (ended) { phase = 2; phaseT = 0; }
        } else {
            if (phaseT > 20 && (in.hit(B_A) || (TEST_AI && phaseT > 40))) {
                if (won) finished = true;
                else { phase = 1; phaseT = 0; ended = false; reset(); }
            }
            if (!won && in.hit(B_Y)) { won = true; skipped = true; finished = true; }
        }
    }
    void draw() {
        if (phase != 0) drawPlay();
        else rect(0, 0, SCR_W, SCR_H, C(18, 22, 40));
        if (phase == 0) {
            rect(0, 0, SCR_W, SCR_H, C(20, 40, 90));
            frameR(140, 120, 1000, 480, WHITE, 4);
            dashH(160, 190, 960, C(255, 255, 255, 120));
            text("MINIGAME", 640, 140, 1.4f, C(255, 255, 255, 170), 1, 6);
            text(title, 640, 220, 3, ORANGE, 1);
            auto ls = wrapText(hint, 52);
            for (size_t i = 0; i < ls.size(); i++) text(ls[i], 640, 330 + i * 40, 2, WHITE, 1);
            text("Press A to start", 640, 520, 2, C(255, 255, 255, 150 + (int)(100 * sinf(phaseT * 0.1f))), 1);
        } else if (phase == 2) {
            rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, 150));
            rect(240, 220, 800, 280, won ? C(20, 90, 60) : C(100, 30, 40));
            frameR(240, 220, 800, 280, WHITE, 4);
            text(won ? "SUCCESS!" : "FAILED", 640, 250, 4, WHITE, 1, 6);
            text(resultMsg, 640, 350, 2, WHITE, 1);
            if (phaseT > 20) text(won ? "A  Continue" : "A  Retry     Y  Skip", 640, 430, 2, C(255, 255, 255, 200), 1);
        }
    }
};

// ---------------------------------------------------------------- ROUNDUP
struct Roundup : Mini {
    struct B { float x, y, vx, vy; Col c; };
    std::vector<B> bots;
    float px, py; int caught, need, timeLeft, secs, cd, flash, dir;
    Roundup(int n, int s) : need(n), secs(s) {
        title = "Bot Roundup";
        hint = "Catch " + std::to_string(n) + " runaway Cleaning bots in " + std::to_string(s) + " seconds. Move: stick / D-pad. Grab: A.";
    }
    void reset() override {
        bots.clear(); px = 640; py = 400; caught = 0; timeLeft = secs * 60; cd = 0; flash = 0; dir = 1;
        Col cs[] = {C(255, 210, 80), C(120, 190, 255), C(255, 140, 120), C(255, 130, 220), C(130, 255, 130), C(190, 190, 200), C(255, 255, 255), C(110, 90, 160)};
        for (int i = 0; i < need + 3; i++) {
            float a = rndf() * 6.28f;
            bots.push_back({100 + rndf() * 1080, 180 + rndf() * 440, cosf(a) * 2, sinf(a) * 2, cs[i % 8]});
        }
    }
    void play(const Input& in) override {
        float mx = in.ax, my = in.ay;
        if (TEST_AI && !bots.empty()) {
            float best = 1e9; B* t = nullptr;
            for (auto& b : bots) { float d = hypotf(b.x - px, b.y - py); if (d < best) { best = d; t = &b; } }
            mx = t->x - px; my = t->y - py;
            float l = hypotf(mx, my); if (l > 1) { mx /= l; my /= l; }
        }
        px = std::min(1230.0f, std::max(50.0f, px + mx * 7)); py = std::min(660.0f, std::max(170.0f, py + my * 7));
        if (mx > 0.2f) dir = 1; else if (mx < -0.2f) dir = -1;
        if (cd > 0) cd--;
        bool grab = in.hit(B_A) || (TEST_AI && cd == 0);
        if (grab && cd == 0) {
            cd = 14; flash = 8;
            for (size_t i = 0; i < bots.size();) {
                if (hypotf(bots[i].x - px, bots[i].y - py) < 75) { bots.erase(bots.begin() + i); caught++; }
                else i++;
            }
        }
        if (flash > 0) flash--;
        for (auto& b : bots) {
            if (rnd() % 90 == 0) { float a = rndf() * 6.28f; b.vx = cosf(a) * 2.2f; b.vy = sinf(a) * 2.2f; }
            float d = hypotf(b.x - px, b.y - py);
            float sp = 1;
            if (d < 170) { b.vx += (b.x - px) / d * 0.25f; b.vy += (b.y - py) / d * 0.25f; sp = 1.0f; }
            float l = hypotf(b.vx, b.vy);
            float mxs = d < 170 ? 3.6f : 2.4f;
            if (l > mxs) { b.vx *= mxs / l; b.vy *= mxs / l; }
            b.x += b.vx * sp; b.y += b.vy * sp;
            if (b.x < 60 || b.x > 1220) { b.vx = -b.vx; b.x = std::min(1220.0f, std::max(60.0f, b.x)); }
            if (b.y < 170 || b.y > 660) { b.vy = -b.vy; b.y = std::min(660.0f, std::max(170.0f, b.y)); }
        }
        if (caught >= need) win("All bots rounded up!");
        else if (--timeLeft <= 0) lose("Time's up! Some bots got away.");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(60, 75, 95));
        for (int x = 0; x < SCR_W; x += 80) rect(x, 120, 2, 600, C(255, 255, 255, 25));
        for (int y = 120; y < SCR_H; y += 80) rect(0, y, SCR_W, 2, C(255, 255, 255, 25));
        rect(0, 0, SCR_W, 120, C(30, 40, 60));
        for (auto& b : bots) drawBot(b.x, b.y, b.c, phaseT, b.vx >= 0 ? 1 : -1, true);
        Look l = playerLook();
        drawPerson(px, py + 4, dir, l, phaseT, true);
        if (flash > 0) frameR(px - 75, py - 75, 150, 150, C(255, 255, 255, 40 + flash * 20), 3);
        text("CAUGHT " + std::to_string(caught) + "/" + std::to_string(need), 40, 40, 2.4f, WHITE);
        text("TIME " + std::to_string(timeLeft / 60 + 1), SCR_W - 40, 40, 2.4f, timeLeft < 600 ? C(255, 120, 120) : WHITE, 2);
        text("A: grab nearby bots", 640, 85, 1.4f, C(255, 255, 255, 160), 1);
    }
};

// ---------------------------------------------------------------- TIMING
struct Timing : Mini {
    int need, lives0, lives, hits; float pos, vel, zoneX, zoneW; std::string label; int flash; bool lastHit;
    Timing(int n, int l, std::string lab) : need(n), lives0(l), label(lab) {
        title = "Timing: " + lab;
        hint = "Press A when the marker is inside the green zone. Hit it " + std::to_string(n) + " times. You can miss " + std::to_string(l - 1) + " times.";
    }
    void reset() override {
        lives = lives0; hits = 0; pos = 0; vel = 9; zoneW = 170; zoneX = 300 + rndf() * 400; flash = 0; lastHit = false;
    }
    void play(const Input& in) override {
        pos += vel;
        if (pos > 800) { pos = 800; vel = -fabsf(vel); }
        if (pos < 0) { pos = 0; vel = fabsf(vel); }
        if (flash > 0) flash--;
        bool press = in.hit(B_A);
        if (TEST_AI && pos > zoneX + zoneW * 0.3f && pos < zoneX + zoneW * 0.7f) press = true;
        if (press) {
            if (pos >= zoneX && pos <= zoneX + zoneW) {
                hits++; lastHit = true; flash = 20;
                vel = (vel > 0 ? 1 : -1) * (fabsf(vel) + 1.0f);
                zoneW = std::max(100.0f, zoneW - 12);
                zoneX = rndf() * (800 - zoneW);
            } else {
                lives--; lastHit = false; flash = 20;
            }
        }
        if (hits >= need) win("Perfect rhythm!");
        else if (lives <= 0) lose("Too many misses.");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(35, 50, 100));
        dashH(60, 150, 1160, C(255, 255, 255, 90)); dashH(60, 570, 1160, C(255, 255, 255, 90));
        text(label, 640, 60, 3, WHITE, 1);
        float bx = 240, by = 320;
        rect(bx, by, 800, 70, C(10, 15, 40));
        rect(bx + zoneX, by, zoneW, 70, C(60, 220, 120));
        frameR(bx, by, 800, 70, WHITE, 3);
        rect(bx + pos - 4, by - 22, 8, 114, flash > 0 ? (lastHit ? C(120, 255, 160) : C(255, 90, 90)) : ORANGE);
        text("HITS " + std::to_string(hits) + "/" + std::to_string(need), 640, 480, 2.4f, WHITE, 1);
        std::string hearts;
        for (int i = 0; i < lives0; i++) hearts += i < lives ? "<3 " : "-- ";
        text(hearts, 640, 530, 2, C(255, 140, 160), 1);
    }
};

// ---------------------------------------------------------------- FIGHT
struct Fight : Mini {
    struct E { float x, y, vx, vy; int hp, maxhp; float ph; bool boss; };
    std::vector<E> es;
    float px, py; int dir, hp, hp0, toSpawn, total, killed, inv, swing, cd, spawnT; std::string label; bool boss; float bossScale;
    Fight(int n, int h, std::string lab) : total(n), hp0(h), label(lab) {
        boss = lab.rfind("boss", 0) == 0;
        title = boss ? "Boss Fight" : "Fight: " + lab;
        hint = boss ? "Beat the boss! A swings around you. Dodge its hits." : "Swat all " + std::to_string(n) + " " + lab + "! A swings around you. Don't get stung - you have " + std::to_string(h) + " hearts.";
    }
    void reset() override {
        es.clear(); px = 640; py = 420; dir = 1; hp = hp0; killed = 0; inv = 0; swing = 0; cd = 0; spawnT = 0;
        toSpawn = boss ? 1 : total;
    }
    void spawn() {
        int side = rndi(0, 3); float x, y;
        if (side == 0) { x = -20; y = rndi(150, 650); } else if (side == 1) { x = 1300; y = rndi(150, 650); }
        else if (side == 2) { x = rndi(0, 1280); y = 110; } else { x = rndi(0, 1280); y = 740; }
        if (boss) { es.push_back({640, 200, 0, 0, 14, 14, 0, true}); }
        else es.push_back({x, y, 0, 0, 1, 1, rndf() * 6.28f, false});
        toSpawn--;
    }
    void play(const Input& in) override {
        float mx = in.ax, my = in.ay;
        if (TEST_AI && !es.empty()) {
            float best = 1e9; E* t = nullptr;
            for (auto& e : es) { float d = hypotf(e.x - px, e.y - py); if (d < best) { best = d; t = &e; } }
            float want = boss ? 95 : 70;
            mx = t->x - px; my = t->y - py; float l = hypotf(mx, my);
            if (l < want) { mx = -mx; my = -my; }
            if (l > 1) { mx /= l; my /= l; }
        }
        px = std::min(1240.0f, std::max(40.0f, px + mx * 6)); py = std::min(670.0f, std::max(170.0f, py + my * 6));
        if (mx > 0.2f) dir = 1; else if (mx < -0.2f) dir = -1;
        if (cd > 0) cd--;
        if (inv > 0) inv--;
        if (swing > 0) swing--;
        bool atk = in.hit(B_A);
        if (TEST_AI) { for (auto& e : es) if (hypotf(e.x - px, e.y - py) < (boss ? 135 : 100)) atk = true; }
        if (atk && cd == 0) {
            cd = boss ? 18 : 22; swing = 8;
            float rad = boss ? 140 : 110;
            for (auto& e : es) if (hypotf(e.x - px, e.y - py) < rad + (e.boss ? 40 : 0)) {
                e.hp--; float dx = e.x - px, dy = e.y - py, l = std::max(1.0f, hypotf(dx, dy));
                e.x += dx / l * (e.boss ? 25 : 60); e.y += dy / l * (e.boss ? 25 : 60);
            }
            for (size_t i = 0; i < es.size();) { if (es[i].hp <= 0) { es.erase(es.begin() + i); killed++; } else i++; }
        }
        spawnT++;
        int maxAlive = boss ? 1 : 5;
        if (toSpawn > 0 && (int)es.size() < maxAlive && spawnT > 25) { spawn(); spawnT = 0; }
        for (auto& e : es) {
            e.ph += 0.2f;
            float dx = px - e.x, dy = py - e.y, l = std::max(1.0f, hypotf(dx, dy));
            float sp = e.boss ? 2.2f : 2.6f;
            e.x += dx / l * sp + cosf(e.ph) * (e.boss ? 0.5f : 1.8f);
            e.y += dy / l * sp + sinf(e.ph * 1.3f) * (e.boss ? 0.5f : 1.8f);
            float hitR = e.boss ? 52 : 30;
            if (inv == 0 && l < hitR) { hp--; inv = 75; px -= dx / l * 40; py -= dy / l * 40; }
        }
        if (killed >= total || (boss && killed >= 1)) win("All clear!");
        else if (hp <= 0) lose("You got swarmed.");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, boss ? C(70, 60, 90) : C(95, 150, 85));
        rect(0, 0, SCR_W, 130, boss ? C(40, 35, 60) : C(130, 190, 235));
        rect(0, 130, SCR_W, 6, C(0, 0, 0, 60));
        for (int i = 0; i < 24; i++) rect((i * 97) % 1280, 160 + (i * 61) % 520, 14, 6, C(255, 255, 255, 25));
        Look l = playerLook();
        if (inv == 0 || (inv / 4) % 2 == 0) drawPerson(px, py + 4, dir, l, phaseT, true);
        if (swing > 0) {
            float rad = boss ? 140 : 110;
            fillCircle(px, py - 40, rad, C(255, 255, 255, 25 + swing * 6));
        }
        for (auto& e : es) {
            if (e.boss) {
                drawBot(e.x, e.y + 30, C(255, 120, 30), phaseT, e.x < px ? 1 : -1, false);
                rect(e.x - 60, e.y - 90, 120, 12, C(40, 0, 0)); rect(e.x - 58, e.y - 88, 116.0f * e.hp / e.maxhp, 8, C(255, 80, 60));
            } else {
                float wob = sinf(phaseT * 1.2f + e.ph) * 5;
                rect(e.x - 16, e.y - 24 + wob, 12, 8, C(220, 240, 255, 180));
                rect(e.x + 4, e.y - 24 - wob, 12, 8, C(220, 240, 255, 180));
                rect(e.x - 14, e.y - 14, 28, 18, C(250, 210, 30));
                rect(e.x - 6, e.y - 14, 5, 18, BLACK); rect(e.x + 5, e.y - 14, 5, 18, BLACK);
                rect(e.x + (e.x < px ? 10 : -14), e.y - 10, 5, 5, C(220, 30, 30));
                rect(e.x + (e.x < px ? 14 : -18), e.y + 2, 4, 4, BLACK);
            }
        }
        std::string hearts;
        for (int i = 0; i < hp0; i++) hearts += i < hp ? "<3 " : "-- ";
        text(hearts, 40, 40, 2.4f, C(255, 90, 120));
        text(boss ? "BOSS" : label + " " + std::to_string(killed) + "/" + std::to_string(total), SCR_W - 40, 40, 2.4f, WHITE, 2);
    }
};

// ---------------------------------------------------------------- CATCH
struct Catch : Mini {
    struct It { float x, y, v; bool good; };
    std::vector<It> its;
    float px; int need, got, lives0, lives, t, flash; std::string label, initial;
    Catch(int n, int l, std::string lab) : need(n), lives0(l), label(lab) {
        title = "Catch: " + lab;
        hint = "Catch " + std::to_string(n) + " falling " + lab + " in your basket. Skip the grey junk! Move: stick / D-pad. " + std::to_string(l) + " lives.";
        initial = lab.substr(0, 1);
        for (auto& c : initial) c = toupper(c);
    }
    void reset() override { its.clear(); px = 640; got = 0; lives = lives0; t = 0; flash = 0; }
    void play(const Input& in) override {
        float mx = in.ax;
        if (TEST_AI) {
            float best = 1e9; It* tg = nullptr;
            for (auto& i : its) if (i.good && i.y < 620 && 620 - i.y < best) { best = 620 - i.y; tg = &i; }
            mx = 0; if (tg) mx = (tg->x - px) / 12.0f; mx = std::max(-1.0f, std::min(1.0f, mx));
        }
        px = std::min(1200.0f, std::max(80.0f, px + mx * 10));
        t++;
        if (flash > 0) flash--;
        int interval = 38;
        if (t % interval == 0) its.push_back({100 + rndf() * 1080, 140, 4.5f + rndf() * 2.0f, (rnd() % 100) >= 22});
        for (size_t i = 0; i < its.size();) {
            auto& it = its[i];
            it.y += it.v;
            bool rm = false;
            if (it.y > 600 && it.y < 650 && fabsf(it.x - px) < 78) {
                rm = true;
                if (it.good) got++; else { lives--; flash = 12; }
            } else if (it.y > 720) {
                rm = true;
                if (it.good) { lives--; flash = 12; }
            }
            if (rm) its.erase(its.begin() + i); else i++;
        }
        if (got >= need) win("Got them all!");
        else if (lives <= 0) lose("Out of lives.");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(70, 50, 110));
        for (int i = 0; i < 16; i++) rect(i * 80 + 38, 130, 2, 590, C(255, 255, 255, 18));
        rect(0, 0, SCR_W, 130, C(35, 25, 60));
        for (auto& it : its) {
            if (it.good) { rect(it.x - 20, it.y - 20, 40, 40, ORANGE); frameR(it.x - 20, it.y - 20, 40, 40, WHITE, 2); text(initial, it.x, it.y - 12, 1.6f, BLACK, 1); }
            else { rect(it.x - 18, it.y - 18, 36, 36, C(110, 110, 120)); text("x", it.x, it.y - 12, 1.6f, C(30, 30, 30), 1); }
        }
        rect(px - 70, 610, 140, 14, C(180, 120, 60)); rect(px - 70, 610, 12, 40, C(140, 90, 40)); rect(px + 58, 610, 12, 40, C(140, 90, 40));
        rect(px - 70, 650, 140, 12, C(140, 90, 40));
        text("CAUGHT " + std::to_string(got) + "/" + std::to_string(need), 40, 40, 2.4f, WHITE);
        std::string hearts;
        for (int i = 0; i < lives0; i++) hearts += i < lives ? "<3 " : "-- ";
        text(hearts, SCR_W - 40, 40, 2.4f, flash > 0 ? C(255, 255, 255) : C(255, 120, 150), 2);
    }
};

// ---------------------------------------------------------------- MAZE (Backrooms)
struct Maze : Mini {
    static const int CW = 17, CH = 11, CS = 64, OX = 96, OY = 8;
    unsigned char walls[CH][CW]; // bits: 1 N, 2 E, 4 S, 8 W (set = wall)
    struct Bt { float x, y; bool got; };
    std::vector<Bt> bottles;
    std::vector<SDL_FRect> rects;
    float px, py, stamina; int need, got, seed; bool exitOpen; int tick;
    std::vector<int> aiPath; // for test ai
    Maze(int n, int sd) : need(n), seed(sd) {
        title = "Backrooms Escape";
        hint = "The hum is draining you. Grab " + std::to_string(n) + " almond waters to keep your strength, then reach the glowing exit door.";
    }
    void gen() {
        u32 saved = rngState; rngState = 7777 + seed * 131;
        for (int y = 0; y < CH; y++) for (int x = 0; x < CW; x++) walls[y][x] = 15;
        bool vis[CH][CW] = {};
        std::vector<std::pair<int, int>> st; st.push_back({0, 0}); vis[0][0] = true;
        while (!st.empty()) {
            int x = st.back().first, y = st.back().second;
            int dirs[4] = {0, 1, 2, 3}; for (int i = 3; i > 0; i--) std::swap(dirs[i], dirs[rnd() % (i + 1)]);
            bool moved = false;
            for (int k = 0; k < 4; k++) {
                int d = dirs[k]; int nx = x + (d == 1) - (d == 3), ny = y + (d == 2) - (d == 0);
                if (nx < 0 || ny < 0 || nx >= CW || ny >= CH || vis[ny][nx]) continue;
                walls[y][x] &= ~(1 << d); walls[ny][nx] &= ~(1 << ((d + 2) % 4));
                vis[ny][nx] = true; st.push_back({nx, ny}); moved = true; break;
            }
            if (!moved) st.pop_back();
        }
        // knock out some extra walls so it isn't a pure tree
        for (int i = 0; i < 18; i++) {
            int x = rndi(1, CW - 2), y = rndi(1, CH - 2), d = rndi(0, 3);
            int nx = x + (d == 1) - (d == 3), ny = y + (d == 2) - (d == 0);
            walls[y][x] &= ~(1 << d); walls[ny][nx] &= ~(1 << ((d + 2) % 4));
        }
        rects.clear();
        float T = 6;
        for (int y = 0; y < CH; y++) for (int x = 0; x < CW; x++) {
            float cx = OX + x * CS, cy = OY + y * CS;
            if (walls[y][x] & 1) rects.push_back({cx - T / 2, cy - T / 2, CS + T, T});
            if (walls[y][x] & 8) rects.push_back({cx - T / 2, cy - T / 2, T, CS + T});
            if (y == CH - 1 && (walls[y][x] & 4)) rects.push_back({cx - T / 2, cy + CS - T / 2, CS + T, T});
            if (x == CW - 1 && (walls[y][x] & 2)) rects.push_back({cx + CS - T / 2, cy - T / 2, T, CS + T});
            if (y < CH - 1 && (walls[y][x] & 4)) rects.push_back({cx - T / 2, cy + CS - T / 2, CS + T, T});
            if (x < CW - 1 && (walls[y][x] & 2)) rects.push_back({cx + CS - T / 2, cy - T / 2, T, CS + T});
        }
        bottles.clear();
        for (int i = 0; i < need; i++) {
            int lo = std::min(2 + i * 3, CW - 3), hi = std::min(CW - 2, 4 + i * 4); int bx = rndi(lo, std::max(lo, hi)), by = rndi(0, CH - 1);
            bottles.push_back({(float)(OX + bx * CS + CS / 2), (float)(OY + by * CS + CS / 2), false});
        }
        rngState = saved;
    }
    bool blocked(float x, float y, float r) {
        for (auto& w : rects)
            if (x + r > w.x && x - r < w.x + w.w && y + r > w.y && y - r < w.y + w.h) return true;
        return false;
    }
    void reset() override {
        gen(); px = OX + CS / 2; py = OY + CS / 2; stamina = 100; got = 0; exitOpen = need == 0; tick = 0;
        for (auto& b : bottles) b.got = false;
        buildPath();
    }
    // BFS over cells for AI: visit bottles then exit
    void buildPath() {
        aiPath.clear();
        std::vector<std::pair<int, int>> goals;
        for (auto& b : bottles) goals.push_back({(int)((b.x - OX) / CS), (int)((b.y - OY) / CS)});
        goals.push_back({CW - 1, CH - 1});
        int cx = 0, cy = 0;
        for (auto& g : goals) {
            int prev[CH][CW]; for (int y = 0; y < CH; y++) for (int x = 0; x < CW; x++) prev[y][x] = -2;
            std::vector<std::pair<int, int>> q; q.push_back({cx, cy}); prev[cy][cx] = -1;
            for (size_t h = 0; h < q.size(); h++) {
                int x = q[h].first, y = q[h].second;
                for (int d = 0; d < 4; d++) {
                    if (walls[y][x] & (1 << d)) continue;
                    int nx = x + (d == 1) - (d == 3), ny = y + (d == 2) - (d == 0);
                    if (nx < 0 || ny < 0 || nx >= CW || ny >= CH || prev[ny][nx] != -2) continue;
                    prev[ny][nx] = y * CW + x; q.push_back({nx, ny});
                }
            }
            std::vector<int> seg; int x = g.first, y = g.second;
            while (prev[y][x] >= 0) { seg.push_back(y * CW + x); int p = prev[y][x]; x = p % CW; y = p / CW; }
            std::reverse(seg.begin(), seg.end());
            for (int c : seg) aiPath.push_back(c);
            cx = g.first; cy = g.second;
        }
    }
    void play(const Input& in) override {
        tick++;
        float mx = in.ax, my = in.ay;
        if (TEST_AI && !aiPath.empty()) {
            int c = aiPath.front();
            float tx = OX + (c % CW) * CS + CS / 2, ty = OY + (c / CW) * CS + CS / 2;
            mx = tx - px; my = ty - py; float l = hypotf(mx, my);
            if (l < 8) { aiPath.erase(aiPath.begin()); mx = my = 0; } else { mx /= l; my /= l; }
        }
        float sp = stamina > 20 ? 4.6f : 3.2f;
        float nx = px + mx * sp; if (!blocked(nx, py, 13)) px = nx;
        float ny = py + my * sp; if (!blocked(px, ny, 13)) py = ny;
        stamina -= 0.035f;
        for (auto& b : bottles) if (!b.got && hypotf(b.x - px, b.y - py) < 30) { b.got = true; got++; stamina = std::min(100.0f, stamina + 35); }
        exitOpen = got >= need;
        float ex = OX + (CW - 1) * CS + CS / 2, ey = OY + (CH - 1) * CS + CS / 2;
        if (exitOpen && hypotf(ex - px, ey - py) < 36) win("You found the way out.");
        else if (stamina <= 0) lose("The hum swallowed you whole. You wake up where you started.");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(10, 10, 4));
        for (int y = 0; y < CH; y++) for (int x = 0; x < CW; x++) {
            float cx = OX + x * CS + CS / 2.0f, cy = OY + y * CS + CS / 2.0f;
            float d = hypotf(cx - px, cy - py);
            float f = d < 190 ? 1.0f : d < 300 ? 1.0f - (d - 190) / 130.0f * 0.8f : 0.14f;
            rect(OX + x * CS, OY + y * CS, CS, CS, dim(((x + y) & 1) ? C(190, 170, 70) : C(176, 156, 62), f));
        }
        for (auto& w : rects) {
            float d = hypotf(w.x + w.w / 2 - px, w.y + w.h / 2 - py);
            float f = d < 190 ? 1.0f : d < 300 ? 1.0f - (d - 190) / 130.0f * 0.85f : 0.1f;
            rect(w.x, w.y, w.w, w.h, dim(C(110, 95, 30), f));
        }
        for (auto& b : bottles) if (!b.got) {
            float d = hypotf(b.x - px, b.y - py); float f = d < 300 ? 1 : 0.3f;
            rect(b.x - 7, b.y - 14, 14, 28, dim(C(120, 200, 255), f)); rect(b.x - 4, b.y - 19, 8, 6, dim(WHITE, f));
        }
        float ex = OX + (CW - 1) * CS + CS / 2, ey = OY + (CH - 1) * CS + CS / 2;
        rect(ex - 18, ey - 24, 36, 48, exitOpen ? C(120, 255, 190, 230) : C(60, 60, 60));
        if (exitOpen) fillCircle(ex, ey, 40 + sinf(tick * 0.1f) * 5, C(120, 255, 190, 50));
        Look l = playerLook(); l.h *= 0.5f; l.tag14 = false;
        drawPerson(px, py + 16, 1, l, tick, true);
        // HUD
        rect(20, 10, 260, 22, C(0, 0, 0, 180)); rect(24, 14, 252.0f * std::max(0.0f, stamina) / 100, 14, stamina > 30 ? C(120, 220, 255) : C(255, 90, 90));
        text("ALMOND " + std::to_string(got) + "/" + std::to_string(need), 300, 8, 1.8f, WHITE);
        text(exitOpen ? "EXIT OPEN" : "EXIT LOCKED", SCR_W - 20, 8, 1.8f, exitOpen ? C(120, 255, 190) : C(200, 200, 200), 2);
    }
};

// ---------------------------------------------------------------- ROOF (platformer)
struct Roof : Mini {
    struct P { float x, y, w, h; };
    std::vector<P> plats;
    struct Star { float x, y; bool got; };
    std::vector<Star> stars;
    float px, py, vx, vy, camX, endX; bool onGround; int diff, tick, coyote, cx0; float spawnX, spawnY; int starsGot;
    Roof(int d) : diff(d) {
        title = "Roof Run";
        hint = "Cross the roof and reach the flag. Move: stick / D-pad. Jump: A or B (hold for higher). Grab stars if you can. Falling just sends you back.";
    }
    void gen() {
        u32 saved = rngState; rngState = 4242 + diff * 77;
        plats.clear(); stars.clear();
        float x = 0, gy = 560;
        plats.push_back({0, gy, 520, 300});
        x = 520;
        int segs = 0;
        while (x < 3000) {
            float gap = rndi(100 + diff * 15, 135 + diff * 20);
            float ny = gy + rndi(-70, 60); ny = std::min(600.0f, std::max(430.0f, ny));
            if (ny < gy) gap = std::min(gap, 135.0f);
            if (gap > 150) plats.push_back({x + gap / 2 - 50, std::min(gy, ny) - 70, 100, 18});
            float len = rndi(260, 480);
            plats.push_back({x + gap, ny, len, 300});
            if (segs % 2 == 1 && stars.size() < 5) stars.push_back({x + gap + len / 2, ny - 90, false});
            x += gap + len; gy = ny; segs++;
        }
        while (stars.size() < 5) { stars.push_back({3000 - 300.0f * (5 - (int)stars.size()), 300, false}); }
        // final stretch
        plats.push_back({x + 120, gy, 560, 300});
        endX = x + 120 + 440;
        rngState = saved;
    }
    void reset() override {
        gen(); px = 80; py = 480; vx = vy = 0; camX = 0; onGround = false; tick = 0; coyote = 0; spawnX = 80; spawnY = 480; starsGot = 0;
        for (auto& s : stars) s.got = false;
    }
    bool hitsAny(float x, float y, float w, float h) {
        for (auto& p : plats) if (x < p.x + p.w && x + w > p.x && y < p.y + p.h && y + h > p.y) return true;
        return false;
    }
    void play(const Input& in) override {
        tick++;
        float mx = in.ax; bool jumpHeld = in.down(B_A) || in.down(B_B) || in.down(B_UP);
        bool jumpHit = in.hit(B_A) || in.hit(B_B) || in.hit(B_UP);
        if (TEST_AI) {
            mx = 1;
            bool ground = false, step = false;
            for (auto& p : plats) {
                if (px + 14 + 60 > p.x && px + 14 + 60 < p.x + p.w && p.y >= py + 56 - 6 && p.y < py + 56 + 120) ground = true;
                if (px + 28 + 40 > p.x && px + 28 + 40 < p.x + p.w && p.y < py + 56 - 6 && p.y > py - 160) step = true;
            }
            if (onGround && (!ground || step)) { jumpHit = true; }
            jumpHeld = true;
        }
        vx = mx * 5.4f;
        if (onGround) coyote = 6; else if (coyote > 0) coyote--;
        if (jumpHit && coyote > 0) { vy = -15.5f; onGround = false; coyote = 0; }
        if (!jumpHeld && vy < -6) vy = -6;
        vy = std::min(16.0f, vy + 0.75f);
        // move x
        px += vx; if (px < 0) px = 0;
        if (hitsAny(px, py, 28, 56)) { px -= vx; for (int i = 0; i < 6 && hitsAny(px, py, 28, 56); i++) px -= (vx > 0 ? 1 : -1); }
        // move y
        py += vy; onGround = false;
        if (hitsAny(px, py, 28, 56)) {
            if (vy > 0) { while (hitsAny(px, py, 28, 56)) py -= 1; onGround = true; spawnX = px; spawnY = py - 20; }
            else { while (hitsAny(px, py, 28, 56)) py += 1; }
            vy = 0;
        }
        if (py > 860) { px = std::max(40.0f, spawnX - 60); py = spawnY - 40; vy = 0; camX = std::max(0.0f, px - 400); }
        camX += ((px - 420) - camX) * 0.12f; if (camX < 0) camX = 0;
        for (auto& s : stars) if (!s.got && fabsf(s.x - (px + 14)) < 34 && fabsf(s.y - (py + 28)) < 44) { s.got = true; starsGot++; }
        if (px + 28 >= endX) { g_miniStars = starsGot; win("Made it across! Stars: " + std::to_string(starsGot) + "/5"); }
    }
    void drawPlay() override {
        for (int y = 0; y < SCR_H; y += 8) rect(0, y, SCR_W, 8, mix(C(70, 120, 210), C(255, 190, 140), y / 720.0f));
        fillCircle(1000 - camX * 0.02f, 160, 60, C(255, 240, 200, 200));
        for (int i = 0; i < 9; i++) { // far skyline
            float bx = i * 220 - fmodf(camX * 0.25f, 220) - 40;
            rect(bx, 380 + (i % 3) * 40, 150, 340, C(60, 80, 140, 200));
            for (int k = 0; k < 6; k++) rect(bx + 20 + (k % 2) * 60, 410 + (i % 3) * 40 + (k / 2) * 60, 24, 30, C(255, 230, 140, 120));
        }
        for (auto& p : plats) {
            float sx = p.x - camX;
            if (sx > SCR_W || sx + p.w < 0) continue;
            rect(sx, p.y, p.w, p.h, p.h > 100 ? C(88, 92, 108) : C(150, 150, 170));
            rect(sx, p.y, p.w, 10, C(190, 195, 215));
            if (p.h > 100) { for (int k = 0; k < p.w; k += 90) rect(sx + k + 20, p.y + 40, 50, 80, C(70, 74, 90)); }
        }
        for (auto& s : stars) if (!s.got) {
            float sx = s.x - camX, by = s.y + sinf(tick * 0.1f + s.x) * 6;
            rect(sx - 4, by - 18, 8, 36, C(255, 220, 60)); rect(sx - 18, by - 4, 36, 8, C(255, 220, 60));
            rect(sx - 10, by - 10, 20, 20, C(255, 240, 150));
        }
        float fx = endX - camX;
        rect(fx, 280, 6, 280, C(220, 220, 230)); rect(fx + 6, 284, 70, 44, ORANGE); text("14", fx + 41, 292, 1.8f, BLACK, 1);
        Look l = playerLook(); l.h *= 0.9f;
        drawPerson(px + 14 - camX, py + 56, 1, l, tick, fabsf(vx) > 0.1f && onGround);
        text("STARS " + std::to_string(starsGot) + "/5", 40, 30, 2.2f, WHITE);
        rect(SCR_W - 340, 36, 300, 10, C(0, 0, 0, 120));
        rect(SCR_W - 340, 36, 300.0f * std::min(1.0f, px / endX), 10, ORANGE);
    }
};

// ---------------------------------------------------------------- factory
static Mini* makeMini(const std::vector<std::string>& a) {
    auto ai = [&](size_t i, int d) { return a.size() > i ? atoi(a[i].c_str()) : d; };
    auto as = [&](size_t i, const char* d) { std::string s = a.size() > i ? a[i] : d; for (auto& c : s) if (c == '_') c = ' '; return s; };
    if (a.empty()) return nullptr;
    const std::string& k = a[0];
    if (k == "roundup") return new Roundup(ai(1, 5), ai(2, 45));
    if (k == "timing") return new Timing(ai(1, 5), ai(2, 3), as(3, "Timing"));
    if (k == "fight") return new Fight(ai(1, 8), ai(2, 5), as(3, "hornets"));
    if (k == "catch") return new Catch(ai(1, 10), ai(2, 3), as(3, "items"));
    if (k == "maze") return new Maze(ai(1, 3), ai(2, 1));
    if (k == "roof") return new Roof(ai(1, 1));
    return nullptr;
}
