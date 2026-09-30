#pragma once
#include <DxLib.h>
#include "UnitBase.h"

class AnimationController;

/// @brief プレイヤーキャラクターの管理・制御を行うクラス
class Player : public UnitBase
{
public:

    /// @brief アニメーション種別を定義する列挙型
    enum class ANIMATION_TYPE
    {
        NONE,  // タイポ修正(NOME -> NONE)
        WALK,
        IDLE,
        MAX
    };

    // 基本設定関連
    static constexpr VECTOR SCALES = { 1.0f, 1.0f, 1.0f };                   // モデルの大きさ
    static constexpr VECTOR DEFAULT_POSITION = { 0.0f, 20.0f, -200.0f };     // 初期位置
    static constexpr COLOR_F COLOR_EMI_DEFAULT = { 0.5f, 0.5f, 0.5f, 0.5f }; // 標準の自己発光色
    static constexpr float SPEED_MOVE = 5.0f;                                // 移動スピード
    static constexpr float RADIUS = 30.0f;                                   // 当たり判定の半径

    /// @brief コンストラクタ
    Player(void);

    /// @brief デストラクタ
    ~Player(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 座標を取得する
    /// @return プレイヤーの現在座標
    VECTOR GetPosition(void) const;

    /// @brief 座標を設定する
    /// @param position 設定する座標
    void SetPosition(VECTOR position);

    /// @brief プレイヤーのAABB最小点を取得する
    /// @return 最小点の座標
    VECTOR GetHitMin(void) const;

    /// @brief プレイヤーのAABB最大点を取得する
    /// @return 最大点の座標
    VECTOR GetHitMax(void) const;

    /// @brief 当たり判定の半径を取得する
    /// @return 半径
    float GetRadius(void) const;

    /// @brief プレイヤーの所持金を取得する
    /// @return 現在の所持金
    int GetMoney(void) const;

    /// @brief プレイヤーの所持金を追加・設定する
    /// @param money 加算する金額
    void AddMoney(int money);

    /// @brief X軸方向の移動ブロックを設定する
    /// @param direction ブロックする方向
    void SetBlockedDirectionX(int direction);

    /// @brief Z軸方向の移動ブロックを設定する
    /// @param direction ブロックする方向
    void SetBlockedDirectionZ(int direction);

    /// @brief 移動ブロックの状態をリセットする
    void ResetBlockDirections(void);

    /// @brief 移動の有効・無効を設定する
    /// @param enabled 有効にする場合はtrue
    void SetMovementEnabled(bool enabled);

    /// @brief 移動が有効か判定する
    /// @return 有効であればtrue
    bool IsMovementEnabled(void) const;

    /// @brief アニメーションを再生する
    /// @param type 再生するアニメーション種別
    /// @param loop ループ再生するかどうか
    void PlayAnimation(ANIMATION_TYPE type, bool loop = true);

private:

    // モデルID
    int modelHandleId_;

    // スケール
    VECTOR scales_;

    // カメラ関連
    VECTOR axis_;
    VECTOR angles_;

    // 状態管理関連
    bool isOnGround_;       // 地面にいるかどうか
    int money_;             // 所持金
    int blockedDirectionX_; // X軸方向のブロック
    int blockedDirectionZ_; // Z軸方向のブロック
    bool movementEnabled_;  // 移動可能フラグ
    int currentAnimationType_;// 現在再生中のアニメーション種別

    // アニメーションコントローラー
    AnimationController* animationController_;

    /// @brief 行動制御
    void ProcessMove(void);
};