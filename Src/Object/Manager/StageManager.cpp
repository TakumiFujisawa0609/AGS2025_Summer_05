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
#include "../../Object/player.h"
#include "../../DrawUI/SceneUI/GameHUD.h"
#include "../PlayerStop.h"

//コンストラクタ
StageManager::StageManager(void)
{
	stageId_ = STAGE_ID::NONE;
	waitStageId_ = STAGE_ID::NONE;
	stage_ = nullptr;
	isStageChanging_ = false;
	deltaTime_ = 1.0f / 60.0f;
}

//デストラクタ
StageManager::~StageManager(void)
{
	Destroy();
}

//初期化処理
void StageManager::Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager)
{
	player_ = player;
	stageId_ = STAGE_ID::NONE;
	waitStageId_ = STAGE_ID::NONE;
	stage_ = nullptr; 

	// フェード用UI
	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// 初期化時
	gameHUD_ = std::make_unique<GameHUD>();
	gameHUD_->Init(player_, dateTimeManager);

	DoChangeStage(STAGE_ID::ATELIER);
}

//破棄処理
void StageManager::Destroy(void)
{
	if (stage_ != nullptr)
	{
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}
}

//更新処理
void StageManager::Update(void)
{
	// デルタタイムの計算
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = std::chrono::duration<float>(nowTime - preTime_).count();
	preTime_ = nowTime;

	gameHUD_->Update();

	// フェード更新
	if (fader_) fader_->Update();

	// ステージ切り替えフェーズ中ならフェード処理を進める（ここでDoChangeStageは呼ぶ）
	if (isStageChanging_)
	{
		Fade();  // ←ここだけ
		return;  // ステージ切り替え中はそれ以外の処理を止める
	}

	// 通常の更新処理
	if (stage_)
	{
		stage_->Update();
	}
}

//描画処理
void StageManager::Draw(void)
{
	if (stage_)
	{
		stage_->Draw();
	}

	gameHUD_->Draw();

	if (fader_) fader_->Draw();
}

//ステージ遷移
void StageManager::ChangeStage(STAGE_ID nextId)
{
	if (isStageChanging_) return;  // 二重呼び出し防止

	waitStageId_ = nextId;

	// 当たり判定をクリア
	CollisionManager::GetInstance().Clear();

	// フェードアウト開始
	if (fader_)
	{
		fader_->SetFade(Fader::STATE::FADE_OUT);
	}
	isStageChanging_ = true;
}

//ステージ遷移本体
void StageManager::DoChangeStage(STAGE_ID stageId)
{
	auto& sound = SoundManager::GetInstance();

	//現在のステージがアトリエならBGMを停止する
	if (stageId_ == STAGE_ID::ATELIER)
	{
		sound.Stop(SoundManager::SOUND::BGM_ATELIER);
	}
	else if (stageId_ == STAGE_ID::GUILD)
	{
		sound.Stop(SoundManager::SOUND::BGM_GUILD);
	}
	else if (stageId_ == STAGE_ID::GARDEN)
	{
		sound.Stop(SoundManager::SOUND::BGM_GARDEN_DAY);
		sound.Stop(SoundManager::SOUND::BGM_GARDEN_NIGHT);
	}


	// 既存のステージを削除
	if (stage_ != nullptr)
	{
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}

	stageId_ = stageId;

	switch (stageId_)
	{
	case StageManager::STAGE_ID::ATELIER:
		stage_ = new AtelierStage(this);
		PlayerStop::GetInstance().ResumeMovement();
		Application::GetInstance().SetActiveUI(false);
		break;

	case StageManager::STAGE_ID::GARDEN:
		stage_ = new GardenStage(this);
		PlayerStop::GetInstance().ResumeMovement();
		Application::GetInstance().SetActiveUI(false);
		break;

	case StageManager::STAGE_ID::GUILD:
		stage_ = new GuildStage(this);
		PlayerStop::GetInstance().ResumeMovement();
		Application::GetInstance().SetActiveUI(false);
		break;

	case StageManager::STAGE_ID::PRIVATE_ROOM:
		stage_ = new PrivateRoomStage();
		PlayerStop::GetInstance().ResumeMovement();
		Application::GetInstance().SetActiveUI(false);
		break;
	}

	if (stage_)
	{
		stage_->Init();
	}

	ResetDeltaTime();

	waitStageId_ = STAGE_ID::NONE;
}

//デルタタイムのリセット
void StageManager::ResetDeltaTime(void)
{
	deltaTime_ = 1.0f / 60.0f;
	preTime_ = std::chrono::system_clock::now();
}

//ステージIDの取得
StageManager::STAGE_ID StageManager::GetStageID() const
{
	return stageId_;
}

//デルタタイムの取得
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
	if (!fader_) return;

	switch (fader_->GetState())
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			if (waitStageId_ != STAGE_ID::NONE)
			{
				DoChangeStage(waitStageId_);
				waitStageId_ = STAGE_ID::NONE;
				fader_->SetFade(Fader::STATE::FADE_IN);
				if (player_)
				{
					switch (stageId_)
					{
					case STAGE_ID::GUILD:
						player_->SetPos({ 0, 20, -200 });
						break;
					case STAGE_ID::ATELIER:
						player_->SetPos({ 0, 20, -200 });
						break;
					case STAGE_ID::GARDEN:
						player_->SetPos({ 0, 20, -200 });
						break;
					default:
						break;
					}
				}
			}
		}
		break;

	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			fader_->SetFade(Fader::STATE::NONE);
			isStageChanging_ = false;
		}
		break;

	default:
		break;
	}
}

