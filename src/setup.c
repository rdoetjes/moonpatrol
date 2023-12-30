#include "setup.h"
#include "globals.h"
#include "backgrounds.h"
#include "player.h"
/*
Sets up the game's game_bg_b, sprites, player and other required initializations.
*/
void setup(Player* p1){
    setup_player(p1, 3);   // setup player 1 with 3 lives (currently we only have a player 1)

    show_game_bg_b();
    scroll_bg_b_offset = 0;

    JOY_init();
}
