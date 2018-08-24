#ifndef TASK_H
#define TASK_H

#include "myLib.h"

//更新順序
enum E_UpdatePrio
{
	eUDP_Tutorial = 0,
	eUDP_FRAME1,
	eUDP_FRAME2,
	eUDP_CARD,
	eUDP_EFFECT,
	eUDP_FIELD,
	eUDP_UI,
	eUDP_CAMERA,
	eUDP_Null,
};
//描画順序
enum E_DrawPrio
{
	eDWP_Tutorial = 0,
	eDWP_FIELD,
	eDWP_ITEM,
	eDWP_PLAYER,
	eDWP_ENEMY,
	eDWP_BOSS,
	eDWP_EFFECT,
	eDWP_UI,
	eDWP_CAMERA,
	eDWP_Null,
};

class CTask{
public:
	CTask();
	CTask(int update_prio, int draw_prio);

	virtual ~CTask(){};
	virtual void Update();
	virtual void Draw();

	int m_priority;
	bool m_update;
	int m_update_priority;	//必要？
	int m_draw_priority;	//必要？

};

#endif TASK_H