
#ifndef GAME_H
#define GAME_H

//ヘッダーファイル
#include "mylib.h"
#include "game_data.h"
#include <time.h>

//プロトタイプ
enum SCREEN;
class CScreen;

//ゲームクラス
class CGame
{
public:
	CGame();
	~CGame();
	void Init();
	void Dest();
	void Update();
	void Draw();
private:
	CScreen*	m_pScreen;	//現在のスクリーンクラスのポインタ
	GameData	m_GameData;	//画面情報
};
#endif GAME_H
