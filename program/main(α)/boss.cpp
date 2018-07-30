#include "boss.h"
#include "boss_manager.h"

CBossData::CBossData(){

}

CBossData::CBossData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type)
: CBaseData(_pos, _living, _alpha, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
{

}

CBoss::CBoss(){
	CBossData m_base;
	for (m_bossy.m_type = 0; m_bossy.m_type < 5; m_bossy.m_type++){
		switch (m_bossy.m_type)
		{
		case 0://本体
			m_base.m_pos = CVector2D(148, 160);
			m_base.m_velocity = 0;
			break;
		case 1://右腕
			m_base.m_pos = CVector2D(53, 200);
			m_base.m_velocity = 5;
			break;
		case 2://右手
			m_base.m_pos = CVector2D(47, 260);
			m_base.m_velocity = 10;
			break;
		case 3://左腕
			m_base.m_pos = CVector2D(245, 200);
			m_base.m_velocity = 5;
			break;
		case 4://左手
			m_base.m_pos = CVector2D(247, 260);
			m_base.m_velocity = 10;
			break;
		}
		m_base.m_type = m_bossy.m_type;
		//座標/生きているかどうか/透過値/角度（ラジアン）/大きさ/アニメーションの種類/速度/質量/アニメーション/体力/摩擦/当たり判定の大きさ/操作可能/種類/何らかの時間
		m_bo.push_back(CBossData(CVector2D(m_base.m_pos.getX(), m_base.m_pos.getY()), true, 0, 0.0f, 0, 0, m_base.m_velocity, 0, 0, 0, 0, m_base.m_type));
	}
	//ボス胴体
	m_boss_img[0] = LoadGraph("media\\img\\boss.png");
	//ボス右腕
	m_boss_img[1] = LoadGraph("media\\img\\boss_rightarm.png");
	//ボス右手
	m_boss_img[2] = LoadGraph("media\\img\\boss_righthand.png");
	//ボス左腕
	m_boss_img[3] = LoadGraph("media\\img\\boss_leftarm.png");
	//ボス左手
	m_boss_img[4] = LoadGraph("media\\img\\boss_lefthand.png");

	m_priority = eDWP_BOSS;
	m_update_priority = 2;
	m_draw_priority = 2;
	CBossManager::GetInstance()->Init(this);
}

void CBoss::Update(){
	CVector2D _pos_;
	for (auto it = m_bo.begin(); it != m_bo.end(); it++){
		if (it->m_type != 0){
			_pos_ = it->m_pos;
			Move(*it,_pos_);
		}
	}
}

void CBoss::Move(CBossData &cd, CVector2D &_pos){
	_pos += CVector2D(0, sin(PI*(cd.m_velocity) / 40.0f) / 2.5f);
	if (100 < cd.m_velocity && cd.m_velocity <= 0){
		cd.m_velocity += 0.8f;
	}
	else if (cd.m_velocity <= 600){
		cd.m_velocity -= 0.8f;
	}
	cd.m_pos = _pos;
}
void CBoss::Draw(){
	for (auto it = m_bo.begin(); it != m_bo.end(); it++){
		DrawRotaGraph((int)it->m_pos.getX() + 500, (int)it->m_pos.getY(), 1, 0, m_boss_img[(int)it->m_type], TRUE, FALSE);
	}

#if defined(_DEBUG) | defined(DEBUG)
#endif
}