#ifndef DIFFICULTY_LEVEL_H
#define DIFFICULTY_LEVEL_H

#include "task.h"
#include "base_data.h"

class CEnemyDifficultyTable{
public:
	int m_enemy_level;
	int m_nomal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CEnemyDifficulty{
public:
	CEnemyDifficulty();
	~CEnemyDifficulty();
	int m_enemy_level;
	int m_nomal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CDifficultyLevel : public CTask{
private:
	CEnemyDifficulty m_enemy_difficulty;
	int m_difficulty_level;
	int m_item_drop_level;
public:
	CDifficultyLevel();
	~CDifficultyLevel(){};

	void Update();
	void Draw();

	void SetDifficulty(int _level){ m_difficulty_level = _level; };
	void SetEnemyLevel(int _level){ m_enemy_difficulty.m_enemy_level = _level; };
	void SetItemDrop(int _level){ m_item_drop_level = _level; };
	CEnemyDifficulty GetEnemyDifficulty(){ return m_enemy_difficulty; };
};

#endif DIFFICULTY_LEVEL_H