#ifndef GAMECLEAR_SCREEN_H
#define GAMECLEAR_SCREEN_H

//�w�b�_�[�t�@�C��
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//�v���g�^�C�v
struct GameData;

//�^�C�g���X�N���[���N���X
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
