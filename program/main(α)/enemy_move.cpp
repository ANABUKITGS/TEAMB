#include "enemy.h"
#include "player_manager.h"

void CMovePattern1::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	if (IsHitCircle(ENEMY_LOCATE_COLLISION, temp->m_collision, cd->m_pos, temp->m_pos)){
		cd->m_locate = true;
		cd->m_counter = 0;
	}
	else
		cd->m_locate = false;

	if (cd->m_control){
		if (cd->m_locate){
			float _rad = PosRad(cd->m_pos, temp->m_pos);
			_pos += CVector2D(cd->m_velocity * cos(_rad), cd->m_velocity * sin(_rad));
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