#include "StageManager.h"

#include<DxLib.h>
#include<cassert>

#include"../../Stage/StageBase.h"
#include"../../Stage/AtelierStage.h"
#include"../../Stage/GardenStage.h"
#include"../../Stage/GuildStage.h"
#include"../../Stage/PrivateRoomStage.h"

StageManager* StageManager::instance_ = nullptr;

//インスタンスの生成
void StageManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new StageManager();
		instance_->Init();
	}
}

//インスタンスの取得
StageManager& StageManager::GetInstance(void)
{
	assert(instance_);
	return *instance_;
}


//コンストラクタ
StageManager::StageManager(void)
{
	stageId_ = STAGE_ID::NONE;
	waitStageId_ = STAGE_ID::NONE;
	stage_ = nullptr;
	isStageChanging_ = false;
	deltaTime_ = 1.0f / 60.0f;
}

//初期化処理
void StageManager::Init(void)
{
	stageId_ = STAGE_ID::NONE;
	waitStageId_ = STAGE_ID::NONE;
	stage_ = new AtelierStage();
	stage_->Init();

	DoChangeStage(STAGE_ID::ATELIER);
}

//破棄処理
void StageManager::Destroy(void)
{

	stage_->Release();
	delete stage_;
	stage_ = nullptr;

	delete instance_;
}

//更新処理
void StageManager::Update(void)
{
	//デルタタイムの計算
	auto nowTime = std::chrono::system_clock::now();

	deltaTime_ = std::chrono::duration<float>(nowTime - preTime_).count();

	preTime_ = nowTime;

	if (isStageChanging_)
	{
		DoChangeStage(waitStageId_);
		isStageChanging_ = false;
	}
	else if (stage_)
	{
		stage_->Update();
	}
}

//描画処理
void StageManager::Draw(void)
{
	// 前フレームの内容を消去（重要）
	ClearDrawScreen();
	stage_->Draw();
}

//ステージ遷移
void StageManager::ChangeStage(STAGE_ID nextId)
{
	waitStageId_ = nextId;

	isStageChanging_ = true;
}

//ステージ遷移本体
void StageManager::DoChangeStage(STAGE_ID stageId)
{
	stageId_ = stageId;

	if (stage_ != nullptr)
	{
		stage_->Release();
		delete stage_;
	}
	
	switch (stageId_)
	{
	case StageManager::STAGE_ID::ATELIER:
		stage_ = new AtelierStage();
		break;

	case StageManager::STAGE_ID::GARDEN:
		stage_ = new GardenStage();
		break;

	case StageManager::STAGE_ID::GUILD:
		stage_ = new GuildStage();
		break;

	case StageManager::STAGE_ID::PRIVATE_ROOM:
		stage_ = new PrivateRoomStage();
		break;
	}

	stage_->Init();

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
