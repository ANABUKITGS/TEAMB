#include "base_data.h"
#include "field_manager.h"
#include "enemy_manager.h"

CCharaData* CCharaData::m_pInstance = nullptr;

CBaseData::CBaseData(){

}

CBaseData::CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type)
: m_pos(_pos)
, m_living(_living)
, m_alpha(_alpha)
, m_rad(_rad)
, m_exrate(_exrate)
, m_animtype(_animtype)
, m_velocity(_velocity)
, m_speed(_velocity)
, m_mass(_mass)
, m_amine_rate(0)
, m_hp(_hp)
, m_friction(_friction)
, m_collision(_collision)
, m_control(true)
, m_type(_type)
, m_timer(0)
, m_damage(0)
, m_invincible(0)
, m_knock_stan(false)
, m_bank_flag(true)
, m_kill_flag(false)
, m_motion_type(0)
, m_direction_type(0)
, m_anim_division(15)
{
	CCharaData::GetInstance()->AddTaskInner(this);
}

CBaseData::CBaseData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type)
: m_pos(_pos)
, m_living(_living)
, m_alpha(256)
, m_rad(_rad)
, m_exrate(_exrate)
, m_animtype(_animtype)
, m_velocity(_velocity)
, m_speed(_velocity)
, m_mass(_mass)
, m_amine_rate(0)
, m_hp(_hp)
, m_friction(_friction)
, m_collision(_collision)
, m_control(true)
, m_type(_type)
, m_timer(0)
, m_damage(0)
, m_invincible(0)
, m_knock_stan(false)
, m_bank_flag(true)
, m_kill_flag(false)
, m_motion_type(0)
, m_direction_type(0)
, m_anim_division(15)
{
}

CBaseData::CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type)
: m_pos(_pos)
, m_living(_living)
, m_alpha(_alpha)
, m_rad(_rad)
, m_exrate(_exrate)
, m_animtype(_animtype)
, m_velocity(0)
, m_speed(0)
, m_mass(0)
, m_amine_rate(0)
, m_hp(0)
, m_friction(0)
, m_collision(0)
, m_control(true)
, m_type(_type)
, m_timer(0)
, m_damage(0)
, m_invincible(0)
, m_knock_stan(false)
, m_bank_flag(true)
, m_kill_flag(false)
, m_motion_type(0)
, m_direction_type(0)
, m_anim_division(15)
{
}

CBaseData::~CBaseData(){
}

void CBaseData::Update(){
}

CCharaData::CCharaData(){
	m_ehp_img[0] = LoadGraph("media\\img\\enemy_hp.jpg");
	m_ehp_img[1] = LoadGraph("media\\img\\enemy_hp_b1.jpg");
	m_hhp_img[0] = LoadGraph("media\\img\\hero_hp2.jpg");
	m_hhp_img[1] = LoadGraph("media\\img\\hero_hp2_b1.jpg");
	m_bhp_img[0] = LoadGraph("media\\img\\boss_hp1.jpg");
	m_bhp_img[1] = LoadGraph("media\\img\\boss_hp2.jpg");
	m_stan_timer_img = LoadGraph("media\\img\\enemy_stan_timer.jpg");
}

void CCharaData::AddTaskInner(CBaseData* task){
	m_chara_data.push_back(task);
}

CCharaData* CCharaData::GetInstance(){
	//CCharaDataを一度のみ（シングルトン）生成して格納
	if (m_pInstance == nullptr){
		m_pInstance = new CCharaData();
	}
	return m_pInstance;
}

void CCharaData::ClearInstance(){
	if (m_pInstance != nullptr)delete m_pInstance;
}

void CCharaData::KillAll(){
	for (auto it = m_chara_data.begin(); it != m_chara_data.end();){
		it = m_chara_data.erase(it);
		continue;
		it++;
	}
}

void CCharaData::AssignmentDelete(){
	for (auto it = m_chara_data.begin(); it != m_chara_data.end();){
		if ((*it)->m_type != PLAYER){
			it = m_chara_data.erase(it);
			continue;
		}
		it++;
	}
}

void CCharaData::AssignmentInvincible(int _type){
	for (auto it = m_chara_data.begin(); it != m_chara_data.end(); it++){
		if (_type == 0){
			if ((*it)->m_animtype == 90){
				(*it)->m_invincible = 1;
			}
			if ((*it)->m_type == ENEMY){
				(*it)->m_invincible = 0;
			}
		}
		else{
			if ((*it)->m_animtype == 90){
				(*it)->m_invincible = 0;
			}
			if ((*it)->m_type == ENEMY){
				(*it)->m_invincible = 1;
			}
		}
	}
}

void CCharaData::Counter(){
	for (auto it = m_chara_data.begin(); it != m_chara_data.end(); it++){
		printfDx("base Type %d ", (*it)->m_type);
		printfDx("HP %d ", (*it)->m_hp);
		//printfDx("pos %f / %f ", (*it)->m_pos.getX(), (*it)->m_pos.getY());
		//printfDx("mass %f ", (*it)->m_mass);
		printfDx("Velo %f ", (*it)->m_velocity);
		//printfDx("cont %d ", (*it)->m_control);
		printfDx("rad %f\n", degree((*it)->m_rad));
	}
}

void CCharaData::Delete(){
	for (auto it = m_chara_data.begin(); it != m_chara_data.end();){
		if ((*it)->m_living == false){
			it = m_chara_data.erase(it);
			continue;
		}
		it++;
	}
}

void CCharaData::Update(){
	int _suu = 0;
	bool _f = false;

	for (auto it1 = m_chara_data.begin(); it1 != m_chara_data.end(); it1++,_suu++){
		if (!(*it1)->m_kill_flag){
			if ((*it1)->m_hp < 1){
				(*it1)->m_kill_flag = true;
				(*it1)->m_amine_rate = 0;
				continue;
			}		//HPが0なら生きていない
		}
		for (auto it2 = m_chara_data.begin(); it2 != m_chara_data.end(); it2++){
			if ((*it1)->m_pos != (*it2)->m_pos){
				if (IsHitCircle((*it1)->m_collision, (*it2)->m_collision, (*it1)->m_pos, (*it2)->m_pos)){
					if (((*it1)->m_type >= BOSS || (*it2)->m_type >= BOSS)){
						LieOnTopProtect(*it1, *it2);//ボスのみ特殊で当たっても弾く処理をしない
						break;
					}
					if ((*it1)->m_invincible == 0 && (*it2)->m_invincible == 0){
						if ((*it1)->m_type != ITEM && (*it2)->m_type != ITEM && (*it1)->m_type != ENEMY_BULLET && (*it2)->m_type != ENEMY_BULLET){
							if ((*it1)->m_type < BOSS || (*it2)->m_type < BOSS)
								CBank(*it1, *it2);
						}
					}

				}
			}
		}
		_f = false;
	}
}

void CCharaData::LieOnTopProtect(CBaseData* cd1, CBaseData* cd2){
	float _vx = cd1->m_pos.getX() - cd2->m_pos.getX();
	float _vy = cd1->m_pos.getY() - cd2->m_pos.getY();

	float _mx = 0;
	float _my = 0;

	if (cd1->m_type == PLAYER){
		_mx = cd1->m_pos.getX();
		_my = cd1->m_pos.getY();
	}
	else if (cd2->m_type == PLAYER){
		_mx = cd2->m_pos.getX();
		_my = cd2->m_pos.getY();
	}

	float _len = sqrt(_vx * _vx + _vy * _vy);

	float _dist = (cd1->m_collision + cd2->m_collision) - _len;

	if (_len > 0)_len = 1 / _len;

	_vx *= _len;
	_vy *= _len;

	if (cd1->m_type == PLAYER){
		if (cd2->m_type >= BOSS && cd2->m_invincible == 0)
			cd1->m_pos += CVector2D(_vx * _dist * 1.1f, _vy*_dist * 1.1f);
		//プレイヤーのマップ外移動防止
		if (cd1->m_pos.getY() < 83 || cd1->m_pos.getY() >  615){
			cd1->m_pos.setY(_my);
		}
		if (cd1->m_pos.getX() < 64 || cd1->m_pos.getX() > 1216){
			cd1->m_pos.setX(_mx);
		}
	}
	if (cd2->m_type == PLAYER){
		if (cd1->m_type >= BOSS && cd1->m_invincible == 0)
			cd2->m_pos -= CVector2D(_vx * _dist * 1.1f, _vy*_dist * 1.1f);
		//プレイヤーのマップ外移動防止
		if (cd2->m_pos.getY() < 83 || cd2->m_pos.getY() >  615){
			cd2->m_pos.setY(_my);
		}
		if (cd2->m_pos.getX() < 64 || cd2->m_pos.getX() > 1216){
			cd2->m_pos.setX(_mx);
		}
	}
}

void CCharaData::CBank(CBaseData* cd1, CBaseData* cd2){

	/*if (cd1->m_knock_stan == true){
		cd1->m_timer += BANK_STAN;
		cd2->m_timer += BANK_STAN;
		cd2->m_knock_stan = true;

		}
	if (cd2->m_knock_stan == true){
		cd1->m_timer += BANK_STAN;
		cd2->m_timer += BANK_STAN;
		cd1->m_knock_stan = true;
	}*/

	if (cd1->m_control){
		if (cd1->m_type == PLAYER)
			cd2->m_velocity = 5.5f;// / cd2->m_mass;
		else
			cd1->m_velocity = 2.5f;// / cd1->m_mass;
	}
	if (cd2->m_control){
		if (cd2->m_type == PLAYER)
			cd1->m_velocity = 5.5f;// / cd1->m_mass;
		else
		cd2->m_velocity = 2.5f;// / cd2->m_mass;
	}

	////操作不可能////
	cd1->m_control = false;
	cd2->m_control = false;

	/////めり込み防止/////
	float _vx = cd1->m_pos.getX() - cd2->m_pos.getX();
	float _vy = cd1->m_pos.getY() - cd2->m_pos.getY();

	float _len = sqrt(_vx * _vx + _vy * _vy);

	float _dist = (cd1->m_collision + cd2->m_collision) - _len;

	if (_len > 0)_len = 1 / _len;

	_vx *= _len;
	_vy *= _len;

	_dist /= 2.0f;

	cd1->m_pos += CVector2D(_vx * _dist * 1.1f, _vy*_dist * 1.1f);
	cd2->m_pos -= CVector2D(_vx * _dist * 1.1f, _vy*_dist * 1.1f);
	///////////////////////
	if (cd1->m_bank_flag){
		//反発係数
		float _e = 1.0f;
		bool _a = false;
		if (cd2->m_velocity > cd1->m_velocity){
			float temp = cd2->m_velocity;
			cd2->m_velocity = cd1->m_velocity;
			cd1->m_velocity = temp;
			_a = true;
		}

		float _rad1 = PosRad(cd1->m_pos, cd2->m_pos);//衝突後の相手
		float _rad2 = cd1->m_rad - _rad1;	//角度の差
		float _rad3 = cd1->m_rad + _rad2;	//衝突後自分の角度


		if (_rad2 < 0)_rad2 = _rad2 + 2 * PI;
		if (_rad3 < 0)_rad3 = _rad3 + 2 * PI;

		//cd1->m_pos += CVector2D(cos(_rad4) * _dist, sin(_rad4) * _dist);
		//cd2->m_pos += CVector2D(cos(_rad1) * _dist, sin(_rad1) * _dist);

		//cd2->m_velocity = cd1->m_velocity;//_s1;

		//cd2->m_velocity = abs(cos(_rad2) * cd1->m_velocity);

		cd2->m_velocity = abs(cos(_rad2) * ((-cd2->m_velocity - cd1->m_velocity)*(1 + _e) / (cd2->m_mass / cd1->m_mass + 1) + cd2->m_velocity));
		cd1->m_velocity = abs(cd1->m_velocity - cd2->m_velocity);

		//cd1->m_velocity = abs(sin(_rad2) * ((-cd1->m_velocity - cd2->m_velocity)*(1 + _e) / (cd1->m_mass / cd2->m_mass + 1) + cd1->m_velocity));

		cd2->m_rad = _rad1;
		cd1->m_rad = _rad3;
	}

}

void CCharaData::Draw(){
	float _hp_division = 1.0f;
	for (auto it = m_chara_data.begin(); it != m_chara_data.end(); it++){
		if ((*it)->m_type == ENEMY){
			if ((*it)->m_invincible == 0){
				if ((*it)->m_animtype == SMALL || (*it)->m_animtype == E_BOMB)
					_hp_division = 0.25f;
				else if ((*it)->m_animtype == BIG)
					_hp_division = 3;
				else
					_hp_division = 1;
				if (((*it)->m_hp / _hp_division) < 64)
					DrawRectGraph((*it)->m_pos.getX() - 32, (*it)->m_pos.getY() - 25, 0, 0, (*it)->m_hp / _hp_division, 4, m_ehp_img[0], FALSE, FALSE);
				if ((*it)->m_damage > 0)
					DrawRectGraph((*it)->m_pos.getX() - 32 + (*it)->m_hp / _hp_division, (*it)->m_pos.getY() - 25, 0, 0, (*it)->m_damage / _hp_division, 4, m_ehp_img[1], FALSE, FALSE);
				if ((*it)->m_timer > 0)
					DrawRectGraph((*it)->m_pos.getX() - 32, (*it)->m_pos.getY() - 21, 0, 0, (*it)->m_timer / 20, 2, m_stan_timer_img, FALSE, FALSE);
			}
		}
		if ((*it)->m_type == PLAYER){
			DrawRectGraph((*it)->m_pos.getX() - 32, (*it)->m_pos.getY() - 47, 0, 0, (*it)->m_hp, 8, m_hhp_img[0], FALSE, FALSE);
			if ((*it)->m_damage > 0)
				DrawRectGraph((*it)->m_pos.getX() - 32 + (*it)->m_hp, (*it)->m_pos.getY() - 47, 0, 0, (*it)->m_damage, 8, m_hhp_img[1], FALSE, FALSE);
		}
		if ((*it)->m_type == BOSS){
			if ((*it)->m_invincible == 0){
				DrawRectGraph((*it)->m_pos.getX() - 382, 0, 0, 0, (*it)->m_hp, 8, m_bhp_img[0], FALSE, FALSE);
				if ((*it)->m_damage > 0)
					DrawRectGraph((*it)->m_pos.getX() - 382 + (*it)->m_hp, 0, 0, 0, (*it)->m_damage, 8, m_bhp_img[1], FALSE, FALSE);
			}
		}
		if ((*it)->m_damage > 0){
			(*it)->m_damage--;
		}

	}
}