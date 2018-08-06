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

	//初期化
	void Init(CBoss* boss);

	//終了処理
	void Finish();

	//データの取得
	CBoss* GetBossAdress() const;

	void Update();
};

#endif BOSS_MANAGER_H