
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
			m_field_data[x][y].m_pos = CVector2D(MAP_HALFCHIP_SIZE + x * MAP_CHIP_SIZE, MAP_SPACE + MAP_HALFCHIP_SIZE + y * MAP_CHIP_SIZE);
			m_field_data[x][y].m_exrate = 1;

			if (x == 19 && y > 0 && y < 10){
				m_field_data[x][y].m_rad = radian(180);
			}
			else if (y == 0 && x > 0 && x < 19){
				m_field_data[x][y].m_rad = radian(90);
			}
			else if (y == 10 && x > 0 && x < 19){
				m_field_data[x][y].m_rad = radian(270);
			}

			else if (x == 19 && y == 10){
				m_field_data[x][y].m_rad = radian(180);
			}
			else if (x == 19 && y == 0 ){
				m_field_data[x][y].m_rad = radian(90);
			}
			else if ( x == 0 && y == 10 ){
				m_field_data[x][y].m_rad = radian(270);
			}

		}
	}
	FileRead_close(fh);

	m_feild_img[GROUND] = LoadGraph("media\\img\\field.jpg", FALSE);
	m_feild_img[WALL] = LoadGraph("media\\img\\wall_moss.jpg", FALSE);
	m_feild_img[CORNER_WALL] = LoadGraph("media\\img\\corner_wall.jpg", FALSE);

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
				m_field_data[x][y].m_exrate, m_field_data[x][y].m_rad, m_feild_img[m_field_data[x][y].m_animtype], TRUE, FALSE);
		}
	}
}