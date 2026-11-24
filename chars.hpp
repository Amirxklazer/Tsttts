// chars.hpp - v0.9.0 character redesign: smooth cartoon people and cleaning bots (replaces the old blocky ones).
// Same Look/drawPerson/drawBot interface, so every existing character, the customizer and all minigames get the new look.
#pragma once

static void chCap(float x1, float y1, float x2, float y2, float w, Col c) {   // rounded limb
    float dx = x2 - x1, dy = y2 - y1, l = sqrtf(dx * dx + dy * dy) + 1e-3f, nx = -dy / l * w / 2, ny = dx / l * w / 2;
    polyFill({{x1 + nx, y1 + ny}, {x2 + nx, y2 + ny}, {x2 - nx, y2 - ny}, {x1 - nx, y1 - ny}}, c);
    fillCircle(x1, y1, w / 2, c); fillCircle(x2, y2, w / 2, c);
}
static void chTri(float ax, float ay, float bx, float by, float cx, float cy, Col c) { polyFill({{ax, ay}, {bx, by}, {cx, cy}}, c); }
static void chOval(float cx, float cy, float rx, float ry, Col c) {
    setCol(c);
    for (int dy = -(int)ry; dy <= (int)ry; dy++) { float dx = rx * sqrtf(std::max(0.0f, 1 - (dy * dy) / (ry * ry))); SDL_FRect r = {cx - dx, cy + dy, dx * 2, 1}; SDL_RenderFillRectF(G.ren, &r); }
}

// feet at (x, gy). dir -1 left / 1 right. walk = frame counter for the walk cycle
static void drawPerson(float x, float gy, int dir, const Look& L, int walk, bool moving) {
    const float s = L.h;
    const Col OL = C(28, 22, 36);                         // outline ink
    float ph = walk * 0.3f, sw = moving ? sinf(ph) : 0, bob = moving ? fabsf(cosf(ph)) * 2.2f * s : sinf(walk * 0.09f) * 0.9f * s;
    float hipY = gy - 27 * s - bob * 0.0f, shY = hipY - 31 * s - bob, R = 21 * s, hcy = shY - 19 * s, hx = x + dir * 1.5f * s;
    Col skin = L.skin, skinD = dim(skin, 0.86f), shirt = L.shirt, shirtD = dim(shirt, 0.8f), pants = L.pants, hair = L.hair, hairD = dim(hair, 0.72f);

    // soft shadow
    chOval(x, gy - 1, 20 * s, 4.5f * s, C(0, 0, 0, 55)); chOval(x, gy - 1, 13 * s, 3 * s, C(0, 0, 0, 45));

    // ---- back items
    if (L.back == 1) { float bx = x - dir * 17 * s; polyFill({{bx - 9 * s, shY - 4 * s}, {bx + 9 * s, shY - 4 * s}, {bx + 10 * s, shY + 26 * s}, {bx - 10 * s, shY + 26 * s}}, OL); polyFill({{bx - 7 * s, shY - 2 * s}, {bx + 7 * s, shY - 2 * s}, {bx + 8 * s, shY + 24 * s}, {bx - 8 * s, shY + 24 * s}}, C(76, 80, 110)); rect(bx - 7 * s, shY + 8 * s, 14 * s, 5 * s, C(249, 115, 22)); }
    else if (L.back == 2) { float fl = sinf(walk * 0.2f) * 3 + (moving ? -dir * 5 : 0); polyFill({{x - 14 * s, shY - 2 * s}, {x + 14 * s, shY - 2 * s}, {x + 22 * s + fl - dir * 8, gy - 8 * s}, {x - 22 * s + fl - dir * 8, gy - 8 * s}}, C(200, 40, 50)); rect(x - 14 * s, shY - 3 * s, 28 * s, 4, C(250, 210, 60)); }
    else if (L.back == 3 || L.back == 4) {
        Col wc = L.back == 3 ? C(250, 250, 255, 240) : C(58, 34, 80, 240); float fl = sinf(walk * 0.12f) * 5;
        for (int k = -1; k <= 1; k += 2) { float bx = x + k * 14 * s; for (int f = 0; f < 3; f++) { float len = (34 - f * 8) * s; chCap(bx, shY + 2 * s + f * 8 * s, bx + k * len, shY - 12 * s + f * 9 * s + fl * k * 0.5f, 9 * s, dim(wc, 1 - f * 0.1f)); } }
    }

    // ---- back arm
    float aw = moving ? -sw * 9 * s : sinf(walk * 0.09f) * 1.2f * s;
    auto arm = [&](float sxo, float swing, Col sleeve) {
        float sx0 = x + sxo, sy0 = shY + 4 * s, hx0 = sx0 + swing * 0.55f + sxo * 0.18f, hy0 = sy0 + 24 * s - fabsf(swing) * 0.12f;
        chCap(sx0, sy0, hx0, hy0, 11.5f * s, OL);
        float mx = sx0 + (hx0 - sx0) * 0.62f, my = sy0 + (hy0 - sy0) * 0.62f;
        chCap(sx0, sy0, mx, my, 9 * s, sleeve); chCap(mx, my, hx0, hy0, 7.5f * s, skin);
    };
    arm(-dir * -13 * s * 0 + (dir > 0 ? -13 : 13) * s, aw, shirtD);

    // ---- legs + shoes
    for (int k = 0; k < 2; k++) {
        float side = k == 0 ? -1 : 1, off = k == 0 ? sw : -sw, lift = moving ? std::max(0.0f, (k == 0 ? -cosf(ph) : cosf(ph))) * 5 * s : 0;
        float lx = x + side * 7 * s, fx = lx + off * 9 * s, fy = gy - 4 * s - lift;
        Col pc = k == 0 ? pants : dim(pants, 0.86f);
        chCap(lx, hipY, fx, fy, 14 * s, OL); chCap(lx, hipY, fx, fy, 11 * s, pc);
        chOval(fx + dir * 3 * s, gy - 3.5f * s - lift, 9 * s, 4.6f * s, OL); chOval(fx + dir * 3 * s, gy - 3.8f * s - lift, 7.6f * s, 3.5f * s, L.shoes);
        rect(fx - 6 * s + dir * 3 * s, gy - 2.2f * s - lift, 12 * s, 1.5f, dim(WHITE, 0.9f));
    }

    // ---- torso (rounded) + clothes
    float tw = 30 * s, bw2 = 27 * s;
    auto torso = [&](float grow, Col c) { polyFill({{x - tw / 2 - grow, shY - grow}, {x + tw / 2 + grow, shY - grow}, {x + bw2 / 2 + grow, hipY + 3 * s + grow}, {x - bw2 / 2 - grow, hipY + 3 * s + grow}}, c); fillCircle(x - tw / 2 + 4 * s, shY + 2 * s, 5 * s + grow, c); fillCircle(x + tw / 2 - 4 * s, shY + 2 * s, 5 * s + grow, c); };
    if (L.topStyle == 6) polyFill({{x - tw / 2 - 3 * s, shY - 2}, {x + tw / 2 + 3 * s, shY - 2}, {x + tw / 2 + 7 * s, hipY + 22 * s}, {x - tw / 2 - 7 * s, hipY + 22 * s}}, OL);
    torso(2, OL);
    if (L.topStyle == 6) { polyFill({{x - tw / 2 - 1 * s, shY}, {x + tw / 2 + 1 * s, shY}, {x + tw / 2 + 5 * s, hipY + 20 * s}, {x - tw / 2 - 5 * s, hipY + 20 * s}}, shirt); rect(x - 1, shY, 2, hipY + 20 * s - shY, shirtD); rect(x - tw / 2 - 5 * s, hipY + 17 * s, tw + 10 * s, 3.5f * s, L.trim); }
    else torso(0, shirt);
    chOval(x - 3 * s, shY + 9 * s, 6 * s, 9 * s, C(255, 255, 255, 22));   // soft light
    if (L.topStyle == 1) {   // hoodie: hood roll, pocket, strings
        chOval(x, shY + 1 * s, 14 * s, 5 * s, shirtD); polyFill({{x - 10 * s, hipY - 9 * s}, {x + 10 * s, hipY - 9 * s}, {x + 12 * s, hipY + 1 * s}, {x - 12 * s, hipY + 1 * s}}, shirtD);
        rect(x - 5 * s, shY + 5 * s, 1.6f, 9 * s, WHITE); rect(x + 4 * s, shY + 5 * s, 1.6f, 9 * s, WHITE);
    } else if (L.topStyle == 2) {   // jacket: lapels + zip
        chTri(x - 1, shY, x - 11 * s, shY, x - 1, shY + 12 * s, mix(shirt, WHITE, 0.6f)); chTri(x + 1, shY, x + 11 * s, shY, x + 1, shY + 12 * s, mix(shirt, WHITE, 0.6f));
        rect(x - 1, shY + 6 * s, 2.2f, hipY - shY - 4 * s, dim(shirt, 0.55f)); rect(x - tw / 2, hipY - 2 * s, tw, 5 * s, shirtD);
    } else if (L.topStyle == 3) {   // striped
        for (int k = 0; k < 4; k++) polyFill({{x - tw / 2 + k * 0.4f, shY + (6 + k * 7.5f) * s}, {x + tw / 2 - k * 0.4f, shY + (6 + k * 7.5f) * s}, {x + tw / 2 - k * 0.6f, shY + (9.5f + k * 7.5f) * s}, {x - tw / 2 + k * 0.6f, shY + (9.5f + k * 7.5f) * s}}, mix(shirt, WHITE, 0.6f));
    } else if (L.topStyle == 4) {   // vest over shirt
        torso(0, mix(shirt, WHITE, 0.85f)); polyFill({{x - tw / 2, shY}, {x - 3 * s, shY}, {x - 2 * s, hipY + 3 * s}, {x - bw2 / 2, hipY + 3 * s}}, shirt); polyFill({{x + tw / 2, shY}, {x + 3 * s, shY}, {x + 2 * s, hipY + 3 * s}, {x + bw2 / 2, hipY + 3 * s}}, shirt);
        for (int k = 0; k < 3; k++) fillCircle(x, shY + (7 + k * 8) * s, 1.6f, L.trim);
    } else if (L.topStyle == 5) {   // overalls
        torso(0, mix(shirt, WHITE, 0.7f)); polyFill({{x - 10 * s, shY + 12 * s}, {x + 10 * s, shY + 12 * s}, {x + 13 * s, hipY + 3 * s}, {x - 13 * s, hipY + 3 * s}}, pants);
        rect(x - 10 * s, shY, 4 * s, 14 * s, pants); rect(x + 6 * s, shY, 4 * s, 14 * s, pants); fillCircle(x - 8 * s, shY + 13 * s, 2, L.trim); fillCircle(x + 8 * s, shY + 13 * s, 2, L.trim);
    } else if (L.topStyle == 7) {   // tracksuit stripes
        rect(x - tw / 2 + 1, shY + 2 * s, 4 * s, hipY - shY, L.trim); rect(x + tw / 2 - 5 * s, shY + 2 * s, 4 * s, hipY - shY, L.trim); rect(x - 1, shY + 5 * s, 2.2f, hipY - shY - 2 * s, dim(shirt, 0.55f)); chOval(x, shY + 1 * s, 9 * s, 3 * s, shirtD);
    } else if (L.topStyle == 8) { fillCircle(x, shY + 14 * s, 7 * s, L.trim); fillCircle(x, shY + 14 * s, 4.4f * s, shirt); }
    else chOval(x, shY + 1.5f * s, 7 * s, 2.6f * s, skinD);   // plain tee: neckline
    if (L.tag14) text("14", x, shY + 5 * s, 1.0f * s, OL, 1);

    // ---- front arm
    arm((dir > 0 ? 13 : -13) * s, -aw, shirt);

    // ---- neck
    rect(x - 4 * s, shY - 5 * s, 8 * s, 8 * s, skinD);

    // ---- back hair (behind the head)
    int hs = L.hairStyle;
    if (hs == 1 || hs == 11) polyFill({{hx - R - 3 * s, hcy - 4 * s}, {hx + R + 3 * s, hcy - 4 * s}, {hx + R + 4 * s, hcy + R + 11 * s}, {hx - R - 4 * s, hcy + R + 11 * s}}, hairD);
    if (hs == 5) { float tx = hx - dir * (R + 4 * s) + (moving ? -dir * sw * 3 : 0); chCap(hx - dir * (R - 2 * s), hcy - 6 * s, tx, hcy + 20 * s, 9 * s, hairD); fillCircle(hx - dir * (R - 1 * s), hcy - 6 * s, 4 * s, L.trim); }
    if (hs == 8) for (int k = -1; k <= 1; k += 2) { float tx = hx + k * (R + 6 * s) + (moving ? sw * k * 2 : 0); chCap(hx + k * (R - 3 * s), hcy - 4 * s, tx, hcy + 22 * s, 9 * s, hairD); fillCircle(hx + k * (R - 3 * s), hcy - 4 * s, 4 * s, L.trim); }
    if (L.acc == 13) {}   // cat ears drawn later

    // ---- head
    fillCircle(hx, hcy, R + 2, OL);
    if (hs == 2) fillCircle(hx, hcy, R + 1, hairD);
    else if (hs != 9) fillCircle(hx, hcy, R + 1.5f, hair);
    fillCircle(hx, hcy + 3 * s, R - 0.5f, hs == 9 ? skin : skin);
    if (hs == 2) { fillCircle(hx, hcy + 5 * s, R - 1, skin); }
    chOval(hx - dir * R * 0.95f, hcy + 4 * s, 3 * s, 4.5f * s, skinD);   // ear (far side)
    chOval(hx + dir * R * 0.95f, hcy + 4 * s, 3 * s, 4.5f * s, skin);

    // ---- face
    float ex0 = hx + dir * 3.5f * s, ey = hcy + 4 * s, esp = 8 * s;
    for (int k = -1; k <= 1; k += 2) {
        float ex = ex0 + k * esp;
        if (L.eyes == 1) { line(ex - 3.5f * s, ey + 0.5f, ex + 3.5f * s, ey + 0.5f, OL); line(ex - 3.5f * s, ey + 1.5f, ex + 3.5f * s, ey + 1.5f, OL); }
        else if (L.eyes == 2) { for (int d2 = 0; d2 < 2; d2++) { line(ex - 3.5f * s, ey + 1 + d2, ex, ey - 2.5f * s + d2, OL); line(ex, ey - 2.5f * s + d2, ex + 3.5f * s, ey + 1 + d2, OL); } }
        else if (L.eyes == 3) { chOval(ex, ey, 5.2f * s, 6.2f * s, WHITE); chOval(ex + dir * 0.8f * s, ey + 0.5f * s, 3.6f * s, 4.8f * s, C(40, 90, 150)); fillCircle(ex + dir * 0.8f * s, ey + 0.5f * s, 2 * s, OL); fillCircle(ex + dir * 0.8f * s - 1.2f * s, ey - 1.8f * s, 1.5f * s, WHITE); }
        else { chOval(ex, ey, 3.2f * s, 4.3f * s, OL); fillCircle(ex + dir * 0.6f * s - 0.8f * s, ey - 1.6f * s, 1.3f * s, WHITE); }
        fillCircle(ex + dir * 1.5f * s, hcy + 12 * s, 3.4f * s, C(255, 130, 140, 70));   // cheek
        line(ex - 3 * s, ey - 7 * s, ex + 3 * s, ey - 6.2f * s - (k * dir > 0 ? 0.8f : 0), hairD);   // brow
    }
    { float mx = ex0, my = hcy + 13 * s; line(mx - 3 * s, my, mx - 1 * s, my + 1.6f * s, OL); line(mx - 1 * s, my + 1.6f * s, mx + 1 * s, my + 1.6f * s, OL); line(mx + 1 * s, my + 1.6f * s, mx + 3 * s, my, OL); }
    // face extras
    if (L.face == 1) for (int k = 0; k < 3; k++) { fillCircle(ex0 - 12 * s + k * 3.2f * s, hcy + 9 * s + (k % 2) * 2, 0.9f, skinD); fillCircle(ex0 + 5 * s + k * 3.2f * s, hcy + 9 * s + (k % 2) * 2, 0.9f, skinD); }
    else if (L.face == 2) { fillCircle(ex0 - esp, hcy + 11 * s, 5 * s, C(255, 110, 130, 120)); fillCircle(ex0 + esp, hcy + 11 * s, 5 * s, C(255, 110, 130, 120)); }
    else if (L.face == 3) { chOval(ex0, hcy + 10.5f * s, 7 * s, 2.4f * s, C(40, 25, 20)); }
    else if (L.face == 4) for (int k = 0; k < 3; k++) { line(ex0 - esp - 12 * s, hcy + 9 * s + k * 3, ex0 - esp - 4 * s, hcy + 10 * s + k * 2, C(40, 40, 48)); line(ex0 + esp + 4 * s, hcy + 10 * s + k * 2, ex0 + esp + 12 * s, hcy + 9 * s + k * 3, C(40, 40, 48)); }

    // ---- front hair
    auto fringe = [&](float depth, float wave) { polyFill({{hx - R - 0.5f, hcy + 2 * s}, {hx - R + 1, hcy - 10 * s}, {hx - 8 * s, hcy - R + 1}, {hx + 4 * s, hcy - R - 1.5f}, {hx + R - 1, hcy - 10 * s}, {hx + R + 0.5f, hcy + 2 * s}, {hx + R - 4 * s, hcy - 6 * s + wave}, {hx + 6 * s, hcy - depth + wave}, {hx - 2 * s, hcy - depth * 0.55f}, {hx - 9 * s, hcy - depth}, {hx - R + 4 * s, hcy - 5 * s}}, hair); };
    switch (hs) {
        case 0: fringe(8 * s, 0); break;
        case 1: fringe(9 * s, 0); break;
        case 2: break;
        case 3: for (int k = 0; k < 7; k++) { float a = IL_PI_C + k * IL_PI_C / 6.0f; fillCircle(hx + cosf(a) * (R - 1 * s), hcy + sinf(a) * (R - 1 * s) - 1 * s, 8.5f * s, k % 2 ? hair : hairD); } fillCircle(hx, hcy - R + 3 * s, 9 * s, hair); fringe(5 * s, 0); break;
        case 4: for (int k = 0; k < 5; k++) { float a = IL_PI_C * 1.12f + k * IL_PI_C * 0.19f; float bx = hx + cosf(a) * (R - 2 * s), by = hcy + sinf(a) * (R - 2 * s); chTri(bx - 6 * s, by + 2 * s, bx + 6 * s, by + 2 * s, bx + cosf(a) * 12 * s, by + sinf(a) * 14 * s - 5 * s, hair); } fringe(8 * s, 0); break;
        case 5: case 6: fringe(8 * s, 0); if (hs == 6) { fillCircle(hx, hcy - R - 3 * s, 9 * s, OL); fillCircle(hx, hcy - R - 3 * s, 7.6f * s, hair); fillCircle(hx - 2 * s, hcy - R - 5 * s, 2.2f * s, mix(hair, WHITE, 0.3f)); } break;
        case 7: fringe(7 * s, 0); polyFill({{hx - R + 1, hcy - 6 * s}, {hx + dir * 10 * s, hcy - R - 1}, {hx + dir * (R - 1), hcy - 3 * s}, {hx + dir * 4 * s, hcy + 8 * s}, {hx - dir * 6 * s, hcy + 1 * s}}, hair); break;
        case 8: fringe(7 * s, 0); break;
        case 9: { fillCircle(hx, hcy, R + 1.5f, hairD); fillCircle(hx, hcy + 3 * s, R - 0.5f, skin); chOval(hx + dir * R * 0.95f, hcy + 4 * s, 3 * s, 4.5f * s, skin);
                  chTri(hx - 6 * s, hcy - R + 6 * s, hx + 6 * s, hcy - R + 6 * s, hx + dir * 3 * s, hcy - R - 16 * s, hair); chTri(hx - 8 * s, hcy - 3 * s, hx + 8 * s, hcy - 3 * s, hx, hcy - R - 5 * s, hair);
                  for (int k = 0; k < 2; k++) chTri(hx - 5 * s + k * 5 * s, hcy - R + 4 * s, hx + k * 5 * s + 3 * s, hcy - R + 4 * s, hx + k * 4 * s - 3 * s, hcy - R - 10 * s, hair); } break;
        case 10: fringe(6 * s, 2 * s); for (int k = 0; k < 4; k++) { float bx = hx - 14 * s + k * 9.5f * s; chTri(bx - 5 * s, hcy - R + 4 * s, bx + 5 * s, hcy - R + 4 * s, bx + (k % 2 ? 4 : -2) * s, hcy - R - (8 + (k % 2) * 6) * s, hair); } break;
        default: fringe(10 * s, 0); polyFill({{hx - R - 0.5f, hcy - 8 * s}, {hx + R + 0.5f, hcy - 8 * s}, {hx + R, hcy - 3 * s}, {hx - R, hcy - 3 * s}}, hair); break;
    }
    chOval(hx - 6 * s, hcy - R + 6 * s, 6 * s, 2.2f * s, C(255, 255, 255, 40));   // hair shine

    // ---- accessories
    float ex = ex0;
    switch (L.acc) {
        case 1: for (int k = -1; k <= 1; k += 2) { float gx = ex + k * esp; fillCircle(gx, ey, 6.6f * s, C(30, 30, 44)); fillCircle(gx, ey, 5.2f * s, C(200, 230, 255, 120)); } line(ex - 2 * s, ey, ex + 2 * s, ey, C(30, 30, 44)); break;
        case 2: polyFill({{hx - R - 1, hcy - 4 * s}, {hx + R + 1, hcy - 4 * s}, {hx + R - 3 * s, hcy - R - 3 * s}, {hx - R + 3 * s, hcy - R - 3 * s}}, C(200, 40, 40)); rect(dir > 0 ? hx : hx - R - 14 * s, hcy - 5 * s, R + 14 * s, 4.5f * s, C(158, 28, 28)); fillCircle(hx, hcy - R - 3 * s, 2.4f * s, C(158, 28, 28)); break;
        case 3: { Col hc = C(44, 44, 58); for (int d2 = 0; d2 < 3; d2++) line(hx - R - d2, hcy + 2 * s, hx - R * 0.6f, hcy - R - 2 - d2, hc), line(hx + R + d2, hcy + 2 * s, hx + R * 0.6f, hcy - R - 2 - d2, hc); line(hx - R * 0.6f, hcy - R - 2, hx + R * 0.6f, hcy - R - 2, hc); chOval(hx - R - 1, hcy + 5 * s, 4 * s, 7 * s, hc); chOval(hx + R + 1, hcy + 5 * s, 4 * s, 7 * s, hc); } break;
        case 4: chCap(hx - 12 * s, shY - 2 * s, hx + 12 * s, shY - 2 * s, 8 * s, C(240, 240, 240)); chCap(hx + 6 * s, shY, hx + 9 * s, shY + 17 * s, 7 * s, C(226, 226, 232)); break;
        case 5: polyFill({{hx - R - 1, hcy - 3 * s}, {hx + R + 1, hcy - 3 * s}, {hx + R - 2 * s, hcy - R - 4 * s}, {hx - R + 2 * s, hcy - R - 4 * s}}, L.trim); rect(hx - R - 2, hcy - 5 * s, 2 * R + 4, 5 * s, dim(L.trim, 0.78f)); fillCircle(hx, hcy - R - 5 * s, 4.2f * s, WHITE); break;
        case 6: rect(hx - R - 1, hcy - 7 * s, 2 * R + 2, 5 * s, L.trim); break;
        case 7: chTri(x, shY + 2 * s, x - 9 * s, shY - 2 * s, x - 9 * s, shY + 7 * s, C(200, 40, 40)); chTri(x, shY + 2 * s, x + 9 * s, shY - 2 * s, x + 9 * s, shY + 7 * s, C(200, 40, 40)); fillCircle(x, shY + 2 * s, 2.6f * s, C(150, 20, 30)); break;
        case 8: chOval(ex + dir * esp, ey, 7 * s, 7 * s, C(20, 20, 24)); line(hx - R, hcy - 6 * s, hx + R, hcy - 3 * s, C(20, 20, 24)); line(hx - R, hcy - 5 * s, hx + R, hcy - 2 * s, C(20, 20, 24)); break;
        case 9: { Col gc = C(250, 210, 60); rect(hx - 10 * s, hcy - R - 4 * s, 20 * s, 7 * s, gc); for (int k = 0; k < 3; k++) chTri(hx - 10 * s + k * 10 * s, hcy - R - 4 * s, hx - 4 * s + k * 10 * s - 6 * s, hcy - R - 4 * s, hx - 7 * s + k * 10 * s, hcy - R - 13 * s, gc); fillCircle(hx, hcy - R - 1 * s, 1.8f * s, C(220, 60, 80)); } break;
        case 10: polyFill({{hx - R - 1, hcy - 2 * s}, {hx + R + 1, hcy - 2 * s}, {hx + R - 2 * s, hcy - R - 3 * s}, {hx - R + 2 * s, hcy - R - 3 * s}}, C(200, 50, 50)); chTri(hx - dir * R, hcy - 5 * s, hx - dir * (R + 12 * s), hcy - 10 * s, hx - dir * (R + 10 * s), hcy + 3 * s, C(170, 36, 36)); break;
        case 11: rect(hx - R, hcy - 9 * s, 2 * R, 4 * s, C(50, 50, 62)); fillCircle(hx - 8 * s, hcy - 7 * s, 6 * s, C(50, 50, 62)); fillCircle(hx + 8 * s, hcy - 7 * s, 6 * s, C(50, 50, 62)); fillCircle(hx - 8 * s, hcy - 7 * s, 4.2f * s, C(130, 225, 255)); fillCircle(hx + 8 * s, hcy - 7 * s, 4.2f * s, C(130, 225, 255)); break;
        case 12: chOval(hx, hcy - R + 2 * s, R + 10 * s, 4.5f * s, C(60, 44, 128)); chTri(hx - 14 * s, hcy - R + 1 * s, hx + 14 * s, hcy - R + 1 * s, hx + dir * 6 * s, hcy - R - 36 * s, C(80, 60, 160)); rect(hx - 13 * s, hcy - R - 3 * s, 26 * s, 3 * s, C(250, 210, 60)); fillCircle(hx + dir * 6 * s, hcy - R - 36 * s, 2.4f * s, C(250, 210, 60)); break;
        case 13: for (int k = -1; k <= 1; k += 2) { chTri(hx + k * 18 * s, hcy - 8 * s, hx + k * 6 * s, hcy - R + 2 * s, hx + k * 17 * s, hcy - R - 10 * s, hair); chTri(hx + k * 15 * s, hcy - 10 * s, hx + k * 9 * s, hcy - R + 3 * s, hx + k * 15.5f * s, hcy - R - 5 * s, C(255, 170, 190)); } break;
        case 14: { float hb = sinf(walk * 0.08f) * 2; for (int d2 = 0; d2 < 3; d2++) { chOval(hx, hcy - R - 8 * s + hb, 15 * s - d2 * 0.6f, 4 * s - d2 * 0.4f, C(255, 235, 120, 255 - d2 * 60)); } chOval(hx, hcy - R - 8 * s + hb, 10 * s, 1.8f * s, C(60, 60, 80, 0)); } break;
        case 15: line(hx, hcy - R, hx, hcy - R - 14 * s, C(150, 150, 160)); line(hx + 1, hcy - R, hx + 1, hcy - R - 14 * s, C(150, 150, 160)); fillCircle(hx, hcy - R - 16 * s, 4 * s, C(255, 80, 80)); fillCircle(hx - 1, hcy - R - 17 * s, 1.4f * s, WHITE); break;
        case 16: for (int k = 0; k < 5; k++) { float a = k * 1.2566f; fillCircle(hx + dir * 12 * s + cosf(a) * 4 * s, hcy - R * 0.55f + sinf(a) * 4 * s, 3 * s, C(255, 140, 190)); } fillCircle(hx + dir * 12 * s, hcy - R * 0.55f, 2.2f * s, C(255, 230, 90)); break;
        case 17: chTri(hx - 11 * s, hcy - R + 3 * s, hx + 11 * s, hcy - R + 3 * s, hx, hcy - R - 24 * s, C(90, 200, 255)); for (int k = 0; k < 3; k++) fillCircle(hx - 4 * s + k * 4 * s, hcy - R - (2 + k * 5) * s, 1.6f * s, C(255, 90, 160)); fillCircle(hx, hcy - R - 25 * s, 3.2f * s, WHITE); break;
        case 18: fillCircle(hx, hcy - R - 2 * s, 12 * s, OL); fillCircle(hx, hcy - R - 2 * s, 10.6f * s, C(240, 120, 20)); rect(hx - 1.5f * s, hcy - R - 17 * s, 3 * s, 6 * s, C(70, 120, 40)); chTri(hx - 6 * s, hcy - R - 6 * s, hx - 2 * s, hcy - R - 6 * s, hx - 4 * s, hcy - R - 2 * s, C(40, 24, 10)); chTri(hx + 2 * s, hcy - R - 6 * s, hx + 6 * s, hcy - R - 6 * s, hx + 4 * s, hcy - R - 2 * s, C(40, 24, 10)); break;
        case 19: for (int k = -1; k <= 1; k += 2) chOval(ex + k * esp, ey, 6.8f * s, 5 * s, C(14, 14, 20)); line(ex - 2 * s, ey - 1, ex + 2 * s, ey - 1, C(14, 14, 20)); chOval(ex - esp - 2 * s, ey - 2 * s, 2 * s, 1 * s, C(255, 255, 255, 80)); break;
        default: break;
    }
}

// cleaning bots: round dome, glowing eyes, antenna light, little treads
static void drawBot(float x, float gy, Col body, int t, int dir, bool happy) {
    const Col OL = C(28, 22, 36);
    float bob = sinf(t * 0.12f) * 2.6f, roll = sinf(t * 0.12f + 1) * 1.2f;
    chOval(x, gy - 1, 27, 5, C(0, 0, 0, 60));
    // treads
    for (int k = -1; k <= 1; k += 2) { chOval(x + k * 14, gy - 5, 12, 6, OL); chOval(x + k * 14, gy - 5, 10.4f, 4.6f, C(60, 62, 76)); for (int d = -2; d <= 2; d++) fillCircle(x + k * 14 + d * 4, gy - 5, 1.1f, C(120, 124, 140)); }
    // body (rounded)
    fillCircle(x, gy - 24 + bob, 27, OL); chOval(x, gy - 24 + bob, 26, 22, body);
    chOval(x, gy - 14 + bob, 24, 11, dim(body, 0.78f));
    chOval(x - 9, gy - 33 + bob, 9, 4.5f, mix(body, WHITE, 0.55f));
    // face plate
    chOval(x + dir * 1, gy - 26 + bob + roll * 0.2f, 18, 12.5f, OL); chOval(x + dir * 1, gy - 26 + bob, 16.6f, 11.3f, C(18, 24, 44));
    Col glow = happy ? C(120, 255, 220) : C(255, 120, 110);
    for (int k = -1; k <= 1; k += 2) { float ex = x + dir * 3 + k * 7.5f; chOval(ex, gy - 28 + bob, 3.8f, happy ? 4.8f : 3.4f, glow); fillCircle(ex - 1.1f, gy - 29.6f + bob, 1.1f, WHITE); }
    if (happy) { for (int d = -3; d <= 3; d++) fillCircle(x + dir * 3 + d * 2, gy - 19 + bob + d * d * 0.28f, 1.1f, glow); }
    else { line(x + dir * 3 - 6, gy - 18 + bob, x + dir * 3 + 6, gy - 20 + bob, glow); line(x + dir * 3 - 6, gy - 19 + bob, x + dir * 3 + 6, gy - 21 + bob, glow); }
    // little arms + antenna
    for (int k = -1; k <= 1; k += 2) chCap(x + k * 25, gy - 20 + bob, x + k * 31, gy - 12 + bob + sinf(t * 0.2f + k) * 3, 5, dim(body, 0.7f));
    chCap(x, gy - 46 + bob, x + sinf(t * 0.1f) * 2, gy - 56 + bob, 2.4f, C(170, 172, 186));
    fillCircle(x + sinf(t * 0.1f) * 2, gy - 58 + bob, 4.6f, OL); fillCircle(x + sinf(t * 0.1f) * 2, gy - 58 + bob, 3.6f, ((t / 20) & 1) ? C(255, 150, 40) : C(255, 90, 40));
}
