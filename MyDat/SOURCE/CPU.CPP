#include "../include/GV.h"

void cpu_cal_num_old1(int n_kind,int n_hold,int *return_angle,int *return_position) {
	int i,j,k,l;
	int touch;
	int max_touch=1;
	int max_drop=0;
	int max_angle,max_position;
	int nx,ny;
	int flag=0;
	int kind=n_kind;
	int drop;
	block_point n_block[BLOCK_MAX];


	for (j=0;j<4;j++) {

		turn_cal( n_kind , j , n_block );

		for (i=-2;i<BOARD_X_MAX+2;i++) {
			
			flag=0;
			touch=0;

			for (k=0;k<BOARD_Y_MAX+1 && flag==0;k++) {
				for (l=0;l<block[kind].n;l++) {

					nx=i+n_block[l].x;
					ny=k+n_block[l].y;

					if (nx<0 || nx>=BOARD_X_MAX){
						flag=1;
						break;
					}

					if (ny>=0 && (board[nx][ny]!=0 || ny>=BOARD_Y_MAX)) {
						drop=k-1;
						flag=2;
						break;
					}

				}
			}

			if (flag==1) {
				touch=0;
			} else if (flag==2) {
				for (l=0;l<block[kind].n;l++) {

					nx=i+n_block[l].x;
					ny=drop+n_block[l].y;

					if (ny<10) {
						touch=0;
						break;
					}

					for (k=0;k<4;k++) {

						switch (k) {
						case 0:
							if (ny-1<0 || board[nx][ny-1]!=0) touch++;
							break;
						case 1:
							if (nx+1>=BOARD_X_MAX || board[nx+1][ny]!=0) touch++;
							break;
						case 2:
							if (ny+1>=BOARD_Y_MAX || board[nx][ny+1]!=0) touch++;
							break;
						case 3:
							if (nx-1<0 || board[nx-1][ny]!=0) touch++;
							break;
						}

					}

				}

				if (max_touch<touch || (max_touch==touch && max_drop<drop)) {
					max_touch=touch;
					max_drop=drop;
					max_angle=j;
					max_position=i;
				}

			} else {
				touch=0;
			}

			if (i==3 && j==1) {
				i+=0;
			}

		}
	}


	*return_angle=max_angle;
	*return_position=max_position;
}

void cpu_cal_num_old2(int n_kind,int n_hold,int *return_angle,int *return_position) {
	int i,j,k,l,m;
	int touch;
	int max_touch=1;
	int max_drop=0;
	int max_angle,max_position;
	int max_state=0;
	int nx,ny;
	int flag=0;
	int kind;
	int drop;
	block_point n_block[BLOCK_MAX];

	for (m=0;m<2;m++) {

		if (m==0) kind=n_kind;
		else if (n_kind!=n_hold) kind=n_hold;
		else break;

		for (j=0;j<4;j++) {

			turn_cal( kind , j , n_block );

			for (i=-2;i<BOARD_X_MAX+2;i++) {
			
				flag=0;
				touch=0;

				for (k=0;k<BOARD_Y_MAX+1 && flag==0;k++) {
					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=k+n_block[l].y;

						if (nx<0 || nx>=BOARD_X_MAX){
							flag=1;
							break;
						}

						if (ny>=0 && (board[nx][ny]!=0 || ny>=BOARD_Y_MAX)) {
							drop=k-1;
							flag=2;
							break;
						}

					}
				}

				if (flag==1) {
					touch=0;
				} else if (flag==2) {
					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=drop+n_block[l].y;

						if (ny<10) {
							touch=0;
							break;
						}

						for (k=0;k<4;k++) {

							switch (k) {
							case 0:
								if (ny-1<0 || board[nx][ny-1]!=0) touch++;
								break;
							case 1:
								if (nx+1>=BOARD_X_MAX || board[nx+1][ny]!=0) touch++;
								break;
							case 2:
								if (ny+1>=BOARD_Y_MAX || board[nx][ny+1]!=0) touch++;
								break;
							case 3:
								if (nx-1<0 || board[nx-1][ny]!=0) touch++;
								break;
							}

						}

					}

					if (max_touch<touch || (max_touch==touch && max_drop<drop) || GetRand(30)==0) {
						max_touch=touch;
						max_drop=drop;
						max_angle=j;
						max_position=i;
						max_state=m;
					}

				} else {
					touch=0;
				}

				if (i==3 && j==1) {
					i+=0;
				}

			}
		}

	}

	if (max_state==0) *return_angle=max_angle;
	else *return_angle=4;
	*return_position=max_position;
}

void cpu_cal_num_old3(int n_kind,int n_hold,int *return_angle,int *return_position) {
	int i,j,k,l,m;
	int touch,untouch;
	int min_untouch=9999;
	int max_drop=0;
	int max_angle,max_position;
	int max_state=0;
	int nx,ny;
	int flag=0;
	int kind;
	int drop;
	block_point n_block[BLOCK_MAX];

	for (m=0;m<2;m++) {

		if (m==0) kind=n_kind;
		else if (n_kind!=n_hold) kind=n_hold;
		else break;

		for (j=0;j<4;j++) {

			turn_cal( kind , j , n_block );

			for (i=-2;i<BOARD_X_MAX+2;i++) {
			
				flag=0;
				touch=0;

				for (k=0;k<BOARD_Y_MAX+1 && flag==0;k++) {
					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=k+n_block[l].y;

						if (nx<0 || nx>=BOARD_X_MAX){
							flag=1;
							break;
						}

						if (ny>=0 && (board[nx][ny]!=0 || ny>=BOARD_Y_MAX)) {
							drop=k-1;
							flag=2;
							break;
						}

					}
				}

				if (flag==1) {
					touch=0;
				} else if (flag==2) {
					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=drop+n_block[l].y;

						if (ny<10) {
							touch=0;
							break;
						}

						for (k=0;k<4;k++) {

							switch (k) {
							case 0:
								if (ny-1<0 || board[nx][ny-1]!=0) touch++;
								break;
							case 1:
								if (nx+1>=BOARD_X_MAX || board[nx+1][ny]!=0) touch++;
								break;
							case 2:
								if (ny+1>=BOARD_Y_MAX || board[nx][ny+1]!=0) touch++;
								break;
							case 3:
								if (nx-1<0 || board[nx-1][ny]!=0) touch++;
								break;
							}

						}

					}

					untouch=block[kind].surface-touch;

					if (min_untouch>untouch || (min_untouch==untouch && max_drop<drop)) {
						min_untouch=untouch;
						max_drop=drop;
						max_angle=j;
						max_position=i;
						max_state=m;
					}

				} else {
					touch=0;
				}

				if (i==3 && j==1) {
					i+=0;
				}

			}
		}

	}

	if (max_state==0) *return_angle=max_angle;
	else *return_angle=4;
	*return_position=max_position;
}

void cpu_cal_num_old4(int n_kind,int n_hold,int *return_angle,int *return_position) {
	int i,j,k,l,m;
	int touch,untouch;
	int min_untouch=9999;
	int max_drop=0;
	int max_angle,max_position;
	int max_state=0;
	int nx,ny;
	int flag=0;
	int kind;
	int drop;
	int n_drop;
	int height[BOARD_X_MAX];
	block_point n_block[BLOCK_MAX];

	for (i=0;i<BOARD_X_MAX;i++) {

		for (j=0;j<BOARD_Y_MAX;j++) {
			if (board[i][j]!=0) {
				height[i]=BOARD_Y_MAX-j;
				break;
			}
		}

		if (j==BOARD_Y_MAX) height[i]=0;

	}

	for (m=0;m<2;m++) {

		if (m==0) kind=n_kind;
		else if (n_kind!=n_hold) kind=n_hold;
		else break;

		for (j=0;j<4;j++) {

			turn_cal( kind , j , n_block );

			for (i=-2;i<BOARD_X_MAX+2;i++) {
			
				flag=0;
				touch=0;

				drop=BOARD_Y_MAX;

				for (l=0;l<block[kind].n;l++) {

					nx=i+n_block[l].x;

					if (nx<0 || nx>=BOARD_X_MAX){
						flag=1;
						break;
					}

					n_drop=(BOARD_Y_MAX-height[nx]-1)-n_block[l].y;

					if (drop>n_drop) {
						drop=n_drop;
					}

				}

				if (flag==1) {
					touch=0;
				} else {
					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=BOARD_Y_MAX-(drop+n_block[l].y);

						if (ny>20) {
							touch=0;
							break;
						}

						for (k=1;k<4;k++) {

							switch (k) {
							/*case 0:
								if (ny-1<0 || board[nx][ny-1]!=0) touch++;
								break;*/
							case 1:
								if (nx+1>=BOARD_X_MAX || height[nx+1]>=ny) touch++;
								break;
							case 2:
								if (drop+n_block[l].y+1>=BOARD_Y_MAX || ny-1==height[nx]) touch++;
								break;
							case 3:
								if (nx-1<0 || height[nx-1]>=ny) touch++;
								break;
							}

						}

					}

					untouch=block[kind].surface-touch;

					if (min_untouch>untouch || (min_untouch==untouch && max_drop<drop)) {
						min_untouch=untouch;
						max_drop=drop;
						max_angle=j;
						max_position=i;
						max_state=m;
					}

				}

			}
		}

	}

	if (max_state==0) *return_angle=max_angle;
	else *return_angle=4;
	*return_position=max_position;
}

void cpu_cal_num_weak(int Pl_n,int n_kind,int n_hold,int *return_angle,int *return_position,int priority) {
	int i,j,k,l,m,n;
	int touch,untouch;
	int min_untouch[5]={9999,9999,9999,9999,9999};
	int max_drop[5]={0,0,0,0,0};
	int max_angle[5],max_position[5];
	int max_state[5]={0,0,0,0,0};
	int min_dig[5]={BOARD_X_MAX*BOARD_Y_MAX,BOARD_X_MAX*BOARD_Y_MAX,BOARD_X_MAX*BOARD_Y_MAX,BOARD_X_MAX*BOARD_Y_MAX,BOARD_X_MAX*BOARD_Y_MAX};
	int nx,ny;
	int flag=0;
	int out_flag;
	int renew_flag;
	int cpu_gameover_flag;
	int kind;
	int drop;
	int dig;
	int n_drop;
	int height[BOARD_X_MAX];
	int height_n[BOARD_X_MAX];
	int add_height[BOARD_X_MAX];
	int hole_n[BOARD_Y_MAX];
	int hole[BOARD_Y_MAX][BOARD_X_MAX];
	int turn_time;
	int clear_line;
	int clear_line_l[BOARD_Y_MAX];
	int max_clear_line[5]={0,0,0,0,0};
	int n_block_y_min;
	int n_block_y_max;
	block_point n_block[BLOCK_MAX];

	for (i=0;i<BOARD_X_MAX;i++) {

		for (j=0;j<BOARD_Y_MAX;j++) {
			if (Pl[Pl_n].board[i][j]!=0) {
				height[i]=BOARD_Y_MAX-j;
				break;
			}
		}

		if (j==BOARD_Y_MAX) height[i]=0;
	}

	for (i=0;i<BOARD_Y_MAX;i++) {
		hole_n[i]=0;
		for (j=0;j<BOARD_X_MAX;j++) {
			if (Pl[Pl_n].board[j][i]==0 && BOARD_Y_MAX-height[j]<=i) {
				hole[i][hole_n[i]]=j;
				hole_n[i]++;
			}
		}
	}

	for (m=0;m<2;m++) {

		if (m==0) kind=n_kind;
		else if (n_kind!=n_hold && Pl[Pl_n].cpu_mode.hold==1 && Pl[Pl_n].holdflag==0) kind=n_hold;
		else break;
		
		if (block[kind].type==0) turn_time=4;
		if (block[kind].type==1) turn_time=1;
		if (block[kind].type==2) turn_time=2;

		for (j=0;j<turn_time;j++) {

			turn_cal( kind , j , n_block );

			n_block_y_min=0;
			n_block_y_max=0;
			for (i=0;i<block[kind].n;i++) {
				if (n_block_y_min>n_block[i].y) n_block_y_min=n_block[i].y;
				if (n_block_y_max<n_block[i].y) n_block_y_max=n_block[i].y;
			}

			for (i=-2;i<BOARD_X_MAX+2;i++) {
			
				flag=0;
				touch=0;

				drop=BOARD_Y_MAX;

				for (l=0;l<block[kind].n;l++) {

					nx=i+n_block[l].x;

					if (nx<0 || nx>=BOARD_X_MAX){
						flag=1;
						break;
					}

					n_drop=(BOARD_Y_MAX-height[nx]-1)-n_block[l].y;

					if (drop>n_drop) {
						drop=n_drop;
					}

				}

				for (k=0;k<BOARD_X_MAX;k++) {
					add_height[k]=0;
				}

				if (flag==1) {
					touch=0;
				} else {

					cpu_gameover_flag=0;

					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=BOARD_Y_MAX-(drop+n_block[l].y);

						//ƒQ[ƒ€ƒI[ƒo[Flag‚ÌZo
						if (ny>20) {
							cpu_gameover_flag=1;
							break;
						}

						//ÚG–ÊÏ‚ÌZo
						for (k=1;k<4;k++) {

							switch (k) {
							/*case 0:
								if (ny-1<0 || Pl[Pl_n].board[nx][ny-1]!=0) touch++;
								break;*/
							case 1:
								if (nx+1>=BOARD_X_MAX || height[nx+1]>=ny) touch++;
								break;
							case 2:
								if (drop+n_block[l].y+1>=BOARD_Y_MAX || ny-1==height[nx]) touch++;
								break;
							case 3:
								if (nx-1<0 || height[nx-1]>=ny) touch++;
								break;
							}

						}

						//ŒvZŒã‚ÌŠe—ñ‚Ì‚‚³‚ğZoB‚±‚ê‚ğŒ³‚É–„–v–ÊÏ‚ğŒvZB
						if (ny-height[nx]>add_height[nx]) {
							add_height[nx]=ny-height[nx];
						}

					}

					/*flag=0;
					for (k=0;k<BOARD_X_MAX;k++) {
						if (add_height[k]>0) {flag=1; break;}
					}
					if (flag==0) {
						flag+=0;
					}*/

					//Á‹—ñ”‚ÌZo
					clear_line=0;

					for (k=0;k<BOARD_Y_MAX;k++) clear_line_l[k]=0;

					for (k=n_block_y_min;k<=n_block_y_max;k++) {

						if (hole_n[k+drop]>0) continue;

						out_flag=0;

						for (l=0;l<BOARD_X_MAX;l++) {
							if (height[l]<BOARD_Y_MAX-(k+drop)) {

								flag=0;

								for (n=0;n<block[kind].n;n++) {
									if (n_block[n].x+i==l && n_block[n].y==k) {
										flag=1;
										break;
									}
								}
								
								if (flag==0) {
									out_flag=1;
									break;
								}

							}
						}

						if (out_flag==0) {
							clear_line++;
							clear_line_l[k+drop]=1;
						}

					}

					if (clear_line>=2) {
						clear_line+=0;
					}

					//–„–v–ÊÏ‚ÌZo
					dig=-block[kind].n;

					for (k=0;k<BOARD_X_MAX;k++) {
						dig+=add_height[k];
					}

					if (clear_line>0) {
						//—ñÁ‚µ‚ª‚ ‚Á‚½ê‡‚ÌŠe—ñ‚Ì‚‚³‚ğZoB
						for (k=0;k<BOARD_X_MAX;k++) {
							for (l=0;l<BOARD_Y_MAX;l++) {
								if (Pl[Pl_n].board[k][l] != 0 && clear_line_l[l]==0) break;
							}

							if (l==BOARD_Y_MAX) {
								height_n[k]=0;
								continue;
							} else height_n[k]=BOARD_Y_MAX-l;

							for (l++;l<BOARD_Y_MAX;l++) {
								if (clear_line_l[l]==1) height_n[k]--;
							}
						}
					
						//ƒuƒƒbƒN‚Ì”z’u‚ğl—¶‚É“ü‚ê‚é
						for (l=0;l<block[kind].n;l++) {

							nx=i+n_block[l].x;
							ny=BOARD_Y_MAX-(drop+n_block[l].y);
						
							for (k=BOARD_Y_MAX-ny;k<BOARD_Y_MAX;k++) {
								if (clear_line_l[k]==1) ny--;
							}

							if (ny>height_n[nx]) {
								height_n[nx]=ny;
							}

						}

						/*****************************************
						–„–v–ÊÏ‚Ì‘Œ¸‚ÍA
						y”z’uŒã‚Ì–„–v–ÊÏz|y”z’u‘O‚Ì–„–v–ÊÏz
						y”z’uŒã‚ÌƒuƒƒbƒN”z{y”z’uŒã‚Ì–„–v–ÊÏz|iy”z’u‘O‚Ì—ñ”‚ÌƒuƒƒbƒN”z{y”z’u‘O‚Ì–„–v–ÊÏz{yƒuƒƒbƒN‚Ì”z|y‰¡•z~yÁ‚µ‚½—ñ”zj
						y”z’uŒã‚Ì—ñ”‚Ì˜az|iy”z’u‘O‚Ì—ñ”‚Ì˜az{yƒuƒƒbƒN‚Ì”z|y‰¡•z~yÁ‚µ‚½—ñ”zj
						y‰¡•z~yÁ‚µ‚½—ñ”z|yƒuƒƒbƒN‚Ì”z|y”z’u‘O‚Ì—ñ”‚Ì˜az{y”z’uŒã‚Ì—ñ”‚Ì˜az
						*****************************************/

						dig=BOARD_X_MAX*clear_line-block[kind].n;

						for (k=0;k<BOARD_X_MAX;k++) {
							dig=dig-height[k]+height_n[k];
						}
					}
					
					//”ñÚG–ÊÏ‚ÌZo
					untouch=block[kind].surface-touch;

					if (dig<=-1 && cpu_gameover_flag==0) {
						dig+=0;
					}

					renew_flag=0;
					for (k=0;k<5;k++) {
						if (Pl[Pl_n].cpu_mode.pattern==0) {
							if (cpu_gameover_flag==0) {
								if (dig<=-1 && min_dig[k]>-1) {renew_flag=k+1; break;}
								else {
									if (min_untouch[k]>untouch) {renew_flag=k+1; break;}
									else if (min_untouch[k]==untouch) {
										if (min_dig[k]>dig) {renew_flag=k+1; break;}
										else if (min_dig[k]==dig) {
											if (max_drop[k]<drop) {renew_flag=k+1; break;}
										}
									}
								}
							}
						} else if (Pl[Pl_n].cpu_mode.pattern==1) {
							if (cpu_gameover_flag==0) {
								if (min_dig[k]>dig) {renew_flag=k+1; break;}
								else if (min_dig[k]==dig) {
									if (min_untouch[k]>untouch) {renew_flag=k+1; break;}
									else if (min_untouch[k]==untouch) {
										if (max_drop[k]<drop) {renew_flag=k+1; break;}
									}
								}
							}
						} else if (Pl[Pl_n].cpu_mode.pattern==2) {
							if (cpu_gameover_flag==0) {
								if (max_clear_line[k]<clear_line) {renew_flag=k+1; break;}
								else if (max_clear_line[k]==clear_line) {
									if (max_drop[k]<drop) {renew_flag=k+1; break;}
									else if (max_drop[k]==drop) {
										/*if (min_dig[k]>dig) {renew_flag=k+1; break;}
										else if (min_dig[k]==dig) {
											if (min_untouch[k]>untouch) {renew_flag=k+1; break;}
											/*else if (min_untouch[k]==untouch) {
												if (min_dig[k]>dig) {renew_flag=k+1; break;}
												/*else if (min_dig[k]==dig) {
													if (max_drop[k]<drop) {renew_flag=k+1; break;}
												}
											}
										}*/
										if (min_untouch[k]>untouch) {renew_flag=k+1; break;}
										else if (min_untouch[k]==untouch) {
											if (min_dig[k]>dig) {renew_flag=k+1; break;}
											/*else if (min_dig[k]==dig) {
												if (max_drop[k]<drop) {renew_flag=k+1; break;}
											}*/
										}
									}
								}
							}
						}
					}

					if (renew_flag>=1) {

						for (k=4;k>renew_flag-1;k--) {
							min_untouch[k]=min_untouch[k-1];
							max_drop[k]=max_drop[k-1];
							max_angle[k]=max_angle[k-1];
							max_position[k]=max_position[k-1];
							min_dig[k]=min_dig[k-1];
							max_state[k]=max_state[k-1];
							max_clear_line[k]=max_clear_line[k-1];
						}

						min_untouch[renew_flag-1]=untouch;
						max_drop[renew_flag-1]=drop;
						max_angle[renew_flag-1]=j;
						max_position[renew_flag-1]=i;
						min_dig[renew_flag-1]=dig;
						max_state[renew_flag-1]=m;
						max_clear_line[renew_flag-1]=clear_line;
					}

				}

			}
		}

	}

	if (max_state[priority]==0) *return_angle=max_angle[priority];
	else *return_angle=4;
	*return_position=max_position[priority];

	/*if (min_dig>0) {
		StopSoundMem( bgm_handle[bgm_num] ) ;
		pause_select=0;
		func_state=999;
	}*/

}
void cpu_cal_num(int Pl_n,int n_kind,int n_hold,int *return_angle,int *return_position) {
	int i,j,k,l,m;
	int touch,untouch;
	int min_untouch=9999;
	int max_drop=0;
	int max_angle,max_position;
	int max_state=0;
	int min_dig=BOARD_X_MAX*BOARD_Y_MAX;
	int nx,ny;
	int flag=0;
	int renew_flag;
	int cpu_gameover_flag;
	int kind;
	int drop;
	int dig;
	int n_drop;
	int height[BOARD_X_MAX];
	int add_height[BOARD_X_MAX];
	int turn_time;
	block_point n_block[BLOCK_MAX];

	for (i=0;i<BOARD_X_MAX;i++) {

		for (j=0;j<BOARD_Y_MAX;j++) {
			if (Pl[Pl_n].board[i][j]!=0) {
				height[i]=BOARD_Y_MAX-j;
				break;
			}
		}

		if (j==BOARD_Y_MAX) height[i]=0;

	}

	for (m=0;m<2;m++) {

		if (m==0) kind=n_kind;
		else if (n_kind!=n_hold && Pl[Pl_n].cpu_mode.hold==1 && holdflag==0) kind=n_hold;
		else break;
		
		if (block[kind].type==0) turn_time=4;
		if (block[kind].type==1) turn_time=1;
		if (block[kind].type==2) turn_time=2;

		for (j=0;j<turn_time;j++) {

			turn_cal( kind , j , n_block );

			for (i=-2;i<BOARD_X_MAX+2;i++) {
			
				flag=0;
				touch=0;

				drop=BOARD_Y_MAX;

				for (l=0;l<block[kind].n;l++) {

					nx=i+n_block[l].x;

					if (nx<0 || nx>=BOARD_X_MAX){
						flag=1;
						break;
					}

					n_drop=(BOARD_Y_MAX-height[nx]-1)-n_block[l].y;

					if (drop>n_drop) {
						drop=n_drop;
					}

				}

				for (k=0;k<BOARD_X_MAX;k++) {
					add_height[k]=0;
				}

				if (flag==1) {
					touch=0;
				} else {

					cpu_gameover_flag=0;

					for (l=0;l<block[kind].n;l++) {

						nx=i+n_block[l].x;
						ny=BOARD_Y_MAX-(drop+n_block[l].y);

						if (ny>20) {
							cpu_gameover_flag=1;
							break;
						}

						for (k=1;k<4;k++) {

							switch (k) {
							/*case 0:
								if (ny-1<0 || Pl[Pl_n].board[nx][ny-1]!=0) touch++;
								break;*/
							case 1:
								if (nx+1>=BOARD_X_MAX || height[nx+1]>=ny) touch++;
								break;
							case 2:
								if (drop+n_block[l].y+1>=BOARD_Y_MAX || ny-1==height[nx]) touch++;
								break;
							case 3:
								if (nx-1<0 || height[nx-1]>=ny) touch++;
								break;
							}

						}

						if (ny-height[nx]>add_height[nx]) {
							add_height[nx]=ny-height[nx];
						}

					}

					dig=-block[kind].n;

					for (k=0;k<BOARD_X_MAX;k++) {
						dig+=add_height[k];
					}

					untouch=block[kind].surface-touch;

					renew_flag=0;
					
					if (Pl[Pl_n].cpu_mode.pattern==0) {
						if (cpu_gameover_flag==0) {
							if (min_untouch>untouch) renew_flag=1;
							else if (min_untouch==untouch) {
								if (min_dig>dig) renew_flag=1;
								else if (min_dig==dig) {
									if (max_drop<drop) renew_flag=1;
								}
							}
						}
					} else if (Pl[Pl_n].cpu_mode.pattern==1) {
						if (cpu_gameover_flag==0) {
							if (min_dig>dig) renew_flag=1;
							else if (min_dig==dig) {
								if (min_untouch>untouch) renew_flag=1;
								else if (min_untouch==untouch) {
									if (max_drop<drop) renew_flag=1;
								}
							}
						}
					}

					if (renew_flag==1) {
						min_untouch=untouch;
						max_drop=drop;
						max_angle=j;
						max_position=i;
						min_dig=dig;
						max_state=m;
					}

				}

			}
		}

	}

	if (max_state==0) *return_angle=max_angle;
	else *return_angle=4;
	*return_position=max_position;

	/*if (min_dig>0) {
		StopSoundMem( bgm_handle[bgm_num] ) ;
		pause_select=0;
		func_state=999;
	}*/

}