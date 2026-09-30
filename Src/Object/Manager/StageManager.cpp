#include "StageManager.h"

#include <DxLib.h>
#include <cassert>

#include "../../Manager/Decoration/SoundManager.h"
#include "../../Stage/StageBase.h"
#include "../../Stage/AtelierStage.h"
#include "../../Stage/GardenStage.h"
#include "../../Stage/GuildStage.h"
#include "../../Stage/PrivateRoomStage.h"
#include "CollisionManager.h"
#include "../../Common/Fader.h"
#include "../../Object/Player.h"
#include "../../DrawUI/SceneUI/GameHUD.h"
#include "../PlayerStop.h"

StageManager::StageManager(void)
{
    stageId_ = STAGE_ID::NONE;
    waitStageId_ = STAGE_ID::NONE;
    stage_ = nullptr;
    isStageChanging_ = false;

    const float DEFAULT_DELTA_TIME = 1.0f / 60.0f;      // デフォルトのデルタタイム
    deltaTime_ = DEFAULT_DELTA_TIME;
}

StageManager::~StageManager(void)
{
    Destroy();
}

void StageManager::Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager)
{
    player_ = player;
    stageId_ = STAGE_ID::NONE;
    waitStageId_ = STAGE_ID::NONE;
    stage_ = nullptr;

    fader_ = std::make_unique<Fader>();
    fader_->Init();

    gameHUD_ = std::make_unique<GameHUD>();
    gameHUD_->Init(player_, dateTimeManager);

    DoChangeStage(STAGE_ID::ATELIER);
}

void StageManager::Destroy(void)
{
    if (stage_ != nullptr)
    {
        stage_->Release();
        delete stage_;
        stage_ = nullptr;
    }
}

void StageManager::Update(void)
{
    auto currentTime = std::chrono::system_clock::now();
    deltaTime_ = std::chrono::duration<float>(currentTime - previousTime_).count();
    previousTime_ = currentTime;

    gameHUD_->Update();

    if (fader_ != nullptr)
    {
        fader_->Update();
    }

    if (isStageChanging_)
    {
        Fade();
        return;
    }

    if (stage_ != nullptr)
    {
        stage_->Update();
    }
}

void StageManager::Draw(void)
{
    if (stage_ != nullptr)
    {
        stage_->Draw();
    }

    gameHUD_->Draw();

    if (fader_ != nullptr)
    {
        fader_->Draw();
    }
}

void StageManager::ChangeStage(STAGE_ID nextId)
{
    if (isStageChanging_)
    {
        return;
    }

    waitStageId_ = nextId;

    CollisionManager::GetInstance().Clear();

    if (fader_ != nullptr)
    {
        fader_->SetFade(Fader::STATE::FADE_OUT);
    }

    isStageChanging_ = true;
}

void StageManager::DoChangeStage(STAGE_ID stageId)
{
    auto& soundManager = SoundManager::GetInstance();

    if (stageId_ == STAGE_ID::ATELIER)
    {
        soundManager.Stop(SoundManager::SOUND::BGM_ATELIER);
    }
    else if (stageId_ == STAGE_ID::GUILD)
    {
        soundManager.Stop(SoundManager::SOUND::BGM_GUILD);
    }
    else if (stageId_ == STAGE_ID::GARDEN)
    {
        soundManager.Stop(SoundManager::SOUND::BGM_GARDEN_DAY);
        soundManager.Stop(SoundManager::SOUND::BGM_GARDEN_NIGHT);
    }

    if (stage_ != nullptr)
    {
        stage_->Release();
        delete stage_;
        stage_ = nullptr;
    }

    stageId_ = stageId;

    switch (stageId_)
    {
    case STAGE_ID::ATELIER:
    {
        stage_ = new AtelierStage(this);
        PlayerStop::GetInstance().ResumeMovement();
        Application::GetInstance().SetActiveUI(false);
        break;
    }
    case STAGE_ID::GARDEN:
    {
        stage_ = new GardenStage(this);
        PlayerStop::GetInstance().ResumeMovement();
        Application::GetInstance().SetActiveUI(false);
        break;
    }
    case STAGE_ID::GUILD:
    {
        stage_ = new GuildStage(this);                  // コンパイルエラー箇所を修正
        PlayerStop::GetInstance().ResumeMovement();
        Application::GetInstance().SetActiveUI(false);
        break;
    }
    case STAGE_ID::PRIVATE_ROOM:
    {
        stage_ = new PrivateRoomStage();
        PlayerStop::GetInstance().ResumeMovement();
        Application::GetInstance().SetActiveUI(false);
        break;
    }
    case STAGE_ID::NONE:
    {
        break;
    }
    }

    if (stage_ != nullptr)
    {
        stage_->Init();
    }

    ResetDeltaTime();

    waitStageId_ = STAGE_ID::NONE;
}

void StageManager::ResetDeltaTime(void)
{
    const float DEFAULT_DELTA_TIME = 1.0f / 60.0f;      // デフォルトのデルタタイム

    deltaTime_ = DEFAULT_DELTA_TIME;
    previousTime_ = std::chrono::system_clock::now();
}

StageManager::STAGE_ID StageManager::GetStageID(void) const
{
    return stageId_;
}

float StageManager::GetDeltaTime(void) const
{
    return deltaTime_;
}

std::shared_ptr<Player> StageManager::GetPlayer(void)
{
    return player_;
}

void StageManager::Fade(void)
{
    if (fader_ == nullptr)
    {
        return;
    }

    switch (fader_->GetState())
    {
    case Fader::STATE::FADE_OUT:
    {
        if (fader_->IsEnd())
        {
            if (waitStageId_ != STAGE_ID::NONE)
            {
                DoChangeStage(waitStageId_);
                waitStageId_ = STAGE_ID::NONE;
                fader_->SetFade(Fader::STATE::FADE_IN);

                if (player_ != nullptr)
                {
                    const float DEFAULT_PLAYER_X = 0.0f;            // プレイヤー初期位置X
                    const float DEFAULT_PLAYER_Y = 20.0f;           // プレイヤー初期位置Y
                    const float DEFAULT_PLAYER_Z = -200.0f;         // プレイヤー初期位置Z

                    VECTOR defaultPosition = {
                        DEFAULT_PLAYER_X,
                        DEFAULT_PLAYER_Y,
                        DEFAULT_PLAYER_Z
                    };

                    switch (stageId_)
                    {
                    case STAGE_ID::GUILD:
                    case STAGE_ID::ATELIER:
                    case STAGE_ID::GARDEN:
                    {
                        player_->SetPosition(defaultPosition);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                }
            }
        }
        break;
    }
    case Fader::STATE::FADE_IN:
    {
        if (fader_->IsEnd())
        {
            fader_->SetFade(Fader::STATE::NONE);
            isStageChanging_ = false;
        }
        break;
    }
    default:
    {
        break;
    }
    }
}