#include "task.h"
#include "task_manager.h"

CTask::CTask() : 
m_priority(-1),
m_update_priority(UDP_NULL),
m_draw_priority(DWP_NULL)
{
	//�����o�[�ɓo�^����Ȃ�
}

CTask::CTask(int update_prio,int draw_prio) :
m_priority(0),
m_update_priority(update_prio),
m_draw_priority(draw_prio)
{
	//�^�X�N�쐬�㎩���I��TaskManager�ɓo�^
	CTaskManager::GetInstance()->Add(this);
}

//CTask::~CTask(){}

void CTask::Update(){
	//�h����Œ�`
	printfDx("CTaskUpdate ");
}

void CTask::Draw(){
	//�h����Œ�`
	printfDx("CTaskDraw\n");
}