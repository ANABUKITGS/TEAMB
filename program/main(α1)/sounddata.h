#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include "myLib.h"

const int SOUND_NUM = 14+1;

enum SOUND_NAME{
	TITLE_BGM = 0, GAME_BGM1, GAME_BGM2, GAMEOVER_BGM, GAMECLEAR_BGM,
	T_SELECT_SE1, S_ATTACK_STAN, S_ATTACK_WIND, S_ATTACK_BOMB, 
	S_ATTACK_CHANGE, S_P_AVOID, S_ITEM_GET, S_HEEL_GET, S_E_DEAD, 
	P_DAMAGE
};

class CSoundData{
private:
	int sound[SOUND_NUM];
public:
	CSoundData();
	~CSoundData();
	int getSound(SOUND_NAME name){ return sound[name]; };
};

#endif SOUNDDATA_H