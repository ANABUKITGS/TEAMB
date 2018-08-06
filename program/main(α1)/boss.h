#ifndef BOSS_H
#define BOSS_H

#include "task.h"
#include "base_data.h"
#include <vector>
#include <list>

const float BOSS_EXRATE = 8.0f;
const float BOSS_SPEED = 0.0f;

using namespace std;

enum BossType{
	body, leftarm, rightarm, lefhand, righand
};

class CBossData : public CBaseData{
public:
	CBossData();
	//座標		・生きてる		・角度		・大きさ	・アニメーション	・速度			・質量		・体力			・摩擦	・当たり判定の大きさ	・種類
	CBossData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);

	//座標		・生きてる		・透過値		・角度		・大きさ	・アニメーション	・速度			・質量		・体力			・摩擦	・当たり判定の大きさ	・種類
	//CBossData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type);
	CBossData(CBaseData _temp);
	~CBossData(){};
	float m_yup = 0;
};

class CBoss : public CTask{
private:
	vector<CBossData> m_bo;
	list<CBossData*> m_bos;
	CBossData m_bossy;
	float i;
	int m_boss_img[5];
	int m_boss_body_img;
	int m_boss_leftarm_img;
	int m_boss_rightarm_img;
	int u = 0;
public:
	CBoss();
	~CBoss(){};
	void Update();
	void Move(CBossData &cd, CVector2D &_pos);
	void Draw();
	//vector<CBossData> *GetBossData(){ return &m_bo; };
};


#endif BOSS_H