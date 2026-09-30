#pragma once

/// @brief ゲーム内の日数と時間帯を管理するクラス
class DateTimeManager
{
public:

    /// @brief 時間帯を定義する列挙型
    enum class TIME_ZONE
    {
        MORNING,    // 朝
        DAY,        // 昼
        EVENING,    // 夕方
        NIGHT,      // 夜
    };

    // 24時間（秒換算）
    static constexpr float HOURS_IN_DAY = 86400.0f; 

    /// @brief コンストラクタ
    DateTimeManager(void);

    /// @brief デストラクタ
    ~DateTimeManager(void) = default;

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief リセット処理
    void Reset(void);

    /// @brief 現在の日数を取得する
    /// @return 現在の日数
    int GetDay(void) const;

    /// @brief 現在の時間帯を取得する
    /// @return 現在の時間帯
    TIME_ZONE GetTimeZone(void) const;

private:

    // 状態管理関連
    int currentDay_;       // 現在の日数
    int lastRecordedHour_; // 最後に記録された時間
};