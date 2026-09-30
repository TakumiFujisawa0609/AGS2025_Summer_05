#pragma once

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

/// @brief 井戸オブジェクトを管理するクラス
class WellObject : public HitObject, public UnitBase
{
public:

    // 当たり判定・クールダウン定数関連
    static constexpr float RADIUS = 40.0f;           // 当たり判定の球体半径
    static constexpr float COOLDOWN_TIME = 400.0f;   // 水汲みのクールダウン時間

    // 配置・モデル定数関連
    static constexpr VECTOR MODEL_POSITION = { 0.0f, -10.0f, 0.0f }; // モデルの初期座標
    static constexpr VECTOR MODEL_SCALE = { 0.1f, 0.15f, 0.1f };     // モデルの描画スケール
    static constexpr VECTOR MODEL_ROTATION = { 0.0f, 0.0f, 0.0f };   // モデルの初期回転角

    /// @brief コンストラクタ
    WellObject(void);

    /// @brief デストラクタ
    virtual ~WellObject(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 当たり判定のタイプを取得する
    /// @return 当たり判定のタイプ（球体）
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

    /// @brief UIを表示状態にする
    void ShowUI(void) override;

    /// @brief UIを非表示状態にする
    void HideUI(void) override;

    /// @brief プレイヤーと接触した時の処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れた時の処理
    void OnPlayerExit(void) override;

    /// @brief トランスフォーム情報を取得する
    /// @return トランスフォームの参照
    Transform& GetTransform(void);

private:

    /// @brief 水を汲む処理を試みる
    void TryDrawWater(void);

    /// @brief クールダウンが終了しているか判定する
    /// @return 終了している場合はtrue
    bool IsCooldownOver(void) const;

    /// @brief クールダウンを開始する
    void StartCooldown(void);

    // 状態フラグ関連
    bool isUIVisible_;      // UIが表示中かどうか
    bool wantsToShowUI_;    // UIを表示したい要求があるかどうか
    bool isOnCooldown_;     // クールダウン中かどうかのフラグ

    // 最後に水を汲んだ時間
    float minedTime_;       
};