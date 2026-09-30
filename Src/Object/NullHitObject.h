#pragma once

#include <DxLib.h>
#include "Interact/HitObject.h"

/// @brief 当たり判定を持たないオブジェクトを表すクラス
class NullHitObject : public HitObject
{
public:

    /// @brief 当たり判定の種類を取得する
    /// @return 当たり判定の種類
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の基準座標を取得する
    /// @return 基準座標ベクトル
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 半径
    float GetHitRadius(void) const override;

    /// @brief 当たり判定の最小座標を取得する
    /// @return 最小座標ベクトル
    VECTOR GetHitMin(void) const override;

    /// @brief 当たり判定の最大座標を取得する
    /// @return 最大座標ベクトル
    VECTOR GetHitMax(void) const override;

    /// @brief UIを表示する
    void ShowUI(void) override;

    /// @brief UIを非表示にする
    void HideUI(void) override;

    /// @brief 有効なオブジェクトか判定する
    /// @return 常にfalse（無効なオブジェクトのため）
    bool IsValid(void) const override;

    /// @brief プレイヤーと接触した際の処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーとの接触が終了した際の処理
    void OnPlayerExit(void) override;
};