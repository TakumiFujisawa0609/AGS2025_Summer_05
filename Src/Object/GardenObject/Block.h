#pragma once

#include <DxLib.h>

#include "../Interact/HitObject.h"
#include "../../Manager/Generic/ResourceManager.h"

/// @brief ブロックオブジェクトを管理するクラス
class Block : public HitObject
{
public:

    /// @brief コンストラクタ
    /// @param modelType 読み込むモデルのタイプ
    /// @param position 初期座標
    /// @param blockSize ブロックのサイズ
    /// @param scale スケール値
    Block(ResourceManager::SRC modelType, const VECTOR& position, float blockSize, float scale);

    /// @brief デストラクタ
    virtual ~Block(void) override;

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 当たり判定のタイプを取得する
    /// @return 当たり判定のタイプ（AABB）
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定AABBの最小座標を取得する
    /// @return 最小座標
    VECTOR GetHitMin(void) const override;

    /// @brief 当たり判定AABBの最大座標を取得する
    /// @return 最大座標
    VECTOR GetHitMax(void) const override;

    /// @brief UIを表示する
    void ShowUI(void) override;

    /// @brief UIを非表示にする
    void HideUI(void) override;

    /// @brief プレイヤーが接触したときの処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れたときの処理
    void OnPlayerExit(void) override;

private:

    // モデルのハンドル
    int modelHandle_;   

    // 位置情報関連
    VECTOR position_;   // 座標
    VECTOR halfSize_;   // 中心からの距離
};