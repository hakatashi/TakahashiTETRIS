#include "../../include/DxLib.h"
//#include "define.h"

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

#include "function.h"


//画像用変数宣言部
GLOBAL int img_bl[19];

GLOBAL int img_ghost[19];

GLOBAL int img_sheet[8];

GLOBAL int img_game;

GLOBAL int img_over;

GLOBAL int img_result;

GLOBAL int img_pause;

GLOBAL int img_num[2][11];

GLOBAL int img_over_select[2][6];

GLOBAL int img_menu_select[2][7];

GLOBAL int img_menu_choice[10][7];

GLOBAL int img_char[5][2][78];

GLOBAL int img_back[5][10];

GLOBAL int img_back_s[5][10][2];

GLOBAL int img_part[10][100];

GLOBAL int img_selection[10][20][20];

GLOBAL int img_window[10];

GLOBAL int img_effect[20][20];

GLOBAL int img_menu[5][10];

GLOBAL int Pl_num;
//ボードの状態
GLOBAL int board[BOARD_X_MAX][BOARD_Y_MAX];
//ボードのブロックの向き
GLOBAL int board_angle[BOARD_X_MAX][BOARD_Y_MAX];
//ブロックの種類の数
GLOBAL int block_kinds;
//ゴーストを何マス下に表示させるかを表す数
GLOBAL int ghost_down;
//ブロックが消えたときにブロックをどれくらい浮かせるかなどを記録する構造体
GLOBAL block_fall_t block_fall[BOARD_X_MAX][BOARD_Y_MAX];
//メインの制御変数
GLOBAL int func_state;
//プログラムを実行してる間ずっと回り続けるカウンター。
GLOBAL int exe_cnt;

GLOBAL int stage_cnt;

GLOBAL block_t block[BLOCK_KIND_MAX];

GLOBAL b_info_t b_info[B_INFO_MAX];

GLOBAL configpad_t configpad[PLAYER_MAX+3];

GLOBAL double app_list[100][BLOCK_KIND_MAX];

GLOBAL int mode;

GLOBAL int pause_flag;

GLOBAL int pause_cnt;

GLOBAL int dis_line_n[BOARD_Y_MAX];
	
GLOBAL int next[NEXT_MAX];

GLOBAL int line;

GLOBAL int score;

GLOBAL double n_score;

GLOBAL int dis_line_times[10];

GLOBAL int dis_line_AC_times[10];

GLOBAL int split_times[10];

GLOBAL int combo_times[20][10];

GLOBAL int combo_times_ini[10];

GLOBAL double dropline;

GLOBAL double harddropline;

GLOBAL int hold;

GLOBAL int combo;

GLOBAL int holdflag;

GLOBAL int hold_cnt;

GLOBAL int starttime_cnt;

GLOBAL int playtime_cnt;

GLOBAL double result_x;

GLOBAL double gameover_x;

GLOBAL double result_score_y[20];

GLOBAL double over_select_y[4];

GLOBAL int over_select;

GLOBAL int result_cnt;

GLOBAL int temp[10];

GLOBAL double d_temp[10];

//これまでに落としたブロックの数を記録する変数
GLOBAL int block_num;

GLOBAL int menu_selected_cnt;

GLOBAL double pause_button_y[4];

GLOBAL int pause_select;

GLOBAL double pause_blend;

GLOBAL int se_flag[SE_MAX];

GLOBAL int se_handle[SE_MAX];

GLOBAL int bgm_num;

GLOBAL int bgm_handle[BGM_MAX];

GLOBAL int bgm_state;

GLOBAL int cpu_flag;
GLOBAL cpu_mode_t cpu_mode;
GLOBAL int cpu_state;
GLOBAL int cpu_state_cnt;
GLOBAL int cpu_aim_angle;
GLOBAL int cpu_aim_position;

GLOBAL int effect_flag[EFFECT_MAX][EFFECT_SET_MAX];

GLOBAL double effect_state[EFFECT_MAX][EFFECT_SET_MAX][20];

GLOBAL Pl_t Pl[PLAYER_MAX];

GLOBAL int gameover_flag;

GLOBAL int pause_push_Pl;

GLOBAL int PadPushPlayer;

GLOBAL int menu_state[10];

GLOBAL int menu_select;

GLOBAL int gameflag;

GLOBAL int all_cpu_flag;

//パッドの入力状態を格納する変数
GLOBAL pad_t pad[PLAYER_MAX+1];

//0:操作中 1:入力待ち
GLOBAL int key_config_state;
GLOBAL configpad_t configpad_ini[PLAYER_MAX+3];
GLOBAL int now_config_pad[2];

GLOBAL double StageSpeed;

GLOBAL double SpeedupEffectFlag;
GLOBAL double SpeedupEffectState[2];

GLOBAL int manuctrl[4];
GLOBAL int menuslct;