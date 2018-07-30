#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "ui.h"

class CUiManager{
private:
	static CUiManager* mp_Instance;
	CUi *m_ui;
	CUiManager();
public:
	~CUiManager();

	static CUiManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CUi* ui);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CUi* GetUiAdress() const;

	void Update();
};

#endif UI_MANAGER_H