
#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"
//#include "map.h"
#include "player.h"

//プロトタイプ
struct GameData;

//セレクトスクリーンクラス
class CGameScreen : public CScreen
{
public:
	CGameScreen();
	~CGameScreen();
	SCREEN GetNextScreen();
	void Load();
	void Release();
	void Init();
	void Update();
	void Draw();
private:
	SCREEN m_state;
	//Map		map;
};

#endif GAME_SCREEN_H