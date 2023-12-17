#include "main.h"
#include <resources.h>
#include <string.h>

static s16 scroll_bg_b_offset = 0;
static Player p1;
static u8 frame_count;

/*
Sets up the game's background, sprites, player and other required initializations.
*/
void setup(void){
    bg_b();
    setup_player(&p1, 3);
}

/*
Draw everything
*/
void draw(){
    char lives[12];
    VDP_setHorizontalScroll(BG_B, scroll_bg_b_offset);
    sprintf(lives, "LIVES: %d", p1.lives);
    VDP_drawText(lives, 40-strlen(lives)-2, 1);
}

/*
Process game logic
*/
void logic(){
    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }
}

/*
sets up the player pointed to by *player
The number of lives is externally configurable, as that might depend on hard or easy game.
The rest of the Player struct is set with fixed values that work for the game.
*/
void setup_player(Player *player, const int lives){
    player->lives = lives;
    player->y = 220;
    player->x = 110;
    player->isJumping = FALSE;
}

/*
Read the background BG_B (which is a static image and not a tileset)
and sets up the scrolling mode for it.
*/
void bg_b(void){
    u16 idx = TILE_USER_INDEX;
    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, -3, FALSE, TRUE);
    idx += background.tileset->numTile;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

/*
MAIN entry point of game
*/
int main()
{   
    setup();
    while(1)
    {
        logic();
        draw();
        SYS_doVBlankProcess();
    }
    return (0);
}