#include "logic.h"
#include "globals.h"

static void jump_animation_handling(void){
    //tracks the amount of frame we are in the air
    //animation state is coupled to this.
    if (p1.jump_state!=GROUND){
        p1.jumpFrame++;
    }

    if (p1.jump_state == UP){
        p1.y--;
    }

    //transistion from jump up to hang air animation
    if (p1.jump_state == UP && p1.jumpFrame > 10){        
        p1.jump_state = HANG;
        SPR_setAnim(p1_sprite, 2);        
    }

    //transistion from hang air to going down animation
    if (p1.jump_state == HANG && p1.jumpFrame > 40){
        p1.jump_state = DOWN;                
        SPR_setAnim(p1_sprite, 3);        
    }

    if (p1.jump_state == DOWN){
        p1.y++;
    }

    //transition from down to ground animation
    if (p1.jump_state == DOWN && p1.jumpFrame > 50){
        p1.jump_state = WAIT;      
        SPR_setAnim(p1_sprite, 0);        
    }

    //wait 50 frames before next posisble jump
    if (p1.jump_state == WAIT && p1.jumpFrame >= 75){
        p1.jump_state = GROUND;
        p1.jumpFrame = 0;  
    }
}

static u16 process_joy(){
    u16 input = JOY_readJoypad(JOY_1);

    if(input & BUTTON_LEFT && p1.x > LEFT_BOUNDERY_PLAYER){
        p1.x-=2;              
    }

    if(input & BUTTON_RIGHT && p1.x < RIGHT_BOUNDERY_PLAYER) {
        p1.x+=2;        
    }

    if (input & BUTTON_B && p1.jump_state == GROUND){
        SPR_setAnim(p1_sprite, 1);
        p1.jump_state = UP;                
    }    

    return input;
}

/*
Process game logic
*/
void logic(){
    process_joy();
    
    if (p1.jump_state != GROUND){
        jump_animation_handling();
    }   

    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }    
}
