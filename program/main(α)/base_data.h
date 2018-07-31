
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
	PLAYER,ENEMY,ITEM
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
	float m_mass;			//����
	int m_amine_rate;		//�A�j���[�V����
	int m_hp;				//�̗�
	float m_friction;		//���C
	float m_collision;		//�����蔻��̑傫��
	bool m_control;			//����\
	int m_type;				//���
	int m_timer;			//���炩�̎���
	int m_damage;			//�_���[�W��
	CBaseData();
	//CharaData�ɕۑ�
	CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);
	//�ۑ�����Ȃ� HP���Ȃ�
	CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction,int _type);
	//alpha���Ȃ�
	CBaseData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);
	~CBaseData();
	void Update();
};

//�e�f�[�^�̊Ǘ��i�G�l�~�[�A�v���C���[�A�A�C�e���̊Ǘ��j
class CCharaData{
private:
	static CCharaData* m_pInstance;
	list<CBaseData*> m_chara_data;
	int m_ehp_img[2];
	int m_hhp_img;
public:
	
	CCharaData();
	~CCharaData(){};

	//�Փˎ��̔���
	void CBank();
	//�S�폜
	void KillAll();			
	//��
	void Counter();			
	//�폜
	void Delete();
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