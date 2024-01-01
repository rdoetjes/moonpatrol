#pragma once
#include <genesis.h>
#include "player.h"

#define CHAR_WIDTH 40
//hugs the left of the screen but with a bit of room to spare
#define LEFT_BOUNDERY_PLAYER 5
//320 is size of width 64 is the number of pixels in x position player sprite
#define RIGHT_BOUNDERY_PLAYER 320-64


Player p1;
u8 frame_count;
s16 scroll_bg_b_offset;
Sprite* p1_sprite;
