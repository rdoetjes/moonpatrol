#include "logic.h"
#include "globals.h"
/*
Process game logic
*/
void logic(){
    frame_count++; 
    if ( (frame_count & 3) == 0) {
        scroll_bg_b_offset--;
    }
    if (frame_count == 0) p1.lives--;
}
