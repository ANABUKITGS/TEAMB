#include "ui_manager.h"
#include "player_manager.h"

CUiData::CUiData(){

}

CUiData::CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type)
:CBaseData(_pos,_living,_rad,_exrate,_animtype,_velocity,_mass,_hp,_friction,_collision,_type)
{
	
}

CUi::CUi(){

	//çUåÇÉAÉCÉRÉì
	for (int i = 0; i < 3; i++){
		m_list_ui.push_back(new CUiData(CVector2D(ATTACK_ICON_X + 90*i,ATTACK_ICON_Y),true,0,UI_EXRATE,i,UI_VELOCITY,UI_MASS,UI_HP,0,0,0));
	}

	LoadDivGraph("media\\img\\icon_stan.png", 2, 2, 1, 128, 128, m_icon_img[0], 0);
	LoadDivGraph("media\\img\\icon_knock_back.png", 2, 2, 1, 128, 128, m_icon_img[1], 0);
	LoadDivGraph("media\\img\\icon_bomb.png", 2, 2, 1, 128, 128, m_icon_img[2], 0);

	m_priority = eDWP_UI;
	m_update_priority = 2;
	m_draw_priority = 2;

	CUiManager::GetInstance()->Init(this);
}

void CUi::Update(){
	
}

void CUi::ChengeIcon(int _type){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end(); it++){
		if ((*it)->m_animtype == _type){
			(*it)->m_amine_rate = 1;
		}
		else{
			(*it)->m_amine_rate = 0;
		}
	}
}

void CUi::Draw(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end(); it++){
		DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_icon_img[(*it)->m_animtype][(*it)->m_amine_rate],
			TRUE, FALSE);
	}
}

void CUi::KillAll(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end();){
		it = m_list_ui.erase(it);
		continue;
		it++;
	}
}