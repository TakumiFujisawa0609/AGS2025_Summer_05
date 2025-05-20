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
#include"../Object/Grid.h"
#include"../DrawUI/DubegUI/InventoryUI.h"
#include"../Object/Manager/ItemManager.h"

SceneGame::SceneGame(void)
{
	grid_ = nullptr;
}

void SceneGame::Init(void)
{
	//グリッド線
	grid_ = new Grid();
	grid_->Init();

	//サウンド
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_TITLE, res.Load(ResourceManager::SRC::BGM_TITLE).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_TITLE, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 50);

	// アイテムマネージャー生成・仮データ登録
	itemManager_ = new ItemManager();
	itemManager_->Init();

	// UIの生成
	inventoryUI_ = new InventoryUI(*itemManager_);
}

void SceneGame::Update(void)
{
	auto& sound = SoundManager::GetInstance();

	//シーン遷移(デバッグ)
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		//決定音
		sound.Play(SoundManager::SOUND::SE_PUSH);

		//BGM停止
		sound.Stop(SoundManager::SOUND::BGM_TITLE);

		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);

		//処理終了
		return;
	}

	// インベントリUIの更新
	inventoryUI_->Update();

	StageManager::GetInstance().Update();
}

void SceneGame::Draw(void)
{
	//ステージの描画
	StageManager::GetInstance().Draw();

	DrawFormatString(0, 0, 0xffffff, "ゲームシーン");

	//グリッド線
	grid_->Draw();

	// インベントリUIの描画
	inventoryUI_->Draw();
}

void SceneGame::Release(void)
{
	grid_->Release();
	delete grid_;
	grid_ = nullptr;

	delete inventoryUI_;
	inventoryUI_ = nullptr;

	delete itemManager_;
	itemManager_ = nullptr;
}
