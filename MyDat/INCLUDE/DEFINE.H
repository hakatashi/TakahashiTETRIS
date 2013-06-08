#define SCREEN_X 220

#define SCREEN_Y -160

#define BOARD_X_MAX 10

#define BOARD_Y_MAX 30

#define PLAYER_MAX 4

#define BLOCK_MAX 100

#define BLOCK_KIND_MAX 100

#define PI 3.1415926535897932384626433832795f

#define B_INFO_MAX 5

#define BLOCK_SIZE 20

#define NEXT_MAX 10

#define SE_MAX 50

#define BGM_MAX 10

#define PAD_MAX 16

#define EFFECT_MAX 100
#define EFFECT_SET_MAX 5

#define EFFECT_DISLINE 0 //0-9
#define EFFECT_ALLCLEAR 10
#define EFFECT_COMBO 11
#define EFFECT_SPLIT 12
#define EFFECT_LINE_NOTICE 13

#define PAD_NUM_RIGHT 0
#define PAD_NUM_LEFT 1
#define PAD_NUM_DOWN 2
#define PAD_NUM_UP 3
#define PAD_NUM_HOLD 4
#define PAD_NUM_TURN_L 5
#define PAD_NUM_TURN_R 6
#define PAD_NUM_KEY1 7
#define PAD_NUM_KEY2 8
#define PAD_NUM_KEY3 9
#define PAD_NUM_PAUSE 10

#define PUSH_DOWN CheckStatePad(-1,PAD_NUM_DOWN)==1
#define PUSH_LEFT CheckStatePad(-1,PAD_NUM_LEFT)==1
#define PUSH_RIGHT CheckStatePad(-1,PAD_NUM_RIGHT)==1
#define PUSH_UP CheckStatePad(-1,PAD_NUM_UP)==1
#define PUSH_HOLD CheckStatePad(-1,PAD_NUM_HOLD)==1
#define PUSH_TURN_R CheckStatePad(-1,PAD_NUM_TURN_R)==1
#define PUSH_TURN_L CheckStatePad(-1,PAD_NUM_TURN_L)==1
#define PUSH_PAUSE CheckStatePad(-1,PAD_NUM_PAUSE)==1

#include "struct.h"
