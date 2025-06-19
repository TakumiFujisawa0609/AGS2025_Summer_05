#include "GardenStage.h"

#include <DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Object/Manager/BlockManager.h"

// コンストラクタ
GardenStage::GardenStage(StageManager* stageManager)
	: stageManager_(stageManager)
{
	blockManager_ = new BlockManager();
}

// 初期化処理
void GardenStage::Init(void)
{
	// CSVファイルからブロック読み込み
	blockManager_->Init(Application::PATH_MAP_DATA);
}

// 更新処理
void GardenStage::Update(void)
{
	auto& input = InputManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_P))
	{
		stageManager_->ChangeStage(StageManager::STAGE_ID::GUILD);
	}

	blockManager_->Update();
}

// 描画処理
void GardenStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "ガーデン");
	blockManager_->Draw();
}

// 解放処理
void GardenStage::Release(void)
{
	if (blockManager_ != nullptr)
	{
		blockManager_->Release();
		delete blockManager_;
		blockManager_ = nullptr;
	}
}
