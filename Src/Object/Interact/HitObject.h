#pragma once

#include <DxLib.h>
#include <memory>

#include "../../Common/Vector2.h"

class Player;

/// @brief インタラクトUIの表示対象オブジェクト基底クラス
class HitObject
{
public:

    /// @brief 当たり判定の種類を定義する列挙型
    enum class HIT_TYPE
    {
        SPHERE, // 球体
        AABB    // 軸並行境界箱
    };

    // UIを非表示にするまでの最大猶予フレーム数
    static constexpr int MAXIMUM_UI_HIDE_DELAY_FRAMES = 30; 

    /// @brief コンストラクタ
    HitObject(void);

    /// @brief デストラクタ
    virtual ~HitObject(void) = default;

    /// @brief 当たり判定の種類(球 or AABB)を取得する
    /// @return 当たり判定の種類
    virtual HIT_TYPE GetHitType(void) const = 0;

    /// @brief 判定用の座標を取得する（中心点）
    /// @return 中心点の座標ベクトル
    virtual VECTOR GetHitPosition(void) const;

    /// @brief 判定半径（球体）を取得する
    /// @return 半径
    virtual float GetHitRadius(void) const;

    /// @brief AABBの最小点を取得する
    /// @return 最小点の座標ベクトル
    virtual VECTOR GetHitMin(void) const;

    /// @brief AABBの最大点を取得する
    /// @return 最大点の座標ベクトル
    virtual VECTOR GetHitMax(void) const;

    /// @brief UIを表示する処理
    virtual void ShowUI(void) = 0;

    /// @brief UIを非表示にする処理
    virtual void HideUI(void) = 0;

    /// @brief プレイヤーとAABBの当たり判定処理
    /// @param player プレイヤーのポインタ
    /// @param playerPosition プレイヤーの座標
    /// @param playerMinimum プレイヤーのAABB最小点
    /// @param playerMaximum プレイヤーのAABB最大点
    virtual void OnPlayerHitAABB(
        Player* player,
        VECTOR& playerPosition,
        const VECTOR& playerMinimum,
        const VECTOR& playerMaximum
    );

    /// @brief プレイヤーと球体の当たり判定処理
    /// @param playerPosition プレイヤーの座標
    /// @param playerRadius プレイヤーの判定半径
    virtual void OnPlayerHitSphere(VECTOR& playerPosition, float playerRadius);

    /// @brief プレイヤーと接触した際の処理
    virtual void OnPlayerHit(void) = 0;

    /// @brief プレイヤーとの接触が終了した際の処理
    virtual void OnPlayerExit(void) = 0;

    /// @brief 有効なオブジェクトか判定する
    /// @return 有効であればtrue
    virtual bool IsValid(void) const;

    /// @brief UIの表示状態を更新する
    /// @param isHit 接触しているかどうか
    virtual void UpdateUIVisibility(bool isHit);

protected:

    // 状態管理関連
    int stageId_;              // ステージID
    bool uiVisible_;           // UI表示フラグ
    int uiHideDelayFrames_;    // UI消去までの猶予フレーム数
};