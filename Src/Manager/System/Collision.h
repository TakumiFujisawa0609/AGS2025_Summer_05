#pragma once

#include <DxLib.h>
#include "../../Common/Vector2.h"

/// @brief 衝突判定を行うクラス
class Collision
{
public:

    /// @brief インスタンスの生成
    static void CreateInstance(void);

    /// @brief インスタンスの取得
    /// @return Collisionのインスタンス参照
    static Collision& GetInstance(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 正方形同士の当たり判定
    /// @param box1 四角形1の位置
    /// @param box1Range 四角形1の長さ
    /// @param box2 四角形2の位置
    /// @param box2Range 四角形2の長さ
    /// @return 当たっているか
    bool IsHitBoxes(
        const Vector2F box1,
        const float box1Range,
        const Vector2F box2,
        const float box2Range
    ) const;

    /// @brief 球体同士の衝突判定
    /// @param position1 球体1の位置
    /// @param radius1 球体1の半径
    /// @param position2 球体2の位置
    /// @param radius2 球体2の半径
    /// @return 当たっているか
    static bool IsHitSpheres(
        const VECTOR& position1,
        float radius1,
        const VECTOR& position2,
        float radius2
    );

    /// @brief 球体とカプセルの衝突判定
    /// @param spherePosition 球体の位置
    /// @param sphereRadius 球体の半径
    /// @param capsulePosition1 カプセルの始点
    /// @param capsulePosition2 カプセルの終点
    /// @param capsuleRadius カプセルの半径
    /// @return 当たっているか
    static bool IsHitSphereCapsule(
        const VECTOR& spherePosition,
        float sphereRadius,
        const VECTOR& capsulePosition1,
        const VECTOR& capsulePosition2,
        float capsuleRadius
    );

private:

    /// @brief インスタンス用
    static Collision* instance_;

    /// @brief コンストラクタ
    Collision(void) = default;

    /// @brief デストラクタ
    ~Collision(void) = default;
};