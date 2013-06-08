#include "../include/GV.h"

void control_player_config() {
	int dir;
	if (PUSH_DOWN) {
		menu_select=(menu_select+4)%16;
	}
	if (PUSH_UP) {
		menu_select=(menu_select+16-4)%16;
	}
	if (menu_select%4>Pl_num-1) {
		menu_select=(int)(menu_select/4)*4+Pl_num-1;
	}
	if (PUSH_RIGHT) {
		do {
			menu_select=(int)(menu_select/4)*4+(menu_select%4+1)%4;
		} while (menu_select%4>Pl_num-1);
	}
	if (PUSH_LEFT) {
		do {
			menu_select=(int)(menu_select/4)*4+(menu_select%4+4-1)%4;
		} while (menu_select%4>Pl_num-1);
	}
	if (PUSH_HOLD || PUSH_TURN_R || PUSH_TURN_L) {

		if (PUSH_HOLD || PUSH_TURN_R) dir=1;
		if (PUSH_TURN_L) dir=-1;

		//ÉvÉåÉCêlêî
		if ((int)(menu_select/4)==0) Pl_num=(Pl_num-1+2+dir)%2+1;
		//PLAYER
		if ((int)(menu_select/4)==1) Pl[menu_select%4].cpu_flag=(Pl[menu_select%4].cpu_flag+2+dir)%2;
		if ((int)(menu_select/4)==2) {
			//CPU_MODE
			if (Pl[menu_select%4].cpu_flag==1) Pl[menu_select%4].cpu_mode.difficalty=(Pl[menu_select%4].cpu_mode.difficalty+5+dir)%5;
			//PAD
			if (Pl[menu_select%4].cpu_flag==0) Pl[menu_select%4].pad_num=(Pl[menu_select%4].pad_num+4+dir)%4;
		}
		if ((int)(menu_select/4)==3) {
			//CPU_PATTERN
			if (Pl[menu_select%4].cpu_flag==1) Pl[menu_select%4].cpu_mode.pattern=(Pl[menu_select%4].cpu_mode.pattern+3+dir)%3;
			//KEYBOARD
			if (Pl[menu_select%4].cpu_flag==0) Pl[menu_select%4].keyboard_num=(Pl[menu_select%4].keyboard_num+3+dir)%3;
		}
	}
	if (PUSH_PAUSE) {
		menu_select=menu_state[0];
		menu_state[0]=-1;
	}
}

void control_key_config() {
	int dir,i,PadInput;

	if (key_config_state==0) {
		if (PUSH_UP || PUSH_DOWN) {
			if (PUSH_UP) dir=-1;
			else dir=1;

			menu_select=(menu_select+14+dir)%14;
		}

		if ((PUSH_RIGHT || PUSH_LEFT || PUSH_HOLD) && menu_select==0) {
			if (PUSH_LEFT) dir=-1;
			else dir=1;

			now_config_pad[0]=(now_config_pad[0]+7+dir)%7;
		} else if (PUSH_HOLD && menu_select<12) {
			key_config_state=1;
			now_config_pad[1]=menu_select-1;
		}

		if (PUSH_HOLD && menu_select==12) {
			for (i=0;i<PLAYER_MAX+3;i++) {
				configpad[i].up=configpad_ini[i].up;
				configpad[i].right=configpad_ini[i].right;
				configpad[i].left=configpad_ini[i].left;
				configpad[i].down=configpad_ini[i].down;
				configpad[i].turn_L=configpad_ini[i].turn_L;
				configpad[i].turn_R=configpad_ini[i].turn_R;
				configpad[i].hold=configpad_ini[i].hold;
				configpad[i].pause=configpad_ini[i].pause;
				configpad[i].key1=configpad_ini[i].key1;
				configpad[i].key2=configpad_ini[i].key2;
				configpad[i].key3=configpad_ini[i].key3;
			}
			menu_select=menu_state[0];
			menu_state[0]=-1;
		}

		if (PUSH_PAUSE || (PUSH_HOLD && menu_select==13)) {
			menu_select=menu_state[0];
			menu_state[0]=-1;
		}
	} else if (key_config_state==1) {
		if (now_config_pad[0]<4) {
			for (i=0;i<16;i++) {
				if (pad[now_config_pad[0]].key[i]==1) {
					switch(now_config_pad[1]) {
					case 0: configpad_ini[now_config_pad[0]].right=i; break;
					case 1: configpad_ini[now_config_pad[0]].left=i; break;
					case 2: configpad_ini[now_config_pad[0]].up=i; break;
					case 3: configpad_ini[now_config_pad[0]].down=i; break;
					case 4: configpad_ini[now_config_pad[0]].hold=i; break;
					case 5: configpad_ini[now_config_pad[0]].turn_R=i; break;
					case 6: configpad_ini[now_config_pad[0]].turn_L=i; break;
					case 7: configpad_ini[now_config_pad[0]].key1=i; break;
					case 8: configpad_ini[now_config_pad[0]].key2=i; break;
					case 9: configpad_ini[now_config_pad[0]].key3=i; break;
					case 10: configpad_ini[now_config_pad[0]].pause=i; break;
					}
					key_config_state=0;
					break;
				}
			}
		} else {
			for (i=0;i<256;i++) {
				if (CheckStateKey(i)==1) {
					switch(now_config_pad[1]) {
					case 0: configpad_ini[now_config_pad[0]].right=i; break;
					case 1: configpad_ini[now_config_pad[0]].left=i; break;
					case 2: configpad_ini[now_config_pad[0]].up=i; break;
					case 3: configpad_ini[now_config_pad[0]].down=i; break;
					case 4: configpad_ini[now_config_pad[0]].hold=i; break;
					case 5: configpad_ini[now_config_pad[0]].turn_R=i; break;
					case 6: configpad_ini[now_config_pad[0]].turn_L=i; break;
					case 7: configpad_ini[now_config_pad[0]].key1=i; break;
					case 8: configpad_ini[now_config_pad[0]].key2=i; break;
					case 9: configpad_ini[now_config_pad[0]].key3=i; break;
					case 10: configpad_ini[now_config_pad[0]].pause=i; break;
					}
					key_config_state=0;
					break;
				}
			}
		}
	}
}

void control_menu(){
	int dir,i,j;
	switch(menu_state[0]) {
	case -1:
		if (PUSH_DOWN) {
			do {
				menu_select=(menu_select+1)%6;
			} while (0);
		}
		if (PUSH_UP) {
			do {
				menu_select=(menu_select+5)%6;
			} while (0);
		}
		if (PUSH_HOLD) {
			if (menu_select<=3) {
				mode=menu_select;
				func_state=51;
				menu_selected_cnt=0;
			}
			switch (menu_select) {
			case 4:
				menu_state[0]=menu_select;
				menu_select=0;
				break;
			case 5:
				menu_state[0]=menu_select;
				menu_select=0;
				now_config_pad[0]=0;
				key_config_state=0;
				for (i=0;i<PLAYER_MAX+3;i++) {
					configpad_ini[i].up=configpad[i].up;
					configpad_ini[i].right=configpad[i].right;
					configpad_ini[i].left=configpad[i].left;
					configpad_ini[i].down=configpad[i].down;
					configpad_ini[i].turn_L=configpad[i].turn_L;
					configpad_ini[i].turn_R=configpad[i].turn_R;
					configpad_ini[i].hold=configpad[i].hold;
					configpad_ini[i].pause=configpad[i].pause;
					configpad_ini[i].key1=configpad[i].key1;
					configpad_ini[i].key2=configpad[i].key2;
					configpad_ini[i].key3=configpad[i].key3;
				}
				break;
			}
		}
		break;
	case 4:
		control_player_config();
		break;
	case 5:
		control_key_config();
		break;
	}
	/*if (CheckStateKey(KEY_INPUT_W)==1) {
		if (window_mode==TRUE) {
			temp[0]=ChangeWindowMode(FALSE);
			switch(temp[0]) {
			case DX_CHANGESCREEN_OK:
				window_mode=FALSE;
				break;
			case DX_CHANGESCREEN_RETURN:
				window_mode=TRUE;
				break;
			case DX_CHANGESCREEN_DEFAULT:
				window_mode=FALSE;
				break;
			}
		} else if (window_mode==FALSE) {
			temp[0]=ChangeWindowMode(TRUE);
			switch(temp[0]) {
			case DX_CHANGESCREEN_OK:
				window_mode=TRUE;
				break;
			case DX_CHANGESCREEN_RETURN:
				window_mode=FALSE;
				break;
			case DX_CHANGESCREEN_DEFAULT:
				window_mode=FALSE;
				break;
			}
		}
		load_graph();
	}*/
}

void control_result() {
	int k,i,j;
	int result_width;

	gameover_x = 530 + duv_2( gameover_x - 530 , 1.0);

	for (i=0;i<20;i++)
		if (result_cnt>i*4)
			result_score_y[i] = (Pl[0].screen_y_d+20*i) + duv_2( result_score_y[i] - (Pl[0].screen_y_d+20*i) , 1.0);
	
	GetGraphSize( img_result , &result_width , &temp[0]);
	result_x = (225-result_width) + duv_2( result_x - (225-result_width) , 0.5 );

	for (i=0;i<4;i++) {
		over_select_y[i] = 480 + duv_2( over_select_y[i] - 480 , 1.5 );
	}
	
	for (k=0;k<Pl_num;k++) {
		Pl[k].pause_cnt++;
		for (i=0;i<EFFECT_MAX;i++) {
			for (j=0;j<EFFECT_SET_MAX;j++) {
				if (Pl[k].effect_flag[i][j]>0) Pl[k].effect_flag[i][j]++;
			}
		}
	}
	
	if (SpeedupEffectFlag>0) SpeedupEffectFlag++;
	if (SpeedupEffectState[1]<StageSpeed) {
		SpeedupEffectState[0]=SpeedupEffectState[1];
		SpeedupEffectState[1]=StageSpeed;
		SpeedupEffectFlag=1;
	}
}

void control_over_select() {
	int i,j,k,aim;

	gameover_x = 530 + duv_2( gameover_x - 530 , 1.0);
	
	for (i=0;i<20;i++) result_score_y[i] = -50 + duv_2( result_score_y[i] - (-50) , 1.6);

	result_x = 640 + duv_2( result_x - 640 , 1.5 );
	
	for (i=0;i<4;i++) {
		aim=aim=Pl[0].screen_y_de-30-(3-i)*40;
		over_select_y[i] = aim + duv_2( over_select_y[i] - aim , 1.5 );
	}

	if (CheckStatePad(-1,PAD_NUM_DOWN)==1) {
		do {
			over_select=(over_select+1)%4;
		} while (over_select==2);
	}
	if (CheckStatePad(-1,PAD_NUM_UP)==1) {
		do {
			over_select=(over_select+3)%4;
		} while (over_select==2);
	}
	
	for (k=0;k<Pl_num;k++) {
		Pl[k].pause_cnt++;
		for (i=0;i<EFFECT_MAX;i++) {
			for (j=0;j<EFFECT_SET_MAX;j++) {
				if (Pl[k].effect_flag[i][j]>0) Pl[k].effect_flag[i][j]++;
			}
		}
	}

	if (SpeedupEffectFlag>0) SpeedupEffectFlag++;
	if (SpeedupEffectState[1]<StageSpeed) {
		SpeedupEffectState[0]=SpeedupEffectState[1];
		SpeedupEffectState[1]=StageSpeed;
		SpeedupEffectFlag=1;
	}
}

void control_game_pause() {
	int i,aim;

	pause_blend = 150 + duv_2(pause_blend - 150 , 0.8);

	for (i=0;i<4;i++) {
		if (i==0) aim=Pl[0].screen_y_de-170; else aim=Pl[0].screen_y_de-30-(3-i)*40;
		pause_button_y[i] = aim + duv_2( pause_button_y[i] - aim , 2.0 );
	}
	
	if (CheckStatePad((all_cpu_flag==0)?pause_push_Pl:-1,PAD_NUM_DOWN)==1) {
		pause_select=(pause_select+1)%3;
	}
	if (CheckStatePad((all_cpu_flag==0)?pause_push_Pl:-1,PAD_NUM_UP)==1) {
		pause_select=(pause_select+2)%3;
	}
}

void control_main() {
	int i,j,k,all_pl_lines;

	pause_blend = 0 + duv_2(pause_blend - 0 , 2.0 );
	
	for (k=0;k<PLAYER_MAX;k++) {
		Pl[k].n_score = (double)Pl[k].score + duv_2( Pl[k].n_score - (double)Pl[k].score , 1.0 );
	
		if (Pl[k].block.flag==1) {
			Pl[k].block.angle_rate=duv_2(Pl[k].block.angle_rate,0.2);
		}

		for (i=0;i<EFFECT_MAX;i++) {
			for (j=0;j<EFFECT_SET_MAX;j++) {
				if (Pl[k].effect_flag[i][j]>0) Pl[k].effect_flag[i][j]++;
			}
		}

		Pl[k].pause_cnt++;
	}

	for (i=0;i<4;i++) {
		pause_button_y[i] = 480 + duv_2( pause_button_y[i] - 480 , 1.5 );
	}

	all_pl_lines=0;

	for (i=0;i<Pl_num;i++) all_pl_lines+=Pl[i].line;

	StageSpeed=0.03+(int)(all_pl_lines/Pl_num/25)*0.04;
	if (SpeedupEffectFlag>0) SpeedupEffectFlag++;
	if (SpeedupEffectState[1]<StageSpeed) {
		SpeedupEffectState[0]=SpeedupEffectState[1];
		SpeedupEffectState[1]=StageSpeed;
		SpeedupEffectFlag=1;
	}
}

void control_func_state() {
	switch (func_state) {
	case 1: //ÉçÉSâÊñ 
		if (CheckStatePad(-1,PAD_NUM_HOLD)==1) {
			func_state=50;
		}
		break;
	}
}