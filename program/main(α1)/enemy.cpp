#include "enemy.h"
#include "enemy_manager.h"
#include "effect_manager.h"

CMovePattern1 MP1;
CAttackPattern1 AP1;
CEffectMovePattern4 EMP4;

CEnemyData::CEnemyData(){

}

CEnemyData::CEnemyData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision,_type)
, BEMove(&MP1)
, BEAttack(&AP1)
, m_counter(0)
, m_locate(false)
, m_attack_flag(false)
, m_attack_cool_time(0)
{
}

CEnemyData::CEnemyData(CBaseData _temp)
:CBaseData(_temp.m_pos, _temp.m_living, _temp.m_alpha, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, BEMove(&MP1)
, BEAttack(&AP1)
, m_counter(0)
, m_locate(false)
, m_attack_flag(false)
, m_attack_cool_time(0)
{
}

CEnemy::CEnemy(){
	m_enemy_img[0] = LoadGraph("media\\img\\enemy.png");

	m_priority = eDWP_ENEMY;
	m_update_priority = 2;
	m_draw_priority = 2;
	
	m_count = 1;
	m_dead_count = 0;

	CEnemyManager::GetInstance()->Init(this);

}

void CEnemy::Delete(){
	for (auto it = m_enemys.begin(); it != m_enemys.end();){
		if ((*it)->m_living == false){
			CBaseData *_temp = new CBaseData((*it)->m_pos, true, 0, 1, ENEMY_DELETE_NUM, 0, 0, 0, 0, 0, ENEMY_DELETE);
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(*_temp,2,NULL));
			m_dead_count++;
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
}

void CEnemy::Update(){
	CVector2D _pos;

	m_dead_count = 0;

	for (auto it = m_enemys.begin(); it != m_enemys.end(); it++){

		_pos = (*it)->m_pos;

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
					}
					(*it)->m_knock_stan = false;
				}
				else
					(*it)->m_velocity -= (*it)->m_friction;
			}
			//意識あり
			else{
				(*it)->m_velocity = ENEMY_SPEED;

				//攻撃処理
				(*it)->Attacker();
			}
		}

		//反射処理
		Reflect(*(*it), _pos);

		(*it)->m_pos = _pos;

	}
	//削除
	Delete();

//#if defined(_DEBUG) | defined(DEBUG)
	if (m_enemys.size() < MAX_ENEMY)
	if (m_count % 50 == 0){
		CVector2D _pos = CVector2D(rand() % 1200 + 30, rand() % 660 + 30);
		CBaseData *_temp_e = new CBaseData(_pos + CVector2D(0,-30), true, 0, 1, ENEMY_CREATE_NUM, 0, 0, 0, 0, 0, ENEMY_CREATE);
		//CBaseData *_temp = new CBaseData(_pos, true, radian((rand() % 360)), ENEMY_EXRATE, 0, ENEMY_SPEED, ENEMY_MASS, ENEMY_HP, ENEMY_FRICTION, ENEMY_COLLISION, ENEMY);
		//m_enemys.push_back(new CEnemyData(*_temp));
		CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(*_temp_e, 2, &EMP4));
		m_count = 1;
	}
	m_count++;

//#endif
}

void CEnemy::Reflect(CEnemyData &cd,CVector2D &_pos){
	if (_pos.getY() > 720){
		cd.m_rad = cd.m_rad*(-1);
		_pos.setY(720 * 2 - _pos.getY());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}
	else if (_pos.getY() < 0){
		cd.m_rad = cd.m_rad*(-1);
		_pos.setY(-_pos.getY());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}

	if (_pos.getX() > 1280){
		cd.m_rad = PI - cd.m_rad;
		_pos.setX(1280 * 2 - _pos.getX());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}
	else if (_pos.getX() < 0){
		cd.m_rad = PI - cd.m_rad;
		_pos.setX(-_pos.getX());
		if (cd.m_control == false)
			cd.m_timer += BANK_STAN;
	}
}

void CEnemy::Draw(){
	for (auto it = m_enemys.begin(); it != m_enemys.end(); it++){
		DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad - degree(90), m_enemy_img[0],
			TRUE,FALSE);
		/*printfDx("enemy Type %d ", (*it)->m_type);
		printfDx("HP %d ", (*it)->m_hp);
		printfDx("mass %f ", (*it)->m_mass);
		printfDx("Velo %f ", (*it)->m_velocity);
		printfDx("rad %f\n", degree((*it)->m_rad));*/
	}
}