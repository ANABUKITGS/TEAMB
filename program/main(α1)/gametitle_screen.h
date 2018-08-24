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
	int title_img[2];
	int title_text_img;
	SCREEN m_state;
};

#endif GAMETITLE_SCREEN_H
