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
#include"../DrawUI/SceneUI/InventoryUI.h"
#include"../Object/Manager/ItemManager.h"

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

	//サウンド
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_TITLE, res.Load(ResourceManager::SRC::BGM_TITLE).handleId_);
	sound.Add(SoundManager::TYPE::SE, SoundManager::SOUND::SE_PUSH, res.Load(ResourceManager::SRC::SE_PUSH).handleId_);
	sound.AdjustVolume(SoundManager::SOUND::BGM_TITLE, 40);
	sound.AdjustVolume(SoundManager::SOUND::SE_PUSH, 50);

	// UIの生成
	inventoryUI_ = new InventoryUI();
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

	// インベントリUIの描画
	inventoryUI_->Draw();

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

	delete inventoryUI_;
	inventoryUI_ = nullptr;
}

void SceneGame::DrawDebug(void)
{
	DrawFormatString(0, 0, 0xffffff, "ゲームシーン");

	//グリッド線
	grid_->Draw();
}
