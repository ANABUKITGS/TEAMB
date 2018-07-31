#include "myLib.h"
#include "game.h"

//���[�J���ϐ�
CGame*		g_pMain = NULL;
const bool	WINDOW_SCREEN = true;

//���[�J���֐�
void win_main_init();
void win_main_loop();
void win_main_dest();

//�E�B���h�E��ʂ̃��C��
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR IpCmdLine,
	int nShowCmd)
{
	win_main_init();

	while (true){
		SetDrawScreen(DX_SCREEN_BACK);

		win_main_loop();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) exit(-1);
		//�E�B���h�E������ꂽ�������̓G���[�̏ꍇ�Q�[��������//
		if (ProcessMessage() == -1) exit(-1);

#if defined( _DEBUG ) | defined( DEBUG )
#endif
	}
	win_main_dest();
}

//���C���̏���������

void win_main_init()
{
	//DirectX�֌W

	ChangeWindowMode(WINDOW_SCREEN);
		SetGraphMode(1280, 720, 32);
		SetMainWindowText(_T("�e�X�g�v���O����"));
	if (WINDOW_SCREEN)
	{
	}
	if (DxLib_Init() == -1)		//���C�u�����̏���������
		return;

	//GAME�֌W
	g_pMain = new CGame();
	g_pMain->Init();
}

//���C�����[�v����
void win_main_loop()
{
	//���C������
	g_pMain->Update();
	g_pMain->Draw();
	ScreenFlip();
}

//���C���I������
void win_main_dest()
{
	g_pMain->Dest();
	delete g_pMain;
	g_pMain = NULL;
}