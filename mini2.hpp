// mini2.hpp - newer minigames: simon (memory), sneak (stealth), rhythm, dodge (bullet arena), defend (lane defence)
// Included by mini.hpp. All of them play themselves when TEST_AI is on.
#pragma once

// buttons shared by simon + rhythm: 0 UP/X, 1 RIGHT/A, 2 DOWN/B, 3 LEFT/Y
static bool padHit(const Input& in, int p) {
    switch (p) {
        case 0: return in.hit(B_UP) || in.hit(B_X);
        case 1: return in.hit(B_RIGHT) || in.hit(B_A);
        case 2: return in.hit(B_DOWN) || in.hit(B_B);
        default: return in.hit(B_LEFT) || in.hit(B_Y);
    }
}
static Col padColor(int p) {
    static const Col cs[4] = {C(80, 220, 120), C(240, 80, 80), C(80, 150, 255), C(250, 210, 70)};
    return cs[p & 3];
}

// ---------------------------------------------------------------- SIMON (memory)
struct Simon : Mini {
    int rounds, lives0, lives, len, shown, step, flashT, flashPad, speed, mode, wait, bad;   // mode 0 showing, 1 input
    std::vector<int> seq;
    Simon(int r, int l, int sp) : rounds(r), lives0(l), speed(sp) {
        title = "Memory Pads";
        hint = "Watch the pads light up, then repeat the order. D-pad or face buttons (Up/X, Right/A, Down/B, Left/Y). Reach a sequence of " + std::to_string(r) + ". " + std::to_string(l) + " lives.";
    }
    void newSeq() { seq.clear(); for (int i = 0; i < rounds; i++) seq.push_back(rndi(0, 3)); }
    void reset() override { lives = lives0; len = 2; newSeq(); startShow(); bad = 0; }
    void startShow() { mode = 0; shown = 0; flashT = 0; flashPad = -1; wait = 40; step = 0; }
    void play(const Input& in) override {
        if (bad > 0) bad--;
        if (mode == 0) {
            if (wait > 0) { wait--; return; }
            if (flashT > 0) { flashT--; if (flashT == 0) { flashPad = -1; wait = std::max(6, speed / 3); shown++; } return; }
            if (shown >= len) { mode = 1; step = 0; wait = 10; return; }
            flashPad = seq[shown]; flashT = speed;
        } else {
            if (wait > 0) { wait--; return; }
            int p = -1;
            if (TEST_AI) { if (phaseT % 9 == 0) p = seq[step]; }
            else for (int i = 0; i < 4; i++) if (padHit(in, i)) p = i;
            if (p < 0) return;
            flashPad = p; flashT = 10;
            if (p == seq[step]) {
                step++;
                if (step >= len) {
                    if (len >= rounds) { win("Perfect memory!"); return; }
                    len++; startShow(); wait = 50;
                }
            } else {
                lives--; bad = 20;
                if (lives <= 0) { lose("Out of lives."); return; }
                startShow(); wait = 60;
            }
        }
        if (mode == 1 && flashT > 0) { flashT--; if (flashT == 0) flashPad = -1; }
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, bad > 0 ? C(70, 30, 40) : C(28, 34, 62));
        rect(0, 0, SCR_W, 110, C(15, 18, 36));
        text(mode == 0 ? "WATCH..." : "YOUR TURN", 640, 36, 2.6f, mode == 0 ? C(255, 220, 120) : C(120, 255, 190), 1);
        text("LENGTH " + std::to_string(len) + "/" + std::to_string(rounds), 40, 40, 2, WHITE);
        std::string h; for (int i = 0; i < lives0; i++) h += i < lives ? "<3 " : "-- ";
        text(h, SCR_W - 40, 40, 2.2f, C(255, 110, 140), 2);
        float cx = 640, cy = 400, d = 135;
        float px[4] = {cx, cx + d, cx, cx - d}, py[4] = {cy - d, cy, cy + d, cy};
        const char* lab[4] = {"X", "A", "B", "Y"};
        for (int i = 0; i < 4; i++) {
            Col c = padColor(i); bool on = flashPad == i;
            rect(px[i] - 100, py[i] - 100, 200, 200, on ? c : C(c.r / 3, c.g / 3, c.b / 3));
            frameR(px[i] - 100, py[i] - 100, 200, 200, on ? WHITE : C(255, 255, 255, 90), on ? 6 : 3);
            text(lab[i], px[i], py[i] - 20, 3.2f, on ? BLACK : C(255, 255, 255, 120), 1);
        }
        if (mode == 1) for (int i = 0; i < len; i++) rect(640 - len * 14 + i * 28, 650, 20, 10, i < step ? C(120, 255, 190) : C(255, 255, 255, 70));
    }
};

// ---------------------------------------------------------------- SNEAK (stealth)
struct Sneak : Mini {
    struct Gd { float x, y, base, amp, ph, w, range; };
    std::vector<Gd> gs;
    std::vector<SDL_FRect> crates;
    float px, py, meter; int lives0, lives, n, t, hit, dir; float lvl;
    Sneak(int guards, int l, int level) : lives0(l), n(guards), lvl(level) {
        title = "Sneak Past";
        hint = "Reach the glowing exit on the right without staying in the light beams. Hold A to crouch: slower, but harder to spot. " + std::to_string(l) + " lives.";
    }
    void reset() override {
        u32 saved = rngState; rngState = 4242 + n * 17 + (int)lvl * 3;
        gs.clear(); crates.clear();
        for (int i = 0; i < n; i++) {
            float x = 300 + (780.0f * (i + 0.5f)) / n;
            bool up = i % 2;
            gs.push_back({x, up ? 690.0f : 160.0f, up ? -1.5708f : 1.5708f, 0.75f + 0.1f * lvl, rndf() * 6.28f, 0.022f + 0.006f * lvl, 330});
        }
        for (int i = 0; i < 5; i++) crates.push_back({220.0f + i * 190 + rndf() * 40, 260.0f + rndf() * 250, 70, 70});
        rngState = saved;
        px = 70; py = 420; meter = 0; lives = lives0; t = 0; hit = 0; dir = 1;
    }
    bool blocked(float x, float y) {
        for (auto& c : crates) if (x > c.x - 12 && x < c.x + c.w + 12 && y > c.y - 6 && y < c.y + c.h + 26) return true;
        return false;
    }
    void play(const Input& in) override {
        t++; if (hit > 0) hit--;
        float mx = in.ax, my = in.ay;
        bool crouch = in.down(B_A);
        if (TEST_AI) { mx = 1; my = sinf(t * 0.05f) * 0.4f; crouch = false; }
        float sp = crouch ? 2.2f : 4.4f;
        float nx = std::min(1240.0f, std::max(30.0f, px + mx * sp)), ny = std::min(690.0f, std::max(170.0f, py + my * sp));
        if (TEST_AI || !blocked(nx, py)) px = nx;
        if (TEST_AI || !blocked(px, ny)) py = ny;
        if (mx > 0.2f) dir = 1; else if (mx < -0.2f) dir = -1;
        bool seen = false;
        for (auto& g : gs) {
            float a = g.base + g.amp * sinf(t * g.w + g.ph);
            float dx = px - g.x, dy = (py - 30) - g.y, d = hypotf(dx, dy);
            float da = fabsf(atan2f(dy, dx) - a); if (da > 3.14159f) da = 6.2832f - da;
            float rng = g.range * (crouch ? 0.72f : 1.0f);
            if (d < rng && da < 0.34f + (d < 90 ? 0.4f : 0)) seen = true;
        }
        if (seen && !TEST_AI) meter += crouch ? 1.1f : 2.0f; else meter = std::max(0.0f, meter - 1.4f);
        if (meter >= 100) {
            lives--; meter = 0; px = 70; py = 420; hit = 40;
            if (lives <= 0) { lose("You were spotted too many times."); return; }
        }
        if (px > 1190) win("Slipped by!");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(34, 36, 48));
        rect(0, 0, SCR_W, 130, C(18, 20, 30));
        for (int x = 0; x < SCR_W; x += 80) rect(x, 130, 2, 590, C(255, 255, 255, 14));
        for (int y = 130; y < SCR_H; y += 80) rect(0, y, SCR_W, 2, C(255, 255, 255, 14));
        rect(1190, 150, 90, 540, C(120, 255, 190, 40 + (int)(30 * sinf(t * 0.1f)))); frameR(1190, 150, 90, 540, C(120, 255, 190), 3);
        text("EXIT", 1235, 400, 1.8f, C(120, 255, 190), 1);
        for (auto& c : crates) { rect(c.x, c.y, c.w, c.h, C(120, 90, 60)); frameR(c.x, c.y, c.w, c.h, C(70, 50, 30), 3); }
        for (auto& g : gs) {
            float a = g.base + g.amp * sinf(t * g.w + g.ph);
            for (float da = -0.34f; da <= 0.34f; da += 0.04f)
                for (float r = 20; r < g.range; r += 28) fillCircle(g.x + cosf(a + da) * r, g.y + sinf(a + da) * r, 9, C(255, 240, 150, 40));
            fillCircle(g.x, g.y, 14, C(250, 250, 255)); fillCircle(g.x + cosf(a) * 8, g.y + sinf(a) * 8, 5, C(220, 40, 40));
        }
        if (hit == 0 || (hit / 4) % 2 == 0) drawPerson(px, py + 4, dir, playerLook(), t, true);
        rect(40, 90, 300, 18, C(0, 0, 0, 160)); rect(42, 92, 296.0f * std::min(100.0f, meter) / 100, 14, meter > 60 ? C(255, 80, 60) : C(255, 200, 60));
        text("SPOTTED", 40, 60, 1.3f, WHITE);
        std::string h; for (int i = 0; i < lives0; i++) h += i < lives ? "<3 " : "-- ";
        text(h, SCR_W - 40, 40, 2.2f, C(255, 110, 140), 2);
    }
};

// ---------------------------------------------------------------- RHYTHM
struct Rhythm : Mini {
    struct Nt { int lane, t; int state; };   // state 0 pending, 1 hit, 2 missed
    std::vector<Nt> notes;
    int total, maxMiss, bpm, t, hits, misses, combo, bestCombo, flash[4], judge, judgeT;
    static const int FALL = 70, LINE = 590;
    Rhythm(int n, int m, int b) : total(n), maxMiss(m), bpm(b) {
        title = "Rhythm";
        hint = "Press the matching button as each note reaches the line: Up/X, Right/A, Down/B, Left/Y. " + std::to_string(n) + " notes. You can miss " + std::to_string(m) + ".";
    }
    void reset() override {
        notes.clear(); t = -60; hits = misses = combo = bestCombo = 0; judge = 0; judgeT = 0;
        for (int i = 0; i < 4; i++) flash[i] = 0;
        u32 saved = rngState; rngState = 99 + total * 7 + bpm;
        int beat = std::max(12, 3600 / bpm), tt = 60, last = -1;
        for (int i = 0; i < total; i++) {
            int lane = rndi(0, 3); if (lane == last && rndi(0, 2)) lane = (lane + 1 + rndi(0, 2)) % 4;
            last = lane;
            notes.push_back({lane, tt, 0});
            bool fast = bpm >= 130 && rndi(0, 2) == 0;
            tt += fast ? beat / 2 : beat;
            if (bpm >= 150 && rndi(0, 5) == 0 && i + 1 < total) { int l2 = (lane + 1 + rndi(0, 2)) % 4; notes.push_back({l2, tt - (fast ? beat / 2 : beat), 0}); i++; }
        }
        total = (int)notes.size();
        rngState = saved;
    }
    void play(const Input& in) override {
        t++;
        for (int i = 0; i < 4; i++) if (flash[i] > 0) flash[i]--;
        if (judgeT > 0) judgeT--;
        for (int p = 0; p < 4; p++) {
            bool press = padHit(in, p);
            if (TEST_AI) for (auto& n : notes) if (n.state == 0 && n.lane == p && n.t == t) press = true;
            if (!press) continue;
            flash[p] = 8;
            Nt* best = nullptr; int bd = 99;
            for (auto& n : notes) if (n.state == 0 && n.lane == p) { int d = abs(n.t - t); if (d < bd) { bd = d; best = &n; } }
            if (best && bd <= 11) {
                best->state = 1; hits++; combo++; bestCombo = std::max(bestCombo, combo);
                judge = bd <= 4 ? 2 : 1; judgeT = 24;
            } else if (!best || bd > 11) { /* ghost press: no penalty */ }
        }
        for (auto& n : notes) if (n.state == 0 && t > n.t + 12) { n.state = 2; misses++; combo = 0; judge = 0; judgeT = 24; }
        if (misses > maxMiss) { lose("Too many missed notes."); return; }
        int done = 0; for (auto& n : notes) if (n.state) done++;
        if (done >= total) win(std::to_string(hits) + "/" + std::to_string(total) + " hit. Best combo " + std::to_string(bestCombo));
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(24, 20, 44));
        rect(0, 0, SCR_W, 110, C(12, 10, 26));
        float lx = 420, lw = 110;
        for (int i = 0; i < 4; i++) {
            float x = lx + i * lw;
            rect(x, 110, lw - 6, 610, C(255, 255, 255, 10));
            Col c = padColor(i);
            rect(x, LINE - 10, lw - 6, 20, flash[i] > 0 ? c : C(c.r / 2, c.g / 2, c.b / 2));
            frameR(x, LINE - 10, lw - 6, 20, WHITE, 2);
        }
        for (auto& n : notes) {
            if (n.state == 1) continue;
            float y = LINE - (n.t - t) * (LINE - 120.0f) / FALL;
            if (y < 100 || y > 700) continue;
            Col c = padColor(n.lane);
            rect(lx + n.lane * lw + 6, y - 14, lw - 18, 28, n.state == 2 ? C(90, 90, 90) : c);
            frameR(lx + n.lane * lw + 6, y - 14, lw - 18, 28, WHITE, 2);
        }
        text("HIT " + std::to_string(hits) + "/" + std::to_string(total), 40, 40, 2.2f, WHITE);
        text("MISS " + std::to_string(misses) + "/" + std::to_string(maxMiss), SCR_W - 40, 40, 2.2f, misses >= maxMiss ? C(255, 100, 100) : WHITE, 2);
        if (combo > 1) text(std::to_string(combo) + " COMBO", 640, 60, 2, C(255, 220, 120), 1);
        if (judgeT > 0) text(judge == 2 ? "PERFECT" : judge == 1 ? "GOOD" : "MISS", 220, 340, 2.4f, judge == 2 ? C(120, 255, 190) : judge == 1 ? C(255, 220, 120) : C(255, 100, 100), 1);
    }
};

// ---------------------------------------------------------------- DODGE (bullet arena)
struct Dodge : Mini {
    struct Bl { float x, y, vx, vy; float r; };
    std::vector<Bl> bs;
    float px, py; int secs, hearts0, hearts, lvl, t, inv, dash, dashCd, dir;
    Dodge(int s, int h, int level) : secs(s), hearts0(h), lvl(level) {
        title = "Dodge";
        hint = "Survive " + std::to_string(s) + " seconds. Move with the stick, press A to dash through danger. " + std::to_string(h) + " hearts.";
    }
    void reset() override { bs.clear(); px = 640; py = 420; hearts = hearts0; t = 0; inv = 0; dash = 0; dashCd = 0; dir = 1; }
    void ring(float x, float y, int n, float sp, float off) { for (int i = 0; i < n; i++) { float a = off + i * 6.2832f / n; bs.push_back({x, y, cosf(a) * sp, sinf(a) * sp, 9}); } }
    void play(const Input& in) override {
        t++;
        float mx = in.ax, my = in.ay;
        if (TEST_AI) { mx = my = 0; }
        float sp = dash > 0 ? 17 : 6;
        px = std::min(1250.0f, std::max(30.0f, px + mx * sp)); py = std::min(690.0f, std::max(170.0f, py + my * sp));
        if (mx > 0.2f) dir = 1; else if (mx < -0.2f) dir = -1;
        if (dash > 0) dash--;
        if (dashCd > 0) dashCd--;
        if (inv > 0) inv--;
        if (in.hit(B_A) && dashCd == 0) { dash = 8; dashCd = 70; inv = std::max(inv, 12); }
        float speedUp = 1.0f + 0.18f * (lvl - 1);
        // patterns
        if (t % std::max(40, 120 - lvl * 14) == 30) ring(160 + rndf() * 960, 200 + rndf() * 100, 10 + lvl * 2, 2.6f * speedUp, rndf() * 6.28f);
        if (lvl >= 2 && t % std::max(26, 70 - lvl * 8) == 0) {
            float sx = rndi(0, 1) ? 20 : 1260, sy = 170 + rndf() * 500, dx = px - sx, dy = py - 30 - sy, l = std::max(1.0f, hypotf(dx, dy));
            bs.push_back({sx, sy, dx / l * 4.4f * speedUp, dy / l * 4.4f * speedUp, 10});
        }
        if (lvl >= 3 && t % 90 == 45) { float cx = 100 + rndf() * 1080; for (int i = 0; i < 6; i++) bs.push_back({cx + (i - 3) * 38, 140.0f - i * 12, 0, 4.0f * speedUp, 11}); }
        if (lvl >= 4 && t % 140 == 70) ring(px, 160, 14, 3.2f, 0);
        for (size_t i = 0; i < bs.size();) {
            auto& b = bs[i]; b.x += b.vx; b.y += b.vy;
            bool dead = b.x < -40 || b.x > 1320 || b.y < 100 || b.y > 770;
            if (!dead && inv == 0 && !TEST_AI && hypotf(b.x - px, b.y - (py - 30)) < b.r + 16) { hearts--; inv = 70; dead = true; }
            if (dead) bs.erase(bs.begin() + i); else i++;
        }
        if (hearts <= 0) { lose("The hits were too many."); return; }
        if (t >= secs * 60) win("You made it through!");
    }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(40, 24, 50));
        rect(0, 0, SCR_W, 130, C(20, 12, 28));
        for (int x = 0; x < SCR_W; x += 80) rect(x, 130, 2, 590, C(255, 255, 255, 12));
        for (auto& b : bs) { fillCircle(b.x, b.y, b.r + 3, C(255, 140, 60, 70)); fillCircle(b.x, b.y, b.r, C(255, 210, 120)); }
        if (inv == 0 || (inv / 4) % 2 == 0) drawPerson(px, py + 4, dir, playerLook(), t, true);
        if (dash > 0) fillCircle(px, py - 30, 44, C(255, 255, 255, 50));
        std::string h; for (int i = 0; i < hearts0; i++) h += i < hearts ? "<3 " : "-- ";
        text(h, 40, 40, 2.4f, C(255, 90, 120));
        text("TIME " + std::to_string(std::max(0, secs - t / 60)), SCR_W - 40, 40, 2.4f, WHITE, 2);
        text(dashCd > 0 ? "DASH ..." : "A: DASH", 640, 85, 1.4f, dashCd > 0 ? C(255, 255, 255, 100) : C(120, 255, 190), 1);
    }
};

// ---------------------------------------------------------------- DEFEND (lane defence)
struct Defend : Mini {
    struct En { float x; int lane, hp, maxhp; float sp; };
    struct Sh { float x; int lane; };
    std::vector<En> es; std::vector<Sh> shots;
    int waves, coreHp0, coreHp, lvl, wave, toSpawn, spawnT, lane, cd, t, waveWait, killedWave;
    Defend(int w, int h, int level) : waves(w), coreHp0(h), lvl(level) {
        title = "Hold the Line";
        hint = "Dust wraiths march on the core. Up / Down switch lanes, A fires. Survive " + std::to_string(w) + " waves. The core can take " + std::to_string(h) + " hits.";
    }
    void reset() override { es.clear(); shots.clear(); coreHp = coreHp0; wave = 0; lane = 1; cd = 0; t = 0; waveWait = 60; toSpawn = 0; spawnT = 0; killedWave = 0; }
    void play(const Input& in) override {
        t++;
        if (cd > 0) cd--;
        int want = lane;
        if (TEST_AI) {
            float best = 1e9; for (auto& e : es) if (e.x < best) { best = e.x; want = e.lane; }
            if (lane != want && t % 6 == 0) lane += want > lane ? 1 : -1;
        } else {
            if (in.hit(B_UP)) lane = std::max(0, lane - 1);
            if (in.hit(B_DOWN)) lane = std::min(2, lane + 1);
        }
        bool fire = in.hit(B_A) || (TEST_AI && lane == want);
        if (fire && cd == 0) { shots.push_back({300, lane}); cd = lvl >= 3 ? 9 : 13; }
        // waves
        if (toSpawn == 0 && es.empty()) {
            if (waveWait > 0) waveWait--;
            else if (wave >= waves) { win("The line held!"); return; }
            else { wave++; toSpawn = 4 + wave * 2 + lvl; spawnT = 0; waveWait = 80; }
        }
        spawnT++;
        if (toSpawn > 0 && spawnT > std::max(20, 52 - wave * 4 - lvl * 4)) {
            spawnT = 0; toSpawn--;
            int hp = 1; if (lvl >= 2 && rndi(0, 3) == 0) hp = 2; if (lvl >= 3 && rndi(0, 5) == 0) hp = 4;
            es.push_back({1320, rndi(0, 2), hp, hp, 1.2f + 0.07f * wave + 0.15f * lvl + rndf() * 0.4f});
        }
        for (auto& s : shots) s.x += 14;
        for (auto& e : es) e.x -= e.sp;
        for (size_t i = 0; i < shots.size();) {
            bool used = false;
            for (auto& e : es) if (e.lane == shots[i].lane && fabsf(e.x - shots[i].x) < 34) { e.hp--; used = true; break; }
            if (used || shots[i].x > 1300) shots.erase(shots.begin() + i); else i++;
        }
        for (size_t i = 0; i < es.size();) {
            if (es[i].hp <= 0) es.erase(es.begin() + i);
            else if (es[i].x < 150) { coreHp--; es.erase(es.begin() + i); }
            else i++;
        }
        if (coreHp <= 0) lose("The core was overrun.");
    }
    float laneY(int l) { return 250 + l * 150.0f; }
    void drawPlay() override {
        rect(0, 0, SCR_W, SCR_H, C(30, 40, 44));
        rect(0, 0, SCR_W, 130, C(14, 20, 24));
        for (int l = 0; l < 3; l++) { rect(120, laneY(l) - 50, 1160, 100, C(255, 255, 255, l == lane ? 22 : 10)); frameR(120, laneY(l) - 50, 1160, 100, C(255, 255, 255, 40), 2); }
        rect(30, 180, 90, 480, C(60, 120, 120)); frameR(30, 180, 90, 480, WHITE, 3);
        rect(40, 190 + 460.0f * (1 - (float)coreHp / coreHp0), 70, 460.0f * coreHp / coreHp0, C(120, 255, 220, 120));
        text("CORE", 75, 160, 1.2f, WHITE, 1);
        drawPerson(300, laneY(lane) + 30, 1, playerLook(), t, true);
        for (auto& s : shots) rect(s.x, laneY(s.lane) - 12, 22, 6, C(255, 240, 150));
        for (auto& e : es) {
            float y = laneY(e.lane);
            Col c = e.maxhp >= 4 ? C(120, 60, 140) : e.maxhp == 2 ? C(150, 150, 170) : C(190, 190, 200);
            fillCircle(e.x, y - 10, e.maxhp >= 4 ? 40 : 28, c);
            rect(e.x - 10, y - 18, 6, 8, BLACK); rect(e.x + 6, y - 18, 6, 8, BLACK);
            if (e.maxhp > 1) rect(e.x - 22, y - 56, 44.0f * e.hp / e.maxhp, 6, C(255, 90, 80));
        }
        text("WAVE " + std::to_string(wave) + "/" + std::to_string(waves), 40, 40, 2.2f, WHITE);
        text("CORE " + std::to_string(coreHp) + "/" + std::to_string(coreHp0), SCR_W - 40, 40, 2.2f, WHITE, 2);
    }
};
