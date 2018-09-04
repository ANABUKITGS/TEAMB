#ifndef _CHANGE_H_
#define	_CHANGE_H_

#include "base_data.h"

class CChangeData : public CBaseData{
public:
	int m_add;					//“§‰ß‰ÁZ’l
	CChangeData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type, int _add);
	~CChangeData();
};

class CChange{
private:
	CChangeData* m_blackback;
	int m_blackback_img;		//‰æ‘œ
	bool m_out_flag;			//Ø‚è‘Ö‚¦Š®—¹
	bool m_change_flag;			//Ø‚è‘Ö‚¦‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
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