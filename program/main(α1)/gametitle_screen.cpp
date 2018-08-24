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
	title_img[0] = LoadGraph("media\\img\\title.png");
	title_img[1] = LoadGraph("media\\img\\titlelogo.png");
	title_text_img = LoadGraph("media\\img\\screentext.png");
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM), DX_PLAYTYPE_LOOP);	//New
}

//実行処理
void CGameTitleScreen::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2))m_state = GAME_SCREEN;

//	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = GAME_SCREEN;
}

//描画
void CGameTitleScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, title_img[0], TRUE);
	DrawGraph(620, 374, title_img[1], TRUE);
	DrawGraph(0, 640, title_text_img, TRUE);

#if defined(_DEBUG) | defined(DEBUG)
	//DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor(255, 255, 255));
#endif
}

//次のステージへ
SCREEN CGameTitleScreen::GetNextScreen()
{
	return(m_state);
}