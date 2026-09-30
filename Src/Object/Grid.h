#pragma once

/// @brief グリッドの描画を管理するクラス
class Grid
{
public:

    // グリッドサイズ・描画関連
    static constexpr float LENGTH = 1200.0f;                           // 線の長さ
    static constexpr float HALF_LENGTH = LENGTH / 2.0f;                // 線の長さの半分
    static constexpr float INTERVAL = 50.0f;                           // 線の間隔
    static const int LINE_COUNT = static_cast<int>(LENGTH / INTERVAL); // 線の数
    static const int HALF_LINE_COUNT = LINE_COUNT / 2;                 // 線の数の半分

    /// @brief コンストラクタ
    Grid(void);

    /// @brief デストラクタ
    ~Grid(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 解放処理
    void Release(void);
};