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

	//初期化
	void Init(CEffect* effect);

	//終了処理
	void Finish();

	//データの取得
	CEffect* GetEffectAdress() const;

	void Update();
};

#endif EFFECT_MANAGER_H