#ifndef SCREEN_H
#define SCREEN_H

//ゲームスクリーンの種類
enum SCREEN{
	TITLE_SCREEN,
	GAME_SCREEN,
	GAMEOVER_SCREEN,
	GAMECLEAR_SCREEN,
	CREDIT_SCREEN
};

class CScreen
{
public:
	virtual SCREEN GetNextScreen() = 0;		//次のスクリーンを示す
	CScreen(){}
	virtual ~CScreen(){}
	virtual void Init(){}
	virtual void Load(){}
	virtual void Release(){}
	virtual void Update(){}
	virtual void Draw(){}
	virtual void Dest(){}
};

#endif SCREEN_H