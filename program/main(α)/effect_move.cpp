#include "effect.h"
#include "player_manager.h"

CEffectMovePattern2 EMP2;

//Žûk
void CEffectMovePattern1::Move(CEffectData *cd){
	if (cd->m_amine_rate / cd->m_rate % cd->m_animtype == cd->m_animtype - 1){
		cd->m_type = BOMB;
		cd->m_animtype = BOMB_NUM;
		cd->m_amine_rate = 1;
		cd->m_rate = 1;
		cd->m_exrate += 0.6;
		cd->BEMove = &EMP2;
	}
}

//”š”­
void CEffectMovePattern2::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == 4){
		for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
			it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
			if (!(*it1)->m_invincible){
				if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
					cd->m_pos.getY()), (*it1)->m_pos)){
					(*it1)->m_rad = PosRad(cd->m_pos, (*it1)->m_pos);
					(*it1)->m_velocity = PLAYER_BOMB_KNOCK_BACK;
					if ((*it1)->m_type == PLAYER){
						(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass / 3;
						(*it1)->m_hp -= (*it1)->m_damage;
					}
					else{
						(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass;
						(*it1)->m_hp -= (*it1)->m_damage;
					}
					(*it1)->m_control = false;
				}
			}
		}
	}
}

//“G‚ÌUŒ‚
void CEffectMovePattern3::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == 4){
		CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
		if (!_temp->m_invincible){
			if (IsHitCircle(ENEMY_ATTACK_COLLISION, _temp->m_collision,
				CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), _temp->m_pos)){
				_temp->m_rad = cd->m_rad;
				_temp->m_velocity = ENEMY_ATTACK_KNOCK_BACK * _temp->m_mass;
				_temp->m_control = false;
				_temp->m_damage = ENEMY_ATTACK_DAMAGE;
				_temp->m_hp -= _temp->m_damage;
			}
		}
	}
}