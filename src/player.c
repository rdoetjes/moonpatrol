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

void player_jump_state_handling(void){
    //tracks the amount of frame we are in the air
    //animation state is coupled to this.
    if (p1.jump_state!=GROUND){
        p1.jumpFrame++;
    }

    // player is jumping move sprite up and set the animation to UP state
    if (p1.jump_state == UP){
        SPR_setAnim(p1_sprite, UP);
        p1.y--;
    }

    //transistion from jump up to hang air animation
    if (p1.jump_state == UP && p1.jumpFrame > JUMP_UP_NR_FAMES){        
        p1.jump_state = HANG;
        SPR_setAnim(p1_sprite, HANG);        
    }

    //transistion from hang air to going down animation
    if (p1.jump_state == HANG && p1.jumpFrame > JUMP_HANG_NR_FAMES){
        p1.jump_state = DOWN;                
    }

    if (p1.jump_state == DOWN){
        SPR_setAnim(p1_sprite, DOWN);        
        p1.y++;
    }

    //transition from down to ground animation
    if (p1.jump_state == DOWN && p1.jumpFrame > JUMP_DOWN_NR_FAMES){
        p1.jump_state = WAIT;      
        SPR_setAnim(p1_sprite, GROUND);        
    }

    //wait 50 frames before next posisble jump
    if (p1.jump_state == WAIT && p1.jumpFrame >= JUMP_WAIT_NR_FRAMES){
        p1.jump_state = GROUND;
        p1.jumpFrame = 0;  
    }
}