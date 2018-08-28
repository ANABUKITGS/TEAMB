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

const float TIMER_ICON_X = 64;
const float TIMER_ICON_Y = 75;

const float TIMER_BACK_ICON_X = 64;
const float TIMER_BACK_ICON_Y = 64;

const float UI_EXRATE = 0.8f;
const float UI_ANIMTYPE = 0;
const float UI_VELOCITY = 0;
const float UI_MASS = 0;
const float UI_HP = 0;
const int UI_TIMER = 60;

const float UI_NO_SELECT_EXRATE = 0.5f;
const float UI_SELECT_EXRATE = 1.0f;
const float ITEM_COMB_TIME = 128.0f;


enum UI_ICON_TYPE{
	ATTACK_ICON
};

enum UI_TYPE{
	TIMER,TIMER_BACK,SECOND_HAND,KALMA
};

enum TEXT_TYPE{
	COMBO,ITEM_CREATE_TEXT,LEVEL_TEXT
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
class CBaseUpdate{
public:
	virtual void Update(CUiData *cd){};
};

class CUiData : public CBaseData{
public:
	CUiData();
	CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type, int _prio,int _r,int _g,int _b, CBaseUpdate* _BUpdate);
	~CUiData(){};

	CBaseUpdate* BUpdate;
	void Update(){ if (BUpdate != NULL)BUpdate->Update(this); };

	CVector2D m_move_pos;		//�ړ���
	float m_move_exrate;		//�傫���̕ύX�l
	float m_move_count;
	int m_priority;			//�`�揇��
	int m_red;
	int m_green;
	int m_blue;
};

class CUi : public CTask{
private:
	list<CUiData*> m_list_ui;
	CUiData m_icon_ui[4];
	CUiData m_combo_ui[3];
	CUiData m_item_ui[3];
	CUiData m_lv_ui[3];
	int m_icon_img[3][2];			//�U���A�C�R��
	int m_ui_img[4];				//
	int m_text_img[3];				//�����n
	int m_num_img[10];				//����
	int m_combo_gage_img;

	int m_comb;						//�R���{��
	float m_comb_timer;				//�R���{�^�C�}�[
	bool m_change_flag;				//�؂�ւ����s�������H
	bool m_endflag;					//�^�C�����~�b�g�ɒB�������H

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

	inline bool GetTimeFlag(){ return m_endflag; };
	inline void SetTimeFlag(bool _flag){ m_endflag = _flag; };
	inline int GetImg(int num1, int num2){ return m_icon_img[num1][num2]; };
	inline void const SetChangeFlag(bool _flag){ m_change_flag = _flag; };
	inline list<CUiData*> *GetUiData(){ return &m_list_ui; };
	inline CUiData* GetComboUiData(int _num){ return &m_combo_ui[_num]; };
	inline CUiData* GetItemUiData(int _num){ return &m_item_ui[_num]; };
	inline CUiData* GetLvUiData(int _num){ return &m_lv_ui[_num]; };

	inline void AddComb(){ m_comb++; };
	inline void SetComb(int _num){ m_comb = _num; };
	inline int GatComb(){ return m_comb; };
	inline void SetCombTimer(int _time){ m_comb_timer = _time; };
};


//��]���̃f�[�^�̓���ւ�
class CRightRotation : public CBaseRotation{
	void rotation(CUiData *cd);
};
class CLeftRotation : public CBaseRotation{
	void rotation(CUiData *cd);
};

//�A�C�R���̃h���[
class CRightIcon : public CBaseIconDraw{
	void IconDraw(CUiData *cd);
};
class CLeftIcon : public CBaseIconDraw{
	void IconDraw(CUiData *cd);
};

//Update
class CTimer : public CBaseUpdate{
	void Update(CUiData *cd);
};

class CSecondHand : public CBaseUpdate{
	void Update(CUiData *cd);
};

class CComb : public CBaseUpdate{
	void Update(CUiData *cd);
};

class CItemText : public CBaseUpdate{
	void Update(CUiData *cd);
};

class CLvNum : public CBaseUpdate{
	void Update(CUiData *cd);
};

#endif _UI_H_