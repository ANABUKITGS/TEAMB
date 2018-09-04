#include "difficulty_level_manager.h"
#include "enemy_manager.h"
#include "ui_manager.h"
#include "field_manager.h"
#include "player_manager.h"
#include "task_manager.h"
#include "item_manager.h"

CEnemyDifficultyTable enemy_diff_table[] = {
	{ 0, 4, 0, 0, 0, 8, 0 },		//チュートリアル
	{ 1, 7, 0, 0, 0, 10, 0 },
	{ 2,7, 0, 0, 0, 16, 0 },
	{ 3,10, 4, 0, 0, 16, 0 },
	{ 4,13, 9, 0, 0, 12, 0 },
	{ 5,14, 17, 0, 0, 8, 0 },
	{ 6,12, 11, 6, 0, 6, 0 },
	{ 7,16, 15, 10, 0, 3, 0 },
	{ 8,10, 10, 5, 1, 3, 0 },
	{ 9,14, 8, 8, 2, 5, 0 },
	{ 10,15, 8, 14, 2, 2, 0 },
	{ 11,10, 9, 4, 0, 4, 3 },
	{ 12,10, 10, 9, 1, 0, 6 },//現在ここまで
	{ 13,10, 11, 8, 1, 2, 0 },
	{ 14,10, 8, 11, 2, 0, 0 },
	{ 15,10, 14, 0, 0, 6, 2 },
	{ 16,10, 13, 5, 4, 3, 5 },
	{ 97,99, 8, 20, 2, 0, 0 },
	{ 98,99, 0, 0, 15, 0, 0 },
	{ 99,99, 0, 0, 0, 0, 29 }
};

CEnemyDifficultyTable boss_diff_table[] = {
	{ 1, 0, 6, 0, 0, 8, 0 },//現在ここまで
};

CEnemyDifficulty::CEnemyDifficulty()
: m_enemy_level(0)
, m_nomal_num(0)
, m_long_num(0)
, m_big_num(0)
, m_small_num(8)
, m_bomb_num(0)
, m_next_kill(4)
{
}

CArrowData::CArrowData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type, CVector2D* _pos2, bool* _living2)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _type)
, m_a_pos(_pos2)
, m_a_living(_living2)
{
	
}

CTutorialData::CTutorialData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _type)
, m_pass_flag(false)
{
	m_invincible = 0;
	m_kill_flag = false;
	m_attack_pass_flag = false;

	for (int i = 0; i < 3; i++)
		m_icon_pass[i] = false;

	m_tutorial_img[0] = LoadGraph("media\\img\\tutorial\\tutorial_0.jpg");
	m_tutorial_img[1] = LoadGraph("media\\img\\tutorial\\tutorial_1.jpg");
	m_tutorial_img[2] = LoadGraph("media\\img\\tutorial\\tutorial_2.jpg");
	m_tutorial_img[3] = LoadGraph("media\\img\\tutorial\\tutorial_3.jpg");

	m_t_range_img[0] = LoadGraph("media\\img\\arrow_head.png");
	m_t_range_img[1] = LoadGraph("media\\img\\range_exp_o_ma.png");
	m_t_range_img[2] = LoadGraph("media\\img\\great.png");
	
	m_t_range = new CBaseData(CVector2D(100, 360), false, 255, 0, 0.4f, 0, 0);
	m_t_text = new CBaseData(CVector2D(100, 360), false, 255, 0, 0.4f, 0, 0);
}

CDifficultyLevel::CDifficultyLevel()
: m_difficulty_level(0)
, m_enmey_max(8)
, m_item_drop_level(ITEM_CREATE_NUM)
, m_level_up(1)
, m_tutorial_flag(true)
{
	m_tutorial = nullptr;
	m_enemy_difficulty = new CEnemyDifficulty();
	m_tutorial = new CTutorialData(CVector2D(1280,0),false,255,0,1,0,0);
	m_priority = 2;

	CDifficultyLevelManager::GetInstance()->Init(this);
}

void CDifficultyLevel::Update(){
	static bool _flag;
	if (!_flag){
		if (CEnemyManager::GetInstance()->GetEnemyAdress()->GetCreateTimer() != 0){
			if (CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType() == M_NORMAL){
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
			}
			else{
				for (auto edt : boss_diff_table){
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
			}
			AddEnemyMax();
			_flag = true;
		}
	}
	if (CEnemyManager::GetInstance()->GetEnemyAdress()->GetCreateTimer() == 0){
		_flag = false;
	}


	if (m_tutorial_flag)
		;
	else{
		if (m_tutorial){
			m_tutorial->KillRange();
			delete m_tutorial;
			m_tutorial = 0;
		}
	}
}

void CDifficultyLevel::Draw(){
	if (m_tutorial_flag){
		if (m_tutorial->m_t_range->m_living)
			DrawRotaGraph(m_tutorial->m_t_range->m_pos.getX(), m_tutorial->m_t_range->m_pos.getY(), m_tutorial->m_t_range->m_exrate, m_tutorial->m_t_range->m_mass, m_tutorial->m_t_range_img[1], TRUE, FALSE);
	}
}

void CDifficultyLevel::AddEnemyMax(){
	m_enmey_max = m_enemy_difficulty->m_nomal_num + m_enemy_difficulty->m_long_num + m_enemy_difficulty->m_big_num + m_enemy_difficulty->m_small_num + m_enemy_difficulty->m_bomb_num;
}

/////////////////////////////////////////

void CTutorialData::Update(){
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	float _add = 0;
	if (m_invincible == 1){
		m_pos.addX(-10);
		if (m_pos.getX() < -1280){
			m_pass_flag = false;
			m_invincible = 0;
			m_animtype++;
			m_pos.setX(1280);
			switch (m_animtype)
			{
			case 1:
				m_t_range->m_pos = CVector2D(300, 360);
				m_t_range->m_living = true;//new CBaseData(CVector2D(100,360),true,255,0,0.4f,0,0);
				m_t_range->m_collision = 100;
				m_t_range->m_exrate = 0;
				m_arrow.push_back(new CArrowData(CVector2D(300, 360), true, 255, 0, 0.6f, 0, 0, NULL, false));
				break;
			case 2:
				m_arrow.push_back(new CArrowData(CVector2D(130, 620), true, 255, 0, 0.6f, 0, 0, NULL, false));
				break;
			case 3:
				break;

			default:
				break;
			}
		}
		else if (m_pos.getX() < 0 && !m_pass_flag){
			m_invincible = 2;
			m_pos.setX(0);
		}
	}
	else if (m_invincible == 2){
		if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2)){
			m_invincible = 1;
			m_pass_flag = true;
		}
	}
	if (m_animtype > 3){
		CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->SetTutorialFlag(false);
	}

	//チュートリアルの行動の処理
	if (m_invincible == 0){
		int _a = 0;
		switch (m_animtype)
		{
		case 1:		//移動チュートリアル
			if (m_t_range->m_living){
				if (IsHitCircle(m_t_range->m_collision, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_collision,
					m_t_range->m_pos, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos)){
					m_t_range->m_living = false;
					for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
						(*it)->m_living = false;
					}
					m_t_text->m_pos = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos;
					m_t_text->m_living = true;
				}
				if (m_t_range->m_exrate < 0.4f)
					m_t_range->m_exrate += 0.005f;
			}
			break;
		case 2:		//攻撃チュートリアル
			m_icon_pass[CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_attack_type] = true;
			for (int i = 0; i < 3; i++){
				if (m_icon_pass[i] == true){
					_a++;
				}
			}
			if (_a == 3){
				for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
					(*it)->m_pos = CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY() - 20);
				}
				//プレイヤーを攻撃したら
				if (!m_attack_pass_flag){
					if (CPlayerManager::GetInstance()->GetPlayerAdress()->GetAttackState() == 0){
						for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
							(*it)->m_living = false;
						}
						CTaskManager::GetInstance()->SerectUpdate(eDWP_ENEMY, true);
					}
				}

				//矢印の生成
				for (auto it = CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->begin();
					it != CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->end(); it++){
					if (!(*it)->m_t_arrow){
						m_arrow.push_back(new CArrowData(CVector2D(130, 620), true, 255, 0, 0.6f, 0, 0, &(*it)->m_pos, &(*it)->m_living));
						(*it)->m_t_arrow = true;
					}
					m_attack_pass_flag = true;
				}

				if (CEnemyManager::GetInstance()->GetEnemyAdress()->GetKillCount() > 3){
					for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
						(*it)->m_living = false;
					}
					m_t_text->m_pos = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos;
					m_t_text->m_living = true;
				}
			}
			break;
		case 3:		//アイテムチュートリアル
			if (CPlayerManager::GetInstance()->GetPlayerAdress()->GetItemGet()){
				for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
					(*it)->m_living = false;
				}
				m_t_text->m_pos = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos;
				m_t_text->m_living = true;
			}
			else{
				for (auto it = CItemManager::GetInstance()->GetItemAdress()->GetItemData()->begin();
					it != CItemManager::GetInstance()->GetItemAdress()->GetItemData()->end(); it++){
					if (!(*it)->m_t_create){
						m_arrow.push_back(new CArrowData(CVector2D(130, 620), true, 255, 0, 0.6f, 0, 0, &(*it)->m_pos, &(*it)->m_living));
						(*it)->m_t_create = true;
					}
				}
				CEnemyManager::GetInstance()->GetEnemyAdress()->SetCreateTimer(210);
			}
			break;

		default:
			break;
		}
	}

	if (m_t_range->m_living){
		m_t_range->m_mass += 0.03f;
	}

	for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
		(*it)->m_mass += 0.035f;
	}

	if (m_t_text->m_living){
		if (m_t_text->m_mass < 1.0f)
			m_t_text->m_mass += 0.015f;
		else{
			m_t_text->m_living = false;
			m_t_text->m_mass = 0;
			m_invincible = 1;
		}
	}

	for (auto it = m_arrow.begin(); it != m_arrow.end();){
		if (!(*it)->m_living){
			it = m_arrow.erase(it);
			continue;
		}
		if (m_animtype > 1 && m_attack_pass_flag){
			if (!*(*it)->m_a_living){
				it = m_arrow.erase(it);
				continue;
			}
		}
		it++;
	}
}

void CTutorialData::Draw(){
	if (CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialFlag()){
		DrawGraph(m_pos.getX(), m_pos.getY(), m_tutorial_img[m_animtype], true);
		for (auto it = m_arrow.begin(); it != m_arrow.end(); it++){
			if (!m_attack_pass_flag)
				DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY() - 60 - 20 * cos((*it)->m_mass), 0.6f, 0, m_t_range_img[0], TRUE, FALSE);
			else{
				DrawRotaGraph((*it)->m_a_pos->getX(), (*it)->m_a_pos->getY() - 60 - 20 * cos((*it)->m_mass), 0.4f, 0, m_t_range_img[0], TRUE, FALSE);
			}
		}
		if (m_t_text->m_living)
			DrawRotaGraph(m_t_text->m_pos.getX(), m_t_text->m_pos.getY() - 290 - 200 * -cos(m_t_text->m_mass), 0.7f, 0, m_t_range_img[2], TRUE, FALSE);
	}
}

int CDifficultyLevel::TutorialState(){
	if (m_tutorial_flag){
		if (m_tutorial != NULL)
			return m_tutorial->m_invincible;
	}
	else{
		return 0;
	}
}

void CTutorialData::KillRange(){
	delete m_t_range;
	m_t_range = 0;
	delete m_t_text;
	m_t_text = 0;
	for (auto it = m_arrow.begin(); it != m_arrow.end();){
		it = m_arrow.erase(it);
		continue;
		it++;
	}
}