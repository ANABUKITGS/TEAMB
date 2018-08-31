#include "boss.h"
#include "boss_manager.h"
#include "player_manager.h"
#include "field_manager.h"

CMoveboss aa;
CMoveboss_aaaa bb;
CMoveboss_bbbb cc;
CMoveboss_cccc dd;

CBossData::CBossData()
{

}

CBossData::CBossData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type)
:CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
, BBMove(&aa)
, BBMove2(&bb)
, BBMove3(&cc)
, BBMove4(&dd)
, m_start_pos()
, m_yup(0)
, m_attack_fla(0)
, m_attack_movea(false)
, m_attack_move2(0)
, m_ty()
, m_rocket_flag(0)
{

}

CBossData::CBossData(CBaseData _temp)
: CBaseData(_temp.m_pos, _temp.m_living, _temp.m_alpha, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, BBMove(&aa)
, BBMove2(&bb)
, BBMove3(&cc)
, BBMove4(&dd)
, m_start_pos(_temp.m_pos.getX(), _temp.m_pos.getY())
, m_yup(0)
, m_attack_fla(0)
, m_attack_movea(false)
, m_attack_move2(0)
, m_ty(_temp.m_type)
, m_rocket_flag(0)
{

}

CBoss::CBoss(){
	CBossData m_base;
	for (m_bossy.m_type = body; m_bossy.m_type < lefhand + 1; m_bossy.m_type++){
		switch (m_bossy.m_type)
		{
		case body://本体
			m_base.m_pos = CVector2D(660, 160);
			m_base.m_hp = BOSS_HP;
			m_base.m_collision = 100;
			break;
		case rightarm://右腕
			m_base.m_pos = CVector2D(553, 200);
			m_base.m_hp = BOSS_HP;
			m_base.m_collision = 10;
			break;
		case righand://右手
			m_base.m_pos = CVector2D(547, 270);
			m_base.m_hp = BOSS_HP;
			m_base.m_collision = 20;
			break;
		case leftarm://左腕
			m_base.m_pos = CVector2D(745, 200);
			m_base.m_hp = BOSS_HP;
			m_base.m_collision = 20;
			break;
		case lefhand://左手
			m_base.m_pos = CVector2D(747, 270);
			m_base.m_hp = BOSS_HP;
			m_base.m_collision = 20;
			break;
		}
		m_base.m_type = m_bossy.m_type;
		m_base.m_ty++;

		//座標/生きてる/角度/大きさ/アニメーション/速度/質量/体力/摩擦/当たり判定の大きさ/種類
		CBaseData *_temp = new CBaseData(m_base.m_pos, true, 0, 0, 90, 0, 100, m_base.m_hp, 0, m_base.m_collision, m_base.m_type);
		m_boss.push_back(new CBossData(*_temp));
	}
	//ボス胴体
	m_boss_img[0] = LoadGraph("media\\img\\3body.png");
	//ボス右腕
	m_boss_img[1] = LoadGraph("media\\img\\boss_rightarm.png");
	//ボス右手
	m_boss_img[2] = LoadGraph("media\\img\\boss_righthand.png");
	//ボス左腕
	m_boss_img[3] = LoadGraph("media\\img\\boss_leftarm.png");
	//ボス左手
	m_boss_img[4] = LoadGraph("media\\img\\boss_lefthand.png");


	m_boss_img[5] = LoadGraph("media\\img\\boss_handright.png");
	m_boss_img[6] = LoadGraph("media\\img\\boss_handleft.png");
	m_boss_img[7] = LoadGraph("media\\img\\1body.png");
	m_boss_img[8] = LoadGraph("media\\img\\rocketpunch2.png");
	m_boss_img[9] = LoadGraph("media\\img\\rocketpunch1.png");
	m_boss_img[10] = LoadGraph("media\\img\\sidepunch1.png");
	m_boss_img[11] = LoadGraph("media\\img\\sidepunch2.png");

	m_boss_img[12] = LoadGraph("media\\img\\damage_boss_arm2.png");
	m_boss_img[13] = LoadGraph("media\\img\\damage_boss_hand2.png");
	m_boss_img[14] = LoadGraph("media\\img\\damage_boss_arm1.png");
	m_boss_img[15] = LoadGraph("media\\img\\damage_boss_hand1.png");

	m_boss_shadow_img = LoadGraph("media\\img\\boss_shadow.png");

	LoadDivGraph("media\\img\\boss.png", 3, 3, 1, 292, 263, m_boss_body_img, 0);

	m_priority = eDWP_BOSS;
	m_update_priority = 2;
	m_draw_priority = 2;
	m_update = true;
	m_attack_flag = false;
	m_attack_counter = 0;
	m_attack_interval = -100;

	m_hpboss = 1;

	CBossManager::GetInstance()->Init(this);
}

void CBoss::Delete(){
	for (auto it = m_boss.begin(); it != m_boss.end();){
		if ((*it)->m_living == false){
			m_dead_count++;
			it = m_boss.erase(it);
			continue;
		}
		it++;
	}
}

void CBoss::KillAll(){
	for (auto it = m_boss.begin(); it != m_boss.end();){
		it = m_boss.erase(it);
		continue;
		it++;
	}
}

void CBoss::Update(){
	CVector2D _pos_;

	int randf = rand() % 500;
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	for (auto it = m_boss.begin(); it != m_boss.end(); it++){
		_pos_ = (*it)->m_pos;
		if ((*it)->m_type != 0){
			//待機浮遊モーション//
			if ((*it)->m_yup >= 0){
				(*it)->m_yup += 0.5f;
				_pos_ += CVector2D(0, sin(PI*((*it)->m_yup) / 40.0f) / 2.5f);
			}
		}
		//boss攻撃ランダム
		if (m_count % 200 == 0){
			m_count = 1;
			if (m_attack_counter == 0){
				if (randf > 0 && randf < 100){
					m_attack_counter = 2;
				}
				if (randf > 100 && randf < 375){
					m_attack_counter = 1;
				}
				if (randf > 375 && randf < 500){
					m_attack_counter = 3;
				}
			}
		}
		m_count++;

		if ((*it)->m_attack_movea == true){
			m_attack_counter = 0;
			(*it)->m_attack_move2 = 0;
			(*it)->m_attack_movea = false;
		}

		if (CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType() != M_BOSS){
			m_attack_interval = -300;
		}

		//ボス本体の描画変化、上下移動変化
		if ((*it)->m_type == body){
			if (m_attack_counter > 0){
				(*it)->m_ty = 10;
				m_attack_interval++;
				(*it)->m_yup += 4.9f;
				if (m_attack_interval < 20){
					_pos_ = CVector2D(_pos_.getX(), 160);
					_pos_ += CVector2D(cos(PI*((*it)->m_yup) / 3.0f) / 0.5f, 0);
				}
			}
			else if (m_attack_counter == 0 && (*it)->m_type == body){
				m_attack_interval = -20;
				_pos_ = CVector2D(660, 160);
				(*it)->m_ty = 3;
			}
		}
		if ((*it)->m_type == body){
			m_hpboss = (*it)->m_hp;
		}

		if (m_attack_interval > 20){
			switch ((*it)->m_type){
			case body:
				break;
			case rightarm:
				(*it)->m_hp = m_hpboss;
				(*it)->BBMove->Move((*it), _pos_, m_attack_counter);
				break;
			case righand:
				(*it)->m_hp = m_hpboss;
				(*it)->BBMove3->Move((*it), _pos_, m_attack_counter);
				break;
			case leftarm:
				(*it)->m_hp = m_hpboss;
				(*it)->BBMove2->Move((*it), _pos_, m_attack_counter);
				break;
			case lefhand:
				(*it)->m_hp = m_hpboss;
				(*it)->BBMove4->Move((*it), _pos_, m_attack_counter);
				break;
			default:
				break;
			}
		}
		//(*it)->Mover2((*it), _pos_);
		(*it)->m_pos = _pos_;

	}

	//削除
	Delete();
}

int CBoss::Hp(){
	for (auto it = m_boss.begin(); it != m_boss.end(); it++){
		if ((*it)->m_type == body)
			return (*it)->m_hp;
	}
}

void CBoss::Draw(){
	for (auto it = m_boss.begin(); it != m_boss.end(); it++){
		/*if ((*it)->m_hp > 100 && (*it)->m_type != body){
		DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_img[(int)(*it)->m_ty - body], TRUE, FALSE);
		}
		else if ((*it)->m_hp <= 100 && (*it)->m_type != body)
		{
		DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_img[(int)(*it)->m_ty - body], TRUE, FALSE);
		}*/

		if (m_attack_counter > 0 && (*it)->m_type != body){
			//ロケットパンチ描画
			if ((*it)->m_rocket_flag != 0 && (*it)->m_type == righand)
				DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, (*it)->m_rad - radian(90), m_boss_img[(int)(*it)->m_ty - body], TRUE, FALSE);

			if ((*it)->m_rocket_flag != 0 && (*it)->m_type == lefhand)
				DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, (*it)->m_rad - radian(90), m_boss_img[(int)(*it)->m_ty - body], TRUE, FALSE);

			if ((*it)->m_rocket_flag == 0)
				DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_img[(int)(*it)->m_ty - body], TRUE, FALSE);
		}

		//HP減少による描画変化
		else if (m_attack_counter == 0 && (*it)->m_type != body && (*it)->m_hp > 150){
			DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_img[(int)(*it)->m_ty - body], TRUE, FALSE);
		}
		else if (m_attack_counter == 0 && (*it)->m_type != body && (*it)->m_hp <= 150){
			DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_img[(int)(*it)->m_ty + 7], TRUE, FALSE);
		}

		//ボス本体と影の描画、HP減少による描画変化
		if (m_attack_counter > 0 && (*it)->m_type == body){
			DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_body_img[2], TRUE, FALSE);
			DrawRotaGraph((int)(*it)->m_pos.getX() - 13, (int)(*it)->m_pos.getY() + 140, 1, 0, m_boss_shadow_img, TRUE, FALSE);
		}
		else if (m_attack_counter == 0 && (*it)->m_type == body && (*it)->m_hp > 150)
		{
			DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_body_img[0], TRUE, FALSE);
			DrawRotaGraph((int)(*it)->m_pos.getX() - 13, (int)(*it)->m_pos.getY() + 150, 1, 0, m_boss_shadow_img, TRUE, FALSE);
		}
		else if ((*it)->m_hp <= 150 && (*it)->m_type == body)
		{
			DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_body_img[1], TRUE, FALSE);
			DrawRotaGraph((int)(*it)->m_pos.getX() - 13, (int)(*it)->m_pos.getY() + 140, 1, 0, m_boss_shadow_img, TRUE, FALSE);
		}
	}
#if defined(_DEBUG) | defined(DEBUG)
	//printfDx("%d\n", m_attack_move);
	//printfDx("%d\n", m_attack_flag);
#endif
}