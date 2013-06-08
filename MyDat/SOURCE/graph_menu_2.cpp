#include "../include/GV.h"

void graph_menu_button() {
	int i,j;
	int draw_x;
	int draw_y;
	int col;
	char string[128];
	if (menu_state[0]==-1 || menu_state[0]==4) {
		for (i=0;i<6;i++) {
			if (i<4) {
				draw_x=70;
				draw_y=88*i+10;
			} else if (i<6) {
				draw_x=105;
				draw_y=370+(i-4)*52;
			}
			if ((menu_select==i && menu_state[0]==-1) || (i==menu_state[0])) {
				if (func_state==50 || menu_selected_cnt/3%2==0)
					DrawGraph(draw_x,draw_y,img_menu_select[1][i],TRUE);
			} else {
				DrawGraph(draw_x,draw_y,img_menu_select[0][i],TRUE);
			}
		}
	}
	if (menu_state[0]==4) {
		//ウィンドウ
		DrawGraph(80,65,img_window[0],TRUE);
		//「プレイ人数」
		if ((int)(menu_select/4)==0) DrawGraph(185,90,img_part[0][10],TRUE);
		else DrawGraph(185,90,img_part[0][0],TRUE);
		//プレイ人数
		DrawGraph(403,90,img_part[0][Pl_num],TRUE);
		//「1P」～「4P」
		for (i=0;i<4;i++) DrawGraph(155+i*95.5,145,img_part[0][3+i],TRUE);
		//ボタン
		for (i=0;i<PLAYER_MAX;i++) {
			for (j=0;j<3;j++) {
				//外枠
				if ((j+1)*4+i==menu_select) DrawGraph(127+i*95.5,179+j*41,img_part[0][8],TRUE);
				else if (i>Pl_num-1) DrawGraph(127+i*95.5,179+j*41,img_part[0][9],TRUE);
				else DrawGraph(127+i*95.5,179+j*41,img_part[0][7],TRUE);
				//中身
				if (i<Pl_num) {
					switch (j) {
					case 0:
						DrawGraph(127+i*95.5,179+j*41,img_selection[0][0][Pl[i].cpu_flag],TRUE);
						break;
					case 1:
						if (Pl[i].cpu_flag==1) DrawGraph(127+i*95.5,179+j*41,img_selection[0][1][Pl[i].cpu_mode.difficalty],TRUE);
						if (Pl[i].cpu_flag==0) DrawGraph(127+i*95.5,179+j*41,img_selection[0][3][Pl[i].pad_num],TRUE);
						break;
					case 2:
						if (Pl[i].cpu_flag==1) DrawGraph(127+i*95.5,179+j*41,img_selection[0][2][Pl[i].cpu_mode.pattern],TRUE);
						if (Pl[i].cpu_flag==0) DrawGraph(127+i*95.5,179+j*41,img_selection[0][5][Pl[i].keyboard_num],TRUE);
						break;
					}
				}
			}
		}
		//「Press Pause Key To Return」
		graph_string_slim_menu(320-get_graph_string_slim_width(3,2,"Press PAUSE Key To Return.")/2,330,3,2,"Press PAUSE Key To Return.");
	}
	if (menu_state[0]==5) {
		//プレイヤー表示枠
		if (menu_select==0) DrawGraph(272,30,img_part[0][8],TRUE);
		else DrawGraph(272,30,img_part[0][7],TRUE);
		//プレイヤー表示
		if (now_config_pad[0]<4) DrawGraph(272,30,img_selection[0][3][now_config_pad[0]],TRUE); 
		else DrawGraph(272,30,img_selection[0][5][now_config_pad[0]-4],TRUE);
		//キー状態表示
		for (i=0;i<11;i++) {

			if (menu_select-1==i) col=3;
			else col=1;

			switch (i) {
			case 0: strcpy(string,"Right"); break;
			case 1: strcpy(string,"Left"); break;
			case 2: strcpy(string,"Up(Harddrop)"); break;
			case 3: strcpy(string,"Down(Drop)"); break;
			case 4: strcpy(string,"Hold"); break;
			case 5: strcpy(string,"TurnRight"); break;
			case 6: strcpy(string,"TurnLeft"); break;
			case 7: strcpy(string,"Key1"); break;
			case 8: strcpy(string,"Key2"); break;
			case 9: strcpy(string,"Key3"); break;
			case 10: strcpy(string,"Pause"); break;
			}

			graph_string_slim_menu(80,80+20*i,col,2,string);

			if (key_config_state==0 || menu_select-1!=i) {

				switch (i) {
				case 0: j=configpad_ini[now_config_pad[0]].right; break;
				case 1: j=configpad_ini[now_config_pad[0]].left; break;
				case 2: j=configpad_ini[now_config_pad[0]].up; break;
				case 3: j=configpad_ini[now_config_pad[0]].down; break;
				case 4: j=configpad_ini[now_config_pad[0]].hold; break;
				case 5: j=configpad_ini[now_config_pad[0]].turn_R; break;
				case 6: j=configpad_ini[now_config_pad[0]].turn_L; break;
				case 7: j=configpad_ini[now_config_pad[0]].key1; break;
				case 8: j=configpad_ini[now_config_pad[0]].key2; break;
				case 9: j=configpad_ini[now_config_pad[0]].key3; break;
				case 10: j=configpad_ini[now_config_pad[0]].pause; break;
				}

				if (now_config_pad[0]<4) {
					if (j<4) {
						if (j==0) strcpy(string,"Down");
						if (j==1) strcpy(string,"Left");
						if (j==2) strcpy(string,"Right");
						if (j==3) strcpy(string,"Up");
					} else {
						sprintf(string,"%02d",j-4);
					}
				} else {
					switch (j) {
					case KEY_INPUT_BACK: strcpy(string,"BackSpace"); break;
					case KEY_INPUT_TAB: strcpy(string,"Tab"); break;
					case KEY_INPUT_RETURN: strcpy(string,"Enter"); break;
					case KEY_INPUT_LSHIFT: strcpy(string,"LeftShift"); break;
					case KEY_INPUT_RSHIFT: strcpy(string,"RightShift"); break;
					case KEY_INPUT_LCONTROL: strcpy(string,"LeftCtrl"); break;
					case KEY_INPUT_RCONTROL: strcpy(string,"RightCtrl"); break;
					case KEY_INPUT_ESCAPE: strcpy(string,"Esc"); break;
					case KEY_INPUT_SPACE: strcpy(string,"Space"); break;
					case KEY_INPUT_PGUP: strcpy(string,"PageUp"); break;
					case KEY_INPUT_PGDN: strcpy(string,"PageDown"); break;
					case KEY_INPUT_END: strcpy(string,"End"); break;
					case KEY_INPUT_HOME: strcpy(string,"Home"); break;
					case KEY_INPUT_LEFT: strcpy(string,"Left"); break;
					case KEY_INPUT_UP: strcpy(string,"Up"); break;
					case KEY_INPUT_RIGHT: strcpy(string,"Right"); break;
					case KEY_INPUT_DOWN: strcpy(string,"Down"); break;
					case KEY_INPUT_INSERT: strcpy(string,"Insert"); break;
					case KEY_INPUT_DELETE: strcpy(string,"Delete"); break;
					case KEY_INPUT_MINUS: strcpy(string,"-"); break;
					case KEY_INPUT_YEN: strcpy(string,"Yen"); break;
					case KEY_INPUT_PREVTRACK: strcpy(string,"PrevTrack"); break;
					case KEY_INPUT_PERIOD: strcpy(string,"."); break;
					case KEY_INPUT_SLASH: strcpy(string,"Slash"); break;
					case KEY_INPUT_LALT: strcpy(string,"LeftAlt"); break;
					case KEY_INPUT_RALT: strcpy(string,"RightAlt"); break;
					case KEY_INPUT_SCROLL: strcpy(string,"ScrollLock"); break;
					case KEY_INPUT_SEMICOLON: strcpy(string,"SemiColon"); break;
					case KEY_INPUT_COLON: strcpy(string,":"); break;
					case KEY_INPUT_LBRACKET: strcpy(string,"LeftBrack"); break;
					case KEY_INPUT_RBRACKET: strcpy(string,"RightBrack"); break;
					case KEY_INPUT_AT: strcpy(string,"AtMark"); break;
					case KEY_INPUT_BACKSLASH: strcpy(string,"BackSlash"); break;
					case KEY_INPUT_COMMA: strcpy(string,","); break;
					case KEY_INPUT_CAPSLOCK: strcpy(string,"CapsLock"); break;
					case KEY_INPUT_PAUSE: strcpy(string,"PauseBreak"); break;
					case KEY_INPUT_NUMPAD0: strcpy(string,"Tenkey0"); break;
					case KEY_INPUT_NUMPAD1: strcpy(string,"Tenkey1"); break;
					case KEY_INPUT_NUMPAD2: strcpy(string,"Tenkey2"); break;
					case KEY_INPUT_NUMPAD3: strcpy(string,"Tenkey3"); break;
					case KEY_INPUT_NUMPAD4: strcpy(string,"Tenkey4"); break;
					case KEY_INPUT_NUMPAD5: strcpy(string,"Tenkey5"); break;
					case KEY_INPUT_NUMPAD6: strcpy(string,"Tenkey6"); break;
					case KEY_INPUT_NUMPAD7: strcpy(string,"Tenkey7"); break;
					case KEY_INPUT_NUMPAD8: strcpy(string,"Tenkey8"); break;
					case KEY_INPUT_NUMPAD9: strcpy(string,"Tenkey9"); break;
					case KEY_INPUT_MULTIPLY: strcpy(string,"Astarisk"); break;
					case KEY_INPUT_ADD: strcpy(string,"Tenkey+"); break;
					case KEY_INPUT_SUBTRACT: strcpy(string,"Tenkey-"); break;
					case KEY_INPUT_DECIMAL: strcpy(string,"Tenkey."); break;
					case KEY_INPUT_DIVIDE: strcpy(string,"TenkeySlsh"); break;
					case KEY_INPUT_NUMPADENTER: strcpy(string,"TenkeyEntr"); break;
					case KEY_INPUT_F1: strcpy(string,"F1"); break;
					case KEY_INPUT_F2: strcpy(string,"F2"); break;
					case KEY_INPUT_F3: strcpy(string,"F3"); break;
					case KEY_INPUT_F4: strcpy(string,"F4"); break;
					case KEY_INPUT_F5: strcpy(string,"F5"); break;
					case KEY_INPUT_F6: strcpy(string,"F6"); break;
					case KEY_INPUT_F7: strcpy(string,"F7"); break;
					case KEY_INPUT_F8: strcpy(string,"F8"); break;
					case KEY_INPUT_F9: strcpy(string,"F9"); break;
					case KEY_INPUT_F10: strcpy(string,"F10"); break;
					case KEY_INPUT_F11: strcpy(string,"F11"); break;
					case KEY_INPUT_F12: strcpy(string,"F12"); break;
					case KEY_INPUT_A: strcpy(string,"A"); break;
					case KEY_INPUT_B: strcpy(string,"B"); break;
					case KEY_INPUT_C: strcpy(string,"C"); break;
					case KEY_INPUT_D: strcpy(string,"D"); break;
					case KEY_INPUT_E: strcpy(string,"E"); break;
					case KEY_INPUT_F: strcpy(string,"F"); break;
					case KEY_INPUT_G: strcpy(string,"G"); break;
					case KEY_INPUT_H: strcpy(string,"H"); break;
					case KEY_INPUT_I: strcpy(string,"I"); break;
					case KEY_INPUT_J: strcpy(string,"J"); break;
					case KEY_INPUT_K: strcpy(string,"K"); break;
					case KEY_INPUT_L: strcpy(string,"L"); break;
					case KEY_INPUT_M: strcpy(string,"M"); break;
					case KEY_INPUT_N: strcpy(string,"N"); break;
					case KEY_INPUT_O: strcpy(string,"O"); break;
					case KEY_INPUT_P: strcpy(string,"P"); break;
					case KEY_INPUT_Q: strcpy(string,"Q"); break;
					case KEY_INPUT_R: strcpy(string,"R"); break;
					case KEY_INPUT_S: strcpy(string,"S"); break;
					case KEY_INPUT_T: strcpy(string,"T"); break;
					case KEY_INPUT_U: strcpy(string,"U"); break;
					case KEY_INPUT_V: strcpy(string,"V"); break;
					case KEY_INPUT_W: strcpy(string,"W"); break;
					case KEY_INPUT_X: strcpy(string,"X"); break;
					case KEY_INPUT_Y: strcpy(string,"Y"); break;
					case KEY_INPUT_Z: strcpy(string,"Z"); break;
					case KEY_INPUT_0: strcpy(string,"0"); break;
					case KEY_INPUT_1: strcpy(string,"1"); break;
					case KEY_INPUT_2: strcpy(string,"2"); break;
					case KEY_INPUT_3: strcpy(string,"3"); break;
					case KEY_INPUT_4: strcpy(string,"4"); break;
					case KEY_INPUT_5: strcpy(string,"5"); break;
					case KEY_INPUT_6: strcpy(string,"6"); break;
					case KEY_INPUT_7: strcpy(string,"7"); break;
					case KEY_INPUT_8: strcpy(string,"8"); break;
					case KEY_INPUT_9: strcpy(string,"9"); break;
					}
				}
			} else {
				strcpy(string,"Press Key.");
			}
			
			graph_string_slim_menu(320,80+20*i,col,2,string);

		}
		
		if (menu_select==12) col=3;
		else col=1;

		graph_string_slim_menu(130,320,col,2,"Save");
		
		if (menu_select==13) col=3;
		else col=1;

		graph_string_slim_menu(130,340,col,2,"Cancel");

	}
}

void graph_menu() {
	DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
	graph_menu_button();
	if (func_state==51) {
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(255.0/30.0*menu_selected_cnt) );
		DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
	}
}

void graph_logo() {
	int Alpha;

	DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
	if (exe_cnt<30) {
		Alpha=(int)(255/30*exe_cnt);
	} else if (exe_cnt<210) {
		Alpha=255;
	} else if (exe_cnt<240) {
		Alpha=(int)(255/30*(240-exe_cnt));
	} else {
		func_state=50;
		return;
	}

	SetDrawBlendMode( DX_BLENDMODE_ALPHA , Alpha );
	GetGraphSize(img_menu[0][0],&temp[0],&temp[1]);
	DrawGraph(320-temp[0]/2,200,img_menu[0][0],TRUE);
	GetGraphSize(img_menu[0][1],&temp[0],&temp[1]);
	DrawGraph(320-temp[0]/2,260,img_menu[0][1],TRUE);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
}

void graph_menun() {
	int i;

	DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);

	for (i=0;i<7;i++) {
		DrawGraph(45+i*80,33,img_menu[3][i],FALSE);
	}

	for (i=0;i<7;i++) {
		
	}
}