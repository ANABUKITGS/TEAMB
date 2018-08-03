#include "change_manager.h"

CChangeManager* CChangeManager::mp_Instance = nullptr;

CChangeManager* CChangeManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CChangeManager();
	}
	return mp_Instance;
}

void CChangeManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// �R���X�g���N�^
CChangeManager::CChangeManager(){
}

// �f�X�g���N�^
CChangeManager::~CChangeManager(){
}

//�}�l�[�W���[��statusdata���Z�b�g
void CChangeManager::Init(CChange* change){
	m_change = change;
}

CChange* CChangeManager::GetChangeAdress() const
{
	return m_change;
}

void CChangeManager::Finish(){
}

void CChangeManager::Update(){
}