#pragma once

/// @brief すべてのシーンの基底となる抽象クラス
class SceneBase
{
public:

    /// @brief コンストラクタ
    SceneBase(void) = default;

    /// @brief デストラクタ
    virtual ~SceneBase(void) = 0;

    /// @brief 初期化処理
    virtual void Init(void) = 0;

    /// @brief 更新処理
    virtual void Update(void) = 0;

    /// @brief 描画処理
    virtual void Draw(void) = 0;

    /// @brief 解放処理
    virtual void Release(void) = 0;
};