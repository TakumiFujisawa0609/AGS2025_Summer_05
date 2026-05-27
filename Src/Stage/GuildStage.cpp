#include "guildStage.h"

#include<DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Object/Manager/StageManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Object/GuildObject/BulletinBoard.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Object/GuildObject/ WallGuild.h"
#include "../Object/GuildObject/ WallGuild2.h"
#include "../Object/GuildObject/ WallGuildZ.h"
#include "../Object/GuildObject/WallGuildZZ.h"
#include "../Object/GuildObject/TableSetGuild.h"
#include "../Object/Manager/TableSetGuildManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/Camera.h"
#include "../Object/player.h"
#include "../DrawUI/SceneUI/QuestUI.h"


//コンストラクタ
GuildStage::GuildStage(StageManager* stageManager) : stageManager_(stageManager)
{

}

//初期化処理
void GuildStage::Init(void)
{
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();

	modelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::STAGE_ATELIER);

	modelIdPos_ = INIT_MODELID_POS;

	pauseUiCount_ = PAUSE_UI_COUNT;

	// 座標をモデルに設定
	MV1SetPosition(modelId_, modelIdPos_);

	// ステージの大きさ
	MV1SetScale(modelId_, MODELID_SCALEA);


	MV1SetRotationXYZ(modelId_, { 0, 0, 0 });

	//カメラ設定
	auto camera = SceneManager::GetInstance().GetCamera();

	camera->ChangeMode(Camera::MODE::FIXED_POINT);

	auto player = stageManager_->GetPlayer();
	camera->SetPos(Camera::DEFAULT_CAMERA_POS, { 0.0f,0.0f,0.0f });

	//BGMの追加
	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_GUILD, res.Load(ResourceManager::SRC::BGM_GUILD).handleId_);

	//BGMの音量調整
	sound.AdjustVolume(SoundManager::SOUND::BGM_GUILD, 15);

	sound.Play(SoundManager::SOUND::BGM_GUILD);
	
	//camera->SetFollow(&player->GetTransform());

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

	counter_ = std::make_shared<Counter>();
	counter_->Init();
	CollisionManager::GetInstance().Register(counter_);

	wall_ = std::make_shared<WallGuild>();
	wall_->Init();
	CollisionManager::GetInstance().Register(wall_);

	wall2_ = std::make_shared<WallGuild2>();
	wall2_->Init();
	CollisionManager::GetInstance().Register(wall2_);

	wallZ_ = std::make_shared<WallGuildZ>();
	wallZ_->Init();
	CollisionManager::GetInstance().Register(wallZ_);

	wallZZ_ = std::make_shared<WallGuildZZ>();
	wallZZ_->Init();
	CollisionManager::GetInstance().Register(wallZZ_);

	tableSetGuildManager_ = std::make_unique<TableSetGuildManager>();
	tableSetGuildManager_->Init();

	for (auto& table : tableSetGuildManager_->GetTableSets())
	{
		CollisionManager::GetInstance().Register(table);
	}
}

// 更新処理
void GuildStage::Update(void)
{
    auto& input = InputManager::GetInstance();
    auto& app = Application::GetInstance();

#ifdef _DEBUG
    if (input.IsTrgDown(KEY_INPUT_P) && stageManager_) {
        stageManager_->ChangeStage(StageManager::STAGE_ID::ATELIER);
    }
#endif

    // UI優先度管理
    switch (app.GetActiveUI()) {
    case ActiveUI::NONE:
        bulletinBoard_->Update();
        receptionist_->Update();
        teleportMovement_->Update();
        break;

    case ActiveUI::QUEST:
        bulletinBoard_->Update();
        break;

    case ActiveUI::DELIVERY:
    case ActiveUI::SHOP:
        receptionist_->Update();
        break;

    case ActiveUI::TELEPORT:
        teleportMovement_->Update();
        break;
    }

    counter_->Update();
    wall_->Update();
    wall2_->Update();
    wallZ_->Update();
    wallZZ_->Update();
    tableSetGuildManager_->Update();

    // UI非表示時のカウント管理
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
        app.SetsActiveUI(ActiveUI::NONE);
        pauseUiCount_ = PAUSE_UI_COUNT;
    }
}

//描画処理
void GuildStage::Draw(void)
{
	//DrawFormatString(0, 20, 0xffffff, "ギルド");

	MV1DrawModel(modelId_);

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

//解放処理
void GuildStage::Release(void)
{

}