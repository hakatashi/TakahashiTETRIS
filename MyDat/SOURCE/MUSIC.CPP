#include "../include/GV.h"

void music_ini(){
	memset(se_flag,0,sizeof(int)*SE_MAX);
}

void bgm_play() {
	int i;
	if (bgm_state==0) {
		for (i=0;i<BGM_MAX;i++) {
			if (CheckSoundMem(bgm_handle[i])==1) StopSoundMem(bgm_handle[i]) ;
		}
	} else if (bgm_state==1) {
		for (i=0;i<BGM_MAX;i++) {
			if (CheckSoundMem(bgm_handle[i])==1) StopSoundMem(bgm_handle[i]) ;
		}
		PlaySoundMem( bgm_handle[bgm_num] , DX_PLAYTYPE_LOOP ) ;
		bgm_state++;
	} else {
		bgm_state++;
	}
}

void music_play(){
	int i;
	for(i=0;i<SE_MAX;i++){
		if(se_flag[i]==1) {
			PlaySoundMem(se_handle[i],DX_PLAYTYPE_BACK);
		}
	}

	bgm_play();
}