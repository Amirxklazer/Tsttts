// illit.hpp - "Adam Chermatti calls you GLLIT" event: a fully animated stage cutscene of five original
// ILLIT-style girls, driven by the NOT ME audio clip (embedded, IMA-ADPCM) and its beat/energy map.
// No lyrics are shown on purpose: the show is told with moves, stickers, colours and light.
#pragma once
#include "nm_audio.hpp"

// ---------------------------------------------------------------- audio
static const short IL_STEP[89] = {7,8,9,10,11,12,13,14,16,17,19,21,23,25,28,31,34,37,41,45,50,55,60,66,73,80,88,97,107,118,130,143,157,173,190,209,230,253,279,307,337,371,408,449,494,544,598,658,724,796,876,963,1060,1166,1282,1411,1552,1707,1878,2066,2272,2499,2749,3024,3327,3660,4026,4428,4871,5358,5894,6484,7132,7845,8630,9493,10442,11487,12635,13899,15289,16818,18500,20350,22385,24623,27086,29794,32767};
static const signed char IL_IDX[8] = {-1, -1, -1, -1, 2, 4, 6, 8};

struct IllitAudio { SDL_AudioDeviceID dev = 0; std::vector<Sint16> pcm; volatile int pos = 0; bool tried = false, ok = false; };
static IllitAudio IA;
static float IL_FORCE_T = -1;   // test hook (--illit-t)

static void illitDecode() {
    if (!IA.pcm.empty()) return;
    IA.pcm.resize(NM_SAMPLES);
    int pred = 0, idx = 0;
    for (int i = 0; i < NM_SAMPLES; i++) {
        int code = (i & 1) ? (NM_ADPCM[i >> 1] >> 4) : (NM_ADPCM[i >> 1] & 15);
        int step = IL_STEP[idx], d = step >> 3;
        if (code & 4) d += step;
        if (code & 2) d += step >> 1;
        if (code & 1) d += step >> 2;
        pred += (code & 8) ? -d : d;
        pred = std::max(-32768, std::min(32767, pred));
        idx = std::max(0, std::min(88, idx + IL_IDX[code & 7]));
        IA.pcm[i] = (Sint16)pred;
    }
}
static void illitCb(void*, Uint8* st, int len) {
    Sint16* o = (Sint16*)st; int n = len / 2, p = IA.pos;
    for (int i = 0; i < n; i++) o[i] = (p < NM_SAMPLES) ? IA.pcm[p++] : 0;
    IA.pos = p;
}
static void illitStart() {
    g.illitT = 0; IA.pos = 0;
    if (!IA.tried) {
        IA.tried = true;
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) == 0) {
            illitDecode();
            SDL_AudioSpec w; SDL_zero(w);
            w.freq = NM_RATE; w.format = AUDIO_S16SYS; w.channels = 1; w.samples = 1024; w.callback = illitCb;
            IA.dev = SDL_OpenAudioDevice(nullptr, 0, &w, nullptr, 0);
            IA.ok = IA.dev != 0;
            if (!IA.ok) fprintf(stderr, "illit audio: %s\n", SDL_GetError());
        } else fprintf(stderr, "illit audio init: %s\n", SDL_GetError());
    }
    if (IA.ok) SDL_PauseAudioDevice(IA.dev, 0);
}
static void illitStop() { if (IA.ok) SDL_PauseAudioDevice(IA.dev, 1); }
static float illitTime() {
    if (IL_FORCE_T >= 0) return IL_FORCE_T;
    return IA.ok ? IA.pos / (float)NM_RATE : g.illitT / 60.0f;
}

// ---------------------------------------------------------------- helpers
static const float IL_PI = 3.14159265f;
static float ilR(int i, int k = 0) { float v = sinf(i * 12.9898f + k * 78.233f) * 43758.5453f; return v - floorf(v); }
static Col ilHue(float h, float s = 0.7f, float v = 1.0f, int a = 255) {
    h -= floorf(h); int i = (int)(h * 6); float f = h * 6 - i, p = v * (1 - s), q = v * (1 - f * s), t2 = v * (1 - (1 - f) * s), r, gg, b;
    switch (i % 6) { case 0: r = v; gg = t2; b = p; break; case 1: r = q; gg = v; b = p; break; case 2: r = p; gg = v; b = t2; break;
                     case 3: r = p; gg = q; b = v; break; case 4: r = t2; gg = p; b = v; break; default: r = v; gg = p; b = q; }
    return C((int)(r * 255), (int)(gg * 255), (int)(b * 255), a);
}
static float ilLow(float t) { int i = (int)(t * 60); i = std::max(0, std::min(NM_FRAMES - 1, i)); return NM_LOW[i] / 255.0f; }
static float ilFlux(float t) { int i = (int)(t * 60); i = std::max(0, std::min(NM_FRAMES - 1, i)); return NM_FLUX[i] / 255.0f; }
static float ilSmooth(float a, float b, float x) { float t = std::max(0.0f, std::min(1.0f, (x - a) / (b - a))); return t * t * (3 - 2 * t); }
static void ilQuad(float x1, float y1, float x2, float y2, float w, Col c) {
    float dx = x2 - x1, dy = y2 - y1, l = sqrtf(dx * dx + dy * dy) + 1e-3f, nx = -dy / l * w / 2, ny = dx / l * w / 2;
    polyFill({{x1 + nx, y1 + ny}, {x2 + nx, y2 + ny}, {x2 - nx, y2 - ny}, {x1 - nx, y1 - ny}}, c);
    fillCircle(x1, y1, w / 2, c); fillCircle(x2, y2, w / 2, c);
}
static void ilRect(float cx, float cy, float w, float h, float rot, Col c) {
    float co = cosf(rot), si = sinf(rot), hw = w / 2, hh = h / 2;
    auto P = [&](float x, float y) { return SDL_FPoint{cx + x * co - y * si, cy + x * si + y * co}; };
    polyFill({P(-hw, -hh), P(hw, -hh), P(hw, hh), P(-hw, hh)}, c);
}
static void ilTri(float x, float y, float ax, float ay, float bx, float by, float cx2, float cy2, Col c) { polyFill({{x + ax, y + ay}, {x + bx, y + by}, {x + cx2, y + cy2}}, c); }

// pictogram icons for the name-tag stickers (shapes only, no words)
static void ilIcon(int id, float x, float y, float s, Col ink) {
    switch (((id % 8) + 8) % 8) {
        case 0: fillCircle(x, y + 2 * s, 9 * s, ink); ilTri(x, y, -9 * s, -2 * s, -9 * s, -11 * s, -2 * s, -6 * s, ink); ilTri(x, y, 9 * s, -2 * s, 9 * s, -11 * s, 2 * s, -6 * s, ink); break;                 // cat
        case 1: fillCircle(x, y - 2 * s, 9 * s, ink); rect(x - 9 * s, y - 2 * s, 18 * s, 8 * s, ink); for (int k = -1; k <= 1; k++) fillCircle(x + k * 6 * s, y + 6 * s, 3 * s, ink); break;                  // jelly
        case 2: rect(x - 11 * s, y, 22 * s, 7 * s, ink); ilTri(x, y, -11 * s, 1 * s, -11 * s, -7 * s, -4 * s, 1 * s, ink); ilTri(x, y, -6 * s, 1 * s, 0, -10 * s, 6 * s, 1 * s, ink); ilTri(x, y, 4 * s, 1 * s, 11 * s, -7 * s, 11 * s, 1 * s, ink); break;   // crown
        case 3: fillCircle(x - 5 * s, y - 3 * s, 6 * s, ink); fillCircle(x + 5 * s, y - 3 * s, 6 * s, ink); ilTri(x, y, -10.5f * s, -1 * s, 10.5f * s, -1 * s, 0, 10 * s, ink); break;                    // heart
        case 4: { std::vector<SDL_FPoint> p; p.push_back({x, y}); for (int k = 0; k <= 10; k++) { float r = (k % 2) ? 4.5f * s : 11 * s, a = -IL_PI / 2 + k * IL_PI / 5; p.push_back({x + cosf(a) * r, y + sinf(a) * r}); } polyFill(p, ink); } break;   // star
        case 5: fillCircle(x, y, 8 * s, ink); rect(x - 12 * s, y - 6 * s, 5 * s, 14 * s, ink); rect(x + 7 * s, y - 6 * s, 5 * s, 14 * s, ink); break;                                                // dog
        case 6: fillCircle(x, y - 1 * s, 9 * s, ink); ilTri(x, y, -5 * s, 6 * s, -9 * s, 12 * s, 1 * s, 8 * s, ink); break;                                                                          // bubble
        default: ilTri(x, y, 3 * s, -11 * s, -6 * s, 2 * s, 0, 2 * s, ink); ilTri(x, y, 0, -3 * s, 7 * s, -3 * s, -3 * s, 11 * s, ink); break;                                                          // bolt
    }
}
static void ilSticker(float x, float y, float rot, int id, float s, int alpha = 255) {
    Col bg = ilHue(ilR(id, 3) + 0.05f * id, 0.35f, 1.0f, alpha), ink = C(40, 24, 56, alpha);
    ilRect(x, y, 46 * s, 30 * s, rot, C(255, 255, 255, alpha));
    ilRect(x, y, 40 * s, 24 * s, rot, bg);
    float co = cosf(rot), si = sinf(rot);
    ilIcon(id, x - 6 * s * co * 0, y, 0.95f * s, ink);
    (void)si;
}

// ---------------------------------------------------------------- the girls (original designs)
struct IlGirl { Col hair, hairHi, top, accent, skirt, skin, shoe; int style; };
static const IlGirl IL_GIRLS[5] = {
    {C(58, 36, 40), C(255, 120, 170), C(255, 130, 170), C(255, 255, 255), C(40, 36, 70), C(250, 214, 190), C(250, 250, 250), 0},
    {C(190, 165, 238), C(235, 215, 255), C(250, 250, 255), C(150, 110, 210), C(120, 90, 190), C(252, 222, 200), C(60, 50, 90), 1},
    {C(24, 22, 30), C(90, 90, 130), C(220, 50, 70), C(255, 255, 255), C(60, 40, 50), C(244, 206, 176), C(240, 240, 240), 2},
    {C(222, 180, 110), C(255, 225, 160), C(60, 190, 190), C(255, 255, 255), C(245, 245, 250), C(250, 218, 190), C(255, 200, 120), 3},
    {C(120, 50, 40), C(190, 100, 70), C(255, 215, 70), C(60, 60, 60), C(70, 110, 170), C(246, 212, 184), C(250, 250, 250), 4},
};
struct IlPose {
    float x = 640, y = 620, s = 1.4f, bounce = 0, lean = 0, aL = 0.25f, aR = 0.25f, bendL = 0.4f, bendR = 0.4f, step = 0, tilt = 0, mouth = 0, dim = 0;
    int face = 0; bool hasTop = false; Col topC = {0, 0, 0, 255};
};

static void drawGirl(int gi, const IlPose& P, float T) {
    const IlGirl& G0 = IL_GIRLS[gi];
    float f = 1.0f - P.dim, s = P.s;
    auto D = [&](Col c) { return dim(c, f); };
    Col top = D(P.hasTop ? P.topC : G0.top), skin = D(G0.skin), hair = D(G0.hair), hi = D(G0.hairHi), skirt = D(G0.skirt), shoe = D(G0.shoe), acc = D(G0.accent);
    float hipY = P.y - 62 * s - P.bounce, hx = P.x, sx = P.x + P.lean * 22 * s, shY = hipY - 70 * s;
    float hcx = sx + P.tilt * 12 * s, hcy = shY - 40 * s, lift = P.bounce * 0.7f;
    float sw = sinf(T * 5 + gi);
    // back hair
    if (G0.style == 0) polyFill({{hcx - 40 * s, hcy - 8 * s}, {hcx + 40 * s, hcy - 8 * s}, {hcx + 36 * s + sw * 3, hcy + 66 * s}, {hcx - 36 * s + sw * 3, hcy + 66 * s}}, hair);
    if (G0.style == 1) { for (int sd = -1; sd <= 1; sd += 2) { float tx = hcx + sd * (46 * s + sw * 5), ty = hcy + 34 * s; ilQuad(hcx + sd * 30 * s, hcy - 6 * s, tx, ty, 14 * s, hair); fillCircle(tx, ty + 6 * s, 15 * s, hair); fillCircle(tx, ty + 6 * s, 9 * s, hi); } }
    if (G0.style == 2) polyFill({{hcx - 42 * s, hcy - 6 * s}, {hcx + 42 * s, hcy - 6 * s}, {hcx + 41 * s, hcy + 32 * s}, {hcx - 41 * s, hcy + 32 * s}}, hair);
    if (G0.style == 3) ilQuad(hcx + 30 * s, hcy - 16 * s, hcx + 62 * s + sw * 8, hcy + 48 * s, 17 * s, hair);
    if (G0.style == 4) { fillCircle(hcx - 27 * s, hcy - 42 * s, 15 * s, hair); fillCircle(hcx + 27 * s, hcy - 42 * s, 15 * s, hair); }
    // legs
    for (int sd = -1; sd <= 1; sd += 2) {
        float ph = P.step + (sd > 0 ? IL_PI : 0), fx = hx + sd * 15 * s + sinf(ph) * 14 * s, fy = P.y - lift - std::max(0.0f, sinf(ph + 1.57f)) * 10 * s;
        ilQuad(hx + sd * 11 * s, hipY, fx, fy - 6 * s, 11 * s, skin);
        ilRect(fx + sd * 2 * s, fy - 2 * s, 24 * s, 10 * s, 0, shoe);
    }
    // skirt + torso
    polyFill({{hx - 17 * s, hipY - 8 * s}, {hx + 17 * s, hipY - 8 * s}, {hx + 28 * s, hipY + 24 * s}, {hx - 28 * s, hipY + 24 * s}}, skirt);
    polyFill({{sx - 24 * s, shY}, {sx + 24 * s, shY}, {hx + 18 * s, hipY - 4 * s}, {hx - 18 * s, hipY - 4 * s}}, top);
    ilQuad((sx + hx) / 2, shY + 6 * s, (sx + hx) / 2, hipY - 6 * s, 3 * s, acc);
    ilQuad(sx - 20 * s, shY + 3 * s, sx + 20 * s, shY + 3 * s, 4 * s, acc);
    // arms (angle from straight-down; larger = more raised, outward)
    for (int sd = -1; sd <= 1; sd += 2) {
        float a = sd < 0 ? P.aL : P.aR, bd = sd < 0 ? P.bendL : P.bendR;
        float ax0 = sx + sd * 25 * s, ay0 = shY + 6 * s;
        float ex = ax0 + sd * sinf(a) * 34 * s, ey = ay0 + cosf(a) * 34 * s;
        float a2 = a + bd, hx2 = ex + sd * sinf(a2) * 32 * s, hy2 = ey + cosf(a2) * 32 * s;
        ilQuad(ax0, ay0, ex, ey, 12 * s, top); ilQuad(ex, ey, hx2, hy2, 10 * s, skin); fillCircle(hx2, hy2, 6 * s, skin);
    }
    // neck + head
    rect(hcx - 6 * s, shY - 10 * s, 12 * s, 14 * s, skin);
    fillCircle(hcx, hcy, 39 * s, hair);
    fillCircle(hcx, hcy + 3 * s, 34 * s, skin);
    // face
    float ey = hcy + 4 * s;
    bool blink = fmodf(T + gi * 0.7f, 3.3f) > 3.18f;
    for (int sd = -1; sd <= 1; sd += 2) {
        float ex = hcx + sd * 13 * s;
        if (P.face == 1) { line(ex - sd * 8 * s, ey - 5 * s, ex + sd * 6 * s, ey + 1 * s, D(C(40, 20, 30))); line(ex - sd * 8 * s, ey - 4 * s, ex + sd * 6 * s, ey + 2 * s, D(C(40, 20, 30))); fillCircle(ex, ey + 4 * s, 3 * s, D(C(40, 20, 30))); }
        else if (P.face == 2) { fillCircle(ex, ey, 7 * s, D(WHITE)); fillCircle(ex, ey, 3.5f * s, D(C(40, 20, 30))); }
        else if (P.face == 3 || blink) { line(ex - 6 * s, ey + 1 * s, ex, ey - 4 * s, D(C(40, 20, 30))); line(ex, ey - 4 * s, ex + 6 * s, ey + 1 * s, D(C(40, 20, 30))); line(ex - 6 * s, ey + 2 * s, ex, ey - 3 * s, D(C(40, 20, 30))); line(ex, ey - 3 * s, ex + 6 * s, ey + 2 * s, D(C(40, 20, 30))); }
        else { fillCircle(ex, ey, 4.4f * s, D(C(40, 20, 30))); fillCircle(ex + 1.5f * s, ey - 1.5f * s, 1.5f * s, D(WHITE)); }
        fillCircle(hcx + sd * 22 * s, hcy + 17 * s, 6 * s, D(C(255, 130, 150, 110)));
    }
    if (P.face == 1) rect(hcx - 6 * s, hcy + 19 * s, 12 * s, 3 * s, D(C(120, 40, 60)));
    else fillCircle(hcx, hcy + 18 * s, 2.5f * s + 5.5f * s * P.mouth, D(C(130, 40, 62)));
    // fringe
    polyFill({{hcx - 36 * s, hcy - 2 * s}, {hcx - 32 * s, hcy - 26 * s}, {hcx - 4 * s, hcy - 40 * s}, {hcx + 30 * s, hcy - 30 * s}, {hcx + 36 * s, hcy - 2 * s}, {hcx + 22 * s, hcy - 12 * s}, {hcx + 8 * s, hcy - 8 * s}, {hcx - 6 * s, hcy - 16 * s}, {hcx - 20 * s, hcy - 8 * s}}, hair);
    ilQuad(hcx - 14 * s, hcy - 30 * s, hcx + 6 * s, hcy - 24 * s, 4 * s, hi);
}

// ---------------------------------------------------------------- stage drawing
static void ilConfetti(float t, int n, float speed, float alpha) {
    for (int i = 0; i < n; i++) {
        float x = fmodf(ilR(i) * 1400 + sinf(t * 1.3f + i) * 40, 1300) - 10;
        float y = fmodf(ilR(i, 1) * 900 + t * (130 + ilR(i, 2) * 170) * speed, 780) - 30;
        ilRect(x, y, 6 + ilR(i, 4) * 8, 10 + ilR(i, 5) * 8, t * (ilR(i, 6) - 0.5f) * 8 + i, ilHue(i * 0.071f + t * 0.1f, 0.6f, 1.0f, (int)(220 * alpha)));
    }
}
static void ilRays(float cx, float cy, float t, Col c, int n = 14) {
    for (int i = 0; i < n; i++) {
        float a = t * 0.35f + i * 2 * IL_PI / n, w = IL_PI / n * 0.7f, L = 1400;
        polyFill({{cx, cy}, {cx + cosf(a) * L, cy + sinf(a) * L}, {cx + cosf(a + w) * L, cy + sinf(a + w) * L}}, c);
    }
}
static void ilBeams(float t, int a) {
    for (int k = 0; k < 3; k++) {
        float bx = 640 + sinf(t * 0.9f + k * 2.1f) * 430;
        float tx = 380 + k * 260;
        polyFill({{tx - 8, 48}, {tx + 8, 48}, {bx + 90, 640}, {bx - 90, 640}}, ilHue(t * 0.08f + k * 0.3f, 0.5f, 1.0f, a));
    }
}
static void ilFormation(int f, int i, float& x, float& yo, float& sm) {
    int d = abs(i - 2);
    switch (f & 3) {
        case 0: x = 240 + 200 * i; yo = 0; sm = 1; break;
        case 1: x = 250 + 195 * i; yo = 22 - d * 34; sm = 1.08f - d * 0.08f; break;
        case 2: x = 250 + 195 * i; yo = (i % 2) ? -52 : 18; sm = (i % 2) ? 0.9f : 1.06f; break;
        default: x = 640 + (i - 2) * 150; yo = (i % 2) ? -26 : 10; sm = (i % 2) ? 0.95f : 1.02f; break;
    }
}
static void ilDance(IlPose& p, int i, float t, int mv, float k, float sm) {
    float b = t * 8.37f + i * 0.55f;
    p.step = b; p.bounce = 26 * k * k * p.s; p.mouth = ilFlux(t) > 0.15f ? 0.5f + 0.5f * sinf(t * 14 + i * 1.3f) : 0;
    p.tilt = sinf(t * 4.18f + i) * 0.6f; (void)sm;
    switch (mv & 3) {
        case 0: p.aL = 2.2f + 0.6f * sinf(b); p.aR = 2.2f + 0.6f * cosf(b); p.bendL = p.bendR = 0.5f; break;
        case 1: p.aL = p.aR = 1.55f; p.bendL = p.bendR = 0.05f + 0.5f * k; break;
        case 2: if (i % 2) { p.aL = 2.9f; p.aR = 0.35f; } else { p.aR = 2.9f; p.aL = 0.35f; } p.bendL = p.bendR = 0.2f; break;
        default: p.aL = p.aR = 0.9f + 0.5f * sinf(b); p.lean = sinf(t * 4.18f + i) * 0.8f; p.bendL = p.bendR = 0.7f; break;
    }
    p.face = k > 0.9f ? 3 : 0;
}

static void drawIllitWorld(float t, int T) {
    float k = ilLow(t), k2 = k * k, fl = ilFlux(t);
    int sec = t < 7.5f ? 0 : t < 22.0f ? 1 : t < 42.3f ? 2 : t < 54.5f ? 3 : t < 69.5f ? 4 : 5;
    // ---- backdrop
    Col g0, g1;
    switch (sec) {
        case 0: g0 = C(16, 52, 60); g1 = C(6, 20, 30); break;
        case 1: case 2: g0 = ilHue(t * 0.04f + 0.85f, 0.6f, 0.42f); g1 = ilHue(t * 0.04f + 0.95f, 0.7f, 0.14f); break;
        case 3: g0 = C(34, 22, 70); g1 = C(8, 6, 22); break;
        case 4: g0 = ilHue(t * 0.15f, 0.7f, 0.65f); g1 = ilHue(t * 0.15f + 0.3f, 0.8f, 0.25f); break;
        default: g0 = C(255, 222, 244); g1 = C(255, 170, 214); break;
    }
    gradient(0, 720, g0, g1);
    if (sec == 4 || sec == 5) ilRays(640, 330, t, C(255, 255, 255, sec == 5 ? 60 : 34));
    if (sec == 1 || sec == 2 || sec == 4) {   // equalizer wall
        for (int i = 0; i < 40; i++) {
            float h = 30 + 170 * ilFlux(t - 0.035f * i) * (0.55f + 0.45f * sinf(i * 1.7f + t * 3));
            rect(i * 32 + 3, 470 - h, 26, h, ilHue(i / 40.0f + t * 0.1f, 0.5f, 1.0f, sec == 4 ? 110 : 70));
        }
    }
    if (sec == 1 || sec == 2) ilBeams(t, 38);
    if (sec == 4) ilBeams(t, 55);
    if (sec == 3) { for (int i = 0; i < 40; i++) fillCircle(fmodf(ilR(i) * 1300 + t * 8, 1300) - 10, 60 + ilR(i, 1) * 360, 1.5f + ilR(i, 2) * 2, C(255, 255, 255, 80 + (int)(80 * sinf(t * 3 + i)))); }
    // floor
    gradient(470, 720, sec == 5 ? C(255, 200, 232) : C(18, 14, 34), sec == 5 ? C(255, 235, 248) : C(40, 26, 64));
    for (int i = -8; i <= 8; i++) line(640 + i * 60, 470, 640 + i * 190, 720, C(255, 255, 255, 26));
    for (int j = 0; j < 6; j++) { float yy = 470 + (j * j) * 7.5f + 10; line(0, yy, 1280, yy, C(255, 255, 255, 22)); }
    if (sec == 4 || sec == 2) rect(0, 470, 1280, 3, ilHue(t * 0.3f, 0.5f, 1.0f, 150));

    // ---- girls
    IlPose P[5]; bool vis[5] = {true, true, true, true, true}; int order[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) { P[i].hasTop = (sec == 1 || sec == 2 || sec == 4); P[i].topC = ilHue(t * 0.25f + i * 0.2f, 0.6f, 1.0f); }
    if (sec == 0) {
        for (int i = 0; i < 5; i++) {
            static const float ox[5] = {130, 280, 640, 1000, 1150};
            P[i].x = ox[i]; P[i].y = i == 2 ? 650 : 590; P[i].s = i == 2 ? 2.0f : 0.95f; P[i].dim = i == 2 ? 0 : 0.55f;
            P[i].step = t * 3 + i; P[i].mouth = 0; P[i].face = 0; P[i].tilt = sinf(t * 2 + i) * 0.3f;
            P[i].aL = P[i].aR = 0.25f + 0.1f * sinf(t * 2 + i);
        }
        int alive = 0; for (int j = 0; j < 16; j++) if (t < 0.8f + j * 0.4f) alive++;
        float shake = alive * 0.012f;
        P[2].face = alive > 0 ? 1 : 3; P[2].lean = sinf(t * 31) * shake * 3; P[2].tilt = sinf(t * 27) * shake * 4;
        P[2].aL = 0.5f + sinf(t * 19) * shake * 5; P[2].aR = 0.5f + cosf(t * 23) * shake * 5; P[2].y += fabsf(sinf(t * 17)) * shake * 24;
        if (alive == 0) { P[2].aL = P[2].aR = 1.2f + (t - 7.0f) * 3.0f; P[2].bendL = P[2].bendR = 0.6f; P[2].mouth = 0.8f; }
    } else if (sec == 3) {
        int turn = std::min(4, (int)((t - 42.3f) / 2.44f)); float lt = t - 42.3f - turn * 2.44f;
        static const float bx[5] = {200, 420, 640, 860, 1080};
        for (int i = 0; i < 5; i++) {
            P[i].x = bx[i]; P[i].y = 560; P[i].s = 0.95f; P[i].dim = 0.5f; P[i].step = t * 2 + i; P[i].aL = P[i].aR = 0.25f; P[i].tilt = sinf(t * 2 + i) * 0.2f;
        }
        float e = ilSmooth(0, 0.35f, lt) * (1 - ilSmooth(2.2f, 2.44f, lt));
        IlPose& a = P[turn];
        a.x = bx[turn] + (640 - bx[turn]) * e; a.y = 560 + 90 * e; a.s = 0.95f + 0.85f * e; a.dim = 0.5f * (1 - e); a.face = 1;
        a.tilt = sinf(lt * 24) * 0.9f * e; a.aR = 0.3f; a.aL = 0.3f; a.mouth = 0.3f;
        float hit = fmodf(lt - 0.25f, 0.55f); if (lt > 0.25f && hit < 0.35f) { a.aR = 2.5f; a.aL = 0.6f; a.face = 2; }
        P[turn].lean = sinf(lt * 16) * 0.3f;
        // reorder so the active girl is drawn last (in front)
        order[turn] = 4; order[4] = turn;
    } else if (sec == 5) {
        float fade = ilSmooth(0, 0.6f, t - 69.5f);
        for (int i = 0; i < 5; i++) {
            float x, yo, sm; ilFormation(1, i, x, yo, sm);
            P[i].x = x; P[i].y = 620 + yo; P[i].s = 1.45f * sm; P[i].aL = P[i].aR = 2.6f + 0.15f * sinf(t * 6 + i); P[i].bendL = P[i].bendR = 0.3f;
            P[i].step = 0; P[i].bounce = (4 + 20 * k2) * (t > 72.2f ? 0.2f : 1); P[i].face = 3; P[i].mouth = 0.6f; P[i].tilt = sinf(t * 3 + i) * 0.4f;
            P[i].dim = 0; (void)fade;
        }
    } else {
        // sections 1, 2 and 4: group choreography
        float st = sec == 1 ? 7.5f : sec == 2 ? 22.0f : 54.5f;
        int bar = (int)((t - st) / 3.0f), f0 = sec == 1 ? 0 : sec == 2 ? (bar / 2) % 4 : bar % 4, f1 = (sec == 2 ? ((bar + 1) / 2) : (bar + 1)) % 4;
        if (sec == 1) f1 = f0;
        float mix = sec == 2 ? ilSmooth(5.2f, 6.0f, fmodf(t - st, 6.0f)) : ilSmooth(2.4f, 3.0f, fmodf(t - st, 3.0f));
        if (sec == 1) mix = 0;
        float slide = ilSmooth(0, 1.2f, t - st);
        for (int i = 0; i < 5; i++) {
            float xa, ya, sa, xb, yb, sb; ilFormation(f0, i, xa, ya, sa); ilFormation(f1, i, xb, yb, sb);
            float x = xa + (xb - xa) * mix, yo = ya + (yb - ya) * mix, sm = sa + (sb - sa) * mix;
            if (slide < 1) { float from = i < 2 ? -140.0f : 1420.0f; x = from + (x - from) * slide; }
            P[i].x = x + sinf(t * 0.5f + i) * 14; P[i].y = 620 + yo; P[i].s = 1.4f * sm;
            int mv = sec == 4 ? 4 : (int)((t - st) / 3.0f);
            if (sec == 4) {   // the big hook: everybody up, everybody jumping
                P[i].step = t * 8.37f + i * 0.4f; P[i].bounce = (14 + 46 * k) * P[i].s; P[i].aL = P[i].aR = 2.5f + 0.4f * k + 0.2f * sinf(t * 9 + i); P[i].bendL = P[i].bendR = 0.5f;
                P[i].face = k > 0.7f ? 3 : 0; P[i].mouth = 0.7f; P[i].tilt = sinf(t * 6 + i) * 0.5f;
            } else ilDance(P[i], i, t, mv, k, sm);
            if (sec == 2) {   // swat the name tags that fly past
                for (int q = 0; q < 6; q++) {
                    float lt = fmodf(t - 22.0f, 6.0f) - q * 0.55f; if (lt < 0 || lt > 2.6f) continue;
                    int dir = (((int)((t - 22.0f) / 6.0f) + q) & 1) ? -1 : 1;
                    float qx = dir > 0 ? -60 + lt * 540 : 1340 - lt * 540;
                    if (fabsf(qx - P[i].x) < 70) { if (qx < P[i].x) P[i].aL = 2.6f; else P[i].aR = 2.6f; P[i].face = 1; }
                }
            }
        }
        std::sort(order, order + 5, [&](int a, int b) { return P[a].y < P[b].y; });
    }
    for (int q = 0; q < 5; q++) { int i = order[q]; if (vis[i]) drawGirl(i, P[i], t); }

    // ---- foreground per section
    if (sec == 0) {   // stickers stuck on the centre girl, peeling off to the beat
        IlPose& c = P[2]; float s = c.s;
        static const float dx[16] = {-20, 18, -4, 24, -26, 8, -14, 20, 0, -30, 30, -8, 14, -22, 26, 2};
        static const float dy[16] = {-150, -128, -96, -92, -70, -60, -34, -30, -8, -4, -112, 22, 34, 56, -150, -176};
        for (int j = 0; j < 16; j++) {
            float tp = 0.8f + j * 0.4f, ox = c.x + dx[j] * s * 1.25f + c.lean * 22 * s, oy = c.y - 62 * s - ((dy[j] < -100) ? -dy[j] * 0.78f * s + 70 * s * 0.0f : -dy[j] * 0.0f) - ((dy[j] >= -100) ? -dy[j] * s * 0.62f : 0) - 10 * s;
            float oy2 = c.y - 140 * s - dy[j] * s * 0.55f;
            (void)oy;
            if (t < tp) ilSticker(ox + sinf(t * 40 + j) * 1.5f, oy2, (ilR(j) - 0.5f) * 0.9f, j, 1.0f + 0.3f * s - 0.3f);
            else {
                float d = t - tp, vx = (ilR(j, 1) - 0.5f) * 900, vy = -520 - 320 * ilR(j, 2);
                float px = ox + vx * d, py = oy2 + vy * d + 780 * d * d, al = 1 - std::max(0.0f, (d - 1.1f) / 0.5f);
                if (al > 0) ilSticker(px, py, d * (ilR(j, 3) * 14 - 7), j, 1.0f, (int)(255 * al));
                if (d < 0.18f) for (int r = 0; r < 8; r++) { float a = r * IL_PI / 4; line(ox + cosf(a) * (10 + d * 200), oy2 + sinf(a) * (10 + d * 200), ox + cosf(a) * (26 + d * 260), oy2 + sinf(a) * (26 + d * 260), C(255, 255, 255, 200)); }
            }
        }
    }
    if (sec == 2) {   // name tags flying across the stage
        for (int q = 0; q < 6; q++) {
            float lt = fmodf(t - 22.0f, 6.0f) - q * 0.55f; if (lt < 0 || lt > 2.6f) continue;
            int dir = (((int)((t - 22.0f) / 6.0f) + q) & 1) ? -1 : 1;
            float x = dir > 0 ? -60 + lt * 540 : 1340 - lt * 540, y = 250 + 50 * ((q * 37) % 5) / 4.0f + sinf(lt * 5 + q) * 22;
            ilSticker(x, y, lt * 3 * dir, q * 3 + (int)((t - 22.0f) / 6.0f), 1.15f);
        }
    }
    if (sec == 3) {
        int turn = std::min(4, (int)((t - 42.3f) / 2.44f)); float lt = t - 42.3f - turn * 2.44f;
        float e = ilSmooth(0, 0.35f, lt) * (1 - ilSmooth(2.2f, 2.44f, lt));
        float ax = 640, chest = 640 - 1.8f * 100;   // approx chest height of the front girl
        polyFill({{ax - 18, 48}, {ax + 18, 48}, {ax + 230, 650}, {ax - 230, 650}}, C(255, 255, 255, (int)(34 * e)));
        for (int j = 0; j < 4; j++) {
            float sp = 0.2f + 0.55f * j, d = lt - sp; if (d < 0) continue;
            int id = turn * 2 + j; float gx = ax + (j - 1.5f) * 34;
            if (d < 0.28f) ilSticker(gx, -40 + (chest + 40) * (d / 0.28f), d * 3, id, 1.3f);
            else if (d < 0.55f) ilSticker(gx + sinf(d * 60) * 2, chest, 0.05f * sinf(d * 40), id, 1.3f);
            else { float u = d - 0.55f, dir = (j & 1) ? 1.0f : -1.0f; float al = 1 - u / 0.8f; if (al > 0) ilSticker(gx + dir * 700 * u, chest - 420 * u + 900 * u * u, u * 10 * dir, id, 1.3f, (int)(255 * al)); }
            if (d > 0.26f && d < 0.62f) {   // "NOT ME" bubble pops when a tag lands
                float pop = ilSmooth(0.26f, 0.34f, d) * (1 - ilSmooth(0.5f, 0.62f, d)), bx = ax + (j & 1 ? 150 : -150), by = 190 + 30 * (j % 2);
                float w = 150 * pop, h = 46 * pop; ilRect(bx, by, w + 6, h + 6, 0, C(30, 20, 50, 230)); ilRect(bx, by, w, h, 0, WHITE);
                if (pop > 0.6f) text("NOT ME!", bx, by - 12, 1.7f * pop, C(220, 40, 90), 1);
            }
        }
    }
    if (sec == 4 || sec == 5) {
        float pulse = 1 + 0.12f * k2;
        float al = sec == 5 ? 255 : 150;
        text("NOT ME", 640, sec == 5 ? 90 : 250, (sec == 5 ? 7.5f : 11.0f) * pulse, sec == 5 ? C(255, 70, 140, 255) : C(255, 255, 255, (int)al), 1, 8);
        ilConfetti(t, sec == 5 ? 60 : 90, 1.0f + k, 1.0f);
        for (int i = 0; i < 10; i++) {   // name-tag burst fan
            float ph = fmodf(t * 0.8f + i * 0.1f, 1.0f), a = i * 0.628f + t * 0.2f, rr = 80 + ph * 760;
            ilSticker(640 + cosf(a) * rr, 330 + sinf(a) * rr * 0.62f, ph * 8 + i, i, 0.9f + ph * 0.5f, (int)(230 * (1 - ph)));
        }
        if (sec == 4 && k > 0.88f) rect(0, 0, 1280, 720, C(255, 255, 255, (int)((k - 0.88f) * 700)));
    }
    if (sec == 5) {
        float u = t - 69.5f;
        for (int r = 0; r < 12; r++) { float a = r * IL_PI / 6 + t; line(640 + cosf(a) * 60, 330 + sinf(a) * 60, 640 + cosf(a) * (120 + 50 * k2 + u * 20), 330 + sinf(a) * (120 + 50 * k2 + u * 20), C(255, 255, 255, 90)); }
        text("ILLIT", 640, 236, 3.2f, C(120, 40, 120), 1, 12);
    }
    if (sec == 1 || sec == 2) ilConfetti(t, 22, 0.7f, 0.6f);
    (void)fl; (void)T;
}

static void drawIllit(int T) {
    float t = illitTime();
    float k = ilLow(t), k2 = k * k;
    // render the stage into the zoom texture so the camera can punch in on the beat
    float zoom = 1.0f + (t > 7.5f ? 0.035f * k2 : 0) + (t > 54.5f && t < 69.5f ? 0.03f + 0.04f * k2 : 0) + (t > 69.5f ? 0.04f * ilSmooth(69.5f, 74.7f, t) : 0);
    bool useTex = G.zoomTex != nullptr;
    if (useTex) { SDL_SetRenderTarget(G.ren, G.zoomTex); SDL_SetRenderDrawColor(G.ren, 0, 0, 0, 255); SDL_RenderClear(G.ren); }
    drawIllitWorld(t, T);
    if (useTex) {
        SDL_SetRenderTarget(G.ren, nullptr);
        float w = SCR_W / zoom, h = SCR_H / zoom, sh = (t > 54.5f && t < 69.5f) ? (rndf() - 0.5f) * 10 * k2 : 0;
        SDL_Rect src = {(int)std::max(0.0f, std::min(SCR_W - w, (SCR_W - w) / 2 + sh)), (int)((SCR_H - h) / 2), (int)w, (int)h};
        SDL_RenderCopy(G.ren, G.zoomTex, &src, nullptr);
    }
    // ---- overlays (not zoomed): letterbox, lower third, TV logo, fades
    rect(0, 0, 1280, 44, BLACK); rect(0, 676, 1280, 44, BLACK);
    rect(26, 8, 14, 14, ((T / 30) & 1) ? C(230, 40, 60) : C(120, 20, 30)); text("14 TV", 50, 4, 1.7f, WHITE);
    float lt = ilSmooth(0.6f, 1.2f, t) * (1 - ilSmooth(5.0f, 5.6f, t)) + ilSmooth(69.5f, 70.0f, t) * 0.0f;
    if (lt > 0.01f) {
        float x = -380 + 410 * lt;
        rect(x, 560, 360, 84, C(10, 10, 20, 220)); rect(x, 560, 8, 84, C(255, 90, 150));
        text("ILLIT", x + 24, 568, 3.0f, WHITE, 0, 4); text("NOT ME", x + 26, 612, 1.8f, C(255, 160, 200));
    }
    if (T > 90 && t < 70) text("X: skip", 1250, 684, 1.2f, C(255, 255, 255, 150), 2);
    if (t < 0.8f) rect(0, 0, 1280, 720, C(0, 0, 0, (int)(255 * (1 - t / 0.8f))));
    if (t > 73.6f) rect(0, 0, 1280, 720, C(0, 0, 0, (int)(255 * ilSmooth(73.6f, 74.7f, t))));
    scanlineOverlay();
}
