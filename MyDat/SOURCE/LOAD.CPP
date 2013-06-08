#include "../include/GV.h"
#include <string.h>
#include <math.h>
#include <Windows.h>

int block_dis[315][3];
int block_dis_element;

void graph_load_graph_first() {
	int roop_i,roop_j;

	block_dis_element=0;
	for (roop_i=0;roop_i<21;roop_i++) {
		for (roop_j=0;roop_j<15;roop_j++) {
			if ((roop_i<7 || 13<roop_i) && roop_j!=7) {
				if (roop_i==0 && roop_j==0) {
					roop_i+=0;
				}
				block_dis[block_dis_element][0]=roop_i;
				block_dis[block_dis_element][1]=roop_j;
				block_dis[block_dis_element][2]=sqrt((float)((roop_i-10)*(roop_i-10)+(roop_j-7)*(roop_j-7)));
				block_dis_element++;
			}
		}
	}

	for (roop_i=0;roop_i<block_dis_element-1;roop_i++) {
		for (roop_j=0;roop_j<block_dis_element-1-roop_i;roop_j++) {
			if (block_dis[roop_j][2]>block_dis[roop_j+1][2]) {
				temp[0]=block_dis[roop_j][0];
				block_dis[roop_j][0]=block_dis[roop_j+1][0];
				block_dis[roop_j+1][0]=temp[0];
				temp[0]=block_dis[roop_j][1];
				block_dis[roop_j][1]=block_dis[roop_j+1][1];
				block_dis[roop_j+1][1]=temp[0];
				temp[0]=block_dis[roop_j][2];
				block_dis[roop_j][2]=block_dis[roop_j+1][2];
				block_dis[roop_j+1][2]=temp[0];
			}
		}
	}
}

int graph_load_times=0;
int graphed_block=0;

void graph_load_graph() {
	/*int i;

	graph_load_times++;
	for (i=graphed_block;i<(int)(block_dis_element/170*graph_load_times) && i<block_dis_element;i++) {
		DrawGraph(
			5+block_dis[i][0]*30+5,
			15+block_dis[i][1]*30+5,
			img_bl[GetRand(6)],
			FALSE);
	}
	Sleep(10);*/
}

void load_graph() {
	img_menu[0][0] = LoadGraph("dat/img/menu/nowloading.png");

	GetGraphSize(img_menu[0][0],&temp[0],&temp[1]);
	DrawGraph((640-temp[0])/2,(480-temp[1])/2,img_menu[0][0],TRUE);

	LoadDivGraph( "dat/img/block.png" , 19 , 8 , 3 , 20 , 20 , img_bl ) ;

	graph_load_graph_first();

	graph_load_graph();

	LoadDivGraph( "dat/img/block_ghost.png" , 19 , 8 , 3 , 20 , 20 , img_ghost ) ;
	graph_load_graph();
	//LoadDivGraph( "dat/img/num/4.png" , 11 , 11 , 1 , 12 , 20 , img_num[0] ) ;
	LoadDivGraph( "dat/img/char/00.png" , 78 , 13 , 6 , 100 , 146 , img_char[0][0] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/00_s.png" , 78 , 13 , 6 , 14 , 20 , img_char[0][1] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/01.png" , 78 , 13 , 6 , 105 , 140 , img_char[1][0] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/01_s.png" , 78 , 13 , 6 , 15 , 20 , img_char[1][1] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/02.png" , 78 , 13 , 6 , 105 , 140 , img_char[2][0] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/02_s.png" , 78 , 13 , 6 , 15 , 20 , img_char[2][1] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/03.png" , 78 , 13 , 6 , 105 , 140 , img_char[3][0] ) ;
	graph_load_graph();
	LoadDivGraph( "dat/img/char/03_s.png" , 78 , 13 , 6 , 15 , 20 , img_char[3][1] ) ;
	graph_load_graph();
	img_sheet[0] = LoadGraph("dat/img/sheet/sheet1_1.png");
	graph_load_graph();
	img_sheet[1] = LoadGraph("dat/img/sheet/sheet1_2.png");
	graph_load_graph();
	img_sheet[2] = LoadGraph("dat/img/sheet/sheet1_3.png");
	graph_load_graph();
	img_sheet[3] = LoadGraph("dat/img/sheet/sheet1_4.png");
	graph_load_graph();
	img_sheet[4] = LoadGraph("dat/img/sheet/sheet2_1.png");
	graph_load_graph();
	img_over_select[0][0] = LoadGraph("dat/img/select_menu_1.png");
	graph_load_graph();
	img_over_select[0][1] = LoadGraph("dat/img/select_menu_2.png");
	graph_load_graph();
	img_over_select[0][2] = LoadGraph("dat/img/select_menu_3.png");
	graph_load_graph();
	img_over_select[0][3] = LoadGraph("dat/img/select_menu_4.png");
	graph_load_graph();
	img_over_select[0][4] = LoadGraph("dat/img/select_menu_5.png");
	graph_load_graph();
	img_over_select[0][5] = LoadGraph("dat/img/select_menu_6.png");
	graph_load_graph();
	img_over_select[1][0] = LoadGraph("dat/img/selected_menu_1.png");
	graph_load_graph();
	img_over_select[1][1] = LoadGraph("dat/img/selected_menu_2.png");
	graph_load_graph();
	img_over_select[1][2] = LoadGraph("dat/img/selected_menu_3.png");
	graph_load_graph();
	img_over_select[1][3] = LoadGraph("dat/img/selected_menu_4.png");
	graph_load_graph();
	img_over_select[1][4] = LoadGraph("dat/img/selected_menu_5.png");
	graph_load_graph();
	img_over_select[1][5] = LoadGraph("dat/img/selected_menu_6.png");
	graph_load_graph();
	img_menu_select[0][0] = LoadGraph("dat/img/menu_1.png");
	graph_load_graph();
	img_menu_select[0][1] = LoadGraph("dat/img/menu_2.png");
	graph_load_graph();
	img_menu_select[0][2] = LoadGraph("dat/img/menu_3.png");
	graph_load_graph();
	img_menu_select[0][3] = LoadGraph("dat/img/menu_4.png");
	graph_load_graph();
	img_menu_select[0][4] = LoadGraph("dat/img/menu_5_new.png");
	graph_load_graph();
	img_menu_select[0][5] = LoadGraph("dat/img/menu_6_new.png");
	graph_load_graph();
	img_menu_select[1][0] = LoadGraph("dat/img/menu_1_s.png");
	graph_load_graph();
	img_menu_select[1][1] = LoadGraph("dat/img/menu_2_s.png");
	graph_load_graph();
	img_menu_select[1][2] = LoadGraph("dat/img/menu_3_s.png");
	graph_load_graph();
	img_menu_select[1][3] = LoadGraph("dat/img/menu_4_s.png");
	graph_load_graph();
	img_menu_select[1][4] = LoadGraph("dat/img/menu_5_s_new.png");
	graph_load_graph();
	img_menu_select[1][5] = LoadGraph("dat/img/menu_6_s_new.png");
	graph_load_graph();
	/*img_menu_choice[0][4] = LoadGraph("dat/img/menu_5_ch_1.png");
	img_menu_choice[1][4] = LoadGraph("dat/img/menu_5_ch_2.png");
	img_menu_choice[2][4] = LoadGraph("dat/img/menu_5_ch_3.png");
	img_menu_choice[3][4] = LoadGraph("dat/img/menu_5_ch_4.png");
	img_menu_choice[4][4] = LoadGraph("dat/img/menu_5_ch_5.png");
	//img_menu_choice[5][4] = LoadGraph("dat/img/menu_5_ch_6.png");
	//img_menu_choice[6][4] = LoadGraph("dat/img/menu_5_ch_7.png");
	img_menu_choice[0][5] = LoadGraph("dat/img/menu_6_ch_1.png");
	img_menu_choice[1][5] = LoadGraph("dat/img/menu_6_ch_2.png");
	img_menu_choice[0][6] = LoadGraph("dat/img/menu_7_ch_1.png");
	img_menu_choice[1][6] = LoadGraph("dat/img/menu_7_ch_2.png");*/
	img_back[0][0] = LoadGraph("dat/img/back/back01.png");
	graph_load_graph();
	img_back[0][1] = LoadGraph("dat/img/back/back02.png");
	graph_load_graph();
	img_back[0][2] = LoadGraph("dat/img/back/back03.png");
	graph_load_graph();
	img_back[0][3] = LoadGraph("dat/img/back/back04.png");
	graph_load_graph();
	img_back[1][0] = LoadGraph("dat/img/back/mesen01.png");
	graph_load_graph();
	img_back[1][1] = LoadGraph("dat/img/back/mesen02.png");
	graph_load_graph();
	img_back[1][2] = LoadGraph("dat/img/back/mesen03.png");
	graph_load_graph();
	img_back[1][3] = LoadGraph("dat/img/back/mesen04.png");
	graph_load_graph();
	img_game = LoadGraph("dat/img/game.png");
	graph_load_graph();
	img_over = LoadGraph("dat/img/over.png");
	graph_load_graph();
	img_result = LoadGraph("dat/img/Result.png");
	graph_load_graph();
	img_pause = LoadGraph("dat/img/Pause.png");
	graph_load_graph();
	img_part[0][0] = LoadGraph("dat/img/config/config01.png");
	graph_load_graph();
	img_part[0][1] = LoadGraph("dat/img/config/config02.png");
	graph_load_graph();
	img_part[0][2] = LoadGraph("dat/img/config/config03.png");
	graph_load_graph();
	img_part[0][3] = LoadGraph("dat/img/config/config04.png");
	graph_load_graph();
	img_part[0][4] = LoadGraph("dat/img/config/config05.png");
	graph_load_graph();
	img_part[0][5] = LoadGraph("dat/img/config/config06.png");
	graph_load_graph();
	img_part[0][6] = LoadGraph("dat/img/config/config07.png");
	graph_load_graph();
	img_part[0][7] = LoadGraph("dat/img/config/button01.png");
	graph_load_graph();
	img_part[0][8] = LoadGraph("dat/img/config/button02.png");
	graph_load_graph();
	img_part[0][9] = LoadGraph("dat/img/config/button03.png");
	graph_load_graph();
	img_part[0][10] = LoadGraph("dat/img/config/config01_s.png");
	graph_load_graph();
	img_selection[0][0][0] = LoadGraph("dat/img/config/config1-1.png");
	graph_load_graph();
	img_selection[0][0][1] = LoadGraph("dat/img/config/config1-2.png");
	graph_load_graph();
	img_selection[0][1][0] = LoadGraph("dat/img/config/config2-1.png");
	graph_load_graph();
	img_selection[0][1][1] = LoadGraph("dat/img/config/config2-2.png");
	graph_load_graph();
	img_selection[0][1][2] = LoadGraph("dat/img/config/config2-3.png");
	graph_load_graph();
	img_selection[0][1][3] = LoadGraph("dat/img/config/config2-4.png");
	graph_load_graph();
	img_selection[0][1][4] = LoadGraph("dat/img/config/config2-5.png");
	graph_load_graph();
	img_selection[0][2][0] = LoadGraph("dat/img/config/config3-2.png");
	graph_load_graph();
	img_selection[0][2][1] = LoadGraph("dat/img/config/config3-1.png");
	graph_load_graph();
	img_selection[0][2][2] = LoadGraph("dat/img/config/config3-3.png");
	graph_load_graph();
	img_selection[0][3][0] = LoadGraph("dat/img/config/config4-1.png");
	graph_load_graph();
	img_selection[0][3][1] = LoadGraph("dat/img/config/config4-2.png");
	graph_load_graph();
	img_selection[0][3][2] = LoadGraph("dat/img/config/config4-3.png");
	graph_load_graph();
	img_selection[0][3][3] = LoadGraph("dat/img/config/config4-4.png");
	graph_load_graph();
	img_selection[0][4][0] = LoadGraph("dat/img/config/config5-1.png");
	graph_load_graph();
	img_selection[0][4][1] = LoadGraph("dat/img/config/config5-2.png");
	graph_load_graph();
	img_selection[0][4][2] = LoadGraph("dat/img/config/config5-3.png");
	graph_load_graph();
	img_selection[0][4][3] = LoadGraph("dat/img/config/config5-4.png");
	graph_load_graph();
	img_selection[0][5][0] = LoadGraph("dat/img/config/config6-1.png");
	graph_load_graph();
	img_selection[0][5][1] = LoadGraph("dat/img/config/config6-2.png");
	graph_load_graph();
	img_selection[0][5][2] = LoadGraph("dat/img/config/config6-3.png");
	graph_load_graph();
	img_selection[0][5][3] = LoadGraph("dat/img/config/config6-4.png");
	graph_load_graph();
	img_window[0] = LoadGraph("dat/img/config/window01.png");
	graph_load_graph();
	img_effect[0][0] = LoadGraph("dat/img/effect/firebullet01.png");
	graph_load_graph();
	img_effect[0][1] = LoadGraph("dat/img/effect/firebullet02.png");
	graph_load_graph();
	img_effect[0][2] = LoadGraph("dat/img/effect/firebullet03.png");
	graph_load_graph();
	img_effect[0][3] = LoadGraph("dat/img/effect/firebullet04.png");
	graph_load_graph();
	img_effect[0][4] = LoadGraph("dat/img/effect/firebullet05.png");
	graph_load_graph();
	img_effect[0][5] = LoadGraph("dat/img/effect/firebullet06.png");
	graph_load_graph();
	img_effect[0][6] = LoadGraph("dat/img/effect/firebullet07.png");
	graph_load_graph();
	img_effect[0][7] = LoadGraph("dat/img/effect/firebullet08.png");
	graph_load_graph();
	img_effect[1][0] = LoadGraph("dat/img/speed_up.png");
	graph_load_graph();
	img_menu[0][0] = LoadGraph("dat/img/menu/load1.png");
	graph_load_graph();
	img_menu[0][1] = LoadGraph("dat/img/menu/load2.png");
	graph_load_graph();
	img_menu[0][2] = LoadGraph("dat/img/menu/version.png");
	graph_load_graph();
	img_menu[1][0] = LoadGraph("dat/img/menu/choice1.png");
	graph_load_graph();
	img_menu[1][1] = LoadGraph("dat/img/menu/choice2.png");
	graph_load_graph();
	img_menu[1][2] = LoadGraph("dat/img/menu/choice3.png");
	graph_load_graph();
	img_menu[1][3] = LoadGraph("dat/img/menu/choice4.png");
	graph_load_graph();
	img_menu[1][4] = LoadGraph("dat/img/menu/choice5.png");
	graph_load_graph();
	img_menu[1][5] = LoadGraph("dat/img/menu/choice6.png");
	graph_load_graph();
	img_menu[1][6] = LoadGraph("dat/img/menu/choice7.png");
	graph_load_graph();
	img_menu[2][0] = LoadGraph("dat/img/menu/choice1s.png");
	graph_load_graph();
	img_menu[2][1] = LoadGraph("dat/img/menu/choice2s.png");
	graph_load_graph();
	img_menu[2][2] = LoadGraph("dat/img/menu/choice3s.png");
	graph_load_graph();
	img_menu[2][3] = LoadGraph("dat/img/menu/choice4s.png");
	graph_load_graph();
	img_menu[2][4] = LoadGraph("dat/img/menu/choice5s.png");
	graph_load_graph();
	img_menu[2][5] = LoadGraph("dat/img/menu/choice6s.png");
	graph_load_graph();
	img_menu[2][6] = LoadGraph("dat/img/menu/choice7s.png");
	graph_load_graph();
	img_menu[3][0] = LoadGraph("dat/img/menu/logo1.png");
	graph_load_graph();
	img_menu[3][1] = LoadGraph("dat/img/menu/logo2.png");
	graph_load_graph();
	img_menu[3][2] = LoadGraph("dat/img/menu/logo3.png");
	graph_load_graph();
	img_menu[3][3] = LoadGraph("dat/img/menu/logo4.png");
	graph_load_graph();
	img_menu[3][4] = LoadGraph("dat/img/menu/logo5.png");
	graph_load_graph();
	img_menu[3][5] = LoadGraph("dat/img/menu/logo6.png");
	graph_load_graph();
	img_menu[3][6] = LoadGraph("dat/img/menu/logo7.png");
	graph_load_graph();
	img_menu[4][0] = LoadGraph("dat/img/menu/round1.png");
	graph_load_graph();
	img_menu[4][1] = LoadGraph("dat/img/menu/round2.png");
	graph_load_graph();
	img_menu[4][2] = LoadGraph("dat/img/menu/round3.png");
	graph_load_graph();
	img_menu[4][3] = LoadGraph("dat/img/menu/round4.png");
	graph_load_graph();
	img_menu[4][4] = LoadGraph("dat/img/menu/round5.png");
	graph_load_graph();
	img_menu[4][5] = LoadGraph("dat/img/menu/round6.png");
	graph_load_graph();
	img_menu[4][6] = LoadGraph("dat/img/menu/round7.png");
	graph_load_graph();
	for (int i=0;i<2;i++) {
		for (int j=0;j<4;j++) {
			GetGraphSize(img_back[i][j],&img_back_s[i][j][0],&img_back_s[i][j][1]);
		}
	}
	graph_load_graph();
}

void load_sound() {
	se_handle[0] = LoadSoundMem("dat/se/new_block_small.wav") ;
	graph_load_graph();
	se_handle[1] = LoadSoundMem("dat/se/1line.wav") ;
	graph_load_graph();
	se_handle[2] = LoadSoundMem("dat/se/2_3line.wav") ;
	graph_load_graph();
	se_handle[3] = LoadSoundMem("dat/se/4line.wav") ;
	graph_load_graph();
	se_handle[4] = LoadSoundMem("dat/se/boss_death.wav") ;
	graph_load_graph();
	se_handle[5] = LoadSoundMem("dat/se/all_clear.mp3") ;
	graph_load_graph();
	se_handle[6] = LoadSoundMem("dat/se/firework1.wav") ;
	graph_load_graph();
	se_handle[7] = LoadSoundMem("dat/se/firework2.wav") ;
	graph_load_graph();
	se_handle[8] = LoadSoundMem("dat/se/firework3.mp3") ;
	graph_load_graph();
	se_handle[9] = LoadSoundMem("dat/se/firework4.mp3") ;
	graph_load_graph();
	bgm_handle[0] = LoadSoundMem("dat/music/normal.mp3") ;
	graph_load_graph();
}

void load_block() {
	char string[256];
	char filename[256];
	//char str[16];
	int file;
	int i,j,k,x,y,col;
	int ax,ay,bx,by;
	int touch_cnt;
	int n_cnt;
	int flag=0;
	int map[10][10];
	int confirm;

	for (i=0;i<1000;i++) {

		sprintf(filename,"dat/csv/block/%03d.txt",i);
		if ( (file=FileRead_open(filename)) == 0 ) break;

		if ( FileRead_scanf(file,"%d %d %d",&x,&y,&col) == -1 ) {
			printfDx("Read error:block %d:first line\n", i);
			break;
		}

		n_cnt=0;
		flag=0;
		
		block[i].x=x;
		block[i].y=y;
		block[i].col=col;
		
		//printfDx("%d %d %d\n",x,y,col);
		FileRead_gets( string, sizeof(string), file ) ;

		for (j=0;j<y && flag==0;j++) {

			FileRead_gets( string, sizeof(string), file ) ;
			//printfDx("%s\n",string);

			for (k=0;k<x && flag==0;k++) {

				switch(string[k]) {
				case '*':
					block[i].p[n_cnt].x=k;
					block[i].p[n_cnt].y=j;
					n_cnt++;
					break;
				case ' ':
					break;
				default:
					printfDx("Read error:block No%d :%d %d:%c \n",i,j,k,string[k]);
					flag=1;
					break;
				}

			}

		}
		
		block[i].n=n_cnt;

		FileRead_close(file);

		touch_cnt=0;

		for (j=0;j<n_cnt;j++) {
			
			ax=block[i].p[j].x;
			ay=block[i].p[j].y;

			for (k=0;k<n_cnt;k++) {
				if (j!=k) {
					
					bx=block[i].p[k].x;
					by=block[i].p[k].y;

					if ((ax==bx && ay-by==1) ||
						(ax==bx && ay-by==-1) ||
						(ax-bx==1 && ay==by) ||
						(ax-bx==-1 && ay==by)) touch_cnt++;
				}
			}
		}

		block[i].surface=block[i].n*4-touch_cnt;

		confirm=0;
			
		for (j=0;j<block[i].x;j++) {
			for (k=0;k<block[i].y;k++) {
				map[j][k]=0;
			}
		}
		for (j=0;j<block[i].n;j++) map[block[i].p[j].x][block[i].p[j].y]=1;

		if (block[i].x==block[i].y) {

			flag=0;

			for (j=0 ; j<block[i].x && flag==0 ; j++) {
				for (k=0 ; k<block[i].y && flag==0 ; k++) {
					if (map[j][k] != map[block[i].x-1-k][j]) {
						flag=1;
					}
				}
			}

			if (flag==0) {
				confirm=1;
				block[i].type=1;
			}

		}

		if (confirm==0) {
			
			flag=0;

			for (j=0 ; j<block[i].x && flag==0 ; j++) {
				for (k=0 ; k<block[i].y && flag==0 ; k++) {
					if (map[j][k] != map[block[i].x-1-j][block[i].y-1-k]) {
						flag=1;
					}
				}
			}

			if (flag==0) {
				block[i].type=2;
			} else {
				block[i].type=0;
			}

			confirm=1;

		}

		graph_load_graph();
	}

	block_kinds=i;

}

void load_app() {
	int file;
	int i,b_cnt,flag;
	int num;
	char string[256];
	char input;

	if ((file=FileRead_open("dat/csv/appearenceH0.csv"))==0) {
		printfDx("Read error:appearenceH0.csv\n");
		return;
	}

	b_cnt=0;
	num=0;
	flag=0;
	while(FileRead_eof(file)==0) {

		if (flag==1) {
			b_cnt++;
			num=0;
			flag=0;
		}

		for( i=0 ; i < sizeof(string)/sizeof(char) ; i++ ){
			input=string[i]=FileRead_getc(file);
			//printfDx("%c",input);
			if (input=='/') {
				while(FileRead_getc(file)!='\n');
				i=-1;
				continue;
			}
			if (input==',') {
				string[i]='\0';
				break;
			}
			if (input=='\n') {
				flag=1;
				string[i]='\0';
				break;
			}
			if (FileRead_eof(file)!=0) {
				FileRead_close(file);
				return;
			}
		}

		if (num>=2) {
			app_list[num-2][b_cnt]=atof(string);
			/*for(i=0;i<strlen(string);i++) {
				printfDx("%c",string[i]);
			}*/
			//printfDx(" %s %d\n",string,atoi(string));
			//printfDx("%d app is %d\n",b_cnt,(int)block[b_cnt].app);
		}

		num++;
	}
	
	graph_load_graph();

	FileRead_close(file);
}

void load(){
	load_graph();
	load_sound();
	load_block();
	load_app();
	//Sleep(100000);
}
