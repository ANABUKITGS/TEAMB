#ifndef PLAYER_H
#define PLAYER_H

#include "task.h"
#include "base_data.h"

using namespace std;

const float PLAYER_EXRATE = 1.0f;
const float PLAYER_SPEED = 5.0f;
const float PLAYER_FRICTION = 5.0f;
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

class CPAtable{
public:
	int m_type;
	CBasePAType *BaseAttackType;
};

class CRadTable{
public:
	int m_rad;				
	int m_max_rad;			//最大角
	int m_min_rad;			//最小角
	int m_type;				//画像の種類
};

class CPlayerData : public CBaseData{
public:
	CBasePAType *AttackType;
	void Action(){ if (AttackType != NULL)AttackType->Type(this); };

	CPlayerData();
	CPlayerData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type);
	~CPlayerData(){};
	
	CBaseData m_charge_effect;		//チャージエフェクト
	CBaseData m_avoid_effect;		//回避エフェクト

	float m_chage_count;	//チャージ量
	int m_attack_type;		//攻撃の種類
	float m_stan;
	float m_knock_back;
	float m_bomb;
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

	//移動処理
	void Move(int key);
	//攻撃切り替え
	void Change(int key);
	//回避
	void Avoid(int key);
	//攻撃
	void Attack(int key);

	//使用していない//
	void Pad();
	void Keyboard();
	////////////

	inline CPlayerData* GetData(){ return m_player; };
};

class CStan			: public CBasePAType{ void Type(CPlayerData *cd); };
class CKnockBack	: public CBasePAType{ void Type(CPlayerData *cd); };
class CBomb			: public CBasePAType{ void Type(CPlayerData *cd); };

#endif PLAYER_H
