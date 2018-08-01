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
const int MAX_ENEMY = 20;


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
	int m_counter;	//移動の切り替え用
	int m_rand;		//使用していない
	bool m_locate;	//見つけているかどうか
};

class CEnemy : public CTask{
private:
	list<CEnemyData*> m_enemys;
	int m_enemy_img[24];
	int m_count;			//出現用カウンター
	int m_dead_count;		//死亡数
public:
	CEnemy();
	~CEnemy(){};

	void Update();
	void Draw();
	void Delete();
	void Move(int key);
	void Reflect(CEnemyData &cd,CVector2D &_pos);
	list<CEnemyData*> *GetEnemyData(){ return &m_enemys; };
	int GetDeadCount(){ return m_dead_count; };
};

class CMovePattern1 : public CBaseEemeyMove{
public:
	void Move(CEnemyData *cd, CVector2D &_pos);
};

#endif ENEMY_H