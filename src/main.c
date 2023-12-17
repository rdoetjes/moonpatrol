#include "main.h"
#include <resources.h>
#include <string.h>

static s16 scroll_bg_b_offset = 0;
static Player p1;
static u8 frame_count;

void setup(void){
    bg_b();
    setup_player(&p1, 3);
}

void setup_player(Player *player, const int lives){
    player->lives = lives;
    player->y = 220;
    player->x = 110;
    player->isJumping = FALSE;
}

void bg_b(void){
    u16 idx = TILE_USER_INDEX;
    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, -3, FALSE, TRUE);
    idx += background.tileset->numTile;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

void draw(){
    char lives[12];
    VDP_setHorizontalScroll(BG_B, scroll_bg_b_offset);
    sprintf(lives, "LIVES: %d", p1.lives);
    VDP_drawText(lives, 40-strlen(lives)-2, 1);
}

void logic(){
    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }
}

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