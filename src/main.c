#include <genesis.h>
#include <resources.h>

u16 idx = TILE_USER_INDEX;

int main(){
    PAL_setPalette(PAL0, game_bg_b.palette->data, DMA);
    idx = game_bg_b.tileset->numTile;
    VDP_drawImageEx(BG_B, &game_bg_b, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, 0, FALSE, TRUE);

    s16 i = 0;
    u16 frame_count = 0;
    while(1){        
        frame_count++;
        if ( (frame_count & 3) == 3){
            i--;
        }
        VDP_setHorizontalScroll(BG_B, i);
        SYS_doVBlankProcess();
    }
    return 0;
}