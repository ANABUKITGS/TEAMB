#ifndef DIFFICULTY_LEVEL_MANAGER_H
#define DIFFICULTY_LEVEL_MANAGER_H

#include "difficulty_level.h"

class CDifficultyLevelManager{
private:
	static CDifficultyLevelManager* mp_Instance;
	CDifficultyLevel *m_difficulty_level;
	CDifficultyLevelManager();
public:
	~CDifficultyLevelManager();

	static CDifficultyLevelManager* GetInstance();
	static void ClearInstance();

	//������
	void Init(CDifficultyLevel* difficulty_level);

	//�I������
	void Finish();

	//�f�[�^�̎擾
	CDifficultyLevel* GetDifficultyLevelAdress() const;

	void Update();
};

#endif DIFFICULTY_LEVEL_MANAGER_H