#include "player_manager.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"
#include "item_manager.h"
#include "change_manager.h"
#include "sounddata_manager.h"
#include "difficulty_level_manager.h"

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
	{ STAN_ITEM, STN_UP_NUM, STN_UP, &item_stan },
	{ KNOCK_BACK_ITEM, WIN_UP_NUM, WIN_UP, &item_knock_back },
	{ BOMB_ITEM, EXP_UP_NUM, EXP_UP, &item_bomb },
	{ HEEL_ITEM, PLAYER_HEEL_NUM, P_HEEL, &item_heel },
};

CAttackRange::CAttackRange(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type)
: CBaseData(_pos,_living,_rad,_exrate,_animtype,_velocity,_mass,_hp,_friction,_collision,_type)
, m_move_pos(_pos)
, m_move_rad(0)
{

}

CPlayerData::CPlayerData()
:CBaseData(CVector2D(0,0),false,0,0,0,0,0,0,0,0,0)
{

}

CPlayerData::CPlayerData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type)
: CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision,_type)
, m_chage_count(0)
, m_attack_type(0)
, m_stan(1)
, m_knock_back(1)
, m_bomb(1)
, m_attack_anim(0)
{
}

CPlayer::CPlayer()
{
	m_player = new CPlayerData(CVector2D(640, 360), true, 256, 0, PLAYER_EXRATE, 0, PLAYER_SPEED, PLAYER_MASS, PLAYER_HP, PLAYER_FRICTION, PLAYER_COLLISION, PLAYER);
	m_player->m_chage_count = 1.0f;
	m_player->m_control_type = false;
	m_player->ControlType = &pad;
	m_player->m_anim_division = 6;
	m_player->m_motion_type = 0;

	LoadDivGraph("media\\img\\hero_m.png", 64, 4, 16, 64, 64, m_player_img, 0);
	LoadDivGraph("media\\img\\charge.png", 10, 2, 5, 384, 384, m_player_charge_img, 0);
	LoadDivGraph("media\\img\\avoid_aria.png", 20, 2, 10, 256, 256, m_player_avoid_img, 0);
	LoadDivGraph("media\\img\\gate.png", 16, 4, 4, 256, 256, m_player_gate_img, 0);
	
	m_player_range_img[0][0] = LoadGraph("media\\img\\range_stn_i_ma.png");
	m_player_range_img[0][1] = LoadGraph("media\\img\\range_stn_o_ma.png");
	m_player_range_img[1][0] = LoadGraph("media\\img\\range_wind_i_ma.png");
	m_player_range_img[1][1] = LoadGraph("media\\img\\range_wind_o_ma.png");
	m_player_range_img[2][0] = LoadGraph("media\\img\\range_exp_i_ma.png");
	m_player_range_img[2][1] = LoadGraph("media\\img\\range_exp_o_ma.png");

	for (auto &pat : player_attack_table){
		if (m_player->m_attack_type == pat.m_type){
			m_player->AttackType = pat.BaseAttackType;
			break;
		}
	}

	m_player->m_charge_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 0.6f, 0, 0, 0, 0, 0, 0, 0);
	m_player->m_avoid_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 0.9f, 0, 0, 0, 0, 0, 0, 0);
	m_player->m_gate_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 1.0f, 0, 0, 0, 0, 0, 0, 0);
	m_player->m_attack_range = CAttackRange(m_player->m_pos, false, m_player->m_rad, 1.0f, 0, 0, 0, 0, 0, 0, 0);
	m_player->m_change_effect = CBaseData(m_player->m_pos, false, m_player->m_rad, 0.3f, 0, 0, 0, 0, 0, 0, 0);

	for (int i = 0; i < 3; i++)
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(i)->m_hp = 1;

	m_timer = 0.0f;
	m_teleport_flag = false;
	m_t_cont = false;
	m_attack_state = 2;
	m_item_get = false;
	m_priority = eDWP_PLAYER;
	m_update_priority = 2;
	m_draw_priority = 2;
	m_update = true;

	i = 0;

	CPlayerManager::GetInstance()->Init(this);
}

void CPlayer::Update(){
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_3, KEY_PAD_INPUT_3)){
		m_player->m_stan += ITEM_STAN_UP;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp++;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_exrate = 1.3f;
	}

	if (!m_t_cont)
		Attack(key);
	
	Move(key);

	if (!m_t_cont)
		Change(key);

	if (!m_t_cont)
		Avoid(key);

	ItemGet();

	if (!CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialFlag())
		m_teleport_flag = Teleport(key);

	AttackRangeMove();

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
	if (m_player->m_avoid_effect.m_amine_rate == 20){
		m_player->m_avoid_effect.m_living = false;
		m_player->m_avoid_effect.m_amine_rate = 0;
	}

	//ゲートエフェクト
	if (m_player->m_gate_effect.m_living == true)
		m_player->m_gate_effect.m_amine_rate++;
	if (m_player->m_gate_effect.m_amine_rate == 80){
		m_player->m_gate_effect.m_amine_rate = 0;
	}

	//攻撃時の範囲エフェクト
	if (m_player->m_attack_range.m_living == true){
		m_player->m_attack_range.m_rad += 0.007;
	}

	//切り替え時のエフェクト
	if (m_player->m_change_effect.m_living == true){
		m_player->m_change_effect.m_pos = m_player->m_pos;
		m_player->m_change_effect.m_rad += 0.03;
		m_player->m_change_effect.m_exrate += 0.009f;
		if (m_player->m_change_effect.m_exrate > 0.2f){
			m_player->m_change_effect.m_alpha -= 17;
		}
		if (m_player->m_change_effect.m_exrate > 0.32f){
			m_player->m_change_effect.m_living = false;
		}
	}
}

void CPlayer::Move(int key){

	//m_player->m_hp = 64;

	float _fx = 0, _fy = 0;

	float _hx = m_player->m_pos.getX();
	float _hy = m_player->m_pos.getY();

//#if defined(_DEBUG) | defined(DEBUG)
	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_10, KEY_PAD_INPUT_10)){
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

			m_player->m_temporary_rad = m_player->m_rad;

			if (!m_t_cont)
				m_player->Control(key, _fx, _fy);

			_hx += _fx; _hy += _fy;

			float _rad = PosRad(_fx, _fy);

			//アニメーションの決定
			if (_fx == 0 && _fy == 0)_flag = false;
			else{
				for (auto& rt : rad_table){
					//右のアニメーションは分解して最大値と最小値を別々でとること
					if (degree(_rad) > 337.5f){
						m_player->m_direction_type = rt.m_type;
						_flag = true;
						break;
					}
					if (degree(_rad) < 22.5f){
						m_player->m_direction_type = rt.m_type;
						_flag = true;
						break;
					}

					if (degree(_rad) > rt.m_min_rad && degree(_rad) < rt.m_max_rad){
						m_player->m_direction_type = rt.m_type;
						_flag = true;
						break;
					}
				}
				m_player->m_rad = _rad;
			}
		}
		//アニメーション処理
		if (_flag == true){
			m_player->m_motion_type = 0;
			m_player->m_amine_rate++;
		}
		else{
			if (m_player->m_anim_division == 8){//攻撃アクション
				m_player->m_amine_rate++;
				if (m_player->m_amine_rate > 23){
					m_player->m_motion_type = 0;
					m_player->m_anim_division = 6;
					m_player->m_amine_rate = 0;
				}
			}
			else{
				if (m_player->m_motion_type == 32)
					m_player->m_amine_rate = 0;//一段階で止める
				else
					m_player->m_amine_rate = 6;
			}
		}
	}

	//マップ当たり判定
	if (_hy < 83 || _hy >  615){
		_hy = m_player->m_pos.getY();
	}
	if (_hx < 64 || _hx > 1216){
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
	if (_f = CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_7, KEY_PAD_INPUT_7) == true){
		_direction = 1;
		m_player->m_attack_type++;
	}
	else if (_f = CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_8, KEY_PAD_INPUT_8) == true){
		_direction = -1;
		m_player->m_attack_type--;
	}

	if (m_player->m_attack_type > 2)
		m_player->m_attack_type = 0;
	else if (m_player->m_attack_type < 0)
		m_player->m_attack_type = 2;

	if (_f == true){
		for (auto &pat : player_attack_table){
			if (m_player->m_attack_type == pat.m_type){
				m_player->m_change_effect.m_pos = m_player->m_pos;
				m_player->m_change_effect.m_animtype = pat.m_type;
				m_player->m_change_effect.m_exrate = 0;
				m_player->m_change_effect.m_living = true;
				m_player->m_change_effect.m_alpha = 255;

				m_player->AttackType = pat.BaseAttackType;
				CUiManager::GetInstance()->GetUiAdress()->SetChangeFlag(_f);
				PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_CHANGE), DX_PLAYTYPE_BACK);
				break;
			}
		}
	}

	//UI//
	CUiManager::GetInstance()->GetUiAdress()->ChengeIcon(_direction);
}

void CPlayer::Attack(int key){
	m_attack_state = 2;
	static int _temp;

	if (m_player->m_control){
		m_attack_state = CKeyData::GetInstance()->LongPress(key, PAD_INPUT_2, KEY_Z_PAD_INPUT_2);
	}

	if (m_attack_state == RELEASE){
		m_player->m_anim_division = 8;
		m_player->m_amine_rate = 0;
		m_player->Action();
		PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(rand() % 3 + 15), DX_PLAYTYPE_BACK);
	}
	else if (m_attack_state == PRESSING){
		m_player->m_chage_count += 0.019;
		//チャージ中のエフェクト
		if ((int)m_player->m_chage_count != _temp){
			m_player->m_charge_effect.m_living = true;
			_temp = m_player->m_chage_count;
		}
		if (m_player->m_chage_count > 4.0f)
			m_player->m_chage_count = 4.0f;

		switch (m_player->m_attack_type)
		{
		case 0:
			m_player->m_attack_range.m_move_pos = m_player->m_pos;
			if (m_player->m_stan - 1.0f > ITEM_STAN_UP * 9.0f)
				m_player->m_attack_range.m_exrate = 0.45f * (1 + (int)m_player->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * 9.0f);
			else
				m_player->m_attack_range.m_exrate = 0.45f * (1 + (int)m_player->m_chage_count * 0.1f) * m_player->m_stan;
			m_player->m_attack_range.m_animtype = 0;
			break;
		case 1:
			m_player->m_attack_range.m_move_pos = CVector2D(m_player->m_pos.getX() + PLAYER_HURRICANE_RANGE * cos(m_player->m_rad), m_player->m_pos.getY() + PLAYER_HURRICANE_RANGE * sin(m_player->m_rad));
			if (m_player->m_knock_back - 1.0f > ITEM_KNOCK_BACK_UP * 9.0f)
				m_player->m_attack_range.m_exrate = 0.60f * (1 + (int)m_player->m_chage_count * 0.1f) * (1.0f + ITEM_KNOCK_BACK_UP * 9.0f);
			else
				m_player->m_attack_range.m_exrate = 0.60f * (1 + (int)m_player->m_chage_count * 0.1f) * m_player->m_knock_back;
			m_player->m_attack_range.m_animtype = 1;
			break;
		case 2:
			m_player->m_attack_range.m_move_pos = CVector2D(m_player->m_pos.getX() + PLAYER_BOMB_RANGE * cos(m_player->m_rad), m_player->m_pos.getY() + PLAYER_BOMB_RANGE * sin(m_player->m_rad));
			if (m_player->m_bomb - 1.0f > ITEM_BOMB_UP * 9.0f)
				m_player->m_attack_range.m_exrate = PLAYER_BOMB_RANGE_EXRATE * (1 + (int)m_player->m_chage_count * 0.1f) * (1.0f+ITEM_BOMB_UP * 9.0f);
			else
				m_player->m_attack_range.m_exrate = PLAYER_BOMB_RANGE_EXRATE * (1 + (int)m_player->m_chage_count * 0.1f) * m_player->m_bomb;
			m_player->m_attack_range.m_animtype = 2;
			break;
		default:
			break;
		}
		m_player->m_attack_range.m_living = true;
		
		m_player->m_motion_type = 32;
	}
	else if (m_attack_state == SEPARATE){
		_temp = m_player->m_chage_count;
		m_player->m_chage_count = 1.0f;
		m_player->m_attack_range.m_living = false;
	}
}

bool CPlayer::Teleport(int key){
	int _type = 2;
	if (m_player->m_control){
		_type = CKeyData::GetInstance()->LongPress2(key, PAD_INPUT_1, KEY_PAD_INPUT_1);
	}
	if (_type == PRESSING){
		m_timer += 0.019;
		m_player->m_gate_effect.m_living = true;
		m_player->m_gate_effect.m_pos = m_player->m_pos;
		m_player->m_motion_type = 35;
		m_player->m_amine_rate = 0;
		if (m_timer > 3.0f){
			m_timer = 0.0f;
			m_player->m_gate_effect.m_living = false;
			return true;
		}
		m_t_cont = true;
	}
	else if (_type == SEPARATE){
		m_timer = 0.0f;
		m_player->m_gate_effect.m_living = false;
		m_t_cont = false;
		//m_player->m_motion_type = 0;
		return false;
	}
	return false;
}

void CPlayer::Avoid(int key){
	if (m_player->m_control){
		if (!m_player->m_avoid_effect.m_living){
			if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_3, KEY_PAD_INPUT_3)){
				m_player->m_invincible = 1;
				m_player->m_velocity = 19.0f;
				m_player->m_timer = 10;
				m_player->m_avoid_effect.m_living = true;
				m_player->m_avoid_effect.m_pos = m_player->m_pos;
				PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(rand() % 2+20), DX_PLAYTYPE_BACK);
				PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_P_AVOID), DX_PLAYTYPE_BACK);
			}
		}
		if (m_player->m_invincible == 1){

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
				m_player->m_invincible = 0;
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

void CPlayer::AttackRangeMove(){
	if (m_player->m_attack_range.m_living){
		if (m_player->m_attack_range.m_pos.getX() < m_player->m_attack_range.m_move_pos.getX() + 15 && m_player->m_attack_range.m_pos.getX() > m_player->m_attack_range.m_move_pos.getX() - 15 &&
			m_player->m_attack_range.m_pos.getY() < m_player->m_attack_range.m_move_pos.getY() + 15 && m_player->m_attack_range.m_pos.getY() > m_player->m_attack_range.m_move_pos.getY() - 15){
			m_player->m_attack_range.m_pos = m_player->m_attack_range.m_move_pos;
		}
		else{
			m_player->m_attack_range.m_move_rad = PosRad(m_player->m_attack_range.m_pos, m_player->m_attack_range.m_move_pos);
			m_player->m_attack_range.m_pos += CVector2D(cos(m_player->m_attack_range.m_move_rad) * 11, sin(m_player->m_attack_range.m_move_rad) * 11);
		}
	}
	else{
		m_player->m_attack_range.m_pos = m_player->m_pos;
	}
}

void CPlayer::ItemGet(){
	for (auto it = CItemManager::GetInstance()->GetItemAdress()->GetItemData()->begin(); it != CItemManager::GetInstance()->GetItemAdress()->GetItemData()->end(); it++){
		if (IsHitCircle(m_player->m_collision, (*it)->m_collision, m_player->m_pos, (*it)->m_pos)){
			(*it)->m_living = false;
			m_item_get = true;
			for (auto &item_type : item_table){
				if ((*it)->m_animtype == item_type.m_i_type){
					m_player->ItemType = item_type.ItemType;
					CEffectData *temp = new CEffectData(m_player->m_pos, true, 0, 1.9f, item_type.m_num, 0, 0, 0, 0, 0, item_type.m_type, 2, NULL);
					CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
					PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(22), DX_PLAYTYPE_BACK);
					if ((*it)->m_animtype != HEEL_ITEM){
						PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ITEM_GET), DX_PLAYTYPE_BACK);
					}
					else{
						PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_HEEL_GET), DX_PLAYTYPE_BACK);
					}
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
		DrawRotaGraph(m_player->m_avoid_effect.m_pos.getX() - 2, m_player->m_avoid_effect.m_pos.getY()-27, m_player->m_avoid_effect.m_exrate,
		0, m_player_avoid_img[m_player->m_avoid_effect.m_amine_rate], TRUE, FALSE);

	//ゲートエフェクト
	if (m_player->m_gate_effect.m_living)
		DrawRotaGraph(m_player->m_gate_effect.m_pos.getX(), m_player->m_gate_effect.m_pos.getY() - 29, m_player->m_gate_effect.m_exrate,
		0, m_player_gate_img[m_player->m_gate_effect.m_amine_rate / 5], TRUE, FALSE);

	//攻撃範囲のエフェクト
	if (m_player->m_attack_range.m_living){
		DrawRotaGraph(m_player->m_attack_range.m_pos.getX() + 1, m_player->m_attack_range.m_pos.getY() + 1, m_player->m_attack_range.m_exrate,
			m_player->m_attack_range.m_rad, m_player_range_img[m_player->m_attack_range.m_animtype][0], TRUE, FALSE);
		DrawRotaGraph(m_player->m_attack_range.m_pos.getX() + 1, m_player->m_attack_range.m_pos.getY() + 1, m_player->m_attack_range.m_exrate,
			-m_player->m_attack_range.m_rad, m_player_range_img[m_player->m_attack_range.m_animtype][1], TRUE, FALSE);
	}

	if (m_player->m_change_effect.m_living){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_player->m_change_effect.m_alpha);
		DrawRotaGraph(m_player->m_change_effect.m_pos.getX() + 1, m_player->m_change_effect.m_pos.getY() + 1, m_player->m_change_effect.m_exrate,
			m_player->m_change_effect.m_rad, m_player_range_img[m_player->m_change_effect.m_animtype][0], TRUE, FALSE);
		DrawRotaGraph(m_player->m_change_effect.m_pos.getX() + 1, m_player->m_change_effect.m_pos.getY() + 1, m_player->m_change_effect.m_exrate,
			-m_player->m_change_effect.m_rad, m_player_range_img[m_player->m_change_effect.m_animtype][1], TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	//分身
	if (m_p_avatar[0].m_living == true){
		SetDrawBright(0, 0, 255);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		for (int i = 0; i < 4; i++){
			DrawRotaGraph(m_p_avatar[i].m_pos.getX(), m_p_avatar[i].m_pos.getY(), m_p_avatar[i].m_exrate,
				0, m_player_img[m_p_avatar[i].m_direction_type + m_p_avatar[i].m_amine_rate / 6 % 3], TRUE, FALSE);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//プレイヤー
	DrawRotaGraph(m_player->m_pos.getX(), m_player->m_pos.getY(), m_player->m_exrate,
		0, m_player_img[m_player->m_direction_type + m_player->m_motion_type + m_player->m_amine_rate / m_player->m_anim_division % 3], TRUE, FALSE);

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