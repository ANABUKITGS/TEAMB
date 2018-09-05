#ifndef DIFFICULTY_LEVEL_H
#define DIFFICULTY_LEVEL_H

#include "task.h"
#include "base_data.h"

class CEnemyDifficultyTable{
public:
	int m_enemy_level;
	int m_next_kill;
	int m_nomal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CEnemyDifficulty{
public:
	CEnemyDifficulty();
	~CEnemyDifficulty(){};
	int m_enemy_level;
	int m_next_kill;
	int m_nomal_num;
	int m_long_num;
	int m_big_num;
	int m_small_num;
	int m_bomb_num;
};

class CArrowData : public CBaseData{
public:
	CArrowData();
	CArrowData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type, CVector2D* _pos2, bool* _living2);
	~CArrowData(){};

	CVector2D *m_a_pos;
	bool *m_a_living;
};

class CTutorialData : public CBaseData{
public:
	CTutorialData();
	CTutorialData(CVector2D _pos, bool _living, float _alpha, float _rad, float _exrate, int _animtype, int _type);
	~CTutorialData(){};
	void Update();
	void Draw();

	CBaseData *m_t_range;
	list<CArrowData*> m_arrow;
	CBaseData *m_t_text;

	void KillRange();

	bool m_pass_flag;
	bool m_attack_pass_flag;
	bool m_icon_pass[3];		//プレイヤーの攻撃アイコンを見たか
	int m_add_alpha;			//チュートリアルの透過用

	int m_select_type;
	int m_tutorial_img[5];
	int m_serect_text_img[2][2];
	int m_t_range_img[3];
};

class CDifficultyLevel : public CTask{
private:
	CEnemyDifficulty *m_enemy_difficulty;
	CTutorialData *m_tutorial;
	int m_difficulty_level;
	int m_enmey_max;
	int m_item_drop_level;
	int m_level_up;
	int m_level_num;
	bool m_tutorial_flag;		//チュートリアルを消すかどうか

public:
	CDifficultyLevel();
	~CDifficultyLevel(){ delete m_enemy_difficulty; };

	void Update();
	void Draw();

	//エネミーを全部足したやつ
	void AddEnemyMax();
	
	int TutorialState();

	inline void SetDifficulty(int _level){ m_difficulty_level = _level; };
	inline void SetEnemyLevel(int _level){ m_enemy_difficulty->m_enemy_level = _level; };
	inline void SetItemDrop(int _level){ m_item_drop_level = _level; };
	inline void SetTutorialFlag(bool _flag){ m_tutorial_flag = _flag; };
	inline void SetInvincible(int _num){ m_tutorial->m_invincible = _num; };//チュートリアルの動き
	inline void SetIconPass(bool _flag,int _num){ m_tutorial->m_icon_pass[_num] = _flag; };//チュートリアルの動き

	inline CEnemyDifficulty *GetEnemyDifficulty(){ return m_enemy_difficulty; };
	inline CTutorialData *GetTutorialData(){ return m_tutorial; };
	inline int GetEneMax(){ return m_enmey_max; };
	inline int GetItemDropLevel(){ return m_item_drop_level; };
	inline bool GetTutorialFlag(){ return m_tutorial_flag; };
	inline int GetInvincible(){ return m_tutorial->m_invincible; };
};

#endif DIFFICULTY_LEVEL_H