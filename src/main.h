#pragma once
#include <genesis.h>

#define CHAR_WIDTH 40

typedef struct Player{
    u8 lives;
    u16 x;
    u16 y;
    bool isJumping;
} Player;

static void setup(void);
static void show_game_bg_b(void);
static void show_gameover_bg_b();
inline static void load_vdp(u16 numPal, const u16* pal, int x, int y, VDPPlane plane, const Image *image);
static void draw();
static void logic(void);
static void setup_player(Player *player, const u8 lives);