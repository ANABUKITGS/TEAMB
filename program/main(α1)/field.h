#ifndef FIELD_H
#define FIELD_H

#include <DxLib.h>
#include "myLib.h"
#include "task.h"
#include "base_data.h"

const int BUFSIZE = 256;
const int MAP_HEIGHT = 11;
const int MAP_WIDTH = 20;
const int MAP_SPACE = 9;
const int MAP_CHIP_SIZE = 64;
const int MAP_HALFCHIP_SIZE = 32;

enum MapNum{
	GROUND, WALL,CORNER_WALL
};

enum MapType{
	M_NORMAL,M_BOSS
};

class CFieldData : public CBaseData{
public:
	CFieldData();
	~CFieldData();
};

class CField : public CTask{
private:
	CFieldData m_field_data[MAP_WIDTH][MAP_HEIGHT];
	int m_feild_img[3];
	int m_field_type;
public:
	CField();
	~CField();
	void Update();
	void Draw();
	void SetFieldType(int _type){ m_field_type = _type; };
	int GetFieldType(){ return m_field_type; };
};

#endif FIELD_H