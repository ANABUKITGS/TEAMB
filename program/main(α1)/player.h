#ifndef PLAYER_H
#define PLAYER_H

#include "task.h"
#include "base_data.h"

using namespace std;

const float PLAYER_EXRATE = 1.0f;
const float PLAYER_SPEED = 5.0f;
const float PLAYER_FRICTION = 0.4f;
const int PLAYER_HP = 64;
const float PLAYER_MASS = 0.5f;

enum PlayerDirection{
	PLAYER_DOWN, PLAYER_DL = 3, PLAYER_LEFT = 6, PLAYER_DR = 9, 
	PLAYER_RIGHT = 12, PLAYER_UL = 15, PLAYER_UP = 18, PLAYER_UR = 21
};

class CPlayerData;

class CBasePAType{
public:
	virtual void Type(CPlayerData *cd){};
};

class CBaseControlType{
public:
	virtual void Type(CPlayerData *cd, int key, float &_fx, float &_fy){};
};

class CBaseItemType{
public:
	virtual void Type(CPlayerData *cd){};
};

//�e�[�u��
class CPAtable{
public:
	int m_type;
	CBasePAType *BaseAttackType;
};

class CRadTable{
public:
	int m_rad;				
	int m_max_rad;			//�ő�p
	int m_min_rad;			//�ŏ��p
	int m_type;				//�摜�̎��
};

class CItemTable{
public:
	int m_i_type;
	CBaseItemType *ItemType;
};

class CPlayerData : public CBaseData{
public:
	CBasePAType *AttackType;
	void Action(){ if (AttackType != NULL)AttackType->Type(this); };
	CBaseControlType *ControlType;
	void Control(int key, float &_fx, float &_fy){ if (ControlType != NULL)ControlType->Type(this,key,_fx,_fy); };
	CBaseItemType *ItemType;
	void ItemAction(){ if (ItemType != NULL)ItemType->Type(this); };

	CPlayerData();
	CPlayerData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type);
	~CPlayerData(){};
	
	CBaseData m_charge_effect;		//�`���[�W�G�t�F�N�g
	CBaseData m_avoid_effect;		//����G�t�F�N�g

	float m_chage_count;	//�`���[�W��
	int m_attack_type;		//�U���̎��
	float m_stan;			//�X�^���̋����l
	float m_knock_back;		//�m�b�N�o�b�N�̋����l
	float m_bomb;			//�{���̋����l
	float m_temporary_rad;	//�ꎞ�I�Ȋp�x�ۑ�	(�m�b�N�o�b�N���ɕ��������������Ȃ邽�߂̉����)
//#if defined(_DEBUG) | defined(DEBUG)
	bool m_control_type;	//����^�C�v
//#endif
};

class CPlayer : public CTask{
private:
	CPlayerData *m_player;
	CPlayerData m_p_avatar[4];
	int m_player_img[24];
	int m_player_charge_img[10];
	int m_player_avoid_img[16];
public:
	CPlayer();
	~CPlayer(){};

	void Update() ;
	void Draw() ;

	void Kill();

	//�ړ�����
	void Move(int key);
	//�U���؂�ւ�
	void Change(int key);
	//���
	void Avoid(int key);
	//�U��
	void Attack(int key);
	//�A�C�e���̊l������
	void ItemGet();

	inline CPlayerData* GetData(){ return m_player; };
};

class CStan			: public CBasePAType{ void Type(CPlayerData *cd); };
class CKnockBack	: public CBasePAType{ void Type(CPlayerData *cd); };
class CBomb			: public CBasePAType{ void Type(CPlayerData *cd); };

class CPad		: public CBaseControlType{ void Type(CPlayerData *cd, int key, float &_fx, float &_fy); };
class CKeyBoard : public CBaseControlType{ void Type(CPlayerData *cd, int key, float &_fx, float &_fy); };

class CStanUp :			public CBaseItemType{ void Type(CPlayerData *cd); };
class CKnockBackUp :	public CBaseItemType{ void Type(CPlayerData *cd); };
class CBombUp :			public CBaseItemType{ void Type(CPlayerData *cd); };
class CHeelUp :			public CBaseItemType{ void Type(CPlayerData *cd); };

#endif PLAYER_H
