#include "stdio.h"
#include "screen.h"
#include "game_screen.h"
#include "gametitle_screen.h"
#include "gameover_screen.h"
#include "gameclear_screen.h"
#include "credit_screen.h"
#include "game.h"

#include "sounddata_manager.h"

CGame::CGame()
{
	m_pScreen = NULL;
}

CGame::~CGame()
{
}

void CGame::Init()
{
	m_GameData.old_screen = TITLE_SCREEN;
	m_GameData.now_screen = TITLE_SCREEN;
	m_pScreen = NULL;
	srand((unsigned int)time(NULL));

	CKeyData::GetInstance();
	new CSoundData();		//New
}

void CGame::Dest()
{
	if (m_pScreen != NULL){
		delete m_pScreen;
		m_pScreen = NULL;
		CSoundManager::GetInstance()->Finish();
	}
}

void CGame::Update()
{
	if (m_pScreen){
		m_GameData.old_screen = m_GameData.now_screen;
		m_GameData.now_screen = m_pScreen->GetNextScreen();
		if (m_GameData.now_screen != m_GameData.old_screen){
			m_pScreen->Dest();
			delete m_pScreen;
			m_pScreen = NULL;
		}
	}
	if (m_pScreen == NULL){
		switch (m_GameData.now_screen)
		{
		case TITLE_SCREEN:
			m_pScreen = new CGameTitleScreen();
			break;
		case GAME_SCREEN:
			m_pScreen = new CGameScreen();
			break;
		case GAMEOVER_SCREEN:
			m_pScreen = new CGameOverScreen();
			break;
		case GAMECLEAR_SCREEN:
			m_pScreen = new CGameClearScreen();
			break;
		case CREDIT_SCREEN:
			m_pScreen = new CCreditScreen();
			break;
		default:
			assert(0);
		}
		if (m_pScreen != NULL){
			m_pScreen->Init();
			m_pScreen->Load();
		}
	}
	if (m_pScreen){
		m_pScreen->Update();
	}
}

void CGame::Draw()
{
	if (m_pScreen){
		m_pScreen->Draw();
	}
}
