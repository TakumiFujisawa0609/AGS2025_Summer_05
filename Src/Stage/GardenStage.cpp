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

GardenStage::GardenStage(StageManager* stageManager)
    : stageManager_(stageManager),
    blockManager_(nullptr),
    plantManager_(nullptr),
    oreManager_(nullptr),
    fenceManager_(nullptr),
    dateTimeManager_(nullptr),
    currentTimeZone_(TimeZone::MORNING)
{
    blockManager_ = new BlockManager();
    plantManager_ = new PlantManager();
    oreManager_ = new OreManager();
    fenceManager_ = new FenceManager();
}

void GardenStage::Init(void)
{
    auto& resourceManager = ResourceManager::GetInstance();
    auto& soundManager = SoundManager::GetInstance();

    blockManager_->Init(Application::PATH_MAP_DATA);

    auto mapData = blockManager_->GetMapData();

    auto camera = SceneManager::GetInstance().GetCamera();

    camera->ChangeMode(Camera::MODE::FOLLOW);

    const int BGM_VOLUME = 30;                          

    soundManager.Add(
        SoundManager::TYPE::BGM,
        SoundManager::SOUND::BGM_GARDEN_DAY,
        resourceManager.Load(ResourceManager::SRC::BGM_GARDEN_DAY).handleId_
    );
    soundManager.Add(
        SoundManager::TYPE::BGM,
        SoundManager::SOUND::BGM_GARDEN_NIGHT,
        resourceManager.Load(ResourceManager::SRC::BGM_GARDEN_NIGHT).handleId_
    );

    soundManager.AdjustVolume(SoundManager::SOUND::BGM_GARDEN_DAY, BGM_VOLUME);
    soundManager.AdjustVolume(SoundManager::SOUND::BGM_GARDEN_NIGHT, BGM_VOLUME);

    soundManager.Play(SoundManager::SOUND::BGM_GARDEN_DAY);

    const float PLANT_ORE_SCALE = 50.0f;                

    plantManager_->Init(mapData, PLANT_ORE_SCALE);
    oreManager_->Init(mapData, PLANT_ORE_SCALE);
    fenceManager_->Init(mapData, PLANT_ORE_SCALE);

    warp_ = std::make_shared<Warp>(stageManager_);
    warp_->Init();

    well_ = std::make_shared<WellObject>();
    well_->Init();

    dateTimeManager_ = new DateTimeManager();
    dateTimeManager_->Init();

    auto& collisionManager = CollisionManager::GetInstance();

    collisionManager.Register(well_);
    collisionManager.Register(warp_);

    for (const auto& plantObject : plantManager_->GetPlantObjects())
    {
        collisionManager.Register(plantObject);
    }

    for (const auto& oreObject : oreManager_->GetOreObjects())
    {
        collisionManager.Register(oreObject);
    }

    for (const auto& fenceObject : fenceManager_->GetFenceObjects())
    {
        collisionManager.Register(fenceObject);
    }

    for (const auto& fenceObjectX : fenceManager_->GetFenceObjectsX())
    {
        collisionManager.Register(fenceObjectX);
    }

    auto player = stageManager_->GetPlayer();
    camera->SetFollow(&player->GetTransform());
}

void GardenStage::Update(void)
{
    blockManager_->Update();
    plantManager_->Update(stageManager_->GetPlayer()->GetPosition());
    oreManager_->Update();
    fenceManager_->Update();
    warp_->Update();
    well_->Update();

    dateTimeManager_->Update();

#ifdef _DEBUG
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.IsTriggerDown(KEY_INPUT_P))
    {
        if (stageManager_ != nullptr)
        {
            stageManager_->ChangeStage(StageManager::STAGE_ID::GUILD);
        }
    }
#endif
}

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

void GardenStage::Release(void)
{
    if (oreManager_ != nullptr)
    {
        oreManager_->Release();
        delete oreManager_;
        oreManager_ = nullptr;
    }

    if (fenceManager_ != nullptr)
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