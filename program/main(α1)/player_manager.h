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

	//初期化
	void Init(CPlayer* player);

	//終了処理
	void Finish();

	//データの取得
	CPlayer* GetPlayerAdress() const;

	void Update();
};

#endif PLAYER_MANAGER_H