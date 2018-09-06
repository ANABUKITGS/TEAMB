//ヘッダーファイル
#include "gametitle_screen.h"
#include "sounddata_manager.h"
#include "change_manager.h"

//コンストラクタ
CGameTitleScreen::CGameTitleScreen()
{
	m_state = TITLE_SCREEN;
}

//デストラクタ
CGameTitleScreen::~CGameTitleScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM));	//New
	CChangeManager::GetInstance()->GetChangeAdress()->Kill();
}

//ロード
void CGameTitleScreen::Load(){}

//リリース
void CGameTitleScreen::Release(){}

//初期化
void CGameTitleScreen::Init(){

	title1_img[0] = LoadGraph("media\\img\\title\\title_back.png");
	title1_img[1] = LoadGraph("media\\img\\title\\title_boss_ver2.png");
	title1_img[2] = LoadGraph("media\\img\\title\\title_player_ver2.png");
	title1_img[3] = LoadGraph("media\\img\\title\\titlelogo.png");

	LoadDivGraph("media\\img\\title\\title_start.png", 2, 1, 2, 512, 64, title2_text_img[0], 0);
	LoadDivGraph("media\\img\\title\\title_credit.png", 2, 1, 2, 512, 64, title2_text_img[1], 0);

	m_title[0].m_pos = CVector2D(0, 0);
	m_title[1].m_pos = CVector2D(0, -150);
	m_title[2].m_pos = CVector2D(-50, 0);
	m_title[3].m_pos = CVector2D(620, 374);

	m_title_text[0].m_pos = CVector2D(173, 600);
	m_title_text[0].m_type = 1;
	m_title_text[1].m_pos = CVector2D(128, 660);
	m_title_text[1].m_type = 0;

	for (int i = 0; i < 4; i++){
		m_title[i].m_alpha = 0;
		if (i == 1)
			m_title[1].m_add_move = -250.0f;//y
		else if (i == 2)
			m_title[2].m_add_move = -200.0f;//x
		else
			m_title[i].m_add_move = 0;
	}

	title_text_img = LoadGraph("media\\img\\screentext.png");
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM), DX_PLAYTYPE_LOOP);	//New
	
	m_timer = 0;
	m_title_num = 0;
	m_control_flag = false;

	new CChange(0, 2);

}

//実行処理
void CGameTitleScreen::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//スキップ処理
	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2)){
		if (m_title[3].m_alpha < 256){
			for (int i = 0; i < 4; i++){
				m_title[i].m_alpha = 256;
			}
			m_title_num = 3;
		}
		else{
			if (!m_control_flag){
				CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
				m_control_flag = true;
			}
		}
	}

	if (m_timer < 80){
		m_timer++;
	}
	else{
		m_timer = 0;
		if (m_title_num < 3)
			m_title_num++;
	}
	for (int i = 0; i <= m_title_num; i++){
		if (i >= 0){
			if (m_title[i].m_alpha < 256)
				m_title[i].m_alpha += 6;
		}
		if (i == 1)
		if (m_title[i].m_pos.getY() > m_title[i].m_add_move)
			m_title[i].m_pos.addY(-3);

		if (i == 2)
		if (m_title[i].m_pos.getX() > m_title[i].m_add_move)
			m_title[i].m_pos.addX(-3);
	}

	//テキストの選択処理
	if (!m_control_flag){
		if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_UP, KEY_UP)){
			m_title_text[0].m_type = 1;
			m_title_text[1].m_type = 0;
		}
		if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_DOWN, KEY_DOWN)){
			m_title_text[1].m_type = 1;
			m_title_text[0].m_type = 0;
		}
	}


	if (m_title[3].m_alpha > 255){
		m_title[3].m_add_move -= 0.04f;
		if (m_title[3].m_add_move < -6.3f)
			m_title[3].m_add_move = 0;
	}
	if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut()){
		if (m_title_text[0].m_type == 1)
			m_state = GAME_SCREEN;
		else if (m_title_text[1].m_type == 1)
			m_state = CREDIT_SCREEN;
	}
	CChangeManager::GetInstance()->GetChangeAdress()->Update();
}

//描画
void CGameTitleScreen::Draw()
{
	ClearDrawScreen();

	for (int i = 0; i <= m_title_num; i++){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_title[i].m_alpha);
		DrawGraph(m_title[i].m_pos.getX(), m_title[i].m_pos.getY() + 15 * sin(m_title[i].m_add_move), title1_img[i], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (m_title[3].m_alpha > 255){
		DrawRotaGraph(m_title_text[0].m_pos.getX(), m_title_text[0].m_pos.getY(), 1, 0, title2_text_img[0][m_title_text[0].m_type], TRUE, FALSE);
		DrawRotaGraph(m_title_text[1].m_pos.getX(), m_title_text[1].m_pos.getY(), 1, 0, title2_text_img[1][m_title_text[1].m_type], TRUE, FALSE);
	}	
	//DrawGraph(0, 640, title_text_img, TRUE);

	CChangeManager::GetInstance()->GetChangeAdress()->Draw();

#if defined(_DEBUG) | defined(DEBUG)
	//DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor(255, 255, 255));
#endif
}

//次のステージへ
SCREEN CGameTitleScreen::GetNextScreen()
{
	return(m_state);
}