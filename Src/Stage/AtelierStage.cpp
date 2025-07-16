#include<DxLib.h>
#include "AtelierStage.h"
#include"../Application.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Object/Manager/StageManager.h"
#include "../Object/AtelierObject/AlchemyPot.h"
#include "../Object/AtelierObject/Teleport.h"
#include "../Object/AtelierObject/WallAtelier.h"
#include "../Object/AtelierObject/WallAtelier2.h"
#include "../Object/AtelierObject/WallAtelierZ.h"
#include "../Object/AtelierObject/WallAtelierZZ.h"
#include "../Object/AtelierObject/TableSetAtelier.h"
#include "../Object/AtelierObject/ItemBox.h"
#include "../Object/Manager/CollisionManager.h"
#include "../Object/Manager/BookshelfManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/Camera.h"
#include "../Object/player.h"
#include "../DrawUI/SceneUI/QuestUI.h"

//コンストラクタ
AtelierStage::AtelierStage(StageManager* stageManager) : stageManager_(stageManager)
{

}

//初期化処理
void AtelierStage::Init(void)
{
	//カメラ設定
	auto camera = SceneManager::GetInstance().GetCamera();

	camera->ChangeMode(Camera::MODE::FIXED_POINT);

	auto player = stageManager_->GetPlayer();
	camera->SetPos(Camera::DEFAULT_CAMERA_POS, { 0.0f,0.0f,0.0f });
	//camera->SetFollow(&player->GetTransform());

	// 鍋
	modelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::STAGE_ATELIER);

	// 鍋の位置
	modelIdPos_ = INIT_MODELID_POS;
	// 座標をモデルに設定
	MV1SetPosition(modelId_, modelIdPos_);
	// 鍋の大きさ
	MV1SetScale(modelId_, MODELID_SCALEA);
	// 生存判定
	isModelId_ = true;

	alchemyPot_ = std::make_shared<AlchemyPot>();
	alchemyPot_->Init();
	alchemyPot_->SetPlayer(stageManager_->GetPlayer());
	CollisionManager::GetInstance().Register(alchemyPot_);

	teleportt_ = std::make_shared<Teleport>(stageManager_);
	teleportt_->Init();
	CollisionManager::GetInstance().Register(teleportt_);


	wall_ = std::make_shared<WallAtelier>();
	wall_->Init();
	CollisionManager::GetInstance().Register(wall_);

	wall2_ = std::make_shared<WallAtelier2>();
	wall2_->Init();
	CollisionManager::GetInstance().Register(wall2_);

	wallZ_ = std::make_shared<WallAtelierZ>();
	wallZ_->Init();
	CollisionManager::GetInstance().Register(wallZ_);

	wallZZ_ = std::make_shared<WallAtelierZZ>();
	wallZZ_->Init();
	CollisionManager::GetInstance().Register(wallZZ_);

	itemBox_ = std::make_shared<ItemBox>();
	itemBox_->Init();
	itemBox_->SetPlayer(stageManager_->GetPlayer());
	CollisionManager::GetInstance().Register(itemBox_);

	wallZZ_ = std::make_shared<WallAtelierZZ>();
	wallZZ_->Init();
	CollisionManager::GetInstance().Register(wallZZ_);

	tableSetAtelier_ = std::make_shared<TableSetAtelier>();
	tableSetAtelier_->Init();
	CollisionManager::GetInstance().Register(tableSetAtelier_);

	bookshelfManager_ = std::make_unique<BookshelfManager>();
	bookshelfManager_->Init();
	for (auto& table : bookshelfManager_->GetGetBookSets())
	{
		CollisionManager::GetInstance().Register(table);
	}


}

void AtelierStage::Update(void)
{
	auto& input = InputManager::GetInstance();
	alchemyPot_->Update();
	teleportt_->Update();
	bookshelfManager_->Update();
	wall_->Update();
	wall2_->Update();
	wallZ_->Update();
	wallZZ_->Update();
	itemBox_->Update();
	tableSetAtelier_->Update();

	// ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		if (stageManager_)
		{
			stageManager_->ChangeStage(StageManager::STAGE_ID::GARDEN);
		}
	}

#ifdef _DEBUG
	// ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		if (stageManager_)
		{
			stageManager_->ChangeStage(StageManager::STAGE_ID::GARDEN);
		}
	}
#endif // _DEBUG

	
}

//描画処理
void AtelierStage::Draw(void)
{
	//DrawFormatString(0, 20, 0xffffff, "アトリエステージ");

	// 鍋の描画
	if (isModelId_)
	{
		MV1DrawModel(modelId_);
	}
	tableSetAtelier_->Draw();
	bookshelfManager_->Draw();
	QuestUI::GetInstance().Draw();
	itemBox_->Draw();
	alchemyPot_->Draw();
	teleportt_->Draw();
	itemBox_->DrawUI();
	wall_->Draw();
	wall2_->Draw();
	wallZ_->Draw();
	wallZZ_->Draw();
	
	

}

//解放処理
void AtelierStage::Release(void)
{
	// メモリから解放する
	MV1DeleteModel(modelId_);
}