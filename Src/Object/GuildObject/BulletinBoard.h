#pragma once

#include <DxLib.h>
#include <memory>
#include <string>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class BulletinBoard : public HitObject, public UnitBase
{
public:

	//半径
	static constexpr float RADIUS = 50.0f;

	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.05f,0.05f,0.05f };

	//モデルのモデル座標用
	static constexpr VECTOR MODEL_POS = { 0.0f,50.0f,0.0f };

	//コンストラクタ
	BulletinBoard(void);

	//デストラクタ
	~BulletinBoard(void);

	//初期化処理
	void Init(void);

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放
	void Release(void)override;

	//HitObjectを継承
	VECTOR GetHitPosition(void) const override;

	float GetHitRadius(void) const override;

	//表示UI
	void ShowUI(void) override;

	//非表示UI
	void  HideUI(void) override;

	bool IsValid(void) const override;

private:
	//掲示板の背景画像のID
	int imageBoardId_;
	
	//表示UIの判定
	bool isShowUI_;

	//依頼リスト表示フラグ
	bool isShowQuestList_;

	//選択中の依頼番号
	int selectedQuest_;

	//依頼リスト
	std::string questList_[3];
};