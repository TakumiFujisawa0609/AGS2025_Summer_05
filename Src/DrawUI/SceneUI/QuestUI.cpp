#include "QuestUI.h"

#include <DxLib.h>
#include <algorithm>
#include <random>

#include "../../Object/Manager/ItemManager.h"
#include "../../DrawUI/Font.h"
#include "../../Manager/System/DateTimeManager.h"
#include "../../Manager/Generic/InputManager.h"

DeliveryQuest::DeliveryQuest(void)
{
    id = -1;

    requiredAmount = 0;

    currentAmount = 0;

    rewardMoney = 0;

    isCompleted = false;

    isActive = false;
}

DeliveryQuest::DeliveryQuest(int questId, const std::string& questTitle, const std::string& questDesc, const std::string& itemId, int required, int money)
{
    id = questId;

    title = questTitle;

    description = questDesc;
    
    targetItemId = itemId;

    requiredAmount = required;

    currentAmount = 0;

    rewardMoney = money * required;

    isCompleted = false;

    isActive = false;
}

//シングルトンインスタンスの初期化
QuestUI* QuestUI::instance_ = nullptr;

//インスタンスの生成
void QuestUI::CreateInstance(void)
{
    if (!instance_)
    {
        instance_ = new QuestUI();
        instance_->Init();
    }
}

//インスタンスの取得
QuestUI& QuestUI::GetInstance(void)
{
    return *instance_;
}

void QuestUI::SetDateTimeManager(DateTimeManager* dtManager)
{
    dateTimeManager_ = dtManager;
}

//初期化処理
void QuestUI::Init(void)
{
    availableQuests_.clear();
    activeQuests_.clear();
    isVisible_ = true;

    completedQuestCount_ = 0;

    lastDay_ = -1;

    InitializeQuests();
}

// 納品依頼データ初期化
void QuestUI::InitializeQuests(void)
{
	// 利用可能な納品依頼リストをクリア
    availableQuests_.clear();

    // 納品依頼データの初期化
    availableQuests_.push_back(DeliveryQuest(0, "回復ポーソン納品", "回復ポーソンを納品",
        "RecoveryPotion", 1, 150));
    availableQuests_.push_back(DeliveryQuest(1, "解毒ポーソン納品", "解毒ポーソンを納品",
        "AntidotePotion", 1 ,300));
    availableQuests_.push_back(DeliveryQuest(2, "魔法ポーソン納品", "魔法ポーソンを納品",
        "MagicPotion", 1, 400));
    availableQuests_.push_back(DeliveryQuest(3, "失敗した作品納品", "失敗した作品を納品",
        "Garbage", 1, 500));
    availableQuests_.push_back(DeliveryQuest(4, "解麻痺ポーソン納品", "解麻痺ポーソンを納品",
        "AntiParalysisPotion", 1, 400));
    availableQuests_.push_back(DeliveryQuest(5, "俊敏ポーソン納品", "俊敏ポーソンを納品",
        "SpeedPotion", 1, 400));
    availableQuests_.push_back(DeliveryQuest(6, "力のポーソン納品", "力のポーソンを納品",
        "PowerPotion", 1, 400));
    availableQuests_.push_back(DeliveryQuest(7, "硬化ポーソン納品", "硬化ポーソンを納品",
        "DefensePotion", 1, 400));
    availableQuests_.push_back(DeliveryQuest(8, "フレイムソードの納品", "フレイムソードの納品",
        "FireSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(9, "ウォーターソードの納品", "ウォーターソードの納品",
        "WaterSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(10, "ウィンドソードの納品", "ウィンドソードの納品",
        "WindSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(11, "アースソードの納品", "アースソードの納品",
        "EarthSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(12, "アイスソードの納品", "アイスソードの納品",
        "IceSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(13, "ライトソードの納品", "ライトソードの納品",
        "LightSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(14, "ダークソードの納品", "ダークソードの納品",
        "DarkSword", 1, 800));
    availableQuests_.push_back(DeliveryQuest(15, "フレイムワンドの納品", "フレイムワンドの納品",
        "FireWand", 1, 800));
    availableQuests_.push_back(DeliveryQuest(16, "ウォーターワンドの納品", "ウォーターワンドの納品",
        "WaterWand", 1, 800));
    availableQuests_.push_back(DeliveryQuest(17, "ウィンドワンドの納品", "ウィンドワンドの納品",
        "WindWand", 1, 800));
    availableQuests_.push_back(DeliveryQuest(18, "アースワンドの納品", "アースワンドの納品",
        "EarthWand", 1, 800));
    availableQuests_.push_back(DeliveryQuest(19, "アイスワンドの納品", "アイスワンドの納品",
        "IceWand", 1, 800));
    availableQuests_.push_back(DeliveryQuest(20, "ライトワンドの納品", "ライトワンドの納品",
        "LightWand", 1, 800));
    availableQuests_.push_back(DeliveryQuest(21, "ダークワンドの納品", "ダークワンドの納品",
        "DarkWand", 1, 800));

    
}

//更新処理
void QuestUI::Update(void)
{
    if (!isVisible_) return;

    if (dateTimeManager_)
    {
        int currentDay = dateTimeManager_->GetDay();

        if (lastDay_ != currentDay)
        {
            lastDay_ = currentDay;
            RefreshDailyQuests();
        }
    }

    // アクティブな依頼の進行状況を更新
    for (auto& quest : activeQuests_)
    {
        if (!quest.isCompleted)
        {
            UpdateQuestProgress(quest);
        }
    }
}


// 個別依頼の進行状況更新
void QuestUI::UpdateQuestProgress(DeliveryQuest& quest)
{
    // 納品依頼：アイテム数をチェック
    int currentCount = GetCurrentItemCount(quest.targetItemId);
    quest.currentAmount = currentCount;
    quest.isCompleted = (quest.currentAmount >= quest.requiredAmount);
}

// アイテム現在数取得
int QuestUI::GetCurrentItemCount(const std::string& itemId)
{
    auto& itemManager = ItemManager::GetInstance();
    auto item = itemManager.FindItemById(itemId);

    if (item)
    {
        return item->GetQuantity();
    }

    return 0;
}

//描画処理
void QuestUI::Draw(void)
{
    if (!isVisible_ || activeQuests_.empty()) return;

    DrawActiveQuests();
}

// アクティブ依頼描画
void QuestUI::DrawActiveQuests(void)
{
    int xBase = 100;
    int yBase = 120;
    int yOffset = yBase + 10;  // 上辺から10px下に開始（余白）
    int lineHeight = 30;       // フォント16〜20に合う余白込みの行間

    int bgWidth = 380;
    int bgHeight = 40 + (activeQuests_.size() * lineHeight);

    DrawBox(xBase, yBase, xBase + bgWidth, yBase + bgHeight, GetColor(0, 0, 0), TRUE);
    DrawBox(xBase, yBase, xBase + bgWidth, yBase + bgHeight, GetColor(255, 255, 255), FALSE);

    Font::GetInstance().DrawDefaultText(xBase + 10, yOffset, "【納品依頼】", 0xffff00, 20);
    yOffset += lineHeight;

    for (const auto& quest : activeQuests_)
    {
        unsigned int titleColor = quest.isCompleted ? 0x00ff00 : 0xffffff;
        Font::GetInstance().DrawDefaultText(xBase + 10, yOffset, quest.title.c_str(), titleColor, 24, Font::FONT_TYPE_ANTIALIASING);

        std::string progressText = "納品: " + std::to_string(quest.currentAmount) + "/" + std::to_string(quest.requiredAmount);
        unsigned int progressColor = quest.isCompleted ? 0x00ff00 :
            (quest.currentAmount > 0 ? 0xffff00 : 0xffffff);

        Font::GetInstance().DrawDefaultText(xBase + 200, yOffset, progressText.c_str(), progressColor, 24, Font::FONT_TYPE_ANTIALIASING);

        if (quest.isCompleted)
        {
            Font::GetInstance().DrawDefaultText(xBase + 330, yOffset, "完了!", 0x00ff00, 24, Font::FONT_TYPE_ANTIALIASING);
        }

        yOffset += lineHeight;
    }



    //// デバッグ情報
    //DrawFormatString(0, 500, 0xffffff, "納品依頼数: %d", (int)activeQuests_.size());
}

//依頼受注
void QuestUI::AcceptQuest(int questId)
{
    if (!activeQuests_.empty())
    {
        return;
    }

    // 抽選された依頼から探す
    for (const auto& selected : selectedQuests_)
    {
        if (selected.id == questId)
        {
            DeliveryQuest quest = selected;
            quest.isActive = true;
            quest.currentAmount = 0;
            quest.isCompleted = false;

            // アクティブ依頼に追加
            activeQuests_.push_back(quest);

            // availableQuests_ 側もフラグ更新（これで再度選ばれないようにするなら）
            for (auto& available : availableQuests_)
            {
                if (available.id == questId)
                {
                    available.isActive = true;
                    break;
                }
            }

            break;
        }
    }
}

//依頼完了
void QuestUI::CompleteQuest(int questId)
{
    // アクティブ依頼から完了依頼を削除
    for (auto it = activeQuests_.begin(); it != activeQuests_.end(); ++it)
    {
        if (it->id == questId && it->isCompleted)
        {
            // 報酬処理などをここに追加可能
            activeQuests_.erase(it);

            // 利用可能依頼リストでも非アクティブに
            for (auto& quest : availableQuests_)
            {
                if (quest.id == questId)
                {
                    quest.isActive = false;
                    break;
                }
            }

            if (completedQuestCount_ < MAX_QUESTS)
            {
                completedQuestCount_++;
            }

            break;
        }
    }
}

//進行状況更新
void QuestUI::UpdateProgress(int questId)
{
    for (auto& quest : activeQuests_)
    {
        if (quest.id == questId)
        {
            UpdateQuestProgress(quest);
            break;
        }
    }
}

//依頼がアクティブかチェック
bool QuestUI::IsQuestActive(int questId) const
{
    for (const auto& quest : activeQuests_)
    {
        if (quest.id == questId)
        {
            return true;
        }
    }
    return false;
}

//依頼が完了済みかチェック
bool QuestUI::IsQuestCompleted(int questId) const
{
    for (const auto& quest : activeQuests_)
    {
        if (quest.id == questId)
        {
            return quest.isCompleted;
        }
    }
    return false;
}

//新しい依頼を受けられるかチェック
bool QuestUI::CanAcceptNewQuest(void) const
{
    return activeQuests_.empty();
}

//UIの表示制御
void QuestUI::SetVisible(bool visible)
{
    isVisible_ = visible;
}

bool QuestUI::IsVisible(void) const
{
    return isVisible_;
}

DeliveryQuest* QuestUI::GetActiveQuest(void)
{
    if (!activeQuests_.empty())
    {
        return &activeQuests_[0];  // 1件のみ受注の前提
    }
    return nullptr;
}

std::vector<DeliveryQuest>& QuestUI::GetActiveQuests(void)
{
    return activeQuests_;
}

//リソースの解放
void QuestUI::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}

// 日替わり
void QuestUI::RefreshDailyQuests(void)
{
    std::vector<DeliveryQuest> questPool;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> percentDist(0, 99); // 0～99の乱数
    std::uniform_int_distribution<int> amountDist(1, 3);   // 1～3の納品数

    for (auto& quest : availableQuests_)
    {
        if (quest.targetItemId == "Garbage")
        {
            if (percentDist(rng) < 10) // 10%の確率で抽選
            {
                questPool.push_back(quest);
            }
        }
        else
        {
            questPool.push_back(quest);
        }
    }

    std::shuffle(questPool.begin(), questPool.end(), rng);

    selectedQuests_.clear();

    int logY = 400;
    DrawBox(0, logY - 5, 640, logY + 100, GetColor(0, 0, 0), TRUE);
    logY += 20;

    for (int i = 0; i < 3 && i < (int)questPool.size(); i++)
    {
        DeliveryQuest q = questPool[i];
        q.requiredAmount = amountDist(rng); // ← ここで1～3の納品数を設定
        q.currentAmount = 0;
        q.isCompleted = false;
        q.isActive = false;

        selectedQuests_.push_back(q);

        DrawFormatString(0, logY, GetColor(255, 255, 255), "- %s x%d", q.title.c_str(), q.requiredAmount);
        logY += 20;
    }
}

const std::vector<DeliveryQuest>& QuestUI::GetSelectedQuests(void) const
{
    return selectedQuests_;
}

int QuestUI::GetCompletedQuestCount(void) const
{
    return completedQuestCount_;
}

bool QuestUI::HasReachedMaxCompletion(void) const
{
    return completedQuestCount_ >= MAX_QUESTS;
}

void QuestUI::SetCompletedQuestCount(int com)
{
    completedQuestCount_ = com;
}


