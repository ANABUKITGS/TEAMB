#ifndef CHANGE_MANAGER_H
#define CHANGE_MANAGER_H

#include "change.h"

class CChangeManager{
private:
	static CChangeManager* mp_Instance;
	CChange *m_change;
	CChangeManager();
public:
	~CChangeManager();

	static CChangeManager* GetInstance();
	static void ClearInstance();

	//初期化
	void Init(CChange* change);

	//終了処理
	void Finish();

	//データの取得
	CChange* GetChangeAdress() const;

	void Update();
};

#endif CHANGE_MANAGER_H