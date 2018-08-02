#ifndef EFFECT_H
#define EFFECT_H

#include "task.h"
#include "base_data.h"
#include <list>

using namespace std;

const int STAN_NUM = 10;
const int KNOCK_BACK_NUM = 16;
const int BOMB_CHARGE_NUM = 15;
const int BOMB_NUM = 8;
const int ENEMY_ATTACK_NUM = 8;

//m_typeÇ≈égópÇµÇƒÇ¢ÇÈÅ@
enum EFFECT_TYPE{
	KNOCK_BACK, STAN, CHARGE_BOMB, BOMB,ENEMY_ATTACK
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
	CEffectData(CBaseData _temp);
	~CEffectData(){};
	
	CBaseEffectMove *BEMove;
	void Mover(){ if (BEMove != NULL)BEMove->Move(this); };

	int m_rate;
};

class CEffect : public CTask{
private:
	list<CEffectData*> m_effects;
	int m_effect_img[5][16];
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
//é˚èk
class CEffectMovePattern1 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//îöî≠
class CEffectMovePattern2 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};
//ìGÇÃçUåÇ
class CEffectMovePattern3 :public CBaseEffectMove{
public:
	void Move(CEffectData *cd);
};

#endif EFFECT_H