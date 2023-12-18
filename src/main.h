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
static void bg_b(void);
static void draw();
static void logic(void);
static void setup_player(Player *player, const u8 lives);
static void gameover_screen();