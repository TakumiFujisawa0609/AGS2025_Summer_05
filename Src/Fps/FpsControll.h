#pragma once

/// @brief FPSの計測および制御を行うクラス
class Fps
{
public:

    // FPS制御関連
    static constexpr int SAMPLE_COUNT = 240; // 平均をとるサンプル数
    static constexpr int TARGET_FPS = 240;   // 設定した目標FPS

    /// @brief デフォルトコンストラクタ
    Fps(void);

    /// @brief デストラクタ
    ~Fps(void);

    /// @brief 初期処理(最初の1回のみ実行)
    void FpsControll_Initialize(void);

    /// @brief 更新処理(毎フレーム実行)
    /// @return 正常に更新された場合はtrue
    bool FpsControll_Update(void);

    /// @brief 描画処理(毎フレーム実行)
    void FpsControll_Draw(void);

    /// @brief 解放・待機処理(毎フレーム実行)
    void FpsControll_Wait(void);

private:

    // 状態管理関連
    int startTime_;   // 測定開始時刻
    int frameCount_;  // フレームカウンタ
    float currentFps_;// 現在のFPS
};