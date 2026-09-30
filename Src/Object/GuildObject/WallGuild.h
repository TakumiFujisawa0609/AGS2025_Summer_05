#pragma once

#include <DxLib.h>
#include "../Interact/HitObject.h"
#include "../UnitBase.h"
#include "../../Utility/Utility.h"

/// @brief ギルド内の壁オブジェクト（左側など）を管理するクラス
class WallGuild : public HitObject, public UnitBase
{
public:

    // バウンディングボックス定数関連
    static constexpr float WIDTH = 150.0f;          // AABBの横幅
    static constexpr float HEIGHT = 500.0f;         // AABBの高さ
    static constexpr float DEPTH = 700.0f;          // AABBの奥行き

    /// @brief コンストラクタ
    WallGuild(void);

    /// @brief デストラクタ
    virtual ~WallGuild(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 当たり判定AABBの最小座標を取得する
    /// @return 最小座標
    VECTOR GetHitMin(void) const override;

    /// @brief 当たり判定AABBの最大座標を取得する
    /// @return 最大座標
    VECTOR GetHitMax(void) const override;

    /// @brief 当たり判定種別を取得する
    /// @return 当たり判定種別（AABB）
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の中心座標を取得する
    /// @return 中心座標
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 半径
    float GetHitRadius(void) const override;

    /// @brief オブジェクトが有効かどうかを取得する
    /// @return 有効な場合はtrue
    bool IsValid(void) const override;

    /// @brief UIを表示する
    void ShowUI(void) override;

    /// @brief UIを非表示にする
    void HideUI(void) override;

    /// @brief プレイヤーが接触したときの処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れたときの処理
    void OnPlayerExit(void) override;

    /// @brief トランスフォーム情報を取得する
    /// @return トランスフォームの参照
    Transform& GetTransform(void);

private:

    // 当たり判定AABB範囲関連
    VECTOR hitMin_;     // AABBの最小座標
    VECTOR hitMax_;     // AABBの最大座標

    // オブジェクトの有効フラグ
    bool isValid_;      
};