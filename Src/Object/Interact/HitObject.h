#pragma once

#include <DxLib.h>
#include "../../Common/Vector2.h"

/// <summary>
/// インタラクトUIの表示対象オブジェクト基底クラス
/// </summary>
class HitObject
{
public:
    HitObject() = default;
    virtual ~HitObject() = default;

    /// <summary>
    /// 判定用の座標を返す（中心点）
    /// </summary>
    virtual VECTOR GetHitPosition() const = 0;

    /// <summary>
    /// 判定半径（球体）を返す
    /// </summary>
    virtual float GetHitRadius() const = 0;

    /// <summary>
    /// UIを表示する処理
    /// </summary>
    virtual void ShowUI() = 0;

    /// <summary>
    /// UIを非表示にする処理
    /// </summary>
    virtual void HideUI() = 0;
};


