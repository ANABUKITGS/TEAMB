#ifndef BOSS_H
#define BOSS_H

#include "task.h"
#include "base_data.h"
#include <vector>
#include <list>

const float BOSS_EXRATE = 8.0f;
const float BOSS_SPEED = 0.0f;

using namespace std;

enum BossType{
	body = 3, rightarm, righand, leftarm, lefhand
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
	int m_attack_movea;
	int m_attack_move2;
};

class CBoss : public CTask{
private:
	list<CBossData*> m_boss;
	CBossData m_bossy;
	int m_boss_img[12];
	int m_boss_shadow_img;
	int m_boss_body_img[3];
	int m_boss_leftarm_img;
	int m_boss_rightarm_img;
	int m_count;			//出現用カウンター
	int m_attack_move;
	bool m_attack_flag;
	float m_current;
	int m_dead_count;		//死亡数
	int m_attack_counter;
	int rocket_punch_flag1;
	int rocket_punch_flag2;
	int m_v;
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