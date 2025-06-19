#pragma once
#include "DxLib.h"
#include<memory>

#include "StageBase.h"
#include "../Object/AtelierObject/AlchemyPot.h"
#include "../Object/AtelierObject/Teleport.h"

class StageManager;

class AtelierStage : public StageBase
{
public:

	//鍋の大きさ
	static constexpr VECTOR MODELID_SCALEA = { 5.0f,5.0f,5.0f };

	// 鍋の初期位置
	static constexpr VECTOR INIT_MODELID_POS = { 0.0f, 0.0f, 0.0f };

	// 鍋の接触判定用半径
	static constexpr float RADIUS_MODELID = 120.0f;

	//コンストラクタ
	AtelierStage(StageManager* stageManager);

	//デストラクタ
	~AtelierStage(void) = default;

	//初期化処理
	void Init(void) override;

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放処理
	void Release(void) override;

private:

	// 球体位置
	VECTOR spherePos = { 0.0f, 20.0f, 0.0f };

	// 鍋
	int modelId_;
	VECTOR modelIdPos_;
	// 鍋の生存判定
	bool isModelId_;

	std::shared_ptr<AlchemyPot> alchemyPot_;
	std::shared_ptr<Teleport> teleportt_;

	// StageManagerの参照
	StageManager* stageManager_;
};