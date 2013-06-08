#define GLOBAL_INSTANCE
#include "../include/GV.h"

void FullscreenMessage() {
	int flag;
	flag=MessageBox(
		NULL ,
		TEXT("�t���X�N���[���ŋN�����܂����H") ,
		TEXT("���A���̃e�g���X������������׋�����񂾁c") , 
		MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	if(flag==IDNO)
		ChangeWindowMode( TRUE );
}

//���[�v�ŕK���s���R�又��
int ProcessLoop(){
    if(ProcessMessage()!=0)return -1;//�v���Z�X�������G���[�Ȃ�-1��Ԃ�
    if(ClearDrawScreen()!=0)return -1;//��ʃN���A�������G���[�Ȃ�-1��Ԃ�
    GetHitKeyStateAll_2();//���݂̃L�[���͏������s��
	GetHitPadStateAll();
	GetHitPadStateDefault();
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){

	//FullscreenMessage();
	ChangeWindowMode( FALSE );

	SetMainWindowText("�����e�g���Xver0.04");
    if (DxLib_Init() == -1) return -1; //������

	load();

	if (SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//����ʉ�

	exe_cnt=0;
	func_state=0;

    while(ProcessLoop()==0){//���C�����[�v
			
		music_ini();

		switch(func_state){
		case 0: //�������[�h
			launch_ini();
			mode=0;
			menu_ini();
			func_state=1;
			break;
		case 1: //���S���
			graph_logo();
			break;
		case 2: //���j���[���
			control_menu();
			graph_menu();
			break;
		case 50: //���[�h�I�����
			control_menu();
			graph_menu();
			break;
		case 51: //���[�h�I����ڍs���
			graph_menu();
			menu_selected_cnt++;
			if (menu_selected_cnt>30) {
				first_ini();
				func_state=100;
			}
			break;
		case 100: //�Q�[�����C�����
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
		case 999: //�|�[�Y���
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
		case 101: //���U���g���
			control_result();
			graph_main();
			stage_cnt++;
			if (CheckStatePad(-1,PAD_NUM_HOLD)==1) func_state=102;
			break;
		case 102: //�Q�[���I�[�o�[��I�����
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
			printfDx("error:�s����func_state\n");
			break;
		}

		control_func_state();

		exe_cnt++;

		music_play();
	
		if(CheckStateKey(KEY_INPUT_ESCAPE)==1) break;//�G�X�P�[�v�����͂��ꂽ��u���C�N
		ScreenFlip();//����ʔ��f
    }

    DxLib_End();//�c�w���C�u�����I������
    return 0;
}