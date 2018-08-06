#include "player_manager.h"

CPlayerManager* CPlayerManager::mp_Instance = nullptr;

CPlayerManager* CPlayerManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CPlayerManager();
	}
	return mp_Instance;
}

void CPlayerManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// �R���X�g���N�^
CPlayerManager::CPlayerManager(){
}

// �f�X�g���N�^
CPlayerManager::~CPlayerManager(){
}

//�}�l�[�W���[��statusdata���Z�b�g
void CPlayerManager::Init(CPlayer* player){
	m_player = player;
}

CPlayer* CPlayerManager::GetPlayerAdress() const
{
	return m_player;
}

void CPlayerManager::Finish(){
}

void CPlayerManager::Update(){
}