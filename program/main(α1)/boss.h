#ifndef BOSS_H
#define BOSS_H

#include "task.h"
#include "base_data.h"
#include <vector>
#include <list>

const float BOSS_EXRATE = 8.0f;
const float BOSS_SPEED = 0.0f;

const float BOSS_BACK = 15.0f;
const int BOSS_HP = 450;
const int BOSS_DAMAGE = 8;

using namespace std;

enum BossType{
	body = 4, rightarm, righand, leftarm, lefhand
};

enum BossAttackType{
	beat, rocket, tuck, beam, push, rock_drop
};

class CBossData;

class CBaseBossMove{
public:
	virtual void Move(CBossData *cd, CVector2D &_pos, int a){};
};

class CBossData : public CBaseData{
public:
	CBossData();
	CBossData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type);
	CBossData(CBaseData _temp);
	~CBossData(){};

	CBaseBossMove *BBMove;
	void Mover(CBossData *cd, CVector2D &_pos, int a){ if (BBMove != NULL)BBMove->Move(this, _pos, a); };

	CBaseBossMove *BBMove2;
	void Mover2(CBossData *cd, CVector2D &_pos, int a){ if (BBMove2 != NULL)BBMove2->Move(this, _pos, a); };

	CBaseBossMove *BBMove3;
	void Mover3(CBossData *cd, CVector2D &_pos, int a){ if (BBMove3 != NULL)BBMove3->Move(this, _pos, a); };

	CBaseBossMove *BBMove4;
	void Mover4(CBossData *cd, CVector2D &_pos, int a){ if (BBMove4 != NULL)BBMove4->Move(this, _pos, a); };

	CVector2D m_start_pos;
	float m_yup = 0;
	int m_ty;
	bool m_attack_fla;
	bool m_attack_movea;
	int m_attack_move2;
	int m_rocket_flag;
	bool m_cool_attacktime;
};

class CBoss : public CTask{
private:
	list<CBossData*> m_boss;
	CBossData m_bossy;
	int m_boss_img[16];
	int m_boss_shadow_img;
	int m_boss_body_img[3];
	int m_count;			//UŒ‚—pƒJƒEƒ“ƒ^[
	bool m_attack_flag;
	int m_dead_count;		//€–S”
	int m_attack_counter;	//UŒ‚‚Ìí—Ş
	int m_attack_interval;	//UŒ‚”­“®‚ÌŠÔŠu
	int m_hpboss;
public:
	CBoss();
	~CBoss(){};
	void Update();

	void KillAll();
	void Delete();

	int Hp();
	void Movestart(CBossData &cd, CVector2D &_pos, bool loop, int type);
	void Draw();
	//list<CBossData*> *GetBossData(){ return &m_boss; };

};

class CMoveboss : public CBaseBossMove{
public:
	void Move(CBossData *cd, CVector2D &_pos, int a);
};

class CMoveboss_aaaa : public CBaseBossMove{
public:
	void Move(CBossData *cd, CVector2D &_pos, int a);
};

class CMoveboss_bbbb : public CBaseBossMove{
public:
	void Move(CBossData *cd, CVector2D &_pos, int a);
};

class CMoveboss_cccc : public CBaseBossMove{
public:
	void Move(CBossData *cd, CVector2D &_pos, int a);
};

#endif BOSS_H