#include "../include/GV.h"
#include <math.h>

void graph_back_effect_DisLine(int Pl_n) {
	int i,j,k,width,cnt,time,col,base;
	int size_x,size_y,apptime;
	char string[16];
	for (j=0;j<EFFECT_SET_MAX;j++) {
		//1～3列
		for (i=0;i<3;i++) {
			cnt=Pl[Pl_n].effect_flag[EFFECT_DISLINE+i][j];

			if (cnt==1) {
				for (k=0;k<20;k++) {
					Pl[Pl_n].effect_state[EFFECT_DISLINE+i][j][k]=2.5f+GetRand(400)/1000.0f;
				}
			}

			if (cnt>0 && cnt<=100) {

				switch(i) {
				case 0:
					strcpy(string,"SINGLE");
					break;
				case 1:
					strcpy(string,"DOUBLE");
					break;
				case 2:
					strcpy(string,"TRIPLE");
					break;
				}

				width=get_graph_char_width(1);
				time=strlen(string);
				if (i==0) col=1;
				else if (i==1) col=3;
				else col=2;

				SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(256.0/100.0*(100-cnt)) );
				for (k=0;k<time;k++) {
					graph_char(
						Pl_n,
						BOARD_X_MAX*BLOCK_SIZE/2+(-time/2.0f+k)*width,
						(BOARD_Y_MAX-10)*BLOCK_SIZE/2*1.2f-Pl[Pl_n].effect_state[EFFECT_DISLINE+i][j][k]*cnt,
						col,
						string[k]);
					if (j==3) {
						j=j;
					}
				}
				//graph_string(BOARD_X_MAX*BLOCK_SIZE/2-width/2,(BOARD_Y_MAX-10)*BLOCK_SIZE/2,1,string);
				SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

			}
		}
		//4～10列
		for (i=3;i<10;i++) {
			cnt=Pl[Pl_n].effect_flag[EFFECT_DISLINE+i][j];

			switch(i) {
			case 3:
				strcpy(string,"TETRIS");
				break;
			case 4:
				strcpy(string,"PENTRIS");
				break;
			case 5:
				strcpy(string,"HEXORIS");
				break;
			case 6:
				strcpy(string,"SEPTRIS");
				break;
			case 7:
				strcpy(string,"OCTRIS");
				break;
			case 8:
				strcpy(string,"NONARIS");
				break;
			case 9:
				strcpy(string,"DECARIS");
				break;
			}

			time=strlen(string);
			
			if (cnt>0 && cnt<=160) {
				base=(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f*1.2f-cnt/2.0f;

				GetGraphSize(img_char[1][0][0],&temp[0],&temp[1]);

				size_x=BOARD_X_MAX*BLOCK_SIZE/(double)time;
				size_y=size_x/(double)temp[0]*(double)temp[1];

				//SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(256.0/100.0*(100-effect_flag[EFFECT_DISLINE+i][j])) );
				for (k=0;k<time;k++) {
					apptime=k*5;
					if (cnt>apptime+0 && cnt<=apptime+5) {
						temp[3]=(double)BOARD_Y_MAX*(double)BLOCK_SIZE/2.0f;
						temp[4]=temp[3]/5.0f*(5-(cnt-apptime));
						temp[2]=temp[4]*((k%2)?(-1):(1));
						graph_char_ex(
							Pl_n,
							size_x*k,
							base+temp[2],
							size_x*(k+1),
							base+temp[2]+size_y,
							/*BOARD_X_MAX*BLOCK_SIZE/time*k,
							base+BOARD_Y_MAX*BLOCK_SIZE/2.0f/5.0f*(5-(cnt-k*10))*(k%2)?-1:1,
							BOARD_X_MAX*BLOCK_SIZE/time*(k+1),
							base+BOARD_Y_MAX*BLOCK_SIZE/2.0f/5.0f*(5-(cnt-k*10))*(k%2)?-1:1+
								BOARD_X_MAX*BLOCK_SIZE/(double)time/(double)temp[0]*(double)temp[1],*/
							1,
							string[k]);
					} else if (cnt>apptime+5 && cnt<=apptime+20) {
						graph_char_ex(
							Pl_n,
							size_x*k,
							base,
							size_x*(k+1),
							base+size_y,
							1,
							string[k]);
					} else if (cnt>apptime+20 && cnt<=apptime+30) {
						graph_char_ex(
							Pl_n,
							size_x*k,
							base-40/10*(10-(cnt-apptime-20)),
							size_x*(k+1),
							base+size_y,
							2,
							string[k]);
					} else if (cnt>apptime+30) {
						graph_char_ex(
							Pl_n,
							size_x*k,
							base,
							size_x*(k+1),
							base+size_y,
							2,
							string[k]);
					}
				}
				//graph_string(BOARD_X_MAX*BLOCK_SIZE/2-width/2,(BOARD_Y_MAX-10)*BLOCK_SIZE/2,1,string);
				//SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

			} else if (cnt<=200) {
				base=(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f*1.2f-cnt/2.0f-(cnt-160)*(cnt-160)/2.0f;

				GetGraphSize(img_char[1][0][0],&temp[0],&temp[1]);

				size_x=BOARD_X_MAX*BLOCK_SIZE/(double)time;
				size_y=size_x/(double)temp[0]*(double)temp[1];

				for (k=0;k<time;k++) {
					graph_char_ex(
						Pl_n,
						size_x*k,
						base,
						size_x*(k+1),
						base+size_y,
						2,
						string[k]);
				}
			}
		}

		cnt=Pl[Pl_n].effect_flag[EFFECT_DISLINE+i][j];

	}
}

void graph_back_effect_AllClear(int Pl_n) {
	int i,j,k,cnt;
	char string[8];
	for (i=0;i<EFFECT_SET_MAX;i++) {
		cnt=Pl[Pl_n].effect_flag[EFFECT_ALLCLEAR][i];
		if (cnt==0) ;
		else if (cnt<=10) {
			graph_char_ex(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-50,
				-1,
				BOARD_X_MAX*BLOCK_SIZE/2.0f+50,
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f*(1.0f/10.0f*cnt),
				3,
				'A');
			graph_char_ex(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-50,
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f*(2.0f-1.0f/10.0f*cnt),
				BOARD_X_MAX*BLOCK_SIZE/2.0f+50,
				-1,
				3,
				'C');
		} else if (cnt<=60) {
			d_temp[0]=5.0f/50.0f*(cnt-10);
			graph_char_ex(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-50-d_temp[0],
				-1,
				BOARD_X_MAX*BLOCK_SIZE/2.0f+50+d_temp[0],
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f,
				3,
				'A');
			graph_char_ex(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-50-d_temp[0],
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f,
				BOARD_X_MAX*BLOCK_SIZE/2.0f+50+d_temp[0],
				-1,
				3,
				'C');
		} else if (cnt<=120) {
			d_temp[0]=duv_2_p( 110 , BOARD_X_MAX*BLOCK_SIZE/3.0f , cnt-60 , 20 );
			d_temp[1]=duv_2_p( BOARD_X_MAX*BLOCK_SIZE/2.0f-55 , 0 , cnt-60 , 20 );
			graph_char_ex(
				Pl_n,
				d_temp[1],
				-1,
				d_temp[1]+d_temp[0],
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-(cnt-60)/12.0f,
				3,
				'A');
			strcpy(string,"All");
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(256.0f/60.0f*(cnt-60)) );
			for (j=0;j<2;j++) {
				d_temp[2]=duv_2_p( 0 , BOARD_X_MAX*BLOCK_SIZE/3.0f*(j+1) , cnt-60 , 60 );
				graph_char_ex(
					Pl_n,
					d_temp[1]+d_temp[2],
					-1,
					d_temp[1]+d_temp[2]+d_temp[0],
					(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-(cnt-60)/12.0f,
					3,
					string[j+1]);
			}
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

			d_temp[0]=duv_2_p( 110 , BOARD_X_MAX*BLOCK_SIZE/5.0f , cnt-60 , 20 );
			d_temp[1]=duv_2_p( BOARD_X_MAX*BLOCK_SIZE/2.0f-55 , 0 , cnt-60 , 20 );
			graph_char_ex(
				Pl_n,
				d_temp[1],
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f+(cnt-60)/12.0f,
				d_temp[1]+d_temp[0],
				-1,
				3,
				'C');
			strcpy(string,"Clear");
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , (int)(256.0f/60.0f*(cnt-60)) );
			for (j=0;j<4;j++) {
				d_temp[2]=duv_2_p( 0 , BOARD_X_MAX*BLOCK_SIZE/5.0f*(j+1) , cnt-60 , 60 );
				graph_char_ex(
					Pl_n,
					d_temp[1]+d_temp[2],
					(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f+(cnt-60)/12.0f,
					d_temp[1]+d_temp[2]+d_temp[0],
					-1,
					3,
					string[j+1]);
			}
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

			graph_string(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-get_graph_string_width(3,"POINT:x50")/2.0f,
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-10-(cnt-70)/20.0f-(cnt-120)*(cnt-120)/6.0f,
				3,
				"POINT:x50");
		} else if (cnt<=300) {
			d_temp[0]=BOARD_X_MAX*BLOCK_SIZE/3.0f;
			d_temp[1]=0;
			strcpy(string,"All");
			for (j=0;j<3;j++) {
				d_temp[2]=BOARD_X_MAX*BLOCK_SIZE/3.0f*j;
				graph_char_ex(
					Pl_n,
					d_temp[1]+d_temp[2],
					-1,
					d_temp[1]+d_temp[2]+d_temp[0],
					(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-(cnt-60)/12.0f,
					3,
					string[j]);
			}
			d_temp[0]=BOARD_X_MAX*BLOCK_SIZE/5.0f;
			d_temp[1]=0;
			strcpy(string,"Clear");
			for (j=0;j<5;j++) {
				d_temp[2]=BOARD_X_MAX*BLOCK_SIZE/5.0f*j;
				graph_char_ex(
					Pl_n,
					d_temp[1]+d_temp[2],
					(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f+(cnt-60)/12.0f,
					d_temp[1]+d_temp[2]+d_temp[0],
					-1,
					3,
					string[j]);
			}
			graph_string(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-get_graph_string_width(3,"POINT:x50")/2.0f,
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-10-(cnt-70)/20.0f,
				3,
				"POINT:x50");
		} else if (cnt<=400) {
			d_temp[0]=BOARD_X_MAX*BLOCK_SIZE/3.0f;
			d_temp[1]=0;
			strcpy(string,"All");
			for (j=0;j<3;j++) {
				d_temp[2]=BOARD_X_MAX*BLOCK_SIZE/3.0f*j;
				graph_char_ex(
					Pl_n,
					d_temp[1]+d_temp[2],
					-1,
					d_temp[1]+d_temp[2]+d_temp[0],
					(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-(cnt-60)/12.0f
					 -(((cnt-300)<j*10)?(0):((cnt-300-j*10)*(cnt-300-j*10)/3.0f)),
					3,
					string[j]);
			}
			d_temp[0]=BOARD_X_MAX*BLOCK_SIZE/5.0f;
			d_temp[1]=0;
			strcpy(string,"Clear");
			for (j=0;j<5;j++) {
				d_temp[2]=BOARD_X_MAX*BLOCK_SIZE/5.0f*j;
				graph_char_ex(
					Pl_n,
					d_temp[1]+d_temp[2],
					(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f+(cnt-60)/12.0f
					 -(((cnt-300)<(j+3)*10)?(0):((cnt-300-(j+3)*10)*(cnt-300-(j+3)*10)/3.0f)),
					d_temp[1]+d_temp[2]+d_temp[0],
					-1,
					3,
					string[j]);
			}

			graph_string(
				Pl_n,
				BOARD_X_MAX*BLOCK_SIZE/2.0f-get_graph_string_width(3,"POINT:x50")/2.0f,
				(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0f-10-(cnt-70)/20.0f+(cnt-300)*(cnt-300)/6.0f,
				3,
				"POINT:x50");
		}
	}
}

void graph_back_effect_Combo(int Pl_n) {
	int i,state,k,cnt,times,num,base_x;
	int ef_cnt;
	double minus_y;
	double rate;
	float sca;
	char string[64];

	for (i=0;i<EFFECT_SET_MAX;i++) {
		cnt=Pl[Pl_n].effect_flag[EFFECT_COMBO][i];
		state=Pl[Pl_n].effect_state[EFFECT_COMBO][i][0];
		ef_cnt=Pl[Pl_n].effect_state[EFFECT_COMBO][i][1];
		GetGraphSize(img_char[1][0][0],&temp[0],&temp[1]);
		d_temp[0]=BOARD_X_MAX*BLOCK_SIZE/2.0;
		d_temp[1]=(BOARD_Y_MAX-10)*BLOCK_SIZE/2.0;
			
		if (ef_cnt==0) minus_y=0;
		else if (ef_cnt<=15) minus_y=(sin(-PI/2.0+PI/15.0*ef_cnt)+1)/2.0*50;
		else if (ef_cnt<=60) minus_y=50;
		else if (ef_cnt<=75) minus_y=(sin(-PI/2.0+PI/15.0*ef_cnt)+1)/2.0*50+50;

		if (ef_cnt==0) ;
		else if (ef_cnt<=15) SetDrawBlendMode(DX_BLENDMODE_ALPHA,256.0/15.0*(15-ef_cnt));
		else if (ef_cnt<=60) SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);
		else if (ef_cnt<=75) SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);

		if (ef_cnt<=15) {
			if (cnt==0) ;
			else if (cnt<=15) {

				switch ((int)(cnt/5)) {
				case 0:
					sca = -1.0f + (1.5f-(-1.0f)) / 10.0f * (cnt%5);
					break;
				case 1:
					sca =  1.5f +   (-0.5f-1.5f) / 10.0f * (cnt%5);
					break;
				case 2:
					sca = -0.5f + (0.0f-(-0.5f)) / 10.0f * (cnt%5);
					break;
				}

				if (state>=10) times=2; else times=1;
				for (k=0;k<times;k++) {
					if (k==0) num=state%10; else num=(int)(state/10);
					sprintf(string,"%d",num);

					if (state>=10) {
						if (k==0) base_x=temp[0]/2.0;
						else base_x=-temp[0]/2.0;
					} else base_x=0;

					graph_char_ex(
						Pl_n,
						d_temp[0]-temp[0]*(1.0f+sca)/2.0f+base_x,
						d_temp[1]-temp[1]/2.0f-temp[0]*(-sca)/2.0f-minus_y,
						d_temp[0]+temp[0]*(1.0f+sca)/2.0f+base_x,
						d_temp[1]+temp[1]/2.0f+temp[0]*(-sca)/2.0f-minus_y,
						2,
						string[0]);

				}
			} else {
				if (state>=10) times=2; else times=1;
				for (k=0;k<times;k++) {
					if (k==0) num=state%10; else num=(int)(state/10);
					sprintf(string,"%d",num);

					if (state>=10) {
						if (k==0) base_x=temp[0]/2.0;
						else base_x=-temp[0]/2.0;
					} else base_x=0;

					graph_char_ex(
						Pl_n,
						d_temp[0]-temp[0]/2.0f+base_x,
						d_temp[1]-temp[1]/2.0f-minus_y,
						d_temp[0]+temp[0]/2.0f+base_x,
						d_temp[1]+temp[1]/2.0f-minus_y,
						2,
						string[0]);

				}
			}

			if (cnt==0) ;
			else {
				//scaは文字大きさの割増分
				if (cnt<=10) sca = 0.0f + (0.5f - 0.0f) / 10.0f * cnt ;
				else if (cnt<=20) sca = 0.5f + (0.0f - 0.5f) / 10.0f * (cnt-10) ;
				else sca=0.0f;

				strcpy(string,"COMBO!");

				for (k=0;k<6;k++) {
					graph_char_ex(
						Pl_n,
						d_temp[0]-50+100.0/6.0*k-10*sca,
						d_temp[1]+50-minus_y,
						d_temp[0]-50+100.0/6.0*(k+1)+10*sca,
						-1,
						1,
						string[k]);
				}

			}
		}

		if (ef_cnt==0) ;
		else if (ef_cnt<=15) SetDrawBlendMode(DX_BLENDMODE_ALPHA,256.0/15.0*ef_cnt);
		else if (ef_cnt<=60) SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		else if (ef_cnt<=75) SetDrawBlendMode(DX_BLENDMODE_ALPHA,256.0/15.0*(15-(ef_cnt-60)));

		if (ef_cnt>0 && ef_cnt<=75 && cnt>0) {

			sprintf(string,"%d combo!",state);
			
			graph_string_slim(
				Pl_n,
				d_temp[0]-get_graph_string_slim_width(3,3,string)/2.0f,
				d_temp[1]-30+50-minus_y,
				3,
				3,
				string);

			switch(state) {
			case 2: rate=1.5; break;
			case 3: rate=2.0; break;
			case 4: rate=3.5; break;
			case 5: rate=5.0; break;
			case 6: rate=7.0; break;
			case 7: rate=10.0; break;
			case 8: rate=15.0; break;
			case 9: rate=20.0; break;
			case 10: rate=30.0; break;
			}

			sprintf(string,"point:x%1.1lf",rate);
			
			graph_string_slim(
				Pl_n,
				d_temp[0]-get_graph_string_slim_width(3,3,string)/2.0f,
				d_temp[1]-10+50-minus_y,
				3,
				3,
				string);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		if (ef_cnt>0 && func_state!=999) Pl[Pl_n].effect_state[EFFECT_COMBO][i][1]++;

	}
}

void graph_back_effect_Split(int Pl_n) {
	int i,j;
	int cnt;
	char string[8];
	double base_x,base_y;

	for (i=0;i<EFFECT_SET_MAX;i++) {

		cnt=Pl[Pl_n].effect_flag[EFFECT_SPLIT][i];
		base_y=70.0;

		if (cnt==0) ;
		else if (cnt<=30) {
			strcpy(string,"SPLIT");
			for (j=0;j<5;j++) {
				if (cnt-3 <= 8.0/5.0*(j+1)) base_x = BOARD_X_MAX*BLOCK_SIZE/5.0*j - (8.0/5.0*(j+1) - (cnt-3))*22.0;
				else base_x = BOARD_X_MAX*BLOCK_SIZE/5.0*j;
				graph_char_ex(
					Pl_n,
					base_x-5+cnt/8.0,
					base_y,
					base_x+BOARD_X_MAX*BLOCK_SIZE/5.0,
					-1,
					1,
					string[j]);
			}
		} else if (cnt<=60) {
			strcpy(string,"SPLIT");
			for (j=0;j<5;j++) {
				base_x = BOARD_X_MAX*BLOCK_SIZE/5.0*j;
				graph_char_ex(
					Pl_n,
					base_x-5+cnt/8.0,
					base_y,
					base_x+BOARD_X_MAX*BLOCK_SIZE/5.0,
					-1,
					1,
					string[j]);
			}
		} else if (cnt<=100) {
			strcpy(string,"SPLIT");
			for (j=0;j<5;j++) {
				if (cnt-60 >= 20.0/5.0*j) base_x = BOARD_X_MAX*BLOCK_SIZE/5.0*j + (cnt-60 - 20.0/5.0*j)*8.0;
				else base_x = BOARD_X_MAX*BLOCK_SIZE/5.0*j;
				graph_char_ex(
					Pl_n,
					base_x-5+cnt/8.0,
					base_y,
					base_x+BOARD_X_MAX*BLOCK_SIZE/5.0,
					-1,
					1,
					string[j]);
			}
		}

	}
}

void graph_back_effect_LineNotice(int Pl_n) {
	int i,j,k;
	int cnt;
	int width;
	char string[64];
	double base_x,base_y;

	for (k=0;k<2;k++) {

		if (k==0) base_y=50.0; else base_y=270.0;
		
		for (i=0;i<EFFECT_SET_MAX;i++) {

			cnt=Pl[Pl_n].effect_flag[EFFECT_LINE_NOTICE][i];
			sprintf(string,"%d Line Cleared",(int)Pl[Pl_n].effect_state[EFFECT_LINE_NOTICE][i][0]);
			width=get_graph_string_slim_width(1,3,string);

			if (cnt==0) ;
			else if (cnt<=30) {
				base_x = BOARD_X_MAX*BLOCK_SIZE/2.0 - width/2.0 + BOARD_X_MAX*BLOCK_SIZE/30.0*(30-cnt);
				graph_string_slim(Pl_n,base_x,base_y,1,3,string);
			} else if (cnt<=130) {
				base_x = BOARD_X_MAX*BLOCK_SIZE/2.0 - width/2.0;
				graph_string_slim(Pl_n,base_x,base_y,1,3,string);
			} else if (cnt<=160) {
				base_x = BOARD_X_MAX*BLOCK_SIZE/2.0 - width/2.0 - BOARD_X_MAX*BLOCK_SIZE/30.0*(cnt-130);
				graph_string_slim(Pl_n,base_x,base_y,1,3,string);
			}

		}
	}
}

void graph_back_effect(int Pl_n) {
	graph_back_effect_AllClear(Pl_n);
	graph_back_effect_Combo(Pl_n);
	graph_back_effect_DisLine(Pl_n);
	graph_back_effect_Split(Pl_n);
	graph_back_effect_LineNotice(Pl_n);
}

void graph_back_image01(int Pl_n) {
	int sum,i,j,k;
	int draw_x,draw_y;
	double speed=1.0;
	double speed_x[4]={-0.2,0.2,-0.5,0.5};

	DrawBox( Pl[Pl_n].screen_x_d , Pl[Pl_n].screen_y_d ,
		Pl[Pl_n].screen_x_de , Pl[Pl_n].screen_y_de ,
		GetColor(255,255,255) , TRUE );

	sum=img_back_s[1][0][1]+img_back_s[1][1][1]+img_back_s[1][2][1]+img_back_s[1][3][1];

	for ( i = (int)(stage_cnt*speed/sum) ; i <= (int)((stage_cnt*speed+BLOCK_SIZE*20)/sum) ; i++ ) {

		draw_y=sum*i-speed*stage_cnt;

		for (j=0;j<4;j++) {
			if (draw_y >= -img_back_s[1][j][1] && draw_y < BLOCK_SIZE*20) {
				temp[0]=(int)(stage_cnt*speed_x[j]/img_back_s[1][j][0]);
				if (speed_x[j]<0) temp[0]--;
				for ( k = temp[0] ; k <= (int)((stage_cnt*speed_x[j]+BLOCK_SIZE*BOARD_X_MAX)/img_back_s[1][j][0]) ; k++ ) {
					draw_x=img_back_s[1][j][0]*k-speed_x[j]*stage_cnt;
					DrawGraph(Pl[Pl_n].screen_x_d+draw_x,Pl[Pl_n].screen_y_d+draw_y,img_back[1][j],TRUE);
				}

			}

			draw_y+=img_back_s[1][j][1];
		}
	}
	
	SetDrawBlendMode( DX_BLENDMODE_ALPHA , 105 );
	DrawBox( Pl[Pl_n].screen_x_d , Pl[Pl_n].screen_y_d ,
		Pl[Pl_n].screen_x_de , Pl[Pl_n].screen_y_de ,
		GetColor(0,0,0),TRUE);
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );

}

bullet_t bullet[PLAYER_MAX][2000];

void graph_back_image02(int Pl_n) {
	int i,j,k,flag;
	double nx,ny,nz;
	double h;
	int randbase;

	flag=0;

	for (i=0;i<10;i++) {
		for (j=0;j<EFFECT_SET_MAX;j++) {
			if (Pl[Pl_n].effect_flag[EFFECT_DISLINE+i][j]==1) flag=1;
		}
	}

	if (flag==1) {
		
		nx=BOARD_X_MAX*BLOCK_SIZE/2.0-25.0+GetRand(5000)/100.0;
		ny=(BOARD_Y_MAX-10)*BLOCK_SIZE/4.0-25.0+GetRand(5000)/100.0;
		nz=-25.0+GetRand(5000)/100.0;

		se_flag[9]=1;

		h=30.0+GetRand(370000)/1000.0;

		for (i=0;i<300;i++) {

			for (j=0;j<2000;j++) {
				if (bullet[Pl_n][j].flag!=1) {
					/******************************
					半径rの球
					　　　　 _,,,..,,_／￣￣￣￣￣この部分の表面積は2πr^2(1-cosθ) （必死の計算による）
					　　　,-_________′-､
　 　					,"　　　 |　 ￣  ヽ 
　　					   /　　 `　 |θ ′　 ﾞ、
　					  ?　　　  ` | ′ 　 　 .
					  !____________________l
　					  ',　　　　　　　　　 ,'
　					   丶　　　　　　　　　/
　　					    ヽ　　　　　　   .'
　　　					 `･_　　　　  .'′
　　　　　　					ﾞ''ｰ-‐'"
					よって
					S=2πr^2(1-cosθ)
					cosθ=1-S/(2πr^2)
					θ=acos(1-S/(2πr^2))
					******************************/
					randbase=4.0*PI*1000*1000/300.0*i;//GetRand(4.0*PI*1000*1000);
					bullet[Pl_n][j].flag=1;
					bullet[Pl_n][j].x=nx;
					bullet[Pl_n][j].y=ny;
					bullet[Pl_n][j].z=nz;
					bullet[Pl_n][j].dy=acos(1.0-randbase/(2.0*PI*1000*1000));
					bullet[Pl_n][j].dx=randbase/h;//bullet[Pl_n][j].dy*50;
					bullet[Pl_n][j].v=2.5;//+GetRand(2000)/10000.0;
					bullet[Pl_n][j].t=0;
					bullet[Pl_n][j].col=2;
					bullet[Pl_n][j].flag=1;
					bullet[Pl_n][j].bright=255;
					break;
				}
			}

		}

	}
	
	SetDrawMode( DX_DRAWMODE_BILINEAR ) ;

	for (i=0;i<2000;i++) {
		if (bullet[Pl_n][i].flag==1) {
			if (func_state!=999) {
				bullet[Pl_n][i].x+=bullet[Pl_n][i].v*sin(bullet[Pl_n][i].dy)*cos(bullet[Pl_n][i].dx);
				bullet[Pl_n][i].y+=bullet[Pl_n][i].v*cos(bullet[Pl_n][i].dy)+bullet[Pl_n][i].t*0.0015;
				bullet[Pl_n][i].z+=bullet[Pl_n][i].v*sin(bullet[Pl_n][i].dy)*sin(bullet[Pl_n][i].dx);
				bullet[Pl_n][i].v*=0.9786;
				if (bullet[Pl_n][i].t<80+(i*17)%40) bullet[Pl_n][i].bright=255.0;
				else if (bullet[Pl_n][i].t<100+(i*17)%40) bullet[Pl_n][i].bright=255.0/20.0*(100+i%40-bullet[Pl_n][i].t);
				else if (bullet[Pl_n][i].t<160+(i*37)%100) {
					if (bullet[Pl_n][i].t%3==0) {
						bullet[Pl_n][i].col=4;
						if (bullet[Pl_n][i].bright>=255) bullet[Pl_n][i].bright=0.0;
						else bullet[Pl_n][i].bright=(GetRand(4)<=2)?255.0:0.0;
					}
				} else bullet[Pl_n][i].flag=0;
				bullet[Pl_n][i].t++;
			}
			if (bullet[Pl_n][i].flag==1) {
				SetDrawBlendMode( DX_BLENDMODE_ADD , bullet[Pl_n][i].bright ) ;
				nx=bullet[Pl_n][i].x-BOARD_X_MAX*BLOCK_SIZE/2.0;
				nz=bullet[Pl_n][i].z;
				DrawGraphF( Pl[Pl_n].screen_x_d+nx*cos(stage_cnt*0.000)-nz*sin(stage_cnt*0.000)+BOARD_X_MAX*BLOCK_SIZE/2.0,
					Pl[Pl_n].screen_y_d+bullet[Pl_n][i].y,
					img_effect[0][bullet[Pl_n][i].col], TRUE ) ;
			}
		}
	}
	
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 ) ;
	
	SetDrawMode( DX_DRAWMODE_NEAREST ) ;

}

void graph_back_image(int Pl_n) {
	graph_back_image02(Pl_n);
}

void graph_back(int Pl_n) {
	graph_back_image(Pl_n);
	graph_back_effect(Pl_n);
}