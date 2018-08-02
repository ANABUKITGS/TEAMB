#include "enemy.h"
#include "player_manager.h"
#include "effect_manager.h"

CEffectMovePattern3 EMP3;

void CMovePattern1::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	//Œ©‚Â‚¯‚Ä‚¢‚é‚©‚Ç‚¤‚©//
	{
		if (IsHitCircle(ENEMY_LOCATE_COLLISION, temp->m_collision, cd->m_pos, temp->m_pos)){
			cd->m_locate = true;
			cd->m_counter = 0;
		}
		else
			cd->m_locate = false;
	}

	//ˆÚ“®ˆ—//
	{
		if (cd->m_control){
			if (cd->m_locate){
				cd->m_rad = PosRad(cd->m_pos, temp->m_pos);
				_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
			}
			else{
				if (cd->m_counter < ENEMY_MOVE){
					//cd->m_rand = rand() % 360;
				}
				if (cd->m_counter < ENEMY_WAIT && cd->m_counter > ENEMY_MOVE){
					_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
				}

				if (cd->m_counter % ENEMY_WAIT == 0){
					cd->m_rad = radian((rand() % 360));
					cd->m_counter = 0;
				}
			}
		}
	}
}

void CAttackPattern1::Attack(CEnemyData *cd){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	if (!cd->m_attack_flag){
		if (IsHitCircle(ENEMY_ATTACK_COLLISION, temp->m_collision,
			CVector2D(cd->m_pos.getX() + ENEMY_RANGE * cos(cd->m_rad), cd->m_pos.getY() + ENEMY_RANGE * sin(cd->m_rad)), temp->m_pos)){
			CEffectData *temp = new CEffectData(CVector2D(cd->m_pos.getX() + ENEMY_RANGE * cos(cd->m_rad), cd->m_pos.getY() + ENEMY_RANGE * sin(cd->m_rad)), true, cd->m_rad, ENEMY_ATTACK_EXRATE, ENEMY_ATTACK_NUM, 0, 1.0f, 0, 0, ENEMY_ATTACK_COLLISION, ENEMY_ATTACK, 1, &EMP3);
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(temp);
			cd->m_attack_flag = true;
			cd->m_attack_cool_time = ENEMY_ATTACK_COOL_TIME;
		}
	}
	if (cd->m_attack_cool_time > 0){
		cd->m_attack_cool_time--;
	}
	else
		cd->m_attack_flag = false;
}