#pragma once

#include <unordered_map>
#include <string>
#include <chrono>

/// @brief ゲーム内時間やタイマーを管理するシングルトンクラス
class TimeManager
{
public:

    /// @brief 明示的にインスタンスを生成する
    static void CreateInstance(void);

    /// @brief 静的インスタンスの取得
    /// @return TimeManagerのインスタンス参照
    static TimeManager& GetInstance(void);

    /// @brief インスタンスの破棄
    static void Destroy(void);

    /// @brief リセット処理
    void Reset(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief ゲーム内時間を取得する
    /// @return ゲーム内時間（秒）
    float GetGameTime(void) const;

    /// @brief ゲーム内の現在の「時」を取得する
    /// @return 時間（時）
    int GetGameHour(void) const;

    /// @brief ゲーム内の現在の「分」を取得する
    /// @return 時間（分）
    int GetGameMinute(void) const;

    /// @brief ゲーム内の現在の「秒」を取得する
    /// @return 時間（秒）
    int GetGameSecond(void) const;

    /// @brief ゲーム内時間を設定する
    /// @param time 設定する時間
    void SetGameTime(float time);

    /// @brief タイマーを開始する
    /// @param id タイマーのID
    /// @param duration タイマーの持続時間
    void StartTimer(const std::string& id, float duration);

    /// @brief タイマーが終了したか判定する
    /// @param id 判定するタイマーのID
    /// @return 終了していればtrue
    bool IsTimerFinished(const std::string& id) const;

    /// @brief タイマーをリセットする
    /// @param id リセットするタイマーのID
    void ResetTimer(const std::string& id);

private:

    /// @brief タイマー管理用構造体
    struct Timer
    {
        float timeLeft; // タイマーの残り時間
        float duration; // タイマーの持続時間
    };

    // 静的インスタンス
    static TimeManager* instance_;                  

    // 時間管理関連
    float gameTime_;                                // ゲーム内時間
    float gameSpeed_;                               // ゲーム内時間の経過速度
    std::chrono::steady_clock::time_point prevTime_;// 前フレームの時間

    // タイマー情報のマップ
    std::unordered_map<std::string, Timer> timers_; 

    /// @brief コンストラクタ
    TimeManager(void) = default;

    /// @brief デストラクタ
    ~TimeManager(void) = default;

    /// @brief インスタンスのコピー禁止
    TimeManager(const TimeManager&) = delete;

    /// @brief 代入演算子の禁止
    TimeManager& operator=(const TimeManager&) = delete;
};