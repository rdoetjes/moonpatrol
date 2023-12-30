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
static void draw(){
    char lives[12];
    VDP_setHorizontalScroll(BG_B, scroll_bg_b_offset);
    sprintf(lives, "LIVES: %d", p1.lives);
    VDP_drawText(lives, CHAR_WIDTH-strlen(lives)-2, 1); // draw text 2 chars from the end of the screen
}

/*
MAIN entry point of game
*/
int main()
{   
    while(1)
    {
        setup(&p1);
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
        show_gameover_bg_b();
        SYS_doVBlankProcess();
        JOY_waitPress(JOY_1, BUTTON_START);
    }
    return (0);
} 
