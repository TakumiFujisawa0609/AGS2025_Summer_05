#pragma once

#include <DxLib.h>
#include <memory>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class InventoryUI;
class Player;

class ItemBox : public HitObject, public UnitBase
{
public:

	static constexpr float RADIUS = 50.0f;
	static constexpr VECTOR SCALE = {0.4f, 0.4f, 0.4f };
	static constexpr VECTOR MODEL_POS = { -335.0f, 0.0f, -300.0f };

	ItemBox();
	~ItemBox();

	void SetPlayer(std::shared_ptr<Player> player);
	void Init(void);
	void Update(void) override;
	void Draw(void) override;
	void DrawUI(void);
	void Release(void) override;

	// 当たり判定
	HIT_TYPE GetHitType(void) const override;
	VECTOR GetHitPosition(void) const override;
	float GetHitRadius(void) const override;

	// UI制御
	void ShowUI(void) override;
	void HideUI(void) override;

	bool IsValid(void) const override;

	// プレイヤーとの接触
	void OnPlayerHit(void) override;
	void OnPlayerExit(void) override;

	bool IsVisible(void) const;

private:

	bool isShowUI_;          // UI接近表示（"アイテムボックス"）
	bool isInventoryOpen_;   // インベントリUI表示

	InventoryUI* inventoryUI_;
	std::shared_ptr<Player> player_;
};
