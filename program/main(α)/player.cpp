#include "player_manager.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"

CStan		stan;
CKnockBack	knock_back;
CBomb		bomb;

CPAtable player_attack_table[] = {
	{0,&stan},
	{1,&knock_back},
	{2,&bomb}
};

CRadTable rad_table[] = {
	{ 0,22.5f,337.5f, PLAYER_RIGHT },
	{ 45,67.5f,22.5f, PLAYER_DR },
	{ 90,112.5f,67.5f, PLAYER_DOWN },
	{ 135,157.5f,112.5f, PLAYER_DL },
	{ 180,202.5f,157.5f, PLAYER_LEFT },
	{ 225,247.5f,202.5f, PLAYER_UL },
	{ 270,292.5f,247.5f, PLAYER_UP },
	{ 315,337.5f,292.5f, PLAYER_UR }
};

CPlayerData::CPlayerData()
:CBaseData()
{

}

CPlayerData::CPlayerData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type)
: CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision,_type)
, m_chage_count(0)
, m_attack_type(0)
{
}

CPlayer::CPlayer()
{
	m_player = new CPlayerData(CVector2D(640, 360), true, 256, 0, PLAYER_EXRATE, 0, PLAYER_SPEED, PLAYER_MASS, PLAYER_HP, PLAYER_FRICTION, PLAYER_COLLISION, PLAYER);
	m_player->m_chage_count = 1.0f;
	//LoadDivGraph("media\\img\\hero.png", 24, 6, 4, 75, 150, m_player_img, 0);
	LoadDivGraph("media\\img\\hero_a2a.png", 24, 6, 4, 71, 70, m_player_img, 0);
	LoadDivGraph("media\\img\\charge.png", 10, 2, 5, 384, 384, m_player_charge_img, 0);

	for (auto &pat : player_attack_table){
		if (m_player->m_attack_type == pat.m_type){
			m_player->AttackType = pat.BaseAttackType;
			break;
		}
	}

	m_player->m_charge_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 0.6f, 0, 0, 0, 0, 0, 0, 0);

	m_priority = eDWP_PLAYER;
	m_update_priority = 2;
	m_draw_priority = 2;

	CPlayerManager::GetInstance()->Init(this);
}

void CPlayer::Update(){
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	Move(key);

	Change(key);

	Attack(key);

}

void CPlayer::Move(int key){

	float _hx = m_player->m_pos.getX();
	float _hy = m_player->m_pos.getY();

	////動いているかどうか////
	bool _flag = false;

	////パッド用////
	{
		if (m_player->m_control == false){
			_hx += cos(m_player->m_rad) * m_player->m_velocity;
			_hy += sin(m_player->m_rad) * m_player->m_velocity;
			if (m_player->m_velocity > 0){
				m_player->m_velocity -= m_player->m_mass;
			}
			else{
				m_player->m_control = true;
				m_player->m_velocity = PLAYER_SPEED;
			}
		}
		else{

			float _fx = 0, _fy = 0;

			////スティックの座標受け取り用////
			int _sx = 0, _sy = 0;

			GetJoypadAnalogInput(&_sx, &_sy, DX_INPUT_PAD1);

			if (_sx == 0 && _sy == 0)_flag = false;
			else{
				_fx = _sx;	_fy = _sy;

				MyVec2Normalize(_fx, _fy, _fx, _fy);

				_fx = _fx * m_player->m_velocity;
				_fy = _fy * m_player->m_velocity;

				_hx += _fx;
				_hy += _fy;

				//角度の算出
				float _f = PosRad(_fx, _fy);

				//アニメーションの決定
				for (auto& rt : rad_table){
					//右のアニメーションは分解して最大値と最小値を別々でとること
					if (degree(_f) > 337.5f){
						m_player->m_animtype = rt.m_type;
						_flag = true;
						break;
					}
					if (degree(_f) < 22.5f){
						m_player->m_animtype = rt.m_type;
						_flag = true;
						break;
					}

					if (degree(_f) > rt.m_min_rad && degree(_f) < rt.m_max_rad){
						m_player->m_animtype = rt.m_type;
						_flag = true;
						break;
					}
				}
				m_player->m_rad = _f;
			}
#if defined(_DEBUG) | defined(DEBUG)
			//printfDx(" %f , %f \n", _fx, _fy);
			//printfDx("角度1 %f \n", degree(m_player->m_rad));

			//to do 角度によって画像の変更を行う
			/*if (key & PAD_INPUT_DOWN){
				_hy += m_player->m_velocity;
				m_player->m_rad = radian(90);
			}
			if (key & PAD_INPUT_LEFT){
				_hx -= m_player->m_velocity;
				m_player->m_rad = radian(180);
			}
			if (key & PAD_INPUT_RIGHT){
				_hx += m_player->m_velocity;
				m_player->m_rad = radian(0);
			}
			if (key & PAD_INPUT_UP){
				_hy -= m_player->m_velocity;
				m_player->m_rad = radian(270);
			}*/

#endif
		}
		//アニメーション処理
		if (_flag == true)
			m_player->m_amine_rate++;
		else
			m_player->m_amine_rate = 6;
	}

	if (m_player->m_charge_effect.m_living == true)
		m_player->m_charge_effect.m_amine_rate++;
	if (m_player->m_charge_effect.m_amine_rate == 10){
		m_player->m_charge_effect.m_living = false;
		m_player->m_charge_effect.m_amine_rate = 0;
	}

#if defined(_DEBUG) | defined(DEBUG)


#endif

	//マップ当たり判定
	if (_hy < 45 || _hy > 675){
		_hy = m_player->m_pos.getY();
	}
	if (_hx < 20 || _hx > 1260){
		_hx = m_player->m_pos.getX();
	}

	m_player->m_pos = CVector2D(_hx, _hy);

#if defined(_DEBUG) | defined(DEBUG)

#endif
}

void CPlayer::Change(int key){
	bool _f = false;
	if (_f = IsKeyTrigger(key, PAD_INPUT_5, KEY_PAD_INPUT_5) == true)
		m_player->m_attack_type--;
	else if (_f = IsKeyTrigger(key, PAD_INPUT_6, KEY_PAD_INPUT_6) == true)
		m_player->m_attack_type++;

	if (m_player->m_attack_type > 2)
		m_player->m_attack_type = 0;
	else if (m_player->m_attack_type < 0)
		m_player->m_attack_type = 2;

	if (_f == true){
		for (auto &pat : player_attack_table){
			if (m_player->m_attack_type == pat.m_type){
				m_player->AttackType = pat.BaseAttackType;
				break;
			}
		}
	}

	//UI//
	CUiManager::GetInstance()->GetUiAdress()->ChengeIcon(m_player->m_attack_type);
}

void CPlayer::Attack(int key){
	int _type = LongPress(key, PAD_INPUT_1);
	int static _temp;
	if (_type == RELEASE){
		m_player->Action();
	}
	else if (_type == PRESSING){
		m_player->m_chage_count += 0.019;
		if ((int)m_player->m_chage_count != _temp){
			m_player->m_charge_effect.m_living = true;
			_temp = m_player->m_chage_count;
		}
		if (m_player->m_chage_count > 4.0f)
			m_player->m_chage_count = 4.0f;
	}
	else if (_type == SEPARATE){
		_temp = m_player->m_chage_count;
		m_player->m_chage_count = 1.0f;
	}
}

void CPlayer::Draw(){

	if(m_player->m_charge_effect.m_living)
		DrawRotaGraph(m_player->m_pos.getX()-2, m_player->m_pos.getY()+27, m_player->m_charge_effect.m_exrate,
		0, m_player_charge_img[m_player->m_charge_effect.m_amine_rate], TRUE, FALSE);

	DrawRotaGraph(m_player->m_pos.getX(), m_player->m_pos.getY(), m_player->m_exrate,
		0, m_player_img[m_player->m_animtype + m_player->m_amine_rate / 6 % 3], TRUE, FALSE);

#if defined(_DEBUG) | defined(DEBUG)
	int color_white = GetColor(255, 255, 255);//色取得
	DrawFormatString(20, 520, color_white, "move_pos( %.1f , %.1f )", m_player->m_pos.getX(), m_player->m_pos.getY());
	DrawFormatString(20, 500, color_white, "P_degree %.1f", degree(m_player->m_rad));
	DrawFormatString(20, 540, color_white, "P_c_c %.1f", m_player->m_chage_count);
	DrawFormatString(20, 560, color_white, "Pat %d", m_player->m_attack_type);
	Fps();
#endif
}