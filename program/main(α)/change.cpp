#include "change.h"

CChangeData::CChangeData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction, float _type)
:CBaseData(_pos,_living,_alpha,_rad,_exrate,_animtype,_velocity,_mass,_friction,_type)
{
}

CChangeData::~CChangeData()
{

}

CChange::CChange()
{
	m_blackback = new CChangeData(CVector2D(0,0),true,255,0,1.0f,0,0,0,0,0);

	m_blackback_img = LoadGraph("media\\img\\blackback.jpg");
}

CChange::~CChange(){

}

void CChange::Update(){

}

void CChange::Draw(){
	DrawGraph(m_blackback->m_pos.getX(), m_blackback->m_pos.getY(),m_blackback_img,TRUE);
}