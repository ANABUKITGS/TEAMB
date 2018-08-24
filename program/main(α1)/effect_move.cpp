#include "effect.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "difficulty_level_manager.h"
#include "sounddata_manager.h"

CEffectMovePattern2 EMP2;
CEffectMovePattern6 EMP6;

//enemy‚Ìs“®ƒpƒ^[ƒ“
/*CMovePattern1 MP1;
CMovePattern2 MP2;
CMovePattern4 MP4;
CMovePattern5 MP5;
CMovePattern6 MP6;
CAttackPattern1 AP1;
CAttackPattern2 AP2;
CAttackPattern4 AP4;
CAttackPattern5 AP5;
CAttackPattern6 AP6;
*/
/*CECreateTable e_c_table[] = {
	{ 0, NORMAL,ENEMY_EXRATE, ENEMY_NORMAL_SPEED, ENEMY_NORMAL_MASS, ENEMY_NORMAL_HP, ENEMY_COLLISION, &MP1, &AP1 },
	{ 1, LONG_RANGE, ENEMY_LONG_EXRATE, ENEMY_LONG_SPEED, ENEMY_LONG_MASS, ENEMY_LONG_HP, ENEMY_LONG_COLLISION, &MP2, &AP2 },
	{ 2, BIG, ENEMY_EXRATE, ENEMY_BIG_SPEED, ENEMY_BIG_MASS, ENEMY_BIG_HP, ENEMY_BIG_COLLISION, &MP4, &AP4 },
	{ 3, SMALL, ENEMY_EXRATE, ENEMY_SMALL_SPEED, ENEMY_SMALL_MASS, ENEMY_SMALL_HP, ENEMY_SMALL_COLLISION, &MP5, &AP5 },
	{ 4, E_BOMB, ENEMY_EXRATE, ENEMY_BOMB_SPEED, ENEMY_BOMB_MASS, ENEMY_BOMB_HP, ENEMY_ATTACK_BOMB_COLLISION, &MP6, &AP6 },
};*/

//”š”­‘O‚ÌŽûk
void CEffectMovePattern1::Move(CEffectData *cd){
	if (cd->m_amine_rate / cd->m_rate % cd->m_animtype == cd->m_animtype - 1){
		cd->m_type = BOMB;
		cd->m_animtype = BOMB_NUM;
		cd->m_amine_rate = 1;
		cd->m_rate = 1;
		cd->m_exrate += 0.6;
		cd->BEMove = &EMP2;
		PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_BOMB), DX_PLAYTYPE_BACK);
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
					(*it1)->m_velocity = PLAYER_BOMB_KNOCK_BACK / (*it1)->m_mass;
					if (cd->m_friction == 0){
						if ((*it1)->m_type == PLAYER)
							(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass / 3;
						else
							(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass;
						(*it1)->m_hp -= (*it1)->m_damage;
					}
					if (cd->m_friction == 1){//ƒ{ƒ€“G‚Ìƒ_ƒ[ƒW
						(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass;
						(*it1)->m_hp -= (*it1)->m_damage;
					}
					if ((*it1)->m_hp < 0)
						(*it1)->m_hp = 0;
					(*it1)->m_control = false;
				}
			}
		}
	}
	if (cd->m_amine_rate % cd->m_animtype == cd->m_animtype - 1){
		CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(new CEffectData(cd->m_pos, true, 0, 1, 0, 0, 0, 0, cd->m_collision, 0, 99, 1, &EMP6));
	}
}

//“G‚ÌUŒ‚
void CEffectMovePattern3::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == 4){
		CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
		if (!_temp->m_invincible){
			if (IsHitCircle(ENEMY_ATTACK_COLLISION, _temp->m_collision,
				CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), _temp->m_pos)){
				_temp->m_temporary_rad = _temp->m_rad;
				_temp->m_rad = cd->m_rad;
				_temp->m_velocity = ENEMY_ATTACK_KNOCK_BACK / _temp->m_mass;
				_temp->m_control = false;
				_temp->m_damage = ENEMY_ATTACK_DAMAGE;
				_temp->m_hp -= _temp->m_damage;
			}
		}
	}
}

//¢Š«
void CEffectMovePattern4::Move(CEffectData *cd){
	//float _num = CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty().m_small_num;
	//if ()

	/*if (cd->m_amine_rate % cd->m_animtype == ENEMY_CREATE_NUM - 1){
		float _rand = 4;//rand() % ENEMY_TYPE;
		for (auto ect : e_c_table){
			if (ect.m_num == _rand){
				CBaseData *_temp = new CBaseData(CVector2D(cd->m_pos.getX(), cd->m_pos.getY() + 30), true, radian((rand() % 360)), ect.m_exrate, ect.m_type, ect.m_speed, ect.m_mass, ect.m_hp, ENEMY_FRICTION, ect.m_collision, ENEMY);
				CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->push_back(new CEnemyData(*_temp, ect.m_BEMove, ect.m_BEAttack));
				break;
			}
		}
	}*/
}

//Žûki“G‚ðW‚ß‚éj
void CEffectMovePattern5::Move(CEffectData *cd){
	for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
		it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
		if (!(*it1)->m_control){
			if (!(*it1)->m_invincible){
				if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
					cd->m_pos.getY()), (*it1)->m_pos)){
					(*it1)->m_rad = PosRad( (*it1)->m_pos,cd->m_pos);
					(*it1)->m_velocity = cd->m_velocity;
					(*it1)->m_bank_flag = false;
				}
			}
		}
	}
}

//”š”­‚Ì‡”Ôˆ—
void CEffectMovePattern6::Move(CEffectData *cd){
	cd->m_collision += 5;
	if (cd->m_collision <= cd->m_friction){
		for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
			it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
			if ((*it1)->m_animtype != E_BOMB){
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
	}
	else{
		cd->m_living = false;
	}
}

//ÕŒ‚”gˆ—
void CEffectMovePattern7::Move(CEffectData *cd){
	if (cd->m_exrate < 1.5f)
		cd->m_exrate += 0.17;
	else
		cd->m_living = false;
}