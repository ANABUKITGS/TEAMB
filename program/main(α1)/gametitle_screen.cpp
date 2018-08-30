//�w�b�_�[�t�@�C��
#include "gametitle_screen.h"
#include "sounddata_manager.h"
#include "change_manager.h"

//�R���X�g���N�^
CGameTitleScreen::CGameTitleScreen()
{
	m_state = TITLE_SCREEN;
}

//�f�X�g���N�^
CGameTitleScreen::~CGameTitleScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM));	//New
	CChangeManager::GetInstance()->GetChangeAdress()->Kill();
}

//���[�h
void CGameTitleScreen::Load(){}

//�����[�X
void CGameTitleScreen::Release(){}

//������
void CGameTitleScreen::Init(){
	title_img[0] = LoadGraph("media\\img\\title.png");
	title_img[1] = LoadGraph("media\\img\\titlelogo.png");

	title1_img[0] = LoadGraph("media\\img\\title_back.png");
	title1_img[2] = LoadGraph("media\\img\\title_player.png");
	title1_img[1] = LoadGraph("media\\img\\title_boss.png");
	title1_img[3] = LoadGraph("media\\img\\titlelogo.png");

	m_title[0].m_pos = CVector2D(0, 0);
	m_title[1].m_pos = CVector2D(0, 0);
	m_title[2].m_pos = CVector2D(0, 0);
	m_title[3].m_pos = CVector2D(620, 374);

	for (int i = 0; i < 4; i++){
		m_title[i].m_alpha = 0;
		m_title[i].m_add_move = 0;
	}

	title_text_img = LoadGraph("media\\img\\screentext.png");
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM), DX_PLAYTYPE_LOOP);	//New
	
	m_timer = 0;
	m_title_num = 0;

	new CChange(0, 2);

}

//���s����
void CGameTitleScreen::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2)){
		if (m_title[3].m_alpha < 256){
			for (int i = 0; i < 4; i++){
				m_title[i].m_alpha = 256;
			}
			m_title_num = 3;
		}
		else{
			CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
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
		if (i >= 0)
		if (m_title[i].m_alpha < 256)
			m_title[i].m_alpha += 6;
	}

	if (m_title[3].m_alpha > 255){
		m_title[3].m_add_move -= 0.04f;
		if (m_title[3].m_add_move < -6.3f)
			m_title[3].m_add_move = 0;
	}
	if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut())m_state = GAME_SCREEN;
	CChangeManager::GetInstance()->GetChangeAdress()->Update();

//	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = GAME_SCREEN;
}

//�`��
void CGameTitleScreen::Draw()
{
	ClearDrawScreen();

	for (int i = 0; i <= m_title_num; i++){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_title[i].m_alpha);
		DrawGraph(m_title[i].m_pos.getX(), m_title[i].m_pos.getY() + 15 * sin(m_title[i].m_add_move), title1_img[i], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (m_title[3].m_alpha > 255)
		DrawGraph(0, 640, title_text_img, TRUE);

	CChangeManager::GetInstance()->GetChangeAdress()->Draw();

#if defined(_DEBUG) | defined(DEBUG)
	//DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor(255, 255, 255));
#endif
}

//���̃X�e�[�W��
SCREEN CGameTitleScreen::GetNextScreen()
{
	return(m_state);
}