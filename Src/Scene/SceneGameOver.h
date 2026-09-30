#pragma once

#include <memory>
#include "SceneBase.h"

class SceneUi;

/// @brief ゲームオーバーシーンを管理するクラス
class SceneGameOver : public SceneBase
{
public:

    /// @brief コンストラクタ
    SceneGameOver(void);

    /// @brief デストラクタ
    virtual ~SceneGameOver(void) override = default;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

private:

    // UIオブジェクト
    std::unique_ptr<SceneUi> ui_;          

    /// @brief 描画処理(デバッグ)
    void DrawDebug(void);
};