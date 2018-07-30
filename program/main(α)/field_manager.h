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

	//������
	void Init(CField* field);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CField* GetFrameAdress() const;

	void Update();
};

#endif FIELD_MANAGER_H