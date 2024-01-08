#include "main.h"
#include "setup.h"
#include "globals.h"
#include "player.h"
#include "backgrounds.h"
#include "logic.h"

#include <resources.h>
#include <string.h>

/*
Draw everything
*/
static void draw(void){
    char lives[12];
    VDP_setHorizontalScroll(BG_B, scroll_bg_b_offset);
    sprintf(lives, "LIVES: %d", p1.lives);
    VDP_drawText(lives, CHAR_WIDTH-strlen(lives)-2, 1); // draw text 2 chars from the end of the screen

    SPR_update();
}

/*
Remove all the sprites from the screen
Show gameover screen and wait for start button to restart the game
*/
static void gameover(void){
   // when player dies we show game over screen and wait for start button.
    SPR_clear();
    show_gameover_bg_b();
    SYS_doVBlankProcess();
    JOY_waitPress(JOY_1, BUTTON_START);
    PAL_setPalette(PAL0, palette_black, DMA);
}

/*
MAIN entry point of game
*/
int main()
{   
    show_sega_bg_b();
    while(1)
    {
        setup(&p1);
        //standard game loop when game is playing and player is still alive
        while(p1.lives > 0){
            //run game logic
            logic();
            //draw all contents to screen
            draw();
            // do all the processing.
            SYS_doVBlankProcessEx(ON_VBLANK_START);
        } 
        // game over screen and wait for start button
        gameover();
    }
    return (0);
} 
