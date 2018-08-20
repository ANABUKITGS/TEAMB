#include "difficulty_level_manager.h"

CEnemyDifficultyTable enemy_diff_table[] = {
	{ 1, 0, 0, 0, 8, 0 },
	{ 2, 0, 0, 0, 12, 0 },
	{ 3, 0, 0, 0, 16, 0 },
	{ 4, 4, 0, 0, 14, 0 },
	{ 5, 8, 0, 0, 12, 0 },
	{ 6, 10, 0, 0, 9, 0 },
	{ 7, 14, 0, 0, 6, 0 },
	{ 8, 6, 3, 0, 6, 0 },
	{ 9, 7, 5, 0, 7, 0 },
	{ 10, 8, 9, 0, 2, 0 },
	{ 11, 5, 2, 1, 4, 0 },
	{ 12, 9, 4, 1, 5, 0 },
	{ 13, 11, 8, 1, 2, 0 },
	{ 14, 8, 11, 1, 0, 0 },
	{ 15, 14, 0, 0, 6, 2 },
	{ 16, 12, 3, 1, 3, 5 },
	{ 97, 6, 15, 2, 0, 0 },
	{ 98, 0, 0, 13, 0, 0 },
	{ 99, 0, 0, 0, 0, 25 }
};

CEnemyDifficulty::CEnemyDifficulty()
: m_enemy_level(1)
, m_nomal_num(0)
, m_long_num(0)
, m_big_num(0)
, m_small_num(8)
, m_bomb_num(0)
{
}

CDifficultyLevel::CDifficultyLevel()
: m_enemy_difficulty()
, m_difficulty_level(1)
, m_item_drop_level(6)
{
	CDifficultyLevelManager::GetInstance()->Init(this);
}

void CDifficultyLevel::Update(){

}

void CDifficultyLevel::Draw(){

}