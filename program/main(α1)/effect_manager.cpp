#include "effect_manager.h"

CEffectManager* CEffectManager::mp_Instance = nullptr;

CEffectManager* CEffectManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CEffectManager();
	}
	return mp_Instance;
}

void CEffectManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// �R���X�g���N�^
CEffectManager::CEffectManager(){
}

// �f�X�g���N�^
CEffectManager::~CEffectManager(){
}

//�}�l�[�W���[��statusdata���Z�b�g
void CEffectManager::Init(CEffect* effect){
	m_effect = effect;
}

CEffect* CEffectManager::GetEffectAdress() const
{
	return m_effect;
}

void CEffectManager::Finish(){
}

void CEffectManager::Update(){
}