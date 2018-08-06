#ifndef CHANGE_MANAGER_H
#define CHANGE_MANAGER_H

#include "change.h"

class CChangeManager{
private:
	static CChangeManager* mp_Instance;
	CChange *m_change;
	CChangeManager();
public:
	~CChangeManager();

	static CChangeManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CChange* change);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CChange* GetChangeAdress() const;

	void Update();
};

#endif CHANGE_MANAGER_H