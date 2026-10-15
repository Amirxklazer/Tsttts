// core.hpp - SDL wrapper: window, input, drawing, bitmap font, small helpers
#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include "font_atlas.h"

#define SCR_W 1280
#define SCR_H 720

#ifdef __SWITCH__
#define SAVE_DIR "sdmc:/switch/Ilot14/"
#else
#define SAVE_DIR "./save/"
#endif

typedef unsigned int u32;

struct Col { Uint8 r, g, b, a; };
static inline Col C(int r, int g, int b, int a = 255) { return Col{(Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a}; }
static const Col WHITE = {255, 255, 255, 255};
static const Col BLACK = {10, 8, 0, 255};
static const Col ORANGE = {249, 115, 22, 255};

// ---------- buttons ----------
enum {
    B_A = 1, B_B = 2, B_X = 4, B_Y = 8, B_UP = 16, B_DOWN = 32, B_LEFT = 64, B_RIGHT = 128,
    B_PLUS = 256, B_MINUS = 512, B_L = 1024, B_R = 2048
};

struct Input {
    u32 held = 0, prev = 0, pressed = 0;
    float ax = 0, ay = 0;
    bool quit = false;
    std::vector<std::pair<float, float>> taps;   // screen taps this frame (1280x720 space)
    float drag = 0;                               // vertical finger drag this frame (pixels)
    bool down(u32 b) const { return (held & b) != 0; }
    bool hit(u32 b) const { return (pressed & b) != 0; }
};

struct Gfx {
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr; SDL_Texture* zoomTex = nullptr;
    SDL_Texture* fontTex = nullptr;
    std::vector<SDL_Joystick*> pads;
    u32 keyHeld = 0, padHeld = 0, inject = 0;
    float padAx = 0, padAy = 0;
    bool scanlines = true;
    int shakeT = 0;
    std::vector<std::pair<float, float>> taps;
    float drag = 0;
    int holdT[4] = {0, 0, 0, 0};
    // local co-op: players 2-4 (pad index 1..3; player 2 can also use the keyboard: I J K L, U = A, O = B)
    bool coop = false;
    u32 padHeldN[4] = {0, 0, 0, 0}, p2Key = 0;
    Input coIn[3];
} G;

// ---------- touch hit regions (menus register these while drawing) ----------
struct Hit { float x, y, w, h; int kind, idx; };   // kind: 0 select+confirm, 1 select, 2 back, 3 left, 4 right
static std::vector<Hit> HITS;
static std::string g_hint = "A Select    B Back";
static bool g_backBtn = true;

// ---------- file helpers ----------
static void ensureDir() {
#ifdef __SWITCH__
    mkdir("sdmc:/switch", 0777);
#endif
    mkdir(SAVE_DIR, 0777);
}
static std::string readFile(const std::string& p) {
    std::string s;
    FILE* f = fopen(p.c_str(), "rb");
    if (!f) return s;
    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
    fclose(f);
    return s;
}
static bool writeFile(const std::string& p, const std::string& s) {
    FILE* f = fopen(p.c_str(), "wb");
    if (!f) return false;
    fwrite(s.data(), 1, s.size(), f);
    fclose(f);
    return true;
}
static std::vector<std::string> splitStr(const std::string& s, char d) {
    std::vector<std::string> out;
    std::string cur;
    for (char c : s) {
        if (c == d) { out.push_back(cur); cur.clear(); }
        else cur += c;
    }
    out.push_back(cur);
    return out;
}
static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// ---------- random ----------
static u32 rngState = 12345;
static u32 rnd() {
    rngState ^= rngState << 13; rngState ^= rngState >> 17; rngState ^= rngState << 5;
    return rngState;
}
static float rndf() { return (rnd() & 0xFFFFFF) / 16777216.0f; }
static int rndi(int a, int b) { return a + (int)(rnd() % (u32)(b - a + 1)); }

// ---------- init ----------
static bool gfxInit(bool headless) {
    Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_JOYSTICK;
    if (SDL_Init(flags) != 0) { fprintf(stderr, "SDL_Init: %s\n", SDL_GetError()); return false; }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    G.win = SDL_CreateWindow("Ilot14", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_W, SCR_H, 0);
    if (!G.win) { fprintf(stderr, "window: %s\n", SDL_GetError()); return false; }
    G.ren = SDL_CreateRenderer(G.win, -1, headless ? SDL_RENDERER_SOFTWARE : (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!G.ren) G.ren = SDL_CreateRenderer(G.win, -1, SDL_RENDERER_SOFTWARE);
    if (!G.ren) { fprintf(stderr, "renderer: %s\n", SDL_GetError()); return false; }
    SDL_RenderSetLogicalSize(G.ren, SCR_W, SCR_H);
    SDL_SetRenderDrawBlendMode(G.ren, SDL_BLENDMODE_BLEND);
    G.zoomTex = SDL_CreateTexture(G.ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCR_W, SCR_H);
    if (G.zoomTex) SDL_SetTextureBlendMode(G.zoomTex, SDL_BLENDMODE_BLEND);
    // font texture
    SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat(0, 256, 448, 32, SDL_PIXELFORMAT_RGBA32);
    Uint8* px = (Uint8*)s->pixels;
    for (int i = 0; i < 256 * 448; i++) {
        px[i * 4 + 0] = 255; px[i * 4 + 1] = 255; px[i * 4 + 2] = 255; px[i * 4 + 3] = FONT_ATLAS[i];
    }
    G.fontTex = SDL_CreateTextureFromSurface(G.ren, s);
    SDL_SetTextureBlendMode(G.fontTex, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(s);
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        SDL_Joystick* j = SDL_JoystickOpen(i);
        if (j) G.pads.push_back(j);
    }
    return true;
}

// ---------- input ----------
static u32 mapKey(SDL_Keycode k) {
    switch (k) {
        case SDLK_z: case SDLK_RETURN: case SDLK_SPACE: return B_A;
        case SDLK_x: case SDLK_BACKSPACE: return B_B;
        case SDLK_c: return B_X;
        case SDLK_v: return B_Y;
        case SDLK_UP: case SDLK_w: return B_UP;
        case SDLK_DOWN: case SDLK_s: return B_DOWN;
        case SDLK_LEFT: case SDLK_a: return B_LEFT;
        case SDLK_RIGHT: case SDLK_d: return B_RIGHT;
        case SDLK_ESCAPE: case SDLK_p: return B_PLUS;
        case SDLK_TAB: return B_MINUS;
        case SDLK_q: return B_L;
        case SDLK_e: return B_R;
    }
    return 0;
}
static u32 mapKey2(SDL_Keycode k) {
    switch (k) {
        case SDLK_u: return B_A; case SDLK_o: return B_B; case SDLK_i: return B_UP; case SDLK_k: return B_DOWN; case SDLK_j: return B_LEFT; case SDLK_l: return B_RIGHT;
    }
    return 0;
}
static u32 mapPad(int b) {
    switch (b) {
        case 0: return B_A; case 1: return B_B; case 2: return B_X; case 3: return B_Y;
        case 6: return B_L; case 7: return B_R;
        case 10: return B_PLUS; case 11: return B_MINUS;
        case 12: return B_LEFT; case 13: return B_UP; case 14: return B_RIGHT; case 15: return B_DOWN;
    }
    return 0;
}

static void pollInput(Input& in) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: in.quit = true; break;
            case SDL_KEYDOWN: if (!e.key.repeat) { G.keyHeld |= mapKey(e.key.keysym.sym); G.p2Key |= mapKey2(e.key.keysym.sym); } break;
            case SDL_KEYUP: G.keyHeld &= ~mapKey(e.key.keysym.sym); G.p2Key &= ~mapKey2(e.key.keysym.sym); break;
            case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP: {
                int idx = 0;
                for (size_t i = 0; i < G.pads.size(); i++) if (SDL_JoystickInstanceID(G.pads[i]) == e.jbutton.which) idx = (int)i;
                u32 b = mapPad(e.jbutton.button);
                if (idx > 3) idx = 3;
                if (e.type == SDL_JOYBUTTONDOWN) G.padHeldN[idx] |= b; else G.padHeldN[idx] &= ~b;
            } break;
            case SDL_FINGERDOWN: G.taps.push_back({e.tfinger.x * SCR_W, e.tfinger.y * SCR_H}); break;
            case SDL_FINGERMOTION: G.drag += e.tfinger.dy * SCR_H; break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.which != SDL_TOUCH_MOUSEID) { float lx = 0, ly = 0; SDL_RenderWindowToLogical(G.ren, e.button.x, e.button.y, &lx, &ly); G.taps.push_back({lx, ly}); }
                break;
            case SDL_MOUSEWHEEL: G.drag += e.wheel.y * 30.0f; break;
            case SDL_JOYDEVICEADDED: {
                SDL_Joystick* j = SDL_JoystickOpen(e.jdevice.which);
                if (j) G.pads.push_back(j);
            } break;
            default: break;
        }
    }
    // sticks (poll so any pad counts)
    float ax = 0, ay = 0;
    for (size_t pi = 0; pi < G.pads.size(); pi++) {
        SDL_Joystick* j = G.pads[pi];
        if (G.coop && pi > 0) continue;
        if (!SDL_JoystickGetAttached(j)) continue;
        float x = SDL_JoystickGetAxis(j, 0) / 32767.0f;
        float y = SDL_JoystickGetAxis(j, 1) / 32767.0f;
        if (fabsf(x) > fabsf(ax)) ax = x;
        if (fabsf(y) > fabsf(ay)) ay = y;
    }
    if (fabsf(ax) < 0.25f) ax = 0;
    if (fabsf(ay) < 0.25f) ay = 0;
    G.padHeld = G.padHeldN[0];
    if (!G.coop) G.padHeld |= G.padHeldN[1] | G.padHeldN[2] | G.padHeldN[3];
    u32 h = G.keyHeld | G.padHeld | G.inject;
    if (ax < -0.5f) h |= B_LEFT;
    if (ax > 0.5f) h |= B_RIGHT;
    if (ay < -0.5f) h |= B_UP;
    if (ay > 0.5f) h |= B_DOWN;
    // analog movement value from digital too
    float dx = ax, dy = ay;
    if (h & B_LEFT) dx = -1;
    if (h & B_RIGHT) dx = 1;
    if (h & B_UP) dy = -1;
    if (h & B_DOWN) dy = 1;
    in.prev = in.held;
    in.held = h;
    in.pressed = in.held & ~in.prev;
    // key repeat for the D-pad: hold a direction and it repeats (easier menu navigation)
    const u32 dirs[4] = {B_UP, B_DOWN, B_LEFT, B_RIGHT};
    for (int i = 0; i < 4; i++) {
        if (h & dirs[i]) {
            G.holdT[i]++;
            if (G.holdT[i] > 22 && (G.holdT[i] - 22) % 6 == 0) in.pressed |= dirs[i];
        } else G.holdT[i] = 0;
    }
    in.taps = G.taps; G.taps.clear();
    in.drag = G.drag; G.drag = 0;
    in.ax = dx; in.ay = dy;
    // co-op players 2..4
    for (int k = 0; k < 3; k++) {
        Input& ci = G.coIn[k];
        u32 hh = G.padHeldN[k + 1] | (k == 0 ? G.p2Key : 0);
        float cx = 0;
        if ((size_t)(k + 1) < G.pads.size() && SDL_JoystickGetAttached(G.pads[k + 1])) {
            float x = SDL_JoystickGetAxis(G.pads[k + 1], 0) / 32767.0f;
            if (fabsf(x) > 0.3f) cx = x;
            if (x < -0.5f) hh |= B_LEFT; if (x > 0.5f) hh |= B_RIGHT;
        }
        if (hh & B_LEFT) cx = -1; if (hh & B_RIGHT) cx = 1;
        ci.prev = ci.held; ci.held = hh; ci.pressed = ci.held & ~ci.prev; ci.ax = cx;
    }
}

// ---------- drawing ----------
static void setCol(Col c) { SDL_SetRenderDrawColor(G.ren, c.r, c.g, c.b, c.a); }
static void rect(float x, float y, float w, float h, Col c) {
    setCol(c);
    SDL_FRect r = {x, y, w, h};
    SDL_RenderFillRectF(G.ren, &r);
}
static void frameR(float x, float y, float w, float h, Col c, int t = 2) {
    rect(x, y, w, t, c); rect(x, y + h - t, w, t, c);
    rect(x, y, t, h, c); rect(x + w - t, y, t, h, c);
}
static void lineH(float x, float y, float w, Col c, int t = 2) { rect(x, y, w, t, c); }
static void dashH(float x, float y, float w, Col c, int dash = 14, int gap = 10, int t = 2) {
    for (float p = 0; p < w; p += dash + gap) rect(x + p, y, std::min<float>(dash, w - p), t, c);
}
static void dashV(float x, float y, float h, Col c, int dash = 14, int gap = 10, int t = 2) {
    for (float p = 0; p < h; p += dash + gap) rect(x, y + p, t, std::min<float>(dash, h - p), c);
}
static void line(float x1, float y1, float x2, float y2, Col c) {
    setCol(c);
    SDL_RenderDrawLineF(G.ren, x1, y1, x2, y2);
}
static void fillCircle(float cx, float cy, float r, Col c) {
    setCol(c);
    for (int dy = -(int)r; dy <= (int)r; dy++) {
        float dx = sqrtf(std::max(0.0f, r * r - dy * dy));
        SDL_FRect rr = {cx - dx, cy + dy, dx * 2, 1};
        SDL_RenderFillRectF(G.ren, &rr);
    }
}

// utf8 -> latin1-ish codes
static std::vector<unsigned char> decodeUtf8(const std::string& s) {
    std::vector<unsigned char> out;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = s[i];
        unsigned cp = c;
        int n = 1;
        if (c >= 0xF0) { cp = c & 7; n = 4; }
        else if (c >= 0xE0) { cp = c & 15; n = 3; }
        else if (c >= 0xC0) { cp = c & 31; n = 2; }
        for (int k = 1; k < n && i + k < s.size(); k++) cp = (cp << 6) | (s[i + k] & 63);
        i += n;
        if (cp == 0x2122) { out.push_back('T'); out.push_back('M'); continue; }
        if (cp == 0x2019 || cp == 0x2018) cp = '\'';
        if (cp == 0x201C || cp == 0x201D) cp = '"';
        if (cp == 0x2026) { out.push_back('.'); out.push_back('.'); out.push_back('.'); continue; }
        if (cp == 0x2014 || cp == 0x2013) cp = '-';
        if (cp == 0x2022) cp = 0xB7;
        if (cp < 32 || cp > 255) cp = '?';
        out.push_back((unsigned char)cp);
    }
    return out;
}
static int utf8len(const std::string& s) { return (int)decodeUtf8(s).size(); }

// text: scale 1 = 8x16 cells. align 0 left, 1 center, 2 right
static int textW(const std::string& s, float sc) { return (int)(utf8len(s) * 8 * sc); }
static void text(const std::string& s, float x, float y, float sc, Col c, int align = 0, float spacing = 0) {
    std::vector<unsigned char> cs = decodeUtf8(s);
    float w = cs.size() * (8 * sc + spacing) - (cs.empty() ? 0 : spacing);
    if (align == 1) x -= w / 2;
    else if (align == 2) x -= w;
    SDL_SetTextureColorMod(G.fontTex, c.r, c.g, c.b);
    SDL_SetTextureAlphaMod(G.fontTex, c.a);
    for (unsigned char ch : cs) {
        if (ch > 32) {
            int i = ch - 32;
            SDL_Rect src = {(i % 16) * 16, (i / 16) * 32, 16, 32};
            SDL_FRect dst = {x, y, 8 * sc, 16 * sc};
            SDL_RenderCopyF(G.ren, G.fontTex, &src, &dst);
        }
        x += 8 * sc + spacing;
    }
}
static void textShadow(const std::string& s, float x, float y, float sc, Col c, int align = 0) {
    text(s, x + 2, y + 2, sc, C(0, 0, 0, 160), align);
    text(s, x, y, sc, c, align);
}

static std::vector<std::string> wrapText(const std::string& s, int maxChars) {
    std::vector<std::string> lines;
    std::string cur;
    int curLen = 0;
    std::vector<std::string> words = splitStr(s, ' ');
    for (auto& w : words) {
        int wl = utf8len(w);
        if (curLen > 0 && curLen + 1 + wl > maxChars) {
            lines.push_back(cur);
            cur.clear(); curLen = 0;
        }
        if (curLen > 0) { cur += ' '; curLen++; }
        cur += w; curLen += wl;
    }
    if (!cur.empty() || lines.empty()) lines.push_back(cur);
    return lines;
}

static Col mix(Col a, Col b, float t) {
    return C((int)(a.r + (b.r - a.r) * t), (int)(a.g + (b.g - a.g) * t), (int)(a.b + (b.b - a.b) * t), (int)(a.a + (b.a - a.a) * t));
}
static Col dim(Col a, float f) { return C((int)(a.r * f), (int)(a.g * f), (int)(a.b * f), a.a); }

static void scanlineOverlay() {
    if (!G.scanlines) return;
    for (int y = 0; y < SCR_H; y += 3) rect(0, y, SCR_W, 1, C(0, 0, 0, 38));
}

// ---------- pixel people / bots ----------
struct Look { Col shirt, hair, skin, pants; int hairStyle; float h; bool tag14; int topStyle = 0, acc = 0, eyes = 0, back = 0, face = 0; Col shoes = {30, 30, 30, 255}; Col trim = {255, 255, 255, 255}; };

// feet at (x, gy). dir -1 left / 1 right. walk = frame counter for legs
static void drawPerson(float x, float gy, int dir, const Look& L, int walk, bool moving) {
    float s = L.h; // scale around 1.0
    float legH = 30 * s, bodyH = 40 * s, headS = 30 * s, bw = 34 * s;
    float swing = moving ? sinf(walk * 0.3f) * 8 * s : 0;
    // shadow
    rect(x - bw * 0.7f, gy - 3, bw * 1.4f, 5, C(0, 0, 0, 70));
    // back items (behind the body)
    {
        float bt = gy - legH - bodyH;
        if (L.back == 1) { rect(x - dir * 16 * s - 9 * s, bt + 4 * s, 18 * s, 28 * s, C(70, 70, 90)); rect(x - dir * 16 * s - 9 * s, bt + 4 * s, 18 * s, 5 * s, C(249, 115, 22)); }
        else if (L.back == 2) { float sw = sinf(walk * 0.2f) * 3; rect(x - 17 * s - 2 + sw, bt + 2 * s, 34 * s + 4, bodyH + legH * 0.8f, C(200, 40, 50)); rect(x - 17 * s - 2 + sw, bt + 2 * s, 34 * s + 4, 4, C(250, 210, 60)); }
        else if (L.back == 3 || L.back == 4) { Col wc = L.back == 3 ? C(250, 250, 255, 235) : C(50, 30, 70, 235); float fl = sinf(walk * 0.12f) * 6; for (int k = -1; k <= 1; k += 2) { float wx = x + k * 18 * s; rect(wx - (k > 0 ? 0 : 22 * s), bt - 4 * s + fl * k, 22 * s, 8 * s, wc); rect(wx - (k > 0 ? 0 : 16 * s), bt + 4 * s + fl * k, 16 * s, 8 * s, dim(wc, 0.85f)); rect(wx - (k > 0 ? 0 : 10 * s), bt + 12 * s + fl * k, 10 * s, 8 * s, dim(wc, 0.7f)); } }
    }
    // legs
    rect(x - 12 * s, gy - legH + (swing > 0 ? -swing * 0.3f : 0), 10 * s, legH + (swing > 0 ? swing * 0.3f : 0), L.pants);
    rect(x + 2 * s, gy - legH + (swing < 0 ? swing * 0.3f : 0), 10 * s, legH - (swing < 0 ? swing * 0.3f : 0), dim(L.pants, 0.85f));
    // shoes
    rect(x - 14 * s, gy - 5, 14 * s, 5, L.shoes);
    rect(x + 1 * s, gy - 5, 14 * s, 5, L.shoes);
    // body
    float by = gy - legH - bodyH;
    rect(x - bw / 2, by, bw, bodyH, L.shirt);
    rect(x - bw / 2 - 6 * s, by + 4, 7 * s, bodyH - 10, dim(L.shirt, 0.9f));
    rect(x + bw / 2 - 1, by + 4, 7 * s, bodyH - 10, dim(L.shirt, 0.9f));
    rect(x - bw / 2 - 6 * s, by + bodyH - 10, 7 * s, 8, L.skin);
    rect(x + bw / 2 - 1, by + bodyH - 10, 7 * s, 8, L.skin);
    // clothing styles
    if (L.topStyle == 1) { // hoodie: hood bulge + pocket
        rect(x - bw / 2 + 2, by - 5, bw - 4, 8, dim(L.shirt, 0.8f));
        rect(x - 12 * s, by + bodyH - 14, 24 * s, 11, dim(L.shirt, 0.82f));
    } else if (L.topStyle == 2) { // jacket: light collar + centre line
        rect(x - 1, by, 3, bodyH, dim(L.shirt, 0.6f));
        rect(x - bw / 2, by, 8, 7, mix(L.shirt, WHITE, 0.5f)); rect(x + bw / 2 - 8, by, 8, 7, mix(L.shirt, WHITE, 0.5f));
        rect(x - bw / 2, by + bodyH - 6, bw, 6, dim(L.shirt, 0.75f));
    } else if (L.topStyle == 3) { // striped
        for (int k = 0; k < 4; k++) rect(x - bw / 2, by + 6 + k * 10 * s, bw, 4, mix(L.shirt, WHITE, 0.55f));
    } else if (L.topStyle == 4) { // vest over white shirt
        rect(x - bw / 2, by, bw, bodyH, mix(L.shirt, WHITE, 0.8f)); rect(x - bw / 2, by, 10 * s, bodyH, L.shirt); rect(x + bw / 2 - 10 * s, by, 10 * s, bodyH, L.shirt);
        for (int k = 0; k < 3; k++) rect(x - 1, by + 8 + k * 11 * s, 3, 3, L.trim);
    } else if (L.topStyle == 5) { // overalls
        rect(x - bw / 2, by, bw, bodyH, mix(L.shirt, WHITE, 0.7f)); rect(x - bw / 2 + 3, by + 14 * s, bw - 6, bodyH - 14 * s, L.pants);
        rect(x - bw / 2 + 4, by, 5, 16 * s, L.pants); rect(x + bw / 2 - 9, by, 5, 16 * s, L.pants); rect(x - 4, by + 20 * s, 8, 7, dim(L.pants, 0.8f));
    } else if (L.topStyle == 6) { // long coat
        rect(x - bw / 2 - 2, by, bw + 4, bodyH + 22 * s, L.shirt); rect(x - 1, by, 3, bodyH + 22 * s, dim(L.shirt, 0.6f));
        rect(x - bw / 2 - 2, by + bodyH + 18 * s, bw + 4, 4, L.trim);
    } else if (L.topStyle == 7) { // track jacket w/ side stripes
        rect(x - bw / 2, by, 5, bodyH, L.trim); rect(x + bw / 2 - 5, by, 5, bodyH, L.trim); rect(x - 1, by, 3, bodyH, dim(L.shirt, 0.6f));
        rect(x - bw / 2, by, bw, 6, dim(L.shirt, 0.8f));
    } else if (L.topStyle == 8) { // logo tee
        fillCircle(x, by + 16 * s, 7 * s, L.trim); fillCircle(x, by + 16 * s, 4 * s, L.shirt);
    }
    if (L.tag14) {
        text("14", x, by + 8 * s, 1.1f * s, BLACK, 1);
    }
    // head
    float hy = by - headS + 2;
    rect(x - headS / 2, hy, headS, headS, L.skin);
    // hair
    if (L.hairStyle == 0) { // short
        rect(x - headS / 2 - 1, hy - 4, headS + 2, 11 * s, L.hair);
    } else if (L.hairStyle == 1) { // long
        rect(x - headS / 2 - 2, hy - 4, headS + 4, 12 * s, L.hair);
        rect(x - headS / 2 - 3, hy, 7 * s, headS + 6, L.hair);
        rect(x + headS / 2 - 4 * s, hy, 7 * s, headS + 6, L.hair);
    } else if (L.hairStyle == 2) { // bald-ish / buzz
        rect(x - headS / 2, hy - 2, headS, 6 * s, dim(L.hair, 0.9f));
    } else if (L.hairStyle == 3) { // curly / big
        rect(x - headS / 2 - 4, hy - 7, headS + 8, 15 * s, L.hair);
    } else if (L.hairStyle == 4) { // spiky
        rect(x - headS / 2 - 1, hy - 3, headS + 2, 9 * s, L.hair);
        for (int k = 0; k < 4; k++) rect(x - headS / 2 + 1 + k * (headS / 4.0f), hy - 12, headS / 4.0f - 2, 11, L.hair);
    } else if (L.hairStyle == 5) { // ponytail
        rect(x - headS / 2 - 1, hy - 4, headS + 2, 11 * s, L.hair);
        rect(x + (dir > 0 ? -headS / 2 - 8 : headS / 2 + 1), hy + 2, 8, 24 * s, L.hair);
    } else if (L.hairStyle == 6) { // bun
        rect(x - headS / 2 - 1, hy - 4, headS + 2, 11 * s, L.hair);
        fillCircle(x, hy - 10, 8 * s, L.hair);
    } else if (L.hairStyle == 7) { // side-swept
        rect(x - headS / 2 - 1, hy - 4, headS + 2, 9 * s, L.hair);
        rect(x - headS / 2 - 1, hy, headS * 0.55f, 12 * s, L.hair);
    } else if (L.hairStyle == 8) { // twin tails
        rect(x - headS / 2 - 1, hy - 4, headS + 2, 11 * s, L.hair);
        rect(x - headS / 2 - 9, hy + 4, 8, 26 * s, L.hair); rect(x + headS / 2 + 1, hy + 4, 8, 26 * s, L.hair);
    } else if (L.hairStyle == 9) { // mohawk
        rect(x - 5, hy - 14, 10, 14, L.hair); rect(x - headS / 2 - 1, hy - 1, headS + 2, 4, dim(L.hair, 0.8f));
    } else if (L.hairStyle == 10) { // messy tall
        rect(x - headS / 2 - 2, hy - 8, headS + 4, 14 * s, L.hair);
        for (int k = 0; k < 3; k++) rect(x - headS / 2 + k * 11, hy - 15 - (k % 2) * 4, 8, 9, L.hair);
    } else { // 11 = long straight with fringe
        rect(x - headS / 2 - 2, hy - 4, headS + 4, 13 * s, L.hair);
        rect(x - headS / 2 - 4, hy, 8 * s, headS + 16, L.hair); rect(x + headS / 2 - 4 * s, hy, 8 * s, headS + 16, L.hair);
    }
    // eyes
    float ex = dir > 0 ? 4 : -4;
    if (L.eyes == 1) { rect(x + ex - 8 * s, hy + 15 * s, 6 * s, 2, BLACK); rect(x + ex + 3 * s, hy + 15 * s, 6 * s, 2, BLACK); }
    else if (L.eyes == 2) { rect(x + ex - 8 * s, hy + 14 * s, 5 * s, 3, BLACK); rect(x + ex + 4 * s, hy + 14 * s, 5 * s, 3, BLACK); }
    else if (L.eyes == 3) { rect(x + ex - 9 * s, hy + 10 * s, 7 * s, 9 * s, WHITE); rect(x + ex + 3 * s, hy + 10 * s, 7 * s, 9 * s, WHITE); rect(x + ex - 7 * s, hy + 12 * s, 4 * s, 5 * s, BLACK); rect(x + ex + 5 * s, hy + 12 * s, 4 * s, 5 * s, BLACK); }
    else { rect(x + ex - 8 * s, hy + 12 * s, 5 * s, 6 * s, BLACK); rect(x + ex + 4 * s, hy + 12 * s, 5 * s, 6 * s, BLACK); }
    rect(x + ex * 1.5f - 4 * s, hy + 23 * s, 8 * s, 2, dim(L.skin, 0.55f));
    // accessories
    if (L.acc == 1) { // glasses
        frameR(x + ex - 10 * s, hy + 10 * s, 10 * s, 10 * s, C(30, 30, 40), 2); frameR(x + ex + 2 * s, hy + 10 * s, 10 * s, 10 * s, C(30, 30, 40), 2);
        rect(x + ex - 1, hy + 14 * s, 4, 2, C(30, 30, 40));
    } else if (L.acc == 2) { // cap
        rect(x - headS / 2 - 2, hy - 6, headS + 4, 12 * s, C(200, 40, 40));
        rect(dir > 0 ? x : x - headS / 2 - 12, hy + 4, headS / 2 + 12, 5, C(160, 30, 30));
    } else if (L.acc == 3) { // headphones
        rect(x - headS / 2 - 3, hy - 3, headS + 6, 5, C(40, 40, 50));
        rect(x - headS / 2 - 6, hy + 8, 8, 14 * s, C(40, 40, 50)); rect(x + headS / 2 - 2, hy + 8, 8, 14 * s, C(40, 40, 50));
    } else if (L.acc == 4) { // scarf
        rect(x - headS / 2 - 1, hy + headS - 2, headS + 2, 9, C(240, 240, 240)); rect(x + 4, hy + headS, 8, 20, C(240, 240, 240));
    } else if (L.acc == 5) { // beanie
        rect(x - headS / 2 - 2, hy - 8, headS + 4, 14 * s, L.trim); fillCircle(x, hy - 9, 4 * s, L.trim); rect(x - headS / 2 - 2, hy + 4, headS + 4, 3, dim(L.trim, 0.7f));
    } else if (L.acc == 6) { // headband
        rect(x - headS / 2 - 1, hy + 2, headS + 2, 5, L.trim);
    } else if (L.acc == 7) { // tie / bow
        rect(x - 4, hy + headS + 2, 8, 6, C(200, 40, 40)); rect(x - 7, hy + headS + 1, 5, 8, C(200, 40, 40)); rect(x + 3, hy + headS + 1, 5, 8, C(200, 40, 40));
    } else if (L.acc == 8) { // eyepatch
        rect(x + ex + 2 * s, hy + 9 * s, 11 * s, 11 * s, C(20, 20, 24)); rect(x - headS / 2, hy + 6 * s, headS, 2, C(20, 20, 24));
    } else if (L.acc == 9) { // little crown
        rect(x - 10, hy - 11, 20, 8, C(250, 210, 60)); for (int k = 0; k < 3; k++) rect(x - 10 + k * 8, hy - 15, 4, 5, C(250, 210, 60));
    } else if (L.acc == 10) { // bandana
        rect(x - headS / 2 - 1, hy - 2, headS + 2, 7, C(200, 50, 50)); rect(x + (dir > 0 ? -headS / 2 - 8 : headS / 2), hy + 2, 8, 6, C(200, 50, 50));
    } else if (L.acc == 11) { // goggles on forehead
        rect(x - headS / 2, hy, headS, 4, C(50, 50, 60)); fillCircle(x - 7, hy + 2, 5, C(120, 220, 255)); fillCircle(x + 7, hy + 2, 5, C(120, 220, 255));
    } else if (L.acc == 12) { // wizard hat
        rect(x - headS / 2 - 8, hy - 2, headS + 16, 5, C(70, 50, 140)); rect(x - 10, hy - 18, 20, 17, C(80, 60, 160)); rect(x - 6, hy - 30, 12, 13, C(80, 60, 160)); rect(x - 2, hy - 38, 6, 9, C(80, 60, 160)); rect(x - 10, hy - 4, 20, 3, C(250, 210, 60));
    } else if (L.acc == 13) { // cat ears
        for (int k = -1; k <= 1; k += 2) { rect(x + k * 11 - 5, hy - 12, 10, 12, L.hair); rect(x + k * 11 - 2, hy - 8, 4, 8, C(255, 170, 190)); }
    } else if (L.acc == 14) { // halo
        float hb = sinf(walk * 0.08f) * 2; frameR(x - 14, hy - 17 + hb, 28, 8, C(255, 235, 120), 3);
    } else if (L.acc == 15) { // antenna
        rect(x - 1, hy - 16, 3, 16, C(120, 120, 130)); fillCircle(x, hy - 18, 4, C(255, 80, 80));
    } else if (L.acc == 16) { // flower
        fillCircle(x + 10, hy + 1, 5, C(255, 140, 190)); fillCircle(x + 10, hy + 1, 2, C(255, 230, 90));
    } else if (L.acc == 17) { // party hat
        rect(x - 9, hy - 8, 18, 8, C(255, 90, 160)); rect(x - 6, hy - 18, 12, 10, C(90, 200, 255)); rect(x - 2, hy - 26, 5, 9, C(255, 230, 90)); fillCircle(x, hy - 27, 3, C(255, 255, 255));
    } else if (L.acc == 18) { // pumpkin hat
        fillCircle(x, hy - 6, 11, C(240, 120, 20)); rect(x - 2, hy - 20, 4, 6, C(70, 120, 40)); rect(x - 5, hy - 8, 3, 3, C(30, 20, 10)); rect(x + 3, hy - 8, 3, 3, C(30, 20, 10));
    } else if (L.acc == 19) { // sunglasses
        rect(x + ex - 11 * s, hy + 10 * s, 11 * s, 8 * s, C(15, 15, 20)); rect(x + ex + 2 * s, hy + 10 * s, 11 * s, 8 * s, C(15, 15, 20)); rect(x + ex - 1, hy + 12 * s, 4, 2, C(15, 15, 20));
    }
    // face extras
    if (L.face == 1) { for (int k = 0; k < 3; k++) { rect(x + ex - 9 * s + k * 4, hy + 20 * s, 2, 2, dim(L.skin, 0.6f)); rect(x + ex + 3 * s + k * 4, hy + 20 * s, 2, 2, dim(L.skin, 0.6f)); } }
    else if (L.face == 2) { rect(x + ex - 11 * s, hy + 19 * s, 6 * s, 4 * s, C(255, 130, 140, 160)); rect(x + ex + 6 * s, hy + 19 * s, 6 * s, 4 * s, C(255, 130, 140, 160)); }
    else if (L.face == 3) { rect(x + ex * 1.5f - 8 * s, hy + 21 * s, 16 * s, 4 * s, C(40, 25, 20)); }
    else if (L.face == 4) { for (int k = 0; k < 3; k++) { rect(x + ex - 18 * s, hy + 18 * s + k * 3, 10 * s, 1, C(40, 40, 40)); rect(x + ex + 10 * s, hy + 18 * s + k * 3, 10 * s, 1, C(40, 40, 40)); } }
}

static void drawBot(float x, float gy, Col body, int t, int dir, bool happy = true) {
    float bob = sinf(t * 0.12f) * 3;
    rect(x - 26, gy - 3, 52, 5, C(0, 0, 0, 70));
    rect(x - 24, gy - 40 + bob, 48, 34, body);
    rect(x - 24, gy - 40 + bob, 48, 6, dim(body, 0.75f));
    rect(x - 18, gy - 6, 10, 6, C(40, 40, 40));
    rect(x + 8, gy - 6, 10, 6, C(40, 40, 40));
    // face plate
    rect(x - 17, gy - 34 + bob, 34, 18, C(20, 24, 40));
    float ex = dir * 2;
    rect(x - 11 + ex, gy - 30 + bob, 6, 8, C(120, 255, 220));
    rect(x + 5 + ex, gy - 30 + bob, 6, 8, C(120, 255, 220));
    if (happy) rect(x - 5 + ex, gy - 20 + bob, 10, 2, C(120, 255, 220));
    // antenna
    rect(x - 1, gy - 52 + bob, 3, 12, C(180, 180, 180));
    fillCircle(x, gy - 54 + bob, 4, ORANGE);
}
