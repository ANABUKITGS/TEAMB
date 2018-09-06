#ifndef GAMECLEAR_SCREEN_H
#define GAMECLEAR_SCREEN_H

//ヘッダーファイル
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//プロトタイプ
struct GameData;

const float ENEMY = 2.0f;

class CClearData{
public:
	CVector2D m_pos;
	int m_animtype;
};

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
	int m_enemy_img[5][88];

	int gameclear_chara_img[5];
	int gameclear_t_img;


	int m_timer;
	int m_title_num;

	float m_ac;
	int m_animcounter;

	CClearData m_clear[5];

	SCREEN m_state;
};

#endif GAMECLEAR_SCREEN_H
