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
class WallGuild3;
class WallGuild4;
class TableSetGuildManager;

/// @brief ギルドステージの管理・描画を行うクラス
class GuildStage : public StageBase
{
public:

    // モデルスケール・配置定数関連
    static constexpr VECTOR MODELID_SCALEA = { 4.0f, 2.2f, 4.0f };          // 背景モデルのスケール
    static constexpr VECTOR INIT_MODELID_POS = { 0.0f, 0.0f, 0.0f };        // 背景モデルの初期位置
    static constexpr float RADIUS_MODELID = 120.0f;                         // モデルの接触判定用半径

    // ポーズUIカウント最大値
    static constexpr int PAUSE_UI_COUNT = 2;                               

    /// @brief コンストラクタ
    /// @param stageManager ステージマネージャーのポインタ
    GuildStage(StageManager* stageManager);

    /// @brief デストラクタ
    virtual ~GuildStage(void) override = default;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

private:

    // ステージモデル情報関連
    int modelId_;                                       // ステージ背景モデルのハンドルID
    VECTOR modelIdPos_;                                 // ステージ背景モデルの座標
    int pauseUiCount_;                                  // UI非表示までの待機カウント

    // オブジェクト管理関連
    std::shared_ptr<BulletinBoard> bulletinBoard_;      // 掲示板
    std::shared_ptr<Receptionist> receptionist_;        // 受付嬢
    std::shared_ptr<TeleportMovement> teleportMovement_; // テレポート移動
    std::shared_ptr<Counter> counter_;                  // カウンター
    std::shared_ptr<WallGuild> wall_;                   // 壁（左など）
    std::shared_ptr<WallGuild2> wall2_;                 // 壁（右など）
    std::shared_ptr<WallGuild3> wallZ_;                 // 壁（奥）
    std::shared_ptr<WallGuild4> wallZZ_;                // 壁（手前）
    std::unique_ptr<TableSetGuildManager> tableSetGuildManager_; // テーブルセットマネージャー

    // ステージマネージャーへの参照
    StageManager* stageManager_;
};