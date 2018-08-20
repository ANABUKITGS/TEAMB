#include "difficulty_level_manager.h"

CDifficultyLevelManager* CDifficultyLevelManager::mp_Instance = nullptr;

CDifficultyLevelManager* CDifficultyLevelManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CDifficultyLevelManager();
	}
	return mp_Instance;
}

void CDifficultyLevelManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// コンストラクタ
CDifficultyLevelManager::CDifficultyLevelManager(){
}

// デストラクタ
CDifficultyLevelManager::~CDifficultyLevelManager(){
}

//マネージャーにstatusdataをセット
void CDifficultyLevelManager::Init(CDifficultyLevel* difficulty_level){
	m_difficulty_level = difficulty_level;
}

CDifficultyLevel* CDifficultyLevelManager::GetDifficultyLevelAdress() const
{
	return m_difficulty_level;
}

void CDifficultyLevelManager::Finish(){
}

void CDifficultyLevelManager::Update(){
}