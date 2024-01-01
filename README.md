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
```c
extern const Image game_bg_b;
```

After we have the image on the ROM and defined it we can set it up for scrolling:
```C
    PAL_setPalette(PAL0, game_bg_b.palette->data, DMA);
    idx = game_bg_b.tileset->numTile;
    VDP_drawImageEx(BG_B, &game_bg_b, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, idx), 0, -3, FALSE, TRUE);
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
```

And then we can actually move it on both the Y and X axis. In our tutorial we only scroll to the left so we subtract from the current position.
```C
    16 i = 0;
    u16 frame_count;
    while(1)
    {
        i--;
        VDP_setHorizontalScroll(BG_B, i);
        SYS_doVBlankProcess();
    }    
```

## Tutorial 2
Splitting up your code in files makes it easier to maintain. Especially when you use global variables to allow for faster function calls as the whole stack frame doesn't need to be setup.

* logic.c will manage all the game logic

## Tutorial 3
In this totorial we will import a player sprite sheet with different animations.
We will change the animations depending on frame count, to have a more control over the whole animation.
Then after the sprite is visible we will move it left and right using the joystick as well as implement the jump wich will play the different animations.

### Player sprite sheet
We created a sprite sheet for the player one. We used Asprite to create the frames of the different animations. Those frames were tagged, so that when we exported the Sprite Sheet, we could seperate the frames based on tags.

A fully exported sprite sheet looks like this:

![Player Sprite sheet](https://github.com/rdoetjes/moonpatrol/blob/main/res/car_step1_animated.png)
![Player is jumping](https://github.com/rdoetjes/moonpatrol/blob/main/docs_images/jump.png)

SGDK will parse the different frames and stores them in the ROM. In order for SGDK to be able to do that, we need to tell it out of how many tiles this sprite is made up.

### Reading the joy stick
Currently we read the joystick in the logic.c as the first step. Later on, if it is desired, we can break it out into it's own dedicated file.

```C
static u16 process_joy(){
    u16 input = JOY_readJoypad(JOY_1);
    
    //move player left
    if(input & BUTTON_LEFT && p1.x > LEFT_BOUNDERY_PLAYER) {
        p1.x-=2;              
    }
    //move player right
    if(input & BUTTON_RIGHT && p1.x < RIGHT_BOUNDERY_PLAYER) {
        p1.x+=2;        
    }
    //move player make the player jump when he's not already jumping
    if (input & BUTTON_B && p1.jump_state == GROUND) {
        p1.jump_state = UP;                
    }    

    return input;
}
```

When the button left is pressed we subtract two pixel postions from the player's x position. When the button to the right is pressed we add 2 pixels to the x position of the player. 

The player sprite location is updated as follows:
```C
void move_player(Player *player){
    SPR_setPosition(p1_sprite, player->x, player->y);
}
```

### Managing the jump state
As you can see we have 4 states in our sprite sheet, they are all related to the jump. We have the animations for:
* the car hovering on the ground (GROUND state)
* the impulse pushing the car up (UP state)
* the car hanging in the air (HANG state)
* the car falling back downn to the ground (DOWN state)
* the wait state, we allow 25 frames before the next jump will/can be triggered (WAIT state)

We manage these states in our logic.c

```C
static void jump_animation_handling(void){
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
```

The p1.jumpFrame is a frame counter that we use to determine the transition from one jump state to the next.
These frame durations are configured in the globals.h, this allows us to tweak the duration of a jump and the indivual states of the jump.

The animation for each state is set using the SPR_setAnim() function.

### Processing the state
We do prefer not to check all the if statemens in jump_animation_handling() when the player isn't actually jumping. So we check if the state, that is set by proces_joy(), is not equal to GROUND, only then we will go through the jump logic. This safes cycles.

```c
void logic(){
    process_joy();
    
    //only process jump animation when we are not on the ground
    if (p1.jump_state != GROUND){
        jump_animation_handling();
    }   

    // move the player based on the p1 structure
    move_player(&p1);
    
...  
}
```

Eventually the sprites are rendered to the screen in the draw() function using the SPR_update()

```C
    SPR_update();
```