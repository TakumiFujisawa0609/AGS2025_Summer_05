#pragma once

#include <DxLib.h>
#include "../../Common/Vector2.h"

/// <summary>
/// インタラクトUIの表示対象オブジェクト基底クラス
/// </summary>
class HitObject
{
public:

    /// <summary>
    /// 当たり判定の種類
    /// </summary>
    enum class HIT_TYPE
    {
        SPHERE,
        AABB
    };

    HitObject() = default;
    virtual ~HitObject() = default;

    /// <summary>
    /// 当たり判定の種類(球 or AABB)
    /// </summary>
    virtual HIT_TYPE GetHitType(void) const = 0;

    /// <summary>
    /// 判定用の座標を返す（中心点）
    /// </summary>
    virtual VECTOR GetHitPosition(void) const { return VGet(0, 0, 0); }

    /// <summary>
    /// 判定半径（球体）を返す
    /// </summary>
    virtual float GetHitRadius(void) const { return 0.0f; }

    /// <summary>
    /// AABBの最小点を返す
    /// </summary>
    virtual VECTOR GetHitMin(void) const { return VGet(0, 0, 0); }

    /// <summary>
    /// AABBの最大点を返す
    /// </summary>
    virtual VECTOR GetHitMax(void) const { return VGet(0, 0, 0); }

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


