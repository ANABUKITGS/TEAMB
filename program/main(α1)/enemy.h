#ifndef ENEMY_H
#define ENEMY_H

#include "task.h"
#include "base_data.h"
#include <vector>

using namespace std;

const float ENEMY_EXRATE = 0.9f;
const float ENEMY_LONG_EXRATE = 1.1f;

const float ENEMY_NORMAL_SPEED = 1.3f;
const float ENEMY_LONG_SPEED = 1.5f;
const float ENEMY_BULLET_SPEED = 1.5f;
const float ENEMY_BIG_SPEED = 0.7f;
const float ENEMY_SMALL_SPEED = 2.5f;
const float ENEMY_BOMB_SPEED = 1.0f;

const float ENEMY_NORMAL_MASS = 1.0f;
const float ENEMY_LONG_MASS = 1.5f;
const float ENEMY_BULLET_MASS = 1.0f;
const float ENEMY_BIG_MASS = 4.5f;
const float ENEMY_SMALL_MASS = 0.5f;
const float ENEMY_BOMB_MASS = 1.0f;

const float ENEMY_FRICTION = 0.1f;

const int ENEMY_NORMAL_HP = 64;
const int ENEMY_LONG_HP = 64;
const int ENEMY_BULLET_HP = 30;
const int ENEMY_BIG_HP = 192;
const int ENEMY_SMALL_HP = 16; //16;
const int ENEMY_BOMB_HP = 16;

const int MAX_ENEMY = 20;
const int ENEMY_TYPE = 5;
const int ENMEY_IMG_NUM = 6;

/*enum EnemyDirection{
	ENEMY_DOWN, ENEMY_LEFT = 6, ENEMY_RIGHT = 12, ENEMY_UP = 18
};*/

enum EnemyType{
	NORMAL,LONG_RANGE,BULLET,MAGIC_SQUARE,BIG,SMALL,E_BOMB
};

enum EnemyDirection{
	ENEMY_DOWN, ENEMY_DL = 2, ENEMY_LEFT = 4, ENEMY_DR = 6,
	ENEMY_RIGHT = 8, ENEMY_UL = 10, ENEMY_UP = 12, ENEMY_UR = 14
};

class CEMoveTable{
public:
	int m_key;
	int m_type;
	float m_temp;
};

class CEnemyRadTable{
public:
	int m_rad;
	int m_max_rad;			//�ő�p
	int m_min_rad;			//�ŏ��p
	int m_type;				//�摜�̎��
};

class CEnemyData;

class CBaseEemeyMove{
public:
	virtual void Move(CEnemyData *cd, CVector2D &_pos){};
};
class CBaseEemeyAttack{
public:
	virtual void Attack(CEnemyData *cd){};
};

class CECreateTable{
public:
	int m_num;
	int m_type;
	float m_exrate;
	float m_speed;
	float m_mass;
	int m_hp;
	float m_collision;
	int m_division;
	CBaseEemeyMove *m_BEMove;
	CBaseEemeyAttack *m_BEAttack;
};

class CEnemyData : public CBaseData{
public:
	CEnemyData();
	CEnemyData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, float _velocity, float _mass, int _hp, float _friction, float _collision, float _type, CBaseEemeyMove *_BEMove, CBaseEemeyAttack *_BEAttack);
	CEnemyData(CBaseData _temp, CVector2D _move_pos, int _invincible, CBaseEemeyMove *_BEMove, CBaseEemeyAttack *_BEAttack);
	~CEnemyData(){};
	
	CBaseEemeyMove *BEMove;
	void Mover(CVector2D &_pos){ if (BEMove != NULL)BEMove->Move(this,_pos); };
	CBaseEemeyAttack *BEAttack;
	void Attacker(){ if (BEAttack != NULL)BEAttack->Attack(this); };
	
	int m_counter;	//�ړ��̐؂�ւ��p
	int m_rand;		//�g�p���Ă��Ȃ�
	bool m_locate;	//�����Ă��邩�ǂ���				true:�����Ă���@false:���Ȃ�
	bool m_attack_flag;		//�U�����邩�ǂ���
	int m_attack_cool_time;		//�U���N�[���^�C��
	bool m_item_flag;			
	bool m_escape_flag;			//��������邩�ǂ���	true:���������@false:���Ȃ�
	bool m_locate_pass;			//��x�ʂ�����
	CVector2D m_move_pos;		//�ړ���
};

class CEneEffect{
public:
	CEneEffect(CVector2D *_pos,bool *_living,float _alpha,float _rad,float _exrate);
	~CEneEffect(){};
	CVector2D *m_pos;
	bool *m_living;
	bool m_delete;			//true:�����@false:�����Ȃ�
	float m_alpha;			//���ߒl
	float m_rad;			//�p�x�i���W�A���j
	float m_exrate;			//�傫��
};

class CEnemyNum{
public:
	int m_normal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CEnemy : public CTask{
private:
	list<CEnemyData*> m_enemys;
	list<CEneEffect*> m_ene_eff;
	CEnemyNum m_enemy_num;
	int m_enemy_img[7][88];
	int m_shadow_img;
	int m_kill_count;			//Kill�m�萔
	int m_create_timer;			//���X�|�[����~����
	int m_timer;

public:
	CEnemy();
	~CEnemy(){};

	void Update();
	void Draw();

	void KillAll();
	void Delete();
	
	void Move(int key);
	void Reflect(CEnemyData &cd,CVector2D &_pos);
	
	void EnemyNum(CEnemyData &cd,int _num);

	list<CEnemyData*> *GetEnemyData(){ return &m_enemys; };
	list<CEneEffect*> *GetEneEffData(){ return &m_ene_eff; };
	void SetKillConutData(int _num){ m_kill_count = _num; };
	void SetCreateTimer(int _timer){ m_create_timer = _timer; };
};

//�ʏ�
class CMovePattern1 : public CBaseEemeyMove{ void Move(CEnemyData *cd, CVector2D &_pos); };
//������
class CMovePattern2 : public CBaseEemeyMove{ void Move(CEnemyData *cd, CVector2D &_pos); };
//�������̋�
class CMovePattern3 : public CBaseEemeyMove{ void Move(CEnemyData *cd, CVector2D &_pos); };
//�d���G�i�傫���j
class CMovePattern4 : public CBaseEemeyMove{ void Move(CEnemyData *cd, CVector2D &_pos); };
//�y���G�i�������j
class CMovePattern5 : public CBaseEemeyMove{ void Move(CEnemyData *cd, CVector2D &_pos); };
//��������G
class CMovePattern6 : public CBaseEemeyMove{ void Move(CEnemyData *cd, CVector2D &_pos); };


//�ʏ�
class CAttackPattern1 : public CBaseEemeyAttack{ void Attack(CEnemyData *cd); };
//������
class CAttackPattern2 : public CBaseEemeyAttack{ void Attack(CEnemyData *cd); };
//�e
class CAttackPattern3 : public CBaseEemeyAttack{ void Attack(CEnemyData *cd); };
//�d���G�i�傫���j
class CAttackPattern4 : public CBaseEemeyAttack{ void Attack(CEnemyData *cd); };
//�y���G�i�������j
class CAttackPattern5 : public CBaseEemeyAttack{ void Attack(CEnemyData *cd); };
//��������G
class CAttackPattern6 : public CBaseEemeyAttack{ void Attack(CEnemyData *cd); };


#endif ENEMY_H