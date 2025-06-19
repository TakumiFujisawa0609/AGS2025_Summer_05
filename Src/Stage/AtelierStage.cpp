#include<DxLib.h>
#include "AtelierStage.h"
#include"../Application.h"
#include"../Manager/Generic/Resource.h"
#include"../Manager/Generic/ResourceManager.h"
#include"../Manager/Generic/InputManager.h"
#include"../Object/Manager/StageManager.h"
#include "../Object/AtelierObject/AlchemyPot.h"
#include "../Object/Manager/CollisionManager.h"

//コンストラクタ
AtelierStage::AtelierStage(StageManager* stageManager) : stageManager_(stageManager)
{

}

//初期化処理
void AtelierStage::Init(void)
{
	// 鍋
	modelId_ = MV1LoadModel("Data/Model/Stage/Grand.mv1");

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
	CollisionManager::GetInstance().Register(alchemyPot_);

	teleportt_ = std::make_shared<Teleport>(stageManager_);
	teleportt_->Init();
	CollisionManager::GetInstance().Register(teleportt_);
}

void AtelierStage::Update(void)
{
	auto& input = InputManager::GetInstance();
	alchemyPot_->Update();
	teleportt_->Update();

	// ステージ遷移(デバッグ)
	if (input.IsTrgDown(KEY_INPUT_P))
	{
		//ステージ遷移
		if (stageManager_)
		{
			stageManager_->ChangeStage(StageManager::STAGE_ID::GARDEN);
		}
	}
}

//描画処理
void AtelierStage::Draw(void)
{
	DrawFormatString(0, 20, 0xffffff, "アトリエステージ");

	// 鍋の描画
	if (isModelId_)
	{
		MV1DrawModel(modelId_);
	}

	alchemyPot_->Draw();
	teleportt_->Draw();
}

//解放処理
void AtelierStage::Release(void)
{
	// メモリから解放する
	MV1DeleteModel(modelId_);
}