#include "task.h"
#include "task_manager.h"

CTask::CTask() : 
m_priority(-1),
m_update_priority(UDP_NULL),
m_draw_priority(DWP_NULL)
{
	//メンバーに登録されない
}

CTask::CTask(int update_prio,int draw_prio) :
m_priority(0),
m_update_priority(update_prio),
m_draw_priority(draw_prio)
{
	//タスク作成後自動的にTaskManagerに登録
	CTaskManager::GetInstance()->Add(this);
}

//CTask::~CTask(){}

void CTask::Update(){
	//派生先で定義
	printfDx("CTaskUpdate ");
}

void CTask::Draw(){
	//派生先で定義
	printfDx("CTaskDraw\n");
}