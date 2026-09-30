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

DeliveryQuest::DeliveryQuest(
    int questId,
    const std::string& questTitle,
    const std::string& questDescription,
    const std::string& itemId,
    int required,
    int money)
{
    id = questId;
    title = questTitle;
    description = questDescription;
    targetItemId = itemId;
    requiredAmount = required;
    currentAmount = 0;
    rewardMoney = money * required;
    isCompleted = false;
    isActive = false;
}

QuestUI* QuestUI::instance_ = nullptr;

void QuestUI::CreateInstance(void)
{
    if (!instance_)
    {
        instance_ = new QuestUI();
        instance_->Init();
    }
}

QuestUI& QuestUI::GetInstance(void)
{
    return *instance_;
}

void QuestUI::SetDateTimeManager(DateTimeManager* dateTimeManager)
{
    dateTimeManager_ = dateTimeManager;
}

void QuestUI::Init(void)
{
    availableQuests_.clear();
    activeQuests_.clear();
    isVisible_ = true;

    completedQuestCount_ = 0;
    lastDay_ = -1;

    InitializeQuests();
}

void QuestUI::InitializeQuests(void)
{
    availableQuests_.clear();

    // 依頼データの各種定数
    const int REQUIRED_AMOUNT = 1;         // 基本となる要求数
    const int REWARD_RECOVERY_POTION = 150; // 回復ポーソン報酬
    const int REWARD_ANTIDOTE_POTION = 300; // 解毒ポーソン報酬
    const int REWARD_NORMAL_POTION = 400;   // 各種通常ポーソン報酬
    const int REWARD_GARBAGE = 500;         // 失敗作報酬
    const int REWARD_WEAPON = 800;          // 武器（剣・杖）報酬

    availableQuests_.push_back(DeliveryQuest(0, "回復ポーソン納品",
        "回復ポーソンを納品", "RecoveryPotion", REQUIRED_AMOUNT, REWARD_RECOVERY_POTION));
    availableQuests_.push_back(DeliveryQuest(1, "解毒ポーソン納品",
        "解毒ポーソンを納品", "AntidotePotion", REQUIRED_AMOUNT, REWARD_ANTIDOTE_POTION));
    availableQuests_.push_back(DeliveryQuest(2, "魔法ポーソン納品",
        "魔法ポーソンを納品", "MagicPotion", REQUIRED_AMOUNT, REWARD_NORMAL_POTION));
    availableQuests_.push_back(DeliveryQuest(3, "失敗した作品納品",
        "失敗した作品を納品", "Garbage", REQUIRED_AMOUNT, REWARD_GARBAGE));
    availableQuests_.push_back(DeliveryQuest(4, "解麻痺ポーソン納品",
        "解麻痺ポーソンを納品", "AntiParalysisPotion", REQUIRED_AMOUNT, REWARD_NORMAL_POTION));
    availableQuests_.push_back(DeliveryQuest(5, "俊敏ポーソン納品",
        "俊敏ポーソンを納品", "SpeedPotion", REQUIRED_AMOUNT, REWARD_NORMAL_POTION));
    availableQuests_.push_back(DeliveryQuest(6, "力のポーソン納品",
        "力のポーソンを納品", "PowerPotion", REQUIRED_AMOUNT, REWARD_NORMAL_POTION));
    availableQuests_.push_back(DeliveryQuest(7, "硬化ポーソン納品",
        "硬化ポーソンを納品", "DefensePotion", REQUIRED_AMOUNT, REWARD_NORMAL_POTION));
    availableQuests_.push_back(DeliveryQuest(8, "フレイムソードの納品",
        "フレイムソードの納品", "FireSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(9, "ウォーターソードの納品",
        "ウォーターソードの納品", "WaterSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(10, "ウィンドソードの納品",
        "ウィンドソードの納品", "WindSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(11, "アースソードの納品",
        "アースソードの納品", "EarthSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(12, "アイスソードの納品",
        "アイスソードの納品", "IceSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(13, "ライトソードの納品",
        "ライトソードの納品", "LightSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(14, "ダークソードの納品",
        "ダークソードの納品", "DarkSword", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(15, "フレイムワンドの納品",
        "フレイムワンドの納品", "FireWand", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(16, "ウォーターワンドの納品",
        "ウォーターワンドの納品", "WaterWand", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(17, "ウィンドワンドの納品",
        "ウィンドワンドの納品", "WindWand", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(18, "アースワンドの納品",
        "アースワンドの納品", "EarthWand", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(19, "アイスワンドの納品",
        "アイスワンドの納品", "IceWand", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(20, "ライトワンドの納品",
        "ライトワンドの納品", "LightWand", REQUIRED_AMOUNT, REWARD_WEAPON));
    availableQuests_.push_back(DeliveryQuest(21, "ダークワンドの納品",
        "ダークワンドの納品", "DarkWand", REQUIRED_AMOUNT, REWARD_WEAPON));
}

void QuestUI::Update(void)
{
    if (!isVisible_)
    {
        return;
    }

    if (dateTimeManager_)
    {
        int currentDay = dateTimeManager_->GetDay();

        if (lastDay_ != currentDay)
        {
            lastDay_ = currentDay;
            RefreshDailyQuests();
        }
    }

    for (auto& quest : activeQuests_)
    {
        if (!quest.isCompleted)
        {
            UpdateQuestProgress(quest);
        }
    }
}

void QuestUI::UpdateQuestProgress(DeliveryQuest& quest)
{
    int currentCount = GetCurrentItemCount(quest.targetItemId);
    quest.currentAmount = currentCount;
    quest.isCompleted = (quest.currentAmount >= quest.requiredAmount);
}

int QuestUI::GetCurrentItemCount(const std::string& itemId)
{
    auto& itemManager = ItemManager::GetInstance();
    auto item = itemManager.FindItemById(itemId);

    if (item)
    {
        return item->GetQuantity();
    }

    const int NOT_FOUND_COUNT = 0;
    return NOT_FOUND_COUNT;
}

void QuestUI::Draw(void)
{
    if (!isVisible_ || activeQuests_.empty())
    {
        return;
    }

    DrawActiveQuests();
}

void QuestUI::DrawActiveQuests(void)
{
    // 描画関連のローカル定数
    const int OFFSET_Y_START = 10;                // 描画開始時のYオフセット
    const int BACKGROUND_HEIGHT_PADDING = 40;     // 背景の高さパディング
    const int OFFSET_X_TITLE = 10;                // タイトルのXオフセット
    const int OFFSET_X_PROGRESS = 200;            // 進行状況テキストのXオフセット
    const int OFFSET_X_COMPLETED = 330;           // 完了テキストのXオフセット
    const int FONT_SIZE_HEADER = 20;              // ヘッダーのフォントサイズ
    const int FONT_SIZE_CONTENT = 24;             // コンテンツのフォントサイズ

    int positionYOffset = ACTIVE_QUEST_DRAW_START_Y + OFFSET_Y_START;
    int backgroundHeight = BACKGROUND_HEIGHT_PADDING + (
        static_cast<int>(activeQuests_.size()) * ACTIVE_QUEST_LINE_HEIGHT);

    DrawBox(
        ACTIVE_QUEST_DRAW_START_X,
        ACTIVE_QUEST_DRAW_START_Y,
        ACTIVE_QUEST_DRAW_START_X + ACTIVE_QUEST_BACKGROUND_WIDTH,
        ACTIVE_QUEST_DRAW_START_Y + backgroundHeight,
        COLOR_BLACK,
        true
    );

    DrawBox(
        ACTIVE_QUEST_DRAW_START_X,
        ACTIVE_QUEST_DRAW_START_Y,
        ACTIVE_QUEST_DRAW_START_X + ACTIVE_QUEST_BACKGROUND_WIDTH,
        ACTIVE_QUEST_DRAW_START_Y + backgroundHeight,
        COLOR_WHITE,
        false
    );

    Font::GetInstance().DrawDefaultText(
        ACTIVE_QUEST_DRAW_START_X + OFFSET_X_TITLE,
        positionYOffset,
        "【納品依頼】",
        COLOR_YELLOW,
        FONT_SIZE_HEADER
    );

    positionYOffset += ACTIVE_QUEST_LINE_HEIGHT;

    for (const auto& quest : activeQuests_)
    {
        unsigned int titleColor = quest.isCompleted ? COLOR_GREEN : COLOR_WHITE;
        Font::GetInstance().DrawDefaultText(
            ACTIVE_QUEST_DRAW_START_X + OFFSET_X_TITLE,
            positionYOffset,
            quest.title.c_str(),
            titleColor,
            FONT_SIZE_CONTENT,
            Font::FONT_TYPE_ANTIALIASING
        );

        std::string progressText = "納品: " + std::to_string(quest.currentAmount) +
            "/" + std::to_string(quest.requiredAmount);

        unsigned int progressColor = quest.isCompleted ? COLOR_GREEN :
            (quest.currentAmount > 0 ? COLOR_YELLOW : COLOR_WHITE);

        Font::GetInstance().DrawDefaultText(
            ACTIVE_QUEST_DRAW_START_X + OFFSET_X_PROGRESS,
            positionYOffset,
            progressText.c_str(),
            progressColor,
            FONT_SIZE_CONTENT,
            Font::FONT_TYPE_ANTIALIASING
        );

        if (quest.isCompleted)
        {
            Font::GetInstance().DrawDefaultText(
                ACTIVE_QUEST_DRAW_START_X + OFFSET_X_COMPLETED,
                positionYOffset,
                "完了!",
                COLOR_GREEN,
                FONT_SIZE_CONTENT,
                Font::FONT_TYPE_ANTIALIASING
            );
        }

        positionYOffset += ACTIVE_QUEST_LINE_HEIGHT;
    }
}

void QuestUI::AcceptQuest(int questId)
{
    if (!activeQuests_.empty())
    {
        return;
    }

    for (const auto& selected : selectedQuests_)
    {
        if (selected.id == questId)
        {
            DeliveryQuest quest = selected;
            quest.isActive = true;

            const int INITIAL_AMOUNT = 0;
            quest.currentAmount = INITIAL_AMOUNT;
            quest.isCompleted = false;

            activeQuests_.push_back(quest);

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

void QuestUI::CompleteQuest(int questId)
{
    for (auto iterator = activeQuests_.begin(); iterator != activeQuests_.end(); ++iterator)
    {
        if (iterator->id == questId && iterator->isCompleted)
        {
            activeQuests_.erase(iterator);

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

bool QuestUI::CanAcceptNewQuest(void) const
{
    return activeQuests_.empty();
}

void QuestUI::SetVisible(bool isVisible)
{
    isVisible_ = isVisible;
}

bool QuestUI::IsVisible(void) const
{
    return isVisible_;
}

DeliveryQuest* QuestUI::GetActiveQuest(void)
{
    if (!activeQuests_.empty())
    {
        const int FIRST_INDEX = 0;
        return &activeQuests_[FIRST_INDEX];
    }
    return nullptr;
}

std::vector<DeliveryQuest>& QuestUI::GetActiveQuests(void)
{
    return activeQuests_;
}

void QuestUI::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}

void QuestUI::RefreshDailyQuests(void)
{
    std::vector<DeliveryQuest> questPool;

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());

    // ランダム生成や描画用のローカル定数
    const int RANDOM_PERCENTAGE_MIN = 0;             // 確率の最小値
    const int RANDOM_PERCENTAGE_MAX = 99;            // 確率の最大値
    const int RANDOM_AMOUNT_MIN = 1;                 // 納品要求数の最小値
    const int RANDOM_AMOUNT_MAX = 3;                 // 納品要求数の最大値
    const int GARBAGE_PROBABILITY_THRESHOLD = 10;    // ゴミ依頼が選ばれる確率のしきい値
    const int DRAW_LIMIT_COUNT = 3;                  // 1日に提示する依頼の数
    const int BACKGROUND_OFFSET_Y = 5;               // ログ背景のYオフセット
    const int BACKGROUND_HEIGHT = 100;               // ログ背景の高さ
    const int LOG_DRAW_START_X = 0;                  // ログ描画のX座標
    const int REFRESH_LOG_BACKGROUND_WIDTH = 640;    // ログ背景の幅
    const int INITIAL_AMOUNT = 0;                    // クエスト受領時の初期進行数

    std::uniform_int_distribution<int> percentDistribution(
        RANDOM_PERCENTAGE_MIN, RANDOM_PERCENTAGE_MAX);
    std::uniform_int_distribution<int> amountDistribution(
        RANDOM_AMOUNT_MIN, RANDOM_AMOUNT_MAX);

    for (auto& quest : availableQuests_)
    {
        if (quest.targetItemId == "Garbage")
        {
            if (percentDistribution(randomGenerator) < GARBAGE_PROBABILITY_THRESHOLD)
            {
                questPool.push_back(quest);
            }
        }
        else
        {
            questPool.push_back(quest);
        }
    }

    std::shuffle(questPool.begin(), questPool.end(), randomGenerator);

    selectedQuests_.clear();

    int logPositionY = REFRESH_LOG_START_Y;

    DrawBox(
        LOG_DRAW_START_X,
        logPositionY - BACKGROUND_OFFSET_Y,
        REFRESH_LOG_BACKGROUND_WIDTH,
        logPositionY + BACKGROUND_HEIGHT,
        COLOR_BLACK,
        true
    );

    logPositionY += REFRESH_LOG_LINE_HEIGHT;

    for (int index = 0; index < DRAW_LIMIT_COUNT && index < static_cast<int>(questPool.size()); ++index)
    {
        DeliveryQuest generatedQuest = questPool[index];
        generatedQuest.requiredAmount = amountDistribution(randomGenerator);
        generatedQuest.currentAmount = INITIAL_AMOUNT;
        generatedQuest.isCompleted = false;
        generatedQuest.isActive = false;

        selectedQuests_.push_back(generatedQuest);

        DrawFormatString(
            LOG_DRAW_START_X,
            logPositionY,
            COLOR_WHITE,
            "- %s x%d",
            generatedQuest.title.c_str(),
            generatedQuest.requiredAmount
        );

        logPositionY += REFRESH_LOG_LINE_HEIGHT;
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

void QuestUI::SetCompletedQuestCount(int completedCount)
{
    completedQuestCount_ = completedCount;
}