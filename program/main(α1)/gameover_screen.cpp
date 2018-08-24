//ヘッダーファイル
#include "gameover_screen.h"
#include "sounddata_manager.h"

//コンストラクタ
CGameOverScreen::CGameOverScreen()
{
	m_state = GAMEOVER_SCREEN;
}

//デストラクタ
CGameOverScreen::~CGameOverScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMEOVER_BGM));	//New
}

//ロード
void CGameOverScreen::Load(){}

//リリース
void CGameOverScreen::Release(){}

//初期化
void CGameOverScreen::Init(){
	gameover_img = LoadGraph("media\\img\\gameover.png");
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMEOVER_BGM), DX_PLAYTYPE_BACK);	//New
}

//実行処理
void CGameOverScreen::Update()
{

	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = TITLE_SCREEN;
}

//描画
void CGameOverScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, gameover_img, TRUE);
	DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor
		(255, 255, 255));
}

//次のステージへ
SCREEN CGameOverScreen::GetNextScreen()
{
	return(m_state);
}