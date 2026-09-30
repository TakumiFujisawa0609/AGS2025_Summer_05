#pragma once

#include <DxLib.h>

#include "../UnitBase.h"
#include "../Interact/HitObject.h"

/// @brief 植物オブジェクトを管理するクラス
class PlantObject : public UnitBase, public HitObject
{
public:

    /// @brief 植物の成長段階を定義する列挙型
    enum class GROW_STAGE
    {
        Sprout,         // 芽
        MidGrowth,      // 成長中
        Mature          // 成熟（収穫可能）
    };

    // 成長時間定数関連
    static constexpr float GROWTH_DURATION_SPROUT = 300.0f; // 芽から成長中への移行時間（フレーム等）
    static constexpr float GROWTH_DURATION_MID = 800.0f;    // 成長中から成熟への移行時間

    /// @brief コンストラクタ
    PlantObject(void);

    /// @brief デストラクタ
    virtual ~PlantObject(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 当たり判定種別を取得する
    /// @return 当たり判定種別（球体）
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の中心座標を取得する
    /// @return 当たり判定の中心座標
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 当たり判定の球体半径
    float GetHitRadius(void) const override;

    /// @brief UIを表示状態にする
    void ShowUI(void) override;

    /// @brief UIを非表示状態にする
    void HideUI(void) override;

    /// @brief オブジェクトが有効かどうかを取得する
    /// @return 有効な場合はtrue
    bool IsValid(void) const override;

    /// @brief プレイヤーと接触した時の処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れた時の処理
    void OnPlayerExit(void) override;

    /// @brief 収穫可能かどうかを判定する
    /// @return 収穫可能であればtrue
    bool CanHarvest(void) const;

    /// @brief 現在の成長段階を取得する
    /// @return 成長段階
    GROW_STAGE GetGrowthStage(void) const;

    /// @brief 植物を植えることを試みる
    void TryPlant(void);

    /// @brief 収穫を試みる
    void TryHarvest(void);

    /// @brief アクティブ状態を設定する
    /// @param active アクティブにする場合はtrue
    void SetActive(bool active);

    /// @brief トランスフォーム情報を取得する
    /// @return トランスフォームの参照
    Transform& GetTransform(void);

private:

    /// @brief 経過時間に応じて成長段階を更新する
    /// @param elapsedTime 経過時間
    void UpdateGrowthStage(float elapsedTime);

    /// @brief 成長段階に合わせてモデルを変更する
    /// @param stage 成長段階
    void ChangeModelForStage(GROW_STAGE stage);

    // 状態管理関連
    GROW_STAGE growthStage_;    // 現在の成長段階
    bool isActive_;             // 成長フラグ
    bool isUIVisible_;          // UI表示フラグ
    bool hasPlant_;             // 植えられているかどうかのフラグ
    float growthStartTime_;     // 成長開始時刻

    // モデル情報関連
    int sproutModelId_;         // 芽のモデルID
    int midGrowthModelId_;      // 成長中のモデルID
    int matureModelId_;         // 成熟時のモデルID
};