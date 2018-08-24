#include "difficulty_level_manager.h"
#include "enemy_manager.h"
#include "ui_manager.h"

CEnemyDifficultyTable enemy_diff_table[] = {
	{ 1,7, 0, 0, 0, 8, 0 },
	{ 2,7, 0, 0, 0, 12, 0 },
	{ 3,8, 0, 0, 0, 16, 0 },
	{ 4,9, 4, 0, 0, 14, 0 },
	{ 5,10, 8, 0, 0, 12, 0 },
	{ 6,10, 11, 0, 0, 9, 0 },
	{ 7,10, 17, 0, 0, 6, 0 },
	{ 8,10, 9, 4, 0, 4, 0 },
	{ 9,10, 8, 8, 0, 5, 0 },
	{ 10,10, 8, 14, 0, 2, 0 },
	{ 11,10, 5, 2, 1, 4, 0 },
	{ 12,10, 9, 4, 1, 5, 0 },
	{ 13,10, 11, 8, 1, 2, 0 },
	{ 14,10, 8, 11, 2, 0, 0 },
	{ 15,10, 14, 0, 0, 6, 2 },
	{ 16,10, 13, 5, 4, 3, 5 },
	{ 97,99, 8, 20, 2, 0, 0 },
	{ 98,99, 0, 0, 15, 0, 0 },
	{ 99,99, 0, 0, 0, 0, 29 }
};

CEnemyDifficulty::CEnemyDifficulty()
: m_enemy_level(1)
, m_nomal_num(0)
, m_long_num(0)
, m_big_num(0)
, m_small_num(8)
, m_bomb_num(0)
, m_next_kill(6)
{
}

CDifficultyLevel::CDifficultyLevel()
: m_difficulty_level(1)
, m_enmey_max(8)
, m_item_drop_level(ITEM_CREATE_NUM)
, m_level_up(1)
{
	m_enemy_difficulty = new CEnemyDifficulty();
	m_priority = eDWP_UI;
	CDifficultyLevelManager::GetInstance()->Init(this);
}

void CDifficultyLevel::Update(){
	static bool _flag;
	if (!_flag){
		if (CUiManager::GetInstance()->GetUiAdress()->GatComb() > m_enemy_difficulty->m_next_kill){
			m_enemy_difficulty->m_enemy_level++;
			for (auto edt : enemy_diff_table){
				if (m_enemy_difficulty->m_enemy_level == edt.m_enemy_level){
					m_enemy_difficulty->m_next_kill = edt.m_next_kill;
					m_enemy_difficulty->m_nomal_num = edt.m_nomal_num;
					m_enemy_difficulty->m_long_num = edt.m_long_num;
					m_enemy_difficulty->m_big_num = edt.m_big_num;
					m_enemy_difficulty->m_small_num = edt.m_small_num;
					m_enemy_difficulty->m_bomb_num = edt.m_bomb_num;
					break;
				}
			}
			AddEnemyMax();
			_flag = true;
		}
	}
	if (CUiManager::GetInstance()->GetUiAdress()->GatComb() == 0){
		_flag = false;
	}
}

void CDifficultyLevel::Draw(){

}

void CDifficultyLevel::AddEnemyMax(){
	m_enmey_max = m_enemy_difficulty->m_nomal_num + m_enemy_difficulty->m_long_num + m_enemy_difficulty->m_big_num + m_enemy_difficulty->m_small_num + m_enemy_difficulty->m_bomb_num;
}