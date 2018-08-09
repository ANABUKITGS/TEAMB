#include "ui_manager.h"
#include "player_manager.h"

CRightRotation RRotation;
CLeftRotation LRotation;

CRightIcon RIcon;
CLeftIcon LIcon;

CTimer			Timer;
CSecondHand		SecondHand;

CUiData::CUiData(){

}

CUiData::CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type, int _prio,CBaseUpdate* _BUpdate)
:CBaseData(_pos,_living,_rad,_exrate,_animtype,_velocity,_mass,_hp,_friction,_collision,_type)
, m_move_pos(_pos)
, m_move_exrate(0)
, m_move_count(0)
, m_priority(_prio)
, BUpdate(_BUpdate)
{
	
}

CUi::CUi()
: m_change_flag(true)
, m_endflag(false)
{

	//攻撃アイコン
	for (int i = 0; i < 3; i++){
		if (i == 1)
			m_icon_ui[i] = CUiData(CVector2D(ATTACK_ICON_X + ATTACK_SPACE_ICON_X * i, ATTACK_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, ATTACK_ICON, i, NULL);
		else
			m_icon_ui[i] = CUiData(CVector2D(ATTACK_ICON_X + ATTACK_SPACE_ICON_X * i, ATTACK_ICON_Y), true, 0, UI_NO_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, ATTACK_ICON, i, NULL);
	}
	//UI関連（現在時間のみ）
	for (int i = 0; i < 3; i++){
		if (i == TIMER){
			m_list_ui.push_back(new CUiData(CVector2D(TIMER_ICON_X,TIMER_BACK_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, TIMER, 0, NULL));
		}
		else if (i == TIMER_BACK){
			m_list_ui.push_back(new CUiData(CVector2D(TIMER_ICON_X, TIMER_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, TIMER_BACK, 0, &Timer));
		}
		else if (i == SECOND_HAND){
			m_list_ui.push_back(new CUiData(CVector2D(TIMER_ICON_X+1, TIMER_ICON_Y+1), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, SECOND_HAND, 0, &SecondHand));
		}
	}

	LoadDivGraph("media\\img\\icon_stan.png", 2, 2, 1, 128, 128, m_icon_img[1], 0);
	LoadDivGraph("media\\img\\icon_knock_back.png", 2, 2, 1, 128, 128, m_icon_img[0], 0);
	LoadDivGraph("media\\img\\icon_bomb.png", 2, 2, 1, 128, 128, m_icon_img[2], 0);

	m_ui_img[0] = LoadGraph("media\\img\\timer.png");
	m_ui_img[1] = LoadGraph("media\\img\\timer_black.png");
	m_ui_img[2] = LoadGraph("media\\img\\second_hand_l.png");
	m_ui_img[3] = LoadGraph("media\\img\\second_hand_s.png");

	m_priority = eDWP_UI;
	m_update_priority = 2;
	m_draw_priority = 2;

	BIconDraw = &RIcon;

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

	for (auto it = m_list_ui.begin(); it != m_list_ui.end(); it++){
		(*it)->Update();
	}
}

void CUi::ChengeIcon(int _direction){
	if (m_change_flag){
		int _a = 0;		//右か左か	0=右、2=左
		_a = 1 + _direction;
		if (_a > 1){
			BRotation = &RRotation;
			BIconDraw = &RIcon;
			Rotation();
		}
		else if (_a < 1){
			BRotation = &LRotation;
			BIconDraw = &LIcon;
			Rotation();
		}

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
		}
	}
}

void CUi::Draw(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end(); it++){
		if ((*it)->m_animtype == TIMER)
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_ui_img[(*it)->m_animtype],
			TRUE, FALSE);
		if ((*it)->m_animtype == TIMER_BACK){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
			DrawCircleGauge((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_rad, m_ui_img[(*it)->m_animtype], 0);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		if ((*it)->m_animtype == SECOND_HAND){
			DrawRotaGraph2((*it)->m_pos.getX(), (*it)->m_pos.getY(), 5, 35, (*it)->m_exrate, radian((*it)->m_rad), m_ui_img[(*it)->m_animtype], TRUE, FALSE);
		}
	}
	IconDraw();
}

void CUi::KillAll(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end();){
		it = m_list_ui.erase(it);
		continue;
		it++;
	}
}