#ifndef GAMECLEAR_SCREEN_H
#define GAMECLEAR_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//プロトタイプ
struct GameData;

//タイトルスクリーンクラス
class CGameClearScreen : public CScreen
{
public:
	CGameClearScreen();
	~CGameClearScreen();
	SCREEN GetNextScreen();
	void Load();
	void Release();
	void Init();
	void Update();
	void Draw();
private:
	int gameclear_text_img;
	int gameclear_img[27];
	float m_ac;
	int m_animcounter;
	SCREEN m_state;
};

#endif GAMECLEAR_SCREEN_H
