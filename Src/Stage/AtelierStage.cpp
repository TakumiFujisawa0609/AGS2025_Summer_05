#include "AtelierStage.h"

#include<DxLib.h>
#include<EffekseerForDXLib.h>

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
	auto& sound = SoundManager::GetInstance();
	auto& res = ResourceManager::GetInstance();
	auto& collision = CollisionManager::GetInstance();

	camera->ChangeMode(Camera::MODE::FIXED_POINT);

	auto player = stageManager_->GetPlayer();
	camera->SetPos(Camera::DEFAULT_CAMERA_POS, { 0.0f,0.0f,0.0f });
	//camera->SetFollow(&player->GetTransform());

	modelId_ = res.LoadModelDuplicate(ResourceManager::SRC::STAGE_ATELIER);

	// 位置
	modelIdPos_ = INIT_MODELID_POS;
	// 座標をモデルに設定
	MV1SetPosition(modelId_, modelIdPos_);
	// 大きさ
	MV1SetScale(modelId_, MODELID_SCALEA);

	MV1SetRotationXYZ(modelId_, { 0, 0, 0 });
	// 生存判定
	isModelId_ = true;

	pauseUiCount_ = PAUSE_UI_COUNT;

	alchemyPot_ = std::make_shared<AlchemyPot>();
	alchemyPot_->Init();
	alchemyPot_->SetPlayer(stageManager_->GetPlayer());
	collision.Register(alchemyPot_);

	teleportt_ = std::make_shared<Teleport>(stageManager_);
	teleportt_->Init();
	collision.Register(teleportt_);


	wall_ = std::make_shared<WallAtelier>();
	wall_->Init();
	collision.Register(wall_);

	wall2_ = std::make_shared<WallAtelier2>();
	wall2_->Init();
	collision.Register(wall2_);

	wallZ_ = std::make_shared<WallAtelierZ>();
	wallZ_->Init();
	collision.Register(wallZ_);

	wallZZ_ = std::make_shared<WallAtelierZZ>();
	wallZZ_->Init();
	collision.Register(wallZZ_);

	itemBox_ = std::make_shared<ItemBox>();
	itemBox_->Init();
	itemBox_->SetPlayer(stageManager_->GetPlayer());
	collision.Register(itemBox_);

	wallZZ_ = std::make_shared<WallAtelierZZ>();
	wallZZ_->Init();
	collision.Register(wallZZ_);

	tableSetAtelier_ = std::make_shared<TableSetAtelier>();
	tableSetAtelier_->Init();
	collision.Register(tableSetAtelier_);

	bookshelfManager_ = std::make_unique<BookshelfManager>();
	bookshelfManager_->Init();
	for (auto& table : bookshelfManager_->GetGetBookSets())
	{
		collision.Register(table);
	}

	//BGMの追加
	sound.Add(SoundManager::TYPE::BGM, SoundManager::SOUND::BGM_ATELIER, res.Load(ResourceManager::SRC::BGM_ATELIER).handleId_);

	//BGMの音量調整
	sound.AdjustVolume(SoundManager::SOUND::BGM_ATELIER, 20);


	if(sound.IsPlaying(SoundManager::SOUND::BGM_ATELIER) == false)
	{ 
		sound.Play(SoundManager::SOUND::BGM_ATELIER);
	}

	//エフェクトの追加
	EffectManager::GetInstance().Add(EffectManager::EFFECT::EFFECT_ALCHENY, res.Load(ResourceManager::SRC::EFFECT_ALCHEMY).handleId_);
	EffectManager::GetInstance().Add(EffectManager::EFFECT::EFFECT_BLAST, res.Load(ResourceManager::SRC::EFFECT_BLAST).handleId_);
	

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

	if (itemBox_->IsVisible() == false && alchemyPot_->isOpen() == false && bookshelfManager_->IsValid() == false)
	{
		pauseUiCount_--;
	}
	else if (itemBox_->IsVisible() == true || alchemyPot_->isOpen() == true || bookshelfManager_->IsValid() == true)
	{
		pauseUiCount_ = PAUSE_UI_COUNT;
	}
	

	if (pauseUiCount_ <= 0)
	{
		Application::GetInstance().SetActiveUI(false);
		pauseUiCount_ = PAUSE_UI_COUNT;
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

	// デバッグ用エフェクト再生
	if (input.IsTrgDown(KEY_INPUT_E))
	{
		EffectManager::GetInstance().Play(EffectManager::EFFECT::EFFECT_ALCHENY, {0.0f, 70.0f, -50.0f}, {0.0f, 0.0f, 0.0f,1.0f}, 15.0f, SoundManager::SOUND::SE_SELECT);
	}
#endif // _DEBUG

	
}

//描画処理
void AtelierStage::Draw(void)
{
	//DrawFormatString(0, 20, 0xffffff, "アトリエステージ");

	// 描画
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
	bookshelfManager_->DrawUI();
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