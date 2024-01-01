#include "player.h"
#include "globals.h"
#include "resources.h"

static void load_sprite(Player* player){
    p1_sprite = SPR_addSprite(&player_sprite, player->x, player->y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
    PAL_setPalette(PAL2, player_sprite.palette->data, DMA);
}

/*
sets up the player pointed to by *player
The number of lives is externally configurable, as that might depend on hard or easy game.
The rest of the Player struct is set with fixed values that work for the game.
*/
void setup_player(Player *player, const u8 lives){
    player->lives = lives;    
    player->x = 90;
    player->y = 180;
    player->jump_state = GROUND;
    player->jumpFrame = 0;
    player->score = 0;

    load_sprite(player);
    SPR_setAnim(p1_sprite, 0);
}

void move_player(Player *player){
    SPR_setPosition(p1_sprite, player->x, player->y);
}