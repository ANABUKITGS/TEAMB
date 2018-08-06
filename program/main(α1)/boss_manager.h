#ifndef BOSS_MANAGER_H
#define BOSS_MANAGER_H

#include "boss.h"

class CBossManager{
private:
	static CBossManager* mp_Instance;
	CBoss *m_boss;
	CBossManager();
public:
	~CBossManager();

	static CBossManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CBoss* boss);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CBoss* GetBossAdress() const;

	void Update();
};

#endif BOSS_MANAGER_H