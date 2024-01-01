#pragma once
#include <genesis.h>
#include "player.h"

#define CHAR_WIDTH 40
//hugs the left of the screen but with a bit of room to spare
#define LEFT_BOUNDERY_PLAYER 5
//320 is size of width 64 is the number of pixels in x position player sprite
#define RIGHT_BOUNDERY_PLAYER 320-64

//define the amount of frame for each jump animation
#define JUMP_UP_NR_FAMES 10
#define JUMP_HANG_NR_FAMES 40 + JUMP_UP_NR_FAMES
#define JUMP_DOWN_NR_FAMES 10 + JUMP_HANG_NR_FAMES
#define JUMP_WAIT_NR_FRAMES JUMP_DOWN_NR_FAMES + 25

Player p1;
u8 frame_count;
s16 scroll_bg_b_offset;
Sprite* p1_sprite;
