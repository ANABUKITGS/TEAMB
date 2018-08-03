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
	int m_blackback_img;
public:
	CChange();
	~CChange();

	void Update();
	void Draw();
};

#endif _CHANGE_H_