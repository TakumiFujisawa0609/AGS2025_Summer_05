#include "guildStage.h"

#include<DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Object/GuildObject/BulletinBoard.h"
#include "../Object/Manager/CollisionManager.h"

//コンストラクタ
GuildStage::GuildStage(StageManager* stageManager) : stageManager_(stageManager)
{

}

//初期化処理
void GuildStage::Init(void)
{
	// 1つのインスタンスを作成
	bulletinBoard_ = std::make_shared<BulletinBoard>();
	bulletinBoard_->Init();
	CollisionManager::GetInstance().Register(bulletinBoard_);

	receptionist_ = std::make_shared<Receptionist>();
	receptionist_->Init();
	receptionist_->SetPlayer(stageManager_->GetPlayer());
	CollisionManager::GetInstance().Register(receptionist_);

	teleportMovement_ = std::make_shared<TeleportMovement>(stageManager_);
	teleportMovement_->Init();
	CollisionManager::GetInstance().Register(teleportMovement_);
}

//更新処理
void GuildStage::Update(void)
{
	auto& input = InputManager::GetInstance();

	//ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		if (stageManager_)
		{
			stageManager_->ChangeStage(StageManager::STAGE_ID::PRIVATE_ROOM);
		}
	}

	bulletinBoard_->Update();
	receptionist_->Update();
	teleportMovement_->Update();
}

//描画処理
void GuildStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "ギルド");

	receptionist_->Draw();
	teleportMovement_->Draw();
	bulletinBoard_->Draw();
}

//解放処理
void GuildStage::Release(void)
{

}