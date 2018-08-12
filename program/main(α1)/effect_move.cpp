#include "effect.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "effect_manager.h"

CEffectMovePattern2 EMP2;
CEffectMovePattern6 EMP6;

//���k
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

//����
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
					//(*it1)->m_kill_flag = true;
				}
			}
		}
	}
	if (cd->m_amine_rate % cd->m_animtype == cd->m_animtype - 1){
		CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(cd->m_pos, true, 0, 1, 0, 0, 0, 0, cd->m_collision, 0, 99, 1, &EMP6));
	}
}

//�G�̍U��
void CEffectMovePattern3::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == 4){
		CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
		if (!_temp->m_invincible){
			if (IsHitCircle(ENEMY_ATTACK_COLLISION, _temp->m_collision,
				CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), _temp->m_pos)){
				_temp->m_temporary_rad = _temp->m_rad;
				_temp->m_rad = cd->m_rad;
				_temp->m_velocity = ENEMY_ATTACK_KNOCK_BACK * _temp->m_mass;
				_temp->m_control = false;
				_temp->m_damage = ENEMY_ATTACK_DAMAGE;
				_temp->m_hp -= _temp->m_damage;
			}
		}
	}
}

//����
void CEffectMovePattern4::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == ENEMY_CREATE_NUM - 1){
		CBaseData *_temp = new CBaseData(CVector2D(cd->m_pos.getX(), cd->m_pos.getY() + 30), true, radian((rand() % 360)), ENEMY_EXRATE, 0, ENEMY_SPEED, ENEMY_MASS, ENEMY_HP, ENEMY_FRICTION, ENEMY_COLLISION, ENEMY);
		CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->push_back(new CEnemyData(*_temp));
	}
}

//���k�i�G���W�߂�j
void CEffectMovePattern5::Move(CEffectData *cd){
	for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
		it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
		if (!(*it1)->m_control){
			if (!(*it1)->m_invincible){
				if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
					cd->m_pos.getY()), (*it1)->m_pos)){
					(*it1)->m_rad = PosRad( (*it1)->m_pos,cd->m_pos);
					(*it1)->m_velocity = PLAYER_HURRICANE_KNOCK_BACK;
					(*it1)->m_bank_flag = false;
				}
			}
		}
	}
}

//�����̏��ԏ���
void CEffectMovePattern6::Move(CEffectData *cd){
	cd->m_collision += 5;
	if (cd->m_collision <= cd->m_friction){
		for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
			it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
			if ((*it1)->m_kill_flag){
				if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
					cd->m_pos.getY()), (*it1)->m_pos)){
					(*it1)->m_living = false;
				}
			}
			if (cd->m_collision == cd->m_friction - 2){
				(*it1)->m_living = false;
			}
		}
	}
	else{
		cd->m_living = false;
	}
}