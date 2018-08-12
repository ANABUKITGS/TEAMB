#include "player_manager.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"
#include "item_manager.h"

CStan		stan;
CKnockBack	knock_back;
CBomb		bomb;
CHurricane	hurricane;

CPad		pad;
CKeyBoard	keyboard;

CStanUp			item_stan;
CKnockBackUp	item_knock_back;
CBombUp			item_bomb;
CHeelUp			item_heel;

CPAtable player_attack_table[] = {
	{ 0, &stan },
	{ 1, &hurricane },
	{ 2, &bomb }
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

CItemTable item_table[] = {
	{ STAN_ITEM, &item_stan },
	{ KNOCK_BACK_ITEM, &item_knock_back },
	{ BOMB_ITEM, &item_bomb },
	{ HEEL_ITEM, &item_heel },
};

CPlayerData::CPlayerData()
:CBaseData(CVector2D(0,0),false,0,0,0,0,0,0,0,0)
{

}

CPlayerData::CPlayerData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type)
: CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision,_type)
, m_chage_count(0)
, m_attack_type(0)
, m_stan(1)
, m_knock_back(1)
, m_bomb(1)
{
}

CPlayer::CPlayer()
{
	m_player = new CPlayerData(CVector2D(640, 360), true, 256, 0, PLAYER_EXRATE, 0, PLAYER_SPEED, PLAYER_MASS, PLAYER_HP, PLAYER_FRICTION, PLAYER_COLLISION, PLAYER);
	m_player->m_chage_count = 1.0f;
	m_player->m_control_type = false;
	m_player->ControlType = &pad;
	//LoadDivGraph("media\\img\\hero.png", 24, 6, 4, 75, 150, m_player_img, 0);
	LoadDivGraph("media\\img\\hero_a2a.png", 24, 6, 4, 71, 70, m_player_img, 0);
	LoadDivGraph("media\\img\\charge.png", 10, 2, 5, 384, 384, m_player_charge_img, 0);
	LoadDivGraph("media\\img\\avoid_aria.png", 16, 2, 8, 384, 384, m_player_avoid_img, 0);

	for (auto &pat : player_attack_table){
		if (m_player->m_attack_type == pat.m_type){
			m_player->AttackType = pat.BaseAttackType;
			break;
		}
	}

	m_player->m_charge_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 0.6f, 0, 0, 0, 0, 0, 0, 0);
	m_player->m_avoid_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 0.6f, 0, 0, 0, 0, 0, 0, 0);

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

	Avoid(key);

	ItemGet();

	//チャージエフェクト
	if (m_player->m_charge_effect.m_living == true)
		m_player->m_charge_effect.m_amine_rate++;
	if (m_player->m_charge_effect.m_amine_rate == 10){
		m_player->m_charge_effect.m_living = false;
		m_player->m_charge_effect.m_amine_rate = 0;
	}

	//回避エフェクト
	if (m_player->m_avoid_effect.m_living == true)
		m_player->m_avoid_effect.m_amine_rate++;
	if (m_player->m_avoid_effect.m_amine_rate == 16){
		m_player->m_avoid_effect.m_living = false;
		m_player->m_avoid_effect.m_amine_rate = 0;
	}

}

void CPlayer::Move(int key){

	float _fx = 0, _fy = 0;

	float _hx = m_player->m_pos.getX();
	float _hy = m_player->m_pos.getY();

//#if defined(_DEBUG) | defined(DEBUG)
	if (IsKeyTrigger(key, PAD_INPUT_10, KEY_PAD_INPUT_10)){
		if (m_player->m_control_type == true){
			m_player->ControlType = &keyboard;
			m_player->m_control_type = false;
		}
		else{
			m_player->ControlType = &pad;
			m_player->m_control_type = true;
		}
	}
//#endif

	////動いているかどうか////
	bool _flag = false;

	{
		if (!m_player->m_control){
			_hx += cos(m_player->m_rad) * m_player->m_velocity;
			_hy += sin(m_player->m_rad) * m_player->m_velocity;
			if (m_player->m_velocity > 0){
				m_player->m_velocity -= m_player->m_friction;
			}
			else{
				m_player->m_control = true;
				m_player->m_velocity = PLAYER_SPEED;
				m_player->m_rad = m_player->m_temporary_rad;
			}
		}
		else{

			m_player->Control(key, _fx, _fy);

			_hx += _fx; _hy += _fy;

			float _rad = PosRad(_fx, _fy);

			//アニメーションの決定
			if (_fx == 0 && _fy == 0)_flag = false;
			else{
				for (auto& rt : rad_table){
					//右のアニメーションは分解して最大値と最小値を別々でとること
					if (degree(_rad) > 337.5f){
						m_player->m_animtype = rt.m_type;
						_flag = true;
						break;
					}
					if (degree(_rad) < 22.5f){
						m_player->m_animtype = rt.m_type;
						_flag = true;
						break;
					}

					if (degree(_rad) > rt.m_min_rad && degree(_rad) < rt.m_max_rad){
						m_player->m_animtype = rt.m_type;
						_flag = true;
						break;
					}
				}
				m_player->m_rad = _rad;
			}
		}
		//アニメーション処理
		if (_flag == true)
			m_player->m_amine_rate++;
		else
			m_player->m_amine_rate = 6;
	}

	//マップ当たり判定
	if (_hy < 45 || _hy > 675){
		_hy = m_player->m_pos.getY();
	}
	if (_hx < 20 || _hx > 1260){
		_hx = m_player->m_pos.getX();
	}

	m_player->m_pos = CVector2D(_hx, _hy);

	if(m_player->m_kill_flag)
		m_player->m_living = false;

#if defined(_DEBUG) | defined(DEBUG)


#endif
}

void CPlayer::Change(int key){
	bool _f = false;
	int _direction = 0;
	if (_f = IsKeyTrigger(key, PAD_INPUT_7, KEY_PAD_INPUT_7) == true){
		_direction = -1;
		m_player->m_attack_type--;
	}
	else if (_f = IsKeyTrigger(key, PAD_INPUT_8, KEY_PAD_INPUT_8) == true){
		_direction = 1;
		m_player->m_attack_type++;
	}

	if (m_player->m_attack_type > 2)
		m_player->m_attack_type = 0;
	else if (m_player->m_attack_type < 0)
		m_player->m_attack_type = 2;

	if (_f == true){
		for (auto &pat : player_attack_table){
			if (m_player->m_attack_type == pat.m_type){
				m_player->AttackType = pat.BaseAttackType;
				CUiManager::GetInstance()->GetUiAdress()->SetChangeFlag(_f);
				break;
			}
		}
	}

	//UI//
	CUiManager::GetInstance()->GetUiAdress()->ChengeIcon(_direction);
}

void CPlayer::Attack(int key){
	int _type = 2;
	static int _temp;

	if (m_player->m_control){
		_type = LongPress(key, PAD_INPUT_2);
	}

	if (_type == RELEASE){
			m_player->Action();
			CUiManager::GetInstance()->GetUiAdress()->SetEstimationLivflag(false);
	}
	else if (_type == PRESSING){
		m_player->m_chage_count += 0.019;
		//チャージ中のエフェクト
		if ((int)m_player->m_chage_count != _temp){
			m_player->m_charge_effect.m_living = true;
			_temp = m_player->m_chage_count;
		}
		if (m_player->m_chage_count > 4.0f)
			m_player->m_chage_count = 4.0f;
		if (m_player->m_attack_type == 0)
			CUiManager::GetInstance()->GetUiAdress()->SetEstimationData(&m_player->m_pos, 1.0f * (1 + (int)m_player->m_chage_count * 0.1f) * m_player->m_stan,1);
		CUiManager::GetInstance()->GetUiAdress()->SetEstimationLivflag(true);
	}
	else if (_type == SEPARATE){
		_temp = m_player->m_chage_count;
		m_player->m_chage_count = 1.0f;
	}
}

void CPlayer::Avoid(int key){
	if (m_player->m_control){
		if (!m_player->m_avoid_effect.m_living){
			if (IsKeyTrigger(key, PAD_INPUT_3, KEY_PAD_INPUT_3)){
				m_player->m_invincible = true;
				m_player->m_velocity = 19.0f;
				m_player->m_timer = 10;
				m_player->m_avoid_effect.m_living = true;
				m_player->m_avoid_effect.m_pos = m_player->m_pos;
			}
		}
		if (m_player->m_invincible == true){

			//回避時の分身生成
			if (m_player->m_timer % 2 == 0){
				for (int i = 3; i > 0; i--){
					m_p_avatar[i] = m_p_avatar[i - 1];
				}
				m_p_avatar[0] = *m_player;
				m_p_avatar[0].m_timer = 9;
			}

			if (m_player->m_timer > 0){
				m_player->m_timer--;
				m_player->m_velocity -= 0.5f;
			}
			else{
				m_player->m_velocity = PLAYER_SPEED;
				m_player->m_invincible = false;
			}
		}
	}

	//分身の削除
	if (m_p_avatar[0].m_timer != 0){
		for (int i = 0; i < 4; i++){
			m_p_avatar[i].m_timer--;
			if (m_p_avatar[i].m_timer == 0){
				m_p_avatar[i].m_living = false;
				m_p_avatar[i].m_pos = CVector2D(-99, -99);
			}
		}
	}

}

void CPlayer::ItemGet(){
	for (auto it = CItemManager::GetInstance()->GetItemAdress()->GetItemData()->begin(); it != CItemManager::GetInstance()->GetItemAdress()->GetItemData()->end(); it++){
		if (IsHitCircle(m_player->m_collision, (*it)->m_collision, m_player->m_pos, (*it)->m_pos)){
			(*it)->m_living = false;
			for (auto &item_type : item_table){
				if ((*it)->m_animtype == item_type.m_i_type){
					m_player->ItemType = item_type.ItemType;
					break;
				}
			}
			m_player->ItemAction();
		}
	}
}

void CPlayer::Draw(){

	//チャージエフェクト
	if(m_player->m_charge_effect.m_living)
		DrawRotaGraph(m_player->m_pos.getX()-2, m_player->m_pos.getY()+27, m_player->m_charge_effect.m_exrate,
		0, m_player_charge_img[m_player->m_charge_effect.m_amine_rate], TRUE, FALSE);
	
	//回避エフェクト
	if (m_player->m_avoid_effect.m_living)
		DrawRotaGraph(m_player->m_avoid_effect.m_pos.getX() - 2, m_player->m_avoid_effect.m_pos.getY() + 27, m_player->m_avoid_effect.m_exrate,
		0, m_player_avoid_img[m_player->m_avoid_effect.m_amine_rate], TRUE, FALSE);

	//分身
	if (m_p_avatar[0].m_living == true){
		SetDrawBright(0, 0, 255);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		for (int i = 0; i < 4; i++){
			DrawRotaGraph(m_p_avatar[i].m_pos.getX(), m_p_avatar[i].m_pos.getY(), m_p_avatar[i].m_exrate,
				0, m_player_img[m_p_avatar[i].m_animtype + m_p_avatar[i].m_amine_rate / 6 % 3], TRUE, FALSE);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//プレイヤー
	DrawRotaGraph(m_player->m_pos.getX(), m_player->m_pos.getY(), m_player->m_exrate,
		0, m_player_img[m_player->m_animtype + m_player->m_amine_rate / 6 % 3], TRUE, FALSE);

#if defined(_DEBUG) | defined(DEBUG)
	int color_white = GetColor(255, 255, 255);//色取得
	DrawFormatString(20, 520, color_white, "move_pos( %.1f , %.1f )", m_player->m_pos.getX(), m_player->m_pos.getY());
	DrawFormatString(20, 500, color_white, "P_degree %.1f", degree(m_player->m_rad));
	DrawFormatString(20, 540, color_white, "P_c_c %.1f", m_player->m_chage_count);
	DrawFormatString(20, 560, color_white, "Pat %d", m_player->m_attack_type);
#endif
}

void CPlayer::Kill(){
	delete m_player;
}