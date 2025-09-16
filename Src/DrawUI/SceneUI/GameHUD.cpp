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
    : moneyIconHandle_(-1), dateTimeManager_(nullptr)
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

    //UIフレームアイコン読み込み
    uiFrameHandle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::UI_FRAME).handleId_;

    // 所持金アイコン読み込み
    moneyIconHandle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MANEY).handleId_;

    // 時間帯アイコン読み込み（例：morning.png, day.png, evening.png, night.png）
    timeIcons_[MORNING] = ResourceManager::GetInstance().Load(ResourceManager::SRC::MORNING).handleId_;
    timeIcons_[DAY] = ResourceManager::GetInstance().Load(ResourceManager::SRC::DAY).handleId_;
    timeIcons_[EVENING] = ResourceManager::GetInstance().Load(ResourceManager::SRC::EVENING).handleId_;
    timeIcons_[NIGHT] = ResourceManager::GetInstance().Load(ResourceManager::SRC::NIGHT).handleId_;
}

void GameHUD::Update(void)
{
    if (QuestUI::GetInstance().HasReachedMaxCompletion() && maxCompleteMessageTimer_ <= 0)
    {
        maxCompleteMessageTimer_ = 60; // 10秒くらい表示
    }

    // タイマーが動いているならカウントダウン
    if (maxCompleteMessageTimer_ > 0)
    {
        maxCompleteMessageTimer_--;

        // 0 になった瞬間にタイトルへ遷移
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
    const int margin = 0;

    // ==== 所持金表示 ====
    int money = player_->GetMoney();

    int iconX = Application::DEFA_SCREEN_SIZE_X - 500;
    int iconY = margin;

    DrawRotaGraph3(iconX, iconY - 60, 0, 0, 0.27f, 0.27f,0,moneyIconHandle_, true);
    font.DrawDefaultText(iconX + 180, iconY + 15, std::to_string(money).c_str(), 0xffffff, 32, Font::FONT_TYPE_ANTIALIASING_EDGE);

    // ==== 時間帯表示 ====
    DateTimeManager::TIME_ZONE timeZone = dateTimeManager_->GetTimeZone();
    int iconIndex = static_cast<int>(timeZone);

    int timeIconX = 0;
    int timeIconY = 0;

    int completedCount = QuestUI::GetInstance().GetCompletedQuestCount();
    std::string completeText = "達成依頼数 : " + std::to_string(completedCount) + " / " + std::to_string(5);
    font.DrawDefaultText(Application::DEFA_SCREEN_SIZE_X / 2 - 100, iconY + 30, completeText.c_str(), GetColor(255, 255, 255), 28, Font::FONT_TYPE_ANTIALIASING_EDGE);

    // MAXに達したら全画面に文字を表示
    if (maxCompleteMessageTimer_ > 0)
    {
       
        std::string msg = "あなたは錬金術師として有名になった!!";
        int msgWidth = font.GetDefaultTextWidth(msg.c_str());
        int screenW = Application::DEFA_SCREEN_SIZE_X / 2;
        int screenH = Application::DEFA_SCREEN_SZIE_Y;
        font.DrawDefaultText(screenW / 2, screenH / 2, msg.c_str(), 0xffffff, 58, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }

   
    

   

    DrawRotaGraph3(timeIconX, timeIconY, 0, 0, 1.5f, 1.5f, 0, timeIcons_[iconIndex], true);

    DrawRotaGraph3(0, 0, 0, 0, 1.5f, 1.5f, 0, uiFrameHandle_, true);
}

   
