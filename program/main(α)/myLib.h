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
//#define STRUCT_ZERO_CLEAR(X)		memset(&X, 0,sizeof(X))
#define FPS							(60)
#define FRAMETIME					(0.0166666)		//(1.0f/FPS)
#define DEG2RAD						(0.0174528)		//(0.0174f)
#define ARRAY_SIZE(a)				(sizeof(a)/sizeof(a[0]))

const float PI = 3.1415926535f;
const int KEY_DATA = 7;				//KeyNumの個数分

const float PLAYER_KNOCK_BACK_COLLISION = 80.0f;
const float PLAYER_STAN_COLLISION = 137.0f;
const float PLAYER_BOMB_COLLISION = 152.0f;
const float ENEMY_ATTACK_COLLISION = 30.0f;

const float PLAYER_COLLISION = 25.0f;
const float ENEMY_COLLISION = 15.0f;
const float ENEMY_LOCATE_COLLISION = 200.0f;;

const float PLAYER_RANGE = 100.0f;
const float PLAYER_BOMB_RANGE = 150.0f;

const float PLAYER_ATTACK_KNOCK_BACK = 4.0f;
const float PLAYER_ATTACK_STAN = 120.0f;
const float PLAYER_STAN_EXRATE = 1.5f;
const float PLAYER_ATTACK_BOMB = 32.0f;
const float PLAYER_BOMB_EXRATE = 1.0f;
const float PLAYER_BOMB_KNOCK_BACK = 8.0f;

const int ENEMY_CHANGE = 600;
const int ENEMY_MOVE = 360;
const int ENEMY_WAIT = 600;

const int ITEM_CREATE_NUM = 10;

enum UpdatePriority{
	UDP_FRAME1, UDP_FRAME2, UDP_CARD, UDP_EFFECT, UDP_FIELD, UDP_UI, UDP_NULL
};

enum DrawPriority{
	DWP_FIELD, DWP_FRAME1, DWP_FRAME2, DWP_CARD, DWP_EFFECT, DWP_UI, DWP_NULL
};

enum KeyNum{
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_Z_PAD_INPUT_1, KEY_PAD_INPUT_7, KEY_PAD_INPUT_8
};

enum KeyState{	//放出、押している、押していない
	RELEASE, PRESSING, SEPARATE,
};

bool IsXKeyTrigger(int key);

bool IsKeyTrigger(int _key, int _key_type, int _num);

////ボタン長押し////
KeyState LongPress(int _key, int _key_type);

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
