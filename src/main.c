#include <genesis.h>
#include <resources.h>

u16 idx = TILE_USER_INDEX;

int main()
{   
    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, -3, FALSE, TRUE);
    idx += background.tileset->numTile;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    s16 i = 0;
    u16 frame_count;
    while(1)
    {
        frame_count++; 
        if (frame_count % 4 == 0) {
            i--;
        }
        VDP_setHorizontalScroll(BG_B, i);
        SYS_doVBlankProcess();
    }
    return (0);
} 
