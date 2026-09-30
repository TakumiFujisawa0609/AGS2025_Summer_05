#pragma once

#include <DxLib.h>
#include <memory>
#include <string>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class StageManager;
class TeleportUI;

/// @brief テレポートによる移動を管理するクラス
class TeleportMovement : public HitObject, public UnitBase
{
public:

    // 配置・寸法定数関連
    static constexpr float RADIUS = 50.0f;                                  // 当たり判定の球体半径
    static constexpr VECTOR SCALE = { 0.05f, 0.05f, 0.05f };                // モデルの拡大縮小率
    static constexpr VECTOR MODEL_POSITION = { 0.0f, 20.0f, -420.0f };      // 初期配置座標

    /// @brief コンストラクタ
    /// @param stageManager ステージマネージャーへのポインタ
    TeleportMovement(StageManager* stageManager);

    /// @brief デストラクタ
    virtual ~TeleportMovement(void) override;

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

private:

    // UI接近表示フラグ
    bool isShowUI_;                         

    // 参照・UI管理関連
    StageManager* stageManager_;            // ステージマネージャーの参照
    std::unique_ptr<TeleportUI> teleportUI_; // テレポートUIのインスタンス
};