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

	//������
	void Init(CItem* item);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CItem* GetItemAdress() const;

	void Update();
};

#endif ITEM_MANAGER_H