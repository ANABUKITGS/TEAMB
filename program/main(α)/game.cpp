#include "stdio.h"
#include "screen.h"
#include "game_screen.h"
#include "gametitle_screen.h"
#include "game.h"

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
}

void CGame::Dest()
{
	if (m_pScreen != NULL){
		delete m_pScreen;
		m_pScreen = NULL;
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
