
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
#include "difficulty_level_manager.h"
#include "sounddata_manager.h"		//new

CStartText Start;

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
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM1));	//New
	StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM2));	//New

	//CBossManager::GetInstance()->GetBossAdress()->KillAll();
}

//ロード
void CGameScreen::Load(){
}

//リリース
void CGameScreen::Release(){}

//初期化
void CGameScreen::Init()
{
	//ここでタスク生成
	CTaskManager::GetInstance()->Add(new CDifficultyLevel);
	CTaskManager::GetInstance()->Add(new CUi);
	CTaskManager::GetInstance()->Add(new CPlayer);
	CTaskManager::GetInstance()->Add(new CField);
	CTaskManager::GetInstance()->Add(new CBoss);
	CTaskManager::GetInstance()->Add(new CEnemy);
	CTaskManager::GetInstance()->Add(new CEffect);
	CTaskManager::GetInstance()->Add(new CItem);
	PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM1), DX_PLAYTYPE_LOOP);	//New
	//if(CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType() != M_BOSS)
	CTaskManager::GetInstance()->NoUpdate(CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType());
	CCharaData::GetInstance()->AssignmentInvincible(CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType());
	new CChange(255,-2);
	CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);

	m_clear_flag = false;
	m_over_flag = false;

	CTaskManager::GetInstance()->SerectUpdate(eDWP_ENEMY,false);
}

//実行処理
void CGameScreen::Update()
{
	static bool _pass;

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ソフトウェアリセット
	if (CKeyData::GetInstance()->IsKeyTrigger2(key, PAD_INPUT_11) &&
		CKeyData::GetInstance()->IsKeyTrigger2(key, PAD_INPUT_12) &&
		CKeyData::GetInstance()->IsKeyTrigger2(key, PAD_INPUT_5) &&
		CKeyData::GetInstance()->IsKeyTrigger2(key, PAD_INPUT_6))
		m_state = TITLE_SCREEN;

	if (CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_hp < 1){
		m_over_flag = true;
		_pass = false;
		CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
	}

	if (CUiManager::GetInstance()->GetUiAdress()->GetTimeFlag()){
		m_over_flag = true;
		_pass = false;
		CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
	}

	if (CBossManager::GetInstance()->GetBossAdress()->Hp() < 61){
		m_clear_flag = true;
		_pass = false;
		CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
	}

	//画面切り替え
	if (CPlayerManager::GetInstance()->GetPlayerAdress()->GetTeleportFlag()){
		CChangeManager::GetInstance()->GetChangeAdress()->SetChange(true);
		_pass = false;
	}

	//フィールドの切り替えは以下の処理
	if (!m_over_flag && !m_clear_flag){
		if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut()){
			if (!_pass){
				CItemManager::GetInstance()->GetItemAdress()->KillAll();
				CEffectManager::GetInstance()->GetEffectAdress()->KillAll();
				CChangeManager::GetInstance()->GetChangeAdress()->SetOut(false);
				CChangeManager::GetInstance()->GetChangeAdress()->Kill();
				CChangeManager::GetInstance()->GetChangeAdress()->SetCData(255, -2);
				if (CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType() != M_BOSS){
					CFieldManager::GetInstance()->GetFrameAdress()->SetFieldType(M_BOSS);
					CCharaData::GetInstance()->AssignmentDelete(ENEMY);
					CEnemyManager::GetInstance()->GetEnemyAdress()->KillAll();
					CPlayerManager::GetInstance()->GetPlayerAdress()->GetData()->m_pos = CVector2D(640, 580);
					StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM1));	//New
					PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM2), DX_PLAYTYPE_LOOP);	//New
				}
				else{
					CCharaData::GetInstance()->AssignmentDelete(ENEMY);
					CEnemyManager::GetInstance()->GetEnemyAdress()->KillAll();
					CFieldManager::GetInstance()->GetFrameAdress()->SetFieldType(M_NORMAL);
					StopSoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM2));	//New
					PlaySoundMem(CSoundManager::GetInstance()->GetStatusAdress()->getSound(GAME_BGM1), DX_PLAYTYPE_LOOP);	//New
				}
				CTaskManager::GetInstance()->NoUpdate(CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType());
				_pass = true;
				CCharaData::GetInstance()->AssignmentInvincible(CFieldManager::GetInstance()->GetFrameAdress()->GetFieldType());
			}
		}
	}

	if (m_over_flag)
	if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut())m_state = GAMEOVER_SCREEN;

	if (m_clear_flag)
	if (CChangeManager::GetInstance()->GetChangeAdress()->GetOut())m_state = GAMECLEAR_SCREEN;

	//最初のフェイドインから
	if (!CChangeManager::GetInstance()->GetChangeAdress()->GetChangeFlag()){
		//スタートの処理
		if (!CUiManager::GetInstance()->GetUiAdress()->GetPass()){
			CUiManager::GetInstance()->GetUiAdress()->SetPass(true);
			CUiManager::GetInstance()->GetUiAdress()->GetUiData()->push_back(new CUiData(CVector2D(920, 360), true, 0, 0, UI_SELECT_EXRATE, 3, TIMER, 0, 0, 0, &Start));
		}
		else if (CUiManager::GetInstance()->GetUiAdress()->GetPass() == 2){
			CUiManager::GetInstance()->GetUiAdress()->SetPass(3);
			//チュートリアルをする場合以下の処理
			if (CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialFlag())
				CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->SetInvincible(1);
		}
	}
	//チュートリアルで説明が出ていなければ以下の処理（各アップデートを行う）
	if (CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->TutorialState() == 0){
		CCharaData::GetInstance()->Update();
		CTaskManager::GetInstance()->UpdateAll();
	}

	//チュートリアル処理
	if (CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialFlag()){
		CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialData()->Update();
	}
	else
		CTaskManager::GetInstance()->SerectUpdate(eDWP_ENEMY, true);

	CCharaData::GetInstance()->Delete();

	CChangeManager::GetInstance()->GetChangeAdress()->Update();

#if defined(_DEBUG) | defined(DEBUG)
	if (CheckHitKey(KEY_INPUT_P) == 1)m_state = TITLE_SCREEN;
	if (CheckHitKey(KEY_INPUT_O) == 1)m_state = GAMECLEAR_SCREEN;
	if (CheckHitKey(KEY_INPUT_L) == 1)m_state = GAMEOVER_SCREEN;
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

	if (CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialFlag())
	CDifficultyLevelManager::GetInstance()->GetDifficultyLevelAdress()->GetTutorialData()->Draw();
	/*DrawString(930, 90, "Game Screen Hit E key to Title Screen", GetColor
		(255, 255, 255));
	DrawString(870, 110, "Change Control Hit Spase key(keyboard or pad)", GetColor
		(255, 255, 255));
		*/
	Fps();
#if defined(_DEBUG) | defined(DEBUG)
#endif
}

//次のステージへ
SCREEN CGameScreen::GetNextScreen()
{
	return(m_state);
}