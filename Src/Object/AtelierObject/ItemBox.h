#pragma once

#include <DxLib.h>
#include <memory>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class InventoryUI;
class Player;

/// @brief アトリエ内のアイテムボックスオブジェクトを管理するクラス
class ItemBox : public HitObject, public UnitBase
{
public:

    // 配置・サイズ定数関連
    static constexpr float RADIUS = 50.0f;                               // 当たり判定の球体半径
    static constexpr VECTOR SCALE = { 0.4f, 0.4f, 0.4f };                // モデルの描画スケール
    static constexpr VECTOR MODEL_POSITION = { -335.0f, 0.0f, -300.0f }; // モデルの初期配置座標

    /// @brief コンストラクタ
    ItemBox(void);

    /// @brief デストラクタ
    ~ItemBox(void) override;

    /// @brief プレイヤーオブジェクトを設定する
    /// @param player プレイヤーのshared_ptr
    void SetPlayer(std::shared_ptr<Player> player);

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief UI描画処理
    void DrawUI(void);

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 当たり判定種別を取得する
    /// @return 当たり判定種別（球体）
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の中心座標を取得する
    /// @return 中心座標
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 半径
    float GetHitRadius(void) const override;

    /// @brief UIを表示する
    void ShowUI(void) override;

    /// @brief UIを非表示にする
    void HideUI(void) override;

    /// @brief オブジェクトが有効かどうかを取得する
    /// @return 常にtrue
    bool IsValid(void) const override;

    /// @brief プレイヤーが接触したときの処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れたときの処理
    void OnPlayerExit(void) override;

    /// @brief インベントリUIが表示されているかどうかを取得する
    /// @return 表示されている場合はtrue
    bool IsVisible(void) const;

private:

    // 状態フラグ関連
    bool isShowUI_;                     // UI接近表示フラグ（"アイテムボックス"）
    bool isInventoryOpen_;              // インベントリUI表示中フラグ

    // インベントリUIのポインタ
    InventoryUI* inventoryUI_;          

    // プレイヤーオブジェクト
    std::shared_ptr<Player> player_;   
};