#ifndef ENEMY_H
#define ENEMY_H

#include "task.h"
#include "base_data.h"
#include <vector>

using namespace std;

const float ENEMY_EXRATE = 0.7f;
const float ENEMY_SPEED = 1.5f;
const float ENEMY_MASS = 1.0f;
const float ENEMY_FRICTION = 0.1f;
const float ENEMY_HP = 64;
const int MAX_ENEMY = 10;


enum EnemyDirection{
	ENEMY_DOWN, ENEMY_LEFT = 6, ENEMY_RIGHT = 12, ENEMY_UP = 18
};

class CEMoveTable{
public:
	int m_key;
	int m_type;
	float m_temp;
};

class CEnemyData;

class CBaseEemeyMove{
public:
	virtual void Move(CEnemyData *cd, CVector2D &_pos){};
};

class CEnemyData : public CBaseData{
public:
	CEnemyData();
	CEnemyData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type);
	CEnemyData(CBaseData _temp);
	~CEnemyData(){};
	CBaseEemeyMove *BEMove;
	void Mover(CVector2D &_pos){ if (BEMove != NULL)BEMove->Move(this,_pos); };
	int m_counter;	//ˆÚ“®‚ÌØ‚è‘Ö‚¦—p
	int m_rand;		//g—p‚µ‚Ä‚¢‚È‚¢
	bool m_locate;	//Œ©‚Â‚¯‚Ä‚¢‚é‚©‚Ç‚¤‚©
};

class CEnemy : public CTask{
private:
	list<CEnemyData*> m_enemys;
	int m_enemy_img[24];
	int m_hp;
	int m_count;
public:
	CEnemy();
	~CEnemy(){};

	void Update();
	void Draw();
	void Delete();
	void Move(int key);
	void Reflect(CEnemyData &cd,CVector2D &_pos);
	list<CEnemyData*> *GetEnemyData(){ return &m_enemys; };
};

class CMovePattern1 : public CBaseEemeyMove{
public:
	void Move(CEnemyData *cd, CVector2D &_pos);
};

#endif ENEMY_H