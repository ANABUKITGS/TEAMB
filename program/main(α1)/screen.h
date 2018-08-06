#ifndef SCREEN_H
#define SCREEN_H

//�Q�[���X�N���[���̎��
enum SCREEN{
	TITLE_SCREEN,
	GAME_SCREEN,
};

class CScreen
{
public:
	virtual SCREEN GetNextScreen() = 0;		//���̃X�N���[��������
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