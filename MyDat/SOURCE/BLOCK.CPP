#include "../include/GV.h"
#include <math.h>

//effect_flagの中からちょうどいい番号を探してフラグを立てて立てた番号を返す関数
int set_effect_flag(int Pl_n,int num) {
	int i,j,max=0,max_num=0;
	for (i=0;i<EFFECT_SET_MAX;i++) {
		if (Pl[Pl_n].effect_flag[num][i]==0) {
			Pl[Pl_n].effect_flag[num][i]=1;
			return i;
		} else {
			if (Pl[Pl_n].effect_flag[num][i]>max) {
				max_num=i;
				max=Pl[Pl_n].effect_flag[num][i];
			}
		}
	}
	Pl[Pl_n].effect_flag[num][max_num]=1;
	return max_num;
}

//Pl_n番目のプレイヤーのnum番目のnext箱にブロックを新規格納する関数。初期化処理でも使用するためnext_out関数から分離
void add_next(int Pl_n,int num) {
	int i,flag;
	double inirand=0;
	double appsum=0;
	double appnow;

	for (i=0;i<block_kinds;i++) appsum+=block[i].app;

	do {
		flag=0;
		inirand=GetRand(appsum*10000)/10000.0f;
		appnow=0;
		for (i=0;i<block_kinds;i++) {
			appnow+=block[i].app;
			if (inirand<appnow) {
				Pl[Pl_n].next[num]=i;
				//if (num==0) Pl[Pl_n].next[num]=5;
				break;
			}
		}
		if (num-2>=0) {
			if (Pl[Pl_n].next[num]==Pl[Pl_n].next[num-1]
				&& Pl[Pl_n].next[num]==Pl[Pl_n].next[num-2]) flag=1;
		}
	} while(flag==1);

}

int next_out(int Pl_n) {
	int ret=Pl[Pl_n].next[0];
	int i;

	for (i=0;i<NEXT_MAX-1;i++) {
		Pl[Pl_n].next[i]=Pl[Pl_n].next[i+1];
	}

	add_next(Pl_n,NEXT_MAX-1);

	return ret;
}

int block_num_search(){
	for(int i=0;i<B_INFO_MAX;i++){//フラグのたって無いenemyを探す
		if(b_info[i].flag==0){
			return i;//使用可能番号を返す
		}
	}
	return -1;//全部埋まっていたらエラーを返す
}

void block_app(int Pl_n,int kind){
	//printfDx("block apped\n");
	if (Pl[Pl_n].block.flag!=1) {
		Pl[Pl_n].block.flag=1;
		Pl[Pl_n].block.angle=0;
		Pl[Pl_n].block.kind=kind;
		Pl[Pl_n].block.gx=(int)(BOARD_X_MAX/2-block[Pl[Pl_n].block.kind].x/2);
		Pl[Pl_n].block.gy=10-block[Pl[Pl_n].block.kind].y;
		Pl[Pl_n].block.v=StageSpeed;
		Pl[Pl_n].block.b_angle=Pl[Pl_n].block.angle;
		Pl[Pl_n].block.b_cent_x=cent_point_cal_x(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle);
		Pl[Pl_n].block.b_cent_y=cent_point_cal_y(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle);
		Pl[Pl_n].block.x=Pl[Pl_n].block.gx*BLOCK_SIZE;
		Pl[Pl_n].block.wait=0;
		Pl[Pl_n].block.cnt=0;
		Pl[Pl_n].block.delay_y=0;
		Pl[Pl_n].block.n_delay_y=0;
		Pl[Pl_n].block.touchflag=0;
		Pl[Pl_n].cpu_state=0;
		Pl[Pl_n].block_num++;
		se_flag[0]=1;
	}
}

void block_disapp(int Pl_n) {
	int i,j,k,flag,dis_n=0;
	int AC_flag=1;
	int split_flag=0;

	for (i=BOARD_Y_MAX-1;i>=0;i--) {

		flag=0;
		for (j=0;j<BOARD_X_MAX;j++) {

			if (Pl[Pl_n].board[j][i]==0) {
				flag=1;
			}

		}

		if (flag==0) {
			Pl[Pl_n].dis_line_n[dis_n]=i;
			if (dis_n>=1 && Pl[Pl_n].dis_line_n[dis_n-1]-i>=2) split_flag=1;
			dis_n++;
			Pl[Pl_n].line++;
			if (Pl[Pl_n].line%10==0) {
				k=set_effect_flag(Pl_n,EFFECT_LINE_NOTICE);
				Pl[Pl_n].effect_state[EFFECT_LINE_NOTICE][k][0]=Pl[Pl_n].line;
			}
		} else {
			for (j=0;j<BOARD_X_MAX;j++) {
				Pl[Pl_n].board[j][i+dis_n]=Pl[Pl_n].board[j][i];
				Pl[Pl_n].board_angle[j][i+dis_n]=Pl[Pl_n].board_angle[j][i];
				Pl[Pl_n].block_fall[j][i+dis_n].plus_y=dis_n*BLOCK_SIZE;
				Pl[Pl_n].block_fall[j][i+dis_n].v=0;
				if (Pl[Pl_n].board[j][i+dis_n]!=0) AC_flag=0;
			}
		}

	}

	for (i=dis_n-1;i>=0;i--) {
		for (j=0;j<BOARD_X_MAX;j++) {
			Pl[Pl_n].board[j][i+dis_n]=0;
			Pl[Pl_n].board_angle[j][i+dis_n]=0;
			Pl[Pl_n].block_fall[j][i+dis_n].plus_y=dis_n*BLOCK_SIZE;
			Pl[Pl_n].block_fall[j][i+dis_n].v=0;
		}
	}

	if (dis_n>0) {
		//dis_n=4+GetRand(6);
		Pl[Pl_n].combo++;
		Pl[Pl_n].combo_times_ini[dis_n-1]++;
		Pl[Pl_n].dis_line_times[dis_n-1]++;
		set_effect_flag(Pl_n,EFFECT_DISLINE+dis_n-1);
		if (Pl[Pl_n].combo>=2) {
			for (i=0;i<EFFECT_SET_MAX;i++) Pl[Pl_n].effect_flag[EFFECT_COMBO][i]=0;
			k=set_effect_flag(Pl_n,EFFECT_COMBO);
			Pl[Pl_n].effect_state[EFFECT_COMBO][k][0]=Pl[Pl_n].combo;
			Pl[Pl_n].effect_state[EFFECT_COMBO][k][1]=0;
		}
		if (AC_flag==1) {
			set_effect_flag(Pl_n,EFFECT_ALLCLEAR);
			Pl[Pl_n].dis_line_AC_times[dis_n-1]++;
			se_flag[5]=1;
		}
		if (split_flag==1) {
			set_effect_flag(Pl_n,EFFECT_SPLIT);
			Pl[Pl_n].split_times[dis_n-1]++;
		}
		if (dis_n==1) se_flag[1]=1;
		else if (dis_n==2 || dis_n==3) se_flag[2]=1;
		else if (dis_n>=4) se_flag[3]=1;
		if (Pl[Pl_n].cpu_flag==1 && Pl[Pl_n].cpu_mode.difficalty==4) {
			Pl[Pl_n].pause_cnt=0;
		} else {
			Pl[Pl_n].pause_flag=3;
			Pl[Pl_n].pause_cnt=0;
		}
	} else {
		if (Pl[Pl_n].combo>=2) {
			for (i=0;i<10;i++) {
				Pl[Pl_n].combo_times[Pl[Pl_n].combo][i]+=Pl[Pl_n].combo_times_ini[i];
				Pl[Pl_n].combo_times_ini[i]=0;
			}
		}
		for (j=0;j<EFFECT_SET_MAX;j++) {
			if (Pl[Pl_n].effect_flag[EFFECT_COMBO][j]>0 && Pl[Pl_n].effect_state[EFFECT_COMBO][j][1]==0) Pl[Pl_n].effect_state[EFFECT_COMBO][j][1]=1;
		}
		Pl[Pl_n].combo=0;
	}
}

void block_gameover(int Pl_n) {
	int i,j,flag=0,alive=0;

	for (i=0;i<BOARD_X_MAX && flag==0;i++) {
		for (j=0;j<10 && flag==0;j++) {

			if (Pl[Pl_n].board[i][j]!=0) {
				flag=1;
			}

		}
	}

	if (flag==1) {
		se_flag[4]=1;
		Pl[Pl_n].pause_flag=1;
		Pl[Pl_n].pause_cnt=0;
		Pl[Pl_n].gameover_x=Pl[Pl_n].screen_x_d+BLOCK_SIZE*BOARD_X_MAX/2.0;
		Pl[Pl_n].playtime_cnt=GetNowCount()-Pl[Pl_n].starttime_cnt;
		if (Pl_num==1) {
			gameover_flag=1;	
			switch(Pl_num) {
			case 0: StartJoypadVibration( DX_INPUT_PAD1, 100, 1000 ) ; break;
			case 1: StartJoypadVibration( DX_INPUT_PAD2, 100, 1000 ) ; break;
			case 2: StartJoypadVibration( DX_INPUT_PAD3, 100, 1000 ) ; break;
			case 3: StartJoypadVibration( DX_INPUT_PAD4, 100, 1000 ) ; break;
			}
			bgm_state=0;
		} else {
			for (i=0;i<Pl_num;i++) {
				if (Pl[i].pause_flag!=1) alive++;
			}
			if (alive<=1) {
				gameover_flag=1;
				switch(Pl_num) {
				case 0: StartJoypadVibration( DX_INPUT_PAD1, 100, 1000 ) ; break;
				case 1: StartJoypadVibration( DX_INPUT_PAD2, 100, 1000 ) ; break;
				case 2: StartJoypadVibration( DX_INPUT_PAD3, 100, 1000 ) ; break;
				case 3: StartJoypadVibration( DX_INPUT_PAD4, 100, 1000 ) ; break;
				}
				bgm_state=0;
				for (i=0;i<Pl_num;i++) {
					if (Pl[i].pause_flag!=1) {
						Pl[i].block.flag=0;
						Pl[i].pause_flag=2;
						Pl[i].pause_cnt=0;
						Pl[i].playtime_cnt=GetNowCount()-Pl[i].starttime_cnt;
					}
				}
			}
		}
	}

}

void block_control() {
	int i,j,k,l,flag=0,touch_flag=0;
	block_point n_block[BLOCK_MAX];

	for(i=0;i<Pl_num;i++) {

		flag=0;

		if (Pl[i].block.flag==1) {

			turn_cal(Pl[i].block.kind,Pl[i].block.angle,n_block);
			touch_flag=0;
			for (k=(Pl[i].block.touchflag==1)?0:((int)Pl[i].block.v);k>=0 && touch_flag==0;k--) {

				for (j=0;j<block[Pl[i].block.kind].n && touch_flag==0;j++) {
	
					if ((int)((int)(Pl[i].block.gy)+1+n_block[j].y-k)>=0 &&
						(Pl[i].board[(int)(Pl[i].block.gx+n_block[j].x)
						][(int)((int)(Pl[i].block.gy)+1+n_block[j].y-k)
						] != 0 || (int)((int)(Pl[i].block.gy)+1+n_block[j].y-k)>=BOARD_Y_MAX)
						) {
						if (Pl[i].block.wait>40 || CheckStateKey(KEY_INPUT_DOWN)==1) {
							for (l=0;l<block[Pl[i].block.kind].n;l++) {
								Pl[i].board[(int)(Pl[i].block.gx+n_block[l].x)][(int)((int)(Pl[i].block.gy)+n_block[l].y)]=Pl[i].block.kind+1;
								Pl[i].board_angle[(int)(Pl[i].block.gx+n_block[l].x)][(int)((int)(Pl[i].block.gy)+n_block[l].y)]=Pl[i].block.angle;
							}
	
							Pl[i].block.flag=0;
	
							Pl[i].holdflag=0;
	
							block_disapp(i);
							
							block_gameover(i);
	
	
							if (Pl[i].pause_flag==0) {
								block_app(i,next_out(i));
							}
	
							break;
						} else {
							Pl[i].block.wait++;
							Pl[i].block.gy=(int)(Pl[i].block.gy)-k;
							Pl[i].block.y=Pl[i].block.gy*BLOCK_SIZE;
						}
	
						touch_flag=1;
						Pl[i].block.touchflag=1;
						
					}
				}
			}

			if (touch_flag==0) {
				Pl[i].block.touchflag=0;
				if (Pl[i].block.v<10) Pl[i].block.wait=0;
			}

			flag=1;

		}

		if (flag==0 && Pl[i].pause_flag==0) {
			block_app(i,next_out(i));
		}

	}

}

void block_lrmove(int Pl_n,int dir) {
	int flag=0;
	int nx,ny;
	int i,j,k;
	int direction;
	int roop;
	block_point n_block[BLOCK_MAX];
	
	turn_cal(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle , n_block);
	
	if (dir>0) direction=1;
	else direction=-1;

	if (dir>20 || dir<-20) return;

	for (k=0;k<abs(dir);k++) {

		for (i=0;i<block[Pl[Pl_n].block.kind].n;i++) {

			nx=(int)(Pl[Pl_n].block.gx+direction+n_block[i].x);
			ny=(int)((int)(Pl[Pl_n].block.gy)+n_block[i].y);

			if (!( nx>=0 && nx<BOARD_X_MAX && Pl[Pl_n].board[nx][ny] == 0 && ( Pl[Pl_n].block.touchflag==1 || Pl[Pl_n].board[nx][ny+1] == 0 )) ){
				flag=1;
				break;
			}

		}

		if (flag==0) Pl[Pl_n].block.gx+=direction;
		else if (Pl[Pl_n].block.cnt<60) {
			for (i=1;i<BOARD_Y_MAX;i++) {

				flag=0;

				for (j=0;j<block[Pl[Pl_n].block.kind].n;j++) {

					nx=(int)(Pl[Pl_n].block.gx+direction+n_block[j].x);
					ny=(int)((int)(Pl[Pl_n].block.gy)+n_block[j].y-i);

					if (!( nx>=0 && nx<BOARD_X_MAX && Pl[Pl_n].board[nx][ny] == 0 && ( Pl[Pl_n].block.touchflag==1 || Pl[Pl_n].board[nx][ny+1] == 0 )) ){
						flag=1;
						break;
					}

				}

				if (flag==0) {
					Pl[Pl_n].block.gx+=direction;
					Pl[Pl_n].block.gy-=i;
					Pl[Pl_n].block.delay_y-=i;
					break;
				}

			}
		}

	}

}

void block_harddrop(int Pl_n) {
	int j,k,l;
	int flag;
	int nx,ny;
	block_point n_block[BLOCK_MAX];

	turn_cal( Pl[Pl_n].block.kind , Pl[Pl_n].block.angle , n_block );
	
	flag=0;
	for (j=0;j<BOARD_Y_MAX && flag==0;j++) {
		for (k=0;k<block[Pl[Pl_n].block.kind].n;k++) {

			nx=(int)(Pl[Pl_n].block.gx+n_block[k].x);
			ny=(int)((int)(Pl[Pl_n].block.gy)+n_block[k].y+j);
			
			if (!( ny<BOARD_Y_MAX && Pl[Pl_n].board[nx][ny] == 0 ) ){

				for (l=0;l<block[Pl[Pl_n].block.kind].n;l++) {
					Pl[Pl_n].board[(int)(Pl[Pl_n].block.gx+n_block[l].x)][(int)((int)(Pl[Pl_n].block.gy)+n_block[l].y+j-1)]=Pl[Pl_n].block.kind+1;
					Pl[Pl_n].board_angle[(int)(Pl[Pl_n].block.gx+n_block[l].x)][(int)((int)(Pl[Pl_n].block.gy)+n_block[l].y+j-1)]=Pl[Pl_n].block.angle;
				}

				Pl[Pl_n].harddropline+=((int)Pl[Pl_n].block.gy+j-1)-Pl[Pl_n].block.gy;
					
				Pl[Pl_n].block.flag=0;
					
				Pl[Pl_n].holdflag=0;
				
				block_disapp(Pl_n);
				
				block_gameover(Pl_n);
				
				if (Pl[Pl_n].pause_flag==0) {
					block_app(Pl_n,next_out(Pl_n));
				}

				flag=1;
				break;
			}
			
		}
	}
}

void block_turn(int Pl_n,int key2,int key3) {
	int flag;
	int esc=0;
	int roop;
	int delay;
	int swift;
	int j,k,l,m;
	int nx,ny;
	block_point n_block[BLOCK_MAX];

	flag=1;
	roop=abs( block[Pl[Pl_n].block.kind].x - block[Pl[Pl_n].block.kind].y )+1;
	if (key2>0) k=-1;
	else if (key3>0) k=1;
	while ((key2>0 && k>=-4 && k<=-1 && esc==0) || (key3>0 && k<=4 && k>=1 && esc==0)) {
				
		turn_cal(Pl[Pl_n].block.kind,Pl[Pl_n].block.angle+k,n_block);

		esc=0;

		for (m=0;m<roop+2 && esc==0;m++) {
			if (m==0) delay=0;
			else if (m==1) delay=1;
			else if (m%2==0) delay=(m+2)/2;
			else if (m%2==1) delay=-(m-1)/2;
						
			for (l=0;l<roop+1 && esc==0;l++) {
							
				if (l==0) swift=0;
				else if (l%2==1) swift=-(l+1)/2;
				else if (l%2==0) swift=l/2;
							
				flag=0;
				
				for (j=0;j<block[Pl[Pl_n].block.kind].n;j++) {
					nx=(int)(Pl[Pl_n].block.gx+n_block[j].x+swift);
					ny=(int)(ceil(Pl[Pl_n].block.gy)+n_block[j].y+delay);
					if ( !
							( nx>=0 && nx<BOARD_X_MAX
							&& Pl[Pl_n].board[nx][ny] == 0
							&& ( Pl[Pl_n].block.touchflag==1 || (delay<0 || Pl[Pl_n].board[nx][ny+1] == 0) ) 
							&& ny+1<=BOARD_Y_MAX )
						) {
						flag=1;
						break;
					}
				}
				
				if (flag==1) continue;

				if (flag==0) {
					Pl[Pl_n].block.b_cent_x=cent_point_cal_x(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle);
					Pl[Pl_n].block.b_cent_y=cent_point_cal_y(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle);
					Pl[Pl_n].block.b_angle=Pl[Pl_n].block.angle;
					Pl[Pl_n].block.angle+=k;
					Pl[Pl_n].block.gx+=swift;
					if (delay<0) {
						Pl[Pl_n].block.delay_y+=delay;
						Pl[Pl_n].block.gy=ceil(Pl[Pl_n].block.gy)+delay;
					}
					Pl[Pl_n].block.angle_rate=1;
					esc=1;
				}
			}
		}
		if (esc==0 && Pl[Pl_n].block.cnt<60) {
			for (l=1;l<BOARD_Y_MAX;l++) {
				flag=0;
				for (j=0;j<block[Pl[Pl_n].block.kind].n;j++) {
					nx=(int)(Pl[Pl_n].block.gx+n_block[j].x);
					ny=(int)((int)(Pl[Pl_n].block.gy)+n_block[j].y-l);
					if ( !
							( nx>=0 && nx<BOARD_X_MAX
							&& Pl[Pl_n].board[nx][ny] == 0
							&& ( Pl[Pl_n].block.touchflag==1) 
							&& ny+1<=BOARD_Y_MAX )
						) {
						flag=1;
						break;
					}
				}
							
				if (flag==0) {
					Pl[Pl_n].block.b_cent_x=cent_point_cal_x(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle);
					Pl[Pl_n].block.b_cent_y=cent_point_cal_y(Pl[Pl_n].block.kind , Pl[Pl_n].block.angle);
					Pl[Pl_n].block.b_angle=Pl[Pl_n].block.angle;
					Pl[Pl_n].block.angle+=k;
					Pl[Pl_n].block.gy=(int)(Pl[Pl_n].block.gy)-l;
					Pl[Pl_n].block.delay_y-=l;
					Pl[Pl_n].block.angle_rate=1;
					break;
				}
			}
		}
		if (key2>0) k--;
		else if (key3>0) k++;

	}
}

void block_hold(int Pl_n) {
	int temp;
	if (Pl[Pl_n].pause_flag==0 && Pl[Pl_n].holdflag==0) {
		if (Pl[Pl_n].hold==0) {
			Pl[Pl_n].hold=Pl[Pl_n].block.kind+1;
			Pl[Pl_n].block.flag=0;
			block_app(Pl_n,next_out(Pl_n));
		} else {
			temp=Pl[Pl_n].hold;
			Pl[Pl_n].hold=Pl[Pl_n].block.kind+1;
			Pl[Pl_n].block.flag=0;
			block_app(Pl_n,temp-1);
			Pl[Pl_n].block_num--;
		}
		Pl[Pl_n].holdflag=1;
		Pl[Pl_n].hold_cnt=0;
	}
}

void block_drop(int i) {
	if (Pl[i].block.touchflag==0) {
		Pl[i].block.gy+=0.4;
		Pl[i].dropline+=0.4;
	}
}

void block_key(int Pl_n){
	int i,j,k,l,m;
	int left,right,up,down,hold_k,turn_L,turn_R,ana;
	int dir,nx,ny,flag;
	int position;
	int aim,min_gx,max_gx;
	block_point n_block[BLOCK_MAX];

	left=CheckStatePad(Pl_n,PAD_NUM_LEFT);
	right=CheckStatePad(Pl_n,PAD_NUM_RIGHT);
	up=CheckStatePad(Pl_n,PAD_NUM_UP);
	down=CheckStatePad(Pl_n,PAD_NUM_DOWN);
	hold_k=CheckStatePad(Pl_n,PAD_NUM_HOLD);
	turn_L=CheckStatePad(Pl_n,PAD_NUM_TURN_L);
	turn_R=CheckStatePad(Pl_n,PAD_NUM_TURN_R);
	if (Pl_n==0) GetJoypadAnalogInput( &ana , &temp[0] , DX_INPUT_PAD1 ) ;
	if (Pl_n==1) GetJoypadAnalogInput( &ana , &temp[0] , DX_INPUT_PAD2 ) ;
	if (Pl_n==2) GetJoypadAnalogInput( &ana , &temp[0] , DX_INPUT_PAD3 ) ;
	if (Pl_n==3) GetJoypadAnalogInput( &ana , &temp[0] , DX_INPUT_PAD4 ) ;

	if (Pl[Pl_n].block.flag==1 && pause_flag==0) {
			
		if (Pl[Pl_n].block.touchflag==0) {
			Pl[Pl_n].block.gy+=Pl[Pl_n].block.v;
		}

		if (left==1 || right==1 || (left>10 && left%3==0) || (right>10 && right%3==0)) {
			if (left>0) dir=-1;
			if (right>0) dir=1;
			block_lrmove(Pl_n,dir);
		}

		/*turn_cal(Pl[Pl_n].block.kind,Pl[Pl_n].block.angle,n_block);

		min_gx=12;
		max_gx=-2;

		for (i=-2;i<13;i++) {
			flag=0;
			for (j=0;j<block[Pl[Pl_n].block.kind].n;j++) {
				if (n_block[j].x+i<0 || n_block[j].x+i>=BOARD_X_MAX) {flag=1; break;}
			}
			if (flag==0 && min_gx>i) min_gx=i;
			if (flag==0 && max_gx<i) max_gx=i;
		}

		position=(int)(BOARD_X_MAX/2-block[Pl[Pl_n].block.kind].x/2);
		
		if (ana==-1000) aim=min_gx;
		else if (ana<0) aim=(int)((double)(ana+1000)/1000.0*(double)(position-min_gx-1))+min_gx+1;
		else if (ana==0) aim=position;
		else if (ana<1000) aim=(int)((double)(ana)/1000.0*(double)(max_gx-position-1))+position+1;
		else if (ana==1000) aim=max_gx;

		block_lrmove(Pl_n,aim-Pl[Pl_n].block.gx);*/

		if (down>0 && Pl[Pl_n].block.cnt>=down) {
			block_drop(Pl_n);
		}

		if (up==1) {
			block_harddrop(Pl_n);
		}

		if (hold_k==1) {
			block_hold(Pl_n);
		}
			
		if (turn_L==1 || (turn_L>10 && turn_L%3==0) || turn_R==1 || (turn_R>10 && turn_R%3==0)) {
			block_turn(Pl_n,turn_L,turn_R);
		}

	}
}

void cpu_key(int Pl_n) {
	if (Pl[Pl_n].pause_flag==0 && Pl[Pl_n].block.flag==1) {
			
		if (Pl[Pl_n].block.touchflag==0) {
			Pl[Pl_n].block.gy+=Pl[Pl_n].block.v;
		}

		if (Pl[Pl_n].cpu_mode.difficalty==0) {

			/************* レベル0 *************/

			switch(Pl[Pl_n].cpu_state) {
			case 0: //出現の瞬間･計算
				cpu_cal_num_weak(
					Pl_n,
					Pl[Pl_n].block.kind,
					(Pl[Pl_n].hold==0)?Pl[Pl_n].next[0]:(Pl[Pl_n].hold-1),
					&Pl[Pl_n].cpu_aim_angle,
					&Pl[Pl_n].cpu_aim_position,
					GetRand(2));
				Pl[Pl_n].cpu_state=1;
				Pl[Pl_n].cpu_state_cnt=0;
				break;
			case 1: //待ち時間
				if (Pl[Pl_n].cpu_state_cnt==30 && Pl[Pl_n].cpu_aim_angle!=4) {
					Pl[Pl_n].cpu_state=2;
				}
				if (Pl[Pl_n].cpu_state_cnt==80 && Pl[Pl_n].cpu_aim_angle==4) {
					Pl[Pl_n].cpu_state=6;
					block_hold(Pl_n);
				}
				break;
			case 2: //回転
				if (Pl[Pl_n].cpu_state_cnt%15==0 && Pl[Pl_n].block.angle<=5) {
					if (Pl[Pl_n].block.angle>Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,1,0);
					else if (Pl[Pl_n].block.angle<Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,0,1);
					else {Pl[Pl_n].cpu_state=3; Pl[Pl_n].cpu_state_cnt=0;}
				}
				break;
			case 3: //待ち時間
				if (Pl[Pl_n].cpu_state_cnt==10) Pl[Pl_n].cpu_state=4;
				break;
			case 4: //左右移動
				if (Pl[Pl_n].cpu_state_cnt%15==0) {
					if (Pl[Pl_n].block.gx>Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,-1);
					else if (Pl[Pl_n].block.gx<Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,1);
					else {Pl[Pl_n].cpu_state=5; Pl[Pl_n].cpu_state_cnt=0;}
				}
				break;
			case 5: //落とす
				block_drop(Pl_n);
				break;
			}
		} else if (Pl[Pl_n].cpu_mode.difficalty==1) {

			/************* レベル1 *************/

			switch(Pl[Pl_n].cpu_state) {
			case 0: //出現の瞬間･計算
				cpu_cal_num_weak(
					Pl_n,
					Pl[Pl_n].block.kind,
					(Pl[Pl_n].hold==0)?Pl[Pl_n].next[0]:(Pl[Pl_n].hold-1),
					&Pl[Pl_n].cpu_aim_angle,
					&Pl[Pl_n].cpu_aim_position,
					GetRand(1)
					);
				Pl[Pl_n].cpu_state=1;
				Pl[Pl_n].cpu_state_cnt=0;
				break;
			case 1: //待ち時間
				if (Pl[Pl_n].cpu_state_cnt==20 && Pl[Pl_n].cpu_aim_angle!=4) {
					Pl[Pl_n].cpu_state=2;
				}
				if (Pl[Pl_n].cpu_state_cnt==60 && Pl[Pl_n].cpu_aim_angle==4) {
					Pl[Pl_n].cpu_state=6;
					block_hold(Pl_n);
				}
				break;
			case 2: //回転
				if (Pl[Pl_n].cpu_state_cnt%11==0 && Pl[Pl_n].block.angle<=5) {
					if (Pl[Pl_n].block.angle>Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,1,0);
					else if (Pl[Pl_n].block.angle<Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,0,1);
					else {Pl[Pl_n].cpu_state=3; Pl[Pl_n].cpu_state_cnt=0;}
				}
				break;
			case 3: //待ち時間
				if (Pl[Pl_n].cpu_state_cnt==7) Pl[Pl_n].cpu_state=4;
				break;
			case 4: //左右移動
				if (Pl[Pl_n].cpu_state_cnt%8==0) {
					if (Pl[Pl_n].block.gx>Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,-1);
					else if (Pl[Pl_n].block.gx<Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,1);
					else {Pl[Pl_n].cpu_state=5; Pl[Pl_n].cpu_state_cnt=0;}
				}
				break;
			case 5: //落とす
				block_drop(Pl_n);
				break;
			}
		} else if (Pl[Pl_n].cpu_mode.difficalty==2) {

			/************* レベル2 *************/

			switch(Pl[Pl_n].cpu_state) {
			case 0: //出現の瞬間･計算
				cpu_cal_num_weak(
					Pl_n,
					Pl[Pl_n].block.kind,
					(Pl[Pl_n].hold==0)?Pl[Pl_n].next[0]:(Pl[Pl_n].hold-1),
					&Pl[Pl_n].cpu_aim_angle,
					&Pl[Pl_n].cpu_aim_position,
					0
					);
				Pl[Pl_n].cpu_state=1;
				Pl[Pl_n].cpu_state_cnt=0;
				break;
			case 1: //待ち時間
				if (Pl[Pl_n].cpu_state_cnt==13 && Pl[Pl_n].cpu_aim_angle!=4) {
					Pl[Pl_n].cpu_state=2;
				}
				if (Pl[Pl_n].cpu_state_cnt==30 && Pl[Pl_n].cpu_aim_angle==4) {
					Pl[Pl_n].cpu_state=6;
					block_hold(Pl_n);
				}
				break;
			case 2: //回転＆移動
				if (Pl[Pl_n].cpu_state_cnt%10==0 && Pl[Pl_n].block.angle<=5) {
					if (Pl[Pl_n].block.angle>Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,1,0);
					else if (Pl[Pl_n].block.angle<Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,0,1);
				}
				if (Pl[Pl_n].cpu_state_cnt%8==0) {
					if (Pl[Pl_n].block.gx>Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,-1);
					else if (Pl[Pl_n].block.gx<Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,1);
				}

				if (Pl[Pl_n].block.gx==Pl[Pl_n].cpu_aim_position && Pl[Pl_n].block.angle==Pl[Pl_n].cpu_aim_angle) {
					Pl[Pl_n].cpu_state=3;
					Pl[Pl_n].cpu_state_cnt=0;
				}

				break;
			case 3: //待ち時間
				if (Pl[Pl_n].cpu_state_cnt==15) Pl[Pl_n].cpu_state=4;
				break;
			case 4: //落とす
				block_harddrop(Pl_n);
				break;
			}
		} else if (Pl[Pl_n].cpu_mode.difficalty==3) {

			/************* レベル3 *************/

			switch(Pl[Pl_n].cpu_state) {
			case 0: //出現の瞬間・計算
				cpu_cal_num_weak(
					Pl_n,
					Pl[Pl_n].block.kind,
					(Pl[Pl_n].hold==0)?Pl[Pl_n].next[0]:(Pl[Pl_n].hold-1),
					&Pl[Pl_n].cpu_aim_angle,
					&Pl[Pl_n].cpu_aim_position,
					0
					);
				if (Pl[Pl_n].cpu_aim_angle==4) {
					Pl[Pl_n].cpu_state=3;
					block_hold(Pl_n);
				} else {
					Pl[Pl_n].cpu_state=1;
					Pl[Pl_n].cpu_state_cnt=0;
				}
				break;
			case 1: //回転＆移動
				/*if (Pl[Pl_n].block.gx>Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,-1);
				else if (Pl[Pl_n].block.gx<Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,1);*/

				block_lrmove(Pl_n,Pl[Pl_n].cpu_aim_position-Pl[Pl_n].block.gx);

				if (Pl[Pl_n].block.angle<=5) {
					if (Pl[Pl_n].block.angle>Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,1,0);
					else if (Pl[Pl_n].block.angle<Pl[Pl_n].cpu_aim_angle) block_turn(Pl_n,0,1);
				}

				if (Pl[Pl_n].cpu_state_cnt==4) Pl[Pl_n].cpu_state=2;

				break;
			case 2: //落とす
				Pl[Pl_n].cpu_state=3;
				block_harddrop(Pl_n);
				break;
			case 3:
				if (Pl[Pl_n].cpu_state_cnt%4==3) {Pl[Pl_n].cpu_state=0; Pl[Pl_n].cpu_state_cnt=0;}
				break;
			}
		} else if (Pl[Pl_n].cpu_mode.difficalty==4) {

			/************* レベル4 *************/

			switch(Pl[Pl_n].cpu_state) {
			case 0: //出現の瞬間・計算
				cpu_cal_num_weak(
					Pl_n,
					Pl[Pl_n].block.kind,
					(Pl[Pl_n].hold==0)?Pl[Pl_n].next[0]:(Pl[Pl_n].hold-1),
					&Pl[Pl_n].cpu_aim_angle,
					&Pl[Pl_n].cpu_aim_position,
					0
					);
				if (Pl[Pl_n].cpu_aim_angle==4) {
					Pl[Pl_n].cpu_state=0;
					Pl[Pl_n].cpu_state_cnt=0;
					block_hold(Pl_n);
				} else {
					Pl[Pl_n].cpu_state=1;
					Pl[Pl_n].cpu_state_cnt=0;
				}
				break;
			case 1: //回転＆移動
				/*if (Pl[Pl_n].block.gx>Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,-1);
				else if (Pl[Pl_n].block.gx<Pl[Pl_n].cpu_aim_position) block_lrmove(Pl_n,1);*/

				block_lrmove(Pl_n,Pl[Pl_n].cpu_aim_position-Pl[Pl_n].block.gx);

				if (Pl[Pl_n].block.angle<=5) {
					if ((Pl[Pl_n].cpu_aim_angle-Pl[Pl_n].block.angle+1)%4-1<0) block_turn(Pl_n,1,0);
					else if ((Pl[Pl_n].cpu_aim_angle-Pl[Pl_n].block.angle+1)%4-1>0) block_turn(Pl_n,0,1);
				}

				if (Pl[Pl_n].cpu_state_cnt>=2 && (Pl[Pl_n].cpu_aim_angle-Pl[Pl_n].block.angle)%4==0 && Pl[Pl_n].cpu_aim_position-Pl[Pl_n].block.gx==0) Pl[Pl_n].cpu_state=2;

				break;
			case 2: //落とす
				Pl[Pl_n].cpu_state=0;
				Pl[Pl_n].cpu_state_cnt=0;
				block_harddrop(Pl_n);
				break;
			case 3:
				if (Pl[Pl_n].cpu_state_cnt%4==3) {Pl[Pl_n].cpu_state=0; Pl[Pl_n].cpu_state_cnt=0;}
				break;
			}
		}

		Pl[Pl_n].cpu_state_cnt++;
	}
}

void block_move() {
	int i,j,k;
	int flag=0;
	int nx,ny;
	block_point n_block[BLOCK_MAX];

	for (i=0;i<Pl_num;i++) {
		if (Pl[i].block.flag==1 && pause_flag==0) {

			turn_cal(Pl[i].block.kind,Pl[i].block.angle,n_block);
			
			for (j=-Pl[i].block.delay_y;j>0;j--) {

				flag=0;

				for (k=0;k<block[Pl[i].block.kind].n;k++) {
					nx=(int)(Pl[i].block.gx+n_block[k].x);
					ny=(int)((int)(Pl[i].block.gy)+n_block[k].y+j);

					if (!( ny<BOARD_Y_MAX && Pl[i].board[nx][ny] == 0 ) ){
						flag=1;
						break;
					}
				}

				if (flag==0) {
					Pl[i].block.gy=(int)(Pl[i].block.gy)+j;
					Pl[i].block.delay_y+=j;
					break;
				}

			}
		}
	}

}

void block_cal(){
	int i;

	for (i=0;i<Pl_num;i++) {
		if (Pl[i].block.flag==1 && Pl[i].pause_flag==0) {
			/*if (b_info[i].touchflag==0) {
				b_info[i].gy+=b_info[i].v;
			}*/
			//b_info[i].v += 0.003;
			if (Pl[i].block.n_delay_y<-5.0) {
				temp[0]+=0;
			}
			if (Pl[i].block.delay_y - Pl[i].block.n_delay_y < -10.0) {
				temp[0]+=0;
			}
			Pl[i].block.n_delay_y = Pl[i].block.delay_y + duv_2( Pl[i].block.n_delay_y - Pl[i].block.delay_y , 0.4 );
			Pl[i].block.y = (Pl[i].block.gy-Pl[i].block.delay_y+Pl[i].block.n_delay_y)*BLOCK_SIZE;
			Pl[i].block.x = Pl[i].block.gx*BLOCK_SIZE + duv_2( Pl[i].block.x - Pl[i].block.gx * BLOCK_SIZE , 0.5 );
			Pl[i].block.cnt++;
		}
	}
}

void ghost_cal() {
	int i,j,k;
	int nx,ny;
	int flag=0;

	block_point n_block[BLOCK_MAX];

	for (i=0;i<Pl_num;i++) {
		if (Pl[i].block.flag==1) {

			turn_cal(Pl[i].block.kind,Pl[i].block.angle,n_block);

			flag=0;
		
			for (j=0;j<BOARD_Y_MAX && flag==0;j++) {
				for (k=0;k<block[Pl[i].block.kind].n;k++) {

					nx=(int)(Pl[i].block.gx+n_block[k].x);
					ny=(int)((int)(Pl[i].block.gy)+n_block[k].y+j);

					if (!( ny<BOARD_Y_MAX && Pl[i].board[nx][ny] == 0 ) ){
						Pl[i].ghost_down=j-1;
						flag=1;
						break;
					}

				}
			}

		}
	}
}

void block_main(){
	for (int i=0;i<Pl_num;i++)
		if (Pl[i].cpu_flag==0) block_key(i);
		else if (Pl[i].cpu_flag==1) cpu_key(i);
	block_move();
	block_control();
	block_cal();
	ghost_cal();
}