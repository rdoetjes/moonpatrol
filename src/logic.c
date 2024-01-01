#include "logic.h"
#include "globals.h"

u16 process_joy(){
    u16 input = JOY_readJoypad(JOY_1);

    if(input & BUTTON_LEFT && p1.x > LEFT_BOUNDERY_PLAYER){
        p1.x-=2;              
    }

    if(input & BUTTON_RIGHT && p1.x < RIGHT_BOUNDERY_PLAYER) {
        p1.x+=2;        
    }

    return input;
}

/*
Process game logic
*/
void logic(){
    process_joy();

    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }
    if (frame_count == 0) p1.lives--;
}
