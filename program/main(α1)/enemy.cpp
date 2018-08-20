#include "enemy.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"

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

CEnemyData::CEnemyData(){

}

CEnemyData::CEnemyData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, CBaseEemeyMove *_BEMove, CBaseEemeyAttack *_BEAttack)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision,_type)
, BEMove(_BEMove)
, BEAttack(_BEAttack)
, m_counter(0)
, m_locate(false)
, m_attack_flag(false)
, m_attack_cool_time(0)
, m_item_flag(false)
, m_escape_flag(false)
{
}

CEnemyData::CEnemyData(CBaseData _temp, CBaseEemeyMove *_BEMove, CBaseEemeyAttack *_BEAttack)
:CBaseData(_temp.m_pos, _temp.m_living, _temp.m_alpha, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, BEMove(_BEMove)
, BEAttack(_BEAttack)
, m_counter(0)
, m_locate(false)
, m_attack_flag(false)
, m_attack_cool_time(0)
, m_item_flag(false)
, m_escape_flag(false)
{
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

	m_priority = eDWP_ENEMY;
	m_update_priority = 2;
	m_draw_priority = 2;
	
	m_count = 1;
	m_dead_count = 0;

	CEnemyManager::GetInstance()->Init(this);

}

void CEnemy::Delete(){
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
	for (auto it = m_enemys.begin(); it != m_enemys.end();){
		if ((*it)->m_kill_flag){
			if (!(*it)->m_item_flag){
				m_dead_count++;
				(*it)->m_item_flag = true;
			}
		}
		if ((*it)->m_living == false){
			if ((*it)->m_animtype != E_BOMB){
				CBaseData *_temp = new CBaseData((*it)->m_pos, true, 0, 1, ENEMY_DELETE_NUM, 0, 0, 0, 0, 0, ENEMY_DELETE);
				CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(*_temp, 2, NULL));
			}
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

	m_dead_count = 0;

	for (auto it = m_enemys.begin(); it != m_enemys.end(); it++){

		_pos = (*it)->m_pos;

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

		//反射処理
		Reflect(*(*it), _pos);

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



		(*it)->m_pos = _pos;

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

//#if defined(_DEBUG) | defined(DEBUG)
	if (m_enemys.size() < MAX_ENEMY)
	if (m_count % 50 == 0){
		CVector2D _pos = CVector2D(rand() % MAP_RANGE_X + 64, rand() % MAP_RANGE_Y + 73);
		CBaseData *_temp_e = new CBaseData(_pos + CVector2D(0,-30), true, 0, 1, ENEMY_CREATE_NUM, 0, 0, 0, 0, 0, ENEMY_CREATE);
		CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(*_temp_e, 2, &EMP4));
		m_count = 1;
	}
	m_count++;

//#endif
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
		if ((*it)->m_animtype != BULLET)
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, /*(*it)->m_rad - degree(90)*/0, m_enemy_img[(*it)->m_animtype][(*it)->m_motion_type + (*it)->m_direction_type + (*it)->m_amine_rate / (*it)->m_anim_division % 2],
			TRUE, FALSE);
		else
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad - degree(90), m_enemy_img[(*it)->m_animtype][0],
			TRUE, FALSE);
	}
}