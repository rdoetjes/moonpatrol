#include "main.h"
#include <resources.h>
#include <string.h>

static s16 scroll_bg_b_offset;
static Player p1;
static u8 frame_count;

/*
Sets up the game's background, sprites, player and other required initializations.
*/
static void setup(void){
    bg_b();
    setup_player(&p1, 3);
    scroll_bg_b_offset = 0;
    JOY_init();
}

/*
Draw everything
*/
static void draw(){
    char lives[12];
    VDP_setHorizontalScroll(BG_B, scroll_bg_b_offset);
    sprintf(lives, "LIVES: %d", p1.lives);
    VDP_drawText(lives, CHAR_WIDTH-strlen(lives)-2, 1); // draw text 2 chars from the end of the screen
}

/*
Process game logic
*/
static void logic(){
    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }
    if (frame_count == 0) p1.lives--;
}

/*
sets up the player pointed to by *player
The number of lives is externally configurable, as that might depend on hard or easy game.
The rest of the Player struct is set with fixed values that work for the game.
*/
static void setup_player(Player *player, const u8 lives){
    player->lives = lives;
    player->y = 220;
    player->x = 110;
    player->isJumping = FALSE;
}

/*
Read the background BG_B (which is a static image and not a tileset)
and sets up the scrolling mode for it.
*/
static void bg_b(void){
    u16 idx = TILE_USER_INDEX;
    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, -3, FALSE, TRUE);
    idx += background.tileset->numTile;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
}

static void gameover_screen(void){
    //hide the lives: x text by writing spaces, as that's still in the buffer.
    char lives[12];
    sprintf(lives, "            ");
    VDP_drawText(lives, CHAR_WIDTH-strlen(lives)-2, 1); // draw text 2 chars from the end of the screen

    //load and display the gameover screen, this is a BG_B image
    u16 idx = TILE_USER_INDEX;
    VDP_setHorizontalScroll(BG_B, 0);
    PAL_setPalette(PAL0, gameover_bg.palette->data, DMA);
    VDP_drawImageEx(BG_B, &gameover_bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, 0, FALSE, TRUE);
    idx += gameover_bg.tileset->numTile;
}

/*
MAIN entry point of game
*/
int main()
{   
    while(1)
    {
        setup();
        //standard game loop when game is playing and player is still alive
        while(p1.lives > 0){
            //run game logic
            logic();
            //draw all contents to screen
            draw();
            //wait for vertical blank
            SYS_doVBlankProcess();
        } 

        // when player dies we show game over screen and wait for start button.
        gameover_screen();
        SYS_doVBlankProcess();
        JOY_waitPress(JOY_1, BUTTON_START);
    }
    return (0);
}