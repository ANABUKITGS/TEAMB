#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "enemy.h"

class CEnemyManager{
private:
	static CEnemyManager* mp_Instance;
	CEnemy *m_enemy;
	CEnemyManager();
public:
	~CEnemyManager();

	static CEnemyManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CEnemy* enemy);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CEnemy* GetEnemyAdress() const;

	void Update();
};

#endif ENEMY_MANAGER_H