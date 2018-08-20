#include "player_manager.h"
#include "boss.h"

/*{
3://�{�� CVector2D(648, 160);
4://�E�r CVector2D(553, 200);
5://�E�� CVector2D(547, 260);
6://���r CVector2D(745, 200);
7://���� CVector2D(747, 260);
}*/

void CMoveboss::Move(CBossData *cd, CVector2D &_pos){

}

void CMoveboss_aaaa::Move(CBossData *cd, CVector2D &_pos){

}

//�E��
void CMoveboss_bbbb::Move(CBossData *cd, CVector2D &_pos, int m_c){
	CVector2D pos;

	if (m_c == 0){
		_pos = CVector2D(547, 270);
		cd->m_ty = cd->m_type;
	}

	else if (m_c == 1){//���P�p��
		cd->m_ty = 11;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(cd->m_pos, CVector2D(547, 800));
		_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

		if (_pos.getY() > 800){
			_pos = CVector2D(547, 0);
			cd->m_attack_fla = true;
		}
	}


	else if (m_c == 2){//�ߐڍU��
		cd->m_ty = 8;
		cd->m_velocity = 4;
		cd->m_rad = PosRad(cd->m_pos, CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));
		_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		if (_pos.getX() > 850 || _pos.getX() < 400 || _pos.getY() > 400 || _pos.getY() < 150){
			cd->m_attack_fla = true;
		}
	}

	else if (m_c == 3){//���p��
		cd->m_ty = 8;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()), CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));

		if (cd->m_attack_move2 == 0){//�������
			cd->m_rad = PosRad(cd->m_pos, CVector2D(547, -50));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));

		}

		if (_pos.getY() < -50){//������ʏ�܂ōs��������W�A�p�x�}��
			_pos = CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY());
			cd->m_attack_move2 = 1;
		}

		if (cd->m_attack_move2 == 1){//�v���C���[�̏c���W�Ɍ������Ă���
			cd->m_ty = 13;
			cd->m_velocity = 15;
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getX() > 1280){
			cd->m_attack_move2 = 2;
			_pos = CVector2D(547, 0);
			cd->m_attack_fla = true;
		}
	}

	if (cd->m_attack_fla == true){//�ߐڍU�����[�V�����I���ɓ���
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
	if (m_c == 0){
		_pos = CVector2D(747, 270);
		cd->m_ty = cd->m_type;
	}

	else if (m_c == 1){//���P�p��
		cd->m_ty = 12;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(cd->m_pos, CVector2D(747, 800));
		_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		if (_pos.getY() > 800){
			_pos = CVector2D(747, 0);
			cd->m_attack_fla = true;
		}
	}

	else if (m_c == 3){//���p��
		cd->m_ty = 8;
		cd->m_velocity = 8;
		cd->m_rad = PosRad(CVector2D(0, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()), CVector2D(CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getX(), CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY()));

		if (cd->m_attack_move2 == 0){//�������
			cd->m_rad = PosRad(cd->m_pos, CVector2D(747, -50));
			_pos += CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getY() < -50){//������ʏ�܂ōs��������W�A�p�x�}��
			_pos = CVector2D(1280, CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos.getY());
			cd->m_attack_move2 = 1;
		}

		if (cd->m_attack_move2 == 1){//�v���C���[�̏c���W�Ɍ������Ă���
			cd->m_ty = 14;
			cd->m_velocity = 15;
			_pos -= CVector2D(cd->m_velocity * cos(cd->m_rad), cd->m_velocity * sin(cd->m_rad));
		}

		if (_pos.getX() < 0){
			cd->m_attack_move2 = 2;
			_pos = CVector2D(747, 0);
			cd->m_attack_fla = true;
		}
	}

	if (cd->m_attack_fla == true){//�ߐڍU�����[�V�����I���ɓ���
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