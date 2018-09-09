#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include "myLib.h"

const int SOUND_NUM = 22+1+10;

enum SOUND_NAME{
	TITLE_BGM = 0, GAME_BGM1, GAME_BGM2, GAMEOVER_BGM, GAMECLEAR_BGM,
	T_SELECT_SE1, S_ATTACK_STAN, S_ATTACK_WIND, S_ATTACK_BOMB, 
	S_ATTACK_CHANGE, S_P_AVOID, S_ITEM_GET, S_HEEL_GET, S_E_DEAD, 
	S_P_DAMAGE, S_PV_ATTACK1, S_PV_ATTACK2, S_PV_ATTACK3,S_PV_DAMAGE1,S_PV_DAMAGE2,
	S_PV_AVOID1, S_PV_AVOID2, S_PV_ITEM_GET,
	S_E_NORMAL, S_ITEM_DROP, S_E_DROP, S_P_TELEPORT, S_E_SMALL, S_E_BULLET, S_E_RANGE, S_E_BIG,
	S_B_ATTACK, S_E_BOMB
};

class CSoundData{
private:
	int sound[SOUND_NUM];
public:
	CSoundData();
	~CSoundData();
	int getSound(int name){ return sound[name]; };
};

#endif SOUNDDATA_H