#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "effect.h"

class CEffectManager{
private:
	static CEffectManager* mp_Instance;
	CEffect *m_effect;
	CEffectManager();
public:
	~CEffectManager();

	static CEffectManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CEffect* effect);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CEffect* GetEffectAdress() const;

	void Update();
};

#endif EFFECT_MANAGER_H