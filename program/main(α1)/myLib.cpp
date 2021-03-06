#include "myLib.h"

CKeyData* CKeyData::mp_Instance = nullptr;

//Vector2Dへの加算
CVector2D& CVector2D::operator+=(const CVector2D& ope){
	x += ope.x;
	y += ope.y;
	return *this;
}

//Vector2Dからの減算
CVector2D& CVector2D::operator-=(const CVector2D& ope){
	x -= ope.x;
	y -= ope.y;
	return *this;
}

//Vector2Dへの代入
CVector2D& CVector2D::operator=(const CVector2D& ope){
	x = ope.x;
	y = ope.y;
	return *this;
}

CVector2D& CVector2D::operator+(const CVector2D& ope){
	x = x + ope.x;
	y = y + ope.y;
	return *this;
}

CVector2D& CVector2D::operator-(const CVector2D& ope){
	x = x - ope.x;
	y = y - ope.y;
	return *this;
}

//Vector2Dの比較
bool CVector2D::operator==(const CVector2D& ope){
	if (x == ope.x&&
		y == ope.y){
		return TRUE;
	}
	return FALSE;
}

//Vector2Dの比較
bool CVector2D::operator!=(const CVector2D& ope){
	if (x != ope.x||
		y != ope.y){
		return TRUE;
	}
	return FALSE;
}

//////ボタン系//////

CKeyData* CKeyData::GetInstance(){
	if (mp_Instance == nullptr)
	{
		mp_Instance = new CKeyData();
	}
	return mp_Instance;
}

void CKeyData::ClearInstance(){
	if (mp_Instance != nullptr) delete mp_Instance;
}


//ボタン入力処理(長押しが効かない)
bool CKeyData::IsKeyTrigger(int _key, int _key_type, int _num){
	if (_key & _key_type){
		if (key_prev[_num] == false){
			key_prev[_num] = true;
			return true;
		}
	}
	else{
		key_prev[_num] = false;
	}
	return false;
}

//ボタン入力処理
bool CKeyData::IsKeyTrigger2(int _key, int _key_type){
	if (_key & _key_type){
		return true;
	}
	else{
		return false;
	}
}

//ボタン長押し処理	放出(RELEASE)、押している(PRESSING)、押していない(SEPARATE)
int CKeyData::LongPress(int _key, int _key_type, int _num){
	static bool _flag1;
	static bool _flag2;

	if (_key & _key_type){
		_flag2 = true;
		key_prev[_num] = PRESSING;
		return key_prev[_num];
	}
	else{
		if (_flag2 == true)_flag1 = true;
	}

	if (_flag1){
		_flag1 = false;
		_flag2 = false;
		key_prev[_num] = RELEASE;
		return key_prev[_num];
	}
	else{
		key_prev[_num] = SEPARATE;
		return key_prev[_num];
	}
}


int CKeyData::LongPress2(int _key, int _key_type, int _num){
	static bool _flag1;
	static bool _flag2;

	if (_key & _key_type){
		_flag2 = true;
		key_prev[_num] = PRESSING;
		return key_prev[_num];
	}
	else{
		if (_flag2 == true)_flag1 = true;
	}

	if (_flag1){
		_flag1 = false;
		_flag2 = false;
		key_prev[_num] = RELEASE;
		return key_prev[_num];
	}
	else{
		key_prev[_num] = SEPARATE;
		return key_prev[_num];
	}
}

///////////////////

bool IsHitCircle(float c1, float c2, CVector2D pos1, CVector2D pos2){
	float hlength = c1 + c2;
	float xlength = pos1.getX() - pos2.getX();
	float ylength = pos1.getY() - pos2.getY();

	if (hlength * hlength >= xlength*xlength + ylength * ylength){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

////正規化
void MyVec2Normalize(CVector2D &out_pos, CVector2D &in_pos){
	CVector2D _temp;
	_temp.setX(in_pos.getX() / sqrt(in_pos.getX()*in_pos.getX() + in_pos.getY()*in_pos.getY()));
	_temp.setY(in_pos.getY() / sqrt(in_pos.getX()*in_pos.getX() + in_pos.getY()*in_pos.getY()));
	out_pos = _temp;
}

////正規化
void MyVec2Normalize(float &in_x, float &in_y, float &out_x, float &out_y){
	float _x, _y;
	_x = in_x / sqrt(in_x * in_x + in_y * in_y);
	_y = in_y / sqrt(in_x * in_x + in_y * in_y);
	out_x = _x;
	out_y = _y;
}

//内積
float MyVec2Dot(float &in_v1, CVector2D &in_pos2){
	float temp;
	temp = in_v1 * (in_pos2.getX()*in_pos2.getX() - in_pos2.getY()*in_pos2.getY());
	return temp;
}

//x,yから角度の算出
float PosRad(float _x, float _y){
	float _rad = atan2(_y,_x);
	if (_rad < 0)_rad = _rad + 2 * PI;
	return _rad;
}
//x,yから角度の算出
float PosRad(CVector2D _pos){
	float _rad = atan2(_pos.getY(), _pos.getX());
	if (_rad < 0)_rad = _rad + 2 * PI;
	return _rad;
}

//二点から角度算出
float PosRad(CVector2D &_pos1, CVector2D &_pos2){
	float _rad = atan2(_pos2.getY() - _pos1.getY(), _pos2.getX() - _pos1.getX());
	if (_rad < 0)_rad = _rad + 2 * PI;
	return _rad;
}

void Fps(){
	int color_white = GetColor(255, 255, 255);//色取得
	static int FpsTime[2] = { 0, }, FpsTime_i = 0;
	static double Fps = 0.0;
	if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();                           //1周目の時間取得
	if (FpsTime_i == 49){
		FpsTime[1] = GetNowCount();                           //50周目の時間取得
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
		FpsTime_i = 0;
	}
	else
		FpsTime_i++;                                          //現在何周目かカウント
	if (Fps != 0)
		DrawFormatString(1200, 700, color_white, "FPS %.1f", Fps); //fpsを表示
}

int MyLibSelect(int &_number, int key, int _max, int _min){
	int _change_num = 0;
	if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_UP, KEY_UP)){
		_number--;
		_change_num = 1;
	}
	else if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_DOWN, KEY_DOWN)){
		_number++;
		_change_num = 1;
	}
	else if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_RIGHT, KEY_RIGHT)){
		//_number--;
		_change_num = 3;
	}
	else if (CKeyData::GetInstance()->IsKeyTrigger(key, PAD_INPUT_LEFT, KEY_LEFT)){
		//_number++;
		_change_num = 3;
	}
	if (_number < _min){
		_number = _max;
	}
	else if (_number > _max){
		_number = _min;
	}
	return _change_num;
}

void IsFadeIn_Out(int& alpha, bool& flag, int permeability){
	if (flag == false){
		alpha += permeability;
	}
	else{
		alpha -= permeability;
	}
	if (alpha >= 256){
		flag = true;
	}
	else if (alpha <= 0){
		flag = false;
	}
}