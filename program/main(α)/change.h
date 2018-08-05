#ifndef _CHANGE_H_
#define	_CHANGE_H_

#include "base_data.h"

class CChangeData : public CBaseData{
public:
	CChangeData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction, float _type);
	~CChangeData();
};

class CChange{
private:
	CChangeData* m_blackback;
	int m_blackback_img;		//‰æ‘œ
	int m_add;					//“§‰ß‰ÁZ’l
	bool m_out_flag;			//Ø‚è‘Ö‚¦Š®—¹
public:
	CChange();
	CChange(float _alpha,int _add);
	~CChange();

	void Update();
	void Draw();
	void Kill(){ delete m_blackback; };
	bool GetOut(){ return m_out_flag; };
};

#endif _CHANGE_H_