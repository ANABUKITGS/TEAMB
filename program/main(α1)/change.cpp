#include "change.h"
#include "change_manager.h"

CChangeData::CChangeData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction, float _type)
:CBaseData(_pos,_living,_alpha,_rad,_exrate,_animtype,_velocity,_mass,_friction,_type)
{
}

CChangeData::~CChangeData()
{

}

CChange::CChange()
: m_add(0)
, m_out_flag(false)
{
	m_blackback = new CChangeData(CVector2D(0,0),true,255,0,1.0f,0,0,0,0,0);

	m_blackback_img = LoadGraph("media\\img\\blackback.jpg");

	CChangeManager::GetInstance()->Init(this);
}

CChange::CChange(float _alpha, int _add)
: m_add(_add)
, m_out_flag(false)
{
	m_blackback = new CChangeData(CVector2D(0, 0), true, _alpha, 0, 1.0f, 0, 0, 0, 0, 0);

	m_blackback_img = LoadGraph("media\\img\\blackback.jpg");

	CChangeManager::GetInstance()->Init(this);
}

CChange::~CChange(){

}

void CChange::Update(){
	if (m_blackback->m_alpha > -1 && m_blackback->m_alpha < 256){
		m_blackback->m_alpha += m_add;
	}
	else
		m_out_flag = true;
}

void CChange::Draw(){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blackback->m_alpha);
		DrawGraph(m_blackback->m_pos.getX(), m_blackback->m_pos.getY(), m_blackback_img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
