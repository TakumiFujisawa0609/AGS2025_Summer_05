#pragma once
#include "DxLib.h"
#include<memory>

#include "StageBase.h"


class StageManager;
class AlchemyPot;
class Teleport;
class ItemBox;
class WallAtelier;
class WallAtelier2;
class WallAtelierZ;
class WallAtelierZZ;
class TableSetAtelier;
class BookshelfManager;

class AtelierStage : public StageBase
{
public:

	//鍋の大きさ
	static constexpr VECTOR MODELID_SCALEA = { 4.0f,2.2f,4.0f };

	// 鍋の初期位置
	static constexpr VECTOR INIT_MODELID_POS = { 0.0f, 0.0f, 0.0f };

	// 鍋の接触判定用半径
	static constexpr float RADIUS_MODELID = 120.0f;

	//ポーズUIカウント最大値
	static constexpr int PAUSE_UI_COUNT = 2.0f;

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

	//UIの表示カウント
	int pauseUiCount_;

	VECTOR modelIdPos_;
	// 鍋の生存判定
	bool isModelId_;

	std::shared_ptr<AlchemyPot> alchemyPot_;
	std::shared_ptr<Teleport> teleportt_;
	std::unique_ptr<BookshelfManager> bookshelfManager_;
	std::shared_ptr<WallAtelier> wall_;
	std::shared_ptr<WallAtelier2> wall2_;
	std::shared_ptr<WallAtelierZ> wallZ_;
	std::shared_ptr<WallAtelierZZ> wallZZ_;
	std::shared_ptr<ItemBox> itemBox_;
	std::shared_ptr<TableSetAtelier> tableSetAtelier_;

	// StageManagerの参照
	StageManager* stageManager_;
};