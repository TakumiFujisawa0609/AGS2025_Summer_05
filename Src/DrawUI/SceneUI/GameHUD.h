#pragma once

#include <string>
#include <array>
#include <memory>

class Player;
class DateTimeManager;

/// @brief ゲームのHUDを管理するクラス
class GameHUD
{
public:

    /// @brief 時間帯アイコンのインデックス
    enum class TIME_ICON_INDEX
    {
        MORNING = 0, // 朝
        DAY,         // 昼
        EVENING,     // 夕
        NIGHT        // 夜
    };

    // 定数関連
    static constexpr int MESSAGE_DISPLAY_TIME = 60;        // メッセージ表示時間
    static constexpr int MAX_QUEST_COUNT = 5;              // 最大クエスト達成数
    static constexpr int FONT_SIZE_MONEY = 32;             // 所持金テキストのフォントサイズ
    static constexpr int FONT_SIZE_QUEST = 28;             // クエストテキストのフォントサイズ
    static constexpr int FONT_SIZE_MESSAGE = 58;           // メッセージのフォントサイズ
    static constexpr unsigned int COLOR_WHITE = 0xffffff;  // 白色
    static constexpr float MONEY_ICON_SCALE = 0.27f;       // 所持金アイコンのスケール
    static constexpr float TIME_ICON_SCALE = 1.5f;         // 時間帯アイコンのスケール
    static constexpr float UI_FRAME_SCALE = 1.5f;          // UIフレームのスケール

    /// @brief コンストラクタ
    /// @param void 
    /// @return なし
    GameHUD(void);

    /// @brief デストラクタ
    /// @param void 
    /// @return なし
    ~GameHUD(void);

    /// @brief 初期化処理
    /// @param player プレイヤーへの参照
    /// @param dateTimeManager 日付・時間管理への参照
    /// @return なし
    void Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager);

    /// @brief 更新処理
    /// @param void 
    /// @return なし
    void Update(void);

    /// @brief 描画処理
    /// @param void 
    /// @return なし
    void Draw(void);

private:

    // 参照関連
    std::shared_ptr<Player> player_;           // プレイヤーへの参照
    DateTimeManager* dateTimeManager_;         // 日付・時間管理への参照

    // ハンドル関連
    int uiFrameHandle_;                        // UIフレームのハンドル
    int moneyIconHandle_;                      // 所持金アイコン
    std::array<int, 4> timeIcons_;             // 時間帯アイコン（朝・昼・夕・夜）

    // タイマー関連
    int maxCompleteMessageTimer_;              // 目標達成メッセージの表示タイマー
};