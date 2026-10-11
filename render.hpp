// render.hpp - all drawing: world, scenes, HUD, dialogue, blueprint menus
#pragma once
#include "engine.hpp"

static const float GY = 590; // ground line in the corridor view

static std::string utf8sub(const std::string& s, int n) {
    std::string out; int cnt = 0;
    for (size_t i = 0; i < s.size() && cnt < n;) {
        unsigned char c = s[i];
        int len = c >= 0xF0 ? 4 : c >= 0xE0 ? 3 : c >= 0xC0 ? 2 : 1;
        out += s.substr(i, len); i += len; cnt++;
    }
    return out;
}

static void gradient(float y0, float y1, Col a, Col b, float x = 0, float w = SCR_W) {
    int steps = 24;
    for (int i = 0; i < steps; i++) {
        float t0 = y0 + (y1 - y0) * i / steps;
        rect(x, t0, w, (y1 - y0) / steps + 1, mix(a, b, (float)i / (steps - 1)));
    }
}

static Col speakerCol(const std::string& who) {
    CharDef* c = nullptr;
    if (!g.dKey.empty()) c = charBy(g.dKey);
    if (!c && who == "Adam") c = charBy("adam_t");
    if (!c) c = charByName(who);
    if (c) return c->look.shirt;
    if (who == "Everyone" || who == "All") return C(200, 200, 210);
    if (who == "???") return C(160, 60, 200);
    return C(150, 150, 165);
}

// ---------------------------------------------------------------- backdrops for cutscenes
static void skyline(float camX, Col c, float baseY, float t) {
    for (int i = 0; i < 12; i++) {
        float bx = i * 130 - fmodf(camX, 130);
        float bh = 120 + ((i * 37) % 5) * 40;
        rect(bx, baseY - bh, 110, bh + 400, c);
        for (int k = 0; k < 4; k++) for (int j = 0; j < (int)(bh / 40); j++)
            if (((i + k + j) * 7) % 3) rect(bx + 14 + k * 24, baseY - bh + 14 + j * 40, 12, 18, C(255, 240, 160, 90));
    }
}

static void drawBackdrop(const std::string& bg, int t) {
    if (bg == "room") {
        gradient(0, 600, C(90, 118, 168), C(62, 84, 128));
        rect(0, 600, SCR_W, 120, C(122, 82, 60)); rect(0, 596, SCR_W, 6, C(60, 40, 30));
        rect(860, 120, 280, 220, C(40, 50, 70)); gradient(130, 330, C(120, 190, 255), C(220, 240, 255), 870, 260);
        rect(995, 130, 10, 200, C(40, 50, 70)); rect(870, 225, 260, 10, C(40, 50, 70));
        rect(180, 150, 130, 170, ORANGE); text("14", 245, 195, 4, BLACK, 1);
        rect(80, 430, 230, 20, C(70, 60, 90)); rect(80, 450, 230, 150, C(90, 75, 120));
    } else if (bg == "outside" || bg == "sunset" || bg == "night") {
        Col top = bg == "outside" ? C(110, 170, 235) : bg == "sunset" ? C(95, 60, 130) : C(8, 12, 36);
        Col bot = bg == "outside" ? C(205, 228, 250) : bg == "sunset" ? C(255, 160, 90) : C(34, 44, 90);
        gradient(0, 600, top, bot);
        if (bg == "night") { for (int i = 0; i < 40; i++) rect((i * 193) % 1280, (i * 71) % 330, 3, 3, C(255, 255, 255, 120 + (i * 17 + t) % 100)); fillCircle(1050, 140, 46, C(250, 250, 220)); }
        if (bg == "sunset") fillCircle(300, 470, 80, C(255, 220, 140));
        skyline(0, bg == "outside" ? C(120, 140, 180) : C(30, 30, 60), 600, t);
        rect(0, 600, SCR_W, 120, bg == "night" ? C(30, 30, 40) : C(92, 94, 102)); rect(0, 596, SCR_W, 8, C(160, 160, 160));
        for (int x = 0; x < 1280; x += 160) rect(x, 660, 80, 6, C(240, 240, 240, 130));
    } else if (bg == "backrooms") {
        rect(0, 0, SCR_W, SCR_H, C(196, 176, 70));
        for (int x = 0; x < SCR_W; x += 48) rect(x, 60, 3, 540, C(170, 150, 50));
        rect(0, 0, SCR_W, 70, C(215, 205, 150));
        for (int x = 60; x < SCR_W; x += 300) rect(x, 20, 160, 26, C(255, 255, 240, 200 + (int)(40 * sinf(t * 0.2f + x))));
        rect(0, 600, SCR_W, 120, C(150, 130, 50)); for (int x = 0; x < SCR_W; x += 64) rect(x, 600, 2, 120, C(120, 100, 40));
    } else if (bg == "roof") {
        gradient(0, 600, C(70, 120, 210), C(255, 190, 140));
        fillCircle(980, 180, 70, C(255, 240, 200, 200));
        skyline(0, C(70, 90, 150), 560, t);
        rect(0, 600, SCR_W, 120, C(110, 114, 130)); rect(0, 590, SCR_W, 14, C(180, 184, 200));
        rect(0, 520, SCR_W, 6, C(60, 60, 70)); for (int x = 0; x < SCR_W; x += 60) rect(x, 520, 5, 70, C(60, 60, 70));
        rect(1000, 380, 120, 140, C(120, 90, 70)); rect(1010, 360, 100, 20, C(90, 65, 50));
        rect(240, 300, 8, 220, C(60, 60, 70)); rect(210, 340, 70, 5, C(60, 60, 70)); rect(220, 380, 50, 5, C(60, 60, 70));
    } else if (bg == "workshop") {
        rect(0, 0, SCR_W, SCR_H, C(158, 128, 96));
        for (int y = 80; y < 520; y += 40) for (int x = 40; x < SCR_W; x += 50) rect(x, y, 6, 6, C(100, 80, 60));
        rect(0, 560, SCR_W, 160, C(100, 66, 44)); rect(0, 550, SCR_W, 14, C(130, 90, 60));
        rect(150, 520, 60, 30, C(240, 240, 235)); rect(260, 510, 20, 40, C(60, 40, 30)); rect(400, 530, 70, 20, C(255, 220, 60));
        rect(560, 520, 12, 30, C(70, 70, 200)); rect(900, 515, 150, 12, C(220, 220, 230));
    } else if (bg == "hornet") {
        gradient(0, 420, C(120, 190, 240), C(210, 235, 250)); rect(0, 420, SCR_W, 300, C(86, 146, 76));
        rect(180, 140, 50, 340, C(100, 70, 40)); fillCircle(205, 130, 120, C(60, 120, 60)); fillCircle(130, 170, 80, C(70, 130, 70));
        fillCircle(205, 330, 36, C(190, 160, 110)); fillCircle(205, 345, 30, C(170, 140, 95)); fillCircle(205, 340, 6, C(40, 30, 20));
        for (int i = 0; i < 9; i++) { float a = t * 0.07f + i; rect(205 + cosf(a) * (60 + i * 6), 330 + sinf(a * 1.3f) * (40 + i * 4), 8, 6, C(250, 210, 30)); }
    } else if (bg == "shop") {
        rect(0, 0, SCR_W, SCR_H, C(255, 226, 206));
        for (int x = 0; x < SCR_W; x += 100) rect(x, 0, 50, 110, (x / 100) % 2 ? C(255, 120, 150) : C(255, 250, 250));
        rect(0, 560, SCR_W, 160, C(240, 200, 170)); rect(120, 440, 1040, 120, C(255, 255, 255)); rect(120, 440, 1040, 10, C(255, 140, 170));
        rect(900, 180, 220, 120, C(255, 255, 255)); text("ICE CREAM", 1010, 220, 2, C(255, 80, 130), 1);
        for (int i = 0; i < 5; i++) { fillCircle(230 + i * 110, 480, 30, mix(C(255, 150, 190), C(150, 220, 255), i / 4.0f)); }
    } else if (bg == "inn") {
        gradient(0, 600, C(160, 66, 76), C(120, 40, 55)); rect(0, 600, SCR_W, 120, C(90, 40, 55));
        for (int x = 60; x < SCR_W; x += 300) { rect(x, 330, 130, 270, C(70, 28, 36)); rect(x + 10, 340, 110, 250, C(100, 40, 50)); text("NST", x + 65, 300, 1.4f, C(255, 215, 120), 1); }
        text("FURTHER INN", 640, 90, 3, C(255, 215, 120, 180), 1, 6);
    } else if (bg == "elev") {
        rect(0, 0, SCR_W, SCR_H, C(110, 114, 124));
        for (int x = 0; x < SCR_W; x += 4) rect(x, 0, 1, SCR_H, C(255, 255, 255, 8 + (x % 16)));
        rect(540, 40, 200, 70, C(20, 20, 30)); text("14", 640, 52, 3, C(255, 120, 40), 1);
        rect(0, 640, SCR_W, 80, C(70, 72, 80));
    } else if (bg == "garage") {
        rect(0, 0, SCR_W, SCR_H, C(84, 88, 98)); rect(0, 0, SCR_W, 80, C(60, 62, 70));
        for (int x = 100; x < SCR_W; x += 380) { rect(x, 80, 60, 520, C(120, 124, 134)); rect(x, 520, 60, 80, C(240, 210, 40)); }
        rect(0, 600, SCR_W, 120, C(70, 72, 80)); for (int x = 0; x < SCR_W; x += 200) rect(x, 650, 90, 6, C(240, 240, 240, 140));
    } else if (bg == "void") {
        rect(0, 0, SCR_W, SCR_H, C(12, 10, 24));
        for (int x = 0; x < SCR_W; x += 80) line(640, 300, x, 720, C(120, 90, 200, 60));
        for (int y = 300; y < SCR_H; y += 40) line(0, y, SCR_W, y, C(120, 90, 200, 40));
    } else {
        gradient(0, SCR_H, C(40, 44, 60), C(20, 22, 34));
        rect(0, 610, SCR_W, 110, C(30, 32, 44));
    }
}

static void drawScene() {
    drawBackdrop(g.sceneBg, g.frame);
    size_t n = g.sceneChars.size();
    for (size_t i = 0; i < n; i++) {
        CharDef* c = charBy(g.sceneChars[i]);
        if (!c) continue;
        float x = n == 1 ? 640 : n == 2 ? (i == 0 ? 420 : 860) : (280 + i * 360);
        bool speaking = g.vs == V_SAY && (g.dKey.empty() ? g.dWho == c->name : g.dKey == c->key);
        float bob = speaking ? sinf(g.frame * 0.3f) * 3 : 0;
        if (c->isBot) { drawBot(x, 612 + bob, c->look.shirt, g.frame, i == 0 ? 1 : -1); continue; }
        Look l = c->look; l.h *= 1.9f; if (c->key == "amir") l.tag14 = true;
        drawPerson(x, 612 + bob, (i == 0 || (n == 3 && i == 1)) ? 1 : -1, l, g.frame, false);
    }
}

// ---------------------------------------------------------------- world themes
static void wallBG(const FloorDef& f) {
    gradient(46, 560, mix(f.wall, WHITE, 0.1f), dim(f.wall, 0.8f));
    rect(0, 560, SCR_W, 30, dim(f.wall, 0.6f));
    rect(0, 590, SCR_W, SCR_H - 590, dim(f.wall, 0.45f));
    rect(0, 588, SCR_W, 4, f.trim);
    rect(0, 46, SCR_W, 46, dim(f.wall, 0.5f));
}

static void drawTheme(const FloorDef& f, float camX) {
    const std::string& th = f.theme;
    auto sx = [&](float wx) { return wx - camX; };
    if (th == "roof" || th == "outside") {
        gradient(0, 590, th == "roof" ? C(70, 120, 210) : C(110, 160, 220), th == "roof" ? C(255, 190, 140) : C(200, 225, 250));
        fillCircle(980 - camX * 0.05f, 170, 64, C(255, 240, 200, 210));
        skyline(camX * 0.3f, th == "roof" ? C(70, 90, 150) : C(120, 140, 180), 560, 0);
        rect(0, 590, SCR_W, 130, th == "roof" ? C(110, 114, 130) : C(88, 90, 98));
        rect(0, 586, SCR_W, 6, C(190, 195, 210));
        if (th == "roof") {
            rect(0, 500, SCR_W, 5, C(60, 60, 70)); for (int x = -((int)camX % 60); x < SCR_W; x += 60) rect(x, 500, 5, 90, C(60, 60, 70));
            rect(sx(760), 380, 130, 200, C(120, 90, 70)); rect(sx(750), 365, 150, 20, C(90, 65, 50));
            rect(sx(1450), 330, 8, 260, C(60, 60, 70)); rect(sx(1415), 380, 80, 5, C(60, 60, 70)); rect(sx(1425), 430, 60, 5, C(60, 60, 70));
        } else {
            for (int x = -((int)camX % 220); x < SCR_W; x += 220) { rect(x + 20, 640, 110, 6, C(240, 240, 240, 140)); }
            rect(sx(300), 440, 240, 70, C(190, 60, 60)); rect(sx(330), 410, 150, 40, C(190, 60, 60)); rect(sx(345), 416, 55, 28, C(140, 190, 230));
            rect(sx(560), 450, 210, 62, C(70, 110, 190)); rect(sx(590), 422, 130, 34, C(70, 110, 190)); rect(sx(600), 428, 48, 24, C(140, 190, 230));
            rect(sx(60), 340, 150, 250, C(30, 20, 20)); frameR(sx(60), 340, 150, 250, ORANGE, 4);
            dashH(sx(70), 350, 130, C(255, 150, 60, 150)); text("STAIRWAY", sx(135), 300, 1.2f, ORANGE, 1);
        }
        return;
    }
    wallBG(f);
    // ceiling lights
    for (float x = 180; x < f.width; x += 320) if (sx(x) > -200 && sx(x) < SCR_W + 100) rect(sx(x), 56, 140, 10, C(255, 255, 235, 230));
    // big faded floor name on the wall
    text(f.name, sx(300), 150, 4, C(255, 255, 255, 34), 0, 4);
    if (th == "hall" || th == "inn") {
        for (size_t i = 0; i + 1 < f.rooms.size(); i++) { // plants between doors
            float px = f.roomX(i) + 220;
            if (sx(px) > -60 && sx(px) < SCR_W + 60) { rect(sx(px) - 14, 530, 28, 58, C(120, 80, 60)); fillCircle(sx(px), 520, 26, C(60, 150, 70)); fillCircle(sx(px) - 14, 505, 16, C(80, 170, 80)); }
        }
        if (th == "inn") text("FURTHER INN", sx(330), 108, 1.6f, C(255, 215, 120), 0, 3);
    } else if (th == "lobby") {
        text("14", sx(700), 120, 14, ORANGE, 0);
        rect(sx(900), 500, 330, 90, C(120, 80, 50)); rect(sx(900), 490, 330, 14, C(170, 120, 80)); text("RECEPTION", sx(1065), 450, 2, C(80, 50, 30), 1);
        rect(sx(2090), 360, 130, 230, C(150, 210, 240, 200)); frameR(sx(2090), 360, 130, 230, C(60, 60, 70), 5); text("EXIT", sx(2155), 325, 1.8f, C(80, 80, 90), 1);
        for (float x : {420.0f, 1500.0f, 1850.0f}) { rect(sx(x) - 16, 530, 32, 58, C(120, 80, 60)); fillCircle(sx(x), 515, 30, C(60, 150, 70)); }
        for (int x = -((int)camX % 120); x < SCR_W; x += 120) { rect(x, 592, 60, 128, C(255, 255, 255, 18)); }
    } else if (th == "under") {
        for (int k = 0; k < 3; k++) rect(0, 100 + k * 18, SCR_W, 10, C(150, 160, 175));
        rect(sx(880), 400, 100, 190, C(60, 110, 200)); rect(sx(890), 415, 80, 90, C(20, 30, 50)); text("SNACK", sx(930), 520, 1.2f, WHITE, 1);
        rect(sx(1500), 380, 120, 210, C(70, 74, 86)); text("STAFF", sx(1560), 400, 1.4f, C(255, 200, 80), 1);
    } else if (th == "parking") {
        for (float x = 100; x < f.width; x += 500) { rect(sx(x), 92, 70, 498, C(130, 134, 146)); rect(sx(x), 500, 70, 90, C(240, 210, 40)); for (int k = 0; k < 4; k++) rect(sx(x) + k * 20, 500, 10, 90, BLACK); }
        for (float x : {620.0f, 1160.0f, 1800.0f}) { rect(sx(x), 500, 230, 70, C(90, 130, 200)); rect(sx(x) + 40, 462, 140, 42, C(90, 130, 200)); rect(sx(x) + 50, 468, 55, 30, C(170, 210, 240)); rect(sx(x) + 20, 560, 40, 30, BLACK); rect(sx(x) + 170, 560, 40, 30, BLACK); }
        for (int k = 0; k < 8; k++) text(f.key == "park1" ? "P1" : "P2", sx(200 + k * 280), 640, 2, C(255, 255, 255, 90), 1);
    } else if (th == "shaft") {
        for (float x = 100; x < f.width; x += 220) rect(sx(x), 92, 14, 498, C(40, 42, 48));
        rect(sx(1180), 120, 200, 470, C(10, 10, 14)); for (int k = 0; k < 6; k++) rect(sx(1180) + k * 36, 120, 18, 470, C(255, 210, 40, 40));
        for (int k = 0; k < 10; k++) rect(sx(1150) + k * 24, 500, 14, 90, k % 2 ? C(255, 210, 40) : BLACK);
        if ((g.frame / 7) % 4 == 0) { rect(sx(1260), 300, 6, 6, C(255, 240, 160)); rect(sx(1300), 340, 5, 5, C(255, 200, 80)); }
        text("DANGER", sx(1280), 210, 2.4f, C(255, 210, 40), 1);
    } else if (th == "ctrl") {
        for (int i = 0; i < 6; i++) for (int j = 0; j < 2; j++) {
            float x = sx(560 + i * 230), y = 150 + j * 150;
            rect(x, y, 190, 120, C(10, 18, 24)); frameR(x, y, 190, 120, C(90, 255, 160, 120), 3);
            for (int k = 0; k < 5; k++) rect(x + 10, y + 12 + k * 20, 40 + ((i * 37 + k * 53 + g.frame / 6) % 120), 6, C(90, 255, 160, 170));
        }
        rect(sx(1080), 470, 160, 120, C(60, 70, 84)); for (int k = 0; k < 6; k++) rect(sx(1095) + k * 24, 485, 14, 14, ((g.frame / 20 + k) % 3) ? C(90, 255, 160) : C(255, 90, 90));
    } else if (th == "vent") {
        for (float x : {700.0f, 1500.0f, 2100.0f}) {
            fillCircle(sx(x), 330, 120, C(30, 40, 46)); fillCircle(sx(x), 330, 100, C(55, 70, 78));
            for (int b = 0; b < 4; b++) { float a = g.frame * 0.12f + b * 1.5708f; for (int o = -4; o <= 4; o++) line(sx(x) + o, 330, sx(x) + cosf(a) * 95 + o, 330 + sinf(a) * 95, C(170, 230, 255, 200)); }
            fillCircle(sx(x), 330, 12, C(20, 20, 24));
        }
        for (int k = 0; k < 4; k++) rect(0, 104 + k * 14, SCR_W, 8, C(150, 170, 180));
    } else if (th == "botpark") {
        for (int i = 0; i < 9; i++) { float x = 620 + i * 230; rect(sx(x) - 52, 580, 104, 12, C(120, 255, 220, 120 + (int)(60 * sinf(g.frame * 0.08f + i)))); rect(sx(x) - 60, 140, 120, 30, C(20, 30, 50)); text("BOT-0" + std::to_string(i), sx(x), 146, 1, C(120, 255, 220), 1); }
        text("14 CLEANING BOTS", sx(330), 108, 1.8f, C(120, 255, 220), 0, 4);
    }
}

static void drawElevator(const FloorDef& f, float camX) {
    float ex = f.elevX - camX;
    if (ex < -120 || ex > SCR_W + 120) return;
    rect(ex - 78, 350, 156, 240, C(60, 64, 74)); rect(ex - 70, 358, 140, 232, C(150, 156, 170));
    rect(ex - 2, 358, 4, 232, C(70, 74, 84));
    rect(ex - 40, 312, 80, 34, C(10, 12, 20)); text(f.level >= 0 ? "+" + std::to_string(f.level) : std::to_string(f.level), ex, 316, 1.6f, C(255, 120, 40), 1);
    rect(ex + 84, 450, 18, 40, C(40, 44, 54)); rect(ex + 90, 458, 6, 6, C(255, 120, 40)); rect(ex + 90, 474, 6, 6, C(120, 255, 190));
}

static void drawDoorSign(float cx, const Room& r, bool own, const FloorDef& f) {
    if (r.secret) {
        rect(cx - 42, 380, 84, 210, C(14, 10, 12)); dashH(cx - 42, 380, 84, ORANGE, 8, 6, 3); dashH(cx - 42, 588, 84, ORANGE, 8, 6, 3);
        dashV(cx - 42, 380, 210, ORANGE, 8, 6, 3); dashV(cx + 40, 380, 210, ORANGE, 8, 6, 3);
        if (F("secret_known")) text("STAIRWAY TO HELL", cx, 350, 1.0f, ORANGE, 1); else text("???", cx, 450, 1.6f, C(255, 150, 60, 120), 1);
        return;
    }
    Col dc = r.key.empty() ? dim(f.wall, 0.4f) : mix(dim(f.wall, 0.55f), f.trim, 0.15f);
    rect(cx - 66, 356, 132, 234, f.trim);
    rect(cx - 60, 362, 120, 228, dc);
    rect(cx - 52, 372, 104, 98, dim(dc, 0.82f)); rect(cx - 52, 482, 104, 98, dim(dc, 0.82f));
    rect(cx + 38, 480, 10, 14, C(240, 220, 120));
    rect(cx - 70, 300, 140, 50, C(18, 20, 30)); frameR(cx - 70, 300, 140, 50, own ? ORANGE : f.trim, 3);
    text(r.id, cx, 304, 1.5f, own ? ORANGE : WHITE, 1);
    text(r.name, cx, 328, 1.0f, C(210, 215, 230), 1);
    if (r.key == "amir") { frameR(cx - 74, 296, 148, 58, ORANGE, 2); }
}

static void drawNpcTag(float x, const CharDef& c, float h) {
    float w = (float)std::max(textW(c.name, 1.2f), textW(c.id, 0.9f)) + 16;
    float y = GY - 110 * h - 64;
    rect(x - w / 2, y, w, 44, C(0, 0, 0, 170));
    text(c.name, x, y + 3, 1.2f, WHITE, 1);
    text(c.id, x, y + 24, 0.9f, C(255, 190, 120), 1);
}

static void drawWorld() {
    FloorDef* f = floorBy(g.floorKey);
    if (!f) return;
    float camX = std::max(0.0f, std::min(f->width - SCR_W, g.px - 640));
    if (g.shake > 0) camX += rndi(-5, 5);
    drawTheme(*f, camX);
    if (f->inElevator) drawElevator(*f, camX);
    for (size_t i = 0; i < f->rooms.size(); i++) {
        float cx = doorX(*f, (int)i) - camX;
        if (cx < -140 || cx > SCR_W + 140) continue;
        drawDoorSign(cx, f->rooms[i], f->rooms[i].key == "amir", *f);
    }
    // objects
    std::vector<ObjSp> all = builtinObjs(g.floorKey);
    for (auto& o : g.objs) if (o.floor == g.floorKey) all.push_back(o);
    for (auto& o : all) {
        float x = o.x - camX;
        if (x < -100 || x > SCR_W + 100) continue;
        bool plain = (o.id == "backdoor" || o.id == "frontdoor" || o.id == "reception" || o.id == "vending" || o.id == "fan" || o.id == "car1" || o.id == "car2" || o.id == "tank" || o.id == "shaftgap");
        if (!plain) { rect(x - 28, 520, 56, 70, C(40, 50, 70)); frameR(x - 28, 520, 56, 70, C(120, 255, 190), 3); rect(x - 20, 530, 40, 24, C(120, 255, 190, 150)); }
        else rect(x - 3, 596, 6, 6, C(255, 255, 255, 100 + (int)(100 * sinf(g.frame * 0.1f))));
    }
    // items
    for (auto& it : g.items) {
        if (it.floor != g.floorKey) continue;
        float x = it.x - camX, bob = sinf(g.frame * 0.1f + it.x) * 4;
        if (x < -50 || x > SCR_W + 50) continue;
        fillCircle(x, GY - 20 + bob, 30, C(255, 220, 120, 40));
        rect(x - 14, GY - 34 + bob, 28, 28, C(255, 200, 80)); frameR(x - 14, GY - 34 + bob, 28, 28, WHITE, 2);
        text(prettyItem(it.key), x, GY - 62 + bob, 1.0f, WHITE, 1);
    }
    // npcs
    for (auto& kv : g.npcs) {
        const Npc& n = kv.second;
        if (!n.visible || n.floor != g.floorKey) continue;
        CharDef* c = charBy(kv.first);
        if (!c) continue;
        float x = n.x - camX;
        if (x < -100 || x > SCR_W + 100) continue;
        if (c->isBot) drawBot(x, GY, c->look.shirt, g.frame + (int)n.phase * 7, n.dir);
        else drawPerson(x, GY, n.dir, c->look, g.frame / 2, !n.still && fabsf(cosf(g.frame * 0.012f + n.phase)) > 0.3f);
        if (fabsf(n.x - g.px) < 200) drawNpcTag(x, *c, c->isBot ? 0.6f : c->look.h);
    }
    // player
    CharDef* pc = charBy("amir");
    drawPerson(g.px - camX, GY, g.pdir, pc->look, g.walk, g.moving);
    // prompt
    if (!g.elevOpen && g.fadePhase == 0 && (g.vs == V_AWAIT || g.vs == V_NONE)) {
        Target t = nearestTarget();
        if (t.kind >= 0) {
            float x = g.px - camX;
            std::string s = "A  " + t.label;
            float w = textW(s, 1.4f) + 24;
            rect(x - w / 2, 330 - 6, w, 34, C(0, 0, 0, 190)); frameR(x - w / 2, 330 - 6, w, 34, ORANGE, 2);
            text(s, x, 330, 1.4f, WHITE, 1);
        }
    }
}

// ---------------------------------------------------------------- HUD / dialogue
static void drawHUD() {
    FloorDef* f = floorBy(g.floorKey);
    rect(0, 0, SCR_W, 44, C(0, 0, 0, 175));
    text("DAY " + std::to_string(g.day), 20, 10, 1.8f, ORANGE);
    if (f) text(f->name, 640, 10, 1.8f, WHITE, 1);
    text("ITEMS " + std::to_string(g.inv.size()), SCR_W - 20, 10, 1.8f, WHITE, 2);
    if (!g.goal.empty() && !g.sceneOn) {
        auto ls = wrapText("GOAL: " + g.goal, 62);
        float h = 14 + ls.size() * 26;
        rect(16, 54, 640, h, C(0, 0, 0, 150)); frameR(16, 54, 640, h, C(249, 115, 22, 160), 2);
        for (size_t i = 0; i < ls.size(); i++) text(ls[i], 28, 60 + i * 26, 1.5f, i == 0 ? C(255, 220, 170) : WHITE);
    }
    if (g.banner > 0) {
        int a = std::min(255, g.banner * 6);
        rect(0, 250, SCR_W, 90, C(0, 0, 0, a * 2 / 3));
        text(g.bannerText, 640, 270, 3.4f, C(255, 255, 255, a), 1, 4);
    }
    float y = 56;
    for (int i = (int)g.toasts.size() - 1; i >= 0; i--) {
        int a = std::min(255, g.toasts[i].life * 5);
        float w = textW(g.toasts[i].t, 1.4f) + 24;
        rect(SCR_W - 16 - w, y, w, 34, C(0, 0, 0, a * 2 / 3)); frameR(SCR_W - 16 - w, y, w, 34, C(249, 115, 22, a / 2), 2);
        text(g.toasts[i].t, SCR_W - 28, y + 5, 1.4f, C(255, 235, 190, a), 2);
        y += 40;
    }
}

static void drawDialog() {
    if (g.vs != V_SAY && g.vs != V_CHOOSE) return;
    float bx = 50, by = 505, bw = 1180, bh = 185;
    rect(bx, by, bw, bh, C(14, 22, 52, 238)); frameR(bx, by, bw, bh, WHITE, 3);
    dashH(bx + 10, by + bh - 12, bw - 20, C(255, 255, 255, 60), 10, 8, 1);
    if (!g.dWho.empty()) {
        Col sc = speakerCol(g.dWho);
        float w = textW(g.dWho, 1.8f) + 40;
        rect(bx + 20, by - 26, w, 40, sc); frameR(bx + 20, by - 26, w, 40, WHITE, 2);
        Col tc = (sc.r + sc.g + sc.b > 420) ? BLACK : WHITE;
        text(g.dWho, bx + 40, by - 20, 1.8f, tc);
    }
    if (!g.dPages.empty()) {
        std::string page = g.dPages[std::min<size_t>(g.dPage, g.dPages.size() - 1)];
        int shown = g.vs == V_CHOOSE ? 99999 : (int)g.dShown;
        std::string sub = utf8sub(page, shown);
        auto ls = splitStr(sub, '\n');
        for (size_t i = 0; i < ls.size(); i++) text(ls[i], bx + 28, by + 22 + i * 42, 1.9f, g.dWho.empty() ? C(215, 220, 235) : WHITE);
        if (g.vs == V_SAY && g.dShown >= utf8len(page)) {
            bool more = g.dPage + 1 < (int)g.dPages.size();
            int a = 150 + (int)(100 * sinf(g.frame * 0.15f));
            text(more ? "A  >>" : "A", bx + bw - 30, by + bh - 36, 1.6f, C(255, 200, 120, a), 2);
        }
    }
    if (g.vs == V_CHOOSE) {
        float ch = 18 + g.dChoices.size() * 48;
        float cw = 700;
        float cx = bx + bw - cw, cy = by - ch - 12;
        rect(cx, cy, cw, ch, C(14, 22, 52, 245)); frameR(cx, cy, cw, ch, ORANGE, 3);
        for (size_t i = 0; i < g.dChoices.size(); i++) {
            float y = cy + 10 + i * 48;
            bool s = (int)i == g.dSel;
            if (s) rect(cx + 8, y, cw - 16, 42, ORANGE);
            text(g.dChoices[i], cx + 24, y + 8, 1.7f, s ? BLACK : WHITE);
        }
    }
}

static void drawCardScreen(const std::string& title, const std::string& sub, int t, bool dark) {
    rect(0, 0, SCR_W, SCR_H, dark ? C(8, 10, 22) : C(28, 64, 150));
    for (int x = 0; x < SCR_W; x += 40) rect(x, 0, 1, SCR_H, C(255, 255, 255, 14));
    for (int y = 0; y < SCR_H; y += 40) rect(0, y, SCR_W, 1, C(255, 255, 255, 14));
    dashH(80, 200, 1120, C(255, 255, 255, 140)); dashH(80, 520, 1120, C(255, 255, 255, 140));
    int a = std::min(255, t * 8);
    text(title, 640, 250, 5, C(255, 255, 255, a), 1, 8);
    text(sub, 640, 360, 2.6f, C(249, 160, 90, a), 1);
    if (t > 50) text("A", 640, 570, 2, C(255, 255, 255, 120 + (int)(100 * sinf(t * 0.12f))), 1);
}

static void drawElevMenu() {
    if (!g.elevOpen) return;
    std::vector<int> l = elevList();
    float w = 520, rowH = 38;
    int vis = std::min<int>(l.size(), 12);
    float h = 70 + vis * rowH;
    float x = 380, y = 90;
    rect(x, y, w, h, C(10, 14, 30, 245)); frameR(x, y, w, h, ORANGE, 3);
    text("ELEVATOR", x + w / 2, y + 12, 2, ORANGE, 1, 4);
    int start = std::max(0, std::min((int)l.size() - vis, g.elevSel - vis / 2));
    for (int i = 0; i < vis; i++) {
        int idx = start + i;
        FloorDef& fl = FLOORS[l[idx]];
        float ry = y + 56 + i * rowH;
        bool s = idx == g.elevSel;
        if (s) rect(x + 8, ry, w - 16, rowH - 4, ORANGE);
        Col c = s ? BLACK : WHITE;
        text((fl.level >= 0 ? "+" : "") + std::to_string(fl.level), x + 24, ry + 6, 1.5f, c);
        text(fl.name, x + 90, ry + 6, 1.5f, c);
        if (fl.key == g.floorKey) text("HERE", x + w - 24, ry + 6, 1.3f, c, 2);
    }
    text("A Go   B Close", x + w / 2, y + h + 10, 1.5f, WHITE, 1);
}

// ---------------------------------------------------------------- blueprint menus
static void blueprintBG() {
    rect(0, 0, SCR_W, SCR_H, C(28, 66, 156));
    for (int x = 0; x < SCR_W; x += 40) rect(x, 0, (x % 200 == 0) ? 2 : 1, SCR_H, C(255, 255, 255, (x % 200 == 0) ? 34 : 15));
    for (int y = 0; y < SCR_H; y += 40) rect(0, y, SCR_W, (y % 200 == 0) ? 2 : 1, C(255, 255, 255, (y % 200 == 0) ? 34 : 15));
    Col wcol = C(255, 255, 255, 190);
    dashH(50, 84, 1180, wcol); dashH(50, 636, 1180, wcol); dashV(56, 70, 580, wcol); dashV(1222, 70, 580, wcol);
    // corner marks
    for (int sx = 0; sx < 2; sx++) for (int sy = 0; sy < 2; sy++) {
        float x = sx ? 1222 : 56, y = sy ? 636 : 84;
        rect(x - 14, y, 30, 2, WHITE); rect(x, y - 14, 2, 30, WHITE);
    }
    text("A Select    B Back", 640, 668, 1.6f, WHITE, 1, 2);
    text("ILOT14 WORLD  " VERSION, 1210, 52, 1.2f, C(255, 255, 255, 150), 2);
}

static void bpButton(float x, float y, float w, float h, const std::string& label, bool sel, bool enabled = true) {
    Col c = enabled ? WHITE : C(255, 255, 255, 90);
    if (sel) { rect(x, y, w, h, WHITE); text(label, x + 28, y + h / 2 - 14, 2.0f, C(28, 66, 156), 0, 2); rect(x - 22, y + h / 2 - 8, 14, 16, ORANGE); }
    else { frameR(x, y, w, h, c, 3); text(label, x + 28, y + h / 2 - 14, 2.0f, c, 0, 2); }
}

static std::string fmtTime(long frames) {
    long s = frames / 60; char b[32]; snprintf(b, sizeof b, "%ldh %02ldm", s / 3600, (s / 60) % 60); return b;
}

static void drawTower() {
    float x0 = 880, x1 = 1170, y0 = 130, y1 = 610;
    std::vector<FloorDef*> fl;
    for (auto& f : FLOORS) if (f.inElevator) fl.push_back(&f);
    float rh = (y1 - y0) / fl.size();
    frameR(x0, y0, x1 - x0, y1 - y0, WHITE, 3);
    int hl = (g.frame / 45) % fl.size();
    for (size_t i = 0; i < fl.size(); i++) {
        float y = y0 + i * rh;
        if (i) dashH(x0, y, x1 - x0, C(255, 255, 255, 120), 8, 6, 1);
        bool h = (int)i == hl;
        if (h) rect(x0 + 2, y + 1, x1 - x0 - 4, rh - 1, C(249, 115, 22, 150));
        text(fl[i]->name, x0 + 8, y + rh / 2 - 7, 0.85f, WHITE);
    }
    rect(x0 + 20, y0 - 22, x1 - x0 - 40, 22, C(255, 255, 255, 40)); text("THE 14", (x0 + x1) / 2, y0 - 20, 1.2f, WHITE, 1, 6);
    line(x1 + 24, y0, x1 + 24, y1, WHITE); rect(x1 + 18, y0 - 1, 12, 2, WHITE); rect(x1 + 18, y1, 12, 2, WHITE);
    text("17 LEVELS", x1 + 34, (y0 + y1) / 2 - 8, 1.0f, C(255, 255, 255, 190));
}

static void drawTitleMenu() {
    blueprintBG();
    drawTower();
    text("\xC3\x8E L O T 1 4", 110, 110, 6.6f, WHITE, 0, 4);
    text("W O R L D   //   BLUEPRINT SERIES", 114, 205, 1.5f, C(255, 255, 255, 200));
    SlotInfo last; if (g.st.lastSlot > 0) last = slotInfo(g.st.lastSlot);
    const char* names[] = {"CONTINUE", "NEW GAME", "SAVE SLOTS", "DAY SELECT", "SETTINGS", "EXIT TO HOMEBREW MENU"};
    for (int i = 0; i < 6; i++) bpButton(130, 250 + i * 64, 560, 52, names[i], g.sel == i, i != 0 || last.exists);
    if (g.msgT > 0) text(g.msg, 130, 640, 1.4f, C(255, 220, 120));
    if (g.sel == 0 && last.exists) text("Slot " + std::to_string(g.st.lastSlot) + " - Day " + std::to_string(last.day), 710, 262, 1.3f, C(255, 255, 255, 180));
}

static void drawSlotList(const std::string& heading, const std::string& hint) {
    blueprintBG();
    text(heading, 110, 110, 3.4f, WHITE, 0, 6);
    text(hint, 114, 175, 1.4f, C(255, 255, 255, 190));
    for (int i = 1; i <= 3; i++) {
        SlotInfo si = slotInfo(i);
        float y = 230 + (i - 1) * 124;
        bool s = g.sel == i - 1;
        if (s) rect(110, y, 1060, 104, C(255, 255, 255, 40));
        frameR(110, y, 1060, 104, WHITE, s ? 4 : 2);
        text("SLOT " + std::to_string(i), 140, y + 16, 2.4f, s ? ORANGE : WHITE, 0, 3);
        if (si.exists) {
            std::string t = DAY_TITLE.count(si.day) ? DAY_TITLE[si.day] : "";
            text("DAY " + std::to_string(si.day) + "  -  " + t, 140, y + 60, 1.7f, WHITE);
            text(fmtTime(si.frames), 1150, y + 16, 1.7f, C(255, 255, 255, 190), 2);
        } else text("EMPTY", 140, y + 60, 1.7f, C(255, 255, 255, 140));
    }
}

static void drawDaySelect() {
    blueprintBG();
    text("DAY SELECT", 110, 100, 3.4f, WHITE, 0, 6);
    text("Days you have reached are unlocked.", 114, 160, 1.4f, C(255, 255, 255, 190));
    for (int d = 1; d <= 31; d++) {
        int i = d - 1; float x = 130 + (i % 8) * 128, y = 210 + (i / 8) * 96;
        bool un = d <= g.st.maxDay, s = g.sel == i;
        if (s) rect(x, y, 112, 80, WHITE); else frameR(x, y, 112, 80, un ? WHITE : C(255, 255, 255, 70), 2);
        Col c = s ? C(28, 66, 156) : (un ? WHITE : C(255, 255, 255, 80));
        text(std::to_string(d), x + 56, y + 20, 2.6f, c, 1);
        if (!un) text("LOCKED", x + 56, y + 58, 0.9f, c, 1);
    }
    int d = g.sel + 1;
    std::string t = DAY_TITLE.count(d) ? DAY_TITLE[d] : "";
    text("DAY " + std::to_string(d) + (g.sel + 1 <= g.st.maxDay ? "  -  " + t : "  -  ???"), 130, 580, 2.0f, ORANGE);
    text("Starts the day with the choices you had when you first got there.", 130, 616, 1.2f, C(255, 255, 255, 170));
}

static void drawSettings() {
    blueprintBG();
    text("SETTINGS", 110, 100, 3.4f, WHITE, 0, 6);
    const char* ts[] = {"SLOW", "NORMAL", "FAST", "INSTANT"};
    bpButton(130, 230, 760, 64, std::string("TEXT SPEED:   ") + ts[g.st.textSpeed], g.sel == 0);
    bpButton(130, 320, 760, 64, std::string("SCANLINES:   ") + (g.st.scanlines ? "ON" : "OFF"), g.sel == 1);
    bpButton(130, 410, 760, 64, "BACK", g.sel == 2);
    text("Left / Right or A changes a setting.", 134, 500, 1.4f, C(255, 255, 255, 190));
}

static void drawPause() {
    rect(0, 0, SCR_W, SCR_H, C(0, 20, 60, 190));
    frameR(300, 120, 680, 480, WHITE, 3);
    text("PAUSED", 640, 150, 3.2f, WHITE, 1, 8);
    const char* names[] = {"RESUME", "SAVE PROGRESS", "SETTINGS", "QUIT TO TITLE"};
    for (int i = 0; i < 4; i++) bpButton(350, 235 + i * 70, 580, 56, names[i], g.sel == i);
    text("Saves the start of Day " + std::to_string(g.day), 640, 535, 1.3f, C(255, 255, 255, 180), 1);
    if (g.msgT > 0) text(g.msg, 640, 565, 1.5f, C(255, 220, 120), 1);
}

static void drawEnding() {
    rect(0, 0, SCR_W, SCR_H, C(8, 10, 22));
    float a = std::min(1.0f, g.cT / 90.0f);
    text("DAY 31 COMPLETE", 640, 200, 4, C(255, 255, 255, (int)(255 * a)), 1, 8);
    text("TO BE CONTINUED...", 640, 300, 3, C(249, 115, 22, (int)(255 * a)), 1, 6);
    text("LOST OF ASHES  -  the story goes on", 640, 400, 1.8f, C(255, 255, 255, (int)(200 * a)), 1);
    text("Thanks for playing  " VERSION, 640, 460, 1.6f, C(255, 255, 255, (int)(160 * a)), 1);
    if (g.cT > 120) text("A", 640, 580, 2, C(255, 255, 255, 120 + (int)(100 * sinf(g.cT * 0.12f))), 1);
}
