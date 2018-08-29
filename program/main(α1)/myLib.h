#ifndef MYLIB_H
#define MYLIB_H

//ヘッダーファイル
#include "DxLib.h"
#include "assert.h"
#include "memory.h"
#include <math.h>
//#include <d3dx11.h>
//#include <d3dx9math.h>

//プリプロセッサ
#define STRUCT_ZERO_CLEAR(X)		memset(&X, 0,sizeof(X))
#define FPS							(60)
#define FRAMETIME					(0.0166666)		//(1.0f/FPS)
#define DEG2RAD						(0.0174528)		//(0.0174f)
#define ARRAY_SIZE(a)				(sizeof(a)/sizeof(a[0]))

const float PI = 3.1415926535f;
const int KEY_DATA = 10;				//KeyNumの個数分

const float PLAYER_COLLISION = 23.0f;				//当たり判定の大きさ
const float PLAYER_KNOCK_BACK_COLLISION = 80.0f;	
const float PLAYER_STAN_COLLISION = 137.0f;
const float PLAYER_BOMB_COLLISION = 80.0f;
const float PLAYER_HURRICANE_COLLISION = 288.0f;

const float ENEMY_COLLISION = 19.0f;
const float ENEMY_LONG_COLLISION = 19.0f;
const float ENEMY_BIG_COLLISION = 44.0f;
const float ENEMY_SMALL_COLLISION = 18.0f;
const float ENEMY_BULLET_COLLISION = 15.0f;
const float ENEMY_ATTACK_BOMB_COLLISION = 21.0f;
const float ENEMY_BOMB_COLLISION = 200.0f;

const float ENEMY_ATTACK_COLLISION = 50.0f;
const float ENEMY_BIG_ATTACK_COLLISION = 85.0f;
const float ENEMY_IMPACK_COLLISION = 180.0f;

const float ENEMY_LOCATE_COLLISION = 170.0f;
const float ENEMY_LONG_LOCATE_COLLISION = 350.0f;
const float ENEMY_LONG_NEAR_COLLISION = 150.0f;
const float ENEMY_BIG_LOCATE_COLLISION = 450.0f;

const float PLAYER_RANGE = 100.0f;					//自機の射程
const float PLAYER_HURRICANE_RANGE = 250.0f;
const float PLAYER_BOMB_RANGE = 200.0f;

const float PLAYER_ATTACK_KNOCK_BACK = 4.0f;		//自機の攻撃系
const float PLAYER_ATTACK_STAN = 200.0f;
const float PLAYER_STAN_EXRATE = 2.3f;
const float PLAYER_ATTACK_BOMB = 20.0f;
const float PLAYER_BOMB_EXRATE = 0.7f;
const float PLAYER_BOMB_RANGE_EXRATE = 0.33f;
const float PLAYER_BOMB_KNOCK_BACK = 14.0f;
const float PLAYER_HURRICANE_KNOCK_BACK = 1.2f;

const float ENEMY_ATTACK_KNOCK_BACK = 9.0f;		//敵の攻撃系
const int ENEMY_ATTACK_DAMAGE = 4;
const int ENEMY_LONG_ATTACK_COOL_TIME = 200;
const float ENEMY_BULLET_ATTACK_DAMAGE = 10.0f;
const float ENEMY_BULLET_KNOCK_BACK = 5.0f;
const float ENEMY_BULLET_EXRATE = 0.5f;
const int ENEMY_ATTACK_COOL_TIME = 70;
const float ENEMY_ATTACK_EXRATE = 1.3f;
const float ENEMY_RANGE = 10.0f;
const int ENEMY_CHANGE = 600;
const int ENEMY_MOVE = 360;
const int ENEMY_WAIT = 600;

const int ENEMY_BIG_ATTACK_COOL_TIME = 190;
const int ENEMY_BIG_ATTACK_STAN = 400;
const float ENEMY_BIG_ATTACK_KNOCK_BACK = 15.0f;
const int ENEMY_BIG_ATTACK_DAMAGE = 25;

//const int ENEMY_SMALL_CHANGE = 600;
const int ENEMY_SMALL_MOVE = 200;
const int ENEMY_SMALL_WAIT = 500;
const int ENEMY_SMALL_DAMAGE = 2;

const int ENEMY_BOMB_MOVE = 200;
const int ENEMY_BOMB_WAIT = 500;
const int ENEMY_BOMB_DAMAGE = 50;
const float ENEMY_BOMB_EXRATE = 1.6;

const int ITEM_CREATE_NUM = 4;						//アイテム系
const float ITEM_STAN_UP = 0.1f;
const float ITEM_KNOCK_BACK_UP = 0.1f;
const float ITEM_BOMB_UP = 0.2f;
const int ITEM_HEEL_UP = 30;

const int TIME_LIMIT = 18000;	//5分				//UI系
const int TIME_SPLIT = 50;		//5分
const float TIME_CIRCLE_SPLIT = 3.6f;

const float BANK_STAN = 600.0f;

const int MAP_RANGE_X = 1152;
const int MAP_RANGE_Y = 544;

const int MAP_REFLECT_RIGHT = 1216;
const int MAP_REFLECT_DOWN = 627;
const int MAP_REFLECT_LEFT = 64;
const int MAP_REFLECT_UP = 73;

enum UpdatePriority{
	UDP_FRAME1, UDP_FRAME2, UDP_CARD, UDP_EFFECT, UDP_FIELD, UDP_UI, UDP_NULL
};

enum DrawPriority{
	DWP_FIELD, DWP_FRAME1, DWP_FRAME2, DWP_CARD, DWP_EFFECT, DWP_UI, DWP_NULL
};

enum KeyNum{
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_Z_PAD_INPUT_2,
	KEY_PAD_INPUT_7, KEY_PAD_INPUT_8, KEY_PAD_INPUT_3, KEY_PAD_INPUT_10,
	KEY_PAD_INPUT_1,
};

//放出、押している、押していない
enum KeyState{	
	RELEASE, PRESSING, SEPARATE,
};

//bool IsKeyTrigger(int _key, int _key_type, int _num);

////ボタン長押し////
//KeyState LongPress(int _key, int _key_type, int _num);

class CKeyData{
private:
	static CKeyData* mp_Instance;

	int key_prev[KEY_DATA];
public:
	CKeyData(){ key_prev[KEY_DATA] = { 0 }; };
	~CKeyData(){};
	static CKeyData* GetInstance();
	static void ClearInstance();

	bool IsKeyTrigger(int _key, int _key_type, int _num);
	int LongPress(int _key, int _key_type, int _num);
	int LongPress2(int _key, int _key_type, int _num);
};

class CVector2D{
private:
	float x;
	float y;
public:
	CVector2D() : x(0), y(0){};
	CVector2D(float pos_x, float pos_y) : x(pos_x), y(pos_y) {};
	inline float getX(void)const{ return x; }
	inline float getY(void)const{ return y; }
	inline void setX(float pos_x){ x = pos_x; }
	inline void setY(float pos_y){ y = pos_y; }
	inline void addX(float pos_x){ x += pos_x; }
	inline void addY(float pos_y){ y += pos_y; }
	CVector2D& operator+=(const CVector2D& ope);
	CVector2D& operator-=(const CVector2D& ope);
	CVector2D& operator=(const CVector2D& ope);
	CVector2D& operator+(const CVector2D& ope);
	CVector2D& operator-(const CVector2D& ope);
	bool operator==(const CVector2D& ope);
	bool operator!=(const CVector2D& ope);
};

//円状判定処理
bool IsHitCircle(float c1, float c2, CVector2D pos1, CVector2D pos2);

//変更したい値,押されたボタン,最大値,最小値
int MyLibSelect(int &_number, int key, int _max, int _min);

//ベクトルの正規化
void MyVec2Normalize(CVector2D &out_pos, CVector2D &in_pos);
void MyVec2Normalize(float &in_x, float &in_y,float &out_x,float &_out_y);

//内積
float MyVec2Dot(float &in_v1, CVector2D &in_pos2);

//x,yから角度の算出
float PosRad(float _x, float _y);
float PosRad(CVector2D _pos);

//二点間から角度算出
float PosRad(CVector2D &_pos1, CVector2D &_pos2);

//FPS
void Fps();

//角度からラジアンに
inline float radian(float _degree){ return _degree * PI / 180.0f; };
//ラジアンから角度に
inline float degree(float _radian){ return _radian * 180.0f / PI; };


#endif MYLIB_H
