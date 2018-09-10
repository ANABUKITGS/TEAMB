
/*

�S�Ă̌��ƂȂ�p�����[�^�[�B

*/

#ifndef _BASE_DATA_H_
#define _BASE_DATA_H_

#include "myLib.h"
#include <vector>
#include <list>

using namespace std;

enum CHARA_TYPE{
	PLAYER, ENEMY, ENEMY_BULLET, ITEM, BOSS
};

class CBaseData{
public:
	CVector2D m_pos;		//���W
	bool m_living;			//�����Ă��邩�ǂ���
	float m_alpha;			//���ߒl
	float m_rad;			//�p�x�i���W�A���j
	float m_exrate;			//�傫��
	int m_animtype;			//�A�j���[�V�����̎��
	float m_velocity;		//���x
	float m_speed;			//�ړ����x
	float m_mass;			//����
	int m_amine_rate;		//�A�j���[�V����
	int m_hp;				//�̗�
	float m_friction;		//���C
	float m_collision;		//�����蔻��̑傫��
	bool m_control;			//����\���ǂ����@true:�\�@false:�s��
	int m_type;				//���
	int m_timer;			//���炩�̎���
	int m_damage;			//�_���[�W��
	int m_invincible;		//���G���ǂ���				0:�ʏ�		1:���G		2:����(ENEMY�Ŏg�p)
	bool m_knock_stan;		//�m�b�N�o�b�N���̃X�^��	true:�X�^������@false:�X�^���Ȃ�
	bool m_bank_flag;		//���ˏ������s�����ǂ����@�@true:����		 false:���Ȃ�
	bool m_kill_flag;		//�̗͂��Ȃ��Ȃ������ǂ����@true:�Ȃ�		 false:����
	int m_motion_type;			//�����̎��
	int m_direction_type;		//�����̎��
	int m_anim_division;		//�A�j���[�V�����̃X�s�[�h�֌W
	CBaseData();
	//CharaData�ɕۑ�
	CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);
	//alpha���Ȃ�
	CBaseData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);
	//�K�v�Œ��
	CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype,int _type);
	~CBaseData();
	void Update();
};

//�e�f�[�^�̊Ǘ��i�G�l�~�[�A�v���C���[�A�A�C�e���̊Ǘ��j
class CCharaData{
private:
	static CCharaData* m_pInstance;
	list<CBaseData*> m_chara_data;
	int m_ehp_img[2];
	int m_hhp_img[2];
	int m_bhp_img[4];
	int m_stan_timer_img;
	int m_player_timer_img[4];
public:
	
	CCharaData();
	~CCharaData(){};

	//�߂荞�ݖh�~�i�{�X�p�j
	void LieOnTopProtect(CBaseData* cd1, CBaseData* cd2);
	//�Փˎ��̔���
	void CBank(CBaseData* cd1, CBaseData* cd2);
	//�S�폜
	void KillAll();			
	//��
	void Counter();			
	//�폜
	void Delete();

	//�w��̃f�[�^�̍폜
	void AssignmentDelete(int _type);

	void AssignmentInvincible(int _type);

	void Update();
	//�`��
	void Draw();

	//�^�X�N�}�l�[�W���[�̃f�[�^�̎擾
	//������g���ƃ}�l�[�W���[�̃f�[�^���g�����Ƃ��o����
	static CCharaData* GetInstance();

	//�i�[����Ă�����̂��폜
	static void ClearInstance();

	//���X�g�Ƀ^�X�N�i�[����
	void AddTaskInner(CBaseData* task);

	list<CBaseData*> *GetCharaData(){ return &m_chara_data; };
};

#endif _BASE_DATA_H_