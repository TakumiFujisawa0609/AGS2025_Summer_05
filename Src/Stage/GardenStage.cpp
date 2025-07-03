#include "GardenStage.h"

#include <DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Object/Manager/BlockManager.h"
#include "../Object/Manager/PlantManager.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Object/Manager/OreMnanager.h"

// コンストラクタ
GardenStage::GardenStage(StageManager* stageManager)
	: stageManager_(stageManager)
{
	blockManager_ = new BlockManager();
	plantManager_ = new PlantManager();
	oreManager_ = new OreManager();
	
}

// 初期化処理
void GardenStage::Init(void)
{
	// CSVファイルからブロック読み込み
	blockManager_->Init(Application::PATH_MAP_DATA);

	// CSVデータ再取得
	auto mapData = blockManager_->GetMapData();

	// 植物初期化
	plantManager_->Init(mapData, 50.0f);

	oreManager_->Init(mapData, 50.0f);

	for (const auto& plant : plantManager_->GetPlantObjects())
	{
		CollisionManager::GetInstance().Register(plant);
	}

	for (const auto& ore : oreManager_->GetOreObjects())
	{
		CollisionManager::GetInstance().Register(ore);
	}
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
	plantManager_->Update();
	oreManager_->Update();
}

// 描画処理
void GardenStage::Draw(void)
{
	blockManager_->Draw();
	plantManager_->Draw();
	oreManager_->Draw();

}

// 解放処理
void GardenStage::Release(void)
{
	if (oreManager_ != nullptr)
	{
		oreManager_->Release();
		delete oreManager_;
		oreManager_ = nullptr;
	}

	if (plantManager_ != nullptr)
	{
		plantManager_->Release();
		delete plantManager_;
		plantManager_ = nullptr;
	}

	if (blockManager_ != nullptr)
	{
		blockManager_->Release();
		delete blockManager_;
		blockManager_ = nullptr;
	}
}
