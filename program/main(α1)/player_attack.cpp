#include "player_manager.h"
#include "effect_manager.h"
#include "enemy_manager.h"

CEffectMovePattern1 EMP1;

void CStan::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), true, 0, PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f), STAN_NUM, 0, 10, 99, 0, PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f), STAN, 1, NULL);
	for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
		it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
		if (cd->m_pos != (*it)->m_pos){
			if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), (*it)->m_pos)){
				(*it)->m_control = false;
				(*it)->m_timer = PLAYER_ATTACK_STAN * (int)cd->m_chage_count;
			}
		}
	}
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CKnockBack::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), 1.0f, KNOCK_BACK_NUM, 0, 10, 99, 0, PLAYER_KNOCK_BACK_COLLISION, KNOCK_BACK, 1, NULL);
	for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
		it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
		if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad),
			cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), (*it)->m_pos)){
			(*it)->m_rad = cd->m_rad;
			(*it)->m_velocity = PLAYER_ATTACK_KNOCK_BACK * (int)cd->m_chage_count * (*it)->m_mass;
			(*it)->m_control = false;
		}
	}
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CBomb::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_BOMB_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_BOMB_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), PLAYER_BOMB_EXRATE * (1 + (int)cd->m_chage_count * 0.1f), BOMB_CHARGE_NUM, 0, (int)cd->m_chage_count, 0, 0, PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f), CHARGE_BOMB, 4,&EMP1);
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
}

void CKnockBackUp::Type(CPlayerData *cd){
	cd->m_knock_back += ITEM_KNOCK_BACK_UP;
}

void CBombUp::Type(CPlayerData *cd){
	cd->m_bomb += ITEM_BOMB_UP;
}

void CHeelUp::Type(CPlayerData *cd){
	cd->m_hp += ITEM_HEEL_UP;
}