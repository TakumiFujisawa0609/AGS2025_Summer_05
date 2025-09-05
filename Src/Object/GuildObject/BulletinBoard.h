#pragma once

#include <DxLib.h>
#include <memory>
#include <string>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class BulletinBoard : public HitObject, public UnitBase
{
public:
	static constexpr int UI_ENTER_DELAY_FRAME = 10; // 入力無視フレーム数

	static constexpr int UI_SHOW_DELAY_MAX = 30;  // UI持続猶予の最大フレーム数（適宜調整）

	static constexpr float UI_CLOSE_DISTANCE = 100.0f;


	//半径
	static constexpr float RADIUS = 50.0f;

	//モデルの大きさ
	static constexpr VECTOR SCALE = { 0.05f,0.05f,0.05f };

	//モデルのモデル座標用
	static constexpr VECTOR MODEL_POS = { 200.0f,-5.0f,350.0f };

	//コンストラクタ
	BulletinBoard(void);

	//デストラクタ
	~BulletinBoard(void);

	//初期化処理
	void Init(void);

	//更新処理
	void Update(void) override;

	void DrawModel(void);

	void DrawUI(void);

	//描画処理
	void Draw(void) override;

	//解放
	void Release(void)override;

	VECTOR GetHitMin(void) const;

	VECTOR GetHitMax(void) const;

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

	void UpdateUIVisibility(bool isHit) override;

	bool GetQuestList(void) const;

private:
	//掲示板の背景画像のID
	int imageBoardId_;

	int imageQuest_;

	int uiOpenWaitFrame_; // UIを開いたあとの猶予時間

	int uiShowUIDelayFrames_;
	
	//表示UIの判定
	bool isShowUI_;

	//依頼リスト表示フラグ
	bool isShowQuestList_;

	//選択中の依頼番号
	int selectedQuest_;

	//依頼リスト
	std::string questList_[3];
};