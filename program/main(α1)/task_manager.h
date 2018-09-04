#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "myLib.h"
#include "task.h"
#include <list>

using namespace std;

class CTaskManager{
private:
	static CTaskManager* m_pInstance;
	list<CTask*> m_TaskList;

	CTaskManager();
public:
	~CTaskManager();		//�X�V
	void UpdateAll();		//�`��
	void DrawAll();			//�폜
	void KillAll();			//�S�폜
	void AssignmentDelete();//�w��̂��̂��폜

	void NoUpdate(int _type);
	void SerectUpdate(int _type,bool _live);

	//�^�X�N�}�l�[�W���[�̃f�[�^�̎擾
	//������g���ƃ}�l�[�W���[�̃f�[�^���g�����Ƃ��o����
	static CTaskManager* GetInstance();

	//�i�[����Ă�����̂��폜
	static void ClearInstance();

	//���X�g�ǉ��֐�
	void Add(CTask* pTask);
	void Add(CTask* pTask, const int priority);

private:
	//���X�g�Ƀ^�X�N�i�[����
	void AddTaskInner(CTask *pTask, const int priority);
};

#endif TASK_MANAGER_H
