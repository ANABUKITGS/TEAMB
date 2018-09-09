#include "ui_manager.h"
#include "player_manager.h"
#include "item_manager.h"
#include "enemy_manager.h"
#include "difficulty_level_manager.h"
#include "field_manager.h"

CRightRotation RRotation;
CLeftRotation LRotation;

CRightIcon RIcon;
CLeftIcon LIcon;

CTimer			Timer;
CSecondHand		SecondHand;
CComb			Combo;
CItemText		ItemText;
CLvNum			LvNum;

CStartText		Start;//

CUiData::CUiData(){

}

CUiData::CUiData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type, int _prio, int _r, int _g, int _b, CBaseUpdate* _BUpdate)
:CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
, m_move_pos(_pos)
, m_move_exrate(0)
, m_move_count(0)
, m_priority(_prio)
, BUpdate(_BUpdate)
, m_red(_r)
, m_green(_g)
, m_blue(_b)
{
}

CUiData::CUiData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type, int _r, int _g, int _b, CBaseUpdate* _BUpdate)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _type)
, m_move_pos(_pos)
, m_move_exrate(0)
, m_move_count(0)
, m_priority(0)
, BUpdate(_BUpdate)
, m_red(_r)
, m_green(_g)
, m_blue(_b)
{
}

CUiData::CUiData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type, CBaseUpdate* _BUpdate)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _type)
, m_move_pos(_pos)
, m_move_exrate(0)
, m_move_count(0)
, m_priority(0)
, BUpdate(_BUpdate)
, m_red(0)
, m_green(0)
, m_blue(0)
, m_img(LoadGraph("media\\img\\start.png"))
{
	m_img = LoadGraph("media\\img\\start.png");
}

CUi::CUi()
: m_comb(0)
, m_comb_timer(0)
, m_change_flag(true)
, m_endflag(false)
, m_pass_flag(false)
{

	//攻撃アイコン
	for (int i = 0; i < 3; i++){
		if (i == 1){
			m_icon_ui[i] = CUiData(CVector2D(ATTACK_ICON_X + ATTACK_SPACE_ICON_X * i, ATTACK_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, ATTACK_ICON, i, NULL);
			m_icon_ui[i].m_amine_rate = 1;
		}
		else
			m_icon_ui[i] = CUiData(CVector2D(ATTACK_ICON_X + ATTACK_SPACE_ICON_X * i, ATTACK_ICON_Y), true, 0, UI_NO_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, ATTACK_ICON, i, NULL);
	}
	//UI関連（現在時間のみ）
	for (int i = 0; i < 3; i++){
		if (i == TIMER){
			m_list_ui.push_back(new CUiData(CVector2D(TIMER_ICON_X, TIMER_BACK_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, TIMER, 0, NULL));
		}
		else if (i == TIMER_BACK){
			m_list_ui.push_back(new CUiData(CVector2D(TIMER_ICON_X - 1, TIMER_ICON_Y), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, TIMER_BACK, 0, &Timer));
		}
		else if (i == SECOND_HAND){
			m_list_ui.push_back(new CUiData(CVector2D(TIMER_ICON_X, TIMER_ICON_Y + 3), true, 0, UI_SELECT_EXRATE, i, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, SECOND_HAND, 0, &SecondHand));
		}
	}

	m_start = new CUiData(CVector2D(920, 360), true, 0, 0, UI_SELECT_EXRATE, 3, TIMER, &Start);

	m_combo_ui[0] = CUiData(CVector2D(1150, 64), false, 0, 1.0f, 1, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, 0, 0, &Combo);
	m_combo_ui[1] = CUiData(CVector2D(1150, 118), false, 0, 1.0f, 2, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, 0, 0, NULL);
	m_combo_ui[2] = CUiData(CVector2D(1150, 64), false, 0, 1.0f, 1, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, 0, 0, NULL);

	m_item_ui[0] = CUiData(CVector2D(430, 64), false, 0, 1.0f, 1, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, 0, 0, &ItemText);
	m_item_ui[1] = CUiData(CVector2D(720, 81), false, 0, 1.0f, 2, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 0, 0, 0, &ItemText);

	m_lv_ui[0] = CUiData(CVector2D(930, 675), true, 0, 1.0f, 3, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 255, 255, 120, &LvNum);
	m_lv_ui[1] = CUiData(CVector2D(1060, 675), true, 0, 1.0f, 3, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 120, 255, 120, &LvNum);
	m_lv_ui[2] = CUiData(CVector2D(1190, 675), true, 0, 1.0f, 3, UI_VELOCITY, UI_MASS, UI_HP, 0, 0, 0, 0, 255, 120, 120, &LvNum);

	LoadDivGraph("media\\img\\stn_book.png", 2, 2, 1, 128, 128, m_icon_img[1], 0);
	LoadDivGraph("media\\img\\wind_book.png", 2, 2, 1, 128, 128, m_icon_img[0], 0);
	LoadDivGraph("media\\img\\exp_book.png", 2, 2, 1, 128, 128, m_icon_img[2], 0);

	m_ui_img[TIMER] = LoadGraph("media\\img\\time.png");
	m_ui_img[TIMER_BACK] = LoadGraph("media\\img\\timer_black.png");
	m_ui_img[SECOND_HAND] = LoadGraph("media\\img\\time_hands2.png");
	m_ui_img[3] = LoadGraph("media\\img\\second_hand_s.png");
	//m_ui_img[SYMBOL] = LoadGraph("media\\img\\symbol.png");

	m_text_img[COMBO] = LoadGraph("media\\img\\combo_2.png");
	m_text_img[ITEM_CREATE_TEXT] = LoadGraph("media\\img\\item_create_text_2.png");
	m_text_img[LEVEL_TEXT] = LoadGraph("media\\img\\lv.png");
	m_text_img[START_TEXT] = LoadGraph("media\\img\\start.png");

	LoadDivGraph("media\\img\\num_lv_ver2.png", 12, 4, 3, 64, 64, m_lv_num_img, 0);
	LoadDivGraph("media\\img\\num_combo.png", 10, 4, 3, 128, 128, m_combo_num_img, 0);
	LoadDivGraph("media\\img\\num_item.png", 10, 4, 3, 128, 128, m_item_num_img, 0);

	m_combo_gage_img = LoadGraph("media\\img\\combo_gage.jpg");

	m_priority = eDWP_UI;
	m_update_priority = 2;
	m_draw_priority = 2;
	m_update = true;

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

	if (m_comb_timer < 0){
		CItemManager::GetInstance()->GetItemAdress()->Create();
		CEnemyManager::GetInstance()->GetEnemyAdress()->SetCreateTimer(210);
		if (CUiManager::GetInstance()->GetUiAdress()->GatComb() >CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_next_kill)
			CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetEnemyDifficulty()->m_enemy_level++;
		m_comb = 0;
		m_comb_timer = 0;
	}
	else if (m_comb_timer > 0){
		m_comb_timer -= 0.8533333f;
	}

	for (int i = 0; i < 2; i++){
		m_combo_ui[i].Update();
	}

	for (int i = 0; i < 2; i++){
		m_item_ui[i].Update();
	}

	for (int i = 0; i < 3; i++){
		m_lv_ui[i].Update();
	}

	if (m_start != NULL)m_start->Update();

	Delete();
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
		else if ((*it)->m_animtype == TIMER_BACK){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
			DrawCircleGauge((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_rad, m_ui_img[(*it)->m_animtype], 0);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if ((*it)->m_animtype == SECOND_HAND){
			DrawRotaGraph2((*it)->m_pos.getX(), (*it)->m_pos.getY(), 8, 56, (*it)->m_exrate, radian((*it)->m_rad), m_ui_img[(*it)->m_animtype], TRUE, FALSE);
		}
		else if ((*it)->m_animtype == START_TEXT){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (*it)->m_alpha);
			DrawRotaGraph((*it)->m_pos.getX() + 15, (*it)->m_pos.getY() - 20, (*it)->m_exrate, (*it)->m_rad, m_text_img[(*it)->m_animtype], TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
			DrawRotaGraph((*it)->m_pos.getX() + 15, (*it)->m_pos.getY() - 20, (*it)->m_exrate, (*it)->m_rad, m_ui_img[(*it)->m_animtype], TRUE, FALSE);
	}

	//コンボ系
	char buf[100];
	int _num;
	int _temp = 0;
	if (m_combo_ui[0].m_living == true){
		_num = sprintf_s(buf, 100, "%d", m_comb);
		if (_num > 2)
			_temp = 52;
		else if (_num > 1)
			_temp = 26;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_combo_ui[0].m_alpha);
		for (int i = 0; i < _num; i++){
			DrawRotaGraph(m_combo_ui[0].m_pos.getX() - _temp + i * 52,
				m_combo_ui[0].m_pos.getY(), m_combo_ui[0].m_exrate, 0, m_combo_num_img[(buf[i] - '0')], TRUE, FALSE);		//'0'
		}
		DrawRotaGraph(m_combo_ui[1].m_pos.getX(), m_combo_ui[1].m_pos.getY(),
			m_combo_ui[1].m_exrate, 0, m_text_img[0], TRUE, FALSE);
		//ゲージ
		DrawRectGraph(m_combo_ui[1].m_pos.getX() - 64, m_combo_ui[1].m_pos.getY() + 19, 0, 0, m_comb_timer, 4, m_combo_gage_img, FALSE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//出現アイテム数
	if (CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType() != M_BOSS)
	if (m_item_ui[0].m_living == true){
		_num = sprintf_s(buf, 100, "%d", m_item_ui[0].m_hp);
		if (_num > 1)
			_temp = 26;
		else if (_num > 2)
			_temp = 52;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_item_ui[0].m_alpha);
		for (int i = 0; i < _num; i++){
			DrawRotaGraph(m_item_ui[0].m_pos.getX() - _temp + i * 68,
				m_item_ui[0].m_pos.getY(), m_item_ui[0].m_exrate, 0, m_item_num_img[(buf[i] - '0')], TRUE, FALSE);		//'0'
		}
		DrawRotaGraph(m_item_ui[1].m_pos.getX(), m_item_ui[1].m_pos.getY(),
			m_item_ui[1].m_exrate, 0, m_text_img[1], TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//レベル
	for (int i = 0; i < 3; i++){
		SetDrawBright(m_lv_ui[i].m_red, m_lv_ui[i].m_green, m_lv_ui[i].m_blue);
		if (m_lv_ui[i].m_hp != (int)MAX_LV){
			_num = sprintf_s(buf, 100, "%d", m_lv_ui[i].m_hp);
			for (int j = 0; j < _num; j++){
				DrawRotaGraph(m_lv_ui[i].m_pos.getX() + 35 + j * 32,
					m_lv_ui[i].m_pos.getY(), m_lv_ui[i].m_exrate, 0, m_lv_num_img[(buf[j] - '0')], TRUE, FALSE);		//'0'
			}
		}
		else
			DrawRotaGraph(m_lv_ui[i].m_pos.getX() + 30,
				m_lv_ui[i].m_pos.getY(), m_lv_ui[i].m_exrate, 0, m_lv_num_img[11], TRUE, FALSE);
		DrawRotaGraph(m_lv_ui[i].m_pos.getX() - 20, m_lv_ui[i].m_pos.getY(), m_lv_ui[i].m_exrate, 0, m_lv_num_img[10], TRUE, FALSE);		//'0'
		SetDrawBright(255, 255, 255);
	}

	IconDraw();
}

void CUi::Delete(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end();){
		if (!(*it)->m_living){
			it = m_list_ui.erase(it);
			continue;
		}
		it++;
	}
}

void CUi::KillAll(){
	for (auto it = m_list_ui.begin(); it != m_list_ui.end();){
		it = m_list_ui.erase(it);
		continue;
		it++;
	}
}

void CUiData::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawRotaGraph(m_pos.getX() + 15, m_pos.getY() - 20, m_exrate, m_rad, m_img, TRUE, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
