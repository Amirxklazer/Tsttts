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

static const float IL_PI_C = 3.14159265f;
static void drawPerson(float x, float gy, int dir, const Look& L, int walk, bool moving);          // defined in chars.hpp (v0.9.0 redesign)
static void drawBot(float x, float gy, Col body, int t, int dir, bool happy = true);               // defined in chars.hpp
