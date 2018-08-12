#ifndef ITEM_H
#define ITEM_H

#include "task.h"
#include "base_data.h"
#include <list>

using namespace std;

const float ITEM_EXRATE = 1.0f;
const float ITEM_SPEED = 0.0f;
const float ITEM_MASS = 1.0f;
const int ITEM_HP = 1000;
const float ITEM_FRICTION = 0.05f;
const float ITEM_COLLISION = 32.0f;

//m_animtypeで使用している　
enum ITEM_TYPE{
	STAN_ITEM, KNOCK_BACK_ITEM, BOMB_ITEM, HEEL_ITEM
};

class CItemData : public CBaseData{
public:
	CItemData();
	CItemData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate);
	CItemData(CBaseData _temp);
	~CItemData(){};
	int m_y_up;
};

class CItem : public CTask{
private:
	list<CItemData*> m_items;
	int m_item_img[4];
	bool m_create_flag;
public:
	CItem();
	~CItem(){};

	void Update();
	void Draw();
	
	void KillAll();
	void Delete();
	//アイテムの生成
	void Create();
	//反射
	void Reflect(CItemData* cd);

	void SetItemCreateFlag(bool _flag){ m_create_flag = _flag; };
	//void GetItemCreateFlag(bool _flag){ m_create_flag = _flag; };
	list<CItemData*> *GetItemData(){ return &m_items; };
};

#endif ITEM_H