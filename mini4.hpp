// mini4.hpp - M2 minigames: stack, sort, dash, balance. All touch-friendly, all play themselves under TEST_AI.
#pragma once

// ---------------------------------------------------------------- STACK THE CRATES (tap to drop)
struct Stack : Mini {
    float x, dir, w, topX, topW; int need, h, lvl, miss, missMax;
    std::vector<std::pair<float, float>> tower;
    Stack(int n, int l) : need(n), lvl(l) { title = "Stack the Crates"; touch = true; missMax = 3; hint = "Tap, or press A, to drop the sliding crate onto the tower. Stack " + std::to_string(n) + " crates. Misses shrink the next crate."; }
    void reset() override { tower.clear(); tower.push_back({640, 260}); x = 200; dir = 1; w = 260; h = 1; miss = 0; }
    void drop() {
        float tx = tower.back().first, tw = tower.back().second;
        float lo = std::max(x - w / 2, tx - tw / 2), hi = std::min(x + w / 2, tx + tw / 2);
        if (hi - lo < 18) { miss++; w *= 0.85f; if (miss > missMax) lose("The tower fell over!"); return; }
        tower.push_back({(lo + hi) / 2, hi - lo}); w = hi - lo; h++;
        if (h > need) win("Perfect tower!");
    }
    void play(const Input& in) override {
        x += dir * (4.0f + lvl * 1.4f + h * 0.15f);
        if (x > 1100) dir = -1; if (x < 180) dir = 1;
        bool tap = in.hit(B_A) || !in.taps.empty();
        if (TEST_AI) { float tx = tower.back().first; if (fabsf(x - tx) < 10) tap = true; }
        if (tap) drop();
    }
    void drawPlay() override {
        boardBG("STACK THE CRATES", "Height " + std::to_string(h - 1) + "/" + std::to_string(need) + "    Slips left " + std::to_string(std::max(0, missMax - miss + 1)));
        float baseY = 640;
        for (size_t i = 0; i < tower.size(); i++) { float yy = baseY - i * 34; rect(tower[i].first - tower[i].second / 2, yy - 32, tower[i].second, 32, i % 2 ? C(249, 115, 22) : C(220, 90, 20)); frameR(tower[i].first - tower[i].second / 2, yy - 32, tower[i].second, 32, BLACK, 2); }
        float yy = baseY - tower.size() * 34;
        rect(x - w / 2, std::max(110.0f, yy - 32), w, 32, C(120, 255, 200)); frameR(x - w / 2, std::max(110.0f, yy - 32), w, 32, BLACK, 2);
    }
};

// ---------------------------------------------------------------- SORT THE LAUNDRY (left bin / right bin)
struct Sort : Mini {
    struct It { float y; int col; }; // col 0 orange (left), 1 blue (right)
    std::vector<It> its; int need, sorted, miss, missMax, spawnT, lvl;
    Sort(int n, int l) : need(n), lvl(l) { title = "Sort the Laundry"; touch = true; missMax = 3; hint = "Orange laundry goes LEFT, blue goes RIGHT. Tap the left or right half of the screen, or use the D-pad. Sort " + std::to_string(n) + " pieces."; }
    void reset() override { its.clear(); sorted = 0; miss = 0; spawnT = 20; }
    void sortIt(int side) { if (its.empty()) return; if (its[0].col == side) sorted++; else miss++; its.erase(its.begin()); }
    void play(const Input& in) override {
        if (in.hit(B_LEFT)) sortIt(0);
        if (in.hit(B_RIGHT)) sortIt(1);
        for (auto& t : in.taps) sortIt(t.first < 640 ? 0 : 1);
        if (TEST_AI && !its.empty() && its[0].y > 250) sortIt(its[0].col);
        if (--spawnT <= 0) { spawnT = std::max(22, 54 - lvl * 7) + rnd() % 14; its.push_back({100, (int)(rnd() % 2)}); }
        for (size_t i = 0; i < its.size();) { its[i].y += 2.8f + lvl * 0.7f; if (its[i].y > 600) { miss++; its.erase(its.begin() + i); continue; } i++; }
        if (sorted >= need) win("All sorted!");
        else if (miss > missMax) lose("Mixed up the laundry!");
    }
    void drawPlay() override {
        boardBG("SORT THE LAUNDRY", "Sorted " + std::to_string(sorted) + "/" + std::to_string(need) + "    Mistakes left " + std::to_string(std::max(0, missMax - miss + 1)));
        rect(60, 620, 480, 60, C(249, 115, 22, 140)); frameR(60, 620, 480, 60, C(249, 115, 22), 3); text("LEFT", 300, 636, 2, WHITE, 1);
        rect(740, 620, 480, 60, C(60, 140, 255, 140)); frameR(740, 620, 480, 60, C(60, 140, 255), 3); text("RIGHT", 980, 636, 2, WHITE, 1);
        for (size_t i = 0; i < its.size(); i++) { Col c = its[i].col ? C(60, 140, 255) : C(249, 115, 22); float yy = its[i].y; rect(600, yy, 80, 60, c); rect(580, yy + 6, 24, 16, c); rect(676, yy + 6, 24, 16, c); frameR(600, yy, 80, 60, BLACK, 3); if (i == 0) frameR(590, yy - 10, 100, 80, WHITE, 3); }
    }
};

// ---------------------------------------------------------------- DASH (3-lane runner)
struct Dash : Mini {
    struct Ob { int lane; float y; };
    std::vector<Ob> obs; int lane, secs, timeLeft, spawnT, lvl, hits, hitMax; float px;
    Dash(int s, int l) : secs(s), lvl(l) { title = "Hallway Dash"; touch = true; hitMax = 3; hint = "Dodge the carts! Tap the left or right side, or use the D-pad, to change lanes. Survive " + std::to_string(s) + " seconds."; }
    void reset() override { obs.clear(); lane = 1; timeLeft = secs * 60; spawnT = 30; hits = 0; px = 640; }
    void play(const Input& in) override {
        if (in.hit(B_LEFT)) lane = std::max(0, lane - 1);
        if (in.hit(B_RIGHT)) lane = std::min(2, lane + 1);
        for (auto& t : in.taps) { if (t.first < 427) lane = 0; else if (t.first > 853) lane = 2; else lane = 1; }
        if (TEST_AI) { for (auto& o : obs) if (o.lane == lane && o.y > 360 && o.y < 600) { int nl = (lane + 1) % 3; bool ok = true; for (auto& o2 : obs) if (o2.lane == nl && o2.y > 300 && o2.y < 640) ok = false; if (!ok) nl = (lane + 2) % 3; lane = nl; break; } }
        px += (320 + lane * 320 - px) * 0.3f;
        if (--spawnT <= 0) { spawnT = std::max(16, 40 - lvl * 5) + rnd() % 12; obs.push_back({(int)(rnd() % 3), 90}); }
        for (size_t i = 0; i < obs.size();) {
            obs[i].y += 5.0f + lvl * 1.2f;
            if (obs[i].y > 560 && obs[i].y < 640 && obs[i].lane == lane) { hits++; obs.erase(obs.begin() + i); continue; }
            if (obs[i].y > 720) { obs.erase(obs.begin() + i); continue; }
            i++;
        }
        if (hits > hitMax) lose("Too many crashes!");
        else if (--timeLeft <= 0) win("Made it down the hall!");
    }
    void drawPlay() override {
        boardBG("HALLWAY DASH", "Time " + std::to_string(timeLeft / 60 + 1) + "    Bumps left " + std::to_string(std::max(0, hitMax - hits + 1)));
        for (int l = 0; l < 3; l++) { rect(320 + l * 320 - 140, 80, 280, 640, C(30, 46, 90)); }
        for (int l = 0; l < 4; l++) rect(160 + l * 320 - 2, 80, 4, 640, C(255, 255, 255, 60));
        for (auto& o : obs) { float x = 320 + o.lane * 320; rect(x - 60, o.y - 40, 120, 70, C(220, 60, 60)); frameR(x - 60, o.y - 40, 120, 70, BLACK, 3); fillCircle(x - 34, o.y + 34, 12, BLACK); fillCircle(x + 34, o.y + 34, 12, BLACK); }
        drawBot(px, 650, ORANGE, phaseT, 1, true);
    }
};

// ---------------------------------------------------------------- BALANCE (keep the tray level)
struct Balance : Mini {
    float pos, vel, tilt; int secs, timeLeft, lvl, out;
    Balance(int s, int l) : secs(s), lvl(l) { title = "Tray Balance"; touch = true; hint = "Keep the ball on the tray. Tap the left or right half of the screen (or D-pad) to tilt. Hold on for " + std::to_string(s) + " seconds."; }
    void reset() override { pos = 0; vel = 0.4f; tilt = 0; timeLeft = secs * 60; out = 0; }
    void play(const Input& in) override {
        float push = 0;
        if (in.hit(B_LEFT)) push = -1; if (in.hit(B_RIGHT)) push = 1;
        if (fabsf(in.ax) > 0.2f) push = in.ax;
        for (auto& t : in.taps) push = t.first < 640 ? -1 : 1;
        if (TEST_AI) push = pos > 12 ? -1 : (pos < -12 ? 1 : (vel > 0.8f ? -0.5f : (vel < -0.8f ? 0.5f : 0)));
        tilt += push * 0.5f; tilt *= 0.9f;
        vel += tilt * 0.12f + ((rnd() % 100) / 100.0f - 0.5f) * (0.14f + lvl * 0.05f); vel *= 0.995f; pos += vel;
        if (fabsf(pos) > 300) lose("The ball rolled off!");
        else if (--timeLeft <= 0) win("Steady hands!");
    }
    void drawPlay() override {
        boardBG("TRAY BALANCE", "Time " + std::to_string(timeLeft / 60 + 1));
        float cx = 640, cy = 460;
        float a = tilt * 0.05f;
        for (int i = -300; i <= 300; i += 4) rect(cx + i, cy + i * a, 4, 12, C(220, 220, 230));
        fillCircle(cx + pos, cy + pos * a - 24, 22, ORANGE); frameR(cx + pos - 20, cy + pos * a - 44, 40, 40, BLACK, 1);
        rect(cx - 8, cy + 20, 16, 120, C(120, 120, 140));
    }
};
