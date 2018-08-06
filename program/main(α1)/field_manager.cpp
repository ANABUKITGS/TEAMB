#include "field_manager.h"

CFieldManager* CFieldManager::mp_Instance = nullptr;

CFieldManager* CFieldManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CFieldManager();
	}
	return mp_Instance;
}

void CFieldManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// �R���X�g���N�^
CFieldManager::CFieldManager(){
}

// �f�X�g���N�^
CFieldManager::~CFieldManager(){
}

//�}�l�[�W���[��statusdata���Z�b�g
void CFieldManager::Init(CField* field){
	m_field = field;
}

CField* CFieldManager::GetFrameAdress() const
{
	return m_field;
}

void CFieldManager::Finish(){
}

void CFieldManager::Update(){
}