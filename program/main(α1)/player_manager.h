#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "player.h"

class CPlayerManager{
private:
	static CPlayerManager* mp_Instance;
	CPlayer *m_player;
	CPlayerManager();
public:
	~CPlayerManager();

	static CPlayerManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CPlayer* player);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CPlayer* GetPlayerAdress() const;

	void Update();
};

#endif PLAYER_MANAGER_H