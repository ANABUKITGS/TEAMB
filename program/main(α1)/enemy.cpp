#include "enemy.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"
#include "difficulty_level_manager.h"
#include "sounddata_manager.h"

CEffectMovePattern1 EMP1_b;
CEffectMovePattern2 EMP2_a;
CEffectMovePattern4 EMP4;

CEnemyRadTable e_rad_table[] = {
	{ 0, 22.5f, 337.5f, ENEMY_RIGHT },
	{ 45, 67.5f, 22.5f, ENEMY_DR },
	{ 90, 112.5f, 67.5f, ENEMY_DOWN },
	{ 135, 157.5f, 112.5f, ENEMY_DL },
	{ 180, 202.5f, 157.5f, ENEMY_LEFT },
	{ 225, 247.5f, 202.5f, ENEMY_UL },
	{ 270, 292.5f, 247.5f, ENEMY_UP },
	{ 315, 337.5f, 292.5f, ENEMY_UR }
};

//enemyの行動パターン
CMovePattern1 MP1;
CMovePattern2 MP2;
CMovePattern4 MP4;
CMovePattern5 MP5;
CMovePattern6 MP6;
CAttackPattern1 AP1;
CAttackPattern2 AP2;
CAttackPattern4 AP4;
CAttackPattern5 AP5;
CAttackPattern6 AP6;

CECreateTable e_c_table[] = {
	{ 0, NORMAL, ENEMY_EXRATE, ENEMY_NORMAL_SPEED, ENEMY_NORMAL_MASS, ENEMY_NORMAL_HP, ENEMY_COLLISION, 1, &MP1, &AP1 },
	{ 1, LONG_RANGE, ENEMY_LONG_EXRATE, ENEMY_LONG_SPEED, ENEMY_LONG_MASS, ENEMY_LONG_HP, ENEMY_LONG_COLLISION, 1, &MP2, &AP2 },
	{ 2, BIG, ENEMY_EXRATE, ENEMY_BIG_SPEED, ENEMY_BIG_MASS, ENEMY_BIG_HP, ENEMY_BIG_COLLISION, 2, &MP4, &AP4 },
	{ 3, SMALL, ENEMY_EXRATE, ENEMY_SMALL_SPEED, ENEMY_SMALL_MASS, ENEMY_SMALL_HP, ENEMY_SMALL_COLLISION, 0.25f, &MP5, &AP5 },
	{ 4, E_BOMB, ENEMY_EXRATE, ENEMY_BOMB_SPEED, ENEMY_BOMB_MASS, ENEMY_BOMB_HP, ENEMY_ATTACK_BOMB_COLLISION, 0.25f, &MP6, &AP6 },
};

CEnemyData::CEnemyData(){

}

CEnemyData::CEnemyData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, CBaseEemeyMove *_BEMove, CBaseEemeyAttack *_BEAttack)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
, BEMove(_BEMove)
, BEAttack(_BEAttack)
, m_counter(0)
, m_locate(false)
, m_attack_flag(false)
, m_attack_cool_time(0)
, m_item_flag(false)
, m_escape_flag(false)
, m_move_pos(0, 0)
{
}

CEnemyData::CEnemyData(CBaseData _temp, CVector2D _move_pos, bool _invincible, CBaseEemeyMove *_BEMove, CBaseEemeyAttack *_BEAttack)
:CBaseData(_temp.m_pos, _temp.m_living, _temp.m_alpha, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, BEMove(_BEMove)
, BEAttack(_BEAttack)
, m_counter(0)
, m_locate(false)
, m_attack_flag(false)
, m_attack_cool_time(0)
, m_item_flag(false)
, m_escape_flag(false)
, m_move_pos(_move_pos)
{
	m_invincible = _invincible;
}

CEneEffect::CEneEffect(CVector2D *_pos, bool *_living, float _alpha, float _rad, float _exrate)
: m_pos(_pos)
, m_living(_living)
, m_alpha(_alpha)
, m_rad(_rad)
, m_exrate(_exrate)
, m_delete(false)
{
	CEnemyManager::GetInstance()->GetEnemyAdress()->GetEneEffData()->push_back(this);
}

CEnemy::CEnemy(){
	LoadDivGraph("media\\img\\enemy_n_m.png",88,4,22,64,64,m_enemy_img[NORMAL]);
	LoadDivGraph("media\\img\\enemy_l_m.png", 88, 4, 22, 48, 48, m_enemy_img[LONG_RANGE]);
	LoadDivGraph("media\\img\\enemy_b_m.png", 88, 4, 22, 128, 128, m_enemy_img[BIG]);
	LoadDivGraph("media\\img\\enemy_s_m.png", 88, 4, 22, 64, 64, m_enemy_img[SMALL]);
	LoadDivGraph("media\\img\\enemy_bom_m.png", 88, 4, 22, 64, 64, m_enemy_img[E_BOMB]);
	m_enemy_img[BULLET][0] = LoadGraph("media\\img\\enemy_long_range_attack.png");
	m_enemy_img[MAGIC_SQUARE][0] = LoadGraph("media\\img\\magic_square.png");
	m_shadow_img = LoadGraph("media\\img\\shadow.png");

	m_enemy_num.m_normal_num = CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_nomal_num;//GetNormalNum();
	m_enemy_num.m_long_num = CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_long_num;//GetLongNum();
	m_enemy_num.m_big_num = CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_big_num;//GetBigNum();
	m_enemy_num.m_small_num = CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_small_num;//GetSmallNum();
	m_enemy_num.m_bomb_num = CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_bomb_num;//GetBombNum();
	
	m_priority = eDWP_ENEMY;
	m_update_priority = 2;
	m_draw_priority = 2;
	m_update = true;
	
	m_count = 1;

	CEnemyManager::GetInstance()->Init(this);

}

void CEnemy::Delete(){
	//エフェクトの削除処理
	for (auto it = m_ene_eff.begin(); it != m_ene_eff.end();){
		if (*(*it)->m_living == false){
			if (!(*it)->m_delete)
				(*it)->m_delete = true;
		}
		if ((*it)->m_delete){
			if ((*it)->m_alpha < 0){
				it = m_ene_eff.erase(it);
				continue;
			}
			(*it)->m_alpha -= 15;
		}
		it++;
	}
	//敵の削除処理
	for (auto it = m_enemys.begin(); it != m_enemys.end();){
		if ((*it)->m_kill_flag){
			if (!(*it)->m_item_flag){
				(*it)->m_item_flag = true;
				(*it)->m_amine_rate = 0;
				(*it)->m_anim_division = 999;
				(*it)->m_motion_type = 32;
				(*it)->m_direction_type /= 2;
			}
		}
		if ((*it)->m_living == false){
			if ((*it)->m_animtype != E_BOMB){
				CBaseData *_temp = new CBaseData((*it)->m_pos, true, 0, 1.5f, ENEMY_DELETE_NUM, 0, 0, 0, 0, 0, ENEMY_DELETE);
				CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(*_temp, 2, NULL));
			}
			CUiManager::GetInstance()->GetUiAdress()->AddComb();
			CUiManager::GetInstance()->GetUiAdress()->SetCombTimer(ITEM_COMB_TIME);
			PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_E_DEAD), DX_PLAYTYPE_BACK);
			it = m_enemys.erase(it);
			continue;
		}
		it++;
	}
}

void CEnemy::KillAll(){
	for (auto it = m_enemys.begin(); it != m_enemys.end();){
		it = m_enemys.erase(it);
		continue;
		it++;
	}
	for (auto it = m_ene_eff.begin(); it != m_ene_eff.end();){
			it = m_ene_eff.erase(it);
			continue;
		it++;
	}
}

void CEnemy::Update(){
	CVector2D _pos;
	int _num = 0;

	m_enemy_num.m_normal_num = 0;
	m_enemy_num.m_long_num = 0;
	m_enemy_num.m_big_num = 0;
	m_enemy_num.m_small_num = 0;
	m_enemy_num.m_bomb_num = 0;

	for (auto it = m_enemys.begin(); it != m_enemys.end(); it++, _num++){

		EnemyNum(*(*it),1);

		_pos = (*it)->m_pos;

		if ((*it)->m_invincible == 0){

			if (!(*it)->m_kill_flag){

				//移動処理
				{
					(*it)->m_counter++;

					//タイマー（スタン）が０なら移動処理
					if ((*it)->m_timer == 0){
						(*it)->Mover(_pos);
					}
					else if ((*it)->m_timer > 0){
						(*it)->m_timer--;
						if ((*it)->m_velocity < 0)
							(*it)->m_velocity = 0;
					}
				}

				//意識が無ければ以下の処理(吹き飛ばし時に通る)
				{
				//意識なし
				if (!(*it)->m_control){
					_pos += CVector2D((*it)->m_velocity * cos((*it)->m_rad), (*it)->m_velocity * sin((*it)->m_rad));

					if ((*it)->m_velocity <= 0){
						if ((*it)->m_timer == 0){
							(*it)->m_velocity = 0;
							(*it)->m_control = true;
							(*it)->m_motion_type = 0;
						}
						(*it)->m_knock_stan = false;
						(*it)->m_bank_flag = true;
					}
					else
						(*it)->m_velocity -= (*it)->m_friction;

					(*it)->m_locate = false;
				}
				//意識あり
				else{

					//攻撃処理
					(*it)->Attacker();
				}
			}

				//角度によっての向き
				{
					for (auto& rt : e_rad_table){
						//右のアニメーションは分解して最大値と最小値を別々でとること
						if (degree((*it)->m_rad) > 337.5f){
							(*it)->m_direction_type = rt.m_type;
							break;
						}
						if (degree((*it)->m_rad) < 22.5f){
							(*it)->m_direction_type = rt.m_type;
							break;
						}
						if (degree((*it)->m_rad) > rt.m_min_rad && degree((*it)->m_rad) < rt.m_max_rad){
							(*it)->m_direction_type = rt.m_type;
							break;
						}
					}
				}
			}
			else  //体力がなければ以下の処理
				(*it)->m_locate = false;

			//アニメーション関係
			(*it)->m_amine_rate++;
			if ((*it)->m_kill_flag){
				if ((*it)->m_animtype == E_BOMB){
					if ((*it)->m_amine_rate > 120){
						(*it)->m_living = false;
						CEffectData *temp = new CEffectData((*it)->m_pos, true, (*it)->m_rad, ENEMY_BOMB_EXRATE, BOMB_NUM, 0, 2, 0, 1, ENEMY_BOMB_COLLISION, BOMB, 1, &EMP2_a);
						CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
					}
					(*it)->m_anim_division = 7;
					(*it)->m_motion_type = 16;
				}
			}

			//反射処理
			Reflect(*(*it), _pos);

			(*it)->m_move_pos = (*it)->m_pos = _pos;

		}
		///落下処理
		else{
			if ((*it)->m_pos.getY() < (*it)->m_move_pos.getY())//↑- ↓+
				(*it)->m_pos.addY(10.0f);
			else{
				(*it)->m_pos.setY((*it)->m_move_pos.getY());
				(*it)->m_invincible = 0;
			}
		}
	}

	//魔法陣のエフェクト
	{
		for (auto it = m_ene_eff.begin(); it != m_ene_eff.end(); it++){
			(*it)->m_rad += radian(0.5f);
			if ((*it)->m_exrate < 1){
				(*it)->m_exrate += 0.03;
			}
		}
	}

	//削除
	Delete();

	//召喚
	for (int i = _num; i < CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEneMax();i++){
		int _type = 0;//= 4;
		CVector2D _pos1 = CVector2D(rand() % MAP_RANGE_X + 64, rand() % MAP_RANGE_Y + 73);
		CVector2D _pos2 = CVector2D(_pos1.getX(), _pos1.getY() - 820);
		
		if (m_enemy_num.m_normal_num < CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_nomal_num)
			_type = 0;
		else if (m_enemy_num.m_long_num < CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_long_num)
			_type = 1;
		else if (m_enemy_num.m_big_num < CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_big_num)
			_type = 2;
		else if (m_enemy_num.m_small_num < CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_small_num)
			_type = 3;
		else if (m_enemy_num.m_bomb_num < CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_bomb_num)
			_type = 4;

		for (auto &ect : e_c_table){
			if (ect.m_num == _type){
				CBaseData *_temp = new CBaseData(_pos2, true, radian((rand() % 360)), ect.m_exrate, ect.m_type, ect.m_speed, ect.m_mass, ect.m_hp, ENEMY_FRICTION, ect.m_collision, ENEMY);
				CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->push_back(new CEnemyData(*_temp, _pos1, 2, ect.m_BEMove, ect.m_BEAttack));
				break;
			}
		}
	}
}

void CEnemy::EnemyNum(CEnemyData &cd,int _num){
	if (cd.m_animtype == NORMAL){
		m_enemy_num.m_normal_num += _num;
	}
	else if (cd.m_animtype == LONG_RANGE){
		m_enemy_num.m_long_num += _num;
	}
	else if (cd.m_animtype == BIG){
		m_enemy_num.m_big_num += _num;
	}
	else if (cd.m_animtype == SMALL){
		m_enemy_num.m_small_num += _num;
	}
	else{
		m_enemy_num.m_bomb_num += _num;
	}
}

void CEnemy::Reflect(CEnemyData &cd,CVector2D &_pos){
	if (_pos.getY() > MAP_REFLECT_DOWN){
		cd.m_rad = cd.m_rad*(-1);
		_pos.setY(MAP_REFLECT_DOWN * 2 - _pos.getY());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}
	else if (_pos.getY() < MAP_REFLECT_UP){
		cd.m_rad = cd.m_rad*(-1);
		_pos.setY(MAP_REFLECT_UP * 2 - _pos.getY());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}

	if (_pos.getX() > MAP_REFLECT_RIGHT){
		cd.m_rad = PI - cd.m_rad;
		_pos.setX(MAP_REFLECT_RIGHT * 2 - _pos.getX());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}
	else if (_pos.getX() < MAP_REFLECT_LEFT){
		cd.m_rad = PI - cd.m_rad;
		_pos.setX(MAP_REFLECT_LEFT * 2 - _pos.getX());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}
}

void CEnemy::Draw(){
	for (auto it = m_ene_eff.begin(); it != m_ene_eff.end(); it++){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (*it)->m_alpha);
		DrawRotaGraph((*it)->m_pos->getX(), (*it)->m_pos->getY(), (*it)->m_exrate, (*it)->m_rad, m_enemy_img[MAGIC_SQUARE][0],
			TRUE, FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (auto it = m_enemys.begin(); it != m_enemys.end(); it++){
		//影
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90);
		DrawRotaGraph((*it)->m_move_pos.getX(), (*it)->m_move_pos.getY() + 24, 0.7, 0, m_shadow_img, TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if ((*it)->m_animtype != BULLET)
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, /*(*it)->m_rad - degree(90)*/0, m_enemy_img[(*it)->m_animtype][(*it)->m_motion_type + (*it)->m_direction_type + (*it)->m_amine_rate / (*it)->m_anim_division % 2],
			TRUE, FALSE);
		else
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad - degree(90), m_enemy_img[(*it)->m_animtype][0],
			TRUE, FALSE);
	}
}