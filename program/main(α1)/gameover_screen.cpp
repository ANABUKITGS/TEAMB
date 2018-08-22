//�w�b�_�[�t�@�C��
#include "gameover_screen.h"

//�R���X�g���N�^
CGameOverScreen::CGameOverScreen()
{
	m_state = GAMEOVER_SCREEN;
}

//�f�X�g���N�^
CGameOverScreen::~CGameOverScreen(){}

//���[�h
void CGameOverScreen::Load(){}

//�����[�X
void CGameOverScreen::Release(){}

//������
void CGameOverScreen::Init(){
	gameover_img = LoadGraph("media\\img\\gameover.png");
}

//���s����
void CGameOverScreen::Update()
{

	if (CheckHitKey(KEY_INPUT_A) == 1) m_state = TITLE_SCREEN;
}

//�`��
void CGameOverScreen::Draw()
{
	ClearDrawScreen();
	DrawGraph(0, 0, gameover_img, TRUE);
	DrawString(10, 100, "TITLE Screen Hit A key to Next Screen", GetColor
		(255, 255, 255));
}

//���̃X�e�[�W��
SCREEN CGameOverScreen::GetNextScreen()
{
	return(m_state);
}