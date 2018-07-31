#include "myLib.h"
#include "game.h"

//ローカル変数
CGame*		g_pMain = NULL;
const bool	WINDOW_SCREEN = true;

//ローカル関数
void win_main_init();
void win_main_loop();
void win_main_dest();

//ウィンドウ画面のメイン
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR IpCmdLine,
	int nShowCmd)
{
	win_main_init();

	while (true){
		SetDrawScreen(DX_SCREEN_BACK);

		win_main_loop();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) exit(-1);
		//ウィンドウが閉じられたもしくはエラーの場合ゲームを消す//
		if (ProcessMessage() == -1) exit(-1);

#if defined( _DEBUG ) | defined( DEBUG )
#endif
	}
	win_main_dest();
}

//メインの初期化処理

void win_main_init()
{
	//DirectX関係

	ChangeWindowMode(WINDOW_SCREEN);
		SetGraphMode(1280, 720, 32);
		SetMainWindowText(_T("テストプログラム"));
	if (WINDOW_SCREEN)
	{
	}
	if (DxLib_Init() == -1)		//ライブラリの初期化処理
		return;

	//GAME関係
	g_pMain = new CGame();
	g_pMain->Init();
}

//メインループ処理
void win_main_loop()
{
	//メイン処理
	g_pMain->Update();
	g_pMain->Draw();
	ScreenFlip();
}

//メイン終了処理
void win_main_dest()
{
	g_pMain->Dest();
	delete g_pMain;
	g_pMain = NULL;
}