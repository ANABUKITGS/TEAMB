#ifndef _UI_H_
#define _UI_H_

#include "task.h"
#include "base_data.h"

const float ATTACK_ICON_X = 60;
const float ATTACK_ICON_Y = 650;
const float UI_EXRATE = 0.8f;
const float UI_ANIMTYPE = 0;
const float UI_VELOCITY = 0;
const float UI_MASS = 0;
const float UI_HP = 0;

class CUiData : public CBaseData{
public:
	CUiData();
	CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type);
	~CUiData(){};
};

class CUi : public CTask{
private:
	list<CUiData*> m_list_ui;
	CUiData* m_serect;
	int m_icon_img[3][2];
public:
	CUi();
	~CUi(){};
	void Update();
	void Draw();
	void ChengeIcon(int _type);
};

#endif _UI_H_