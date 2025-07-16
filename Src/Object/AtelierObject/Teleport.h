#pragma once

#include <DxLib.h>
#include <memory>
#include <string>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class StageManager;

class TeleportUI;

class Teleport : public HitObject, public UnitBase
{
public:

	//半径
	static constexpr float RADIUS = 50.0f;

	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.05f,0.05f,0.05f };

	//モデルのモデル座標用
	static constexpr VECTOR MODEL_POS = { 0.0f,0.0f, -420.0f };

	//コンストラクタ
	Teleport(StageManager* stageManager);

	//デストラクタ
	~Teleport(void);

	//初期化処理
	void Init(void);

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放
	void Release(void)override;

	//HitObjectを継承

	HIT_TYPE GetHitType(void) const override;

	VECTOR GetHitPosition(void) const override;

	float GetHitRadius(void) const override;

	//表示UI
	void ShowUI(void) override;

	//非表示UI
	void  HideUI(void) override;

	bool IsValid(void) const override;

	void OnPlayerHit(void) override;

	void OnPlayerExit(void) override;

private:
	bool isShowUI_;
	StageManager* stageManager_;

	std::unique_ptr<TeleportUI> teleportUI_;

};