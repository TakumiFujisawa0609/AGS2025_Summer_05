#pragma once

#include <memory>
#include "SceneBase.h"

class SceneUi;

/// @brief ゲームクリアシーンを管理するクラス
class SceneGameClear : public SceneBase
{
public:

    /// @brief コンストラクタ
    SceneGameClear(void);

    /// @brief デストラクタ
    virtual ~SceneGameClear(void) override = default;

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