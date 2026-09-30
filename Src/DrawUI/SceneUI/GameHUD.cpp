#include "GameHUD.h"

#include <DxLib.h>

#include "../../Object/player.h"
#include "../Font.h"
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Application.h"
#include "../../Manager/System/DateTimeManager.h"
#include "../../Manager/Generic/SceneManager.h"
#include "QuestUI.h"


GameHUD::GameHUD(void)
    : player_(nullptr)
    , dateTimeManager_(nullptr)
    , uiFrameHandle_(-1)
    , moneyIconHandle_(-1)
    , maxCompleteMessageTimer_(0)
{
    timeIcons_.fill(-1);
}

GameHUD::~GameHUD(void)
{
}

void GameHUD::Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager)
{
    player_ = player;
    dateTimeManager_ = dateTimeManager;

    uiFrameHandle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::UI_FRAME).handleId_;
    moneyIconHandle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MONEY).handleId_; 

    timeIcons_[static_cast<size_t>(TIME_ICON_INDEX::MORNING)] = 
        ResourceManager::GetInstance().Load(ResourceManager::SRC::MORNING).handleId_;
    timeIcons_[static_cast<size_t>(TIME_ICON_INDEX::DAY)] = 
        ResourceManager::GetInstance().Load(ResourceManager::SRC::DAY).handleId_;
    timeIcons_[static_cast<size_t>(TIME_ICON_INDEX::EVENING)] = 
        ResourceManager::GetInstance().Load(ResourceManager::SRC::EVENING).handleId_;
    timeIcons_[static_cast<size_t>(TIME_ICON_INDEX::NIGHT)] = 
        ResourceManager::GetInstance().Load(ResourceManager::SRC::NIGHT).handleId_;
}

void GameHUD::Update(void)
{
    if (QuestUI::GetInstance().HasReachedMaxCompletion() && maxCompleteMessageTimer_ <= 0)
    {
        maxCompleteMessageTimer_ = MESSAGE_DISPLAY_TIME;
    }

    if (maxCompleteMessageTimer_ > 0)
    {
        maxCompleteMessageTimer_--;

        if (maxCompleteMessageTimer_ == 0)
        {
            SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
            QuestUI::GetInstance().SetCompletedQuestCount(0);
        }
    }
}

void GameHUD::Draw(void)
{
    auto& font = Font::GetInstance();

    // 描画位置関連のローカル定数
    const int MARGIN = 0;                 // 画面端からのマージン
    const int MONEY_ICON_OFFSET_X = -500; // 所持金アイコンのX座標オフセット
    const int MONEY_ICON_OFFSET_Y = -60;  // 所持金アイコンのY座標オフセット
    const int MONEY_TEXT_OFFSET_X = 180;  // 所持金テキストのX座標オフセット
    const int MONEY_TEXT_OFFSET_Y = 15;   // 所持金テキストのY座標オフセット
    const int QUEST_TEXT_OFFSET_X = -100; // クエストテキストのX座標オフセット
    const int QUEST_TEXT_OFFSET_Y = 30;   // クエストテキストのY座標オフセット

    int money = player_->GetMoney(); // 所持金

    int moneyIconPositionX = Application::FULL_SCREEN_SIZE_X + MONEY_ICON_OFFSET_X; // 所持金アイコンのX座標
    int moneyIconPositionY = MARGIN;                                                // 所持金アイコンのY座標

    DrawRotaGraph3(moneyIconPositionX, moneyIconPositionY + MONEY_ICON_OFFSET_Y,
        0, 0, MONEY_ICON_SCALE, MONEY_ICON_SCALE, 0, moneyIconHandle_, true);

    font.DrawDefaultText(moneyIconPositionX + MONEY_TEXT_OFFSET_X, moneyIconPositionY
        + MONEY_TEXT_OFFSET_Y, std::to_string(money).c_str(), COLOR_WHITE,
        FONT_SIZE_MONEY, Font::FONT_TYPE_ANTIALIASING_EDGE);

    DateTimeManager::TIME_ZONE timeZone = dateTimeManager_->GetTimeZone(); // 現在の時間帯
    int iconIndex = static_cast<int>(timeZone);                            // 時間帯のインデックス

    int timeIconPositionX = 0; // 時間帯アイコンのX座標
    int timeIconPositionY = 0; // 時間帯アイコンのY座標

    int completedCount = QuestUI::GetInstance().GetCompletedQuestCount();
    std::string completeText = "達成依頼数 : " + std::to_string(completedCount)
        + " / " + std::to_string(MAX_QUEST_COUNT);

    font.DrawDefaultText(Application::FULL_SCREEN_SIZE_X / 2 + QUEST_TEXT_OFFSET_X, moneyIconPositionY 
        + QUEST_TEXT_OFFSET_Y, completeText.c_str(), COLOR_WHITE, FONT_SIZE_QUEST, 
        Font::FONT_TYPE_ANTIALIASING_EDGE);

    // MAXに達したら全画面に文字を表示
    if (maxCompleteMessageTimer_ > 0)
    {
        std::string message = "あなたは錬金術師として有名になった!!";                   // 表示するメッセージ
        int messageWidth = font.GetDefaultTextWidth(message.c_str());                   // メッセージの描画幅
        int screenWidthHalf = Application::FULL_SCREEN_SIZE_X / 2;                      // 画面の幅の半分
        int screenHeight = Application::FULL_SCREEN_SIZE_Y;                             // 画面の高さ

        font.DrawDefaultText(screenWidthHalf / 2, screenHeight / 2, message.c_str(),
            COLOR_WHITE, FONT_SIZE_MESSAGE, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }

    DrawRotaGraph3(timeIconPositionX, timeIconPositionY, 0, 0, TIME_ICON_SCALE,
        TIME_ICON_SCALE, 0, timeIcons_[iconIndex], true);

    DrawRotaGraph3(0, 0, 0, 0, UI_FRAME_SCALE, UI_FRAME_SCALE, 0, uiFrameHandle_, true);
}