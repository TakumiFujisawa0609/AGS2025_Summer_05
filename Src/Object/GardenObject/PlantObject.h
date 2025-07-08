#pragma once

#include <DxLib.h>

#include "../UnitBase.h"
#include "../Interact/HitObject.h"

class PlantObject : public UnitBase, public HitObject
{
public:

	enum class GROW_STAGE
	{
		Sprout,
		MidGrowth,
		Mature
	};

	static constexpr float GROWTH_DURATION_SPROUT = 300.0f;
	static constexpr float GROWTH_DURATION_MID = 800.0f;

	PlantObject(void);

	~PlantObject(void);

	HIT_TYPE GetHitType(void) const override;

	VECTOR GetHitPosition(void) const override;

	float GetHitRadius(void) const override;

	void ShowUI(void) override;
	
	void HideUI(void) override;
	
	bool IsValid(void) const override;

	void OnPlayerHit(void) override;

	void OnPlayerExit(void) override;

	void Init(void);

	void Update(void) override;

	void Draw(void) override;

	void Release(void) override;

	bool CanHarvest(void) const;

	GROW_STAGE GetGrowthStage(void) const;

	void TryPlant(void);

	void TryHarvest(void);

	void SetActive(bool active);


	Transform& GetTransforms(void);

private:

	GROW_STAGE growthStage_;

	bool isActive_;

	bool isUIVisible_;

	bool hasPlant_;

	float growthStartTime_;

	int sproutModelId_;

	int midGrowthModelId_;

	int matureModelId_;

	void UpdateGrowthStage(float elapsedTime);

	void ChangeModelForStage(GROW_STAGE stage);
};

