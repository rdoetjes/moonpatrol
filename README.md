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

## Tutorial 2
Splitting up your code in files makes it easier to maintain. Especially when you use global variables to allow for faster function calls as the whole stack frame doesn't need to be setup.


## Tutorial 3
We created a sprite sheet for the player one. We used Asprite to create the frames of the different animations. Those frames were tagged, so that when we exported the Sprite Sheet, we could seperate the frames based on tags.

A fully exported sprite sheet looks like this:

![Player Sprite sheet](https://github.com/rdoetjes/moonpatrol/blob/main/res/car_step1_animated.png)

SGDK will parse the different frames and stores them in the ROM. In order for SGDK to be able to do that, we need to tell it out of how many tiles this sprite is made up.

<pre>
SPRITE player_sprite "car_step1_animated.png" 8 4 FAST 5
</pre>
In this case the meta sprite is 8 tiles wide and 4 tiles tall. We will change the frames every 5*(1/60)

### Managing the jump state
As you can see we have 4 states in our sprite sheet, they are all related to the jump. We have the animations for:
* the car hovering on the ground (GROUND state)
* the impulse pushing the car up (UP state)
* the car hanging in the air (HANG state)
* the car falling back downn to the ground (DOWN state)

We manage these states in our logic.c

```C
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
```