#pragma once

#include <memory>

#include "StageBase.h"

class BlockManager;
class StageManager;
class PlantManager;
class OreManager;

class GardenStage : public StageBase
{
public:
	//コンストラクタ
	GardenStage(StageManager* stageManager);

	//デストラクタ
	~GardenStage(void) = default;

	//初期化処理
	void Init(void) override;

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放処理
	void Release(void) override;

private:
	BlockManager* blockManager_;

	// StageManagerの参照
	StageManager* stageManager_;

	PlantManager* plantManager_;

	OreManager* oreManager_;
};