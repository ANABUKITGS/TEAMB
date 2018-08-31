#include "player_manager.h"
#include "boss.h"

/*
//本体(660, 160);
//右腕(553, 200);
//右手(547, 270);
//左腕(745, 200);
//左手(747, 270);
*/

//右腕
void CMoveboss::Move(CBossData *cd, CVector2D &_pos, int m_c){

	if (m_c == 0){
		_pos = CVector2D(553, 200);
	}

}

//左腕
void CMoveboss_aaaa::Move(CBossData *cd, CVector2D &_pos, int m_c){

	if (m_c == 0){
		_pos = CVector2D(745, 200);

	}
}

//右手
void CMoveboss_bbbb::Move(CBossData *cd, CVector2D &_pos, int m_c){
	CVector2D pos;
	CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	if (m_c == 0){
		_pos = CVector2D(547, 270);
		cd->m_ty = cd->m_type;
		cd->m_attack_movea = true;
		cd->m_attack_fla = false;
	}

	//ロケパン
	else if (m_c == 1){

		//ロケットパンチ初期位置から下
		if (cd->m_rocket_flag == 0){
			cd->m_ty = 12;
			cd->m_velocity = 8;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(547, 800));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

			if (_pos.getY() > 800){

				if (cd->m_hp < 400){
					_pos = CVector2D(0, 0);
					cd->m_rocket_flag = 1;
				}

				else cd->m_rocket_flag = 9;

			}
		}

		//ロケットパンチ左上から右下
		else if (cd->m_rocket_flag == 1){
			cd->m_ty = 12;
			cd->m_velocity = 14;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(1280, 800));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

			if (_pos.getY() > 800){

				if (cd->m_hp < 300){
					_pos = CVector2D(1280, 0);
					cd->m_rocket_flag = 2;
				}

				else cd->m_rocket_flag = 9;

			}
		}

		//ロケットパンチ右上から左下
		else if (cd->m_rocket_flag == 2){
			cd->m_ty = 12;
			cd->m_velocity = 14;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(0, 800));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

			if (_pos.getY() > 800){
				_pos = CVector2D(547, 0);
				cd->m_rocket_flag = 9;
				cd->m_attack_fla = true;
			}
		}

		//ロケットパンチの攻撃終了
		if (cd->m_rocket_flag == 9){
			_pos = CVector2D(547, 0);
			cd->m_attack_fla = true;
			cd->m_rocket_flag = 0;
		}
	}

	//近接攻撃
	else if (m_c == 2){
		cd->m_ty = 9;

		if (cd->m_attack_fla == true){
			cd->m_velocity = 4;
			cd->m_rad = PosRad(cd->m_pos, cd->m_start_pos);
		}
		else{
			cd->m_velocity = 4;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));
		}
		_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

		if (IsHitCircle(cd->m_collision + 1, _temp->m_collision, cd->m_pos, _temp->m_pos)){
			cd->m_attack_fla = true;
		}

		if (_pos.getX() > 850 || _pos.getX() < 400 || _pos.getY() > 400 || _pos.getY() < 150){
			cd->m_attack_fla = true;
		}
	}

	//横パン
	else if (m_c == 3){
		cd->m_ty = 9;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()), CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));

		//拳を上に
		if (cd->m_attack_move2 == 0){
			cd->m_rad = PosRad(cd->m_pos, CVector2D(547, -50));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		//拳が画面上まで行ったら座標、角度挿入

		if (_pos.getY() < -50){
			_pos = CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY());
			cd->m_attack_move2 = 1;
		}

		//プレイヤーの縦座標に向かっていく
		if (cd->m_attack_move2 == 1){
			cd->m_ty = 14;
			cd->m_velocity = 15;
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getX() > 1280){
			cd->m_attack_move2 = 2;
			_pos = CVector2D(547, 0);
			cd->m_attack_fla = true;
		}
	}

	if (IsHitCircle(cd->m_collision + 1, _temp->m_collision, cd->m_pos, _temp->m_pos)){
		_temp->m_control = false;
		_temp->m_rad = PosRad(cd->m_pos, _temp->m_pos);
		_temp->m_velocity = 10 / _temp->m_mass;
		_temp->m_damage = BOSS_DAMAGE;
		_temp->m_hp -= _temp->m_damage;
	}

	//近接攻撃モーション終わりに入る
	if (cd->m_attack_fla == true){
		cd->m_velocity = 9;
		cd->m_rad = PosRad(cd->m_start_pos, cd->m_pos);

		if (_pos.getX() != 0){
			_pos -= CVector2D(cd->m_velocity * cos(cd->m_rad) / 2, 0);
		}

		if (_pos.getY() != 0){
			_pos -= CVector2D(0, cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getX() > 545 && _pos.getX() < 550 && _pos.getY() > 265 && _pos.getY() < 275){
			cd->m_attack_movea = true;
			cd->m_attack_fla = false;
			cd->m_ty = cd->m_type;
			cd->m_rad = 0;
		}
	}
}

//左手
void CMoveboss_cccc::Move(CBossData *cd, CVector2D &_pos, int m_c){
	CVector2D pos;
	CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	if (m_c == 0){
		_pos = CVector2D(747, 270);
		cd->m_ty = cd->m_type;
		cd->m_attack_movea = true;
		cd->m_attack_fla = false;
	}

	//ロケパン
	else if (m_c == 1){

		//ロケットパンチ初期位置から下
		if (cd->m_rocket_flag == 0){
			cd->m_ty = 12;
			cd->m_velocity = 8;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(747, 800));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

			if (_pos.getY() > 800){

				if (cd->m_hp < 400){
					_pos = CVector2D(1280, 0);
					cd->m_rocket_flag = 1;
				}
				else cd->m_rocket_flag = 9;
			}
		}

		//ロケットパンチ右上から左下
		else if (cd->m_rocket_flag == 1){
			cd->m_ty = 12;
			cd->m_velocity = 14;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(0, 800));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

			if (_pos.getY() > 800){

				if (cd->m_hp < 300){
					_pos = CVector2D(0, 0);
					cd->m_rocket_flag = 2;
				}
				else cd->m_rocket_flag = 9;
			}
		}

		//ロケットパンチ左上から右下
		else if (cd->m_rocket_flag == 2){
			cd->m_ty = 12;
			cd->m_velocity = 14;
			cd->m_rad = PosRad(cd->m_pos, CVector2D(1280, 800));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

			if (_pos.getY() > 800){
				_pos = CVector2D(747, 0);
				cd->m_rocket_flag = 9;
				cd->m_attack_fla = true;
			}
		}

		//ロケットパンチの攻撃終了
		if (cd->m_rocket_flag == 9){
			_pos = CVector2D(747, 0);
			cd->m_attack_fla = true;
			cd->m_rocket_flag = 0;
		}
	}
	//横パン
	else if (m_c == 3){
		cd->m_ty = 10;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()), CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));

		//拳を上に
		if (cd->m_attack_move2 == 0){
			cd->m_rad = PosRad(cd->m_pos, CVector2D(747, -50));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		//拳が画面上まで行ったら座標、角度挿入
		if (_pos.getY() < -50){
			_pos = CVector2D(1280, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY());
			cd->m_attack_move2 = 1;
		}

		//プレイヤーの縦座標に向かっていく
		if (cd->m_attack_move2 == 1){
			cd->m_ty = 15;
			cd->m_velocity = 15;
			_pos -= CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getX() < 0){
			cd->m_attack_move2 = 2;
			_pos = CVector2D(747, 0);
			cd->m_attack_fla = true;
		}
	}

	if (IsHitCircle(cd->m_collision + 1, _temp->m_collision, cd->m_pos, _temp->m_pos)){
		_temp->m_control = false;
		_temp->m_rad = PosRad(cd->m_pos, _temp->m_pos);
		_temp->m_velocity = 10 / _temp->m_mass;
		_temp->m_damage = BOSS_DAMAGE;
		_temp->m_hp -= _temp->m_damage;
	}

	//近接攻撃モーション終わりに入る
	if (cd->m_attack_fla == true){
		cd->m_velocity = 9;
		cd->m_rad = PosRad(cd->m_start_pos, cd->m_pos);

		if (_pos.getX() != 0){
			_pos -= CVector2D(cd->m_velocity * cos(cd->m_rad) / 2, 0);
		}

		if (_pos.getY() != 0){
			_pos -= CVector2D(0, cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getX() > 745 && _pos.getX() < 750 && _pos.getY() > 265 && _pos.getY() < 275){
			cd->m_attack_movea = true;
			cd->m_attack_fla = false;
			cd->m_ty = cd->m_type;
			cd->m_rad = 0;
		}
	}
}