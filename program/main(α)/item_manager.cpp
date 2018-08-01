#include "item_manager.h"

CItemManager* CItemManager::mp_Instance = nullptr;

CItemManager* CItemManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CItemManager();
	}
	return mp_Instance;
}

void CItemManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// コンストラクタ
CItemManager::CItemManager(){
}

// デストラクタ
CItemManager::~CItemManager(){
}

//マネージャーにstatusdataをセット
void CItemManager::Init(CItem* item){
	m_item = item;
}

CItem* CItemManager::GetItemAdress() const
{
	return m_item;
}

void CItemManager::Finish(){
}

void CItemManager::Update(){
}