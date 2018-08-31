#include "enemy_manager.h"
#include "player_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"

CEffectMovePattern1 EMP1_a;
CEffectMovePattern3 EMP3;
CEffectMovePattern7 EMP7;
CMovePattern3		MP3;
CAttackPattern3		AP3;

	/*Šî–{Œ` 
		’Êí:ŠÔŒo‰ß‚Åƒ‰ƒ“ƒ_ƒ€‚ÈŒü‚«‚É’¼i¨’â~ 
		”­Œ©:’Ç”ö
	*/
void CMovePattern1::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	bool _flag = false;

	//Œ©‚Â‚¯‚Ä‚¢‚é‚©‚Ç‚¤‚©//
	{
		if (IsHitCircle(ENEMY_LOCATE_COLLISION, temp->m_collision, cd->m_pos, temp->m_pos)){
			if (!cd->m_locate)cd->m_locate = true;
			cd->m_counter = 0;
		}
		else
			cd->m_locate = false;
	}

	//‹z‚¢‚İ‚ÌˆÚ“®ˆ—
	if (cd->m_control){
		for (auto it = CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->begin();
			it != CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->end(); it++){
			if ((*it)->m_type == KNOCK_BACK){
				if (IsHitCircle(cd->m_collision, (*it)->m_collision, cd->m_pos, (*it)->m_pos)){
					_flag = true;
					cd->m_speed = cd->m_save_speed - (*it)->m_velocity * 0.4f;
					cd->m_rad = PosRad((*it)->m_pos, cd->m_pos);
				}
			}
		}
		if (_flag){
			_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
		}
		else{
			//ˆÚ“®ˆ—//
			cd->m_speed = cd->m_save_speed;
			if (cd->m_locate){
				cd->m_rad = PosRad(cd->m_pos, temp->m_pos);
				_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
			}
			else{
				if (cd->m_counter < ENEMY_WAIT && cd->m_counter > ENEMY_MOVE){
					_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
				}

				if (cd->m_counter % ENEMY_WAIT == 0){
					cd->m_rad = radian((rand() % 360));
					cd->m_counter = 0;
				}
			}
		}
	}
	if (cd->m_anim_division == 14){
		if (cd->m_amine_rate > 26){
			cd->m_motion_type = 0;
			cd->m_anim_division = 15;
		}
	}
}

	/*’â~Œ^ 
		’Êí:ŠÔŒo‰ß‚Åƒ‰ƒ“ƒ_ƒ€‚ÈŒü‚«‚É’¼i¨’â~
		”­Œ©:‚»‚Ìê‚Å’â~ 
				‚ ‚é‹——£‚Ü‚Å‹ß‚Ã‚­‚Æ‹——£‚ğæ‚ë‚¤‚Æ‚·‚é
	*/
void CMovePattern2::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	bool _flag = false;
	//Œ©‚Â‚¯‚Ä‚¢‚é‚©‚Ç‚¤‚©//
	{
		if (IsHitCircle(ENEMY_LONG_LOCATE_COLLISION, temp->m_collision, cd->m_pos, temp->m_pos)){
			if (!cd->m_locate){
				cd->m_locate = true;
				new CEneEffect(&cd->m_pos, &cd->m_locate, 255, 0, 0);
			}
			//cd->m_counter = 0;
		}
		else
			cd->m_locate = false;
	}

	//‹z‚¢‚İ‚ÌˆÚ“®ˆ—
	if (cd->m_control){
		for (auto it = CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->begin();
			it != CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->end(); it++){
			if ((*it)->m_type == KNOCK_BACK){
				if (IsHitCircle(cd->m_collision, (*it)->m_collision, cd->m_pos, (*it)->m_pos)){
					_flag = true;
					cd->m_speed = cd->m_save_speed - (*it)->m_velocity * 0.4f;
					cd->m_rad = PosRad((*it)->m_pos, cd->m_pos);
				}
			}
		}
		if (_flag){
			_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
		}
		else{
			//ˆÚ“®ˆ—//
			cd->m_speed = cd->m_save_speed;
			//‹ß‚Ã‚¢‚½‚ç“¦‚°‚é
			if (!cd->m_escape_flag){
				if (IsHitCircle(ENEMY_LONG_NEAR_COLLISION, temp->m_collision, cd->m_pos, temp->m_pos)){
					cd->m_escape_flag = true;
					cd->m_counter = 0;
				}
			}
			else{
				if (cd->m_counter > 100){
					cd->m_escape_flag = false;
				}
			}

			if (!cd->m_escape_flag){//’Êís“®
				if (cd->m_locate){
					cd->m_rad = PosRad(cd->m_pos, temp->m_pos);
				}
				else{
					if (cd->m_counter < ENEMY_WAIT && cd->m_counter > ENEMY_MOVE){
						_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
					}

					if (cd->m_counter % ENEMY_WAIT == 0){
						cd->m_rad = radian((rand() % 360));
						cd->m_counter = 0;
					}
				}
			}
			else{//“G‚©‚ç‹——£‚ğæ‚é
				cd->m_rad = PosRad(temp->m_pos, cd->m_pos);
				_pos += CVector2D((cd->m_speed + 1) * cos(cd->m_rad), (cd->m_speed + 1) * sin(cd->m_rad));
			}
		}
	}
	if (cd->m_anim_division == 14){
		if (cd->m_amine_rate > 26){
			cd->m_motion_type = 0;
			cd->m_anim_division = 15;
		}
	}
}

void CMovePattern3::Move(CEnemyData *cd, CVector2D &_pos){
	_pos += CVector2D((cd->m_speed + 3) * cos(cd->m_rad), (cd->m_speed + 3) * sin(cd->m_rad));

	if (cd->m_counter % 200 == 0){
		cd->m_living = false;
	}
}

//Šî–{Œ`
void CMovePattern4::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	bool _flag = false;

	//Œ©‚Â‚¯‚Ä‚¢‚é‚©‚Ç‚¤‚©//
	{
		if (IsHitCircle(ENEMY_BIG_LOCATE_COLLISION, temp->m_collision, cd->m_pos, temp->m_pos)){
			if (!cd->m_locate)cd->m_locate = true;
			cd->m_counter = 0;
		}
		else
			cd->m_locate = false;
	}

	//‹z‚¢‚İ‚ÌˆÚ“®ˆ—
	if (cd->m_control){
		for (auto it = CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->begin();
			it != CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->end(); it++){
			if ((*it)->m_type == KNOCK_BACK){
				if (IsHitCircle(cd->m_collision, (*it)->m_collision, cd->m_pos, (*it)->m_pos)){
					_flag = true;
					cd->m_speed = cd->m_save_speed - (*it)->m_velocity * 0.4f;
					cd->m_rad = PosRad((*it)->m_pos, cd->m_pos);
				}
			}
		}
		if (_flag){
			_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
		}
		else{
			//ˆÚ“®ˆ—//
			cd->m_speed = cd->m_save_speed;
			if (cd->m_locate){
				cd->m_rad = PosRad(cd->m_pos, temp->m_pos);
				_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
			}
			else{
				if (cd->m_counter < ENEMY_WAIT && cd->m_counter > ENEMY_MOVE){
					_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
				}

				if (cd->m_counter % ENEMY_WAIT == 0){
					cd->m_rad = radian((rand() % 360));
					cd->m_counter = 0;
				}
			}
		}
	}

	if (cd->m_anim_division == 14){
		if (cd->m_amine_rate > 26){
			cd->m_motion_type = 0;
			cd->m_anim_division = 15;
		}
	}
}

//Šî–{Œ` ’Êí:ŠÔŒo‰ß‚Åƒ‰ƒ“ƒ_ƒ€‚ÈŒü‚«‚É’¼i¨’â~
void CMovePattern5::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	bool _flag = false;

	//‹z‚¢‚İ‚ÌˆÚ“®ˆ—
	if (cd->m_control){
		for (auto it = CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->begin();
			it != CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->end(); it++){
			if ((*it)->m_type == KNOCK_BACK){
				if (IsHitCircle(cd->m_collision, (*it)->m_collision, cd->m_pos, (*it)->m_pos)){
					_flag = true;
					cd->m_speed = cd->m_save_speed - (*it)->m_velocity * 0.4f;
					cd->m_rad = PosRad((*it)->m_pos, cd->m_pos);
				}
			}
		}
		if (_flag){
			_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
			cd->m_speed = cd->m_save_speed;
		}
		else{
			//ˆÚ“®ˆ—//
			if (cd->m_counter < ENEMY_SMALL_WAIT && cd->m_counter > ENEMY_SMALL_MOVE){
				_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
			}

			if (cd->m_counter % ENEMY_SMALL_WAIT == 0){
				cd->m_rad = radian((rand() % 360));
				cd->m_counter = 0;
			}
		}
	}
	if (cd->m_anim_division == 14){
		if (cd->m_amine_rate > 26){
			cd->m_motion_type = 0;
			cd->m_anim_division = 15;
		}
	}
}

//Šî–{Œ` ’Êí:ŠÔŒo‰ß‚Åƒ‰ƒ“ƒ_ƒ€‚ÈŒü‚«‚É’¼i¨’â~
void CMovePattern6::Move(CEnemyData *cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	bool _flag = false;

	//‹z‚¢‚İ‚ÌˆÚ“®ˆ—
	if (cd->m_control){
		for (auto it = CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->begin();
			it != CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->end(); it++){
			if ((*it)->m_type == KNOCK_BACK){
				if (IsHitCircle(cd->m_collision, (*it)->m_collision, cd->m_pos, (*it)->m_pos)){
					_flag = true;
					cd->m_speed = cd->m_save_speed - (*it)->m_velocity * 0.4f;
					cd->m_rad = PosRad((*it)->m_pos, cd->m_pos);
				}
			}
		}
		if (_flag){
			_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
		}
		else{
			//ˆÚ“®ˆ—//
			cd->m_speed = cd->m_save_speed;
			if (cd->m_counter < ENEMY_BOMB_WAIT && cd->m_counter > ENEMY_BOMB_MOVE){
				_pos += CVector2D(cd->m_speed * cos(cd->m_rad), cd->m_speed * sin(cd->m_rad));
			}
			if (cd->m_counter % ENEMY_BOMB_WAIT == 0){
				cd->m_rad = radian((rand() % 360));
				cd->m_counter = 0;
			}
		}
	}
	if (cd->m_anim_division == 7){
		if (cd->m_amine_rate > 26){
			cd->m_motion_type = 0;
			cd->m_anim_division = 15;
			cd->m_living = false;
		}
	}
}

void CAttackPattern1::Attack(CEnemyData *cd){
	CPlayerData *_temp1 = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	if (!cd->m_attack_flag){
		if (IsHitCircle(ENEMY_ATTACK_COLLISION, _temp1->m_collision,
			CVector2D(cd->m_pos.getX() + ENEMY_RANGE * cos(cd->m_rad), cd->m_pos.getY() + ENEMY_RANGE * sin(cd->m_rad)), _temp1->m_pos)){

			cd->m_amine_rate = 0;
			cd->m_motion_type = 16;
			cd->m_anim_division = 14;
			cd->m_attack_flag = true;
			cd->m_attack_cool_time = ENEMY_ATTACK_COOL_TIME;

		}
	}
	else{
		if (cd->m_amine_rate == 8){
			CEffectData *_temp2 = new CEffectData(CVector2D(cd->m_pos.getX() + ENEMY_RANGE * cos(cd->m_rad), cd->m_pos.getY() + ENEMY_RANGE * sin(cd->m_rad)), true, cd->m_rad + radian(180), ENEMY_ATTACK_EXRATE, ENEMY_ATTACK_NUM, 0, 1.0f, 0, 0, ENEMY_ATTACK_COLLISION, ENEMY_ATTACK, 1, &EMP3);
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(_temp2);
		}
	}

	if (cd->m_attack_cool_time > 0){
		cd->m_attack_cool_time--;
	}
	else
		cd->m_attack_flag = false;
}

void CAttackPattern2::Attack(CEnemyData *cd){
	if (!cd->m_escape_flag){
		if (cd->m_locate)
			cd->m_attack_cool_time++;
		else
			cd->m_attack_cool_time = 0;

		if (cd->m_attack_cool_time == ENEMY_LONG_ATTACK_COOL_TIME){
			CPlayerData *_temp1 = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
			cd->m_rad = PosRad(cd->m_pos, _temp1->m_pos);
			CBaseData *_temp2 = new CBaseData(cd->m_pos, true, cd->m_rad, ENEMY_BULLET_EXRATE, BULLET, ENEMY_BULLET_SPEED, ENEMY_BULLET_MASS, ENEMY_BULLET_HP, ENEMY_FRICTION, ENEMY_COLLISION, ENEMY_BULLET);
			CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->push_back(new CEnemyData(*_temp2, CVector2D(0,0),false, &MP3, &AP3));
			cd->m_attack_cool_time = 0;

			cd->m_amine_rate = 0;
			cd->m_motion_type = 16;
			cd->m_anim_division = 14;
		}
	}
}

void CAttackPattern3::Attack(CEnemyData *cd){
	CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	if (_temp->m_invincible == 0){
		if (IsHitCircle(ENEMY_BULLET_COLLISION, _temp->m_collision, cd->m_pos, _temp->m_pos)){
			_temp->m_control = false;
			_temp->m_rad = PosRad(cd->m_pos, _temp->m_pos);
			_temp->m_velocity = ENEMY_BULLET_KNOCK_BACK / _temp->m_mass;
			CUiManager::GetInstance()->GetUiAdress()->SetComb(0);
			CEnemyManager::GetInstance()->GetEnemyAdress()->SetKillConutData(0);
			_temp->m_damage = ENEMY_BULLET_ATTACK_DAMAGE;
			_temp->m_hp -= _temp->m_damage;
			cd->m_living = false;
		}
	}
}

//d‚¢
void CAttackPattern4::Attack(CEnemyData *cd){
	CPlayerData *_temp1 = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
	if (!cd->m_attack_flag){
		if (IsHitCircle(ENEMY_BIG_ATTACK_COLLISION, _temp1->m_collision,
			cd->m_pos, _temp1->m_pos)){
			for (auto it = CCharaData::GetInstance()->GetCharaData()->begin();
				it != CCharaData::GetInstance()->GetCharaData()->end(); it++){
				if ((*it)->m_invincible == 0){
					if (cd->m_pos != (*it)->m_pos){
						if (IsHitCircle(ENEMY_IMPACK_COLLISION, (*it)->m_collision,
							cd->m_pos, (*it)->m_pos)){
							(*it)->m_control = false;
							(*it)->m_timer = ENEMY_BIG_ATTACK_STAN;
							(*it)->m_velocity = ENEMY_BIG_ATTACK_KNOCK_BACK / (*it)->m_mass;
							(*it)->m_rad = PosRad(cd->m_pos, (*it)->m_pos);
							if ((*it)->m_type == PLAYER){
								(*it)->m_damage = ENEMY_BIG_ATTACK_DAMAGE;
								CUiManager::GetInstance()->GetUiAdress()->SetComb(0);
								CEnemyManager::GetInstance()->GetEnemyAdress()->SetKillConutData(0);
								(*it)->m_hp -= (*it)->m_damage;
							}
							cd->m_amine_rate = 0;
							cd->m_motion_type = 16;
							cd->m_anim_division = 14;
						}
					}
				}
			}

			CEffectData *_temp2 = new CEffectData(cd->m_pos, true, cd->m_rad, 0, 0, 0, 1.0f, 0, ENEMY_IMPACK_COLLISION, 0, IMPACT, 1, &EMP7);
			CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(_temp2);
			cd->m_attack_flag = true;
			cd->m_attack_cool_time = ENEMY_BIG_ATTACK_COOL_TIME;

		}
	}
	if (cd->m_attack_cool_time > 0){
		cd->m_attack_cool_time--;
	}
	else
		cd->m_attack_flag = false;
}

//Œy‚¢
void CAttackPattern5::Attack(CEnemyData *cd){
	if (!cd->m_attack_flag){
	CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
		if (IsHitCircle(ENEMY_SMALL_COLLISION + 6, _temp->m_collision,
			cd->m_pos, _temp->m_pos)){
			if (_temp->m_invincible == 0){
				_temp->m_control = false;
				_temp->m_rad = PosRad(cd->m_pos, _temp->m_pos);
				_temp->m_velocity = 7.0f / _temp->m_mass;
				_temp->m_damage = 2;
				_temp->m_hp -= _temp->m_damage;
				CUiManager::GetInstance()->GetUiAdress()->SetComb(0);
				CEnemyManager::GetInstance()->GetEnemyAdress()->SetKillConutData(0);
			}
			cd->m_amine_rate = 0;
			cd->m_motion_type = 16;
			cd->m_anim_division = 14;
			cd->m_attack_flag = true;
			cd->m_attack_cool_time = 40;
		}
	}
	if (cd->m_attack_cool_time > 0){
		cd->m_attack_cool_time--;
	}
	else
		cd->m_attack_flag = false;
}

//”š”­
void CAttackPattern6::Attack(CEnemyData *cd){
	if (!cd->m_attack_flag){
		CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();
		if (_temp->m_invincible == 0){
			if (IsHitCircle(ENEMY_ATTACK_BOMB_COLLISION + 6, _temp->m_collision,
				cd->m_pos, _temp->m_pos)){
				cd->m_amine_rate = 0;
				cd->m_motion_type = 16;
				cd->m_anim_division = 7;
				cd->m_kill_flag = true;
				cd->m_attack_flag = true;
				cd->m_attack_cool_time = 40;
			}
		}
	}
	if (cd->m_attack_cool_time > 0){
		cd->m_attack_cool_time--;
	}
	else
		cd->m_attack_flag = false;
}