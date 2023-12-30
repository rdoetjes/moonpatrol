#include "setup.h"
#include "backgrounds.h"
#include "player.h"
/*
Sets up the game's game_bg_b, sprites, player and other required initializations.
*/
void setup(Player* p1){
    show_game_bg_b();
    setup_player(p1, 3);
    scroll_bg_b_offset = 0;
    JOY_init();
}
