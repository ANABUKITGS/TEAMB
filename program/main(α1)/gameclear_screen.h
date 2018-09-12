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
	int m_type;
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
	int m_enemy_img[5][88];
	int m_gameclear_chara_img[5];
	int m_gameclear_text_img;

	int m_timer;
	int m_x, m_xx;
	float m_ac;
	int m_animcounter;

	CClearData m_clear[6];
	SCREEN m_state;
};

#endif GAMECLEAR_SCREEN_H
