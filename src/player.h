#pragma once
#include <genesis.h>

typedef struct Player{
    u8 lives;
    u16 x;
    u16 y;
    bool isJumping;
} Player;

void setup_player(Player *player, const u8 lives);
