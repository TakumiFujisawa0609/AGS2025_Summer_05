#pragma once

#include <DxLib.h>
#include <memory>
#include <string>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class Player;

/// @brief 錬金釜オブジェクトのクラス
class AlchemyPot : public HitObject, public UnitBase
{
public:

    // 形状関連定数
    static constexpr float RADIUS = 50.0f;                     // 半径
    static constexpr VECTOR MODEL_SCALE = { 3.0f, 3.0f, 3.0f };// モデルの大きさ

    /// @brief モデル座標
    static constexpr VECTOR MODEL_POSITION = { 0.0f, 10.0f, -50.0f };

    /// @brief コンストラクタ
    AlchemyPot(void);

    /// @brief デストラクタ
    ~AlchemyPot(void);

    /// @brief プレイヤーの参照を設定する
    /// @param player 設定するプレイヤー
    void SetPlayer(std::shared_ptr<Player> player);

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    // HitObject継承関連

    /// @brief 当たり判定の種類を取得する
    /// @return 当たり判定の種類
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の中心座標を取得する
    /// @return 当たり判定の中心座標
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 当たり判定の半径
    float GetHitRadius(void) const override;

    /// @brief UIを表示する
    void ShowUI(void) override;

    /// @brief UIを非表示にする
    void HideUI(void) override;

    /// @brief オブジェクトが有効か判定する
    /// @return 有効であればtrue
    bool IsValid(void) const override;

    /// @brief プレイヤーが接触した時の処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れた時の処理
    void OnPlayerExit(void) override;

    /// @brief 錬金UIが開いているか判定する
    /// @return 開いていればtrue
    bool IsOpen(void) const;

private:

    // UI表示フラグ
    bool isShowUserInterface_;

    /// @brief プレイヤーの参照
    std::shared_ptr<Player> player_;
};