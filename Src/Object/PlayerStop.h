#pragma once

class Player;

/// @brief プレイヤーの移動停止を管理するシングルトンクラス
class PlayerStop
{
public:

    /// @brief インスタンスを生成する
    static void CreateInstance(void);

    /// @brief インスタンスを取得する
    /// @return PlayerStopのインスタンス参照
    static PlayerStop& GetInstance(void);

    /// @brief インスタンスを破棄する
    static void Destroy(void);

    /// @brief 操作対象のプレイヤーを設定する
    /// @param player プレイヤーのポインタ
    void SetPlayer(Player* player);

    /// @brief プレイヤーの移動を停止する
    void StopMovement(void);

    /// @brief プレイヤーの移動を再開する
    void ResumeMovement(void);

    /// @brief プレイヤーが停止状態か判定する
    /// @return 停止状態であればtrue
    bool IsStopped(void) const;

private:

    /// @brief コンストラクタ
    PlayerStop(void);

    /// @brief デストラクタ
    ~PlayerStop(void);

    /// @brief コピーコンストラクタ（使用禁止）
    PlayerStop(const PlayerStop&) = delete;

    /// @brief 代入演算子（使用禁止）
    PlayerStop& operator=(const PlayerStop&) = delete;

    /// @brief 静的インスタンス
    static PlayerStop* instance_;

    // 状態管理関連
    bool isStopped_; // 停止状態フラグ
    Player* player_; // 対象のプレイヤー
};