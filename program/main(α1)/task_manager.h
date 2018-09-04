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
	~CTaskManager();		//更新
	void UpdateAll();		//描画
	void DrawAll();			//削除
	void KillAll();			//全削除
	void AssignmentDelete();//指定のものを削除

	void NoUpdate(int _type);
	void SerectUpdate(int _type,bool _live);

	//タスクマネージャーのデータの取得
	//これを使うとマネージャーのデータを使うことが出来る
	static CTaskManager* GetInstance();

	//格納されているものを削除
	static void ClearInstance();

	//リスト追加関数
	void Add(CTask* pTask);
	void Add(CTask* pTask, const int priority);

private:
	//リストにタスク格納処理
	void AddTaskInner(CTask *pTask, const int priority);
};

#endif TASK_MANAGER_H
