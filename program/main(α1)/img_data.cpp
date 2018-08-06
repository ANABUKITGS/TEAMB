#include "img_data.h"
#include "img_data_manager.h"

CImg::CImg(){
	int _img_amout[] = {IMG_CARD,IMG_FRAME,IMG_SELECT};
	for (int i = 0; i < IMG_TYPE; i++){
		m_img_amout[i] = _img_amout[i];
	}
	char *item[] = { "acd_x3.png", "ch01.png","cd_sele01.png","move_select.png"};
	char buf[256];
	for (int j = 0,_num = 0; j < IMG_TYPE; j++){
		for (int i = 0; i < m_img_amout[j]; i++,_num++){
			sprintf_s(buf, "media\\img\\%s", item[_num]);
			m_img[j][i] = LoadGraph(buf);
		}
	}
	//m_img[] = LoadGraph("media\\img\\acd_x3.png");
	CImgDataManager::GetInstance()->Init(this);
}

