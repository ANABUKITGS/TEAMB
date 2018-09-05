#ifndef GAMETITLE_SCREEN_H
#define GAMETITLE_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//プロトタイプ
struct GameData;

class CTitleData{
public:
	CVector2D m_pos;
	int m_alpha;
	float m_add_move;
};

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
	int title1_img[4];
	int title_text_img;

	int m_timer;
	int m_title_num;
	CTitleData m_title[4];
	
	SCREEN m_state;
};

#endif GAMETITLE_SCREEN_H
