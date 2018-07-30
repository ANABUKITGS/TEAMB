
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
		}
	}
	FileRead_close(fh);

	m_feild_img[0] = LoadGraph("media\\img\\field64.jpg");
	m_feild_img[1] = LoadGraph("media\\img\\field_stone.png");

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
			DrawGraph(m_field_data[x][y].m_pos.getX(), m_field_data[x][y].m_pos.getY(),
				m_feild_img[m_field_data[x][y].m_animtype], TRUE);
		}
	}
}