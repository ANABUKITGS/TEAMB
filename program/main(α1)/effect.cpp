#include "effect.h"
#include "effect_manager.h"
#include "enemy_manager.h"


CEffectData::CEffectData()
:CBaseData()
{}

CEffectData::CEffectData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate, CBaseEffectMove *_BEMove, int _red, int _green, int _blue)
: CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass,_hp, _friction,_collision,_type)
, m_rate(_rate)
, BEMove(_BEMove)
, m_red(_red)
, m_green(_green)
, m_blue(_blue)
{
	m_speed = 0;
}

CEffectData::CEffectData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate, CBaseEffectMove *_BEMove)
: CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
, m_rate(_rate)
, BEMove(_BEMove)
, m_red(0)
, m_green(0)
, m_blue(0)
{
	m_speed = 0;
}

CEffectData::CEffectData(CBaseData _temp, int _rate, CBaseEffectMove *_BEMove)
: CBaseData(_temp.m_pos, _temp.m_living, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, m_rate(_rate)
, BEMove(_BEMove)
, m_red(0)
, m_green(0)
, m_blue(0)
{
}

CEffect::CEffect(){
	LoadDivGraph("media\\img\\kaze.png", KNOCK_BACK_NUM, 4, 4, 512, 512, m_effect_img[KNOCK_BACK], 0);
	LoadDivGraph("media\\img\\stn.png", STAN_NUM, 2, 12, 128, 128, m_effect_img[STAN], 0);
	LoadDivGraph("media\\img\\bomb_cha_m.png", BOMB_CHARGE_NUM, 4, 5, 256, 256, m_effect_img[CHARGE_BOMB], 0);
	//LoadDivGraph("media\\img\\bomb_cha1.png", BOMB_CHARGE_NUM, 5, 4, 192, 192, m_effect_img[CHARGE_BOMB], 0);
	LoadDivGraph("media\\img\\exp.png", BOMB_NUM, 2, 7, 256, 256, m_effect_img[BOMB], 0);
	LoadDivGraph("media\\img\\e_attack.png", ENEMY_ATTACK_NUM, 2, 8, 128, 128, m_effect_img[ENEMY_ATTACK], 0);
	LoadDivGraph("media\\img\\enemy_create.png", ENEMY_CREATE_NUM, 2, 10, 384, 384, m_effect_img[ENEMY_CREATE], 0);
	LoadDivGraph("media\\img\\enemy_delete_ver2.png", ENEMY_DELETE_NUM, 2, 8, 256, 256, m_effect_img[ENEMY_DELETE], 0);
	LoadDivGraph("media\\img\\player_hit.png", PLAYER_HIT_NUM, 2, 4, 384, 384, m_effect_img[PLAYER_HIT], 0);
	LoadDivGraph("media\\img\\heel_eff.png", PLAYER_HEEL_NUM, 4, 4, 64, 64, m_effect_img[P_HEEL], 0);
	LoadDivGraph("media\\img\\stn_up.png", STN_UP_NUM, 4, 5, 64, 64, m_effect_img[STN_UP], 0);
	LoadDivGraph("media\\img\\wind_up.png", WIN_UP_NUM, 4, 5, 64, 64, m_effect_img[WIN_UP], 0);
	LoadDivGraph("media\\img\\exp_up.png", EXP_UP_NUM, 4, 5, 64, 64, m_effect_img[EXP_UP], 0);
	LoadDivGraph("media\\img\\item_create.png", E_ITEM_CREATE_NUM, 2, 7, 384, 384, m_effect_img[ITEM_CREATE], 0);

	//LoadDivGraph("media\\img\\impact2.png", 1, 1, 1, 256, 256, m_effect_img[IMPACT], 0);
	m_effect_img[IMPACT][0] = LoadGraph("media\\img\\impact2.png");
	m_effect_img[ITEM_CREATE2][0] = LoadGraph("media\\img\\item_c_c.png");
	m_effect_img[STAR][0] = LoadGraph("media\\img\\star.png");

	m_priority = eDWP_EFFECT;
	m_update_priority = 2;
	m_draw_priority = 2;
	m_update = true;

	CEffectManager::GetInstance()->Init(this);
}

void CEffect::Update(){
	for (auto it = m_effects.begin(); it != m_effects.end(); it++){

			(*it)->m_amine_rate++;

		(*it)->Mover();
		if ((*it)->m_type != 99 && (*it)->m_type != IMPACT && (*it)->m_type != ITEM_CREATE2 && (*it)->m_type != STAR){
			if ((*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype == (*it)->m_animtype - 1)
				(*it)->m_living = false;
		}
	}
	Delete();
}

void CEffect::Draw(){
	for (auto it = m_effects.begin(); it != m_effects.end(); it++){
		if ((*it)->m_type == IMPACT || (*it)->m_type == ITEM_CREATE2){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (*it)->m_alpha);
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_effect_img[(*it)->m_type][0], TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if ((*it)->m_type == STAR){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (*it)->m_alpha);
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad + (*it)->m_mass, m_effect_img[(*it)->m_type][0], TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if ((*it)->m_type == ITEM_CREATE){
			//SetDrawBright((*it)->m_red, (*it)->m_green, (*it)->m_blue);
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_effect_img[(*it)->m_type][(*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype], TRUE, FALSE);
			//SetDrawBright(255, 255, 255);
		}
		else if ((*it)->m_type != 99){
			DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_effect_img[(*it)->m_type][(*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype], TRUE, FALSE);
		}
	}
}

void CEffect::Delete(){
	for (auto it = m_effects.begin(); it != m_effects.end();){
		if ((*it)->m_living == false){
			it = m_effects.erase(it);
			continue;
		}
		it++;
	}
}

void CEffect::KillAll(){
	for (auto it = m_effects.begin(); it != m_effects.end();){
		it = m_effects.erase(it);
		continue;
		it++;
	}
}