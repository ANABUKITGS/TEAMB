#include "effect.h"
#include "effect_manager.h"
#include "enemy_manager.h"

CEffectData::CEffectData()
:CBaseData()
{}

CEffectData::CEffectData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _rate)
: CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass,_hp, _friction,_collision,_type)
, m_rate(_rate)
{
}

CEffectData::CEffectData(CBaseData _temp)
: CBaseData(_temp.m_pos, _temp.m_living, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
{
	//CEffectManager::GetInstance()->GetEffectAdress()->GetEffectData()->push_back(this);
}

CEffect::CEffect(){
	LoadDivGraph("media\\img\\knock_back.png", 16, 2, 8, 240, 240, m_effect_img[0], 0);
	LoadDivGraph("media\\img\\stan_b1.png", 10, 5, 2, 192, 192, m_effect_img[1], 0);
	LoadDivGraph("media\\img\\bomb_cha0.png", 14, 5, 3, 128, 128, m_effect_img[2], 0);
	LoadDivGraph("media\\img\\bomb.png", 8, 2, 4, 384, 384, m_effect_img[3], 0);
	
	m_priority = eDWP_EFFECT;
	m_update_priority = 2;
	m_draw_priority = 2;

	CEffectManager::GetInstance()->Init(this);

}

void CEffect::Update(){
	for (auto it = m_effects.begin(); it != m_effects.end(); it++){
		(*it)->m_amine_rate++;

		if ((*it)->m_type == CHARGE_BOMB){
			if ((*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype == (*it)->m_animtype - 1){
				(*it)->m_type = BOMB;
				(*it)->m_animtype = BOMB_NUM;
				(*it)->m_amine_rate = 1;
				(*it)->m_rate = 1;
			}
		}

		if ((*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype == (*it)->m_animtype - 1)
			(*it)->m_living = false;

		if ((*it)->m_type == BOMB){
			if ((*it)->m_amine_rate % (*it)->m_animtype == 4){
				for (auto it1 = CCharaData::GetInstance()->GetCharaData()->begin()/*CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->begin()*/;
					it1 != CCharaData::GetInstance()->GetCharaData()->end()/*CEnemyManager::GetInstance()->GetEnemyAdress()->GetEnemyData()->end()*/; it1++){
					if (IsHitCircle((*it)->m_collision, ENEMY_COLLISION, CVector2D((*it)->m_pos.getX(),
						(*it)->m_pos.getY()), (*it1)->m_pos)){
						(*it1)->m_rad = PosRad((*it)->m_pos, (*it1)->m_pos);
						(*it1)->m_velocity = PLAYER_BOMB_KNOCK_BACK;
						//(*it1)->m_hp -= (int)PLAYER_ATTACK_BOMB * (*it)->m_mass;
						if ((*it1)->m_type == PLAYER)
							(*it1)->m_hp -= (int)(PLAYER_ATTACK_BOMB * (*it)->m_mass) / 3;
						else
							(*it1)->m_hp -= (int)PLAYER_ATTACK_BOMB * (*it)->m_mass;
						(*it1)->m_control = false;
						(*it1)->m_damage = (int)PLAYER_ATTACK_BOMB * (*it)->m_mass;
					}
				}
			}
		}
	}

	Delete();
}

void CEffect::Draw(){
	for (auto it = m_effects.begin(); it != m_effects.end(); it++){
		DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY(), (*it)->m_exrate, (*it)->m_rad, m_effect_img[(*it)->m_type][(*it)->m_amine_rate / (*it)->m_rate % (*it)->m_animtype], TRUE, FALSE);
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