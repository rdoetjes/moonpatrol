#include "backgrounds.h"
#include "resources.h"
#include "globals.h"

/*
load_vdp is a convenience wrapper that avoids expensive code duplication but is inlined for speed (rather a bigger rom than losing cycles)
Now we call a single function to load a vdp image and set the palette, instead
of doing those lines for every screen we want to load.
*/
inline static void load_vdp(u16 numPal, const u16* pal, int x, int y, VDPPlane plane, const Image *image){
    u16 idx = TILE_USER_INDEX;
    VDP_drawImageEx(plane, image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), x, y, FALSE, TRUE);
    idx += image->tileset->numTile;
    PAL_setPalette(numPal, image->palette->data, DMA);
}

/*
Read the game_bg_b BG_B (which is a static image and not a tileset)
and sets up the scrolling mode for it.
*/
void show_game_bg_b(void){
    load_vdp(PAL0, game_bg_b.palette->data, 0, 0, BG_B, &game_bg_b);
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

/*
Loads the game over screen and displayts it on BG_B plane
*/
void show_gameover_bg_b(void){
    //hide the lives: x text by writing spaces, as that's still in the buffer.
    char lives[12];
    sprintf(lives, "            ");
    VDP_drawText(lives, CHAR_WIDTH-strlen(lives)-2, 1); // draw text 2 chars from the end of the screen

    //load and display the gameover screen, this is a BG_B image
    VDP_setHorizontalScroll(BG_B, 0);   //be sure to set scroll to 0 because then we update the whole screen
    load_vdp(PAL0, gameover_bg_b.palette->data, 0, 0, BG_B, &gameover_bg_b);
}

/*
Show sega splash screen
*/
void show_sega_bg_b(void){
    JOY_init();
    u16 palette_full[64];
    memcpy(&palette_full[0] , sega_bg_b.palette->data, 16 * 2);

    PAL_setPalette(PAL0, palette_black, DMA);	
    PAL_fadeIn(0, 63, palette_full, 10, FALSE);
    load_vdp(PAL0, sega_bg_b.palette->data, 0, 0, BG_B, &sega_bg_b);
    JOY_waitPress(JOY_1, BUTTON_START);
    PAL_fadeOut(0, 63, 60, FALSE);
    PAL_setPalette(PAL0, palette_black, DMA);	
}