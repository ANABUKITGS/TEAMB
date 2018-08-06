#include "task.h"
#include "task_manager.h"

CTask::CTask() : 
m_priority(-1),
m_update_priority(UDP_NULL),
m_draw_priority(DWP_NULL)
{
	//ƒƒ“ƒo[‚É“o˜^‚³‚ê‚È‚¢
}

CTask::CTask(int update_prio,int draw_prio) :
m_priority(0),
m_update_priority(update_prio),
m_draw_priority(draw_prio)
{
	//ƒ^ƒXƒNì¬Œã©“®“I‚ÉTaskManager‚É“o˜^
	CTaskManager::GetInstance()->Add(this);
}

//CTask::~CTask(){}

void CTask::Update(){
	//”h¶æ‚Å’è‹`
	printfDx("CTaskUpdate ");
}

void CTask::Draw(){
	//”h¶æ‚Å’è‹`
	printfDx("CTaskDraw\n");
}