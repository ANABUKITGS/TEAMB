#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include "field.h"

class CFieldManager{
private:
	static CFieldManager* mp_Instance;
	CField *m_field;
	CFieldManager();
public:
	~CFieldManager();

	static CFieldManager* GetInstance();
	static void ClearInstance();

	//初期化
	void Init(CField* field);

	//終了処理
	void Finish();

	//データの取得
	CField* GetFrameAdress() const;

	void Update();
};

#endif FIELD_MANAGER_H