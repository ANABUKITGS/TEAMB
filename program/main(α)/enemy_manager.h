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

	//初期化
	void Init(CEnemy* enemy);

	//終了処理
	void Finish();

	//データの取得
	CEnemy* GetEnemyAdress() const;

	void Update();
};

#endif ENEMY_MANAGER_H