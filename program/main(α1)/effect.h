#ifndef EFFECT_H
#define EFFECT_H

#include "task.h"
#include "base_data.h"
#include <list>

using namespace std;

const int STAN_NUM = 24;
const int KNOCK_BACK_NUM = 16;		//16
const int BOMB_CHARGE_NUM = 15;
const int BOMB_NUM = 14;
const int ENEMY_ATTACK_NUM = 16;
const int ENEMY_CREATE_NUM = 20;
const int ENEMY_DELETE_NUM = 16;
const int PLAYER_HIT_NUM = 8;
const int PLAYER_HEEL_NUM = 16;
const int EXP_UP_NUM = 17;
const int STN_UP_NUM = 17;
const int WIN_UP_NUM = 17;
const int E_ITEM_CREATE_NUM = 14;

const int EFFECT_IMG = 14;

//m_typeÅgpµÄ¢é@
enum EFFECT_TYPE{
	KNOCK_BACK, STAN, CHARGE_BOMB, BOMB, ENEMY_ATTACK, ENEMY_CREATE ,ENEMY_DELETE,
	PLAYER_HIT,IMPACT,P_HEEL,STN_UP,WIN_UP,EXP_UP,ITEM_CREATE
};

class CEffectData;

class CBaseEffectMove{
public:
	virtual void Move(CEffectData *cd){};
};

class CEffectData : public CBaseData{
public:
	CEffectData();
	CEffectData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate, CBaseEffectMove *_BEMove);
	CEffectData(CBaseData _temp, int _rate, CBaseEffectMove *_BEMove);
	~CEffectData(){};
	
	CBaseEffectMove *BEMove;
	void Mover(){ if (BEMove != NULL)BEMove->Move(this); };

	int m_rate;
};

class CEffect : public CTask{
private:
	list<CEffectData*> m_effects;
	int m_effect_img[EFFECT_IMG][25];
	int m_count;
public:
	CEffect();
	~CEffect(){};

	void Update();
	void Draw();

	void KillAll();
	void Delete();

	list<CEffectData*> *GetEffectData(){ return &m_effects; };
};
//ûk
class CEffectMovePattern1 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//­
class CEffectMovePattern2 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//GÌU
class CEffectMovePattern3 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//¢«
class CEffectMovePattern4 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//ûkiGðWßéj
class CEffectMovePattern5 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//­Ô
class CEffectMovePattern6 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//Õg
class CEffectMovePattern7 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//ACeo»
class CEffectMovePattern8 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};

#endif EFFECT_H