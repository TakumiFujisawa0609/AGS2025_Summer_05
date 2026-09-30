#pragma once

#include <string>
#include <vector>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"
#include "../../Utility/Utility.h"

/// @brief 鉱石オブジェクトを管理するクラス
class OreObject : public HitObject, public UnitBase
{
public:

    /// @brief 鉱石のクールダウン状態を定義する列挙型
    enum class COOL_DOWNSTATE
    {
        READY,          // 採掘可能
        COOLINGDOWN     // クールタイム中
    };

    // 鉱石の再採掘可能までのクールタイム
    static constexpr float ORE_COOLDOWN_TIME = 600.0f;  

    /// @brief コンストラクタ
    OreObject(void);

    /// @brief デストラクタ
    virtual ~OreObject(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 採掘を試みる
    void TryMine(void);

    /// @brief 当たり判定種別を取得する
    /// @return 当たり判定種別（球体）
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

    /// @brief クールダウンを開始する
    void StartCooldown(void);

    /// @brief クールダウンが終了しているか判定する
    /// @return 終了している場合はtrue
    bool IsCooldownOver(void) const;

    // 位置・スケール・回転
    Transform transform_;           

    // 状態管理関連
    COOL_DOWNSTATE cooldownState_;  // 現在のクールダウン状態
    bool isOnCooldown_;             // クールダウン中かどうかのフラグ
    float minedTime_;               // 最後に採掘された時間

    // 当たり判定・UI表示フラグ関連
    float radius_;                  // 当たり判定の半径
    bool isUIVisible_;              // UIが表示中かどうか
    bool wantsToShowUI_;            // UIを表示したい要求があるかどうか

    // モデルのハンドルID
    int modelId_;                   
};