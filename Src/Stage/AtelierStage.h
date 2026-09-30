#pragma once
#include "DxLib.h"
#include <memory>

#include "StageBase.h"

class StageManager;
class AlchemyPot;
class Teleport;
class ItemBox;
class WallAtelier;
class WallAtelier2;
class WallAtelier3;
class WallAtelier4;
class TableSetAtelier;
class BookshelfManager;

/// @brief アトリエステージの管理・描画を行うクラス
class AtelierStage : public StageBase
{
public:

    // モデルスケール・配置定数関連
    static constexpr VECTOR MODEL_SCALE = { 4.0f, 2.2f, 4.0f };             // 背景モデルのスケール
    static constexpr VECTOR MODEL_INITIAL_POSITION = { 0.0f, 0.0f, 0.0f };  // 背景モデルの初期位置
    static constexpr float MODEL_RADIUS = 120.0f;                           // モデルの接触判定用半径

    // ポーズUIカウント最大値
    static constexpr int PAUSE_UI_COUNT_MAX = 2;                            

    /// @brief コンストラクタ
    /// @param stageManager ステージマネージャーのポインタ
    AtelierStage(StageManager* stageManager);

    /// @brief デストラクタ
    virtual ~AtelierStage(void) override = default;

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
    int modelId_;                           // ステージ背景モデルのハンドルID
    VECTOR modelPosition_;                  // ステージ背景モデルの座標

    // UI非表示までの待機カウント
    int pauseUiCount_;                     

    // オブジェクト管理関連
    std::shared_ptr<AlchemyPot> alchemyPot_;            // 錬金釜
    std::shared_ptr<Teleport> teleport_;                // テレポートポイント
    std::unique_ptr<BookshelfManager> bookshelfManager_;// 本棚マネージャー
    std::shared_ptr<WallAtelier> wallLeft_;             // 壁オブジェクト（左）
    std::shared_ptr<WallAtelier2> wallRight_;           // 壁オブジェクト（右）
    std::shared_ptr<WallAtelier3> wallBack_;            // 壁オブジェクト（奥）
    std::shared_ptr<WallAtelier4> wallFront_;           // 壁オブジェクト（手前）
    std::shared_ptr<ItemBox> itemBox_;                  // アイテムボックス
    std::shared_ptr<TableSetAtelier> tableSetAtelier_;  // テーブルセット

    // ステージマネージャーへの参照
    StageManager* stageManager_;
};