# MOONPATROL SGDK
This is a light weight interpretation of the infamous game MoonPatrol. It is used in this case as a teaching aid since the game mechanics are relatively simple and cover most features of the SGDK (Sega Development kit).
<p>
Each lesson/tutorial is in it's own branch so please check the branches of this repository. The end product is merged into main branch.

## Tutorial 1
We will be drawing a background and letting that scroll. In order to draw a background you will need a pixel art tool, anyone will do but you need to have a palette for the Genesis. We are using Asprite, it cheap easy and does the trick and you can load the plaette named "Sega Genesis new.pal" from this repository in the root, and you will have the 512 colors that the Genesis/MegaDrive supports.

It's important to know that a Genesis can only handle 16 different color for each background and sprite(s). With palette swapping more colors can be shown on the screen though but that's beyond the basics of this lesson.

A background image when shown in "high res" needs to be 512x256 in order to allow for seamless scrolling.
![The 512x256 nackground image](https://github.com/rdoetjes/moonpatrol/blob/main/res/bg_1_v2.png)

The image is defined in the res/resources.res file, this allows the compiler and the toolchain to cut th epng into tiles and pack them and put them on the ROM image.

Then we can reference it C by adding a line to the resources.h file that is similar to this:
<pre>
extern const Image game_bg_b;
</pre>

After we have the image on the ROM and defined it we can set it up for scrolling:
<pre>
    PAL_setPalette(PAL0, game_bg_b.palette->data, DMA);
    VDP_drawImageEx(BG_B, &game_bg_b, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, -3, FALSE, TRUE);
    idx += game_bg_b.tileset->numTile;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
</pre>
And then we can actually move it on both the Y and X axis. In our tutorial we only scroll to the left so we subtract from the current position.
<pre>
    16 i = 0;
    u16 frame_count;
    while(1)
    {
        i--;
        VDP_setHorizontalScroll(BG_B, i);
        SYS_doVBlankProcess();
    }    
</pre>