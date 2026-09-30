#pragma once

#include <memory>
#include <chrono>
#include <vector>

#include "../../Application.h"
#include "../../Common/Fader.h"

class StageBase;
class Fader;
class Player;
class DateTimeManager;
class GameHUD;

/// @brief ステージの切り替えや進行管理を行うクラス
class StageManager
{
public:

    /// @brief ステージIDを定義する列挙型
    enum class STAGE_ID
    {
        NONE,           // なし
        ATELIER,        // アトリエステージ
        GARDEN,         // 庭ステージ
        GUILD,          // ギルドステージ
        PRIVATE_ROOM,   // 自室ステージ
    };

    /// @brief コンストラクタ
    StageManager(void);

    /// @brief デストラクタ
    ~StageManager(void);

    /// @brief 初期化処理
    /// @param player プレイヤーの参照
    /// @param dateTimeManager 日時管理クラスの参照
    void Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager);

    /// @brief 破棄処理
    void Destroy(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief ステージ変更のリクエスト
    /// @param nextId 遷移先のステージID
    void ChangeStage(STAGE_ID nextId);

    /// @brief 現在のステージIDを取得する
    /// @return 現在のステージID
    STAGE_ID GetStageID(void) const;

    /// @brief デルタタイムを取得する
    /// @return デルタタイム
    float GetDeltaTime(void) const;

    /// @brief プレイヤーを取得する
    /// @return プレイヤーの参照
    std::shared_ptr<Player> GetPlayer(void);

    /// @brief フェード処理を進める
    void Fade(void);

private:

    /// @brief デルタタイムをリセットする
    void ResetDeltaTime(void);

    /// @brief ステージ切り替えの本体処理
    /// @param stageId 切り替え先のステージID
    void DoChangeStage(STAGE_ID stageId);

    // オブジェクト管理関連
    std::unique_ptr<Fader> fader_;      // フェード管理
    StageBase* stage_;                  // 現在のステージ
    std::unique_ptr<GameHUD> gameHUD_;  // HUD表示
    std::shared_ptr<Player> player_;    // プレイヤー

    // 状態管理関連
    STAGE_ID stageId_;                  // 現在のステージID
    STAGE_ID waitStageId_;              // 次のステージID
    bool isStageChanging_;              // 遷移中フラグ

    // 時間管理関連
    std::chrono::system_clock::time_point previousTime_; // 前回の時間
    float deltaTime_;                                    // デルタタイム
};