#include <genesis.h>

typedef struct Player{
    u8 lives;
    u16 x;
    u16 y;
    bool isJumping;
} Player;

void setup(void);
void bg_b(void);
void draw(void);
void logic(void);
void setup_player(Player *player, const int lives);