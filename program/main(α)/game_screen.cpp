
//�w�b�_�[�t�@�C��
#include "game_screen.h"
#include "task_manager.h"

#include "field_manager.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"
//#include "boss_manager.h"

//�R���X�g���N�^
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
	CTaskManager::GetInstance()->KillAll();
}

//�f�X�g���N�^
CGameScreen::~CGameScreen(){
	
}

//���[�h
void CGameScreen::Load(){
}

//�����[�X
void CGameScreen::Release(){}

//������
void CGameScreen::Init(){
	//�����Ń^�X�N����
	//CTaskManager::GetInstance()->Add( new CFrame);
	CTaskManager::GetInstance()->Add(new CPlayer);
	CTaskManager::GetInstance()->Add(new CField);
	CTaskManager::GetInstance()->Add(new CEnemy);
	//CTaskManager::GetInstance()->Add(new CBoss);
	CTaskManager::GetInstance()->Add(new CEffect);
	CTaskManager::GetInstance()->Add(new CUi);
}

//���s����
void CGameScreen::Update()
{
	if (CheckHitKey(KEY_INPUT_E) == 1) m_state = TITLE_SCREEN;
	CTaskManager::GetInstance()->UpdateAll();

	CCharaData::GetInstance()->CBank();
	CCharaData::GetInstance()->Delete();

#if defined(_DEBUG) | defined(DEBUG)
	CCharaData::GetInstance()->Counter();
#endif
}

//�`��
void CGameScreen::Draw()
{
	ClearDrawScreen();
	DrawString(10, 100, "Game Screen\n Hit E key to Title Screen", GetColor
		(255, 255, 255));
	CTaskManager::GetInstance()->DrawAll();
	CCharaData::GetInstance()->Draw();
}

//���̃X�e�[�W��
SCREEN CGameScreen::GetNextScreen()
{
	return(m_state);
}