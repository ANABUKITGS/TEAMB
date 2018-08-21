#ifndef DIFFICULTY_LEVEL_H
#define DIFFICULTY_LEVEL_H

#include "task.h"
#include "base_data.h"

class CEnemyDifficultyTable{
public:
	int m_enemy_level;
	int m_next_kill;
	int m_nomal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CEnemyDifficulty{
public:
	CEnemyDifficulty();
	~CEnemyDifficulty(){};
	int m_enemy_level;
	int m_next_kill;
	int m_nomal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CDifficultyLevel : public CTask{
private:
	CEnemyDifficulty *m_enemy_difficulty;
	int m_difficulty_level;
	int m_enmey_max;
	int m_item_drop_level;
	int m_level_up;
	int m_level_num;
public:
	CDifficultyLevel();
	~CDifficultyLevel(){ delete m_enemy_difficulty; };

	void Update();
	void Draw();

	//エネミーを全部足したやつ
	void AddEnemyMax();

	inline void SetDifficulty(int _level){ m_difficulty_level = _level; };
	inline void SetEnemyLevel(int _level){ m_enemy_difficulty->m_enemy_level = _level; };
	inline void SetItemDrop(int _level){ m_item_drop_level = _level; };
	
	inline CEnemyDifficulty *GetEnemyDifficulty(){ return m_enemy_difficulty; };
	inline int GetEneMax(){ return m_enmey_max; };
	inline int GetItemDropLevel(){ return m_item_drop_level; };
};

#endif DIFFICULTY_LEVEL_H