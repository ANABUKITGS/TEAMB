#include "base_data.h"

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
, m_mass(_mass)
, m_amine_rate(0)
, m_hp(_hp)
, m_friction(_friction)
, m_collision(_collision)
, m_control(true)
, m_type(_type)
, m_timer(0)
, m_damage(0)
, m_invincible(false)
, m_knock_stan(false)
, m_bank_flag(true)
, m_kill_flag(false)
{
	CCharaData::GetInstance()->AddTaskInner(this);
}

CBaseData::CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction, int _type)
: m_pos(_pos)
, m_living(_living)
, m_alpha(_alpha)
, m_rad(_rad)
, m_exrate(_exrate)
, m_animtype(_animtype)
, m_velocity(_velocity)
, m_mass(_mass)
, m_amine_rate(0)
, m_hp(0)
, m_friction(_friction)
, m_collision(0)
, m_control(true)
, m_type(_type)
, m_timer(0)
, m_damage(0)
, m_invincible(false)
, m_knock_stan(false)
, m_bank_flag(true)
, m_kill_flag(false)
{
}

CBaseData::CBaseData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type)
: m_pos(_pos)
, m_living(_living)
, m_alpha(256)
, m_rad(_rad)
, m_exrate(_exrate)
, m_animtype(_animtype)
, m_velocity(_velocity)
, m_mass(_mass)
, m_amine_rate(0)
, m_hp(_hp)
, m_friction(_friction)
, m_collision(_collision)
, m_control(true)
, m_type(_type)
, m_timer(0)
, m_damage(0)
, m_invincible(false)
, m_knock_stan(false)
, m_bank_flag(true)
, m_kill_flag(false)
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
	m_stan_timer_img = LoadGraph("media\\img\\enemy_stan_timer.jpg");
}

void CCharaData::AddTaskInner(CBaseData* task){
	m_chara_data.push_back(task);
}

CCharaData* CCharaData::GetInstance(){
	//CCharaData‚ğˆê“x‚Ì‚İiƒVƒ“ƒOƒ‹ƒgƒ“j¶¬‚µ‚ÄŠi”[
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
		if ((*it1)->m_hp < 1){ (*it1)->m_kill_flag = true; continue; }		//HP‚ª0‚È‚ç¶‚«‚Ä‚¢‚È‚¢
		for (auto it2 = m_chara_data.begin(); it2 != m_chara_data.end(); it2++){
			/*if (_f == false){
				for (int s = 0; s < _suu; s++){
					it2++;
					_f = true;
				}
			}*/
			if ((*it1)->m_pos != (*it2)->m_pos){
				if (IsHitCircle((*it1)->m_collision, (*it2)->m_collision, (*it1)->m_pos, (*it2)->m_pos)){
					if (!(*it1)->m_invincible && !(*it2)->m_invincible){
						if ((*it1)->m_type != ITEM && (*it2)->m_type != ITEM){
							CBank(*it1, *it2);
						}
					}
				}
			}
		}
		_f = false;
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

	////‘€ì•s‰Â”\////
	cd1->m_control = false;
	cd2->m_control = false;

	/////‚ß‚è‚İ–h~/////
	float _vx = cd1->m_pos.getX() - cd2->m_pos.getX();
	float _vy = cd1->m_pos.getY() - cd2->m_pos.getY();

	float _len = sqrt(_vx * _vx + _vy * _vy);

	float _dist = (cd1->m_collision + cd2->m_collision) - _len;

	if (_len > 0)_len = 1 / _len;

	_vx *= _len;
	_vy *= _len;

	_dist /= 2.0f;

	cd1->m_pos += CVector2D(_vx * _dist * 1.2f, _vy*_dist * 1.2f);
	cd2->m_pos -= CVector2D(_vx * _dist * 1.2f, _vy*_dist * 1.2f);
	///////////////////////
	if (cd1->m_bank_flag){
		//”½”­ŒW”
		float _e = 1.0f;
		bool _a = false;
		if (cd2->m_velocity > cd1->m_velocity){
			float temp = cd2->m_velocity;
			cd2->m_velocity = cd1->m_velocity;
			cd1->m_velocity = temp;
			_a = true;
		}

		float _rad1 = PosRad(cd1->m_pos, cd2->m_pos);//Õ“ËŒã‚Ì‘Šè
		float _rad2 = cd1->m_rad - _rad1;	//Šp“x‚Ì·
		float _rad3 = cd1->m_rad + _rad2;	//Õ“ËŒã©•ª‚ÌŠp“x

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
	for (auto it = m_chara_data.begin(); it != m_chara_data.end(); it++){
		if ((*it)->m_type == ENEMY){
			DrawRectGraph((*it)->m_pos.getX() - 32, (*it)->m_pos.getY() - 25, 0, 0, (*it)->m_hp, 4, m_ehp_img[0], FALSE, FALSE);
			if ((*it)->m_damage > 0)
				DrawRectGraph((*it)->m_pos.getX() - 32 + (*it)->m_hp, (*it)->m_pos.getY() - 25, 0, 0, (*it)->m_damage, 4, m_ehp_img[1], FALSE, FALSE);
			if ((*it)->m_timer > 0)
				DrawRectGraph((*it)->m_pos.getX() - 32, (*it)->m_pos.getY() - 21, 0, 0, (*it)->m_timer/15, 2, m_stan_timer_img, FALSE, FALSE);
		}
		if ((*it)->m_type == PLAYER){
			DrawRectGraph((*it)->m_pos.getX() - 32, (*it)->m_pos.getY() - 47, 0, 0, (*it)->m_hp, 8, m_hhp_img[0], FALSE, FALSE);
			if ((*it)->m_damage > 0)
				DrawRectGraph((*it)->m_pos.getX() - 32 + (*it)->m_hp, (*it)->m_pos.getY() - 47, 0, 0, (*it)->m_damage, 8, m_hhp_img[1], FALSE, FALSE);
		}
		if ((*it)->m_damage > 0){
			(*it)->m_damage--;
		}
	}
}