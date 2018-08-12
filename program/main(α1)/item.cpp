#include "item.h"
#include "item_manager.h"
#include "enemy_manager.h"

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
	m_item_img[STAN_ITEM] = LoadGraph("media\\img\\pow_up_stan.png");
	m_item_img[KNOCK_BACK_ITEM] = LoadGraph("media\\img\\pow_up_kb.png");
	m_item_img[BOMB_ITEM] = LoadGraph("media\\img\\pow_up_bomb.png");
	m_item_img[HEEL_ITEM] = LoadGraph("media\\img\\heel.png");

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

	Create();

	Delete();
}

void CItem::Create(){
	int _item_num = CEnemyManager::GetInstance()->GetEnemyAdress()->GetDeadCount() / ITEM_CREATE_NUM;
	for (int i = 0; i < _item_num; i++){
		CBaseData* _temp = new CBaseData(CVector2D(rand() % 1200 + 30, rand() % 660 + 30), true, radian((rand() % 360)), ITEM_EXRATE, rand() % 4, ITEM_SPEED, ITEM_MASS, ITEM_HP, ITEM_FRICTION, ITEM_COLLISION, ITEM);
		m_items.push_back(new CItemData(*_temp));
	}
}

void CItem::Reflect(CItemData* cd){
	if (cd->m_pos.getY() > 720){
		cd->m_rad = cd->m_rad*(-1);
		cd->m_pos.setY(720 * 2 - cd->m_pos.getY());
		cd->m_animtype++;
	}
	else if (cd->m_pos.getY() < 0){
		cd->m_rad = cd->m_rad*(-1);
		cd->m_pos.setY(-cd->m_pos.getY());
		cd->m_animtype++;
	}

	if (cd->m_pos.getX() > 1280){
		cd->m_rad = PI - cd->m_rad;
		cd->m_pos.setX(1280 * 2 - cd->m_pos.getX());
		cd->m_animtype++;
	}
	else if (cd->m_pos.getX() < 0){
		cd->m_rad = PI - cd->m_rad;
		cd->m_pos.setX(-cd->m_pos.getX());
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