#include "StageManager.h"

#include <DxLib.h>
#include <cassert>

#include "../../Stage/StageBase.h"
#include "../../Stage/AtelierStage.h"
#include "../../Stage/GardenStage.h"
#include "../../Stage/GuildStage.h"
#include "../../Stage/PrivateRoomStage.h"
#include "CollisionManager.h"

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
void StageManager::Init(void)
{
	stageId_ = STAGE_ID::NONE;
	waitStageId_ = STAGE_ID::NONE;
	stage_ = nullptr; 
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

	// ステージ遷移フラグのチェックを先に行う
	if (isStageChanging_)
	{
		DoChangeStage(waitStageId_);
		isStageChanging_ = false;
		return;  // 切り替え後は更新処理をスキップ
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
}

//ステージ遷移
void StageManager::ChangeStage(STAGE_ID nextId)
{
	waitStageId_ = nextId;

	// 既存のステージのオブジェクトをクリア
	CollisionManager::GetInstance().Clear();

	isStageChanging_ = true;
}

//ステージ遷移本体
void StageManager::DoChangeStage(STAGE_ID stageId)
{
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
		break;

	case StageManager::STAGE_ID::GARDEN:
		stage_ = new GardenStage(this);
		break;

	case StageManager::STAGE_ID::GUILD:
		stage_ = new GuildStage(this);
		break;

	case StageManager::STAGE_ID::PRIVATE_ROOM:
		stage_ = new PrivateRoomStage();
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