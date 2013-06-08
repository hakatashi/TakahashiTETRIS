#include "../include/GV.h"
#include <math.h>

void turn_cal(int kind,int angle,block_point *n_block) {
	int i,orig_x,orig_y,n;
	if (block[kind].y>block[kind].x) n=1;
	else n=0;
	for (i=0;i<block[kind].n;i++) {
		switch ((angle>=0)?(angle%4):((4-abs(angle)%4)%4)) {
		case 0:
			n_block[i].x=block[kind].p[i].x;
			n_block[i].y=block[kind].p[i].y;
			break;
		case 1:
			orig_x=(int)((block[kind].x+block[kind].y)/2)+n;
			orig_y=(int)((block[kind].y+block[kind].x)/2)-block[kind].x+n;
			n_block[i].x=orig_x-1-block[kind].p[i].y;
			n_block[i].y=orig_y+block[kind].p[i].x;
			break;
		case 2:
			orig_x=block[kind].x;
			orig_y=block[kind].y;
			n_block[i].x=orig_x-1-block[kind].p[i].x;
			n_block[i].y=orig_y-1-block[kind].p[i].y;
			break;
		case 3:
			orig_x=(int)((block[kind].x+block[kind].y)/2)-block[kind].y+n;
			orig_y=(int)((block[kind].x+block[kind].y)/2)+n;
			n_block[i].x=orig_x+block[kind].p[i].y;
			n_block[i].y=orig_y-1-block[kind].p[i].x;
			break;
		}
	}
}

double cent_point_cal_x( int kind , int angle ) {
	int n;
	if (block[kind].y>block[kind].x) n=1;
	else n=0;
	switch((angle>=0)?(angle%4):((4-abs(angle)%4)%4)) {
	case 0:
		return block[kind].x/2.0;
		break;
	case 1:
		return (int)((block[kind].x+block[kind].y)/2.0)+n-block[kind].y/2.0;
		break;
	case 2:
		return block[kind].x/2.0;
		break;
	case 3:
		return (int)((block[kind].x+block[kind].y)/2.0)+n-block[kind].y/2.0;
		break;
	}
	return -1;
}

double cent_point_cal_y( int kind , int angle ) {
	int n;
	if (block[kind].y>block[kind].x) n=1;
	else n=0;
	switch((angle>=0)?(angle%4):((4-abs(angle)%4)%4)) {
	case 0:
		return block[kind].y/2.0;
		break;
	case 1:
		return (int)((block[kind].y+block[kind].x)/2.0)+n-block[kind].x/2.0;
		break;
	case 2:
		return block[kind].y/2.0;
		break;
	case 3:
		return (int)((block[kind].x+block[kind].y)/2.0)+n-block[kind].x/2.0;
		break;
	}
	return -1;
}

double duv_2(double n , double k ) {
	double r;

	if (n>0) {

		r=sqrt(n)-k;

		if (r>0) return r*r;
		else return 0;

	} else {

		r=-sqrt(abs(n))+k;

		if (r<0) return -r*r;
		else return 0;

	}

}

double duv_2_p( double start, double aim, int nowtime, int alltime) {
	int remain=alltime-nowtime;
	if (remain>=0) return aim+(start-aim)*(remain*remain)/(double)(alltime*alltime);
	else return aim;
}

void cal_score() {
	int i,j,k;
	int rate;
	double rate2;

	for (k=0;k<Pl_num;k++) {
		Pl[k].score=0;
		Pl[k].score+=(int)Pl[k].dropline;
		Pl[k].score+=(int)(Pl[k].harddropline*2.0);
		for (i=0;i<10;i++) {
			switch(i) {
			case 0:	rate=40;	break;
			case 1:	rate=100;	break;
			case 2:	rate=300;	break;
			case 3:	rate=1200;	break;
			case 4:	rate=2400;	break;
			case 5:	rate=4800;	break;
			case 6:	rate=9600;	break;
			case 7:	rate=10000;	break;
			case 8:	rate=10000;	break;
			case 9:	rate=0;	break;
			}
			Pl[k].score+=(Pl[k].dis_line_times[i]+Pl[k].dis_line_AC_times[i]*49)*rate;

			for (j=0;j<20;j++) {
				switch(j) {
				case 2: rate2=1.5; break;
				case 3: rate2=2.0; break;
				case 4: rate2=3.5; break;
				case 5: rate2=5.0; break;
				case 6: rate2=7.0; break;
				case 7: rate2=10.0; break;
				case 8: rate2=15.0; break;
				case 9: rate2=20.0; break;
				case 10: rate2=30.0; break;
				default: rate2=1.0; break;
				}
				Pl[k].score+=Pl[k].combo_times[j][i]*rate*(rate2-1.0);
			}
		}
	}
}

int char_to_num(char ch) {
	switch(ch) {
	case 'A':	return 0;	break;
	case 'B':	return 1;	break;
	case 'C':	return 2;	break;
	case 'D':	return 3;	break;
	case 'E':	return 4;	break;
	case 'F':	return 5;	break;
	case 'G':	return 6;	break;
	case 'H':	return 7;	break;
	case 'I':	return 8;	break;
	case 'J':	return 9;	break;
	case 'K':	return 10;	break;
	case 'L':	return 11;	break;
	case 'M':	return 12;	break;
	case 'N':	return 13;	break;
	case 'O':	return 14;	break;
	case 'P':	return 15;	break;
	case 'Q':	return 16;	break;
	case 'R':	return 17;	break;
	case 'S':	return 18;	break;
	case 'T':	return 19;	break;
	case 'U':	return 20;	break;
	case 'V':	return 21;	break;
	case 'W':	return 22;	break;
	case 'X':	return 23;	break;
	case 'Y':	return 24;	break;
	case 'Z':	return 25;	break;
	case 'a':	return 26;	break;
	case 'b':	return 27;	break;
	case 'c':	return 28;	break;
	case 'd':	return 29;	break;
	case 'e':	return 30;	break;
	case 'f':	return 31;	break;
	case 'g':	return 32;	break;
	case 'h':	return 33;	break;
	case 'i':	return 34;	break;
	case 'j':	return 35;	break;
	case 'k':	return 36;	break;
	case 'l':	return 37;	break;
	case 'm':	return 38;	break;
	case 'n':	return 39;	break;
	case 'o':	return 40;	break;
	case 'p':	return 41;	break;
	case 'q':	return 42;	break;
	case 'r':	return 43;	break;
	case 's':	return 44;	break;
	case 't':	return 45;	break;
	case 'u':	return 46;	break;
	case 'v':	return 47;	break;
	case 'w':	return 48;	break;
	case 'x':	return 49;	break;
	case 'y':	return 50;	break;
	case 'z':	return 51;	break;
	case '0':	return 52;	break;
	case '1':	return 53;	break;
	case '2':	return 54;	break;
	case '3':	return 55;	break;
	case '4':	return 56;	break;
	case '5':	return 57;	break;
	case '6':	return 58;	break;
	case '7':	return 59;	break;
	case '8':	return 60;	break;
	case '9':	return 61;	break;
	case '.':	return 62;	break;
	case '!':	return 63;	break;
	case '?':	return 64;	break;
	case ',':	return 65;	break;
	case '%':	return 66;	break;
	case ':':	return 67;	break;
	case '"':	return 68;	break;
	case '=':	return 69;	break;
	case '&':	return 70;	break;
	case '-':	return 71;	break;
	case '+':	return 72;	break;
	case '<':	return 73;	break;
	case '>':	return 74;	break;
	case '~':	return 75;	break;
	case '(':	return 76;	break;
	case ')':	return 77;	break;
	default:	return -1;	break;
	}
}