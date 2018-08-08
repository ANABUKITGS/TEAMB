#include "ui_manager.h"
#include "player_manager.h"

CUiData::CUiData(){

}

CUiData::CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type, int _prio)
:CBaseData(_pos,_living,_rad,_exrate,_animtype,_velocity,_mass,_hp,_friction,_collision,_type)
, m_move_pos(_pos)
, m_move_exrate(0)
, m_move_count(0)
, m_priority(_prio)
{
	
}

CUi::CUi(){

	//攻撃アイコン
	for (int i = 0; i < 3; i++){
		//m_list_ui.push_back(new CUiData(CVector2D(ATTACK_ICON_X + 90*i,ATTACK_ICON_Y),true,0,UI_EXRATE,i,UI_VELOCITY,UI_MASS,UI_HP,0,0,ATTACK_ICON));
		if (i == 1)
			m_icon_ui[i] = CUiData(CVector2D(ATTACK_ICON_X + ATTACK_SPACE_ICON_X * i, ATTACK_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, ATTACK_ICON,1);
		else
			m_icon_ui[i] = CUiData(CVector2D(ATTACK_ICON_X + ATTACK_SPACE_ICON_X * i, ATTACK_ICON_Y), true, 0, UI_NO_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, ATTACK_ICON,0);
	}

	LoadDivGraph("media\\img\\icon_stan.png", 2, 2, 1, 128, 128, m_icon_img[1], 0);
	LoadDivGraph("media\\img\\icon_knock_back.png", 2, 2, 1, 128, 128, m_icon_img[0], 0);
	LoadDivGraph("media\\img\\icon_bomb.png", 2, 2, 1, 128, 128, m_icon_img[2], 0);

	m_priority = eDWP_UI;
	m_update_priority = 2;
	m_draw_priority = 2;

	m_change_flag = true;

	CUiManager::GetInstance()->Init(this);
}

void CUi::Update(){

	//攻撃アイコンの処理
	for (int i = 0; i < 3; i++){
		if (m_icon_ui[i].m_move_pos.getX() != m_icon_ui[i].m_pos.getX()){
			m_icon_ui[i].m_move_count += 6.0f;
			static float _mv = 0.0f;
			_mv = m_icon_ui[i].m_pos.getX() - m_icon_ui[i].m_move_pos.getX();
			m_icon_ui[i].m_pos.setX(m_icon_ui[i].m_pos.getX() - sin(radian(m_icon_ui[i].m_move_count)) * _mv);
			
			if (m_icon_ui[i].m_exrate != m_icon_ui[i].m_move_exrate){
				static float _mv_e = 0.0f;
				_mv_e = m_icon_ui[i].m_exrate - m_icon_ui[i].m_move_exrate;
				m_icon_ui[i].m_exrate -= _mv_e / 10;
			}
		}
	}
}

void CUi::ChengeIcon(int _direction){
	if (m_change_flag){

		/*if (_direction != 0)
			m_icon_ui[1 + _direction].m_priority = 2;
		
		/*for (int i = 0; i+1 < 3; i++){
				int a = 0;
				a = m_icon_ui[i].m_priority;
				m_icon_ui[i].m_priority = m_icon_ui[i + 1].m_priority;
				m_icon_ui[i + 1].m_priority = a;
		}*/
		for (int i = 0; i < 3; i++){
			//移動先の決定
			m_icon_ui[i].m_move_count = 0;
			m_icon_ui[i].m_move_pos.addX(ATTACK_SPACE_ICON_X * _direction);
			if (m_icon_ui[i].m_move_pos.getX() < ATTACK_ICON_X1 - ATTACK_SPACE_ICON_X + 1){
				m_icon_ui[i].m_move_pos.setX(ATTACK_ICON_X3);		//右へ
			}
			else if (m_icon_ui[i].m_move_pos.getX() > ATTACK_ICON_X3 + ATTACK_SPACE_ICON_X - 1){
				m_icon_ui[i].m_move_pos.setX(ATTACK_ICON_X1);		//左へ
			}

			if (m_icon_ui[i].m_move_pos.getX() == ATTACK_ICON_X2){
				m_icon_ui[i].m_amine_rate = 1;
				m_icon_ui[i].m_move_exrate = UI_SELECT_EXRATE;
			}
			else{
				m_icon_ui[i].m_amine_rate = 0;
				m_icon_ui[i].m_move_exrate = UI_NO_SELECT_EXRATE;
			}
			//printfDx(" %d / prio %d\n", i, m_icon_ui[i].m_priority);
		}
		/*CUiData _temp;
		for (int i = 0; i < 3; i++){
			for (int j = 1; j < 3; j++){
				if (m_icon_ui[i].m_priority < m_icon_ui[j].m_priority){
					_temp = m_icon_ui[j];
					m_icon_ui[j] = m_icon_ui[i];
					m_icon_ui[i] = _temp;
				}
			}
		}*/
	}
}

void CUi::Draw(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end(); it++){
		DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_icon_img[(*it)->m_animtype][(*it)->m_amine_rate],
			TRUE, FALSE);
	}
	
	for (int i = 0; i < 3; i++){
		DrawRotaGraph(m_icon_ui[i].m_pos.getX(), m_icon_ui[i].m_pos.getY(), m_icon_ui[i].m_exrate, m_icon_ui[i].m_rad, m_icon_img[m_icon_ui[i].m_animtype][m_icon_ui[i].m_amine_rate],
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