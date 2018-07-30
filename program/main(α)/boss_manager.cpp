#include "boss_manager.h"

CBossManager* CBossManager::mp_Instance = nullptr;

CBossManager* CBossManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CBossManager();
	}
	return mp_Instance;
}

void CBossManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// �R���X�g���N�^
CBossManager::CBossManager(){
}

// �f�X�g���N�^
CBossManager::~CBossManager(){
}

//�}�l�[�W���[��statusdata���Z�b�g
void CBossManager::Init(CBoss* boss){
	m_boss = boss;
}

CBoss* CBossManager::GetBossAdress() const
{
	return m_boss;
}

void CBossManager::Finish(){
}

void CBossManager::Update(){
}