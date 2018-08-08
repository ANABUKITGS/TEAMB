#ifndef _UI_H_
#define _UI_H_

#include "task.h"
#include "base_data.h"

const float ATTACK_ICON_X = 60;
const float ATTACK_ICON_Y = 650;
const float ATTACK_SPACE_ICON_X = 75;

const float ATTACK_ICON_X1 = 60;
const float ATTACK_ICON_X2 = 135;	//ATTACK_ICON_X1 * ATTACK_SPACE_ICON_X * i
const float ATTACK_ICON_X3 = 210;
const float UI_EXRATE = 0.8f;
const float UI_ANIMTYPE = 0;
const float UI_VELOCITY = 0;
const float UI_MASS = 0;
const float UI_HP = 0;

const float UI_NO_SELECT_EXRATE = 0.5f;
const float UI_SELECT_EXRATE = 1.0f;

enum UI_TYPE{
	ATTACK_ICON,TIMER,KARMA
};

class CUiData;

class CBaseRotation{
public:
	virtual void rotation(CUiData *cd){};
};
class CBaseIconDraw{
public:
	virtual void IconDraw(CUiData *cd){};
};

class CUiData : public CBaseData{
public:
	CUiData();
	CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type, int _prio);
	~CUiData(){};

	CVector2D m_move_pos;		//移動先
	float m_move_exrate;		//大きさの変更値
	float m_move_count;
	int m_priority;			//描画順序
};

class CUi : public CTask{
private:
	list<CUiData*> m_list_ui;
	CUiData m_icon_ui[4];
	CUiData* m_add_icon;
	int m_icon_img[3][2];
	bool m_change_flag;		//切り替えを行ったか？

	CBaseRotation* BRotation;
	void Rotation(){ if (BRotation != NULL)BRotation->rotation(m_icon_ui); };
	CBaseIconDraw* BIconDraw;
	void IconDraw(){ if (BIconDraw != NULL)BIconDraw->IconDraw(m_icon_ui); }
public:
	CUi();
	~CUi(){};
	void Update();
	void Draw();

	void KillAll();

	void ChengeIcon(int _direction);

	int GetImg(int num1, int num2){ return m_icon_img[num1][num2]; };
	void const SetChangeFlag(bool _flag){ m_change_flag = _flag; };
};

//回転時のデータの入れ替え
class CRightRotation : public CBaseRotation{
	void rotation(CUiData *cd);
};
class CLeftRotation : public CBaseRotation{
	void rotation(CUiData *cd);
};

//アイコンのドロー
class CRightIcon : public CBaseIconDraw{
	void IconDraw(CUiData *cd);
};
class CLeftIcon : public CBaseIconDraw{
	void IconDraw(CUiData *cd);
};

#endif _UI_H_