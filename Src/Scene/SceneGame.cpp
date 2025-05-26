#include "SceneGame.h"

#include<DxLib.h>

#include"../Application.h"
#include"../Common/Easing.h"
#include"../Manager/Generic/SceneManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Decoration/SoundManager.h"
#include"../Manager/System/Collision.h"
#include"../Object/Manager/StageManager.h"
#include"../DrawUI/SceneUI/InventoryUI.h"
#include"../Object/Manager/AlchemyManager.h"
#include"../Object/Manager/ItemManager.h"
#include"../Object/Grid.h"
#include"../Object/player.h"

SceneGame::SceneGame(void)
{
	grid_ = nullptr;
}

void SceneGame::Init(void)
{
	//アイテムマネージャー
	auto itemManager_ = &ItemManager::GetInstance();

	//グリッド線
	grid_ = new Grid();
	grid_->Init();

	//プレイヤー
	player_ = new Player();
	player_->Init();

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

	// インベントリUIの更新
	inventoryUI_->Update();

	// Rキーで錬金メニューの開閉
	if (input.IsTrgDown(KEY_INPUT_R))
	{
		if (alchemy.IsOpen())
			alchemy.Close();
		else
			alchemy.Open();
	}

	// 錬金メニューが開いているときのみ更新
	if (alchemy.IsOpen())
	{
		alchemy.Update();
	}


	StageManager::GetInstance().Update();

	//プレイヤー
	player_->Update();
}

void SceneGame::Draw(void)
{
	auto& alchemy = AlchemyManager::GetInstance();

	//ステージの描画
	StageManager::GetInstance().Draw();

	// インベントリUIの描画
	inventoryUI_->Draw();

	if(alchemy.IsOpen())
	{
		alchemy.Draw();
	}
	

#ifdef _DEBUG
	//デバック表示
	DrawDebug();
#endif // _DEBUG

	//グリッド線
	grid_->Draw();
}

void SceneGame::Release(void)
{
	grid_->Release();
	delete grid_;
	grid_ = nullptr;
}
