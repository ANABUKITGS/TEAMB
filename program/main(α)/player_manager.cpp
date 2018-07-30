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

// コンストラクタ
CPlayerManager::CPlayerManager(){
}

// デストラクタ
CPlayerManager::~CPlayerManager(){
}

//マネージャーにstatusdataをセット
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