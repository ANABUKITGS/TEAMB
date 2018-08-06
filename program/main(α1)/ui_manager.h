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

	//初期化
	void Init(CUi* ui);

	//終了処理
	void Finish();

	//データの取得
	CUi* GetUiAdress() const;

	void Update();
};

#endif UI_MANAGER_H