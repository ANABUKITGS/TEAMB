#ifndef FIELD_H
#define FIELD_H

#include <DxLib.h>
#include "myLib.h"
#include "task.h"
#include "base_data.h"

const int BUFSIZE = 256;
const int MAP_HEIGHT = 11;
const int MAP_WIDTH = 20;
const int MAP_SPACE = 10;
const int MAP_CHIP_SIZE = 64;

class CFieldData : public CBaseData{
public:
	CFieldData();
	~CFieldData();
};

class CField : public CTask{
private:
	CFieldData m_field_data[MAP_WIDTH][MAP_HEIGHT];
	int m_feild_img[2];
public:
	CField();
	~CField();
	void Update();
	void Draw();
};

#endif FIELD_H