typedef struct{
	int x;
	int y;
}block_point;

typedef struct{
	double app;
	int n;
	int col;
	int x;
	int y;
	int surface;
	int type;
	block_point p[BLOCK_MAX];
}block_t;

typedef struct{
	int flag;
	double gx,gy;
	double x,y;
	int delay_y;
	double n_delay_y;
	double v;
	int kind;
	int angle;
	int b_angle;
	double b_cent_x;
	double b_cent_y;
	double angle_rate;
	int state;
	int wait;
	int cnt;
	int touchflag;
}b_info_t;

typedef struct{
	double v;
	double plus_y;
}block_fall_t;

typedef struct{
	int difficalty;
	int hold;
	int pattern;
}cpu_mode_t;

//パッドに関する構造体
typedef struct{
	int key[PAD_MAX];
}pad_t;

//コンフィグに関する構造体
typedef struct{
	int left;
	int up;
	int right;
	int down;
	int hold;
	int turn_L;
	int turn_R;
	int key1;
	int key2;
	int key3;
	int pause;
}configpad_t;

typedef struct{
	int screen_x;
	int screen_y;
	int screen_x_d;
	int screen_y_d;
	int screen_x_de;
	int screen_y_de;
	int board[BOARD_X_MAX][BOARD_Y_MAX];
	int board_angle[BOARD_X_MAX][BOARD_Y_MAX];
	int ghost_down;
	block_fall_t block_fall[BOARD_X_MAX][BOARD_Y_MAX];
	b_info_t block;
	int dis_line_n[BOARD_Y_MAX];
	int next[NEXT_MAX];
	int line;
	int score;
	double n_score;
	int dis_line_times[10];
	int dis_line_AC_times[10];
	int split_times[10];
	int combo_times[20][10];
	int combo_times_ini[10];
	double dropline;
	double harddropline;
	int hold;
	int combo;
	int holdflag;
	int hold_cnt;
	int starttime_cnt;
	int playtime_cnt;
	double result_x;
	double gameover_x;
	double result_score_y[20];
	double over_select_y[4];
	int over_select;
	int result_cnt;
	int block_num;
	int effect_flag[EFFECT_MAX][EFFECT_SET_MAX];
	double effect_state[EFFECT_MAX][EFFECT_SET_MAX][20];
	int cpu_flag;
	cpu_mode_t cpu_mode;
	int cpu_state;
	int cpu_state_cnt;
	int cpu_aim_angle;
	int cpu_aim_position;
	int pause_flag;
	int pause_cnt;
	int keyboard_num;
	int pad_num;
} Pl_t;

typedef struct {
	double x,y,z;
	double dx,dy,v;
	double bright;
	int t;
	int col;
	int flag;
} bullet_t;