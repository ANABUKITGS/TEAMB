#include "item.h"
#include "item_manager.h"
#include "enemy_manager.h"
#include "difficulty_level_manager.h"
#include "ui_manager.h"

CItemData::CItemData()
:CBaseData()
{}

CItemData::CItemData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, int _y_up)
: CBaseData(_pos, _living, _rad, _exrate, _animtype, _velocity, _mass, _hp, _friction, _collision, _type)
, m_y_up(_y_up)
{
}

CItemData::CItemData(CBaseData _temp)
: CBaseData(_temp.m_pos, _temp.m_living, _temp.m_alpha, _temp.m_rad, _temp.m_exrate, _temp.m_animtype, _temp.m_velocity, _temp.m_mass, _temp.m_hp, _temp.m_friction, _temp.m_collision, _temp.m_type)
, m_y_up(0)
{
	//CItemManager::GetInstance()->GetItemAdress()->GetItemData()->push_back(this);
}

CItem::CItem()
:m_create_flag(false)
{
	m_item_img[STAN_ITEM] = LoadGraph("media\\img\\stn_buff_by.png");
	m_item_img[KNOCK_BACK_ITEM] = LoadGraph("media\\img\\wind_buff_bg.png");
	m_item_img[BOMB_ITEM] = LoadGraph("media\\img\\exp_buff_br.png");
	m_item_img[HEEL_ITEM] = LoadGraph("media\\img\\recovery_bp.png");

	m_priority = eDWP_ITEM;

	CItemManager::GetInstance()->Init(this);

}

void CItem::Update(){

	for (auto it = m_items.begin(); it != m_items.end(); it++){
		
		(*it)->m_pos += CVector2D((*it)->m_velocity * cos((*it)->m_rad), (*it)->m_velocity * sin((*it)->m_rad));

		if ((*it)->m_velocity > 0){
			(*it)->m_velocity -= (*it)->m_friction;
		}
		else{
			(*it)->m_velocity = 0;
		}

		//”½ŽËˆ—
		Reflect((*it));

		if ((*it)->m_animtype > 3)
			(*it)->m_animtype = 0;


		(*it)->m_y_up += 2;
		if ((*it)->m_y_up > 360){
			(*it)->m_y_up = 0;
		}
	}

	Delete();
}

void CItem::Create(){
	int _item_num = CUiManager::GetInstance()->GetUiAdress()->GatComb() / CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetItemDropLevel();
	for (int i = 0; i < _item_num; i++){
		CBaseData* _temp = new CBaseData(CVector2D(rand() % MAP_RANGE_X + 64, rand() % MAP_RANGE_Y + 73), true, radian((rand() % 360)), ITEM_EXRATE, rand() % 4, ITEM_SPEED, ITEM_MASS, ITEM_HP, ITEM_FRICTION, ITEM_COLLISION, ITEM);
		m_items.push_back(new CItemData(*_temp));
	}
}

void CItem::Reflect(CItemData* cd){
	if (cd->m_pos.getY() > MAP_REFLECT_DOWN){
		cd->m_rad = cd->m_rad*(-1);
		cd->m_pos.setY(MAP_REFLECT_DOWN * 2 - cd->m_pos.getY());
		cd->m_animtype++;
	}
	else if (cd->m_pos.getY() < MAP_REFLECT_UP){
		cd->m_rad = cd->m_rad*(-1);
		cd->m_pos.setY(MAP_REFLECT_UP * 2 - cd->m_pos.getY());
		cd->m_animtype++;
	}

	if (cd->m_pos.getX() > MAP_REFLECT_RIGHT){
		cd->m_rad = PI - cd->m_rad;
		cd->m_pos.setX(MAP_REFLECT_RIGHT * 2 - cd->m_pos.getX());
		cd->m_animtype++;
	}
	else if (cd->m_pos.getX() < MAP_REFLECT_LEFT){
		cd->m_rad = PI - cd->m_rad;
		cd->m_pos.setX(MAP_REFLECT_LEFT * 2 - cd->m_pos.getX());
		cd->m_animtype++;
	}
}

void CItem::Draw(){
	for (auto it = m_items.begin(); it != m_items.end(); it++){
		DrawRotaGraph((*it)->m_pos.getX(), (*it)->m_pos.getY() + sin(radian((*it)->m_y_up)) * 6, (*it)->m_exrate, 0/*(*it)->m_rad*/, m_item_img[(*it)->m_animtype], TRUE, FALSE);
	}
}

void CItem::Delete(){
	for (auto it = m_items.begin(); it != m_items.end();){
		if ((*it)->m_living == false){

			it = m_items.erase(it);
			continue;
		}
		it++;
	}
}

void CItem::KillAll(){
	for (auto it = m_items.begin(); it != m_items.end();){
		it = m_items.erase(it);
		continue;
		it++;
	}
}