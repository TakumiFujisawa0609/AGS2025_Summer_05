#pragma once

#include <DxLib.h>
#include "../Interact/HitObject.h"
#include "../UnitBase.h"
#include "../../Utility/Utility.h"

class LibraryUI;

/// @brief 本棚オブジェクトのクラス
class Bookshelf : public HitObject, public UnitBase
{
public:

    // 形状関連定数
    static constexpr float WIDTH = 150.0f;  // 幅
    static constexpr float HEIGHT = 150.0f; // 高さ
    static constexpr float DEPTH = 10.0f;   // 奥行き

    /// @brief コンストラクタ
    Bookshelf(void);

    /// @brief デストラクタ
    ~Bookshelf(void);

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief UIの描画処理
    void DrawUI(void);

    /// @brief 解放処理
    void Release(void) override;

    // HitObject継承関連

    /// @brief 当たり判定の最小座標を取得する
    /// @return 最小座標
    VECTOR GetHitMin(void) const override;

    /// @brief 当たり判定の最大座標を取得する
    /// @return 最大座標
    VECTOR GetHitMax(void) const override;

    /// @brief 当たり判定の種類を取得する
    /// @return 当たり判定の種類
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の中心座標を取得する
    /// @return 中心座標
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 当たり判定の半径
    float GetHitRadius(void) const override;

    /// @brief 有効かどうかを判定する
    /// @return 有効であればtrue
    bool IsValid(void) const override;

    /// @brief UIを表示する
    void ShowUI(void) override;

    /// @brief UIを非表示にする
    void HideUI(void) override;

    /// @brief プレイヤーが接触した時の処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れた時の処理
    void OnPlayerExit(void) override;

    /// @brief 視認可能か判定する
    /// @return 視認可能であればtrue
    bool IsVisible(void) const;

    /// @brief Transformを取得する
    /// @return Transformの参照
    Transform& GetTransform(void);

private:

    // 判定用座標関連
    VECTOR hitMin_; // 最小座標
    VECTOR hitMax_; // 最大座標

    // 書庫UIのポインタ
    LibraryUI* libraryUserInterface_;

    // 状態フラグ関連
    bool isValid_;               // 有効フラグ
    bool isShowUserInterface_;   // UI接近表示
    bool isLibraryOpen_;         // インベントリUI表示フラグ
};