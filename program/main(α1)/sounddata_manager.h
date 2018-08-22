#ifndef SOUNDDATA_MANAGER_H
#define SOUNDDATA_MANAGER_H

#include "sounddata.h"

class CSoundManager{
private:
	static CSoundManager* mp_Instance;
	CSoundData *m_sound;
	CSoundManager();
public:
	~CSoundManager();

	static CSoundManager* GetInstance();
	static void ClearInstance();

	//初期化
	void Init(CSoundData* sound);

	//終了処理
	void Finish();

	//データの所得
	CSoundData* GetStatusAdress() const;

	void Update();
};

#endif SOUNDDATA_MANAGER_H