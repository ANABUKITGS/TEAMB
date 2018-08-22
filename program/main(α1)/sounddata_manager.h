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

	//������
	void Init(CSoundData* sound);

	//�I������
	void Finish();

	//�f�[�^�̏���
	CSoundData* GetStatusAdress() const;

	void Update();
};

#endif SOUNDDATA_MANAGER_H