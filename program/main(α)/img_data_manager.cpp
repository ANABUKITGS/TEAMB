#include "img_data_manager.h"

CImgDataManager* CImgDataManager::mp_Instance = nullptr;

CImgDataManager* CImgDataManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CImgDataManager();
	}
	return mp_Instance;
}

void CImgDataManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// �R���X�g���N�^
CImgDataManager::CImgDataManager(){
}

// �f�X�g���N�^
CImgDataManager::~CImgDataManager(){
}

//�}�l�[�W���[��statusdata���Z�b�g
void CImgDataManager::Init(CImg* img_data){
	m_img_data = img_data;
}

CImg* CImgDataManager::GetImgDataAdress() const
{
	return m_img_data;
}

void CImgDataManager::Finish(){
}

void CImgDataManager::Update(){
}