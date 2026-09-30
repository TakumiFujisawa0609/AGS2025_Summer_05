#include "AtelierStage.h"

#include <DxLib.h>
#include <EffekseerForDXLib.h>

#include "../Application.h"
#include "../Manager/Decoration/EffectManager.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Object/AtelierObject/AlchemyPot.h"
#include "../Object/AtelierObject/Teleport.h"
#include "../Object/AtelierObject/WallAtelier.h"
#include "../Object/AtelierObject/WallAtelier2.h"
#include "../Object/AtelierObject/WallAtelier3.h"
#include "../Object/AtelierObject/WallAtelier4.h"
#include "../Object/AtelierObject/TableSetAtelier.h"
#include "../Object/AtelierObject/ItemBox.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Object/Manager/BookshelfManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/Camera.h"
#include "../Object/player.h"
#include "../DrawUI/SceneUI/QuestUI.h"

AtelierStage::AtelierStage(StageManager* stageManager)
    : stageManager_(stageManager),
    modelId_(-1),
    pauseUiCount_(0)
{
}

void AtelierStage::Init(void)
{
    const float CAMERA_TARGET_OFFSET = 0.0f;            

    auto camera = SceneManager::GetInstance().GetCamera();
    auto& soundManager = SoundManager::GetInstance();
    auto& resourceManager = ResourceManager::GetInstance();
    auto& collisionManager = CollisionManager::GetInstance();

    camera->ChangeMode(Camera::MODE::FIXED_POINT);

    auto player = stageManager_->GetPlayer();
    camera->SetPosition(
        Camera::DEFAULT_CAMERA_POSITION,
        { CAMERA_TARGET_OFFSET, CAMERA_TARGET_OFFSET, CAMERA_TARGET_OFFSET }
    );

    modelId_ = resourceManager.LoadModelDuplicate(ResourceManager::SRC::STAGE_ATELIER);

    modelPosition_ = MODEL_INITIAL_POSITION;

    if (modelId_ != -1)
    {
        const float ROTATION_ZERO = 0.0f;               

        MV1SetPosition(modelId_, modelPosition_);
        MV1SetScale(modelId_, MODEL_SCALE);
        MV1SetRotationXYZ(modelId_, { ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO });
    }

    pauseUiCount_ = PAUSE_UI_COUNT_MAX;

    alchemyPot_ = std::make_shared<AlchemyPot>();
    alchemyPot_->Init();
    alchemyPot_->SetPlayer(stageManager_->GetPlayer());
    collisionManager.Register(alchemyPot_);

    teleport_ = std::make_shared<Teleport>(stageManager_);
    teleport_->Init();
    collisionManager.Register(teleport_);

    wallLeft_ = std::make_shared<WallAtelier>();
    wallLeft_->Init();
    collisionManager.Register(wallLeft_);

    wallRight_ = std::make_shared<WallAtelier2>();
    wallRight_->Init();
    collisionManager.Register(wallRight_);

    wallBack_ = std::make_shared<WallAtelier3>();
    wallBack_->Init();
    collisionManager.Register(wallBack_);

    wallFront_ = std::make_shared<WallAtelier4>();
    wallFront_->Init();
    collisionManager.Register(wallFront_);

    itemBox_ = std::make_shared<ItemBox>();
    itemBox_->Init();
    itemBox_->SetPlayer(stageManager_->GetPlayer());
    collisionManager.Register(itemBox_);

    tableSetAtelier_ = std::make_shared<TableSetAtelier>();
    tableSetAtelier_->Init();
    collisionManager.Register(tableSetAtelier_);

    bookshelfManager_ = std::make_unique<BookshelfManager>();
    bookshelfManager_->Init();

    for (auto& bookshelf : bookshelfManager_->GetBookshelves())
    {
        collisionManager.Register(bookshelf);
    }

    const int BGM_VOLUME = 20;                          

    soundManager.Add(
        SoundManager::TYPE::BGM,
        SoundManager::SOUND::BGM_ATELIER,
        resourceManager.Load(ResourceManager::SRC::BGM_ATELIER).handleId_
    );

    soundManager.AdjustVolume(SoundManager::SOUND::BGM_ATELIER, BGM_VOLUME);

    if (!soundManager.IsPlaying(SoundManager::SOUND::BGM_ATELIER))
    {
        soundManager.Play(SoundManager::SOUND::BGM_ATELIER);
    }

    EffectManager::GetInstance().Add(
        EffectManager::EFFECT::EFFECT_ALCHEMY,
        resourceManager.Load(ResourceManager::SRC::EFFECT_ALCHEMY).handleId_
    );
    EffectManager::GetInstance().Add(
        EffectManager::EFFECT::EFFECT_BLAST,
        resourceManager.Load(ResourceManager::SRC::EFFECT_BLAST).handleId_
    );
}

void AtelierStage::Update(void)
{
    alchemyPot_->Update();
    teleport_->Update();
    bookshelfManager_->Update();
    wallLeft_->Update();
    wallRight_->Update();
    wallBack_->Update();
    wallFront_->Update();
    itemBox_->Update();
    tableSetAtelier_->Update();

    if (!itemBox_->IsVisible() && !alchemyPot_->IsOpen() && !bookshelfManager_->IsValid())
    {
        pauseUiCount_--;
    }
    else if (itemBox_->IsVisible() || alchemyPot_->IsOpen() || bookshelfManager_->IsValid())
    {
        pauseUiCount_ = PAUSE_UI_COUNT_MAX;
    }

    if (pauseUiCount_ <= 0)
    {
        Application::GetInstance().SetActiveUI(false);
        pauseUiCount_ = PAUSE_UI_COUNT_MAX;
    }

#ifdef _DEBUG
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.IsTriggerDown(KEY_INPUT_P))
    {
        if (stageManager_ != nullptr)
        {
            stageManager_->ChangeStage(StageManager::STAGE_ID::GARDEN);
        }
    }

    if (inputManager.IsTriggerDown(KEY_INPUT_E))
    {
        const float EFFECT_POS_X = 0.0f;                // エフェクトのX座標
        const float EFFECT_POS_Y = 70.0f;               // エフェクトのY座標
        const float EFFECT_POS_Z = -50.0f;              // エフェクトのZ座標
        const float EFFECT_SCALE = 15.0f;               // エフェクトのスケール
        const float EFFECT_ROTATION_W = 1.0f;           // エフェクトの回転W成分

        EffectManager::GetInstance().Play(
            EffectManager::EFFECT::EFFECT_ALCHEMY,
            { EFFECT_POS_X, EFFECT_POS_Y, EFFECT_POS_Z },
            { 0.0f, 0.0f, 0.0f, EFFECT_ROTATION_W },
            EFFECT_SCALE,
            SoundManager::SOUND::SE_SELECT
        );
    }
#endif // _DEBUG
}

void AtelierStage::Draw(void)
{
    if (modelId_ != -1)
    {
        MV1DrawModel(modelId_);
    }

    tableSetAtelier_->Draw();
    bookshelfManager_->Draw();
    QuestUI::GetInstance().Draw();
    itemBox_->Draw();
    alchemyPot_->Draw();
    teleport_->Draw();
    itemBox_->DrawUI();
    bookshelfManager_->DrawUI();
    wallLeft_->Draw();
    wallRight_->Draw();
    wallBack_->Draw();
    wallFront_->Draw();
}

void AtelierStage::Release(void)
{
    if (modelId_ != -1)
    {
        MV1DeleteModel(modelId_);
        modelId_ = -1;
    }
}