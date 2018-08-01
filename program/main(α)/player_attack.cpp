#include "player_manager.h"
#include "effect_manager.h"
#include "enemy_manager.h"

void CStan::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), true, 0, PLAYER_STAN_EXRATE * (1 + (int)cd->m_chage_count * 0.1f), STAN_NUM, 0, 10, 99, 0, PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f), STAN, 1);
	for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
		it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
		if (IsHitCircle(temp->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), (*it)->m_pos)){
			(*it)->m_control = false;
			(*it)->m_timer = PLAYER_ATTACK_STAN * (int)cd->m_chage_count;
		}
	}
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CKnockBack::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), 1.0f, KNOCK_BACK_NUM, 0, 10, 99, 0, PLAYER_KNOCK_BACK_COLLISION, KNOCK_BACK,1);
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
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_BOMB_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_BOMB_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), PLAYER_BOMB_EXRATE * (1 + (int)cd->m_chage_count * 0.1f), BOMB_CHARGE_NUM, 0, (int)cd->m_chage_count, 0, 0, PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f), CHARGE_BOMB, 4);
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}