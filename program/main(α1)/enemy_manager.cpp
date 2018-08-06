#include "enemy_manager.h"

CEnemyManager* CEnemyManager::mp_Instance = nullptr;

CEnemyManager* CEnemyManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CEnemyManager();
	}
	return mp_Instance;
}

void CEnemyManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// コンストラクタ
CEnemyManager::CEnemyManager(){
}

// デストラクタ
CEnemyManager::~CEnemyManager(){
}

//マネージャーにstatusdataをセット
void CEnemyManager::Init(CEnemy* enemy){
	m_enemy = enemy;
}

CEnemy* CEnemyManager::GetEnemyAdress() const
{
	return m_enemy;
}

void CEnemyManager::Finish(){
}

void CEnemyManager::Update(){
}