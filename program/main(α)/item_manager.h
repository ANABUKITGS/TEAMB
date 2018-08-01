#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "item.h"

class CItemManager{
private:
	static CItemManager* mp_Instance;
	CItem *m_item;
	CItemManager();
public:
	~CItemManager();

	static CItemManager* GetInstance();
	static void ClearInstance();

	//初期化
	void Init(CItem* item);

	//終了処理
	void Finish();

	//データの取得
	CItem* GetItemAdress() const;

	void Update();
};

#endif ITEM_MANAGER_H