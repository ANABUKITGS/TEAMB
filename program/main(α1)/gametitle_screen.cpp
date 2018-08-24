//�w�b�_�[�t�@�C��
#include "gametitle_screen.h"
#include "sounddata_manager.h"

//�R���X�g���N�^
CGameTitleScreen::CGameTitleScreen()
{
	m_state = TITLE_SCREEN;
}

//�f�X�g���N�^
CGameTitleScreen::~CGameTitleScreen(){
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM));	//New
}

//���[�h
void CGameTitleScreen::Load(){}

//�����[�X
void CGameTitleScreen::Release(){}

//������
void CGameTitleScreen::Init(){
	title_img = LoadGraph("media\\img\\title.png");
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(TITLE_BGM), DX_PLAYTYPE_LOOP);	//New
}

//���s����
void CGameTitleScreen::Update()
{
	
	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = GAME_SCREEN;
}

//�`��
void CGameTitleScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, title_img, TRUE);
	DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor
		(255, 255, 255));
}

//���̃X�e�[�W��
SCREEN CGameTitleScreen::GetNextScreen()
{
	return(m_state);
}