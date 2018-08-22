//ヘッダーファイル
#include "gameclear_screen.h"

//コンストラクタ
CGameClearScreen::CGameClearScreen()
{
	m_state = GAMECLEAR_SCREEN;
}

//デストラクタ
CGameClearScreen::~CGameClearScreen(){}

//ロード
void CGameClearScreen::Load(){}

//リリース
void CGameClearScreen::Release(){}

//初期化
void CGameClearScreen::Init(){
	m_ac = 0;
	m_animcounter = 0;
	gameclear_img[0] = LoadGraph("media\\img\\gameclear\\clear00.png");
	gameclear_img[1] = LoadGraph("media\\img\\gameclear\\clear01.png");
	gameclear_img[2] = LoadGraph("media\\img\\gameclear\\clear02.png");
	gameclear_img[3] = LoadGraph("media\\img\\gameclear\\clear03.png");
	gameclear_img[4] = LoadGraph("media\\img\\gameclear\\clear04.png");
	gameclear_img[5] = LoadGraph("media\\img\\gameclear\\clear05.png");
	gameclear_img[6] = LoadGraph("media\\img\\gameclear\\clear06.png");
	gameclear_img[7] = LoadGraph("media\\img\\gameclear\\clear07.png");
	gameclear_img[8] = LoadGraph("media\\img\\gameclear\\clear08.png");
	gameclear_img[9] = LoadGraph("media\\img\\gameclear\\clear09.png");
	gameclear_img[10] = LoadGraph("media\\img\\gameclear\\clear10.png");
	gameclear_img[11] = LoadGraph("media\\img\\gameclear\\clear11.png");
	gameclear_img[12] = LoadGraph("media\\img\\gameclear\\clear12.png");
	gameclear_img[13] = LoadGraph("media\\img\\gameclear\\clear13.png");
	gameclear_img[14] = LoadGraph("media\\img\\gameclear\\clear14.png");
	gameclear_img[15] = LoadGraph("media\\img\\gameclear\\clear15.png");
	gameclear_img[16] = LoadGraph("media\\img\\gameclear\\clear16.png");
	gameclear_img[17] = LoadGraph("media\\img\\gameclear\\clear17.png");
	gameclear_img[18] = LoadGraph("media\\img\\gameclear\\clear18.png");
	gameclear_img[19] = LoadGraph("media\\img\\gameclear\\clear19.png");
	gameclear_img[20] = LoadGraph("media\\img\\gameclear\\clear20.png");
	gameclear_img[21] = LoadGraph("media\\img\\gameclear\\clear21.png");
	gameclear_img[22] = LoadGraph("media\\img\\gameclear\\clear22.png");
	gameclear_img[23] = LoadGraph("media\\img\\gameclear\\clear23.png");
	gameclear_img[24] = LoadGraph("media\\img\\gameclear\\clear24.png");
	gameclear_img[25] = LoadGraph("media\\img\\gameclear\\clear25.png");
	gameclear_img[26] = LoadGraph("media\\img\\gameclear\\clear26.png");
}

//実行処理
void CGameClearScreen::Update()
{
	m_animcounter++;
	m_animcounter %= MAXINT;
	m_ac = m_animcounter / 8;
	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = TITLE_SCREEN;
}

//描画
void CGameClearScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, gameclear_img[(int)m_ac % 26], TRUE);
	DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor
		(255, 255, 255));
}

//次のステージへ
SCREEN CGameClearScreen::GetNextScreen()
{
	return(m_state);
}