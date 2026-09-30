#include "GuildStage.h"

#include <DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Object/GuildObject/BulletinBoard.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Object/GuildObject/WallGuild.h"
#include "../Object/GuildObject/WallGuild2.h"
#include "../Object/GuildObject/WallGuild3.h"
#include "../Object/GuildObject/WallGuild4.h"
#include "../Object/GuildObject/TableSetGuild.h"
#include "../Object/Manager/TableSetGuildManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/Camera.h"
#include "../Object/player.h"
#include "../DrawUI/SceneUI/QuestUI.h"

GuildStage::GuildStage(StageManager* stageManager)
    : stageManager_(stageManager),
    modelId_(-1),
    pauseUiCount_(0)
{
}

void GuildStage::Init(void)
{
    auto& soundManager = SoundManager::GetInstance();
    auto& resourceManager = ResourceManager::GetInstance();
    auto& collisionManager = CollisionManager::GetInstance();

    modelId_ = resourceManager.LoadModelDuplicate(ResourceManager::SRC::STAGE_ATELIER);

    modelIdPos_ = INIT_MODELID_POS;
    pauseUiCount_ = PAUSE_UI_COUNT;

    const float ROTATION_ZERO = 0.0f;                   

    MV1SetPosition(modelId_, modelIdPos_);
    MV1SetScale(modelId_, MODELID_SCALEA);
    MV1SetRotationXYZ(modelId_, { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO });

    auto camera = SceneManager::GetInstance().GetCamera();

    camera->ChangeMode(Camera::MODE::FIXED_POINT);

    const float CAMERA_TARGET_OFFSET = 0.0f;            
    auto player = stageManager_->GetPlayer();
    camera->SetPosition(
        Camera::DEFAULT_CAMERA_POSITION,
        { CAMERA_TARGET_OFFSET, CAMERA_TARGET_OFFSET, CAMERA_TARGET_OFFSET }
    );

    const int BGM_VOLUME = 15;                         

    soundManager.Add(
        SoundManager::TYPE::BGM,
        SoundManager::SOUND::BGM_GUILD,
        resourceManager.Load(ResourceManager::SRC::BGM_GUILD).handleId_
    );

    soundManager.AdjustVolume(SoundManager::SOUND::BGM_GUILD, BGM_VOLUME);
    soundManager.Play(SoundManager::SOUND::BGM_GUILD);

    bulletinBoard_ = std::make_shared<BulletinBoard>();
    bulletinBoard_->Init();
    collisionManager.Register(bulletinBoard_);

    receptionist_ = std::make_shared<Receptionist>();
    receptionist_->Init();
    receptionist_->SetPlayer(stageManager_->GetPlayer());
    collisionManager.Register(receptionist_);

    teleportMovement_ = std::make_shared<TeleportMovement>(stageManager_);
    teleportMovement_->Init();
    collisionManager.Register(teleportMovement_);

    counter_ = std::make_shared<Counter>();
    counter_->Init();
    collisionManager.Register(counter_);

    wall_ = std::make_shared<WallGuild>();
    wall_->Init();
    collisionManager.Register(wall_);

    wall2_ = std::make_shared<WallGuild2>();
    wall2_->Init();
    collisionManager.Register(wall2_);

    wallZ_ = std::make_shared<WallGuild3>();
    wallZ_->Init();
    collisionManager.Register(wallZ_);

    wallZZ_ = std::make_shared<WallGuild4>();
    wallZZ_->Init();
    collisionManager.Register(wallZZ_);

    tableSetGuildManager_ = std::make_unique<TableSetGuildManager>();
    tableSetGuildManager_->Init();

    for (auto& table : tableSetGuildManager_->GetTableSets())
    {
        collisionManager.Register(table);
    }
}

void GuildStage::Update(void)
{
    auto& inputManager = InputManager::GetInstance();
    auto& application = Application::GetInstance();

#ifdef _DEBUG
    if (inputManager.IsTriggerDown(KEY_INPUT_P) && stageManager_ != nullptr)
    {
        stageManager_->ChangeStage(StageManager::STAGE_ID::ATELIER);
    }
#endif

    switch (application.GetActiveUIType())
    {
    case Application::ACTIVE_UI_TYPE::NONE:
        bulletinBoard_->Update();
        receptionist_->Update();
        teleportMovement_->Update();
        break;

    case Application::ACTIVE_UI_TYPE::QUEST:
        bulletinBoard_->Update();
        break;

    case Application::ACTIVE_UI_TYPE::DELIVERY:
    case Application::ACTIVE_UI_TYPE::SHOP:
        receptionist_->Update();
        break;

    case Application::ACTIVE_UI_TYPE::TELEPORT:
        teleportMovement_->Update();
        break;
    }

    counter_->Update();
    wall_->Update();
    wall2_->Update();
    wallZ_->Update();
    wallZZ_->Update();
    tableSetGuildManager_->Update();

    if (!bulletinBoard_->GetQuestList() &&
        !receptionist_->GetShopUiVisible() &&
        !receptionist_->GetDeliveryMenu())
    {
        pauseUiCount_--;
    }
    else
    {
        pauseUiCount_ = PAUSE_UI_COUNT;
    }

    if (pauseUiCount_ <= 0)
    {
        application.SetActiveUIType(Application::ACTIVE_UI_TYPE ::NONE);
        pauseUiCount_ = PAUSE_UI_COUNT;
    }
}

void GuildStage::Draw(void)
{
    if (modelId_ != -1)
    {
        MV1DrawModel(modelId_);
    }

    bulletinBoard_->DrawModel();
    receptionist_->DrawModel();
    counter_->Draw();
    wall_->Draw();
    wall2_->Draw();
    wallZ_->Draw();
    wallZZ_->Draw();
    tableSetGuildManager_->Draw();
    bulletinBoard_->DrawUI();
    QuestUI::GetInstance().Draw();
    receptionist_->DrawUI();
    teleportMovement_->Draw();
}

void GuildStage::Release(void)
{
    if (modelId_ != -1)
    {
        MV1DeleteModel(modelId_);
        modelId_ = -1;
    }
}