#ifndef GAMEOVER_SCREEN_H
#define GAMEOVER_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//プロトタイプ
struct GameData;

//タイトルスクリーンクラス
class CGameOverScreen : public CScreen
{
public:
	CGameOverScreen();
	~CGameOverScreen();
	SCREEN GetNextScreen();
	void Load();
	void Release();
	void Init();
	void Update();
	void Draw();
private:
	int m_timer;
	int m_gameover_img;
	int m_gameover_text_img;
	SCREEN m_state;
};

#endif GAMEOVER_SCREEN_H
