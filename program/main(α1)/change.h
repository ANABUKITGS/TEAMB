#ifndef _CHANGE_H_
#define	_CHANGE_H_

#include "base_data.h"

class CChangeData : public CBaseData{
public:
	int m_add;					//���߉��Z�l
	CChangeData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type, int _add);
	~CChangeData();
};

class CChange{
private:
	CChangeData* m_blackback;
	int m_blackback_img;		//�摜
	bool m_out_flag;			//�؂�ւ�����
	bool m_change_flag;			//�؂�ւ����Ă��邩�ǂ���
public:
	CChange();
	CChange(float _alpha,int _add);
	~CChange();

	void Update();
	void Draw();
	void Kill(){ delete m_blackback; };
	bool GetOut(){ return m_out_flag; };
	bool GetChangeFlag(){ return m_change_flag; };
	void SetOut(bool _flag){ m_out_flag = _flag; };
	void SetChange(bool _flag){ m_change_flag = _flag; };
	void SetCData( float _alpha,int _add);

};

#endif _CHANGE_H_