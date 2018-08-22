#include "sounddata_manager.h"

CSoundManager* CSoundManager::mp_Instance = nullptr;

CSoundManager* CSoundManager::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CSoundManager();
	}
	return mp_Instance;
}

void CSoundManager::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}

// コンストラクタ
CSoundManager::CSoundManager(){
}

// デストラクタ
CSoundManager::~CSoundManager(){
	delete m_sound;
}

//マネージャーにstatusdataをセット
void CSoundManager::Init(CSoundData* sound){
	m_sound = sound;
}

CSoundData* CSoundManager::GetStatusAdress() const
{
	return m_sound;
}

void CSoundManager::Finish(){
}

void CSoundManager::Update(){
}