#include "effect.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "effect_manager.h"
#include "difficulty_level_manager.h"
#include "sounddata_manager.h"
#include "ui_manager.h"
#include "item_manager.h"

CEffectMovePattern2 EMP2;
CEffectMovePattern6 EMP6;
CEffectMovePattern9 EMP9;
CEffectMovePattern10 EMP10;

//爆発前の収縮
void CEffectMovePattern1::Move(CEffectData *cd){
	if (cd->m_amine_rate / cd->m_rate % cd->m_animtype == cd->m_animtype - 1){
		cd->m_type = BOMB;
		cd->m_animtype = BOMB_NUM;
		cd->m_amine_rate = 1;
		cd->m_rate = 1;
		cd->m_exrate += 0.4;
		cd->BEMove = &EMP2;
		PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_BOMB), DX_PLAYTYPE_BACK);
	}
}

//爆発
void CEffectMovePattern2::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == 4){
		for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
			it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
			if ((*it1)->m_invincible == 0){
				if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
					cd->m_pos.getY()), (*it1)->m_pos)){
					(*it1)->m_rad = PosRad(cd->m_pos, (*it1)->m_pos);
					(*it1)->m_velocity = PLAYER_BOMB_KNOCK_BACK / (*it1)->m_mass;
					if (cd->m_friction == 0){
						if ((*it1)->m_type == PLAYER){
							CUiManager::GetInstance()->GetUiAdress()->SetComb(0);
							CEnemyManager::GetInstance()->GetEnemyAdress()->SetKillConutData(0);
							(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass / 3;
						}
						//追加↓
						else if ((*it1)->m_type == BOSS){
							(*it1)->m_damage = (int)10 * cd->m_mass / 2;
							for (auto it2 = CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->begin();
								it2 != CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->end(); it2++){
								if ((*it2)->m_control == false){
									if (IsHitCircle(cd->m_collision, (*it2)->m_collision, CVector2D(cd->m_pos.getX(),
										cd->m_pos.getY()), (*it2)->m_pos)){
										(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass;
										(*it2)->m_control = true;
									}
								}
							}
						}
						else{
							(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass;
						}
					}
					if (cd->m_friction == 1){//ボム敵のダメージ
						(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * cd->m_mass;
					}
					(*it1)->m_hp -= (*it1)->m_damage;
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

//敵の攻撃
void CEffectMovePattern3::Move(CEffectData *cd){
	if (cd->m_amine_rate % cd->m_animtype == 4){
		CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
		if (_temp->m_invincible == 0){
			if (IsHitCircle(ENEMY_ATTACK_COLLISION, _temp->m_collision,
				CVector2D(cd->m_pos.getX(), cd->m_pos.getY()), _temp->m_pos)){
				_temp->m_temporary_rad = _temp->m_rad;
				_temp->m_rad = cd->m_rad - radian(180);
				_temp->m_velocity = ENEMY_ATTACK_KNOCK_BACK / _temp->m_mass;
				_temp->m_control = false;
				_temp->m_damage = ENEMY_ATTACK_DAMAGE;
				_temp->m_hp -= _temp->m_damage;
				CUiManager::GetInstance()->GetUiAdress()->SetComb(0);
				CEnemyManager::GetInstance()->GetEnemyAdress()->SetKillConutData(0);
			}
		}
	}
}

//召喚
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

//収縮（敵を集める）
void CEffectMovePattern5::Move(CEffectData *cd){
	for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
		it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
		if ((*it1)->m_type != PLAYER){
			if ((*it1)->m_invincible == 0){
				if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
					cd->m_pos.getY()), (*it1)->m_pos)){
					if (!(*it1)->m_control){
						(*it1)->m_rad = PosRad((*it1)->m_pos, cd->m_pos);
						float _vx = cd->m_pos.getX() - (*it1)->m_pos.getX();
						float _vy = cd->m_pos.getY() - (*it1)->m_pos.getY();
						float _len = sqrt(_vx * _vx + _vy * _vy);
						(*it1)->m_velocity = cd->m_velocity * ((_len / cd->m_collision) + 0.1f);
						
						(*it1)->m_bank_flag = false;
					}
				}
			}
		}
	}
}

//爆発の順番処理
void CEffectMovePattern6::Move(CEffectData *cd){
	cd->m_collision += 3;
	if (cd->m_collision <= cd->m_friction){
		for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin();
			it1 != CCharaData::GetInstance()->GetCharaData()->end(); it1++){
			if ((*it1)->m_animtype != E_BOMB){
				if ((*it1)->m_kill_flag){
					if (IsHitCircle(cd->m_collision, (*it1)->m_collision, CVector2D(cd->m_pos.getX(),
						cd->m_pos.getY()), (*it1)->m_pos)){
						if ((*it1)->m_type != ITEM){
							(*it1)->m_living = false;
						}
					}
					if (cd->m_collision >= cd->m_friction - 4){
						if ((*it1)->m_type != ITEM){
							(*it1)->m_living = false;
						}
					}
				}
			}
		}
	}
	else{
		cd->m_living = false;
	}
}

//衝撃波処理
void CEffectMovePattern7::Move(CEffectData *cd){
	if (cd->m_exrate < 1.5f)
		cd->m_exrate += 0.17;
	else
		cd->m_living = false;
}

//アイテム出現処理
void CEffectMovePattern8::Move(CEffectData *cd){
	if (cd->m_amine_rate > E_ITEM_CREATE_NUM * cd->m_rate - 3){
		CBaseData* _temp1 = new CBaseData(cd->m_pos, true, 0, ITEM_EXRATE, rand() % 4, ITEM_SPEED, ITEM_MASS, ITEM_HP, ITEM_FRICTION, ITEM_COLLISION, ITEM);
		CItemManager::GetInstance()->GetItemAdress()->GetItemData()->push_back(new CItemData(*_temp1));
		CEffectData *_temp2 = new CEffectData(cd->m_pos, true, 0, 0.0f, 0, 0, 0, 0, 0, 0, ITEM_CREATE2, 2, &EMP9);
		CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(_temp2);
	}
}

//アイテム出現処理２
void CEffectMovePattern9::Move(CEffectData *cd){
	if (cd->m_exrate < 1.5f)
		cd->m_exrate += 0.03;
	else
		cd->m_living = false;

	cd->m_alpha -= 6;
}

//アイテム出現処理３（☆）
void CEffectMovePattern10::Move(CEffectData *cd){
	if (cd->m_timer < 65)
		cd->m_timer += 1;
	else
		cd->m_living = false;
	
	if (cd->m_alpha > 0 && cd->m_timer > 50)
		cd->m_alpha -= 20;
		

	if (degree(cd->m_speed) < 89){
		cd->m_speed += 0.04f;		//移動値 移動量 * 1~0まで			
	}

	if (cd->m_exrate < cd->m_collision){
		cd->m_exrate += 0.006f;			//大きさ
	}

	cd->m_mass += 0.09f;//☆の画像の回転

	cd->m_pos += CVector2D((cos(cd->m_speed)*cd->m_velocity) * cos(cd->m_rad), (cos(cd->m_speed)*cd->m_velocity) * sin(cd->m_rad));
}

//敵爆破処理
void CEffectMovePattern11::Move(CEffectData *cd){
	int _num = CEnemyManager::GetInstance()->GetEnemyAdress()->GetKillCount() / 5;
	if (cd->m_amine_rate == 14){
		for (int i = 0; i < _num; i++){
			CEffectData *_temp2 = new CEffectData(cd->m_pos, true, rand() % 360, 0.1f, 0, ((rand() % 4) + 5) * 1.0f /*8.0f*/, 0, 0, 0, (rand() % 30) * 0.01f + 0.12f, STAR, 1, &EMP10);
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(_temp2);
		}
	}
}

//ミステリーアイテムの爆破処理
void CEffectMovePattern12::Move(CEffectData *cd){
	/*if (cd->m_amine_rate / cd->m_rate % cd->m_animtype == cd->m_animtype - 1){
		cd->m_type = BOMB;
		cd->m_animtype = BOMB_NUM;
		cd->m_amine_rate = 1;
		cd->m_rate = 1;
		cd->m_exrate += 0.4;
		cd->BEMove = &EMP2;
		PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(S_ATTACK_BOMB), DX_PLAYTYPE_BACK);
	}*/
}
