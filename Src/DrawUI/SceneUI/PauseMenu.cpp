#include "PauseMenu.h"
#include <DxLib.h>
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"

PauseMenu::PauseMenu(void)
    : mode_(MODE_PAUSE::SELECT),
    visible_(false),
    decisionMade_(false),
    currentIndex_(0),
    howToPlayIndex_(0),
    howToPlayPage_(0),
    controlHandle_(-1),
    alchemyHandle_(-1),
    objectiveHandle_(-1),
    atelierHandle_(-1),
    guildHandle_(-1),
    gardenHandle_(-1)
{
    menuItems_ =
    {
        "続ける",
        "遊び方",
        "操作説明",
        "ゲーム終了"
    };

    howToPlayItems_ =
    {
        "目標について",
        "錬金について",
        "アトリエについて",
        "ギルドについて",
        "ガーデンについて",
        "戻る"
    };
}

void PauseMenu::Show(void)
{
    visible_ = true;
    currentIndex_ = 0;
    decisionMade_ = false;
    mode_ = MODE_PAUSE::SELECT;
}

void PauseMenu::Hide(void)
{
    visible_ = false;
    decisionMade_ = false;
    mode_ = MODE_PAUSE::SELECT;
}

bool PauseMenu::IsVisible(void) const
{
    return visible_;
}

bool PauseMenu::IsDecisionMade(void) const
{
    return decisionMade_;
}

int PauseMenu::GetSelectedIndex(void) const
{
    return currentIndex_;
}

void PauseMenu::Init(void)
{
    alchemyHandle_ = LoadGraph((Application::PATH_IMAGE + "UI/renkint.png").c_str());
    objectiveHandle_ = LoadGraph((Application::PATH_IMAGE + "UI/mokuhyou.png").c_str());
    controlHandle_ = LoadGraph((Application::PATH_IMAGE + "UI/sousa.png").c_str());
    atelierHandle_ = LoadGraph((Application::PATH_IMAGE + "UI/atrieT.png").c_str());
    guildHandle_ = LoadGraph((Application::PATH_IMAGE + "UI/girudo.png").c_str());
    gardenHandle_ = LoadGraph((Application::PATH_IMAGE + "UI/gadenT.png").c_str());
}

void PauseMenu::Update(void)
{
    SoundManager& sound = SoundManager::GetInstance();
    auto& input = InputManager::GetInstance();

    // メニューのインデックス定数
    const int MENU_INDEX_CONTINUE = 0;     // 続ける
    const int MENU_INDEX_HOW_TO_PLAY = 1;  // 遊び方
    const int MENU_INDEX_CONTROL = 2;      // 操作説明
    const int MENU_INDEX_EXIT = 3;         // ゲーム終了

    // サブメニューからページ番号へのオフセット
    const int SUB_MENU_PAGE_OFFSET = 1;    // ページ番号オフセット

    if (mode_ == MODE_PAUSE::SELECT)
    {
        if (input.IsTriggerDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentIndex_ = (currentIndex_ + static_cast<int>(menuItems_.size()) - 1)
                % static_cast<int>(menuItems_.size());
        }

        if (input.IsTriggerDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentIndex_ = (currentIndex_ + 1) % static_cast<int>(menuItems_.size());
        }

        if (input.IsTriggerDown(KEY_INPUT_RETURN))
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);

            if (currentIndex_ == MENU_INDEX_CONTINUE)
            {
                visible_ = false;
            }
            else if (currentIndex_ == MENU_INDEX_HOW_TO_PLAY)
            {
                mode_ = MODE_PAUSE::HOW_TO_PLAY_MENU;
                howToPlayIndex_ = 0;
            }
            else if (currentIndex_ == MENU_INDEX_CONTROL)
            {
                mode_ = MODE_PAUSE::CONTROL;
            }
            else if (currentIndex_ == MENU_INDEX_EXIT)
            {
                decisionMade_ = true;
            }
        }
    }
    else if (mode_ == MODE_PAUSE::HOW_TO_PLAY_MENU)
    {
        if (input.IsTriggerDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            howToPlayIndex_ = (howToPlayIndex_ +
                static_cast<int>(howToPlayItems_.size()) - 1)
                % static_cast<int>(howToPlayItems_.size());
        }

        if (input.IsTriggerDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            howToPlayIndex_ = (howToPlayIndex_ + 1)
                % static_cast<int>(howToPlayItems_.size());
        }

        if (input.IsTriggerDown(KEY_INPUT_RETURN))
        {
            if (howToPlayIndex_ == static_cast<int>(howToPlayItems_.size()) - 1)
            {
                mode_ = MODE_PAUSE::SELECT;
            }
            else
            {
                howToPlayPage_ = howToPlayIndex_ + SUB_MENU_PAGE_OFFSET;
                mode_ = MODE_PAUSE::HOW_TO_PLAY_PAGE;
            }
        }

        if (input.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            mode_ = MODE_PAUSE::SELECT;
        }
    }
    else if (mode_ == MODE_PAUSE::HOW_TO_PLAY_PAGE)
    {
        if (input.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            mode_ = MODE_PAUSE::HOW_TO_PLAY_MENU;
        }
    }
    else if (mode_ == MODE_PAUSE::CONTROL)
    {
        if (input.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            mode_ = MODE_PAUSE::SELECT;
        }
    }
}

void PauseMenu::Draw(void)
{
    if (!visible_)
    {
        return;
    }

    const int screenWidth = Application::FULL_SCREEN_SIZE_X;
    const int screenHeight = Application::FULL_SCREEN_SIZE_Y;

    // 描画関連定数
    const int DRAW_ORIGIN_X = 0; // 描画原点X座標
    const int DRAW_ORIGIN_Y = 0; // 描画原点Y座標

    if (mode_ == MODE_PAUSE::HOW_TO_PLAY_MENU)
    {
        // メニュー描画のオフセット定数
        const int SUB_MENU_MARGIN_Y = 20;     // 項目間のマージン
        const int GUIDE_TEXT_POSITION_X = 50; // ガイドテキストX座標
        const int GUIDE_TEXT_OFFSET_Y = 50;   // ガイドテキスト下部からのオフセット

        DrawBox(DRAW_ORIGIN_X, DRAW_ORIGIN_Y, screenWidth, screenHeight, COLOR_BLACK, true);

        const int startPositionY = screenHeight / 2 -
            (static_cast<int>(howToPlayItems_.size()) *
                (FONT_SIZE_SUB_MENU + SUB_MENU_MARGIN_Y)) / 2;

        for (int index = 0; index < static_cast<int>(howToPlayItems_.size()); ++index)
        {
            int itemPositionY = startPositionY + index
                * (FONT_SIZE_SUB_MENU + SUB_MENU_ITEM_HEIGHT);
            int textWidth = Font::GetInstance().GetDefaultTextWidth(howToPlayItems_[index]);
            int textPositionX = (screenWidth / 2) - textWidth;

            if (index == howToPlayIndex_)
            {
                int boxWidth = textWidth + MARGIN_X_SELECTION * 2;
                int boxPositionX = (screenWidth - boxWidth) / 2;

                DrawBox(boxPositionX, itemPositionY - MARGIN_Y_SELECTION,
                    boxPositionX + boxWidth, itemPositionY
                    + FONT_SIZE_SUB_MENU + MARGIN_Y_SELECTION,
                    COLOR_YELLOW, false);
            }

            Font::GetInstance().DrawDefaultText(
                textPositionX,
                itemPositionY,
                howToPlayItems_[index].c_str(),
                COLOR_WHITE,
                FONT_SIZE_SUB_MENU,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }

        Font::GetInstance().DrawDefaultText(
            GUIDE_TEXT_POSITION_X,
            screenHeight - GUIDE_TEXT_OFFSET_Y,
            "SPACEで決定 / ESCで戻る",
            COLOR_GRAY,
            FONT_SIZE_GUIDE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );

        return;
    }

    if (mode_ == MODE_PAUSE::HOW_TO_PLAY_PAGE)
    {
        // ページインデックス定数
        const int PAGE_OBJECTIVE = 1; // 目標ページ
        const int PAGE_ALCHEMY = 2;   // 錬金ページ
        const int PAGE_ATELIER = 3;   // アトリエページ
        const int PAGE_GUILD = 4;     // ギルドページ
        const int PAGE_GARDEN = 5;    // ガーデンページ

        // 画像およびテキスト定数
        const double IMAGE_SCALE = 1.0; // 画像のスケール
        const double IMAGE_ANGLE = 0.0; // 画像の角度
        const int BACK_TEXT_POSITION_X = 50; // 戻るテキストX座標
        const int BACK_TEXT_OFFSET_Y = 30;   // 戻るテキスト下部からのオフセット

        DrawBox(DRAW_ORIGIN_X, DRAW_ORIGIN_Y, screenWidth, screenHeight, COLOR_BLACK, true);

        if (howToPlayPage_ == PAGE_OBJECTIVE)
        {
            DrawRotaGraph(screenWidth / 2, screenHeight / 2, IMAGE_SCALE,
                IMAGE_ANGLE, objectiveHandle_, true);
        }
        else if (howToPlayPage_ == PAGE_ALCHEMY)
        {
            DrawRotaGraph(screenWidth / 2, screenHeight / 2, IMAGE_SCALE,
                IMAGE_ANGLE, alchemyHandle_, true);
        }
        else if (howToPlayPage_ == PAGE_ATELIER)
        {
            DrawRotaGraph(screenWidth / 2, screenHeight / 2, IMAGE_SCALE,
                IMAGE_ANGLE, atelierHandle_, true);
        }
        else if (howToPlayPage_ == PAGE_GUILD)
        {
            DrawRotaGraph(screenWidth / 2, screenHeight / 2, IMAGE_SCALE,
                IMAGE_ANGLE, guildHandle_, true);
        }
        else if (howToPlayPage_ == PAGE_GARDEN)
        {
            DrawRotaGraph(screenWidth / 2, screenHeight / 2, IMAGE_SCALE,
                IMAGE_ANGLE, gardenHandle_, true);
        }

        DrawString(BACK_TEXT_POSITION_X, screenHeight - BACK_TEXT_OFFSET_Y,
            "ESCキーで戻る", COLOR_GRAY);
        return;
    }

    if (mode_ == MODE_PAUSE::CONTROL)
    {
        // 画像およびテキスト定数
        const double IMAGE_SCALE = 1.0; // 画像のスケール
        const double IMAGE_ANGLE = 0.0; // 画像の角度
        const int BACK_TEXT_POSITION_X = 50; // 戻るテキストX座標
        const int BACK_TEXT_OFFSET_Y = 30;   // 戻るテキスト下部からのオフセット

        DrawBox(DRAW_ORIGIN_X, DRAW_ORIGIN_Y, screenWidth, screenHeight, COLOR_BLACK, true);
        DrawRotaGraph(screenWidth / 2, screenHeight / 2, IMAGE_SCALE,
            IMAGE_ANGLE, controlHandle_, true);
        DrawString(BACK_TEXT_POSITION_X, screenHeight - BACK_TEXT_OFFSET_Y,
            "ESCキーで戻る", COLOR_GRAY);
        return;
    }

    // 通常のポーズメニューに関する定数
    const int MENU_BOX_PADDING_HEIGHT = 40;       // ボックスの高さパディング
    const int MENU_ITEM_OFFSET_Y = 20;            // 最初の項目のYオフセット
    const int SELECTION_BOX_OFFSET_X = 10;        // 選択枠のXオフセット
    const int SELECTION_BOX_OFFSET_Y_TOP = 5;     // 選択枠の上部オフセット
    const int SELECTION_BOX_OFFSET_Y_BOTTOM = 30; // 選択枠の下部オフセット
    const int MENU_TEXT_OFFSET_X = 150;           // テキストのXオフセット

    const int boxHeight = static_cast<int>(menuItems_.size())
        * MENU_ITEM_HEIGHT + MENU_BOX_PADDING_HEIGHT;
    const int boxPositionX = (screenWidth - MENU_BOX_WIDTH) / 2;
    const int boxPositionY = (screenHeight - boxHeight) / 2;

    DrawBox(boxPositionX, boxPositionY, boxPositionX + MENU_BOX_WIDTH,
        boxPositionY + boxHeight, COLOR_BLACK, true);

    DrawBox(boxPositionX, boxPositionY, boxPositionX + MENU_BOX_WIDTH,
        boxPositionY + boxHeight, COLOR_WHITE, false);

    for (int index = 0; index < static_cast<int>(menuItems_.size()); ++index)
    {
        int itemPositionY = boxPositionY + MENU_ITEM_OFFSET_Y + index * MENU_ITEM_HEIGHT;

        if (index == currentIndex_)
        {
            DrawBox(boxPositionX + SELECTION_BOX_OFFSET_X,
                itemPositionY - SELECTION_BOX_OFFSET_Y_TOP,
                boxPositionX + MENU_BOX_WIDTH - SELECTION_BOX_OFFSET_X,
                itemPositionY + SELECTION_BOX_OFFSET_Y_BOTTOM,
                COLOR_YELLOW, false);
        }

        Font::GetInstance().DrawDefaultText(boxPositionX + MENU_TEXT_OFFSET_X,
            itemPositionY, menuItems_[index].c_str(), COLOR_WHITE, FONT_SIZE_MENU,
            Font::FONT_TYPE_ANTIALIASING_EDGE);
    }
}

void PauseMenu::Release(void)
{
    DeleteGraph(controlHandle_);
    DeleteGraph(alchemyHandle_);
    DeleteGraph(objectiveHandle_);
    DeleteGraph(atelierHandle_);
    DeleteGraph(guildHandle_);
    DeleteGraph(gardenHandle_);
}