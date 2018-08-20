
//ヘッダーファイル
#include "game_screen.h"
#include "task_manager.h"

#include "field_manager.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "effect_manager.h"
#include "ui_manager.h"
#include "boss_manager.h"
#include "item_manager.h"
#include "change_manager.h"

//コンストラクタ
CGameScreen::CGameScreen()
{
	m_state = GAME_SCREEN;
}

//デストラクタ
CGameScreen::~CGameScreen(){
	CTaskManager::GetInstance()->KillAll();
	CCharaData::GetInstance()->KillAll();
	CItemManager::GetInstance()->GetItemAdress()->KillAll();
	CEnemyManager::GetInstance()->GetEnemyAdress()->KillAll();
	CEffectManager::GetInstance()->GetEffectAdress()->KillAll();
	CPlayerManager::GetInstance()->GetPlayerAdress()->Kill();
	CUiManager::GetInstance()->GetUiAdress()->KillAll();
	CChangeManager::GetInstance()->GetChangeAdress()->Kill();
	CBossManager::GetInstance()->GetBossAdress()->KillAll();
}

//ロード
void CGameScreen::Load(){
}

//リリース
void CGameScreen::Release(){}

//初期化
void CGameScreen::Init(){
	//ここでタスク生成
	CTaskManager::GetInstance()->Add(new CPlayer);
	CTaskManager::GetInstance()->Add(new CField);
	CTaskManager::GetInstance()->Add(new CBoss);
	CTaskManager::GetInstance()->Add(new CEnemy);
	CTaskManager::GetInstance()->Add(new CEffect);
	CTaskManager::GetInstance()->Add(new CUi);
	CTaskManager::GetInstance()->Add(new CItem);
	new CChange(0,2);
}

//実行処理
void CGameScreen::Update()
{
	bool _ef = false;	//終了フラグ
	if (CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_hp < 1)_ef = true;
	if (CUiManager::GetInstance()->GetUiAdress()->GetTimeFlag())_ef = true;
	if (_ef){
		CChangeManager::GetInstance()->GetChangeAdress()->Update();
		if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut())m_state = TITLE_SCREEN;
	}

	CCharaData::GetInstance()->Update();
	
	CTaskManager::GetInstance()->UpdateAll();

	CCharaData::GetInstance()->Delete();

#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_P) == 1)m_state = TITLE_SCREEN;
	CCharaData::GetInstance()->Counter();
#endif
}

//描画
void CGameScreen::Draw()
{
	ClearDrawScreen();

	CTaskManager::GetInstance()->DrawAll();
	CCharaData::GetInstance()->Draw();

	CChangeManager::GetInstance()->GetChangeAdress()->Draw();

	DrawString(930, 90, "Game Screen Hit E key to Title Screen", GetColor
		(255, 255, 255));
	DrawString(870, 110, "Change Control Hit Spase key(keyboard or pad)", GetColor
		(255, 255, 255));

#if defined(_DEBUG) | defined(DEBUG)
	Fps();
#endif
}

//次のステージへ
SCREEN CGameScreen::GetNextScreen()
{
	return(m_state);
}