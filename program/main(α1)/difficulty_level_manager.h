#ifndef DIFFICULTY_LEVEL_MANAGER_H
#define DIFFICULTY_LEVEL_MANAGER_H

#include "difficulty_level.h"

class CDifficultyLevelManager{
private:
	static CDifficultyLevelManager* mp_Instance;
	CDifficultyLevel *m_difficulty_level;
	CDifficultyLevelManager();
public:
	~CDifficultyLevelManager();

	static CDifficultyLevelManager* GetInstance();
	static void ClearInstance();

	//初期化
	void Init(CDifficultyLevel* difficulty_level);

	//終了処理
	void Finish();

	//データの取得
	CDifficultyLevel* GetDifficultyLevelAdress() const;

	void Update();
};

#endif DIFFICULTY_LEVEL_MANAGER_H