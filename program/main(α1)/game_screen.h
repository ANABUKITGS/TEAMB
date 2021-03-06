
#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"

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
	bool m_clear_flag;
	bool m_over_flag;
	//int m_text_img[2];
};

#endif GAME_SCREEN_H