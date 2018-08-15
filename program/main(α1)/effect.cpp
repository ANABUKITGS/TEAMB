#include "effect.h"
#include "effect_manager.h"
#include "enemy_manager.h"


CEffectData::CEffectData()
:CBaseData()
{}

CEffectData::CEffectData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate,CBaseEffectMove *_BEMove)
: CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass,_hp, _friction,_collision,_type)
, m_rate(_rate)
, BEMove(_BEMove)
{
}

CEffectData::CEffectData(CBaseData _temp, int _rate, CBaseEffectMove *_BEMove)
: CBaseData(_temp.m_pos, _temp.m_living, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, m_rate(_rate)
, BEMove(_BEMove)
{
}

CEffect::CEffect(){
	LoadDivGraph("media\\img\\hurricane.png", KNOCK_BACK_NUM, 2, 8, 384, 384, m_effect_img[KNOCK_BACK], 0);
	LoadDivGraph("media\\img\\stan_b1.png", STAN_NUM, 5, 2, 192, 192, m_effect_img[STAN], 0);
	LoadDivGraph("media\\img\\bomb_cha0.png", BOMB_CHARGE_NUM, 5, 3, 128, 128, m_effect_img[CHARGE_BOMB], 0);
	LoadDivGraph("media\\img\\exp.png", BOMB_NUM, 2, 7, 256, 256, m_effect_img[BOMB], 0);		//•ÏX
	LoadDivGraph("media\\img\\e_attack.png", ENEMY_ATTACK_NUM, 2, 4, 384, 384, m_effect_img[ENEMY_ATTACK], 0);
	LoadDivGraph("media\\img\\enemy_create.png", ENEMY_CREATE_NUM, 2, 10, 384, 384, m_effect_img[ENEMY_CREATE], 0);
	LoadDivGraph("media\\img\\enemy_delete.png", ENEMY_DELETE_NUM, 5, 3, 192, 192, m_effect_img[ENEMY_DELETE], 0);
	LoadDivGraph("media\\img\\player_hit.png", PLAYER_HIT_NUM, 2, 4, 384, 384, m_effect_img[PLAYER_HIT], 0);

	m_priority = eDWP_EFFECT;
	m_update_priority = 2;
	m_draw_priority = 2;

	CEffectManager::GetInstance()->Init(this);

}

void CEffect::Update(){
	for (auto it = m_effects.begin(); it != m_effects.end(); it++){
		(*it)->m_amine_rate++;

		(*it)->Mover();
		if ((*it)->m_type != 99){
			if ((*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype == (*it)->m_animtype - 1)
				(*it)->m_living = false;
		}
	}

	Delete();
}

void CEffect::Draw(){
	for (auto it = m_effects.begin(); it != m_effects.end(); it++){
		if ((*it)->m_type != 99){
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