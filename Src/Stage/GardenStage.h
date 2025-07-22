#pragma once

#include <memory>

#include "StageBase.h"

class BlockManager;
class StageManager;
class PlantManager;
class FenceManager;
class OreManager;
class Warp;
class WellObject;
class DateTimeManager;

class GardenStage : public StageBase
{
public:
	enum class TimeZone
	{
		MORNING,
		DAY,
		EVENING,
		NIGHT
	};

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

	FenceManager* fenceManager_;

	DateTimeManager* dateTimeManager_;

	std::shared_ptr<Warp> warp_;

	std::shared_ptr<WellObject> well_;

	TimeZone currentTimeZone_;

};