#include "task_manager.h"


CTaskManager* CTaskManager::m_pInstance = nullptr;

CTaskManager::CTaskManager(){}

CTaskManager::~CTaskManager(){}

void CTaskManager::KillAll(){
	if (m_TaskList.size() != NULL) m_TaskList.clear();
}

void CTaskManager::AssignmentDelete(){
	for (auto it = m_TaskList.begin(); it != m_TaskList.end();){
		if ((*it)->m_priority == eDWP_ENEMY){
			it = m_TaskList.erase(it);
			continue;
		}
		it++;
	}
}

void CTaskManager::Add(CTask* pTask){
	AddTaskInner(pTask, (*pTask).m_priority);
}

void CTaskManager::Add(CTask* pTask, const int priority){
	AddTaskInner(pTask, priority);
}

void CTaskManager::AddTaskInner(CTask* pTask,  const int priority){
	if ( m_TaskList.size() == NULL){		//empty()�̓_��
		m_TaskList.push_back(pTask);
	}
	else{
		auto it = m_TaskList.begin();
		for (; it != m_TaskList.end(); it++){
			if ((*it)->m_priority > priority){
				m_TaskList.insert(it, pTask);
				break;
			}

		}
		if (it == m_TaskList.end()){
			m_TaskList.push_back(pTask);
		}
	}
}

CTaskManager* CTaskManager::GetInstance(){
	//CTaskManager����x�̂݁i�V���O���g���j�������Ċi�[
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CTaskManager();
	}
	//�����Ԃ�
	return m_pInstance;
}

void CTaskManager::ClearInstance(){
	//���������[�N���
	if (m_pInstance != nullptr) delete m_pInstance;
}

void CTaskManager::NoUpdate(int _type){
	for (auto it = m_TaskList.begin(); it != m_TaskList.end(); it++){
		if (_type == 0){
			if ((*it)->m_priority == eDWP_BOSS){
				(*it)->m_update = false;
			}
			else{
				(*it)->m_update = true;
			}
		}
		else{
			if ((*it)->m_priority == eDWP_ENEMY){
				(*it)->m_update = false;
			}
			else{
				(*it)->m_update = true;
			}
		}
	}
}

void CTaskManager::UpdateAll(){
	clsDx();
	for (auto it = m_TaskList.begin(); it != m_TaskList.end(); it++){
		if ((*it)->m_update)
			(*it)->Update();
#if defined(_DEBUG) | defined(DEBUG)
		//printfDx("Task_priority[%d]\n", (*it)->m_priority);
#endif
		//CTask* pTask = *it;		//�����d�v
		//pTask->Update();
	}
}

void CTaskManager::DrawAll(){
	for (auto it = m_TaskList.begin(); it != m_TaskList.end(); it++){
		if ((*it)->m_update)
			(*it)->Draw();
		//CTask* pTask = *it;		//�����d�v
		//pTask->Draw();
	}
}
