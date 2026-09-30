#include "BulletinBoard.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../../DrawUI/SceneUI/QuestUI.h"
#include "../PlayerStop.h"

BulletinBoard::BulletinBoard(void)
{
    const float INITIAL_RADIUS = 0.0f;                  // 初期当たり判定半径
    const int INITIAL_QUEST_INDEX = 0;                  // 初期選択クエストインデックス
    const int INITIAL_IMAGE_ID = 0;                     // 初期画像ID
    const int INITIAL_TIMER = 0;                        // 初期タイマー値
    const bool INITIAL_FLAG = false;                    // 初期フラグ状態

    transform_ = Transform();
    transform_.position = VECTOR();
    transform_.localPosition = VAdd(transform_.position, MODEL_POS);
    radius_ = INITIAL_RADIUS;
    isShowUI_ = INITIAL_FLAG;
    isShowQuestList_ = INITIAL_FLAG;
    selectedQuest_ = INITIAL_QUEST_INDEX;
    imageBoardId_ = INITIAL_IMAGE_ID;

    imageQuest_ = INITIAL_IMAGE_ID;

    uiOpenWaitFrame_ = INITIAL_TIMER;
    uiShowUIDelayFrames_ = INITIAL_TIMER;
}

BulletinBoard::~BulletinBoard(void)
{
}

void BulletinBoard::Init(void)
{
    const float ROTATION_ANGLE = 180.0f;                // 向き調整用の回転角（度）
    const float MODEL_ROTATION_Y = -105.3f;             // モデル初期Y軸回転角
    const float ROTATION_ZERO = 0.0f;                   // 回転ゼロ値
    const int INITIAL_QUEST_INDEX = 0;                  // 初期選択クエストインデックス
    const bool INITIAL_FLAG = false;                    // 初期フラグ状態

    auto& resourceManager = ResourceManager::GetInstance();

    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::BULLETIN_BOARD));
    transform_.quaternionRotation = Quaternion();
    transform_.quaternionRotationLocal = Quaternion::AngleAxis(
        Utility::DegreeToRadianDouble(ROTATION_ANGLE),
        Utility::AXIS_Y
    );
    transform_.scale = SCALE;
    transform_.rotation = { ROTATION_ZERO, MODEL_ROTATION_Y, ROTATION_ZERO };
    transform_.position = MODEL_POS;
    radius_ = RADIUS;
    isShowUI_ = INITIAL_FLAG;
    isShowQuestList_ = INITIAL_FLAG;
    selectedQuest_ = INITIAL_QUEST_INDEX;

    imageBoardId_ = resourceManager.Load(ResourceManager::SRC::IMAGE_BOARD).handleId_;
    imageQuest_ = resourceManager.Load(ResourceManager::SRC::IMAGE_REQUEST).handleId_;

    MV1SetScale(transform_.modelId, transform_.scale);
    MV1SetPosition(transform_.modelId, transform_.position);
    MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
}

void BulletinBoard::Update(void)
{
    const int QUEST_LIST_COUNT = 3;                     // クエストの総数
    const int STEP_OFFSET = 1;                          // 選択位置移動量
    const int MINIMUM_INDEX = 0;                        // 最小インデックス
    const int ZERO_FLAG = 0;                            // 未選択フラグ判定値
    const bool FLAG_true = true;                        // 有効フラグ
    const bool FLAG_false = false;                      // 無効フラグ

    auto& inputManager = InputManager::GetInstance();
    auto& soundManager = SoundManager::GetInstance();
    auto& application = Application::GetInstance();

    if (isShowUI_ && inputManager.IsTriggerDown(KEY_INPUT_RETURN))
    {
        application.SetActiveUIType(Application::ACTIVE_UI_TYPE::QUEST);
        application.SetActiveUI(FLAG_true);

        soundManager.Play(SoundManager::SOUND::SE_PUSH);

        if (!isShowQuestList_)
        {
            isShowQuestList_ = FLAG_true;
        }
        else
        {
            auto& questUI = QuestUI::GetInstance();
            const auto& selectedQuests = questUI.GetSelectedQuests();

            if (selectedQuest_ >= MINIMUM_INDEX &&
                selectedQuest_ < static_cast<int>(selectedQuests.size()))
            {
                int questId = selectedQuests[selectedQuest_].id;
                questUI.AcceptQuest(questId);
            }

            PlayerStop::GetInstance().ResumeMovement();
            isShowQuestList_ = FLAG_false;
            isShowUI_ = FLAG_false;

            application.SetActiveUIType(Application::ACTIVE_UI_TYPE::NONE);
            application.SetActiveUI(FLAG_false);
        }
    }

    if (isShowQuestList_)
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_LEFT))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            selectedQuest_ = (selectedQuest_ - STEP_OFFSET + QUEST_LIST_COUNT) % QUEST_LIST_COUNT;
        }
        else if (inputManager.IsTriggerDown(KEY_INPUT_RIGHT))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            selectedQuest_ = (selectedQuest_ + STEP_OFFSET) % QUEST_LIST_COUNT;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            soundManager.Play(SoundManager::SOUND::SE_CANCEL);
            isShowQuestList_ = FLAG_false;
            isShowUI_ = FLAG_false;
            PlayerStop::GetInstance().ResumeMovement();

            application.SetActiveUIType(Application::ACTIVE_UI_TYPE::NONE);
            application.SetActiveUI(FLAG_false);
        }
    }

    if (selectedQuest_ == ZERO_FLAG)
    {
        PlayerStop::GetInstance().ResumeMovement();
    }
}

void BulletinBoard::DrawModel(void)
{
    MV1DrawModel(transform_.modelId);
}

void BulletinBoard::DrawUI(void)
{
    SetUseZBufferFlag(false);

    const int screenWidth = Application::FULL_SCREEN_SIZE_X;
    const int screenHeight = Application::FULL_SCREEN_SIZE_Y;

    if (!isShowUI_)
    {
        SetUseZBufferFlag(true);
        return;
    }

    auto& questUI = QuestUI::GetInstance();
    const auto& quests = questUI.GetSelectedQuests();

    const int COLOR_MIN = 0;                            // 色の最小値
    const int COLOR_MAX = 255;                          // 色の最大値
    const int COLOR_BLACK = GetColor(COLOR_MIN, COLOR_MIN, COLOR_MIN); // 黒色
    const int COLOR_WHITE = GetColor(COLOR_MAX, COLOR_MAX, COLOR_MAX); // 白色

    if (!isShowQuestList_)
    {
        const int FONT_SIZE = 24;                       // フォントサイズ
        const int TEXT_PADDING_WIDTH = 30;              // テキスト背景枠の余白幅
        const int BOX_HEIGHT = 30;                      // 背景ボックスの高さ
        const int SCREEN_HALF_DIVISOR = 2;              // 画面半分除数
        const int BOX_OFFSET_Y = 100;                   // ボックス表示位置Yオフセット
        const int BG_OFFSET_LEFT = 20;                  // 背景左側オフセット
        const int BG_OFFSET_TOP = 10;                   // 背景上部オフセット
        const int BG_EXPAND_RIGHT = 20;                 // 背景右側拡張幅
        const int BG_EXPAND_BOTTOM = 10;                // 背景下部拡張幅
        const int TEXT_OFFSET_INNER = 5;                // ボックス内テキスト余白

        const char* text = "依頼";
        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_PADDING_WIDTH;
        int boxPositionX = (screenWidth - boxWidth) / SCREEN_HALF_DIVISOR;
        int boxPositionY = (screenHeight / SCREEN_HALF_DIVISOR) + BOX_OFFSET_Y;

        DrawBox(
            boxPositionX - BG_OFFSET_LEFT,
            boxPositionY - BG_OFFSET_TOP,
            boxPositionX + boxWidth + BG_EXPAND_RIGHT,
            boxPositionY + BOX_HEIGHT + BG_EXPAND_BOTTOM,
            COLOR_BLACK,
            true
        );
        DrawBox(
            boxPositionX - BG_OFFSET_LEFT,
            boxPositionY - BG_OFFSET_TOP,
            boxPositionX + boxWidth + BG_EXPAND_RIGHT,
            boxPositionY + BOX_HEIGHT + BG_EXPAND_BOTTOM,
            COLOR_WHITE,
            false
        );
        Font::GetInstance().DrawDefaultText(
            boxPositionX + TEXT_OFFSET_INNER,
            boxPositionY + TEXT_OFFSET_INNER,
            text,
            COLOR_WHITE,
            FONT_SIZE
        );
    }
    else
    {
        PlayerStop::GetInstance().StopMovement();

        uiOpenWaitFrame_ = UI_ENTER_DELAY_FRAME;

        const int BOX_WIDTH = 400;                      // 依頼枠の幅
        const int BOX_HEIGHT = 600;                     // 依頼枠の高さ
        const int SPACING = 100;                        // 枠間のスペース
        const int TOTAL_BOXES = 3;                      // 表示する枠の数
        const int MARGIN_SPACES = 2;                    // 全体のスペース数
        const int SCREEN_HALF_DIVISOR = 2;              // 中央配置用除数
        const int START_POSITION_Y = 200;               // 描画開始Y座標

        const int startPositionX = (screenWidth - (TOTAL_BOXES * BOX_WIDTH + MARGIN_SPACES * SPACING)) / SCREEN_HALF_DIVISOR;

        const float BG_OFFSET = -5.0f;                  // 背景描画位置オフセット
        const int BG_CENTER_POS = 0;                    // 背景描画の中心位置
        const double ROTATION_ANGLE_ZERO = 0.0;         // 背景回転角ゼロ
        const double BG_SCALE = 1.23;                   // 背景拡大率

        const int TITLE_OFFSET_Y = 100;                 // タイトルのYオフセット
        const int TITLE_FONT_SIZE = 24;                 // タイトルフォントサイズ
        const int TEXT_COLOR_WHITE = 0xffffff;          // 白色テキスト
        const int TEXT_COLOR_YELLOW = 0xffff00;         // 黄色テキスト
        const int TEXT_COLOR_GRAY = 0xcccccc;           // 灰色テキスト

        const int LOOP_START = 0;                       // ループ開始インデックス

        DrawRotaGraph3(
            BG_OFFSET,
            BG_OFFSET,
            BG_CENTER_POS,
            BG_CENTER_POS,
            BG_SCALE,
            BG_SCALE,
            ROTATION_ANGLE_ZERO,
            imageBoardId_,
            true
        );

        Font::GetInstance().DrawDefaultText(
            startPositionX,
            START_POSITION_Y - TITLE_OFFSET_Y,
            "===== 納品依頼一覧 =====",
            TEXT_COLOR_WHITE,
            TITLE_FONT_SIZE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );

        for (int i = LOOP_START; i < TOTAL_BOXES; i++)
        {
            int currentPositionX = startPositionX + i * (BOX_WIDTH + SPACING);
            int textColor = (i == selectedQuest_) ? TEXT_COLOR_YELLOW : TEXT_COLOR_WHITE;

            int imageWidth;
            int imageHeight;
            GetGraphSize(imageQuest_, &imageWidth, &imageHeight);

            int imagePositionX = currentPositionX + (BOX_WIDTH / SCREEN_HALF_DIVISOR) - (imageWidth / SCREEN_HALF_DIVISOR);
            int imagePositionY = START_POSITION_Y + (BOX_HEIGHT / SCREEN_HALF_DIVISOR) - (imageHeight / SCREEN_HALF_DIVISOR);

            DrawGraph(imagePositionX, imagePositionY, imageQuest_, true);

            std::string questText = "未設定";

            if (i < static_cast<int>(quests.size()))
            {
                const auto& quest = quests[i];
                questText = quest.title + " x" + std::to_string(quest.requiredAmount);
            }

            const int TEXT_OFFSET_X = 10;               // 依頼名テキストのXオフセット
            const int TEXT_OFFSET_Y = 10;               // 依頼名テキストのYオフセット
            const int QUEST_FONT_SIZE = 32;             // 依頼名フォントサイズ

            Font::GetInstance().DrawDefaultText(
                currentPositionX + TEXT_OFFSET_X,
                START_POSITION_Y + (BOX_HEIGHT / SCREEN_HALF_DIVISOR) - TEXT_OFFSET_Y,
                questText.c_str(),
                textColor,
                QUEST_FONT_SIZE
            );
        }

        const int HELP_OFFSET_Y = 30;                   // 操作説明テキストのYオフセット

        Font::GetInstance().DrawDefaultText(
            startPositionX,
            START_POSITION_Y + BOX_HEIGHT + HELP_OFFSET_Y,
            "←→キー: 選択  Enter: 決定  ESC: 閉じる",
            TEXT_COLOR_GRAY,
            TITLE_FONT_SIZE
        );
    }

    SetUseZBufferFlag(true);
}

void BulletinBoard::Draw(void)
{
}

void BulletinBoard::Release(void)
{
}

VECTOR BulletinBoard::GetHitMin(void) const
{
    return {
        transform_.position.x - radius_,
        transform_.position.y - radius_,
        transform_.position.z - radius_
    };
}

VECTOR BulletinBoard::GetHitMax(void) const
{
    return {
        transform_.position.x + radius_,
        transform_.position.y + radius_,
        transform_.position.z + radius_
    };
}

HitObject::HIT_TYPE BulletinBoard::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR BulletinBoard::GetHitPosition(void) const
{
    return transform_.position;
}

float BulletinBoard::GetHitRadius(void) const
{
    return radius_;
}

void BulletinBoard::ShowUI(void)
{
    const bool FLAG_true = true;                        // 有効フラグ
    const bool FLAG_false = false;                      // 無効フラグ

    isShowUI_ = FLAG_true;
    isShowQuestList_ = FLAG_false;
}

void BulletinBoard::HideUI(void)
{
    const bool FLAG_false = false;                      // 無効フラグ

    isShowUI_ = FLAG_false;
    isShowQuestList_ = FLAG_false;
}

bool BulletinBoard::IsValid(void) const
{
    return true;
}

void BulletinBoard::OnPlayerHit(void)
{
    ShowUI();
}

void BulletinBoard::OnPlayerExit(void)
{
    HideUI();
}

void BulletinBoard::UpdateUIVisibility(bool isHit)
{
    const bool FLAG_true = true;                        // 有効フラグ
    const bool FLAG_false = false;                      // 無効フラグ
    const int ZERO_FRAME = 0;                           // 遅延フレーム判定のゼロ値

    if (isShowUI_)
    {
        uiVisible_ = FLAG_true;
        uiHideDelayFrames_ =  UI_SHOW_DELAY_MAX;
        return;
    }

    if (isHit)
    {
        uiVisible_ = FLAG_true;
        uiHideDelayFrames_ = UI_SHOW_DELAY_MAX;
        ShowUI();
    }
    else
    {
        if (uiHideDelayFrames_ > ZERO_FRAME)
        {
            uiHideDelayFrames_--;
            ShowUI();
        }
        else if (uiVisible_)
        {
            uiVisible_ = FLAG_false;
            HideUI();
            OnPlayerExit();
        }
    }
}

bool BulletinBoard::GetQuestList(void) const
{
    return isShowQuestList_;
}