//�w�b�_�[�t�@�C��
#include "gameover_screen.h"
#include "sounddata_manager.h"

//�R���X�g���N�^
CGameOverScreen::CGameOverScreen()
{
	m_state = GAMEOVER_SCREEN;
}

//�f�X�g���N�^
CGameOverScreen::~CGameOverScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMEOVER_BGM));	//New
}

//���[�h
void CGameOverScreen::Load(){}

//�����[�X
void CGameOverScreen::Release(){}

//������
void CGameOverScreen::Init(){
	m_gameover_img = LoadGraph("media\\img\\gameover.png");
	m_gameover_text_img = LoadGraph("media\\img\\screentext.png");
	m_timer = 0;
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAMEOVER_BGM), DX_PLAYTYPE_BACK);	//New
}

//���s����
void CGameOverScreen::Update()
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (m_timer < 450){
		m_timer++;
	}
	else{
		m_state = TITLE_SCREEN;
	}

	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2))m_state = TITLE_SCREEN;

//	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = TITLE_SCREEN;
}

//�`��
void CGameOverScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, m_gameover_img, TRUE);
	DrawGraph(0, 640, m_gameover_text_img, TRUE);


#if defined(_DEBUG) | defined(DEBUG)
	//DrawString(10, 100, "GAMEOVER Screen Hit A key to Next Screen", GetColor(255, 255, 255));
#endif
}

//���̃X�e�[�W��
SCREEN CGameOverScreen::GetNextScreen()
{
	return(m_state);
}