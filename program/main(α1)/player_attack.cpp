#include "player_manager.h"
#include "effect_manager.h"
#include "enemy_manager.h"
#include "ui_manager.h"
#include "sounddata_manager.h"

CEffectMovePattern1 EMP1;
CEffectMovePattern5 EMP5;

void CStan::Type(CPlayerData *cd){
	float _stan_collision = 0;
	float _stan_exrate = 0;
	if (cd->m_stan - 1.0f > ITEM_STAN_UP * MAX_LV){
		_stan_collision = PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * MAX_LV);
		_stan_exrate = PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * MAX_LV);
	}
	else{
		_stan_collision = PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * cd->m_stan;
		_stan_exrate = PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f) * cd->m_stan;
	}
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), true, 0, _stan_exrate, STAN_NUM, 0, 10, 99, 0, _stan_collision, STAN, 1, NULL);
	for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
		it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
		if (cd->m_pos != (*it)->m_pos){
			if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), (*it)->m_pos)){
				(*it)->m_control = false;
				(*it)->m_timer = PLAYER_ATTACK_STAN * ((int)cd->m_chage_count * cd->m_stan);
				(*it)->m_motion_type = 40;
			}
		}
	}
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_STAN), DX_PLAYTYPE_BACK);
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CKnockBack::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), 1.0f * cd->m_knock_back, KNOCK_BACK_NUM, 0, 10, 99, 0, PLAYER_KNOCK_BACK_COLLISION * cd->m_knock_back, KNOCK_BACK, 1, NULL);
	for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
		it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
		if (cd->m_pos != (*it)->m_pos){
			if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad),
				cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), (*it)->m_pos)){
				(*it)->m_rad = cd->m_rad;
				(*it)->m_velocity = PLAYER_ATTACK_KNOCK_BACK * (int)cd->m_chage_count * (*it)->m_mass * cd->m_knock_back;
				(*it)->m_control = false;
				(*it)->m_knock_stan = true;
			}
		}
	}
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CHurricane::Type(CPlayerData *cd){
	float _cyclone_collision = 0;
	float _cyclone_exrate = 0;
	if (cd->m_knock_back - 1.0f > ITEM_KNOCK_BACK_UP * MAX_LV){
		_cyclone_collision = PLAYER_HURRICANE_COLLISION * (1 + ITEM_KNOCK_BACK_UP * MAX_LV);
		_cyclone_exrate = 0.8f * (1 + (int)cd->m_chage_count * 0.1f) * (1 + ITEM_KNOCK_BACK_UP * MAX_LV);
	}
	else{
		_cyclone_collision = PLAYER_HURRICANE_COLLISION * cd->m_knock_back;
		_cyclone_exrate = 0.8f * (1 + (int)cd->m_chage_count * 0.1f) * cd->m_knock_back;
	}
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_WIND), DX_PLAYTYPE_BACK);
	CEffectData *temp = new CEffectData(CVector2D(cd->m_attack_range.m_pos.getX(), cd->m_attack_range.m_pos.getY()), true, cd->m_rad + radian(90), _cyclone_exrate, KNOCK_BACK_NUM, PLAYER_HURRICANE_KNOCK_BACK + 3.5f * cd->m_knock_back, 10, 99, 0, _cyclone_collision, KNOCK_BACK, 3, &EMP5);
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CBomb::Type(CPlayerData *cd){
	float _bomb_collision = 0;
	float _bomb_exrate = 0;
	if (cd->m_bomb - 1.0f > ITEM_BOMB_UP * MAX_LV){
		_bomb_collision = PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_BOMB_UP * MAX_LV);
		_bomb_exrate = (PLAYER_BOMB_EXRATE + 0.1) * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_BOMB_UP * MAX_LV);
	}
	else{
		_bomb_collision = PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * cd->m_bomb;
		_bomb_exrate = PLAYER_BOMB_EXRATE * (1 + (int)cd->m_chage_count * 0.1f) * cd->m_bomb;
	}
	CEffectData *temp = new CEffectData(CVector2D(cd->m_attack_range.m_pos.getX(), cd->m_attack_range.m_pos.getY()), true, cd->m_rad + radian(90), _bomb_exrate, BOMB_CHARGE_NUM, 0, (int)cd->m_chage_count * cd->m_bomb, 0, 0, _bomb_collision, CHARGE_BOMB, 4, &EMP1);
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}


void CPad::Type(CPlayerData *cd, int key, float &_fx, float &_fy){

	////スティックの座標受け取り用////
	int _sx = 0, _sy = 0;
	GetJoypadAnalogInput(&_sx, &_sy, DX_INPUT_PAD1);

	if (_sx != 0 || _sy != 0)
	{
		_fx = _sx;	_fy = _sy;

		MyVec2Normalize(_fx, _fy, _fx, _fy);

		_fx = _fx * cd->m_speed;
		_fy = _fy * cd->m_speed;
	}
}

void CKeyBoard::Type(CPlayerData *cd, int key, float &_fx, float &_fy){
	//to do 角度によって画像の変更を行う
	if (key & PAD_INPUT_DOWN){
		_fy += cd->m_speed;
	}
	if (key & PAD_INPUT_LEFT){
		_fx -= cd->m_speed;
	}
	if (key & PAD_INPUT_RIGHT){
		_fx += cd->m_speed;
	}
	if (key & PAD_INPUT_UP){
		_fy -= cd->m_speed;
	}
}

void CStanUp::Type(CPlayerData *cd){
	cd->m_stan += ITEM_STAN_UP;
	if (CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp < (int)MAX_LV)
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp++;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_exrate = 1.3f;
}

void CKnockBackUp::Type(CPlayerData *cd){
	cd->m_knock_back += ITEM_KNOCK_BACK_UP;
	if (CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp < (int)MAX_LV)
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp++;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_exrate = 1.3f;
}

void CBombUp::Type(CPlayerData *cd){
	cd->m_bomb += ITEM_BOMB_UP;
	if (CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp < (int)MAX_LV)
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp++;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_exrate = 1.3f;
}

void CHeelUp::Type(CPlayerData *cd){
	if (cd->m_hp < 64)
		cd->m_hp += ITEM_HEEL_UP;
}

void CMystery::Type(CPlayerData *cd){
	int _type = rand() % 15;
	float _bomb_collision = 0;
	float _bomb_exrate = 0;
	float _stan_collision = 0;
	float _stan_exrate = 0;
	//int _type = 0;//rand() % 2;
	switch (_type)
	{
		/*case 0:
			float _stan_collision = 0;
			float _stan_exrate = 0;
			_stan_collision = PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * MAX_LV);
			_stan_exrate = PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * MAX_LV);
			for (int i = 0; i < 8; i++){
			CEffectData *temp = new CEffectData(CVector2D(rand() % MAP_RANGE_X + 64, rand() % MAP_RANGE_Y + 73), true, 0, _stan_exrate, STAN_NUM, 0, 10, 99, 0, _stan_collision, STAN, 1, NULL);
			for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
			it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
			if (cd->m_pos != (*it)->m_pos){
			if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, temp->m_pos, (*it)->m_pos)){
			(*it)->m_control = false;
			(*it)->m_timer = 1400;
			(*it)->m_motion_type = 40;
			}
			}
			}
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
			}
			PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_STAN), DX_PLAYTYPE_BACK);
			break;

			/*case 1:
			cd->m_bomb = 1.0f;
			CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp = 1;
			CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_exrate = 1.3f;
			break;*/

	case 0:
	case 1:
	case 2:
		cd->m_bomb += ITEM_BOMB_UP * 5;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp += 5;
		if (CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp > (int)MAX_LV)
			CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp = 10;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_exrate = 1.3f;
		break;
	case 3:
	case 4:
	case 5:
		cd->m_knock_back += ITEM_KNOCK_BACK_UP * 5;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp += 5;
		if (CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp > (int)MAX_LV)
			CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp = 10;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_exrate = 1.3f;
		break;
	case 6:
	case 7:
	case 8:
		cd->m_stan += ITEM_STAN_UP * 5;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp += 5;
		if (CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp > (int)MAX_LV)
			CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp = 10;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_exrate = 1.3f;
		break;
	case 9:
		cd->m_bomb = 1.0f;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp = 1;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_exrate = 1.3f;
		break;
	case 10:
		cd->m_knock_back = 1.0f;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp = 1;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_exrate = 1.3f;
		break;
	case 11:
		cd->m_stan = 1.0f;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp = 1;
		CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_exrate = 1.3f;
		break;
	case 12:
	case 13:
		_bomb_collision = PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_BOMB_UP * MAX_LV);
		_bomb_exrate = (PLAYER_BOMB_EXRATE + 0.1) * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_BOMB_UP * MAX_LV);
		for (int i = 0; i < 8; i++){
			CEffectData *temp = new CEffectData(CVector2D(rand() % MAP_RANGE_X + 64, rand() % MAP_RANGE_Y + 73), true, cd->m_rad + radian(90), _bomb_exrate, BOMB_CHARGE_NUM, 0, 256, 0, 0, _bomb_collision, CHARGE_BOMB, 4, &EMP1);
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
		}
		break;
	case 14:
		_stan_collision = PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * MAX_LV);
		_stan_exrate = PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * MAX_LV);
		for (int i = 0; i < 8; i++){
			CEffectData *temp = new CEffectData(CVector2D(rand() % MAP_RANGE_X + 64, rand() % MAP_RANGE_Y + 73), true, 0, _stan_exrate, STAN_NUM, 0, 10, 99, 0, _stan_collision, STAN, 1, NULL);
			for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
				it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
				if (cd->m_pos != (*it)->m_pos){
					if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, temp->m_pos, (*it)->m_pos)){
						(*it)->m_control = false;
						(*it)->m_timer = 1400;
						(*it)->m_motion_type = 40;
					}
				}
			}
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
		}
		PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_STAN), DX_PLAYTYPE_BACK);
		break;
	default:
		break;
	}
}