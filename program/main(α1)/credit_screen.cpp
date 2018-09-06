//ヘッダーファイル
#include "credit_screen.h"
#include "sounddata_manager.h"
#include "change_manager.h"

//コンストラクタ
CCreditScreen::CCreditScreen()
{
	m_state = CREDIT_SCREEN;
}

//デストラクタ
CCreditScreen::~CCreditScreen(){
	//StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMEOVER_BGM));	//New
}

//ロード
void CCreditScreen::Load(){}

//リリース
void CCreditScreen::Release(){}

//初期化
void CCreditScreen::Init(){
	credit_img = LoadGraph("media\\img\\tutorial\\credit.jpg");
	credit_text_img = LoadGraph("media\\img\\screentext.png");
	new CChange(255, -2);
	CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
}

//実行処理
void CCreditScreen::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2)){
		CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
	}
	if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut()){
		m_state = TITLE_SCREEN;
	}

	CChangeManager::GetInstance()->GetChangeAdress()->Update();
}

//描画
void CCreditScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, credit_img, TRUE);
	DrawGraph(0, 640, credit_text_img, TRUE);

	CChangeManager::GetInstance()->GetChangeAdress()->Draw();
#if defined(_DEBUG) | defined(DEBUG)
	//DrawString(10, 100, "GAMEOVER Screen Hit A key to Next Screen", GetColor(255, 255, 255));
#endif
}

//次のステージへ
SCREEN CCreditScreen::GetNextScreen()
{
	return(m_state);
}