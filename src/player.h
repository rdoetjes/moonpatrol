#pragma once
#include <genesis.h>

typedef enum Jump_state {
    GROUND,
    UP,
    HANG,
    DOWN,
    WAIT
} Jump_state;

typedef struct Player{
    u8 lives;
    u16 x;
    u16 y;
    u32 score;
    Jump_state jump_state;
    u8 jumpFrame;
} Player;

void setup_player(Player *player, const u8 lives);
void move_player(Player* player);
void player_jump_state_handling(void);