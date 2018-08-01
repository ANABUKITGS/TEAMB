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

//m_typeÇ≈égópÇµÇƒÇ¢ÇÈÅ@
enum EFFECT_TYPE{
	KNOCK_BACK, STAN, CHARGE_BOMB, BOMB
};

class CEffectData : public CBaseData{
public:
	CEffectData();
	CEffectData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate);
	CEffectData(CBaseData _temp);
	~CEffectData(){};
	int m_rate;
};

class CEffect : public CTask{
private:
	list<CEffectData*> m_effects;
	int m_effect_img[4][16];
	int m_count;
public:
	CEffect();
	~CEffect(){};

	void Update();
	void Draw();

	void KillAll();
	void Delete();

	void Bomb(CEffectData* cd);

	list<CEffectData*> *GetEffectData(){ return &m_effects; };
};

#endif EFFECT_H