#define GLOBAL_INSTANCE
#include "../include/GV.h"

void FullscreenMessage() {
	int flag;
	flag=MessageBox(
		NULL ,
		TEXT("フルスクリーンで起動しますか？") ,
		TEXT("俺、このテトリスが完成したら勉強するんだ…") , 
		MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	if(flag==IDNO)
		ChangeWindowMode( TRUE );
}

//ループで必ず行う３大処理
int ProcessLoop(){
    if(ProcessMessage()!=0)return -1;//プロセス処理がエラーなら-1を返す
    if(ClearDrawScreen()!=0)return -1;//画面クリア処理がエラーなら-1を返す
    GetHitKeyStateAll_2();//現在のキー入力処理を行う
	GetHitPadStateAll();
	GetHitPadStateDefault();
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){

	//FullscreenMessage();
	ChangeWindowMode( FALSE );

	SetMainWindowText("高橋テトリスver0.04");
    if (DxLib_Init() == -1) return -1; //初期化

	load();

	if (SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//裏画面化

	exe_cnt=0;
	func_state=0;

    while(ProcessLoop()==0){//メインループ
			
		music_ini();

		switch(func_state){
		case 0: //初期ロード
			launch_ini();
			mode=0;
			menu_ini();
			func_state=1;
			break;
		case 1: //ロゴ画面
			graph_logo();
			break;
		case 2: //メニュー画面
			control_menu();
			graph_menu();
			break;
		case 50: //モード選択画面
			control_menu();
			graph_menu();
			break;
		case 51: //モード選択後移行画面
			graph_menu();
			menu_selected_cnt++;
			if (menu_selected_cnt>30) {
				first_ini();
				func_state=100;
			}
			break;
		case 100: //ゲームメイン画面
			control_main();
			block_main();
			cal_score();
			graph_main();
			stage_cnt++;
			if (gameover_flag==1 && CheckStatePad(-1,PAD_NUM_HOLD)==1) {
				result_ini();
				func_state=101;
			}
			if (CheckStatePad(-1,PAD_NUM_PAUSE)==1) {
				pause_push_Pl=PadPushPlayer;
				StopSoundMem( bgm_handle[bgm_num] ) ;
				pause_select=0;
				func_state=999;
			}
			break;
		case 999: //ポーズ画面
			control_game_pause();
			graph_main();
			if (CheckStatePad((all_cpu_flag==0)?pause_push_Pl:-1,PAD_NUM_HOLD)==1) {
				switch (pause_select) {
				case 0:
					PlaySoundMem( bgm_handle[bgm_num] , DX_PLAYTYPE_LOOP , FALSE ) ;
					func_state=100;
					break;
				case 1:
					first_ini();
					func_state=100;
					break;
				case 2:
					menu_ini();
					func_state=50;
					break;
				}
			}
			if (CheckStatePad((all_cpu_flag==0)?pause_push_Pl:-1,PAD_NUM_PAUSE)==1) {
				PlaySoundMem( bgm_handle[bgm_num] , DX_PLAYTYPE_LOOP , FALSE ) ;
				func_state=100;
			}
			break;
		case 101: //リザルト画面
			control_result();
			graph_main();
			stage_cnt++;
			if (CheckStatePad(-1,PAD_NUM_HOLD)==1) func_state=102;
			break;
		case 102: //ゲームオーバー後選択画面
			control_over_select();
			graph_main();
			stage_cnt++;
			if (CheckStatePad(-1,PAD_NUM_HOLD)==1) {
				switch (over_select) {
				case 0:
					first_ini();
					func_state=100;
					break;
				case 1:
					menu_ini();
					menu_select=mode;
					func_state=50;
					break;
				case 3:
					func_state=101;
					break;
				}
			}
			break;
		default:
			printfDx("error:不明なfunc_state\n");
			break;
		}

		control_func_state();

		exe_cnt++;

		music_play();
	
		if(CheckStateKey(KEY_INPUT_ESCAPE)==1) break;//エスケープが入力されたらブレイク
		ScreenFlip();//裏画面反映
    }

    DxLib_End();//ＤＸライブラリ終了処理
    return 0;
}