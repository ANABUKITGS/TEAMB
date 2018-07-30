#include "ui_manager.h"

CUiManager* CUiManager::mp_Instance = nullptr;

CUiManager* CUiManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CUiManager();
	}
	return mp_Instance;
}

void CUiManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// コンストラクタ
CUiManager::CUiManager(){
}

// デストラクタ
CUiManager::~CUiManager(){
}

//マネージャーにstatusdataをセット
void CUiManager::Init(CUi* ui){
	m_ui = ui;
}

CUi* CUiManager::GetUiAdress() const
{
	return m_ui;
}

void CUiManager::Finish(){
}

void CUiManager::Update(){
}