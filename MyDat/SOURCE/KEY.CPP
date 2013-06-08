#include "../include/GV.h"

unsigned int stateKey[256];

int GetHitKeyStateAll_2(){
    char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
    for(int i=0;i<256;i++){
		if (GetHitKeyStateAll_Key[i]==1) stateKey[i]++;
		else stateKey[i]=0;
    }
    return 0;
}

int CheckStateKey(unsigned char Handle){
	return stateKey[Handle];
}

//引数１と引数２のうち大きい方を引数１に代入する
void input_pad_or_key(int *p, int k){
	*p = *p>k ? *p : k;
}

//パッドとキーボードの両方の入力をチェックする関数
void GetHitPadStateAll(){
	int h,i,PadInput,mul=1;
	for (h=0;h<PLAYER_MAX;h++) {
		switch(h) {
		case 0:
			PadInput = GetJoypadInputState( DX_INPUT_PAD1 );//パッドの入力状態を取得
			break;
		case 1:
			PadInput = GetJoypadInputState( DX_INPUT_PAD2 );//パッドの入力状態を取得
			break;
		case 2:
			PadInput = GetJoypadInputState( DX_INPUT_PAD3 );//パッドの入力状態を取得
			break;
		case 3:
			PadInput = GetJoypadInputState( DX_INPUT_PAD4 );//パッドの入力状態を取得
			break;
		}
		for(i=0;i<16;i++){
			if(PadInput & mul)  pad[h].key[i]++;
			else		pad[h].key[i]=0;
			mul*=2;
		}
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].left]   ,CheckStateKey(configpad[Pl[h].keyboard_num+4].left  ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].up]     ,CheckStateKey(configpad[Pl[h].keyboard_num+4].up    ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].right]  ,CheckStateKey(configpad[Pl[h].keyboard_num+4].right ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].down]   ,CheckStateKey(configpad[Pl[h].keyboard_num+4].down  ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].hold]   ,CheckStateKey(configpad[Pl[h].keyboard_num+4].hold  ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].turn_L] ,CheckStateKey(configpad[Pl[h].keyboard_num+4].turn_L));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].turn_R] ,CheckStateKey(configpad[Pl[h].keyboard_num+4].turn_R));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].key1]   ,CheckStateKey(configpad[Pl[h].keyboard_num+4].key1  ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].key2]   ,CheckStateKey(configpad[Pl[h].keyboard_num+4].key2  ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].key3]   ,CheckStateKey(configpad[Pl[h].keyboard_num+4].key3  ));
		input_pad_or_key(&pad[Pl[h].pad_num].key[configpad[Pl[h].pad_num].pause]  ,CheckStateKey(configpad[Pl[h].keyboard_num+4].pause ));
	}
}

//標準入力をチェックする関数
void GetHitPadStateDefault(){
	int h,i,PadInput,mul=1;

	PadInput = GetJoypadInputState( DX_INPUT_PAD1 );//パッドの入力状態を取得
	
	for(i=0;i<16;i++){
		if(PadInput & mul)  pad[PLAYER_MAX].key[i]++;
		else		pad[PLAYER_MAX].key[i]=0;
		mul*=2;
	}

	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].left]   ,CheckStateKey(configpad[PLAYER_MAX].left  ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].up]     ,CheckStateKey(configpad[PLAYER_MAX].up    ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].right]  ,CheckStateKey(configpad[PLAYER_MAX].right ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].down]   ,CheckStateKey(configpad[PLAYER_MAX].down  ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].hold]   ,CheckStateKey(configpad[PLAYER_MAX].hold  ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].turn_L] ,CheckStateKey(configpad[PLAYER_MAX].turn_L));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].turn_R] ,CheckStateKey(configpad[PLAYER_MAX].turn_R));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].key1]   ,CheckStateKey(configpad[PLAYER_MAX].key1  ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].key2]   ,CheckStateKey(configpad[PLAYER_MAX].key2  ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].key3]   ,CheckStateKey(configpad[PLAYER_MAX].key3  ));
	input_pad_or_key(&pad[PLAYER_MAX].key[configpad[0].pause]  ,CheckStateKey(configpad[PLAYER_MAX].pause ));
}

//渡されたパッドキー番号の入力状態を返す。返り値が-1なら不正
int CheckStatePad(int Pl_n,unsigned int Handle){
	int i,j,k,maximam,ValidPlayer,ValidFlag,flag=0;
	flag+=0;
	if(0<=Handle && Handle<PAD_MAX && 0<=Pl_n && Pl_n<PLAYER_MAX){
		if (Handle==PAD_NUM_LEFT) return pad[Pl_n].key[configpad[Pl_n].left];
		if (Handle==PAD_NUM_UP) return pad[Pl_n].key[configpad[Pl_n].up];
		if (Handle==PAD_NUM_RIGHT) return pad[Pl_n].key[configpad[Pl_n].right];
		if (Handle==PAD_NUM_DOWN) return pad[Pl_n].key[configpad[Pl_n].down];
		if (Handle==PAD_NUM_HOLD) return pad[Pl_n].key[configpad[Pl_n].hold];
		if (Handle==PAD_NUM_TURN_L) return pad[Pl_n].key[configpad[Pl_n].turn_L];
		if (Handle==PAD_NUM_TURN_R) return pad[Pl_n].key[configpad[Pl_n].turn_R];
		if (Handle==PAD_NUM_KEY1) return pad[Pl_n].key[configpad[Pl_n].key1];
		if (Handle==PAD_NUM_KEY2) return pad[Pl_n].key[configpad[Pl_n].key2];
		if (Handle==PAD_NUM_KEY3) return pad[Pl_n].key[configpad[Pl_n].key3];
		if (Handle==PAD_NUM_PAUSE) return pad[Pl_n].key[configpad[Pl_n].pause];
	}
	else if (0<=Handle && Handle<PAD_MAX && Pl_n==-1) {
		if (gameflag==0 || all_cpu_flag==1) {
			if (Handle==PAD_NUM_LEFT) return pad[PLAYER_MAX].key[configpad[0].left];
			if (Handle==PAD_NUM_UP) return pad[PLAYER_MAX].key[configpad[0].up];
			if (Handle==PAD_NUM_RIGHT) return pad[PLAYER_MAX].key[configpad[0].right];
			if (Handle==PAD_NUM_DOWN) return pad[PLAYER_MAX].key[configpad[0].down];
			if (Handle==PAD_NUM_HOLD) return pad[PLAYER_MAX].key[configpad[0].hold];
			if (Handle==PAD_NUM_TURN_L) return pad[PLAYER_MAX].key[configpad[0].turn_L];
			if (Handle==PAD_NUM_TURN_R) return pad[PLAYER_MAX].key[configpad[0].turn_R];
			if (Handle==PAD_NUM_KEY1) return pad[PLAYER_MAX].key[configpad[0].key1];
			if (Handle==PAD_NUM_KEY2) return pad[PLAYER_MAX].key[configpad[0].key2];
			if (Handle==PAD_NUM_KEY3) return pad[PLAYER_MAX].key[configpad[0].key3];
			if (Handle==PAD_NUM_PAUSE) return pad[PLAYER_MAX].key[configpad[0].pause];
		} else {
			maximam=-1;
			for (i=0;i<Pl_num;i++) {
				if (maximam<(k=CheckStatePad(i,Handle)) || i==0) {
					maximam=k;
					PadPushPlayer=i;
				}
			}
			return maximam;
		}
	} else {
		printfDx("CheckStatePadに渡した値が不正です\n");
		return -1;
	}
}