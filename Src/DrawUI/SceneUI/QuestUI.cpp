#include "QuestUI.h"

#include <DxLib.h>
#include <algorithm>
#include <random>

#include "../../Object/Manager/ItemManager.h"
#include "../../DrawUI/Font.h"
#include "../../Manager/System/DateTimeManager.h"

DeliveryQuest::DeliveryQuest(void)
{
    id = -1;

    requiredAmount = 0;

    currentAmount = 0;

    rewardMoney = 0;

    isCompleted = false;

    isActive = false;
}

DeliveryQuest::DeliveryQuest(int questId, const std::string& questTitle, const std::string& questDesc, const std::string& itemId, int required , int money)
{
    id = questId;

    title = questTitle;

    description = questDesc;

    targetItemId = itemId;

    requiredAmount = required;

    currentAmount = 0;

    rewardMoney = money;

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

    lastDay_ = -1;

    InitializeQuests();
}

// 納品依頼データ初期化
void QuestUI::InitializeQuests(void)
{
	// 利用可能な納品依頼リストをクリア
    availableQuests_.clear();

    // 納品依頼データの初期化
    availableQuests_.push_back(DeliveryQuest(0, "回復ポーソン納品", "回復ポーションを納品",
        "RecoveryPotion", 3, 300));
    availableQuests_.push_back(DeliveryQuest(1, "解毒ポーソン納品", "解毒ポーションを納品",
        "AntidotePotion", 2 ,400));
    availableQuests_.push_back(DeliveryQuest(2, "魔法ポーソン納品", "魔法ポーションを納品",
        "MagicPotion", 1, 500));
    availableQuests_.push_back(DeliveryQuest(3, "失敗した作品納品", "失敗した作品を納品",
        "Garbage", 1, 1000));
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

            std::vector<DeliveryQuest> questPool;

           /* for (auto& quest : availableQuests_)
            {
                if (quest.targetItemId == "Garbage")
                {
                    if (GetRand(100) < 100)
                    {
                        questPool.push_back(quest);
                    }
                }
                else
                {
                    questPool.push_back(quest);
                }
            }*/


            //ランダムで最大3件抽選
            std::random_device rd;
            std::mt19937 rng(rd());
            std::shuffle(questPool.begin(), questPool.end(), rng);

            selectedQuests_.clear();
            for (int i = 0; i < 3 && i < (int)questPool.size(); i++)
            {
                DeliveryQuest q = questPool[i];
                q.requiredAmount = GetRand(2) + 1;
                q.currentAmount = 0;
                q.isCompleted = false;
                q.isActive = false;

                selectedQuests_.push_back(q);
            }
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
    int yOffset = 10;
    int lineHeight = 25;

    // 背景描画
    int bgWidth = 350;
    int bgHeight = 30 + (activeQuests_.size() * lineHeight);
    DrawBox(10, 5, 10 + bgWidth, 5 + bgHeight, GetColor(0, 0, 0), TRUE);
    DrawBox(10, 5, 10 + bgWidth, 5 + bgHeight, GetColor(255, 255, 255), FALSE);

    // タイトル描画
    Font::GetInstance().DrawDefaultText(15, yOffset, "【納品依頼】", 0xffff00, 20);
    yOffset += lineHeight;

    // アクティブ依頼リスト描画
    for (const auto& quest : activeQuests_)
    {
        // 依頼タイトル
        unsigned int titleColor = quest.isCompleted ? 0x00ff00 : 0xffffff;
        Font::GetInstance().DrawDefaultText(20, yOffset, quest.title.c_str(), titleColor, 16);

        // 納品進行状況表示
        std::string progressText = "納品: " + std::to_string(quest.currentAmount) + "/" + std::to_string(quest.requiredAmount);

        // 進行状況の色分け
        unsigned int progressColor = quest.isCompleted ? 0x00ff00 :
            (quest.currentAmount > 0 ? 0xffff00 : 0xffffff);

        Font::GetInstance().DrawDefaultText(220, yOffset, progressText.c_str(), progressColor, 16);

        // 完了マーク
        if (quest.isCompleted)
        {
            Font::GetInstance().DrawDefaultText(320, yOffset, "完了!", 0x00ff00, 16);
        }

        yOffset += lineHeight;
    }

    //// デバッグ情報
    //DrawFormatString(0, 500, 0xffffff, "納品依頼数: %d", (int)activeQuests_.size());
}

//依頼受注
void QuestUI::AcceptQuest(int questId)
{
    // 既に依頼を受けている場合は新しい依頼を受けられない
    if (!activeQuests_.empty())
    {
    Font::GetInstance().DrawDefaultText (0, 180, "既に依頼を受けています。完了してから新しい依頼を受けてください。", 0xff0000, 16);
        return;
    }

    // 利用可能な依頼から指定IDの依頼を探す
    for (auto& quest : availableQuests_)
    {
        if (quest.id == questId && !quest.isActive)
        {
            quest.isActive = true;
            quest.currentAmount = 0;
            quest.isCompleted = false;

            // アクティブ依頼リストに追加
            activeQuests_.push_back(quest);

            //// デバッグ出力
            //DrawFormatString(0, 520, 0x00ff00, "依頼受注: %s", quest.title.c_str());
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