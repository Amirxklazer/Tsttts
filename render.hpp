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
    } else if (bg == "hall") {
        gradient(0, 600, C(96, 112, 150), C(70, 84, 124)); rect(0, 600, SCR_W, 120, C(60, 66, 96)); rect(0, 596, SCR_W, 6, ORANGE);
        for (int x = 80; x < SCR_W; x += 300) { rect(x, 330, 130, 266, C(230, 230, 240)); rect(x + 8, 338, 114, 250, C(120, 130, 170)); }
        for (int x = 100; x < SCR_W; x += 320) rect(x, 70, 150, 12, C(255, 255, 235));
    } else if (bg == "deep") {
        rect(0, 0, SCR_W, SCR_H, C(14, 26, 32));
        for (int x = 0; x < SCR_W; x += 120) { rect(x, 0, 26, 600, C(30, 52, 60)); rect(x + 8, 0, 4, 600, C(50, 90, 96)); }
        for (int y = 120; y < 500; y += 130) rect(0, y, SCR_W, 14, C(40, 70, 78));
        rect(0, 600, SCR_W, 120, C(20, 34, 40)); rect(0, 596, SCR_W, 6, C(255, 140, 50));
        for (int x = 40; x < SCR_W; x += 260) rect(x, 480, 10, 10, C(255, 140, 50, 120 + (int)(100 * sinf(t * 0.1f + x))));
    } else if (bg == "void") {
        rect(0, 0, SCR_W, SCR_H, C(12, 10, 24));
        for (int x = 0; x < SCR_W; x += 80) line(640, 300, x, 720, C(120, 90, 200, 60));
        for (int y = 300; y < SCR_H; y += 40) line(0, y, SCR_W, y, C(120, 90, 200, 40));
    } else {
        gradient(0, SCR_H, C(40, 44, 60), C(20, 22, 34));
        rect(0, 610, SCR_W, 110, C(30, 32, 44));
    }
}

static void drawEmote(float x, float y, const std::string& e, int t) {
    float bob = sinf(t * 0.2f) * 3;
    float w = std::max(50.0f, (float)textW(e, 2.4f) + 26);
    rect(x - w / 2, y - 66 + bob, w, 54, WHITE); frameR(x - w / 2, y - 66 + bob, w, 54, BLACK, 3);
    rect(x - 7, y - 12 + bob, 14, 12, WHITE); rect(x - 4, y - 3 + bob, 8, 5, BLACK);
    text(e, x, y - 56 + bob, 2.4f, BLACK, 1);
}

static void drawScene() {
    float sx = g.shake > 0 ? (float)rndi(-6, 6) : 0;
    drawBackdrop(g.sceneBg, g.frame);
    std::vector<Actor*> order;
    for (auto& a : g.actors) order.push_back(&a);
    for (Actor* ap : order) {
        Actor& a = *ap;
        CharDef* c = charBy(a.key);
        if (!c) continue;
        bool speaking = g.vs == V_SAY && (g.dKey.empty() ? g.dWho == c->name : g.dKey == c->key);
        float bob = speaking ? sinf(g.frame * 0.3f) * 3 : 0, ox = sx, oy = 0;
        float prog = a.animT > 0 ? 1.0f - a.animT / (float)animLen(a.animName) : 0;
        float fr = (float)g.frame, ph = (float)(a.key.size() * 37 % 100);
        oy += sinf(fr * 0.06f + ph) * 1.6f;                    // idle breathing
        if (a.walking) oy -= fabsf(sinf(fr * 0.35f)) * 6;      // walking step bob
        const std::string& an = a.animName;
        if (an == "hop") oy = -fabsf(sinf(prog * 6.2832f * 1.5f)) * 70;
        else if (an == "shake") ox += sinf(fr * 1.6f) * 8;
        else if (an == "fall") { oy = prog * prog * 520; ox += prog * 90 * a.dir; }
        else if (an == "rise") oy = (1 - prog) * 400;
        else if (an == "bow") oy = sinf(prog * 3.1416f) * 40;
        else if (an == "wave") { ox += sinf(fr * 0.5f) * 6; oy -= fabsf(sinf(fr * 0.25f)) * 10; }
        else if (an == "dance") { ox += sinf(fr * 0.28f) * 34; oy = -fabsf(sinf(fr * 0.28f)) * 26; }
        else if (an == "nod") oy += fabsf(sinf(prog * 6.2832f * 2)) * 16;
        else if (an == "point") ox += a.dir * sinf(prog * 3.1416f) * 26;
        else if (an == "laugh") { oy = -fabsf(sinf(fr * 0.7f)) * 14; ox += sinf(fr * 0.9f) * 3; }
        else if (an == "shiver") ox += sinf(fr * 2.4f) * 3;
        else if (an == "sit") oy = 30 * sinf(std::min(1.0f, prog * 6) * 1.5708f);
        else if (an == "stomp") { oy = -sinf(prog * 6.2832f * 2) * 16; ox += sinf(fr * 1.8f) * 4; }
        else if (an == "float") oy = -sinf(prog * 3.1416f) * 40 + sinf(fr * 0.2f) * 6;
        else if (an == "jump") oy = -sinf(prog * 3.1416f) * 150;
        else if (an == "cheer") { oy = -fabsf(sinf(prog * 6.2832f * 2)) * 60; }
        else if (an == "tilt") ox += sinf(prog * 3.1416f) * 14;
        else if (an == "shrug") oy += sinf(prog * 3.1416f) * 12;
        else if (an == "sway") ox += sinf(fr * 0.12f) * 22;
        else if (an == "bounce") oy = -fabsf(sinf(fr * 0.4f)) * 36;
        else if (an == "clap") { oy = -fabsf(sinf(fr * 0.8f)) * 10; ox += sinf(fr * 1.6f) * 2; }
        else if (an == "zoomies") ox += sinf(prog * 6.2832f * 3) * 200;
        else if (an == "twirl") oy = -sinf(prog * 3.1416f) * 50;
        else if (an == "sneak") { oy += 14; ox += sinf(prog * 6.2832f) * 30; }
        else if (an == "dizzy") { ox += sinf(fr * 0.2f) * 18; oy += sinf(fr * 0.4f) * 5; }
        else if (an == "salute") oy -= sinf(prog * 3.1416f) * 14;
        int dirv = a.dir;
        if (a.animName == "spin" || a.animName == "cheer" || a.animName == "twirl" || a.animName == "dizzy") dirv = ((g.frame / 4) % 2) ? 1 : -1;
        if (a.animName == "look") dirv = ((g.frame / 14) % 2) ? 1 : -1;
        if (a.animName == "dance") dirv = ((g.frame / 18) % 2) ? 1 : -1;
        if (c->isBot) drawBot(a.x + ox, 612 + bob + oy, c->look.shirt, g.frame, dirv, a.animName != "shake");
        else {
            Look l = c->look; l.h *= 1.9f;
            drawPerson(a.x + ox, 612 + bob + oy, dirv, l, g.frame, a.walking);
        }
        if (a.emoteT > 0) drawEmote(a.x + ox, 612 - (c->isBot ? 150 : 340 * c->look.h), a.emote, g.frame);
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


static void drawOutsideDecor(const FloorDef& f, float camX) {
    auto sx = [&](float wx) { return wx - camX; };
    for (int x = -((int)camX % 220); x < SCR_W; x += 220) rect(x + 20, 640, 110, 6, C(240, 240, 240, 120));
    if (f.key == "reghaia") {
        // the building
        rect(sx(60), 150, 420, 440, C(150, 140, 130)); for (int r = 0; r < 6; r++) for (int c = 0; c < 4; c++) rect(sx(90) + c * 100, 180 + r * 66, 60, 40, ((r + c) % 3 == 0) ? C(255, 220, 140) : C(70, 90, 130));
        rect(sx(200), 470, 120, 120, C(40, 30, 30)); frameR(sx(200), 470, 120, 120, ORANGE, 4); text("14", sx(260), 430, 3, ORANGE, 1);
        // bus stop
        rect(sx(820), 420, 180, 12, C(60, 90, 150)); rect(sx(826), 432, 8, 158, C(60, 60, 70)); rect(sx(986), 432, 8, 158, C(60, 60, 70));
        rect(sx(850), 300, 14, 290, C(200, 200, 205)); rect(sx(820), 250, 76, 52, C(40, 150, 90)); text("ETUSA", sx(858), 258, 1.2f, WHITE, 1); text("14", sx(858), 278, 1.4f, WHITE, 1);
        // a bus
        float bx = sx(1180 + fmodf(g.frame * 0.6f, 600));
        if (F("bus_passing")) { rect(bx, 450, 300, 110, C(40, 150, 90)); rect(bx + 20, 466, 60, 36, C(170, 220, 240)); rect(bx + 100, 466, 60, 36, C(170, 220, 240)); rect(bx + 180, 466, 60, 36, C(170, 220, 240)); fillCircle(bx + 60, 560, 24, BLACK); fillCircle(bx + 230, 560, 24, BLACK); }
        // kiosk
        rect(sx(1540), 430, 150, 160, C(210, 110, 60)); rect(sx(1530), 410, 170, 26, C(240, 190, 80)); rect(sx(1560), 460, 110, 50, C(250, 235, 190)); text("KIOSK", sx(1615), 420, 1.3f, C(60, 30, 20), 1);
        // cable car station + wire
        rect(sx(2230), 190, 140, 400, C(120, 130, 150)); rect(sx(2220), 170, 160, 30, C(80, 90, 110)); text("TELEPHERIQUE", sx(2300), 120, 1.3f, WHITE, 1); text("EL MADANIA", sx(2300), 146, 1.1f, C(255, 220, 120), 1);
        line(sx(2380), 190, sx(3200), 40, C(40, 40, 50)); line(sx(2380), 192, sx(3200), 42, C(40, 40, 50));
        float cx2 = sx(2500 + fmodf(g.frame * 0.8f, 600)); float cy2 = 190 - (cx2 - sx(2380)) * (150.0f / 820.0f) + 30;
        rect(cx2 - 30, cy2, 60, 40, C(230, 90, 60)); rect(cx2 - 22, cy2 + 8, 44, 18, C(170, 220, 240));
    } else {   // madania
        for (int i = 0; i < 6; i++) rect(sx(900 + i * 140), 220 + (i % 2) * 40, 100, 370 - (i % 2) * 40, C(190, 180, 170));
        rect(sx(180), 230, 160, 360, C(120, 130, 150)); text("TELEPHERIQUE", sx(260), 190, 1.2f, WHITE, 1); text("REGHAIA", sx(260), 212, 1.1f, C(255, 220, 120), 1);
        rect(sx(1380), 240, 340, 350, C(60, 20, 40)); rect(sx(1370), 220, 360, 30, C(255, 200, 80)); text("CINEMA", sx(1550), 224, 2.2f, C(60, 20, 40), 1);
        for (int k = 0; k < 8; k++) fillCircle(sx(1390) + k * 44, 235, 5, ((g.frame / 8 + k) % 2) ? WHITE : C(255, 200, 80));
        rect(sx(1450), 330, 100, 90, C(250, 240, 200)); rect(sx(1570), 330, 100, 90, C(250, 240, 200)); rect(sx(1490), 470, 120, 120, C(30, 18, 24));
        rect(sx(2140), 500, 330, 10, C(60, 60, 70)); for (int k = 0; k < 7; k++) rect(sx(2140) + k * 52, 440, 8, 70, C(60, 60, 70));
        fillCircle(sx(2300), 240, 70, C(255, 190, 120, 120));
    }
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
        } else if (f.key != "out1") {
            drawOutsideDecor(f, camX);
        } else {
            for (int x = -((int)camX % 220); x < SCR_W; x += 220) { rect(x + 20, 640, 110, 6, C(240, 240, 240, 140)); }
            rect(sx(300), 440, 240, 70, C(190, 60, 60)); rect(sx(330), 410, 150, 40, C(190, 60, 60)); rect(sx(345), 416, 55, 28, C(140, 190, 230));
            rect(sx(560), 450, 210, 62, C(70, 110, 190)); rect(sx(590), 422, 130, 34, C(70, 110, 190)); rect(sx(600), 428, 48, 24, C(140, 190, 230));
            rect(sx(60), 340, 150, 250, C(30, 20, 20)); frameR(sx(60), 340, 150, 250, ORANGE, 4);
            dashH(sx(70), 350, 130, C(255, 150, 60, 150)); text("STAIRWAY", sx(135), 300, 1.2f, ORANGE, 1);
        }
        return;
    }
    if (th == "deep") {
        rect(0, 0, SCR_W, SCR_H, C(14, 26, 32));
        for (int x = -((int)camX % 120); x < SCR_W; x += 120) { rect(x, 92, 26, 498, C(30, 52, 60)); rect(x + 8, 92, 4, 498, C(50, 90, 96)); }
        for (int y = 150; y < 500; y += 120) rect(0, y, SCR_W, 14, C(40, 70, 78));
        rect(0, 590, SCR_W, 130, C(20, 34, 40)); rect(0, 588, SCR_W, 4, C(255, 140, 50));
        for (int x = -((int)camX % 260); x < SCR_W; x += 260) rect(x + 40, 470, 10, 10, C(255, 140, 50, 120 + (int)(100 * sinf(g.frame * 0.1f + x))));
        text(f.name, 640, 110, 2.4f, C(255, 140, 50, 90), 1, 6);
        return;
    }
    if (th == "cinema") {
        rect(0, 0, SCR_W, SCR_H, C(30, 12, 24)); rect(0, 590, SCR_W, 130, C(70, 20, 30)); rect(0, 586, SCR_W, 6, C(255, 200, 80));
        for (int x = -((int)camX % 200); x < SCR_W; x += 200) { rect(x + 20, 140, 120, 170, C(40, 30, 60)); frameR(x + 20, 140, 120, 170, C(255, 200, 80), 3); text("NOW", x + 80, 190, 1.4f, C(255, 200, 80), 1); text("SHOWING", x + 80, 214, 1.2f, WHITE, 1); }
        rect(sx(700), 440, 240, 150, C(100, 70, 40)); text("TICKETS", sx(820), 400, 1.8f, C(255, 200, 80), 1);
        rect(sx(1200), 430, 220, 160, C(200, 50, 60)); for (int k = 0; k < 6; k++) rect(sx(1200) + k * 37, 430, 18, 160, WHITE); fillCircle(sx(1310), 410, 40, C(255, 245, 200)); text("POPCORN", sx(1310), 380, 1.5f, WHITE, 1);
        rect(sx(1800), 300, 280, 290, C(20, 20, 30)); frameR(sx(1800), 300, 280, 290, C(255, 200, 80), 4); text("SALLE 1", sx(1940), 260, 2, C(255, 200, 80), 1);
        rect(sx(110), 380, 150, 210, C(50, 30, 30)); text("EXIT", sx(185), 340, 1.6f, C(120, 255, 190), 1);
        return;
    }
    if (th == "school") {
        gradient(46, 560, C(235, 225, 190), C(215, 205, 165)); rect(0, 560, SCR_W, 30, C(150, 140, 110)); rect(0, 590, SCR_W, 130, C(120, 110, 90)); rect(0, 586, SCR_W, 6, C(60, 120, 90));
        for (int x = -((int)camX % 300); x < SCR_W; x += 300) { rect(x + 60, 150, 140, 130, C(170, 210, 235)); frameR(x + 60, 150, 140, 130, C(90, 80, 70), 4); }
        text("ECOLE", sx(320), 110, 3, C(60, 120, 90), 0, 4);
        rect(sx(820), 360, 160, 230, C(110, 70, 40)); text("CLASS 3B", sx(900), 330, 1.5f, C(60, 40, 30), 1);
        rect(sx(1500), 380, 280, 14, C(90, 60, 40)); fillCircle(sx(1560), 340, 36, C(250, 250, 250)); rect(sx(1620), 350, 100, 40, C(150, 150, 150)); text("YARD", sx(1640), 300, 1.6f, C(60, 120, 90), 1);
        rect(sx(2130), 360, 160, 230, C(60, 90, 70)); text("TEACHERS", sx(2210), 330, 1.5f, WHITE, 1);
        rect(sx(110), 380, 120, 210, C(40, 150, 90)); text("BUS", sx(170), 350, 1.6f, WHITE, 1);
        return;
    }
    if (th == "roomint") {
        gradient(46, 560, mix(f.wall, WHITE, 0.08f), dim(f.wall, 0.85f)); rect(0, 560, SCR_W, 30, dim(f.wall, 0.6f)); rect(0, 590, SCR_W, 130, C(98, 72, 52)); rect(0, 586, SCR_W, 6, f.trim);
        rect(sx(1250), 150, 220, 240, C(150, 200, 240)); frameR(sx(1250), 150, 220, 240, C(40, 40, 50), 6); rect(sx(1356), 150, 8, 240, C(40, 40, 50));
        rect(sx(160), 380, 120, 210, C(40, 34, 30)); frameR(sx(160), 380, 120, 210, f.trim, 4);
        if (f.key == "room_amir") { rect(sx(380), 500, 280, 90, C(235, 235, 235)); rect(sx(380), 470, 90, 40, C(249, 115, 22)); rect(sx(820), 470, 240, 20, C(110, 80, 60)); rect(sx(840), 420, 120, 50, C(30, 40, 60)); for (int k = 0; k < 8; k++) rect(sx(1240) + (k % 4) * 52, 410 + (k / 4) * 60, 40, 44, C(240, 230, 200)); }
        else if (f.key == "room_dalia") { rect(sx(380), 556, 170, 34, C(120, 190, 255)); fillCircle(sx(430), 546, 14, C(120, 190, 255)); rect(sx(820), 470, 200, 20, C(240, 180, 200)); rect(sx(1240), 330, 240, 140, C(250, 245, 230)); for (int k = 0; k < 5; k++) rect(sx(1255) + k * 44, 350 + (k % 2) * 30, 34, 20, C(255, 120, 150)); }
        else { rect(sx(380), 560, 140, 30, C(150, 120, 80)); rect(sx(420), 540, 60, 22, C(150, 120, 80)); rect(sx(900), 380, 220, 210, C(80, 60, 50)); for (int k = 0; k < 4; k++) rect(sx(910), 400 + k * 50, 200, 6, C(40, 30, 26)); rect(sx(1240), 470, 130, 120, C(70, 74, 84)); rect(sx(1250), 440, 110, 40, C(255, 255, 255)); }
        text(f.name, 640, 110, 1.8f, C(255, 255, 255, 110), 1, 4);
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
    std::string l2 = c.id; Col c2 = C(255, 190, 120);
    if (c.isBot) {
        const BotInfo* b = botOf(c.key);
        if (b) {
            CharDef* oc = charBy(b->ownerKey);
            l2 = b->ownerKey == "amir" ? "YOUR BOT" : oc ? "Owner: " + oc->name : "The building's bot";
            if (b->ownerKey == "amir") c2 = C(120, 255, 190);
        }
    }
    float w = (float)std::max(textW(c.name, 1.2f), textW(l2, 0.9f)) + 16;
    float y = GY - 110 * h - 64;
    rect(x - w / 2, y, w, 44, C(0, 0, 0, 170));
    text(c.name, x, y + 3, 1.2f, WHITE, 1);
    text(l2, x, y + 24, 0.9f, c2, 1);
}

static void drawWorld() {
    FloorDef* f = floorBy(g.floorKey);
    if (!f) return;
    float fx = g.px;
    if (!g.focusKey.empty()) { auto it = g.npcs.find(g.focusKey); if (it != g.npcs.end() && it->second.floor == g.floorKey) fx = it->second.x; }
    float camX = std::max(0.0f, std::min(f->width - SCR_W, fx - 640));
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
        bool plain = (o.id.rfind("p_", 0) == 0 || o.id == "backdoor" || o.id == "frontdoor" || o.id == "reception" || o.id == "vending" || o.id == "fan" || o.id == "car1" || o.id == "car2" || o.id == "tank" || o.id == "shaftgap");
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
    if (g.coopOn && P1EMT > 0) drawEmote(g.px - camX, GY - 112 * pc->look.h - 70, P1EM, g.frame);
    // co-op players
    if (g.coopOn) for (int k = 0; k < 3; k++) {
        CoPlayer& cp = g.co[k]; CharDef* cc = charBy(cp.key);
        if (!cp.on || !cc || cp.floor != g.floorKey) continue;
        float x = cp.x - camX;
        if (cc->isBot) drawBot(x, GY, cc->look.shirt, g.frame + k * 9, cp.dir); else drawPerson(x, GY, cp.dir, cc->look, cp.walk, cp.moving);
        float hh = cc->isBot ? 0.6f : cc->look.h;
        text("P" + std::to_string(k + 2) + " " + cc->name, x, GY - 112 * hh - 46, 1.1f, k == 0 ? C(120, 220, 255) : k == 1 ? C(255, 150, 200) : C(200, 255, 130), 1, 2);
        if (cp.emoteT > 0) drawEmote(x, GY - 112 * hh - 70, cp.em, g.frame);
    }
    // co-op chat log + hint
    if (g.coopOn) {
        for (size_t i = 0; i < CHATLOG.size(); i++) {
            float y = 560 + i * 24 - (CHATLOG.size() - 1) * 24;
            std::string s = CHATLOG[i].who + ": " + CHATLOG[i].txt;
            rect(14, y - 4, 16 + s.size() * 11.0f, 22, C(0, 0, 0, 140));
            text(s, 22, y, 1.1f, C(255, 255, 255), 0, 1);
        }
        text(std::string("L chat: ") + QCHAT[P1PH] + "   R next", 14, 690, 1.0f, C(220, 220, 220), 0, 1);
    }
    // prompt
    if (!g.elevOpen && g.fadePhase == 0 && (g.vs == V_AWAIT || g.vs == V_NONE)) {
        Target t = nearestTarget();
        if (t.kind >= 0) {
            float x = g.px - camX;
            std::string s = "A  " + t.label + (t.kind == 0 ? "    X  Say..." : "");
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
    int chn = g.chapter;
    text("CH" + std::to_string(chn) + "  DAY " + std::to_string(g.day), 20, 10, 1.8f, ORANGE);
    if (f) text(f->name, 640, 10, 1.8f, WHITE, 1);
    text("ITEMS " + std::to_string(g.inv.size()) + "   Y PHONE", SCR_W - 20, 10, 1.8f, WHITE, 2);
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
    rect(bx, by, bw, bh, g.st.hiCon ? C(0, 0, 0, 255) : C(14, 22, 52, 238)); frameR(bx, by, bw, bh, g.st.hiCon ? C(255, 255, 0) : WHITE, 3);
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
        for (size_t i = 0; i < ls.size(); i++) text(ls[i], bx + 28, by + 20 + i * (g.st.bigText ? 50 : 42), g.st.bigText ? 2.4f : 1.9f, g.dWho.empty() ? C(215, 220, 235) : WHITE);
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

// ---------------------------------------------------------------- elevator interior
static void thickLine(float x1, float y1, float x2, float y2, float t, Col c) {
    float dx = x2 - x1, dy = y2 - y1, l = std::max(1.0f, hypotf(dx, dy));
    int n = (int)l;
    for (int i = 0; i <= n; i += 2) rect(x1 + dx * i / n - t / 2, y1 + dy * i / n - t / 2, t, t, c);
}
static void drawTri(float cx, float cy, float w, bool up, Col c) {
    for (int r = 0; r < (int)w; r += 2) {
        float ww = up ? r : w - r;
        rect(cx - ww / 2, cy - w / 2 + r, ww, 2, c);
    }
}
static std::string lvlStr(int lv) { return lv == 0 ? "L" : (lv > 0 ? "+" : "") + std::to_string(lv); }

static void drawElevatorScene() {
    float shx = 0, shy = 0;
    if (g.elevPhase == 3) { shx = sinf(g.frame * 2.3f) * 1.6f; shy = cosf(g.frame * 1.9f) * 1.4f; }
    const float BX0 = 400, BX1 = 880, BY0 = 120, BY1 = 560;
    // ---- ceiling
    for (int y = 0; y < (int)BY0; y++) {
        float t = y / BY0; float l = BX0 * t, r = SCR_W - BX0 * t;
        rect(l, y, r - l, 1, mix(C(206, 208, 214), C(150, 154, 164), t));
    }
    // light panel
    for (int y = 22; y < 100; y++) {
        float t = y / BY0; float l = BX0 * t + 80 * (1 - t) + 40, r = SCR_W - l;
        rect(l, y, r - l, 1, C(255, 250, 228));
    }
    // ---- side walls
    for (int x = 0; x < (int)BX0; x++) {
        float t = x / BX0; float top = BY0 * t, bot = SCR_H - (SCR_H - BY1) * t;
        float lx = x, rx = SCR_W - 1 - x;
        Col cl = mix(C(112, 118, 130), C(160, 166, 178), t);
        rect(lx, top, 1, bot - top, cl);
        rect(rx, top, 1, bot - top, dim(cl, 0.92f));
    }
    float seams[] = {0, 130, 240, 320, 370};
    for (float sx : seams) for (int k = 0; k < 2; k++) {
        float x = k ? SCR_W - 1 - sx : sx; float t = std::min(1.0f, sx / BX0);
        rect(x, BY0 * t, 3, SCR_H - (SCR_H - BY1) * t - BY0 * t, C(70, 74, 86));
    }
    // handrails
    for (int x = 0; x < (int)BX0; x += 2) {
        float t = x / BX0; float top = BY0 * t, bot = SCR_H - (SCR_H - BY1) * t; float y = top + (bot - top) * 0.62f;
        rect(x, y, 3, 9 - 5 * t, C(225, 228, 235)); rect(SCR_W - 1 - x - 2, y, 3, 9 - 5 * t, C(205, 208, 216));
    }
    // ---- floor (tiles in perspective)
    for (int y = (int)BY1; y < SCR_H; y++) {
        float t = (y - BY1) / (SCR_H - BY1); float l = BX0 * (1 - t), r = BX1 + BX0 * t;
        rect(l, y, r - l, 1, mix(C(58, 60, 70), C(34, 36, 44), t));
    }
    for (int k = -8; k <= 8; k++) {
        float xb = 640 + k * 150; float x560 = 640 + (xb - 640) * (BY1 - 300) / (SCR_H - 300);
        line(x560, BY1, xb, SCR_H, C(0, 0, 0, 80));
    }
    for (float y : {575.0f, 600.0f, 640.0f, 690.0f}) rect(BX0 * (1 - (y - BY1) / (SCR_H - BY1)), y, SCR_W - 2 * BX0 * (1 - (y - BY1) / (SCR_H - BY1)), 2, C(0, 0, 0, 70));
    // ---- back wall
    rect(BX0, BY0, BX1 - BX0, BY1 - BY0, C(150, 156, 168));
    for (int x = (int)BX0; x < (int)BX1; x += 40) rect(x, BY0, 2, BY1 - BY0, C(255, 255, 255, 18));
    rect(BX0, BY0, BX1 - BX0, 14, C(110, 116, 128));
    // doorway
    const float DX0 = 480, DX1 = 800, DY0 = 206, DY1 = 560;
    // view through the doors
    int viewIdx = (g.elevPhase >= 4 && g.elevPhase <= 6) ? g.elevTo : g.elevFrom;
    SDL_Rect clip = {(int)(DX0 + shx), (int)DY0, (int)(DX1 - DX0), (int)(DY1 - DY0)};
    rect(DX0, DY0, DX1 - DX0, DY1 - DY0, C(20, 20, 26));
    if (g.elevDoor > 0.02f) {
        SDL_RenderSetClipRect(G.ren, &clip);
        drawTheme(FLOORS[viewIdx], 0);
        float dd = FLOORS[viewIdx].inElevator ? 1 : 0;
        text(FLOORS[viewIdx].name, 640, DY0 + 24, 1.6f, C(255, 255, 255, 200), 1, 2);
        text(lvlStr(FLOORS[viewIdx].level), 640, DY0 + 52, 2.2f, C(255, 160, 80, 220), 1);
        SDL_RenderSetClipRect(G.ren, nullptr);
    }
    // door panels
    float o = g.elevDoor, pw = 160 * (1 - o);
    for (int k = 0; k < 2; k++) {
        float px0 = k == 0 ? DX0 : DX1 - pw;
        if (pw < 1) continue;
        rect(px0 + shx, DY0, pw, DY1 - DY0, C(186, 190, 200));
        for (int y = (int)DY0; y < (int)DY1; y += 6) rect(px0 + shx, y, pw, 1, C(255, 255, 255, 22));
        rect(px0 + shx, DY0, pw, (DY1 - DY0), C(0, 0, 0, 0));
        rect(k == 0 ? px0 + shx : px0 + shx + pw - 8, DY0, 8, DY1 - DY0, C(120, 126, 140));
        if (g.elevPhase == 3) for (int b = 0; b < 4; b++) { float yy = DY0 + fmodf(g.frame * 6.0f + b * 90, DY1 - DY0); rect(px0 + shx, yy, pw, 14, C(255, 255, 255, 26)); }
        if (o < 0.05f) { text("14", px0 + (k == 0 ? pw - 32 : 32), DY0 + 140, 2.4f, ORANGE, 1); }
    }
    frameR(DX0 - 8 + shx, DY0 - 8, DX1 - DX0 + 16, DY1 - DY0 + 8, C(88, 94, 108), 8);
    rect(DX0 - 8, DY1 - 2, DX1 - DX0 + 16, 8, C(70, 74, 86));
    // indicator above the doors
    rect(560, 136, 160, 60, C(8, 8, 12)); frameR(560, 136, 160, 60, C(60, 64, 76), 4);
    int curLv = FLOORS[g.elevCur].level;
    bool ding = g.elevPhase == 4 && (g.elevT / 4) % 2 == 0;
    Col led = ding ? C(255, 240, 160) : C(255, 120, 30);
    text(lvlStr(curLv), 650, 148, 3.0f, led, 1);
    if (g.elevPhase == 3 && g.elevPath.size() > 1) {
        bool goingUp = FLOORS[g.elevTo].level > FLOORS[g.elevFrom].level;
        drawTri(590, 166, 22, goingUp, (g.frame / 8) % 2 ? led : dim(led, 0.4f));
    }
    if (ding) text("*DING*", 640, 100, 1.6f, C(30, 30, 40), 1, 3);
    // ---- control panel (right)
    std::vector<int> l = elevList();
    float PX = 944, PY = 80, PW = 296, PH = 560;
    rect(PX, PY, PW, PH, C(92, 98, 112)); frameR(PX, PY, PW, PH, C(200, 204, 214), 4); rect(PX + 6, PY + 6, PW - 12, PH - 12, C(60, 64, 76));
    rect(PX + 16, PY + 16, PW - 32, 66, C(8, 8, 12)); frameR(PX + 16, PY + 16, PW - 32, 66, C(40, 44, 54), 3);
    int showIdx = g.elevPhase >= 3 ? g.elevCur : (l.empty() ? 0 : l[std::min<int>(g.elevSel, (int)l.size() - 1)]);
    text(FLOORS[showIdx].name, PX + PW / 2, PY + 22, 1.3f, C(255, 150, 60), 1);
    text(lvlStr(FLOORS[showIdx].level), PX + PW / 2, PY + 46, 2.4f, C(255, 190, 110), 1);
    for (size_t i = 0; i < l.size(); i++) {
        float cx = PX + 90 + (i % 2) * 118, cy = PY + 128 + (i / 2) * 46;
        bool sel = g.elevPhase == 2 && (int)i == g.elevSel;
        bool target = g.elevPhase >= 3 && l[i] == g.elevTo && g.elevPhase < 6;
        bool here = l[i] == (g.elevPhase >= 5 ? g.elevTo : g.elevFrom);
        fillCircle(cx, cy, 24, C(210, 214, 224));
        fillCircle(cx, cy, 20, target ? C(255, 200, 90) : C(48, 52, 62));
        if (target) fillCircle(cx, cy, 30, C(255, 190, 80, 55));
        if (sel) { for (int k = 0; k < 3; k++) { float rr = 28 + k; for (int a = 0; a < 48; a++) { float an = a * 0.1309f; rect(cx + cosf(an) * rr - 1, cy + sinf(an) * rr - 1, 3, 3, ORANGE); } } }
        text(lvlStr(FLOORS[l[i]].level), cx, cy - 8, 1.1f, target ? BLACK : WHITE, 1);
        if (here) rect(cx + 20, cy - 24, 8, 8, C(90, 255, 160));
    }
    // ---- player
    Look pl = playerLook(); pl.h *= 1.9f;
    drawPerson(250 + shx, 690 + shy, 1, pl, g.frame, false);
    // ---- light flicker / vignette while riding
    if (g.elevPhase == 3 && (g.frame % 97) < 3) rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, 70));
    if (g.elevPhase == 2) {
        text("A Press floor     B Leave", 560, 664, 1.5f, WHITE, 1);
    }
    for (int y = 0; y < SCR_H; y += 2) rect(0, y, SCR_W, 1, C(0, 0, 0, 14));
}

// ---------------------------------------------------------------- blueprint menus
static Col themeCol() { static const Col t[6] = {{28, 66, 156, 255}, {18, 22, 56, 255}, {24, 96, 70, 255}, {150, 70, 40, 255}, {140, 40, 90, 255}, {50, 54, 62, 255}}; return t[APP.theme % 6]; }
static void blueprintBG() {
    rect(0, 0, SCR_W, SCR_H, themeCol());
    for (int x = 0; x < SCR_W; x += 40) rect(x, 0, (x % 200 == 0) ? 2 : 1, SCR_H, C(255, 255, 255, (x % 200 == 0) ? 34 : 15));
    for (int y = 0; y < SCR_H; y += 40) rect(0, y, SCR_W, (y % 200 == 0) ? 2 : 1, C(255, 255, 255, (y % 200 == 0) ? 34 : 15));
    Col wcol = C(255, 255, 255, 190);
    dashH(50, 84, 1180, wcol); dashH(50, 636, 1180, wcol); dashV(56, 70, 580, wcol); dashV(1222, 70, 580, wcol);
    // corner marks
    for (int sx = 0; sx < 2; sx++) for (int sy = 0; sy < 2; sy++) {
        float x = sx ? 1222 : 56, y = sy ? 636 : 84;
        rect(x - 14, y, 30, 2, WHITE); rect(x, y - 14, 2, 30, WHITE);
    }
    text(g_hint, 640, 668, 1.5f, WHITE, 1, 2);
    if (g_backBtn) { frameR(56, 22, 140, 38, WHITE, 2); text("< BACK", 126, 30, 1.5f, WHITE, 1, 2); HITS.push_back({56, 22, 140, 38, 2, 0}); }
    text("ILOT14 WORLD  " VERSION, 1210, 52, 1.2f, C(255, 255, 255, 150), 2);
}

static void bpButton(float x, float y, float w, float h, const std::string& label, bool sel, bool enabled = true, int idx = -1) {
    if (idx >= 0) HITS.push_back({x, y, w, h, 0, idx});
    Col c = enabled ? WHITE : C(255, 255, 255, 90);
    float sc = h < 50 ? 1.7f : 2.0f;
    if (sel) { rect(x, y, w, h, WHITE); text(label, x + 28, y + h / 2 - 8 * sc, sc, themeCol(), 0, 2); rect(x - 22, y + h / 2 - 8, 14, 16, ORANGE); }
    else { frameR(x, y, w, h, c, 3); text(label, x + 28, y + h / 2 - 8 * sc, sc, c, 0, 2); }
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
    text("\xC3\x8E L O T 1 4", 110, 98, 6.6f, WHITE, 0, 4);
    text("W O R L D   //   BLUEPRINT SERIES", 114, 180, 1.5f, C(255, 255, 255, 200));
    SlotInfo last; if (g.st.lastSlot > 0) last = slotInfo(g.st.lastSlot);
    const char* names[] = {"CONTINUE", "NEW GAME", "SAVE SLOTS", "DAY SELECT", "CHAPTERS", "CO-OP", "CUSTOMIZE", "EXTRAS", "SETTINGS", "EXIT TO HOMEBREW MENU"};
    for (int i = 0; i < 10; i++) bpButton(130, 212 + i * 42, 560, 36, names[i], g.sel == i, i != 0 || last.exists, i);
    if (g.msgT > 0) text(g.msg, 130, 642, 1.4f, C(255, 220, 120));
    if (g.sel == 0 && last.exists) text("Slot " + std::to_string(g.st.lastSlot) + " - Ch." + std::to_string(last.chapter) + " Day " + std::to_string(last.day), 710, 224, 1.3f, C(255, 255, 255, 180));
    if (g.sel == 4) text(g.st.unl[2] ? "Next chapters unlocked!" : "5 chapters, 191 days", 710, 392, 1.3f, C(120, 255, 190));
    if (g.sel == 5) text("Local multiplayer: up to 4 players", 710, 434, 1.3f, C(120, 255, 190));
    if (g.sel == 7) text("Badges, redeem codes, lore, endings", 710, 518, 1.3f, C(120, 255, 190));
    text(std::to_string(U_BADGES.size()) + "/" + std::to_string(NBADGES) + " badges", 1210, 668, 1.2f, C(255, 255, 255, 150), 2);
}

static void drawSlotList(const std::string& heading, const std::string& hint) {
    blueprintBG();
    text(heading, 110, 110, 3.4f, WHITE, 0, 6);
    text(hint, 114, 175, 1.4f, C(255, 255, 255, 190));
    for (int i = 1; i <= 3; i++) {
        SlotInfo si = slotInfo(i);
        float y = 230 + (i - 1) * 124;
        bool s = g.sel == i - 1;
        HITS.push_back({110, y, 1060, 104, 0, i - 1});
        if (s) rect(110, y, 1060, 104, C(255, 255, 255, 40));
        frameR(110, y, 1060, 104, WHITE, s ? 4 : 2);
        text("SLOT " + std::to_string(i), 140, y + 16, 2.4f, s ? ORANGE : WHITE, 0, 3);
        if (si.exists) {
            std::string t = dayTitleOf(si.chapter, si.day);
            text("CH" + std::to_string(si.chapter) + "  -  DAY " + std::to_string(si.day) + "  -  " + t, 140, y + 60, 1.7f, WHITE);
            text(fmtTime(si.frames), 1150, y + 16, 1.7f, C(255, 255, 255, 190), 2);
        } else text("EMPTY", 140, y + 60, 1.7f, C(255, 255, 255, 140));
    }
}

static void drawDaySelect() {
    blueprintBG();
    text("DAY SELECT", 110, 90, 3.4f, WHITE, 0, 6);
    Col cc[6] = {WHITE, WHITE, ORANGE, C(120, 255, 220), C(255, 120, 150), C(255, 230, 120)};
    int ch = g.dsCh, len = CH_LEN[ch];
    for (int c = 1; c <= 5; c++) {
        float x = 100 + (c - 1) * 214; bool un = g.st.unl[c], on = c == ch;
        HITS.push_back({x, 148, 204, 40, 5, c});
        if (on) rect(x, 148, 204, 40, cc[c]);
        else frameR(x, 148, 204, 40, un ? cc[c] : C(255, 255, 255, 70), 2);
        text("CH" + std::to_string(c) + " " + std::string(CH_NAME[c]) + (un ? "" : " [LOCKED]"), x + 102, 158, 0.9f, on ? C(20, 30, 70) : (un ? cc[c] : C(255, 255, 255, 90)), 1);
    }
    int maxd = g.st.maxD[ch];
    for (int d = 1; d <= len; d++) {
        int i = d - 1; float x = 130 + (i % 8) * 128, y = 204 + (i / 8) * 76;
        bool un = d <= maxd, s = g.sel == i;
        HITS.push_back({x, y, 112, 68, 0, i});
        if (s) rect(x, y, 112, 68, WHITE); else frameR(x, y, 112, 68, un ? WHITE : C(255, 255, 255, 70), 2);
        rect(x + 4, y + 4, 104, 5, C(cc[ch].r, cc[ch].g, cc[ch].b, un ? 255 : 90));
        Col c = s ? themeCol() : (un ? WHITE : C(255, 255, 255, 80));
        text(std::to_string(d), x + 56, y + 16, 2.4f, c, 1);
        if (!un) text("LOCKED", x + 56, y + 48, 0.9f, c, 1);
    }
    int d = g.sel + 1;
    text("DAY " + std::to_string(d) + (d <= maxd ? "  -  " + dayTitleOf(ch, d) : "  -  ???"), 130, 596, 1.9f, ORANGE);
    text("Starts the day with the choices you had when you first got there.", 130, 630, 1.1f, C(255, 255, 255, 170));
}

static void drawSettings() {
    blueprintBG();
    text("SETTINGS", 110, 100, 3.4f, WHITE, 0, 6);
    const char* ts[] = {"SLOW", "NORMAL", "FAST", "INSTANT"};
    const char* au[] = {"OFF (press A)", "LONG", "NORMAL", "SHORT"};
    bpButton(130, 190, 760, 60, std::string("TEXT SPEED:   ") + ts[g.st.textSpeed], g.sel == 0, true, 0);
    bpButton(130, 270, 760, 60, std::string("AUTO-ADVANCE:   ") + au[g.st.autoAdv], g.sel == 1, true, 1);
    bpButton(130, 350, 760, 60, std::string("SCANLINES:   ") + (g.st.scanlines ? "ON" : "OFF"), g.sel == 2, true, 2);
    bpButton(130, 430, 760, 60, std::string("BIG TEXT:   ") + (g.st.bigText ? "ON" : "OFF"), g.sel == 3, true, 3);
    bpButton(130, 510, 760, 60, std::string("HIGH CONTRAST:   ") + (g.st.hiCon ? "ON" : "OFF"), g.sel == 4, true, 4);
    bpButton(130, 590, 760, 60, "BACK", g.sel == 5, true, 5);
    text("Hold Y during dialogue to fast-forward it.", 134, 680, 1.3f, C(255, 255, 255, 190));
}

static void drawPause() {
    rect(0, 0, SCR_W, SCR_H, C(0, 20, 60, 190));
    frameR(300, 80, 680, 560, WHITE, 3);
    text("PAUSED", 640, 100, 3.2f, WHITE, 1, 8);
    const char* names[] = {"RESUME", "SAVE PROGRESS", "BOT REGISTRY", "CUSTOMIZE", "SETTINGS", "QUIT TO TITLE"};
    HITS.push_back({0, 0, SCR_W, SCR_H, 2, 0});
    HITS.push_back({300, 80, 680, 560, 1, g.sel});
    for (int i = 0; i < 6; i++) bpButton(350, 175 + i * 62, 580, 50, names[i], g.sel == i, true, i);
    text("Saves the start of Chapter " + std::to_string(g.chapter) + " - Day " + std::to_string(g.day), 640, 560, 1.3f, C(255, 255, 255, 180), 1);
    if (g.msgT > 0) text(g.msg, 640, 590, 1.5f, C(255, 220, 120), 1);
}

// ---------------------------------------------------------------- effects overlay
static void drawFX() {
    for (auto& p : g.parts) {
        float a = std::min(1.0f, p.life / 25.0f);
        if (p.type == 3) line(p.x, p.y, p.x + p.vx * 1.5f, p.y - p.vy * 1.5f, C(p.c.r, p.c.g, p.c.b, 140));
        else if (p.type == 4) { rect(p.x - 7, p.y - 3, 14, 9, C(250, 210, 30)); rect(p.x - 2, p.y - 3, 3, 9, BLACK); rect(p.x + 2, p.y - 8, 8, 4, C(220, 240, 255, 190)); }
        else if (p.type == 2) { rect(p.x - 2, p.y - 2, 5, 5, C(p.c.r, p.c.g, p.c.b, (int)(255 * a))); }
        else rect(p.x, p.y, 9, 6, C(p.c.r, p.c.g, p.c.b, 230));
    }
    if (g.dark > 0) {
        float d = g.dark;
        if (g.flickerT > 0 && (g.flickerT / 5) % 2) d *= 0.4f;
        rect(0, 0, SCR_W, SCR_H, C(0, 5, 20, (int)(235 * d)));
    } else if (g.flickerT > 0 && (g.flickerT / 4) % 3 == 0) rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, 150));
    if (g.bars > 0.01f) {
        float h = 64 * g.bars;
        rect(0, 0, SCR_W, h, BLACK); rect(0, SCR_H - h, SCR_W, h, BLACK);
    }
}

// ---------------------------------------------------------------- chapters / customize / registry screens
static void drawChapters() {
    blueprintBG();
    text("CHAPTERS", 110, 100, 3.4f, WHITE, 0, 6);
    struct Ch { const char* n; const char* t; std::string d; bool un; };
    Ch chs[5] = {{"CHAPTER 1  -  31 DAYS", "LOST THE ASH", "The Dalia quest, the hornets, the Backrooms, Prime, Îlot14 Day.", true},
                 {"CHAPTER 2  -  35 DAYS", "FURTHER INN", g.st.unl[2] ? "Reopen the Inn. The ledger, the knocking, Room 000." : "Finish Day 31 of Chapter 1 to unlock.", g.st.unl[2]},
                 {"CHAPTER 3  -  40 DAYS", "LOWEST POINT", g.st.unl[3] ? "Level 18. Doors with names. The shape behind the glass." : "Finish Day 35 of Chapter 2 to unlock.", g.st.unl[3]},
                 {"CHAPTER 4  -  45 DAYS", "NEVER", g.st.unl[4] ? "The list of Nevers. Signs, rules and the building's oldest promise." : "Finish Day 40 of Chapter 3 to unlock.", g.st.unl[4]},
                 {"CHAPTER 5", "SAFE ASCENT", g.st.unl[5] ? "The long safe climb back up." : "Finish Day 45 of Chapter 4.", g.st.unl[5]}};
    for (int i = 0; i < 5; i++) {
        float y = 140 + i * 100; bool sel = g.sel == i;
        HITS.push_back({110, y, 1060, 92, 0, i});
        if (sel) rect(110, y, 1060, 92, C(255, 255, 255, 40));
        frameR(110, y, 1060, 92, chs[i].un ? WHITE : C(255, 255, 255, 90), sel ? 4 : 2);
        Col c = chs[i].un ? WHITE : C(255, 255, 255, 110);
        text(chs[i].n, 140, y + 8, 1.5f, sel ? ORANGE : c, 0, 4);
        text(chs[i].t, 140, y + 34, 1.9f, c);
        text(chs[i].d, 140, y + 66, 1.2f, C(255, 255, 255, chs[i].un ? 190 : 110));
        if (!chs[i].un) { rect(1066, y + 24, 60, 44, C(255, 255, 255, 40)); frameR(1066, y + 24, 60, 44, C(255, 255, 255, 140), 3); text("LOCK", 1096, y + 36, 1.0f, C(255, 255, 255, 170), 1); }
    }
    if (g.msgT > 0) text(g.msg, 110, 650, 1.4f, C(255, 220, 120));
}

static void drawCustomize() {
    blueprintBG();
    text("CUSTOMIZE", 110, 92, 2.2f, WHITE, 0, 4);
    Look l = lookFromAppear(APP); l.h *= 2.4f;
    frameR(800, 150, 360, 480, WHITE, 3); dashH(810, 580, 340, C(255, 255, 255, 120));
    int dirv = ((g.custSpin / 90) % 2) ? -1 : 1;
    drawPerson(980, 580, dirv, l, g.frame, false);
    text("YOU", 980, 160, 1.6f, WHITE, 1, 6);
    struct Row { std::string a, b; };
    std::vector<Row> rows = {
        {"SKIN", SKIN_N[APP.skin]}, {"HAIR STYLE", HAIR_N[APP.hairStyle]}, {"HAIR COLOR", std::to_string(APP.hairCol + 1) + " / 12"},
        {"HEIGHT", HEIGHT_N[APP.height]}, {"CLOTHES", TOP_N[APP.top]}, {"CLOTHES COLOR", std::to_string(APP.topCol + 1) + " / 12"},
        {"PANTS", std::to_string(APP.pants + 1) + " / 8"}, {"SHOES", std::to_string(APP.shoes + 1) + " / 6"}, {"EYES", EYES_N[APP.eyes]},
        {"HAT / EXTRA", ACC_N[APP.acc]}, {"BACK", BACK_N[APP.back]}, {"FACE", FACE_N[APP.face]}, {"UI THEME", THEME_N[APP.theme]}, {"14 BADGE", APP.tag14 ? "ON" : "OFF"}, {"RESET", ""}, {"DONE", ""}};
    for (size_t i = 0; i < rows.size(); i++) {
        float y = 128 + i * 31; bool sel = g.custSel == (int)i;
        if (i < 14) { HITS.push_back({110, y, 320, 28, 3, (int)i}); HITS.push_back({430, y, 320, 28, 4, (int)i}); } else HITS.push_back({110, y, 640, 28, 0, (int)i});
        if (sel) { rect(110, y, 640, 28, WHITE); rect(88, y + 7, 14, 15, ORANGE); }
        else frameR(110, y, 640, 28, WHITE, 2);
        Col c = sel ? themeCol() : WHITE;
        text(rows[i].a, 130, y + 4, 1.4f, c, 0, 2);
        if (!rows[i].b.empty()) text((sel ? "<  " : "") + rows[i].b + (sel ? "  >" : ""), 730, y + 4, 1.4f, c, 2);
    }
    float sy = 632;
    auto sw = [&](const Col* cs, int n, int cur) { for (int i = 0; i < n; i++) { rect(110 + i * 44, sy, 36, 18, cs[i]); if (i == cur) frameR(108 + i * 44, sy - 2, 40, 22, WHITE, 2); } };
    if (g.custSel == 0) sw(SKIN_C, 8, APP.skin);
    if (g.custSel == 2) sw(HAIR_C, 12, APP.hairCol);
    if (g.custSel == 5) sw(TOP_C, 12, APP.topCol);
    if (g.custSel == 6) sw(PANT_C, 8, APP.pants);
    if (g.custSel == 7) sw(SHOE_C, 6, APP.shoes);
}

static void drawRegistry() {
    blueprintBG();
    text("BOT REGISTRY", 110, 100, 3.0f, WHITE, 0, 6);
    text("Everyone in the 14 owns a Cleaning bot.", 114, 150, 1.4f, C(255, 255, 255, 190));
    const BotInfo* mine = botOwnedBy("amir");
    if (mine) {
        rect(110, 178, 1060, 54, C(120, 255, 190, 60)); frameR(110, 178, 1060, 54, C(120, 255, 190), 3);
        text("YOUR BOT:  " + mine->name, 130, 186, 1.8f, C(120, 255, 190));
        text(mine->personality, 130, 210, 1.1f, WHITE);
    }
    int rowsVis = 7;
    int n = (int)BOTS.size();
    g.regScroll = std::max(0, std::min(n - rowsVis, g.regScroll));
    for (int r = 0; r < rowsVis && g.regScroll + r < n; r++) {
        const BotInfo& b = BOTS[g.regScroll + r];
        CharDef* oc = charBy(b.ownerKey);
        float y = 248 + r * 52;
        frameR(110, y, 1060, 46, C(255, 255, 255, 150), 2);
        std::string owner = b.ownerKey == "amir" ? "AMIR (you)" : oc ? oc->name + "  " + oc->id : "THE BUILDING";
        text(b.name, 130, y + 4, 1.5f, b.ownerKey == "amir" ? C(120, 255, 190) : WHITE);
        text("owner: " + owner, 130, y + 25, 1.0f, C(255, 190, 120));
        text(b.personality, 1150, y + 14, 1.1f, C(255, 255, 255, 190), 2);
    }
    text(std::to_string(g.regScroll + 1) + "-" + std::to_string(std::min(n, g.regScroll + rowsVis)) + " / " + std::to_string(n) + "   Up / Down: scroll", 640, 622, 1.2f, C(255, 255, 255, 170), 1);
}

static void drawEnding() {
    rect(0, 0, SCR_W, SCR_H, C(8, 10, 22));
    float a = std::min(1.0f, g.cT / 90.0f);
    text("CHAPTER " + std::to_string(g.endCh) + " COMPLETE", 640, 200, 4, C(255, 255, 255, (int)(255 * a)), 1, 8);
    text(g.endCh < 5 ? std::string(CH_NAME[g.endCh]) + " - done" : "TO BE CONTINUED...", 640, 300, 3, C(249, 115, 22, (int)(255 * a)), 1, 6);
    if (g.endCh < 5 && g.cT > 100) text("CHAPTER " + std::to_string(g.endCh + 1) + ": " + std::string(CH_NAME[g.endCh + 1]) + " - UNLOCKED. Press Continue!", 640, 520, 2, C(120, 255, 190, 220), 1, 3);
    text("LOST OF ASHES  -  the story goes on", 640, 400, 1.8f, C(255, 255, 255, (int)(200 * a)), 1);
    text("Thanks for playing  " VERSION, 640, 460, 1.6f, C(255, 255, 255, (int)(160 * a)), 1);
    if (g.cT > 120) text("A", 640, 580, 2, C(255, 255, 255, 120 + (int)(100 * sinf(g.cT * 0.12f))), 1);
}


// ---------------------------------------------------------------- touch warning (in-game touches are not supported)
static void drawTouchWarn() {
    if (g.touchWarn <= 0) return;
    int a = std::min(255, g.touchWarn * 8);
    float w = 330, h = 104, x = SCR_W - w - 14, y = 14;
    rect(x, y, w, h, C(24, 10, 14, a)); frameR(x, y, w, h, C(255, 70, 70, a), 3);
    float cx = x + 52, cy = y + 66, k = 0.36f;
    Col sk = C(240, 200, 160, a), ol = C(60, 40, 30, a), red = C(255, 60, 60, a);
    rect(cx - 44 * k, cy - 6 * k, 88 * k, 66 * k, ol); rect(cx - 40 * k, cy - 2 * k, 80 * k, 58 * k, sk);
    float fl[4] = {58, 72, 78, 66};
    for (int i = 0; i < 4; i++) { float fx = cx + (-40 + i * 20) * k; rect(fx - 1, cy - (4 + fl[i] + 2) * k, 20 * k, (fl[i] + 4) * k, ol); rect(fx, cy - (4 + fl[i]) * k, 16 * k, (fl[i] + 2) * k, sk); }
    rect(cx - 70 * k, cy + 6 * k, 34 * k, 24 * k, ol); rect(cx - 66 * k, cy + 10 * k, 30 * k, 16 * k, sk);
    for (int j = 0; j < 60; j++) { float an = j * 0.1047f; rect(cx + cosf(an) * 36 - 2, cy - 14 + sinf(an) * 36 - 2, 4, 4, red); }
    thickLine(cx - 26, cy - 40, cx + 26, cy + 12, 5, red);
    text("PLAY WITH", x + 200, y + 18, 1.9f, C(255, 255, 255, a), 1, 2);
    text("JOY-CONS", x + 200, y + 46, 2.2f, C(255, 90, 90, a), 1, 2);
    text("Touch is for menus only", x + 200, y + 80, 1.0f, C(255, 255, 255, (int)(a * 0.8f)), 1);
}

// ================================================================ v0.5 screens: extras, redeem, badges, lore, co-op, keyboard, scare
static void drawKeyboard(float y0) {
    const float kw = 78, kh = 54, gp = 6, x0 = 640 - (10 * (kw + gp) - gp) / 2;
    for (int r = 0; r < 5; r++) {
        int n = g.kb.rowLen(r);
        for (int c = 0; c < n; c++) {
            float w = r < 4 ? kw : (10 * (kw + gp) - gp - 2 * gp) / 3.0f;
            float x = x0 + c * (w + gp), y = y0 + r * (kh + gp);
            bool sel = g.kb.r == r && g.kb.c == c;
            HITS.push_back({x, y, w, kh, 6, r * 16 + c});
            if (sel) rect(x, y, w, kh, WHITE); else frameR(x, y, w, kh, C(255, 255, 255, 200), 2);
            std::string lab = r < 4 ? std::string(1, Kb::ROW(r)[c]) : (c == 0 ? "SPACE" : c == 1 ? "DEL" : "OK");
            text(lab, x + w / 2, y + 14, 2.0f, sel ? themeCol() : (r == 4 && c == 2 ? C(120, 255, 190) : WHITE), 1);
        }
    }
}

static void drawExtras() {
    blueprintBG();
    text("EXTRAS", 110, 100, 3.4f, WHITE, 0, 6);
    const char* n[3] = {"REDEEM CODE", "BADGES", "LORE & ENDINGS"};
    std::string d[3] = {"Type a code to unlock lore and custom endings.", std::to_string(U_BADGES.size()) + " of " + std::to_string(NBADGES) + " badges earned.", std::to_string(U_LORE.size()) + " of " + std::to_string(NLORE) + " entries unlocked."};
    for (int i = 0; i < 3; i++) {
        float y = 190 + i * 130; bool sel = g.extSel == i;
        HITS.push_back({110, y, 1060, 112, 0, i});
        if (sel) rect(110, y, 1060, 112, C(255, 255, 255, 40));
        frameR(110, y, 1060, 112, WHITE, sel ? 4 : 2);
        text(n[i], 140, y + 20, 2.4f, sel ? ORANGE : WHITE, 0, 4);
        text(d[i], 140, y + 70, 1.4f, C(255, 255, 255, 190));
    }
}

static void drawRedeem() {
    blueprintBG();
    text("REDEEM CODE", 110, 100, 3.4f, WHITE, 0, 6);
    text("Type a code, then press OK (or +).", 114, 160, 1.4f, C(255, 255, 255, 190));
    rect(300, 196, 680, 62, C(8, 18, 50)); frameR(300, 196, 680, 62, WHITE, 3);
    std::string t = g.kb.text + (((g.frame / 25) % 2) ? "_" : "");
    text(t, 320, 212, 2.6f, WHITE, 0, 4);
    drawKeyboard(280);
    text("Your outfit code: " + outfitCode(), 640, 672, 1.2f, C(150, 220, 255), 1, 2);
    if (g.redeemT > 0) text(g.redeemMsg, 640, 614, 1.6f, C(255, 220, 120), 1);
}

static void drawBadges() {
    blueprintBG();
    text("BADGES", 110, 90, 3.0f, WHITE, 0, 6);
    text(std::to_string(U_BADGES.size()) + " / " + std::to_string(NBADGES), 1150, 100, 2, ORANGE, 2);
    const int per = 8; int top = std::max(0, std::min(NBADGES - per, g.badgeSel - per / 2));
    for (int k = 0; k < per && top + k < NBADGES; k++) {
        int i = top + k; const BadgeDef& b = BADGE_LIST[i]; bool un = U_BADGES.count(b.id) > 0;
        float y = 146 + k * 58; bool sel = g.badgeSel == i;
        HITS.push_back({110, y, 1060, 52, 0, i});
        if (sel) rect(110, y, 1060, 52, C(255, 255, 255, 36));
        frameR(110, y, 1060, 52, un ? ORANGE : C(255, 255, 255, 90), sel ? 3 : 2);
        fillCircle(146, y + 26, 18, un ? ORANGE : C(255, 255, 255, 50));
        if (un) text("*", 146, y + 12, 2.0f, themeCol(), 1); else text("?", 146, y + 12, 2.0f, C(255, 255, 255, 120), 1);
        text(un ? b.name : "???", 185, y + 6, 1.6f, un ? WHITE : C(255, 255, 255, 120));
        text(b.desc, 185, y + 30, 1.1f, C(255, 255, 255, un ? 190 : 110));
    }
}

static void drawLore() {
    blueprintBG();
    text("LORE & ENDINGS", 110, 90, 3.0f, WHITE, 0, 6);
    std::vector<std::string> es = loreEntries();
    text(std::to_string(es.size()) + " / " + std::to_string(NLORE) + " unlocked.  Redeem codes in Extras to find more.", 114, 140, 1.2f, C(255, 255, 255, 190));
    if (es.empty()) { text("Nothing here yet.", 640, 330, 2.4f, C(255, 255, 255, 130), 1); return; }
    const int per = 8; int top = std::max(0, std::min((int)es.size() - per, g.loreSel - per / 2));
    for (int k = 0; k < per && top + k < (int)es.size(); k++) {
        int i = top + k; const LoreDef& L = LORE_LIST[loreIndex(es[i])]; bool sel = g.loreSel == i;
        float y = 172 + k * 56;
        HITS.push_back({110, y, 1060, 50, 0, i});
        if (sel) rect(110, y, 1060, 50, C(255, 255, 255, 36));
        frameR(110, y, 1060, 50, sel ? WHITE : C(255, 255, 255, 120), sel ? 3 : 2);
        text(std::string(L.kind), 130, y + 14, 1.2f, std::string(L.kind) == "ENDING" ? ORANGE : C(120, 255, 220));
        text(L.title, 260, y + 12, 1.7f, WHITE);
    }
}

static void drawLoreView() {
    blueprintBG();
    std::vector<std::string> es = loreEntries();
    if (g.loreSel >= (int)es.size()) return;
    const LoreDef& L = LORE_LIST[loreIndex(es[g.loreSel])];
    std::vector<std::string> pg = pagesOf(L.pages);
    text(std::string(L.kind) + ":  " + L.title, 640, 110, 2.8f, ORANGE, 1, 4);
    frameR(160, 170, 960, 380, WHITE, 3);
    // little animated backdrop
    for (int i = 0; i < 14; i++) { float x = 180 + fmodf(i * 97 + g.frame * (0.3f + (i % 3) * 0.2f), 920), y = 190 + (i * 53) % 340; fillCircle(x, y, 2 + i % 3, C(255, 255, 255, 40)); }
    int p = std::max(0, std::min((int)pg.size() - 1, g.lorePage));
    auto ls = wrapText(pg[p], 46);
    for (size_t i = 0; i < ls.size(); i++) text(ls[i], 640, 230 + i * 40, 2.0f, WHITE, 1);
    text("Page " + std::to_string(p + 1) + " / " + std::to_string(pg.size()), 640, 580, 1.3f, C(255, 255, 255, 170), 1);
    HITS.push_back({160, 170, 960, 380, 0, 0});
}

static std::vector<std::string> coopList() {
    std::vector<std::string> v;
    for (auto& c : CHARS) { if (c.key == "amir") continue; if (c.isBot) { const BotInfo* b = botOf(c.key); if (!b || !b->named) continue; } v.push_back(c.key); }
    return v;
}

static void drawCoop() {
    blueprintBG();
    text("CO-OP", 110, 96, 3.4f, WHITE, 0, 6);
    text("Player 1 is Amir. Players 2-4: press A on your own controller to join.", 114, 150, 1.3f, C(255, 255, 255, 200));
    text("Keyboard player 2:  I J K L move, U = A, O = B.   Left / Right changes your character.", 114, 176, 1.1f, C(255, 255, 255, 150));
    std::vector<std::string> ls = coopList();
    for (int k = 0; k < 3; k++) {
        float x = 110 + k * 360, y = 214; bool sel = g.sel == k;
        HITS.push_back({x, y, 340, 330, 0, k});
        if (sel) rect(x, y, 340, 330, C(255, 255, 255, 36));
        frameR(x, y, 340, 330, g.co[k].on ? C(120, 255, 190) : WHITE, sel ? 4 : 2);
        text("PLAYER " + std::to_string(k + 2), x + 170, y + 12, 1.8f, sel ? ORANGE : WHITE, 1, 3);
        if (g.co[k].on) {
            CharDef* c = charBy(ls[g.coSel[k] % ls.size()]);
            if (c) {
                if (c->isBot) drawBot(x + 170, y + 230, c->look.shirt, g.frame, 1);
                else { Look l = c->look; l.h *= 1.8f; drawPerson(x + 170, y + 270, 1, l, g.frame, false); }
                text("<  " + c->name + "  >", x + 170, y + 290, 1.6f, WHITE, 1);
            }
        } else text(std::string(k == 0 ? "Press A (pad 2 or U)" : "Press A on your pad"), x + 170, y + 150, 1.3f, C(255, 255, 255, 170), 1);
    }
    bool s3 = g.sel == 3;
    HITS.push_back({440, 566, 400, 52, 0, 3});
    bpButton(440, 566, 400, 52, "START CO-OP", s3, true, -1);
}

static void drawAskOverlay() {
    rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, 200));
    text(g.askPrompt.empty() ? "SAY SOMETHING" : g.askPrompt, 640, 70, 2.4f, ORANGE, 1, 4);
    rect(300, 130, 680, 62, C(8, 18, 50)); frameR(300, 130, 680, 62, WHITE, 3);
    text(g.kb.text + (((g.frame / 25) % 2) ? "_" : ""), 320, 146, 2.6f, WHITE, 0, 4);
    drawKeyboard(230);
    text("A type   B delete   Y clear   + / OK send", 640, 650, 1.2f, C(255, 255, 255, 170), 1);
}

static void drawScare(int T) {
    rect(0, 0, SCR_W, SCR_H, BLACK);
    if (T < 36) {   // glitch the game for a moment
        for (int i = 0; i < 40; i++) rect(rndi(0, 1280), rndi(0, 720), rndi(40, 400), rndi(2, 16), C(rndi(0, 255), rndi(0, 255), rndi(0, 255), 160));
        if (T > 18) rect(0, 0, SCR_W, SCR_H, BLACK);
        return;
    }
    if (T < 120) { if (T > 50 && T < 100) text("Ilot14 World has stopped responding.", 640, 340, 1.6f, C(160, 160, 160), 1); return; }
    float t = (T - 120) / 60.0f;
    float a = std::min(1.0f, t);
    // moonlit background
    gradient(0, 720, C((int)(30 * a), (int)(8 * a), (int)(20 * a)), C((int)(90 * a), (int)(30 * a), 0));
    fillCircle(1020, 150, 90, C(255, 200, 90, (int)(200 * a)));
    for (int i = 0; i < 6; i++) { float bx = fmodf(100 + i * 220 + (T * (1.5f + i * 0.3f)), 1400) - 60, by = 90 + i * 40 + sinf(T * 0.1f + i) * 20; rect(bx, by, 26, 8, C(10, 10, 14)); rect(bx - 12, by - 6, 14, 6, C(10, 10, 14)); rect(bx + 24, by - 6, 14, 6, C(10, 10, 14)); }
    for (int i = 0; i < 6; i++) { line(0, 0, 160 - i * 12, i * 40, C(230, 230, 230, 120)); line(1280, 0, 1120 + i * 12, i * 40, C(230, 230, 230, 120)); }
    // rope from the ceiling to the ankle
    float sway = sinf(T * 0.05f) * 26;
    float ax = 640 + sway, ay = 190;
    rect(639, 0, 3, 120, C(150, 120, 80)); line(640, 120, ax, ay, C(150, 120, 80));
    Look L = playerLook();
    // upside-down Amir: ankles at the top, head at the bottom
    rect(ax - 14, ay, 12, 100, L.pants); rect(ax + 2, ay, 12, 100, dim(L.pants, 0.85f));
    rect(ax - 16, ay - 6, 16, 10, L.shoes); rect(ax, ay - 6, 16, 10, L.shoes);
    rect(ax - 24, ay + 100, 48, 70, L.shirt); text("14", ax, ay + 124, 1.4f, BLACK, 1);
    rect(ax - 36, ay + 104, 12, 70, dim(L.shirt, 0.9f)); rect(ax + 24, ay + 104, 12, 70, dim(L.shirt, 0.9f));
    rect(ax - 36, ay + 174, 12, 14, L.skin); rect(ax + 24, ay + 174, 12, 14, L.skin);
    rect(ax - 6, ay + 168, 12, 8, L.skin);
    // pumpkin mask head
    fillCircle(ax, ay + 212, 40, C(240, 120, 20)); rect(ax - 4, ay + 244, 8, 12, C(60, 120, 40));
    float fl = 0.7f + 0.3f * sinf(T * 0.3f);
    for (int i = 0; i < 3; i++) { /* eyes (upside-down triangles) */ }
    rect(ax - 22, ay + 196, 14, 12, C(255, (int)(220 * fl), 60)); rect(ax + 8, ay + 196, 14, 12, C(255, (int)(220 * fl), 60));
    for (int k = 0; k < 5; k++) rect(ax - 20 + k * 9, ay + 222 + (k % 2) * 6, 7, 8, C(255, (int)(220 * fl), 60));
    text("BOO", ax, ay + 262, 1.6f, C(255, 255, 255, 180), 1);
    if (T > 220) text("HAPPY HALLOWEEN", 640, 560, 3.2f, C(255, 150, 40), 1, 6);
    if (T > 300) text("It's just a prank. Amir is fine. The pumpkin is the scary part.", 640, 620, 1.4f, C(255, 255, 255, 190), 1);
    if (T > 520) rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, (int)(255 * std::min(1.0f, (T - 520) / 40.0f))));
}

static void drawBadgeToast() {
    if (g.badgeToastT <= 0) return;
    float p = std::min(1.0f, g.badgeToastT / 20.0f) * std::min(1.0f, (260 - g.badgeToastT) / 12.0f);
    float w = 460, h = 70, x = 24, y = 720 - 24 - h * p;
    rect(x, y, w, h, C(10, 16, 36, 235)); frameR(x, y, w, h, ORANGE, 3);
    fillCircle(x + 38, y + 35, 22, ORANGE); text("*", x + 38, y + 18, 2.4f, themeCol(), 1);
    text("BADGE UNLOCKED", x + 76, y + 10, 1.1f, ORANGE);
    text(g.badgeToast, x + 76, y + 34, 1.7f, WHITE);
}

// ---------------------------------------------------------------- 14 logo + intro
static void polyFill(const std::vector<SDL_FPoint>& p, Col c) {
    std::vector<SDL_Vertex> v;
    for (auto& q : p) { SDL_Vertex x; x.position = q; x.color = {c.r, c.g, c.b, c.a}; x.tex_coord = {0, 0}; v.push_back(x); }
    std::vector<int> idx;
    for (size_t i = 1; i + 1 < p.size(); i++) { idx.push_back(0); idx.push_back((int)i); idx.push_back((int)i + 1); }
    SDL_RenderGeometry(G.ren, nullptr, v.data(), (int)v.size(), idx.data(), (int)idx.size());
}
// logo coordinates live in a 270x270 box; shapes are lists of convex polygons
typedef std::vector<std::vector<SDL_FPoint>> Shapes;
static void logoShapes(float ox, float oy, float s, const Shapes& sh, Col fill, float ay) {
    float t = 5 * s / 2.2f;
    auto map = [&](const std::vector<SDL_FPoint>& p) {
        std::vector<SDL_FPoint> a;
        for (auto& q : p) a.push_back({ox + (q.x - 128) * s, oy + (q.y - 130) * s + ay});
        return a;
    };
    for (auto& p : sh) {
        auto a = map(p);
        for (int d = 0; d < 12; d++) {
            float ang = d * 0.5236f;
            std::vector<SDL_FPoint> o;
            for (auto& q : a) o.push_back({q.x + cosf(ang) * t, q.y + sinf(ang) * t});
            polyFill(o, C(0, 0, 0, fill.a));
        }
    }
    for (auto& p : sh) polyFill(map(p), fill);
}
static void drawLogo14(float cx, float cy, float s, Col fill, float t1, float t4) {
    float e1 = 1 - (1 - t1) * (1 - t1), e4 = 1 - (1 - t4) * (1 - t4);
    Col f1 = fill; f1.a = (int)(255 * std::min(1.0f, t1 * 1.5f));
    Col f4 = fill; f4.a = (int)(255 * std::min(1.0f, t4 * 1.5f));
    Shapes one = {{{56, 98}, {104, 32}, {126, 26}, {80, 104}}, {{106, 28}, {126, 28}, {126, 112}, {106, 112}}};
    Shapes four = {{{138, 30}, {156, 30}, {156, 160}, {138, 160}}, {{138, 142}, {200, 142}, {200, 160}, {138, 160}}, {{182, 40}, {200, 40}, {200, 234}, {182, 234}}};
    logoShapes(cx, cy, s, one, f1, -(1 - e1) * 140 * s);
    logoShapes(cx, cy, s, four, f4, (1 - e4) * 140 * s);
}
static void drawPencil(float x, float y, float s, float a) {
    int al = (int)(255 * a);
    // tilted pencil: body, tip, lead
    float ang = 0.30f;
    auto P = [&](float px, float py) { return SDL_FPoint{x + (px * cosf(ang) - py * sinf(ang)) * s, y + (px * sinf(ang) + py * cosf(ang)) * s}; };
    polyFill({P(-7, -90), P(7, -90), P(7, 30), P(-7, 30)}, C(0, 0, 0, al));
    polyFill({P(-5, -88), P(5, -88), P(5, 28), P(-5, 28)}, C(30, 144, 255, al));
    polyFill({P(-7, 30), P(7, 30), P(0, 52)}, C(0, 0, 0, al));
    polyFill({P(-4, 32), P(4, 32), P(0, 46)}, C(240, 210, 170, al));
}
static void drawIntro(int t) {
    rect(0, 0, SCR_W, SCR_H, C(10, 8, 0));
    float cx = 640, cy = 300, s = 1.5f;
    // phase A (0-130): blue sketch version + pencil; phase B (130-250): turns orange, title text
    float k = std::min(1.0f, std::max(0.0f, (t - 120) / 40.0f));
    Col col = C((int)(30 + (249 - 30) * k), (int)(144 + (115 - 144) * k), (int)(255 + (22 - 255) * k));
    float t1 = std::min(1.0f, t / 40.0f), t4 = std::min(1.0f, std::max(0.0f, (t - 25) / 40.0f));
    drawLogo14(cx, cy, s, col, t1, t4);
    if (t > 60 && k < 1) drawPencil(cx + 130 * s + std::min(1.0f, (t - 60) / 30.0f) * 0 , cy + 60 * s, 1.5f, std::min(1.0f, (t - 60) / 20.0f) * (1 - k));
    if (t > 140) {
        float a = std::min(1.0f, (t - 140) / 30.0f);
        text("\xC3\x8E L O T 1 4   W O R L D", 640, 540, 3.4f, C(255, 255, 255, (int)(255 * a)), 1, 3);
        text("A game by Amir", 640, 600, 1.5f, C(249, 115, 22, (int)(220 * a)), 1);
    }
    int fade = t < 20 ? 255 - t * 12 : (t > 245 ? (t - 245) * 17 : 0);
    if (fade > 0) rect(0, 0, SCR_W, SCR_H, C(0, 0, 0, std::min(255, fade)));
}
