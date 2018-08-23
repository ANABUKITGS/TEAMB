#include "change.h"
#include "change_manager.h"

CChangeData::CChangeData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction, float _type,int _add)
:CBaseData(_pos,_living,_alpha,_rad,_exrate,_animtype,_velocity,_mass,_friction,_type)
, m_add(_add)
{
	//CChangeManager::GetInstance()->GetChangeAdress()->SetData(this);
}

CChangeData::~CChangeData()
{

}

CChange::CChange()
:m_out_flag(false)
, m_change_flag(false)
{
	m_blackback = new CChangeData(CVector2D(0,0),true,255,0,1.0f,0,0,0,0,0,0);

	m_blackback_img = LoadGraph("media\\img\\blackback.jpg");

	CChangeManager::GetInstance()->Init(this);
}

CChange::CChange(float _alpha, int _add)
:m_out_flag(false)
{
	m_blackback = new CChangeData(CVector2D(0, 0), true, _alpha, 0, 1.0f, 0, 0, 0, 0, 0, _add);

	m_blackback_img = LoadGraph("media\\img\\blackback.jpg");

	CChangeManager::GetInstance()->Init(this);
}

CChange::~CChange(){

}

void CChange::SetCData(float _alpha,int _add){
	m_blackback = new CChangeData(CVector2D(0, 0), true, _alpha, 0, 1.0f, 0, 0, 0, 0, 0, _add);
}


void CChange::Update(){
	if (m_change_flag){
		if (m_blackback->m_alpha > -1 && m_blackback->m_alpha < 256){
			m_blackback->m_alpha += m_blackback->m_add;
		}
		else{
			m_out_flag = true;
			if (m_blackback->m_add < 0){
				m_change_flag = false;
				Kill();
				SetCData(0, 2);
				m_out_flag = false;
			}
		}
	}
}

void CChange::Draw(){
	if (m_change_flag){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_blackback->m_alpha);
		DrawGraph(m_blackback->m_pos.getX(), m_blackback->m_pos.getY(), m_blackback_img, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	printfDx("alpha = %f\n", m_blackback->m_alpha);
}
