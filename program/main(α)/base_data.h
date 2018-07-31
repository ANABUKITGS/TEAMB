
/*

全ての元となるパラメーター達

*/

#ifndef _BASE_DATA_H_
#define _BASE_DATA_H_

#include "myLib.h"
#include <vector>
#include <list>

using namespace std;

enum CHARA_TYPE{
	PLAYER,ENEMY,ITEM
};

class CBaseData{
public:
	CVector2D m_pos;		//座標
	bool m_living;			//生きているかどうか
	float m_alpha;			//透過値
	float m_rad;			//角度（ラジアン）
	float m_exrate;			//大きさ
	int m_animtype;			//アニメーションの種類
	float m_velocity;		//速度
	float m_mass;			//質量
	int m_amine_rate;		//アニメーション
	int m_hp;				//体力
	float m_friction;		//摩擦
	float m_collision;		//当たり判定の大きさ
	bool m_control;			//操作可能
	int m_type;				//種類
	int m_timer;			//何らかの時間
	int m_damage;			//ダメージ量
	CBaseData();
	//CharaDataに保存
	CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);
	//保存されない HPがない
	CBaseData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, float _friction,int _type);
	//alphaがない
	CBaseData(CVector2D _pos, bool _living, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, int _type);
	~CBaseData();
	void Update();
};

//各データの管理（エネミー、プレイヤー、アイテムの管理）
class CCharaData{
private:
	static CCharaData* m_pInstance;
	list<CBaseData*> m_chara_data;
	int m_ehp_img[2];
	int m_hhp_img;
public:
	
	CCharaData();
	~CCharaData(){};

	//衝突時の反射
	void CBank();
	//全削除
	void KillAll();			
	//数
	void Counter();			
	//削除
	void Delete();
	//描画
	void Draw();

	//タスクマネージャーのデータの取得
	//これを使うとマネージャーのデータを使うことが出来る
	static CCharaData* GetInstance();

	//格納されているものを削除
	static void ClearInstance();

	//リストにタスク格納処理
	void AddTaskInner(CBaseData* task);

	list<CBaseData*> *GetCharaData(){ return &m_chara_data; };
};

#endif _BASE_DATA_H_