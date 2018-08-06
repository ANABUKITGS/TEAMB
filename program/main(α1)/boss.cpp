#include "boss.h"
#include "boss_manager.h"
#include "player_manager.h"

CBossData::CBossData()
:CBaseData()
{

}

CBossData::CBossData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type)
: CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
{

}

CBossData::CBossData(CBaseData _temp)
: CBaseData(_temp.m_pos, _temp.m_living, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
{

}

CBoss::CBoss(){
	CBossData m_base;
	for (m_bossy.m_type = 3; m_bossy.m_type < 8; m_bossy.m_type++){
		switch (m_bossy.m_type)
		{
		case 3://本体
			m_base.m_pos = CVector2D(648, 160);
			m_base.m_yup = 0;
			break;
		case 4://右腕
			m_base.m_pos = CVector2D(553, 200);
			m_base.m_yup = 5;
			break;
		case 5://右手
			m_base.m_pos = CVector2D(547, 260);
			m_base.m_yup = 10;
			break;
		case 6://左腕
			m_base.m_pos = CVector2D(745, 200);
			m_base.m_yup = 5;
			break;
		case 7://左手
			m_base.m_pos = CVector2D(747, 260);
			m_base.m_yup = 10;
			break;
		}
		m_base.m_type = m_bossy.m_type;
		//座標/生きてる/角度/大きさ/アニメーション/速度/質量/体力/摩擦/当たり判定の大きさ/種類
		_temp = new CBaseData(m_base.m_pos, true, 256, 0, 0, 0, 0, 1, 0, 0, 0, m_base.m_type);
		m_boss.push_back(new CBossData(*_temp));
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

	u = true;
	a = 0;
	b = 0;
	m_priority = eDWP_BOSS;
	m_update_priority = 2;
	m_draw_priority = 2;

	m_boss_rightarm_img = 0;
	m_attack_flag = false;


	CBossManager::GetInstance()->Init(this);
}

void CBoss::Update(){
	CVector2D _pos_;

	int randf = rand() % 100;

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	bool _f = false;
	if (_f = IsKeyTrigger(key, PAD_INPUT_5, 5/*sキー*/) == true){
		printfDx("押している");
		u = false;
	}
	else{
		printfDx("押してない");
	}
	for (auto it = m_boss.begin(); it != m_boss.end(); it++){
		if ((*it)->m_type != 3){
			//待機浮遊モーション//
			if ((*it)->m_yup <= 0){
				(*it)->m_yup -= 0.8f;
				(*it)->m_pos += CVector2D(0, sin(PI*((*it)->m_yup) / 40.0f) / 2.5f);
			}
		}
		_pos_ = (*it)->m_pos;
		Move(*(*it), _pos_);
		//Movestart(*(*it), _pos_, u, 0);
	}
	printfDx("[[%d]]\n", randf);
}

/*void CBoss::Movestart(CBossData &cd, CVector2D &_pos, bool loop, int type){
CVector2D _pos_;
switch (type)
{
case 0:
default:
break;
}
}*/

void CBoss::Move(CBossData &cd, CVector2D &_pos){
	CPlayerData *temp = CPlayerManager::GetInstance()->GetPlayerAdress()->GetData();

	CVector2D pos_;
	CVector2D pos;
	pos = _pos;
	a = 0;
	b = 0;
	if (u == true){
		switch (cd.m_type)
		{
		case body:
			break;
		case rightarm:
			break;
		case righand:
			if (m_attack_flag == true){//近接攻撃モーション終わりに入る
				if (cd.m_pos.getX() != 687 && cd.m_pos.getY() != 300){
					m_boss_rightarm_img -= 1;
					pos_ -= CVector2D((float)m_boss_rightarm_img + 4.1f, (float)m_boss_rightarm_img);
				}
				if (cd.m_pos.getY() <= 300){
					m_boss_rightarm_img = 0;
					u = true;
					m_attack_flag = false;
					a = 0;
					b = 0;
				}
			}
			break;
		case lefhand:
			break;
		case leftarm:
			break;
		default:
			break;
		}
	}
	else{
		switch (cd.m_type)
		{
		case body:
			break;
		case rightarm:
			break;
		case righand:
			a += 10.0f;
			b += 5.0f;
			cd.m_rad = PosRad(cd.m_pos, temp->m_pos);
			_pos += CVector2D(cd.m_velocity * cos(cd.m_rad), cd.m_velocity * sin(cd.m_rad));

			//	pos_ -= CVector2D(b, a);
			if (cd.m_pos.getY() > 400){
				m_attack_flag = true;
				u = true;
				cd.m_velocity = 10;
			}
			break;
		case lefhand:
			break;
		case leftarm:
			break;
		default:
			break;
		}
	}
	cd.m_pos = CVector2D(pos.getX() - pos_.getX(), pos.getY() - pos_.getY());
}

void CBoss::Draw(){
	for (auto it = m_boss.begin(); it != m_boss.end(); it++){
		DrawRotaGraph((int)(*it)->m_pos.getX(), (int)(*it)->m_pos.getY(), 1, 0, m_boss_img[(int)(*it)->m_type - 3], TRUE, FALSE);
		printfDx("[[[[[[[[%f", (*it)->m_pos.getX());
		printfDx("%f\n", (*it)->m_pos.getY());

	}

#if defined(_DEBUG) | defined(DEBUG)
	printfDx("%d\n", u);
	printfDx("%d\n", m_attack_flag);
#endif
}