//ヘッダーファイル
#include "gametitle_screen.h"
#include "sounddata_manager.h"

//コンストラクタ
CGameTitleScreen::CGameTitleScreen()
{
	m_state = TITLE_SCREEN;
}

//デストラクタ
CGameTitleScreen::~CGameTitleScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM));	//New
}

//ロード
void CGameTitleScreen::Load(){}

//リリース
void CGameTitleScreen::Release(){}

//初期化
void CGameTitleScreen::Init(){
	title_img = LoadGraph("media\\img\\title.png");
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM), DX_PLAYTYPE_LOOP);	//New
}

//実行処理
void CGameTitleScreen::Update()
{
	
	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = GAME_SCREEN;
}

//描画
void CGameTitleScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, title_img, TRUE);
	DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor
		(255, 255, 255));
}

//次のステージへ
SCREEN CGameTitleScreen::GetNextScreen()
{
	return(m_state);
}