#pragma once

#include <string>
#include <vector>
#include <memory>

class DateTimeManager;

/// @brief 納品依頼情報を格納する構造体
struct DeliveryQuest
{
    int id;                      // 依頼ID
    std::string title;           // 依頼タイトル
    std::string description;     // 依頼説明
    std::string targetItemId;    // 対象アイテムID
    int requiredAmount;          // 必要数量
    int currentAmount;           // 現在の進行数
    int rewardMoney;             // 報酬金
    bool isCompleted;            // 完了フラグ
    bool isActive;               // アクティブフラグ

    /// @brief デフォルトコンストラクタ
    DeliveryQuest(void);

    /// @brief パラメータ指定コンストラクタ
    /// @param questId 依頼ID
    /// @param questTitle 依頼タイトル
    /// @param questDescription 依頼説明
    /// @param itemId 対象アイテムID
    /// @param required 必要数量
    /// @param money 報酬金
    DeliveryQuest(
        int questId,
        const std::string& questTitle,
        const std::string& questDescription,
        const std::string& itemId,
        int required,
        int money
    );
};

/// @brief 納品依頼UIおよび依頼の進行を管理するシングルトンクラス
class QuestUI
{
public:

    // システム定数
    static constexpr int MAX_QUESTS = 5;                        // 最大依頼数

    // 描画・UI関連定数
    static constexpr int ACTIVE_QUEST_DRAW_START_X = 100;       // アクティブ依頼描画のX基準位置
    static constexpr int ACTIVE_QUEST_DRAW_START_Y = 120;       // アクティブ依頼描画のY基準位置
    static constexpr int ACTIVE_QUEST_BACKGROUND_WIDTH = 380;   // アクティブ依頼背景の幅
    static constexpr int ACTIVE_QUEST_LINE_HEIGHT = 30;         // 行の高さ
    static constexpr int REFRESH_LOG_START_Y = 400;             // 日替わり更新ログのY基準位置
    static constexpr int REFRESH_LOG_LINE_HEIGHT = 20;          // 日替わり更新ログの行の高さ
    static constexpr unsigned int COLOR_WHITE = 0xffffff;       // 白色
    static constexpr unsigned int COLOR_YELLOW = 0xffff00;      // 黄色
    static constexpr unsigned int COLOR_GREEN = 0x00ff00;       // 緑色（完了色）
    static constexpr unsigned int COLOR_BLACK = 0x000000;       // 黒色

    /// @brief シングルトンインスタンス生成
    static void CreateInstance(void);

    /// @brief シングルトンインスタンスの取得
    /// @return QuestUIのインスタンス参照
    static QuestUI& GetInstance(void);

    /// @brief リソースの解放
    static void Destroy(void);

    ~QuestUI(void) = default;

    /// @brief 日数マネージャーの設定
    /// @param dateTimeManager 日数マネージャーへのポインタ
    void SetDateTimeManager(DateTimeManager* dateTimeManager);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 依頼受注
    /// @param questId 受注する依頼ID
    void AcceptQuest(int questId);

    /// @brief 依頼完了
    /// @param questId 完了する依頼ID
    void CompleteQuest(int questId);

    /// @brief 進行状況更新
    /// @param questId 更新する依頼ID
    void UpdateProgress(int questId);

    /// @brief 新しい依頼を受けられるかチェック
    /// @return 受けられる場合はtrue
    bool CanAcceptNewQuest(void) const;

    /// @brief 依頼がアクティブかチェック
    /// @param questId チェックする依頼ID
    /// @return アクティブな場合はtrue
    bool IsQuestActive(int questId) const;

    /// @brief 依頼が完了済みかチェック
    /// @param questId チェックする依頼ID
    /// @return 完了済みの場合はtrue
    bool IsQuestCompleted(int questId) const;

    /// @brief UIの表示状態を設定する
    /// @param isVisible 表示する場合はtrue
    void SetVisible(bool isVisible);

    /// @brief UIが表示中か取得する
    /// @return 表示中の場合はtrue
    bool IsVisible(void) const;

    /// @brief アクティブ依頼を取得（1件のみ受けている前提）
    /// @return アクティブな依頼へのポインタ（ない場合はnullptr）
    DeliveryQuest* GetActiveQuest(void);

    /// @brief アクティブな納品依頼リストを取得
    /// @return アクティブ依頼のリスト参照
    std::vector<DeliveryQuest>& GetActiveQuests(void);

    /// @brief 日替わり依頼リストの更新
    void RefreshDailyQuests(void);

    /// @brief 選択された依頼候補リストを取得
    /// @return 依頼候補リストの定数参照
    const std::vector<DeliveryQuest>& GetSelectedQuests(void) const;

    /// @brief 完了したクエスト数を取得
    /// @return 完了数
    int GetCompletedQuestCount(void) const;

    /// @brief 最大クエスト完了数に達したかチェック
    /// @return 達している場合はtrue
    bool HasReachedMaxCompletion(void) const;

    /// @brief 完了したクエスト数を設定
    /// @param completedCount 設定する完了数
    void SetCompletedQuestCount(int completedCount);

private:
    QuestUI(void) = default;
    QuestUI(const QuestUI&) = delete;
    QuestUI& operator=(const QuestUI&) = delete;

    static QuestUI* instance_;

    // データ関連
    std::vector<DeliveryQuest> availableQuests_; // 利用可能な納品依頼リスト
    std::vector<DeliveryQuest> activeQuests_;    // アクティブな納品依頼リスト
    std::vector<DeliveryQuest> selectedQuests_;  // 依頼候補

    // 日数管理関連
    DateTimeManager* dateTimeManager_;

    // 状態管理関連
    bool isVisible_;                             // UI表示フラグ
    int lastDay_;                                // 前回ゲーム内日数
    int completedQuestCount_;                    // 完了したクエストの数

    /// @brief 納品依頼データ初期化
    void InitializeQuests(void);

    /// @brief 個別依頼の進行状況更新
    /// @param quest 更新対象のクエスト
    void UpdateQuestProgress(DeliveryQuest& quest);

    /// @brief アクティブ依頼描画
    void DrawActiveQuests(void);

    /// @brief アイテム現在数取得
    /// @param itemId 取得対象のアイテムID
    /// @return アイテムの所持数
    int GetCurrentItemCount(const std::string& itemId);
};