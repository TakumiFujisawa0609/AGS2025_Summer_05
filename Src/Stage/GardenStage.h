#pragma once

#include <memory>

#include "StageBase.h"

class BlockManager;
class StageManager;
class PlantManager;
class FenceManager;
class OreManager;
class Warp;
class WellObject;
class DateTimeManager;

/// @brief ガーデンステージの管理・描画を行うクラス
class GardenStage : public StageBase
{
public:

    /// @brief 時間帯を定義する列挙型
    enum class TimeZone
    {
        MORNING,    // 朝
        DAY,        // 昼
        EVENING,    // 夕方
        NIGHT       // 夜
    };

    /// @brief コンストラクタ
    /// @param stageManager ステージマネージャーのポインタ
    GardenStage(StageManager* stageManager);

    /// @brief デストラクタ
    virtual ~GardenStage(void) override = default;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

private:

    // マネージャー関連
    BlockManager* blockManager_;            // ブロックマネージャー
    StageManager* stageManager_;            // ステージマネージャーの参照
    PlantManager* plantManager_;            // 植物マネージャー
    OreManager* oreManager_;                // 鉱石マネージャー
    FenceManager* fenceManager_;            // フェンスマネージャー
    DateTimeManager* dateTimeManager_;      // 日時マネージャー

    // オブジェクト関連
    std::shared_ptr<Warp> warp_;            // ワープオブジェクト
    std::shared_ptr<WellObject> well_;      // 井戸オブジェクト

    // 現在の時間帯
    TimeZone currentTimeZone_;              
};