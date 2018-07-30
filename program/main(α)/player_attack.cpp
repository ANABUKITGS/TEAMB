#include "player_manager.h"
#include "effect_manager.h"
#include "enemy_manager.h"

void CStan::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), true, 0, 1.5f, STAN_NUM, 0, 10, 99, 0, PLAYER_STAN_COLLISION * (1 + (int)cd->m_chage_count * 0.1f), STAN);
	for (auto it = CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->begin();
		it != CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->end(); it++){
		if (IsHitCircle(cd->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), (*it)->m_pos)){
			(*it)->m_control = false;
			(*it)->m_timer = PLAYER_ATTACK_STAN * (int)cd->m_chage_count;
		}
	}
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CKnockBack::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), 1.0f, KNOCK_BACK_NUM, 0, 10, 99, 0, PLAYER_KNOCK_BACK_COLLISION, KNOCK_BACK);
	for (auto it = CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->begin();
		it != CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->end(); it++){
		if (IsHitCircle(cd->m_collision, ENEMY_COLLISION, CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad),
			cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), (*it)->m_pos)){
			(*it)->m_rad = cd->m_rad;
			(*it)->m_velocity = PLAYER_ATTACK_KNOCK_BACK * (int)cd->m_chage_count * (*it)->m_mass;
			(*it)->m_control = false;
		}
	}
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}

void CBomb::Type(CPlayerData *cd){
	CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad), cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(90), 1.0f, BOMB_CHARGE_NUM, 0,(int)cd->m_chage_count, 0, 0, PLAYER_BOMB_COLLISION * (1 + (int)cd->m_chage_count * 0.1f), CHARGE_BOMB);
	/*for (auto it = CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->begin();
		it != CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->end(); it++){
		if (IsHitCircle(PLAYER_ATTACK_COLLISION, ENEMY_COLLISION, CVector2D(cd->m_pos.getX() + PLAYER_RANGE * cos(cd->m_rad),
			cd->m_pos.getY() + PLAYER_RANGE * sin(cd->m_rad)), (*it)->m_pos)){
			(*it)->m_rad = cd->m_rad;
			(*it)->m_velocity = PLAYER_ATTACK_KNOCK_BACK * cd->m_chage_count * (*it)->m_mass;
			(*it)->m_control = false;
		}
	}*/
	CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
}