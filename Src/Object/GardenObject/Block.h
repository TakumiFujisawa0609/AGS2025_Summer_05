#pragma once

#include <DxLib.h>

#include "../Interact/HitObject.h"
#include "../../Manager/Generic/ResourceManager.h"

class Block : public HitObject
{
public:

	//コンストラクタ
	Block(ResourceManager::SRC modelType, const VECTOR& pos, float blockSize, float scale);

	//デストラクタ
	~Block(void);

	//更新処理
	void Update(void);

	//描画処理
	void Draw(void);

	//当たり判定のタイプ
	HIT_TYPE GetHitType(void) const override;

	//判定用の最小点を取得
	VECTOR GetHitMin(void) const override;

	// 判定用の最大点を取得
	VECTOR GetHitMax(void) const override;

	// UIを表示する処理
	void ShowUI(void) override;

	// UIを非表示にする処理
	void HideUI(void) override;

	void OnPlayerHit(void) override;

	void OnPlayerExit(void) override;
private:
	
	//モデルのハンドル
	int modelHandle_;

	//座標
	VECTOR pos_;

	//中心からの距離
	VECTOR halfSize_;
};