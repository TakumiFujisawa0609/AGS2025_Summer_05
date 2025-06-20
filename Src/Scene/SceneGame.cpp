#include "SceneGame.h"

#include <DxLib.h>

#include "../Common/Easing.h"
#include "../Manager/Generic/Camera.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Manager/System/Collision.h"
#include "../Object/Manager/StageManager.h"
#include "../Object/Manager/AlchemyManager.h"
#include "../Object/Manager/ItemManager.h"
#include "../Object/Grid.h"
#include "../Object/player.h"
#include "../DrawUI/SceneUI/InventoryUI.h"
#include "../DrawUI/Font.h"
#include "../Manager/System/DateTimeManager.h"



SceneGame::SceneGame(void)
{
	grid_ = nullptr;
	isStartFont_ = true;
}

void SceneGame::Init(void)
{
	// ステージ管理初期
	stageManager_ = new StageManager();
	stageManager_->Init();

	//カメラ
	auto camera = SceneManager::GetInstance().GetCamera();

	//カメラを固定に設定
	camera->ChangeMode(Camera::MODE::FOLLOW);

	//アイテムマネージャー
	auto itemManager_ = &ItemManager::GetInstance();

	//日数
	dateTimeManager_ = new DateTimeManager();
	dateTimeManager_->Init();

	//グリッド線
	grid_ = new Grid();
	grid_->Init();

	//プレイヤー
	player_ = new Player();
	player_->Init();


	//カメラをプレイヤーに追従
	camera->SetFollow(&player_->GetTransform());

	//サウンド
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_TITLE, res.Load(ResourceManager::SRC::BGM_TITLE).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_TITLE, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 50);

	// UIの生成
	inventoryUI_ = new InventoryUI();

	AlchemyManager::GetInstance().Init();


}

void SceneGame::Update(void)
{
	auto& sound = SoundManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& alchemy = AlchemyManager::GetInstance();

	////シーン遷移(デバッグ)
	//if (input.IsTrgDown(KEY_INPUT_SPACE))
	//{
	//	//決定音
	//	sound.Play(SoundManager::SOUND::SE_PUSH);

	//	//BGM停止
	//	sound.Stop(SoundManager::SOUND::BGM_TITLE);

	//	//シーン遷移
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

	//	//処理終了
	//	return;
	//}

	//日数
	dateTimeManager_->Update();

	// インベントリUIの更新
	inventoryUI_->Update();

	//// Rキーで錬金メニューの開閉
	//if (input.IsTrgDown(KEY_INPUT_R))
	//{
	//	if (alchemy.IsOpen())
	//		alchemy.Close();
	//	else
	//		alchemy.Open();
	//}

	//// 錬金メニューが開いているときのみ更新
	//if (alchemy.IsOpen())
	//{
	//	alchemy.Update();
	//}


	//プレイヤー
	player_->Update();

	stageManager_->Update();

	
}

void SceneGame::Draw(void)
{
	auto& alchemy = AlchemyManager::GetInstance();

	//プレイヤーの描画
	player_->Draw();

	//ステージの描画
	stageManager_->Draw();

	int x;
	x = Application::DEFA_SCREEN_SIZE_X;

	if (isStartFont_ == true)
	{
		Font::GetInstance().DrawDefaultText((x - (x / 2)) - 10, 0, "移動と表記が出ている場所でEneterキーを押して\nギルドに移動してそこで依頼を受けよう", 0xffffff, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
	}
	else
	{
		Font::GetInstance().DrawDefaultText((x - (x / 2)) - 100, 0, "依頼を受けたらアトリエに戻って\n錬金と表記が出ている場所でEneterキーを押してアイテムを錬成しよう\nアイテムができたらギルドに戻ってアイテムを納品しよう", 0xffffff, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
	}

	// インベントリUIの描画
	inventoryUI_->Draw();

	if (InputManager::GetInstance().IsNew(KEY_INPUT_RETURN))
	{
		isStartFont_ = false;
	}

	
	

	

	/*if(alchemy.IsOpen())
	{
		alchemy.Draw();
	}*/
	

#ifdef _DEBUG
	//デバック表示
	DrawDebug();
#endif // _DEBUG
}

void SceneGame::Release(void)
{

	grid_->Release();
	delete grid_;
	grid_ = nullptr;

	//プレイヤーの解放
	player_->Release();
	delete player_;
	player_ = nullptr;

	//インベントリUIの解放
	delete inventoryUI_;
	inventoryUI_ = nullptr;

	//ステージマネージャーの削除
	stageManager_->Destroy();
	delete stageManager_;

	
}

void SceneGame::DrawDebug(void)
{
	grid_->Draw();

	int day = dateTimeManager_->GetDay();

	// 時間帯を文字列に変換
	const char* timeZoneStr = nullptr;
	switch (dateTimeManager_->GetTimeZone())
	{
	case DateTimeManager::TIME_ZONE::MORNING: timeZoneStr = "朝"; break;
	case DateTimeManager::TIME_ZONE::DAY:     timeZoneStr = "昼"; break;
	case DateTimeManager::TIME_ZONE::EVENING: timeZoneStr = "夕方"; break;
	case DateTimeManager::TIME_ZONE::NIGHT:   timeZoneStr = "夜"; break;
	}

	// 表示用（画面左上）
	DrawFormatString(20, 100, GetColor(255, 255, 255), "日付: %d日目", day);
	DrawFormatString(20, 120, GetColor(255, 255, 255), "時間帯: %s", timeZoneStr);
}

