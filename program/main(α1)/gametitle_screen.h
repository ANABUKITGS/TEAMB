#ifndef GAMETITLE_SCREEN_H
#define GAMETITLE_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//プロトタイプ
struct GameData;

//タイトルスクリーンクラス
class CGameTitleScreen : public CScreen
{
public:
	CGameTitleScreen();
	~CGameTitleScreen();
	SCREEN GetNextScreen();
	void Load();
	void Release();
	void Init();
	void Update();
	void Draw();
private:
	SCREEN m_state;
};

#endif GAMETITLE_SCREEN_H
