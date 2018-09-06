//ヘッダーファイル
#include "gameclear_screen.h"
#include "sounddata_manager.h"

//コンストラクタ
CGameClearScreen::CGameClearScreen()
{
	m_state = GAMECLEAR_SCREEN;
}

//デストラクタ
CGameClearScreen::~CGameClearScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMECLEAR_BGM));	//New
}

//ロード
void CGameClearScreen::Load(){}

//リリース
void CGameClearScreen::Release(){}

//初期化
void CGameClearScreen::Init(){
	m_ac = 0;
	m_animcounter = 0;

	gameclear_chara_img[0] = LoadGraph("media\\img\\clearchara1.png");
	gameclear_chara_img[1] = LoadGraph("media\\img\\clearchara2.png");
	gameclear_chara_img[2] = LoadGraph("media\\img\\clearchara3.png");
	gameclear_chara_img[3] = LoadGraph("media\\img\\clearchara4.png");
	gameclear_chara_img[4] = LoadGraph("media\\img\\clearchara5.png");

	gameclear_text_img = LoadGraph("media\\img\\screentext.png");

	LoadDivGraph("media\\img\\enemy_n_m.png", 88, 4, 22, 64, 64, m_enemy_img[0]);
	LoadDivGraph("media\\img\\enemy_l_m.png", 88, 4, 22, 48, 48, m_enemy_img[1]);
	LoadDivGraph("media\\img\\enemy_s_m.png", 88, 4, 22, 64, 64, m_enemy_img[2]);
	LoadDivGraph("media\\img\\enemy_b_m.png", 88, 4, 22, 128, 128, m_enemy_img[3]);
	LoadDivGraph("media\\img\\enemy_bom_m.png", 88, 4, 22, 64, 64, m_enemy_img[4]);

	m_clear[0].m_pos = CVector2D(-400, 590);
	m_clear[1].m_pos = CVector2D(-230, 615);
	m_clear[2].m_pos = CVector2D(-50, 595);
	m_clear[3].m_pos = CVector2D(1290, 530);
	m_clear[4].m_pos = CVector2D(1530, 592);

	gameclear_t_img = LoadGraph("media\\img\\gameclear.png");

	m_timer = 0;
	m_title_num = 2;

	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMECLEAR_BGM), DX_PLAYTYPE_BACK);	//New
}

//実行処理
void CGameClearScreen::Update()
{
	m_animcounter++;
	m_animcounter %= MAXINT;
	m_ac = m_animcounter / 14;
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//雑魚キャラの移動
	for (int i = 0; i < 5; i++){
		if (i >= 0)
			switch (i){
			case 0:
				if (m_clear[i].m_pos.getX() < 60){
					m_clear[i].m_animtype = 8;
					m_clear[i].m_pos += CVector2D(ENEMY, 0);
				}
				else
					m_clear[i].m_animtype = 0;
				break;
			case 1:
				if (m_clear[i].m_pos.getX() < 230){
					m_clear[i].m_animtype = 8;
					m_clear[i].m_pos += CVector2D(ENEMY, 0);
				}
				else
					m_clear[i].m_animtype = 0;
				break;
			case 2:
				if (m_clear[i].m_pos.getX() < 410){
					m_clear[i].m_animtype = 8;
					m_clear[i].m_pos += CVector2D(ENEMY, 0);
				}
				else
					m_clear[i].m_animtype = 0;
				break;
			case 3:
				if (m_clear[i].m_pos.getX() > 830){
					m_clear[i].m_animtype = 4;
					m_clear[i].m_pos -= CVector2D(ENEMY, 0);
				}
				else
					m_clear[i].m_animtype = 0;
				break;
			case 4:
				if (m_clear[i].m_pos.getX() > 1070){
					m_clear[i].m_animtype = 4;
					m_clear[i].m_pos -= CVector2D(ENEMY, 0);
				}
				else
					m_clear[i].m_animtype = 0;
				break;
			default:
				break;
		}

		if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2))m_state = TITLE_SCREEN;

		//	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = TITLE_SCREEN;
	}

}
//描画
void CGameClearScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, gameclear_t_img, TRUE);
	DrawRotaGraph(620, 600, 0.3f, 0, gameclear_chara_img[(int)m_ac % 5], TRUE, FALSE);

	for (int i = 0; i < 5; i++){
		DrawGraph(m_clear[i].m_pos.getX(), m_clear[i].m_pos.getY(), m_enemy_img[i][m_clear[i].m_animtype + (int)m_ac % 2], TRUE);
	}
#if defined(_DEBUG) | defined(DEBUG)
	//DrawString(10, 100, "GAMECLEAR Screen Hit A key to Next Screen", GetColor(255, 255, 255));
#endif
}

//次のステージへ
SCREEN CGameClearScreen::GetNextScreen()
{
	return(m_state);
}