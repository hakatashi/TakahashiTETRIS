#include "../include/GV.h"
#include <math.h>

void graph_string(int Pl_n,int x,int y,int kind,char *string) {
	int i,length,num;
	length=strlen(string);
	GetGraphSize(img_char[kind][1][0],&temp[0],&temp[1]);
	for (i=0;i<length;i++) {
		if ((num=char_to_num(string[i]))!=-1) {
			DrawGraph(Pl[Pl_n].screen_x_d+x+i*temp[0],Pl[Pl_n].screen_y_d+y,img_char[kind][1][num],TRUE);
		}
	}
}

int get_graph_string_width(int kind,char *string) {
	int length;
	length=strlen(string);
	GetGraphSize(img_char[kind][1][0],&temp[0],&temp[1]);
	return length*temp[0];
}

void graph_string_slim(int Pl_n,int x,int y,int kind,int slim,char *string) {
	int i,length,num;
	length=strlen(string);
	GetGraphSize(img_char[kind][1][0],&temp[0],&temp[1]);
	for (i=0;i<length;i++) {
		if ((num=char_to_num(string[i]))!=-1) {
			DrawGraph(Pl[Pl_n].screen_x_d+x+i*temp[0]-slim*i,Pl[Pl_n].screen_y_d+y,img_char[kind][1][num],TRUE);
		}
	}
}

int get_graph_string_slim_width(int kind,int slim,char *string) {
	int length;
	length=strlen(string);
	GetGraphSize(img_char[kind][1][0],&temp[0],&temp[1]);
	return length*temp[0]-slim*length;
}

void graph_string_slim_menu(int x,int y,int kind,int slim,char *string) {
	int i,length,num;
	length=strlen(string);
	GetGraphSize(img_char[kind][1][0],&temp[0],&temp[1]);
	for (i=0;i<length;i++) {
		if ((num=char_to_num(string[i]))!=-1) {
			DrawGraph(x+i*temp[0]-slim*i,y,img_char[kind][1][num],TRUE);
		}
	}
}

void graph_char(int Pl_n,int x,int y,int kind,char chara) {
	int num;
	if ((num=char_to_num(chara))!=-1) {
		DrawGraph(Pl[Pl_n].screen_x_d+x,Pl[Pl_n].screen_y_d+y,img_char[kind][1][num],TRUE);
	}
}

int get_graph_char_width(int kind) {
	GetGraphSize(img_char[kind][1][0],&temp[0],&temp[1]);
	return temp[0];
}

void graph_char_ex(int Pl_n,int x1,int y1,int x2,int y2,int kind,char chara) {
	GetGraphSize(img_char[kind][0][0],&temp[0],&temp[1]);
	if (y1==-1) y1=(int)(y2-((double)x2-(double)x1)/(double)temp[0]*(double)temp[1]);
	else if (y2==-1) y2=(int)(y1+((double)x2-(double)x1)/(double)temp[0]*(double)temp[1]);
	DrawExtendGraph( Pl[Pl_n].screen_x_d+x1, Pl[Pl_n].screen_y_d+y1,
		Pl[Pl_n].screen_x_d+x2, Pl[Pl_n].screen_y_d+y2,
		img_char[kind][0][char_to_num(chara)] , TRUE );
}

void graph_number(int x,int y,int number,int figure) {
	int i;
	GetGraphSize(img_char[3][1][0],&temp[0],&temp[1]);
	if (figure==0) {
	} else {
		for (i=0;i<figure;i++) {
			DrawGraph(x+(figure-i-1)*(temp[0]-4)-2,y,img_char[3][1][number%10+52],TRUE);
			number=(int)(number/10);
		}
	}
}

int get_graph_number_width(int figure) {
	GetGraphSize(img_char[3][1][0],&temp[0],&temp[1]);
	return figure*(temp[0]-4)+2;
}

void graph_ghost(int Pl_n) {
	int j;
	int nx,ny;
	int img_n;

	block_point n_block[BLOCK_MAX];

	if (Pl[Pl_n].block.flag==1) {
			
		turn_cal(Pl[Pl_n].block.kind,Pl[Pl_n].block.angle,n_block);

		for (j=0;j<block[Pl[Pl_n].block.kind].n;j++) {
			nx=(int)(Pl[Pl_n].block.gx+n_block[j].x);
			ny=(int)((int)(Pl[Pl_n].block.gy)+n_block[j].y+Pl[Pl_n].ghost_down);

			DrawGraph(
				Pl[Pl_n].screen_x+BLOCK_SIZE*nx,
				Pl[Pl_n].screen_y+BLOCK_SIZE*ny,
				img_ghost[block[Pl[Pl_n].block.kind].col],
				FALSE);

		}
	}
}

void graph_board_block(int Pl_n) {
	int i,j;
	int img_n;
	for (i=0;i<BOARD_X_MAX;i++) {
		for (j=0;j<BOARD_Y_MAX;j++) {
			if (Pl[Pl_n].board[i][j]!=0) {
				DrawRotaGraph(
					Pl[Pl_n].screen_x+BLOCK_SIZE*i+BLOCK_SIZE/2.0,
					Pl[Pl_n].screen_y+BLOCK_SIZE*j+BLOCK_SIZE/2.0,
					1.0,
					PI/2.0f*Pl[Pl_n].board_angle[i][j],
					img_bl[block[Pl[Pl_n].board[i][j]-1].col],
					FALSE,
					FALSE);
			} else {
				//DrawGraph(20*i,20*j,img_bl[7],FALSE);
			}
			//DrawFormatString(20*i,20*j,GetColor(255,255,255),"%d\n",board[i][j]);
		}
	}
}

void graph_board(int Pl_n){
	int i,j;
	int img_n,col;
	int flag;
	int imgx,imgy;
	int speed;

	switch (Pl[Pl_n].cpu_flag) {
	case 0:
		speed=20;
		break;
	case 1:
		if (Pl[Pl_n].cpu_mode.difficalty==3) speed=5;
		else if (Pl[Pl_n].cpu_mode.difficalty==4) speed=5;
		else speed=20;
		break;
	}

	if (Pl[Pl_n].pause_flag==0) {
		graph_board_block(Pl_n);
		if (Pl[Pl_n].cpu_mode.difficalty==4) {
			if (Pl[Pl_n].pause_cnt<speed) {
				col=(int)(256.0/(double)speed*((double)speed-Pl[Pl_n].pause_cnt));
				SetDrawBlendMode( DX_BLENDMODE_ADD , col );
				for (i=0;i<BOARD_Y_MAX && Pl[Pl_n].dis_line_n[i]!=99;i++) {
					DrawBox(
						Pl[Pl_n].screen_x+0 ,
						Pl[Pl_n].screen_y+BLOCK_SIZE*Pl[Pl_n].dis_line_n[i] ,
						Pl[Pl_n].screen_x+BLOCK_SIZE*BOARD_X_MAX ,
						Pl[Pl_n].screen_y+BLOCK_SIZE*(Pl[Pl_n].dis_line_n[i]+1) ,
						GetColor(255,255,255) ,
						TRUE );
				}
				SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
			} else {
				for (i=0;i<BOARD_Y_MAX;i++) {Pl[Pl_n].dis_line_n[i]=100;}
			}
		}
	} else if (Pl[Pl_n].pause_flag==1) {
		graph_board_block(Pl_n);
	} else if (Pl[Pl_n].pause_flag==2) {
		graph_board_block(Pl_n);
	} else if (Pl[Pl_n].pause_flag==3) {
		for (i=0;i<BOARD_X_MAX;i++) {
			for (j=0;j<BOARD_Y_MAX;j++) {
				if (Pl[Pl_n].board[i][j]!=0) {
					DrawRotaGraph(
						Pl[Pl_n].screen_x+BLOCK_SIZE*i+BLOCK_SIZE/2.0,
						Pl[Pl_n].screen_y+BLOCK_SIZE*j-Pl[Pl_n].block_fall[i][j].plus_y+BLOCK_SIZE/2.0,
						1.0,
						PI/2.0f*Pl[Pl_n].board_angle[i][j],
						img_bl[block[Pl[Pl_n].board[i][j]-1].col],
						FALSE,
						FALSE);
				}
			}
		}
		if (Pl[Pl_n].pause_cnt<speed) {
			col=(int)(256.0/(double)speed*((double)speed-Pl[Pl_n].pause_cnt));
			SetDrawBlendMode( DX_BLENDMODE_ADD , col );
			for (i=0;i<BOARD_Y_MAX && Pl[Pl_n].dis_line_n[i]!=99;i++) {
				DrawBox(
					Pl[Pl_n].screen_x+0 ,
					Pl[Pl_n].screen_y+BLOCK_SIZE*Pl[Pl_n].dis_line_n[i] ,
					Pl[Pl_n].screen_x+BLOCK_SIZE*BOARD_X_MAX ,
					Pl[Pl_n].screen_y+BLOCK_SIZE*(Pl[Pl_n].dis_line_n[i]+1) ,
					GetColor(255,255,255) ,
					TRUE );
			}
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
		} else {
			flag=0;
			for (i=0;i<BOARD_X_MAX;i++) {
				for (j=0;j<BOARD_Y_MAX;j++) {
					Pl[Pl_n].block_fall[i][j].v+=2.0/(double)speed;
					Pl[Pl_n].block_fall[i][j].plus_y-=Pl[Pl_n].block_fall[i][j].v;
					if (Pl[Pl_n].block_fall[i][j].plus_y<=0) {
						Pl[Pl_n].block_fall[i][j].plus_y=0;
						Pl[Pl_n].block_fall[i][j].v=0;
					}
					if (Pl[Pl_n].block_fall[i][j].plus_y>0) flag=1;
				}
			}
			if (flag==0) {
				Pl[Pl_n].pause_flag=0;
				for (i=0;i<BOARD_Y_MAX;i++) {Pl[Pl_n].dis_line_n[i]=100;}
			}
		}
	}
}

void graph_block(int Pl_n) {
	int j;
	int img_n;
	double cent_x,cent_y;
	double rel_x,rel_y,angle;
	char string[64];
	//block_point n_block[BLOCK_MAX];

	SetDrawMode( DX_DRAWMODE_BILINEAR ) ;

	if (Pl[Pl_n].block.flag==1) {

		cent_x=Pl[Pl_n].block.x +
				(Pl[Pl_n].block.b_cent_x * Pl[Pl_n].block.angle_rate
				+ cent_point_cal_x(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle) * (1.0-Pl[Pl_n].block.angle_rate))
				* BLOCK_SIZE;
		cent_y=Pl[Pl_n].block.y + 
				(Pl[Pl_n].block.b_cent_y * Pl[Pl_n].block.angle_rate
				+ cent_point_cal_y(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle) * (1.0-Pl[Pl_n].block.angle_rate))
				* BLOCK_SIZE;
		angle=(Pl[Pl_n].block.b_angle * Pl[Pl_n].block.angle_rate + Pl[Pl_n].block.angle * (1.0-Pl[Pl_n].block.angle_rate))*PI/2.0;
			
		//turn_cal(Pl[Pl_n].block.kind,Pl[Pl_n].block.angle,n_block);

		for (j=0;j<block[Pl[Pl_n].block.kind].n;j++) {
			//DrawFormatString(300,80,GetColor(255,255,255),"%d\n",Pl[Pl_n].block.angle);
			//DrawGraph(300+20*n_block[j].x,40+20*n_block[j].y,img_bl[Pl[Pl_n].block.kind],FALSE);

			rel_x=(block[Pl[Pl_n].block.kind].p[j].x-block[Pl[Pl_n].block.kind].x/2.0+0.5)*BLOCK_SIZE;
			rel_y=(block[Pl[Pl_n].block.kind].p[j].y-block[Pl[Pl_n].block.kind].y/2.0+0.5)*BLOCK_SIZE;

			DrawRotaGraphF(
				Pl[Pl_n].screen_x
				+ cent_x
					+ rel_x * cos(angle)
					- rel_y * sin(angle),
				Pl[Pl_n].screen_y
				+ cent_y
					+ rel_x * sin(angle)
					+ rel_y * cos(angle),
				1.0, angle,
				img_bl[block[Pl[Pl_n].block.kind].col] , FALSE , FALSE ) ;

			/*DrawFormatString(
				cent_x
					+ rel_x * cos(angle)
					- rel_y * sin(angle),
				cent_y
					+ rel_x * sin(angle)
					+ rel_y * cos(angle),GetColor(255,255,255),"%d\n",Pl[Pl_n].block.kind);*/
		}
		//sprintf(string,"%d",Pl[Pl_n].block.wait);
		//DrawString(Pl[Pl_n].screen_x+cent_x,Pl[Pl_n].screen_y+cent_y,string,GetColor(0,0,0));
		//DrawCircle(cent_x,cent_y,3,GetColor(0,0,0),TRUE) ;
		//DrawCircle(Pl[Pl_n].block.x,Pl[Pl_n].block.y,3,GetColor(255,0,0),TRUE) ;

	}
	SetDrawMode( DX_DRAWMODE_NEAREST ) ;
}

void graph_sheet() {
	if (Pl_num==1) {
		DrawGraph(0,0,img_sheet[0],FALSE);
		DrawGraph(220,440,img_sheet[1],FALSE);
		DrawGraph(420,0,img_sheet[3],FALSE);
		DrawGraph(220,0,img_sheet[2],FALSE);
	} else if (Pl_num==2) {
		DrawGraph(0,0,img_sheet[4],FALSE);
	}
	//for (int i=0;i<22;i++) DrawFormatString(0,20*i,GetColor(0,0,0),"%d %f",i,block[i].app);
}

void graph_next(){
	int i,j,k;
	int sep;
	int img_n;
	double startx,starty;
	double gx,gy,size,bsize;
	
	SetDrawMode( DX_DRAWMODE_BILINEAR ) ;

	for (k=0;k<Pl_num;k++) {
		for (i=0;i<6;i++) {

			if (block[Pl[k].next[i]].x >= block[Pl[k].next[i]].y) {
				sep=block[Pl[k].next[i]].x;
				startx=0.0;
				starty=( block[Pl[k].next[i]].x - block[Pl[k].next[i]].y ) / 2.0;
			} else {
				sep=block[Pl[k].next[i]].y;
				startx=( block[Pl[k].next[i]].y - block[Pl[k].next[i]].x ) / 2.0;
				starty=0;
			}

			if (sep<=2) {
				sep=3;
				startx=(3-block[Pl[k].next[i]].x) / 2.0;
				starty=(3-block[Pl[k].next[i]].y) / 2.0;
			}
		
			if (Pl_num==1) {
				if (i==0) {
					size=66.0+sin(PI/180.0*stage_cnt*12.0)*7.0;
					gx=456.0-size/2.0;
					gy=75.0-size/2.0;
				}
				if (1<=i && i<=5) {
					size=39;
					gx=423;
					gy=115+45*(i-1);
				}
			} else if (Pl_num==2) {
				if (i==0) {
					size=54.0+sin(PI/180.0*stage_cnt*12.0)*7.0;
					gx=165.0-size/2.0;
					gy=41.0-size/2.0;
				} else if (i==1) {
					size=39;
					gx=198;
					gy=28;
				} else if (2<=i && i<=4) {
					size=39;
					gx=243;
					gy=28+45*(i-2);
				} else break;

				if (k==1) gx+=310;
			} else break;

			bsize = size/(double)sep;

			for (j=0;j<block[Pl[k].next[i]].n;j++) {
				DrawExtendGraphF(
					gx + (block[Pl[k].next[i]].p[j].x+startx)*bsize,
					gy + (block[Pl[k].next[i]].p[j].y+starty)*bsize,
					gx + (block[Pl[k].next[i]].p[j].x+startx+1)*bsize,
					gy + (block[Pl[k].next[i]].p[j].y+starty+1)*bsize,
					img_bl[block[Pl[k].next[i]].col],
					FALSE);
			}
		}

		if (Pl[k].hold != 0) {

			if (block[Pl[k].hold-1].x >= block[Pl[k].hold-1].y) {
				sep=block[Pl[k].hold-1].x;
				startx=0.0;
				starty=( block[Pl[k].hold-1].x - block[Pl[k].hold-1].y ) / 2.0;
			} else {
				sep=block[Pl[k].hold-1].y;
				startx=( block[Pl[k].hold-1].y - block[Pl[k].hold-1].x ) / 2.0;
				starty=0.0;
			}

			if (sep<=2) {
				sep=3;
				startx=(3-block[Pl[k].hold-1].x) / 2.0;
				starty=(3-block[Pl[k].hold-1].y) / 2.0;
			}
		
			if (Pl_num==1) {
				if (Pl[k].hold_cnt<10) size=66.0/10.0*(Pl[k].hold_cnt+1);
				else size=66.0;
				gx=184.0-size/2.0;
				gy=75.0-size/2.0;
			} else if (Pl_num==2) {
				if (Pl[k].hold_cnt<10) size=54.0/10.0*(Pl[k].hold_cnt+1);
				else size=54.0;
				gx=70.0-size/2.0;
				gy=40.0-size/2.0;

				if (k==1) gx+=310;
			}
		
			bsize = size/(double)sep;

			for (j=0;j<block[Pl[k].hold-1].n;j++) {
				DrawExtendGraphF(
					gx + (block[Pl[k].hold-1].p[j].x+startx)*bsize,
					gy + (block[Pl[k].hold-1].p[j].y+starty)*bsize,
					gx + (block[Pl[k].hold-1].p[j].x+startx+1)*bsize,
					gy + (block[Pl[k].hold-1].p[j].y+starty+1)*bsize,
					img_bl[block[Pl[k].hold-1].col],
					FALSE);
			}

			Pl[k].hold_cnt++;
		}

	}

	SetDrawMode( DX_DRAWMODE_NEAREST ) ;
}

void graph_point() {
	int i;
	//DrawFormatString( 640 - GetDrawFormatStringWidth( "%d", line), 160, GetColor(255,255,255), "%d", line) ;
	if (Pl_num==1) {
		graph_number(640-get_graph_number_width(10),63,(int)Pl[0].n_score,10);
		graph_number(640-get_graph_number_width(4),160,Pl[0].line,4);
		graph_number(640-get_graph_number_width(4),180,Pl[0].block_num,4);
	} else if (Pl_num==2) {
		for (i=0;i<2;i++) {
			graph_number(195+i*310,0,(int)Pl[i].n_score,8);
			graph_number(240-get_graph_number_width(4)+i*310,70,Pl[i].line,4);
			graph_number(240-get_graph_number_width(4)+i*310,90,Pl[i].block_num,4);
		}
	}
	//DrawFormatString( 640 - GetDrawFormatStringWidth( "%d", score), 70, GetColor(0,255,255), "%d", score) ;
}

void graph_gameover(int Pl_n) {
	int i,j;
	int imgx,imgy;
	SetDrawMode( DX_DRAWMODE_BILINEAR ) ;
	if (Pl[Pl_n].pause_cnt<=5) {
		GetGraphSize( img_game , &imgx , &imgy ) ;
		DrawExtendGraphF(
			Pl[Pl_n].gameover_x-imgx*(5-Pl[Pl_n].pause_cnt),
			180-imgy*(5-Pl[Pl_n].pause_cnt),
			Pl[Pl_n].gameover_x+imgx*(6-Pl[Pl_n].pause_cnt),
			180+imgy*(6-Pl[Pl_n].pause_cnt),
			img_game,
			TRUE);
	} else {
		DrawGraphF((float)Pl[Pl_n].gameover_x-110.0f+sin(PI/180.0f*(float)Pl[Pl_n].pause_cnt/1.5f)*40.0f,180.0f,img_game,TRUE) ;
	}

	if (Pl[Pl_n].pause_cnt<10);
	else if (Pl[Pl_n].pause_cnt>=10 && Pl[Pl_n].pause_cnt<=15) {
		GetGraphSize( img_over , &imgx , &imgy ) ;
		DrawExtendGraphF(
			Pl[Pl_n].gameover_x-imgx*(5-(Pl[Pl_n].pause_cnt-10)),
			240-imgy*(5-(Pl[Pl_n].pause_cnt-10)),
			Pl[Pl_n].gameover_x+imgx*(6-(Pl[Pl_n].pause_cnt-10)),
			240+imgy*(6-(Pl[Pl_n].pause_cnt-10)),
			img_over,
			TRUE);
	} else {
		DrawGraphF((float)((float)Pl[Pl_n].gameover_x-90.0f-sin(PI/180.0f*(float)Pl[Pl_n].pause_cnt/1.5f)*40.0f),240.0f,img_over,TRUE) ;
	}
	SetDrawMode( DX_DRAWMODE_NEAREST ) ;
}

void graph_result_strings() {
	int i,j;
	char str[128];
	
	for (j=0;j<Pl_num;j++) {
		for (i=0;i<20;i++) {

			switch(i) {
			case 0:
				sprintf(str,"プレイ時間 %02d:%02d:%05.2f",
					Pl[j].playtime_cnt/3600000,
					Pl[j].playtime_cnt%3600000/60000,
					Pl[j].playtime_cnt%60000/1000.0);
				break;
			case 1:
				sprintf(str,"シングル    %d",Pl[j].dis_line_times[0]);
				break;
			case 2:
				sprintf(str,"ダブル      %d",Pl[j].dis_line_times[1]);
				break;
			case 3:
				sprintf(str,"トリプル    %d",Pl[j].dis_line_times[2]);
				break;
			case 4:
				sprintf(str,"テトリス    %d",Pl[j].dis_line_times[3]);
				break;
			case 5:
				sprintf(str,"SCORE    %d",Pl[j].score);
				break;
			case 6:
				sprintf(str,"LINE    %d",Pl[j].line);
				break;
			case 7:
				sprintf(str,"BLOCK    %d",Pl[j].block_num);
				break;
			case 8:
				sprintf(str,"DROP    %.1f",Pl[j].dropline);
				break;
			case 9:
				sprintf(str,"HARDDROP    %.1f",Pl[j].harddropline);
				break;
			default:
				strcpy(str,"--------");
				break;
			}

			DrawString(Pl[j].screen_x_d,result_score_y[i],str,GetColor(255,255,255));

		}
	}
}

void graph_masking() {
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (result_cnt<60)?((int)(100.0/60.0*result_cnt)):100 );
	DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
}

void graph_over_select_button() {
	int i,j;
	for (j=0;j<Pl_num;j++) {
		for (i=0;i<4;i++) {
			GetGraphSize(img_over_select[0][i],&temp[0],&temp[1]);
			if (i==over_select) DrawGraph(Pl[j].screen_x_de-temp[0]-5,over_select_y[i],img_over_select[1][i],TRUE);
			else DrawGraph(Pl[j].screen_x_de-temp[0]-5,over_select_y[i],img_over_select[0][i],TRUE);
		}
	}
}

void graph_game_pause_button() {
	int i;
	int s;
	int img_h;
	for (i=0;i<4;i++) {
		if (i==0) img_h=img_pause;
		if (i==pause_select+1) s=1; else s=0;
		if (i==1) img_h=img_over_select[s][5];
		if (i==2) img_h=img_over_select[s][4];
		if (i==3) img_h=img_over_select[s][1];
		GetGraphSize(img_h,&temp[0],&temp[1]);
		DrawGraph(Pl[pause_push_Pl].screen_x_de-temp[0]-5,pause_button_y[i],img_h,TRUE);
	}
}

void graph_result_over() {
	graph_masking();
	graph_result_strings();
	graph_over_select_button();

	if (Pl_num==1) DrawGraph(result_x,200,img_result,TRUE);
}

void graph_game_pause() {
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)pause_blend );
	DrawBox(0,0,640,480,GetColor(0,0,0),TRUE);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
	graph_game_pause_button();
}

void graph_speedup_effect() {
	double size,alpha;
	int col;
	char str[128];

	if (SpeedupEffectFlag>0) {

		size=0;
		if (SpeedupEffectFlag<=3) {
			size=1.0+1.0/3.0*(3-SpeedupEffectFlag);
			alpha=255.0/3.0*SpeedupEffectFlag;
		} else if (SpeedupEffectFlag<=40) {
			size=1.0+0.2/37.0*(SpeedupEffectFlag-3);
			alpha=255;
		} else if (SpeedupEffectFlag<=50) {
			size=1.2+2.5/10.0*(SpeedupEffectFlag-40);
			alpha=255.0/10.0*(50-SpeedupEffectFlag);
		}

		if (size>0) {
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(alpha) );
			GetGraphSize( img_effect[1][0] , &temp[0] , &temp[1] ) ;
			DrawExtendGraph( 320-temp[0]/2.0*size, 200-temp[1]/2.0*size, 320+temp[0]/2.0*size, 200+temp[1]/2.0*size, img_effect[1][0] , TRUE ) ;
			sprintf(str,"NEW SPEED : %3.2fG", SpeedupEffectState[1]);
			if (stage_cnt/10%2==0) col=1;
			else col=2;
			temp[3]=get_graph_string_slim_width(col,2,str);
			graph_string_slim_menu(320-temp[3]/2.0, 240, col, 2, str);
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 );
		}
	}
}

void graph_main(){
	graph_sheet();
	for (int i=0;i<Pl_num;i++) {
		SetDrawArea( Pl[i].screen_x_d , Pl[i].screen_y_d ,
			Pl[i].screen_x_de , Pl[i].screen_y_de );
		graph_back(i);
		graph_ghost(i);
		graph_block(i);
		graph_board(i);
		if (Pl[i].pause_flag==1) graph_gameover(i);
	}
	SetDrawArea(0,0,640,480);
	graph_next();
	graph_point();
	graph_speedup_effect();
	graph_game_pause();
	if (func_state==101 || func_state==102) {
		graph_result_over();
		result_cnt++;
	}
}