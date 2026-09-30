#pragma once

#include <unordered_map>
#include <memory>

#include "Common/Transform.h"
#include "Common/AnimationController.h"

/// @brief ユニット（キャラクター等の動的オブジェクト）の基底クラス
class UnitBase
{
public:

    /// @brief アニメーション状態を定義する列挙型
    enum class ANIMATION
    {
        NONE,       // 指定なし
        IDLE,       // 待機
        WALK,       // 歩き
    };

    /// @brief コンストラクタ
    UnitBase(void);

    /// @brief デストラクタ
    virtual ~UnitBase(void) = 0;

    /// @brief 初期化処理
    virtual void Init(void) = 0;

    /// @brief 更新処理
    virtual void Update(void) = 0;

    /// @brief 描画処理
    virtual void Draw(void) = 0;

    /// @brief 解放処理
    virtual void Release(void) = 0;

    /// @brief モデル情報を取得する
    /// @return Transformの参照
    const Transform& GetTransform(void) { return transform_; }

    /// @brief 位置を取得する
    /// @return 現在の位置ベクトル
    const VECTOR& GetPosition(void) const { return transform_.position; }

    /// @brief 角度を取得する
    /// @return 現在の角度ベクトル
    const VECTOR& GetRotation(void) const { return transform_.rotation; }

    /// @brief 大きさを取得する
    /// @return 現在の大きさベクトル
    const VECTOR& GetScale(void) const { return transform_.scale; }

    /// @brief 1フレーム前の位置を取得する
    /// @return 1フレーム前の位置ベクトル
    const VECTOR& GetPreviousPosition(void) const { return previousPosition_; }

    /// @brief 当たり判定用の半径を取得する
    /// @return 半径
    const float GetRadius(void) const { return radius_; }

    /// @brief 位置を設定する
    /// @param position 設定する位置ベクトル
    void SetPosition(const VECTOR& position) { transform_.position = position; }

    /// @brief 回転処理
    /// @param degree 回転する角度(デグリー角)
    /// @param axis 回転方向の軸ベクトル
    void Turn(const float degree, const VECTOR& axis);

protected:

    // 状態管理関連
    Transform transform_;           // モデルの情報
    VECTOR previousPosition_;       // 1フレーム前の座標
    float radius_;                  // 当たり判定の半径
    float speed_;                   // 移動速度
    VECTOR movementVector_;         // 移動量ベクトル

    // アニメーション制御
    std::unique_ptr<AnimationController> animationController_;

    /// @brief アニメーションのリセット処理
    virtual void InitAnimation(void);
};