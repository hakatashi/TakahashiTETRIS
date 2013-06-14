#include "../include/GV.h"

void ini_board() {
	int i,j,k;
	for (k=0;k<PLAYER_MAX;k++) {
		for (j=0;j<BOARD_Y_MAX;j++) {
			temp[0]=GetRand(9);
			for (i=0;i<BOARD_X_MAX;i++) {
				//board[i][j]=(i+j)%7+1;
				/*if (j==29 && i!=4) Pl[k].board[i][j]=8;
				else if (j>=27 && i!=3 && i!=4 && i!=5) Pl[k].board[i][j]=8;
				else */Pl[k].board[i][j]=0;
				Pl[k].board_angle[i][j]=0;
				//if (j>15 && i!=temp[0]) board[i][j]=8;
				//if (j>26 && i!=4) board[i][j]=8;
			}
		}
	}
}

void launch_ini() {
	Pl_num=1;
	all_cpu_flag=0;
	gameflag=0;
	for (int i=0;i<PLAYER_MAX;i++) {
		configpad[i].down=0;
		configpad[i].left=1;
		configpad[i].right=2;
		configpad[i].up=3;
		configpad[i].turn_L=10;
		configpad[i].turn_R=11;
		configpad[i].hold=4;
		configpad[i].key1=7;
		configpad[i].key2=8;
		configpad[i].key3=9;
		configpad[i].pause=13;
		Pl[i].cpu_flag=0;
		Pl[i].cpu_mode.hold=1;
		Pl[i].cpu_mode.pattern=1;
		Pl[i].keyboard_num=0;
		Pl[i].pad_num=i;
	}
	configpad[PLAYER_MAX].left=KEY_INPUT_LEFT;
	configpad[PLAYER_MAX].up=KEY_INPUT_UP;
	configpad[PLAYER_MAX].right=KEY_INPUT_RIGHT;
	configpad[PLAYER_MAX].down=KEY_INPUT_DOWN;
	configpad[PLAYER_MAX].hold=KEY_INPUT_Z;
	configpad[PLAYER_MAX].turn_L=KEY_INPUT_X;
	configpad[PLAYER_MAX].turn_R=KEY_INPUT_C;
	configpad[PLAYER_MAX].key1=KEY_INPUT_A;
	configpad[PLAYER_MAX].key2=KEY_INPUT_S;
	configpad[PLAYER_MAX].key3=KEY_INPUT_D;
	configpad[PLAYER_MAX].pause=KEY_INPUT_LCONTROL;
	configpad[PLAYER_MAX+1].left=KEY_INPUT_F;
	configpad[PLAYER_MAX+1].up=KEY_INPUT_T;
	configpad[PLAYER_MAX+1].right=KEY_INPUT_H;
	configpad[PLAYER_MAX+1].down=KEY_INPUT_G;
	configpad[PLAYER_MAX+1].hold=KEY_INPUT_Z;
	configpad[PLAYER_MAX+1].turn_L=KEY_INPUT_X;
	configpad[PLAYER_MAX+1].turn_R=KEY_INPUT_C;
	configpad[PLAYER_MAX+1].key1=KEY_INPUT_A;
	configpad[PLAYER_MAX+1].key2=KEY_INPUT_S;
	configpad[PLAYER_MAX+1].key3=KEY_INPUT_D;
	configpad[PLAYER_MAX+1].pause=KEY_INPUT_LCONTROL;
	configpad[PLAYER_MAX+2].left=KEY_INPUT_NUMPAD4;
	configpad[PLAYER_MAX+2].up=KEY_INPUT_NUMPAD8;
	configpad[PLAYER_MAX+2].right=KEY_INPUT_NUMPAD6;
	configpad[PLAYER_MAX+2].down=KEY_INPUT_NUMPAD2;
	configpad[PLAYER_MAX+2].hold=KEY_INPUT_PERIOD;
	configpad[PLAYER_MAX+2].turn_L=KEY_INPUT_SLASH;
	configpad[PLAYER_MAX+2].turn_R=KEY_INPUT_BACKSLASH;
	configpad[PLAYER_MAX+2].key1=KEY_INPUT_L;
	configpad[PLAYER_MAX+2].key2=KEY_INPUT_SEMICOLON;
	configpad[PLAYER_MAX+2].key3=KEY_INPUT_COLON;
	configpad[PLAYER_MAX+2].pause=KEY_INPUT_RCONTROL;
	for (int i=0;i<10;i++) {
		menu_state[i]=-1;
	}
}

/*void ini_block() {
	block[0].n=4;
	block[0].x=4;
	block[0].y=1;
	block[0].col=0;
	block[0].app=4;
	block[0].p[0].x=0;
	block[0].p[0].y=0;
	block[0].p[1].x=1;
	block[0].p[1].y=0;
	block[0].p[2].x=2;
	block[0].p[2].y=0;
	block[0].p[3].x=3;
	block[0].p[3].y=0;
	
	block[1].n=4;
	block[1].x=2;
	block[1].y=2;
	block[1].col=1;
	block[1].app=3;
	block[1].p[0].x=0;
	block[1].p[0].y=0;
	block[1].p[1].x=1;
	block[1].p[1].y=0;
	block[1].p[2].x=0;
	block[1].p[2].y=1;
	block[1].p[3].x=1;
	block[1].p[3].y=1;
	
	block[2].n=4;
	block[2].x=3;
	block[2].y=2;
	block[2].col=2;
	block[2].app=3;
	block[2].p[0].x=0;
	block[2].p[0].y=1;
	block[2].p[1].x=1;
	block[2].p[1].y=1;
	block[2].p[2].x=1;
	block[2].p[2].y=0;
	block[2].p[3].x=2;
	block[2].p[3].y=0;
	
	block[3].n=4;
	block[3].x=3;
	block[3].y=2;
	block[3].col=3;
	block[3].app=3;
	block[3].p[0].x=0;
	block[3].p[0].y=0;
	block[3].p[1].x=1;
	block[3].p[1].y=0;
	block[3].p[2].x=1;
	block[3].p[2].y=1;
	block[3].p[3].x=2;
	block[3].p[3].y=1;
	
	block[4].n=4;
	block[4].x=3;
	block[4].y=2;
	block[4].col=4;
	block[4].app=3;
	block[4].p[0].x=0;
	block[4].p[0].y=0;
	block[4].p[1].x=1;
	block[4].p[1].y=0;
	block[4].p[2].x=2;
	block[4].p[2].y=0;
	block[4].p[3].x=2;
	block[4].p[3].y=1;
	
	block[5].n=4;
	block[5].x=3;
	block[5].y=2;
	block[5].col=5;
	block[5].app=3;
	block[5].p[0].x=0;
	block[5].p[0].y=0;
	block[5].p[1].x=1;
	block[5].p[1].y=0;
	block[5].p[2].x=2;
	block[5].p[2].y=0;
	block[5].p[3].x=0;
	block[5].p[3].y=1;
	
	block[6].n=4;
	block[6].x=3;
	block[6].y=2;
	block[6].col=6;
	block[6].app=4;
	block[6].p[0].x=0;
	block[6].p[0].y=0;
	block[6].p[1].x=1;
	block[6].p[1].y=0;
	block[6].p[2].x=2;
	block[6].p[2].y=0;
	block[6].p[3].x=1;
	block[6].p[3].y=1;
	
	block[7].n=9;
	block[7].x=5;
	block[7].y=4;
	block[7].col=7;
	block[7].app=1;
	block[7].p[0].x=2;
	block[7].p[0].y=0;
	block[7].p[1].x=2;
	block[7].p[1].y=1;
	block[7].p[2].x=3;
	block[7].p[2].y=1;
	block[7].p[3].x=2;
	block[7].p[3].y=2;
	block[7].p[4].x=0;
	block[7].p[4].y=3;
	block[7].p[5].x=1;
	block[7].p[5].y=3;
	block[7].p[6].x=2;
	block[7].p[6].y=3;
	block[7].p[7].x=3;
	block[7].p[7].y=3;
	block[7].p[8].x=4;
	block[7].p[8].y=3;
	
	block[8].n=39;
	block[8].x=7;
	block[8].y=9;
	block[8].col=7;
	block[8].app=0.3;
	block[8].p[0].x=0;
	block[8].p[0].y=0;
	block[8].p[1].x=1;
	block[8].p[1].y=0;
	block[8].p[2].x=2;
	block[8].p[2].y=0;
	block[8].p[3].x=3;
	block[8].p[3].y=0;
	block[8].p[4].x=4;
	block[8].p[4].y=0;
	block[8].p[5].x=5;
	block[8].p[5].y=0;
	block[8].p[6].x=6;
	block[8].p[6].y=0;
	block[8].p[7].x=0;
	block[8].p[7].y=1;
	block[8].p[8].x=4;
	block[8].p[8].y=1;
	block[8].p[9].x=0;
	block[8].p[9].y=2;
	block[8].p[10].x=2;
	block[8].p[10].y=2;
	block[8].p[11].x=3;
	block[8].p[11].y=2;
	block[8].p[12].x=4;
	block[8].p[12].y=2;
	block[8].p[13].x=5;
	block[8].p[13].y=2;
	block[8].p[14].x=6;
	block[8].p[14].y=2;
	block[8].p[15].x=0;
	block[8].p[15].y=3;
	block[8].p[16].x=2;
	block[8].p[16].y=3;
	block[8].p[17].x=6;
	block[8].p[17].y=3;
	block[8].p[18].x=0;
	block[8].p[18].y=4;
	block[8].p[19].x=2;
	block[8].p[19].y=4;
	block[8].p[20].x=3;
	block[8].p[20].y=4;
	block[8].p[21].x=4;
	block[8].p[21].y=4;
	block[8].p[22].x=5;
	block[8].p[22].y=4;
	block[8].p[23].x=6;
	block[8].p[23].y=4;
	block[8].p[24].x=0;
	block[8].p[24].y=5;
	block[8].p[25].x=2;
	block[8].p[25].y=5;
	block[8].p[26].x=6;
	block[8].p[26].y=5;
	block[8].p[27].x=0;
	block[8].p[27].y=6;
	block[8].p[28].x=2;
	block[8].p[28].y=6;
	block[8].p[29].x=3;
	block[8].p[29].y=6;
	block[8].p[30].x=4;
	block[8].p[30].y=6;
	block[8].p[31].x=5;
	block[8].p[31].y=6;
	block[8].p[32].x=6;
	block[8].p[32].y=6;
	block[8].p[33].x=0;
	block[8].p[33].y=7;
	block[8].p[34].x=4;
	block[8].p[34].y=7;
	block[8].p[35].x=0;
	block[8].p[35].y=8;
	block[8].p[36].x=2;
	block[8].p[36].y=8;
	block[8].p[37].x=4;
	block[8].p[37].y=8;
	block[8].p[38].x=6;
	block[8].p[38].y=8;

	block[9].n=12;
	block[9].x=5;
	block[9].y=4;
	block[9].col=7;
	block[9].app=0;
	block[9].p[0].x=0;
	block[9].p[0].y=1;
	block[9].p[1].x=0;
	block[9].p[1].y=2;
	block[9].p[2].x=0;
	block[9].p[2].y=3;
	block[9].p[3].x=1;
	block[9].p[3].y=3;
	block[9].p[4].x=2;
	block[9].p[4].y=0;
	block[9].p[5].x=2;
	block[9].p[5].y=1;
	block[9].p[6].x=2;
	block[9].p[6].y=2;
	block[9].p[7].x=2;
	block[9].p[7].y=3;
	block[9].p[8].x=3;
	block[9].p[8].y=3;
	block[9].p[9].x=4;
	block[9].p[9].y=1;
	block[9].p[10].x=4;
	block[9].p[10].y=2;
	block[9].p[11].x=4;
	block[9].p[11].y=3;
}*/

void first_ini() {
	ini_board();
	//ini_block();
	stage_cnt=0;
	bgm_num=0;
	bgm_state=1;
	gameflag=1;
	gameover_flag=0;
	StageSpeed=0.03;
	SpeedupEffectFlag=0;
	SpeedupEffectState[0]=StageSpeed;
	SpeedupEffectState[1]=StageSpeed;
	if (Pl_num==1) {
		Pl[0].screen_x_d=220;
		Pl[0].screen_y_d=40;
		Pl[0].screen_x=Pl[0].screen_x_d;
		Pl[0].screen_y=Pl[0].screen_y_d-BLOCK_SIZE*10;
		Pl[0].screen_x_de=Pl[0].screen_x_d+BLOCK_SIZE*10;
		Pl[0].screen_y_de=Pl[0].screen_y_d+BLOCK_SIZE*20;
	}
	if (Pl_num==2) {
		Pl[0].screen_x_d=40;
		Pl[0].screen_y_d=70;
		Pl[0].screen_x=Pl[0].screen_x_d;
		Pl[0].screen_y=Pl[0].screen_y_d-BLOCK_SIZE*10;
		Pl[0].screen_x_de=Pl[0].screen_x_d+BLOCK_SIZE*10;
		Pl[0].screen_y_de=Pl[0].screen_y_d+BLOCK_SIZE*20;
		Pl[1].screen_x_d=350;
		Pl[1].screen_y_d=70;
		Pl[1].screen_x=Pl[1].screen_x_d;
		Pl[1].screen_y=Pl[1].screen_y_d-BLOCK_SIZE*10;
		Pl[1].screen_x_de=Pl[1].screen_x_d+BLOCK_SIZE*10;
		Pl[1].screen_y_de=Pl[1].screen_y_d+BLOCK_SIZE*20;
	}

	all_cpu_flag=1;
	for (int i=0;i<Pl_num;i++) {
		if (Pl[i].cpu_flag==0) all_cpu_flag=0;
	}
	
	pause_blend = 0;
	for (int i=0;i<block_kinds;i++) {
		block[i].app=app_list[mode][i];
	}
	for (int i=0;i<4;i++) pause_button_y[i]=480;
	for (int i=0;i<Pl_num;i++) {
		Pl[i].line=0;
		Pl[i].hold=0;
		Pl[i].holdflag=0;
		Pl[i].combo=0;
		Pl[i].harddropline=0;
		Pl[i].dropline=0;
		Pl[i].score=0;
		Pl[i].n_score=0;
		Pl[i].block_num=0;
		Pl[i].cpu_state=0;
		Pl[i].starttime_cnt=GetNowCount();
		Pl[i].ghost_down=0;
		Pl[i].pause_flag=0;
		Pl[i].block.touchflag=0;
		Pl[i].cpu_mode.hold=1;
		for (int j=0;j<B_INFO_MAX;j++) Pl[i].block.flag=0;
		for (int j=0;j<10;j++) Pl[i].dis_line_times[j]=0;
		for (int j=0;j<10;j++) Pl[i].dis_line_AC_times[j]=0;
		for (int j=0;j<10;j++) Pl[i].split_times[j]=0;
		for (int j=0;j<10;j++) Pl[i].combo_times_ini[j]=0;
		for (int j=0;j<BOARD_Y_MAX;j++) Pl[i].dis_line_n[j]=100;
		for (int j=0;j<NEXT_MAX;j++) add_next(i,j);
		for (int j=0;j<EFFECT_MAX;j++) for (int k=0;k<EFFECT_SET_MAX;k++) Pl[i].effect_flag[j][k]=0;
		for (int j=0;j<20;j++) for (int k=0;k<10;k++) Pl[i].combo_times[j][k]=0;
	}
}

void result_ini() {
	GetGraphSize( img_result , &temp[0] , &temp[1] );
	result_x=-temp[0];
	for (int i=0;i<20;i++) result_score_y[i]=480;
	for (int i=0;i<4;i++) over_select_y[i]=480;
	over_select=0;
	result_cnt=0;
}

void menu_ini(){
	gameflag=0;
	all_cpu_flag=0;
	bgm_state=0;
}
