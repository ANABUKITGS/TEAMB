#include "player_manager.h"
#include "boss.h"

/*
//�{��(660, 160);
//�E�r(553, 200);
//�E��(547, 270);
//���r(745, 200);
//����(747, 270);
*/

//�E�r
void CMoveboss::Move(CBossData *cd, CVector2D &_pos, int m_c){

	if (m_c == 0){
		_pos = CVector2D(553, 200);
	}

}

//���r
void CMoveboss_aaaa::Move(CBossData *cd, CVector2D &_pos, int m_c){

	if (m_c == 0){
		_pos = CVector2D(745, 200);

	}
}

//�E��
void CMoveboss_bbbb::Move(CBossData *cd, CVector2D &_pos, int m_c){
	CVector2D pos;
	CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	if (m_c == 0){
		_pos = CVector2D(547, 270);
		cd->m_ty = cd->m_type;
		cd->m_attack_movea = true;
		cd->m_attack_fla = false;
	}

	//���P�p��
	else if (m_c == 1){

		//���P�b�g�p���`�����ʒu���牺
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

		//���P�b�g�p���`���ォ��E��
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

		//���P�b�g�p���`�E�ォ�獶��
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

		//���P�b�g�p���`�̍U���I��
		if (cd->m_rocket_flag == 9){
			_pos = CVector2D(547, 0);
			cd->m_attack_fla = true;
			cd->m_rocket_flag = 0;
		}
	}

	//�ߐڍU��
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

	//���p��
	else if (m_c == 3){
		cd->m_ty = 9;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()), CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));

		//�������
		if (cd->m_attack_move2 == 0){
			cd->m_rad = PosRad(cd->m_pos, CVector2D(547, -50));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		//������ʏ�܂ōs��������W�A�p�x�}��

		if (_pos.getY() < -50){
			_pos = CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY());
			cd->m_attack_move2 = 1;
		}

		//�v���C���[�̏c���W�Ɍ������Ă���
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

	//�ߐڍU�����[�V�����I���ɓ���
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

//����
void CMoveboss_cccc::Move(CBossData *cd, CVector2D &_pos, int m_c){
	CVector2D pos;
	CPlayerData *_temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	if (m_c == 0){
		_pos = CVector2D(747, 270);
		cd->m_ty = cd->m_type;
		cd->m_attack_movea = true;
		cd->m_attack_fla = false;
	}

	//���P�p��
	else if (m_c == 1){

		//���P�b�g�p���`�����ʒu���牺
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

		//���P�b�g�p���`�E�ォ�獶��
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

		//���P�b�g�p���`���ォ��E��
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

		//���P�b�g�p���`�̍U���I��
		if (cd->m_rocket_flag == 9){
			_pos = CVector2D(747, 0);
			cd->m_attack_fla = true;
			cd->m_rocket_flag = 0;
		}
	}
	//���p��
	else if (m_c == 3){
		cd->m_ty = 10;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()), CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));

		//�������
		if (cd->m_attack_move2 == 0){
			cd->m_rad = PosRad(cd->m_pos, CVector2D(747, -50));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		//������ʏ�܂ōs��������W�A�p�x�}��
		if (_pos.getY() < -50){
			_pos = CVector2D(1280, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY());
			cd->m_attack_move2 = 1;
		}

		//�v���C���[�̏c���W�Ɍ������Ă���
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

	//�ߐڍU�����[�V�����I���ɓ���
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