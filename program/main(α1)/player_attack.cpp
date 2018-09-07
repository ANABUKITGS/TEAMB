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
	if (cd->m_stan - 1.0f > ITEM_STAN_UP * 9.0f){
		_stan_collision = PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * 9.0f);
		_stan_exrate = PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_STAN_UP * 9.0f);
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
	if (cd->m_knock_back - 1.0f > ITEM_KNOCK_BACK_UP * 9.0f){
		_cyclone_collision = PLAYER_HURRICANE_COLLISION * (1 + ITEM_KNOCK_BACK_UP * 9.0f);
		_cyclone_exrate = 0.8f * (1 + (int)cd->m_chage_count * 0.1f) * (1 + ITEM_KNOCK_BACK_UP * 9.0f);
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
	if (cd->m_bomb - 1.0f > ITEM_BOMB_UP * 9.0f){
		_bomb_collision = PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_BOMB_UP * 9.0f);
		_bomb_exrate = (PLAYER_BOMB_EXRATE+0.1) * (1 + (int)cd->m_chage_count * 0.1f) * (1.0f + ITEM_BOMB_UP * 9.0f);
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

		_fx = _fx * cd->m_velocity;
		_fy = _fy * cd->m_velocity;
	}
}

void CKeyBoard::Type(CPlayerData *cd, int key, float &_fx, float &_fy){
	//to do 角度によって画像の変更を行う
	if (key & PAD_INPUT_DOWN){
		_fy += cd->m_velocity;
	}
	if (key & PAD_INPUT_LEFT){
		_fx -= cd->m_velocity;
	}
	if (key & PAD_INPUT_RIGHT){
		_fx += cd->m_velocity;
	}
	if (key & PAD_INPUT_UP){
		_fy -= cd->m_velocity;
	}
}

void CStanUp::Type(CPlayerData *cd){
	cd->m_stan += ITEM_STAN_UP;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_hp++;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(0)->m_exrate = 1.3f;
}

void CKnockBackUp::Type(CPlayerData *cd){
	cd->m_knock_back += ITEM_KNOCK_BACK_UP;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_hp++;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(1)->m_exrate = 1.3f;
}

void CBombUp::Type(CPlayerData *cd){
	cd->m_bomb += ITEM_BOMB_UP;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_hp++;
	CUiManager::GetInstance()->GetUiAdress()->GetLvUiData(2)->m_exrate = 1.3f;
}

void CHeelUp::Type(CPlayerData *cd){
	if (cd->m_hp < 64)
		cd->m_hp += ITEM_HEEL_UP;
}