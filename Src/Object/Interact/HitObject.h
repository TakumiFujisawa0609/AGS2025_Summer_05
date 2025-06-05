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
    virtual VECTOR GetHitPosition(void) const = 0;

    /// <summary>
    /// 判定半径（球体）を返す
    /// </summary>
    virtual float GetHitRadius(void) const = 0;

    /// <summary>
    /// UIを表示する処理
    /// </summary>
    virtual void ShowUI(void) = 0;

    /// <summary>
    /// UIを非表示にする処理
    /// </summary>
    virtual void HideUI(void) = 0;

    virtual bool IsValid(void) const { return true; }

protected:
    int stageID_ = -1;
};


