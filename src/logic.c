#include "logic.h"
#include "globals.h"

static u16 process_joy(){
    u16 input = JOY_readJoypad(JOY_1);
    
    //move player left
    if(input & BUTTON_LEFT && p1.x > LEFT_BOUNDERY_PLAYER){
        p1.x-=2;              
    }
    //move player right
    if(input & BUTTON_RIGHT && p1.x < RIGHT_BOUNDERY_PLAYER) {
        p1.x+=2;        
    }
    //move player make the player jump when he's not already jumping
    if (input & BUTTON_B && p1.jump_state == GROUND){
        p1.jump_state = UP;                
    }    

    return input;
}

/*
Process game logic
*/
void logic(){
     process_joy();
    
    //only process jump animation when we are not on the ground
    if (p1.jump_state != GROUND){
        player_jump_state_handling();
    }   

    // move the player based on the p1 structure
    move_player(&p1);
    
    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }  
}
