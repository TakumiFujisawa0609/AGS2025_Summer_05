#include "GardenStage.h"

#include <DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/System/TimeManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Manager/System/DateTimeManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Object/Manager/BlockManager.h"
#include "../Object/Manager/PlantManager.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Object/Manager/OreMnanager.h"
#include "../Object/GardenObject/Warp.h"
#include "../Object/Manager/FenceManager.h"
#include "../Object/GardenObject/WellObject.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/Camera.h"
#include "../Object/Player.h"
#include "../DrawUI/SceneUI/QuestUI.h"

// コンストラクタ
GardenStage::GardenStage(StageManager* stageManager)
	: stageManager_(stageManager)
{
	blockManager_ = new BlockManager();
	plantManager_ = new PlantManager();
	oreManager_ = new OreManager();
	fenceManager_ = new FenceManager();

	TimeZone currentTimeZone_ = TimeZone::MORNING;
}

// 初期化処理
void GardenStage::Init(void)
{
	auto& res = ResourceManager::GetInstance();
	auto& sound = SoundManager::GetInstance();
	
	// CSVファイルからブロック読み込み
	blockManager_->Init(Application::PATH_MAP_DATA);

	// CSVデータ再取得
	auto mapData = blockManager_->GetMapData();

	//カメラ設定
	auto camera = SceneManager::GetInstance().GetCamera();

	camera->ChangeMode(Camera::MODE::FOLLOW);

	//BGMの追加
	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_GARDEN_DAY, res.Load(ResourceManager::SRC::BGM_GARDEN_DAY).handleId_);
	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_GARDEN_NIGHT, res.Load(ResourceManager::SRC::BGM_GARDEN_NIGHT).handleId_);

	//BGMの音量調整
	sound.AdjustVolume(SoundManager::SOUND::BGM_GARDEN_DAY, 30);
	sound.AdjustVolume(SoundManager::SOUND::BGM_GARDEN_NIGHT, 30);

	sound.Play(SoundManager::SOUND::BGM_GARDEN_DAY);

	auto& timeManager = TimeManager::GetInstance();
	int hour = timeManager.GetGameHour();


	// 植物初期化
	plantManager_->Init(mapData, 50.0f);

	oreManager_->Init(mapData, 50.0f);

	fenceManager_->Init(mapData, 50.0f);

	warp_ = std::make_shared<Warp>(stageManager_);
	warp_->Init();

	well_ = std::make_shared<WellObject>();
	well_->Init();

	dateTimeManager_ = new DateTimeManager();
	dateTimeManager_->Init();

	CollisionManager::GetInstance().Register(well_);

	CollisionManager::GetInstance().Register(warp_);

	for (const auto& plant : plantManager_->GetPlantObjects())
	{
		CollisionManager::GetInstance().Register(plant);
	}

	for (const auto& ore : oreManager_->GetOreObjects())
	{
		CollisionManager::GetInstance().Register(ore);
	}

	for (const auto& fne : fenceManager_->GetFenceObjects())
	{
		CollisionManager::GetInstance().Register(fne);
	}

	for (const auto& fneX : fenceManager_->GetFenceObjectsX())
	{
		CollisionManager::GetInstance().Register(fneX);
	}

	// カメラをプレイヤーに追従
    auto player = stageManager_->GetPlayer();  
    camera->SetFollow(&player->GetTransform());
}

// 更新処理
void GardenStage::Update(void)
{
	auto& input = InputManager::GetInstance();

#ifdef _DEBUG
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		stageManager_->ChangeStage(StageManager::STAGE_ID::GUILD);
	}
#endif


	// 各オブジェクトの更新
	blockManager_->Update();
	plantManager_->Update(stageManager_->GetPlayer()->GetPos());
	oreManager_->Update();
	fenceManager_->Update();
	warp_->Update();
	well_->Update();

	// DateTimeManager の更新も忘れずに
	dateTimeManager_->Update();
}

// 描画処理
void GardenStage::Draw(void)
{
	blockManager_->Draw();
	plantManager_->Draw();
	oreManager_->Draw();
	fenceManager_->Draw();
	warp_->Draw();
	well_->Draw();

	QuestUI::GetInstance().Draw();

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

	if (fenceManager_!= nullptr)
	{
		fenceManager_->Release();
		delete fenceManager_;
		fenceManager_ = nullptr;
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

	if (dateTimeManager_ != nullptr)
	{
		delete dateTimeManager_;
		dateTimeManager_ = nullptr;
	}
}
