#pragma once

#include <memory>

#include "StageBase.h"

#include "../Object/GuildObject/BulletinBoard.h"
#include "../Object/GuildObject/Receptionist.h"
#include "../Object/GuildObject/TeleportMovement.h"
#include "../Object/GuildObject/Counter.h"

class StageManager;
class WallGuild;
class WallGuild2;
class WallGuildZ;
class WallGuildZZ;
class TableSetGuildManager;


class GuildStage : public StageBase
{
public:

	//ステージの大きさ
	static constexpr VECTOR MODELID_SCALEA = { 4.0f,2.2f,4.0f };

	// ステージの初期位置
	static constexpr VECTOR INIT_MODELID_POS = { 0.0f, 0.0f, 0.0f };

	// ステージの接触判定用半径
	static constexpr float RADIUS_MODELID = 120.0f;

	//ポーズUIカウント最大値
	static constexpr int PAUSE_UI_COUNT = 2.0f;

	//コンストラクタ
	GuildStage(StageManager* stageManager);

	//デストラクタ
	~GuildStage(void) = default;

	//初期化処理
	void Init(void) override;

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放処理
	void Release(void) override;

private:
	//ステージモデル
	int modelId_;

	//UIの表示カウント
	int pauseUiCount_;

	VECTOR modelIdPos_;

	std::shared_ptr<BulletinBoard> bulletinBoard_;
	std::shared_ptr<Receptionist> receptionist_;
	std::shared_ptr<TeleportMovement> teleportMovement_;
	std::shared_ptr<Counter> counter_;

	std::shared_ptr<WallGuild> wall_;
	std::shared_ptr<WallGuild2> wall2_;
	std::shared_ptr<WallGuildZ> wallZ_;
	std::shared_ptr<WallGuildZZ> wallZZ_;

	std::unique_ptr<TableSetGuildManager> tableSetGuildManager_;

	// StageManagerの参照
	StageManager* stageManager_;
};