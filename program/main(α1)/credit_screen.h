#ifndef CREDIT_SCREEN_H
#define CREDIT_SCREEN_H

//�w�b�_�[�t�@�C��
#include "myLib.h"
#include "screen.h"
#include "game_data.h"

//�v���g�^�C�v
struct GameData;

//�^�C�g���X�N���[���N���X
class CCreditScreen : public CScreen
{
public:
	CCreditScreen();
	~CCreditScreen();
	SCREEN GetNextScreen();
	void Load();
	void Release();
	void Init();
	void Update();
	void Draw();
private:
	int credit_img;
	int credit_text_img;
	SCREEN m_state;
};

#endif CREDIT_SCREEN_H
