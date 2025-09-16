#pragma once

#include <string>
#include <vector>
#include <memory>

class DateTimeManager;

//納品依頼情報を格納する構造体
struct DeliveryQuest
{
	int id;					    //依頼ID
	std::string title;		    //依頼タイトル
    std::string description;     // 依頼説明
    std::string targetItemId;    // 対象アイテムID
    int requiredAmount;          // 必要数量
    int currentAmount;           // 現在の進行数
	int rewardMoney;             // 報酬金
    bool isCompleted;            // 完了フラグ
    bool isActive;               // アクティブフラグ

    DeliveryQuest(void);

    DeliveryQuest(int questId, const std::string& questTitle, const std::string& questDesc, const std::string& itemId, int required, int money);
};

class QuestUI
{
public:

    static constexpr int MAX_QUESTS = 5;

    //シングルトンインスタンス生成
    static void CreateInstance(void);
    
    //シングルトンインスタンスの取得
    static QuestUI& GetInstance(void);

    //リソースの解放
    static void Destroy(void);

    ~QuestUI(void) = default;

	// 日数マネージャーの設定
    void SetDateTimeManager(DateTimeManager* dtManager);

    //初期化処理
    void Init(void);

    //更新処理
    void Update(void);

    //描画処理
    void Draw(void);

    //納品依頼管理

    //依頼受注
    void AcceptQuest(int questId);

    //依頼完了
    void CompleteQuest(int questId);

    //進行状況更新
    void UpdateProgress(int questId);

    //新しい依頼を受けられるかチェック
    bool CanAcceptNewQuest(void) const;

    //依頼がアクティブかチェック
    bool IsQuestActive(int questId) const;

    //依頼が完了済みかチェック
    bool IsQuestCompleted(int questId) const;

    // UI表示制御
    void SetVisible(bool visible);

    bool IsVisible(void) const;

    // アクティブ依頼を取得（1件のみ受けている前提）
    DeliveryQuest* GetActiveQuest(void);

    std::vector<DeliveryQuest>& GetActiveQuests(void);

    void RefreshDailyQuests(void);

    const std::vector<DeliveryQuest>& GetSelectedQuests(void) const;

    int GetCompletedQuestCount(void) const;

    bool HasReachedMaxCompletion(void) const;

    void SetCompletedQuestCount(int com);


private:
    QuestUI() = default;

    QuestUI(const QuestUI&) = delete;

    QuestUI& operator=(const QuestUI&) = delete;

    static QuestUI* instance_;

    // 利用可能な納品依頼リスト
    std::vector<DeliveryQuest> availableQuests_;

    // アクティブな納品依頼リスト
    std::vector<DeliveryQuest> activeQuests_; 

    //依頼候補
    std::vector<DeliveryQuest> selectedQuests_;

    //日数
    DateTimeManager* dateTimeManager_;
    
    // UI表示フラグ
    bool isVisible_;  

    //前回ゲーム内日数
    int lastDay_;

    int completedQuestCount_;

    // 内部メソッド
   
    // 納品依頼データ初期化
    void InitializeQuests(void);

    // 個別依頼の進行状況更新
    void UpdateQuestProgress(DeliveryQuest& quest); 
    
    // アクティブ依頼描画
    void DrawActiveQuests(void);                  

    // アイテム現在数取得
    int GetCurrentItemCount(const std::string& itemId); 


};

