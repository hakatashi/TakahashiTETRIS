#include "define.h"

//graph.cpp
	//描画メイン
	GLOBAL void graph_main();

//key.cpp
	//現在のキー入力処理を行う
	GLOBAL int GetHitKeyStateAll_2();
	//受け取ったキー番号の現在の入力状態を返す
	GLOBAL int CheckStateKey(unsigned char Handle);

//laod.cpp
	//データのロード
	GLOBAL void load();

	GLOBAL void load_graph();

//ini.cpp
		GLOBAL void first_ini();

		GLOBAL void menu_ini();

		GLOBAL void launch_ini();

		GLOBAL void block_main();

		GLOBAL void turn_cal(int kind,int angle,block_point *n_block);

		GLOBAL double cent_point_cal_x( int kind , int angle );

		GLOBAL double cent_point_cal_y( int kind , int angle );

		GLOBAL double duv_2(double n , double k);

		GLOBAL void cal_score();

		GLOBAL void add_next(int Pl_n,int num);

		GLOBAL void control_menu();

		GLOBAL void result_ini();

		GLOBAL void control_over_select();

		GLOBAL void control_result();

		GLOBAL void graph_menu();

		GLOBAL void control_game_pause();

		GLOBAL void control_main();

		GLOBAL void music_ini();

		GLOBAL void music_play();
		
		GLOBAL void cpu_cal_num(int Pl_n,int n_kind,int n_hold,int *return_angle,int *return_position);
		GLOBAL void cpu_cal_num_weak(int Pl_n,int n_kind,int n_hold,int *return_angle,int *return_position,int priority);
		GLOBAL void cpu_cal_num_old1(int n_kind,int n_hold,int *return_angle,int *return_position);
		GLOBAL void cpu_cal_num_old2(int n_kind,int n_hold,int *return_angle,int *return_position);
		GLOBAL void cpu_cal_num_old3(int n_kind,int n_hold,int *return_angle,int *return_position);
		GLOBAL void cpu_cal_num_old4(int n_kind,int n_hold,int *return_angle,int *return_position);

		GLOBAL int char_to_num(char ch);

		GLOBAL void graph_back(int Pl_n);

		GLOBAL void graph_string(int Pl_n,int x,int y,int kind,char *string);

		GLOBAL int get_graph_string_width(int kind,char *string);

		GLOBAL void graph_string_slim(int Pl_n,int x,int y,int kind,int slim,char *string);

		GLOBAL void graph_string_slim_menu(int x,int y,int kind,int slim,char *string);

		GLOBAL int get_graph_string_slim_width(int kind,int slim,char *string);

		GLOBAL void graph_char(int Pl_n,int x,int y,int kind,char chara);

		GLOBAL int get_graph_char_width(int kind);

		GLOBAL void graph_char_ex(int Pl_n,int x1,int y1,int x2,int y2,int kind,char chara);

		GLOBAL double duv_2_p( double start, double aim, int nowtime, int alltime);
		
		GLOBAL void GetHitPadStateAll();

		GLOBAL void GetHitPadStateDefault();

		GLOBAL int CheckStatePad(int Pl,unsigned int Handle);

		GLOBAL void graph_logo();

		GLOBAL void graph_menun();

		GLOBAL void control_func_state();