
#include "task_manager.h"
#include "field_manager.h"

CFieldData::CFieldData(){
}

CFieldData::~CFieldData(){

}

CField::CField(){
	char buf[BUFSIZE];
	sprintf_s(buf, 256, "media\\txt\\map.txt");
	int fh = FileRead_open(buf);
	for (int y = 0; y < MAP_HEIGHT; y++){
		FileRead_gets(buf, 256, fh);
		for (int x = 0; x < MAP_WIDTH; x++){
			m_field_data[x][y].m_animtype = (int)(buf[x] - '0');
			m_field_data[x][y].m_pos = CVector2D(x * MAP_CHIP_SIZE,MAP_SPACE + y * MAP_CHIP_SIZE);
			if (x == 0 && y > 0 && y < 10){
				m_field_data[x][y].m_rad = 0;
			}
			else if (x == 20 && y > 0 && y < 10){
				m_field_data[x][y].m_rad = radian(180);
			}
			else if (y == 0 && x > 0 && x < 20){
				m_field_data[x][y].m_rad = radian(90);
			}
			else if (y == 11 && x > 0 && x < 20){
				m_field_data[x][y].m_rad = radian(270);
			}
		}
	}
	FileRead_close(fh);

	m_feild_img[GROUND] = LoadGraph("media\\img\\field.png");
	m_feild_img[WALL] = LoadGraph("media\\img\\wall_moss.png");
	m_feild_img[CORNER_WALL] = LoadGraph("media\\img\\corner_wall.png");
	//m_feild_img[1] = LoadGraph("media\\img\\field_stone.png");

	m_priority = eDWP_FIELD;
	CFieldManager::GetInstance()->Init(this);
}

CField::~CField(){
}

void CField::Update(){
}

void CField::Draw(){
	for (int y = 0; y < MAP_HEIGHT; y++){
		for (int x = 0; x < MAP_WIDTH; x++){
			DrawRotaGraph(m_field_data[x][y].m_pos.getX(), m_field_data[x][y].m_pos.getY(),
				m_field_data[x][y].m_exrate, m_field_data[x][y].m_rad, m_feild_img[m_field_data[x][y].m_animtype], FALSE, FALSE);
		}
	}
}