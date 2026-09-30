#include "SceneTitle.h"

#include <DxLib.h>
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Decoration/SoundManager.h"
#include "../Manager/Generic/Camera.h"
#include "../DrawUI/SceneUI/SceneUI.h"
#include "../Object/Grid.h"
#include "../Application.h"
#include "../DrawUI/Font.h"

SceneTitle::SceneTitle(void)
{
    const int INITIAL_ALPHA = 0;                            // 初期アルファ値
    const int INITIAL_PAGE = 0;                             // 初期ページ番号
    const int INITIAL_COUNT = 0;                            // 初期カウント値
    const bool INITIAL_FLAG = false;                        // 初期フラグ状態

    logoHandle_ = -1;
    grid_ = nullptr;
    isDecided_ = INITIAL_FLAG;
    blackAlpha_ = INITIAL_ALPHA;
    operationHandle_ = -1;
    movieHandle_ = -1;
    showBlackBackground_ = INITIAL_FLAG;
    playHandle_ = -1;
    playHandle2_ = -1;
    isPlay_ = INITIAL_FLAG;
    exitRequested_ = INITIAL_FLAG;
    howToPlayPage_ = INITIAL_PAGE;
    atelierHandle_ = -1;
    guildHandle_ = -1;
    gardenHandle_ = -1;
    pauseUiCount_ = INITIAL_COUNT;
}

void SceneTitle::Init(void)
{
    const int INITIAL_CURSOR_INDEX = 0;                     // 初期カーソル位置インデックス
    const int BGM_VOLUME = 40;                              // BGMの音量
    const int SE_PUSH_VOLUME = 20;                          // 決定SEの音量
    const int SE_SELECT_VOLUME = 30;                        // 選択SEの音量
    const int MOVIE_VOLUME = 255;                           // 動画の音量
    const bool MOVIE_LOOP_FLAG = true;                      // 動画のループ再生フラグ
    const bool INITIAL_FLAG = true;                         // 初期フラグ状態
    const bool INITIAL_FLAG_FALSE = false;                  // 初期フラグ状態（偽）

    auto camera = SceneManager::GetInstance().GetCamera();
    camera->ChangeMode(Camera::MODE::FREE);

    grid_ = new Grid();
    grid_->Init();

    uiMain_ = std::make_unique<SceneUi>();
    uiMain_->AddCharacter("開始");
    uiMain_->AddCharacter("遊び方");
    uiMain_->AddCharacter("操作説明");
    uiMain_->AddCharacter("クレジット");
    uiMain_->AddCharacter("ゲーム終了");

    uiHowToPlay_ = std::make_unique<SceneUi>();
    uiHowToPlay_->AddCharacter("目標について");
    uiHowToPlay_->AddCharacter("錬金について");
    uiHowToPlay_->AddCharacter("アトリエについて");
    uiHowToPlay_->AddCharacter("ギルドについて");
    uiHowToPlay_->AddCharacter("ガーデンについて");
    uiHowToPlay_->AddCharacter("戻る");

    inHowToPlayMenu_ = INITIAL_FLAG_FALSE;
    howToPlayPage_ = INITIAL_CURSOR_INDEX;

    auto& soundManager = SoundManager::GetInstance();
    auto& resourceManager = ResourceManager::GetInstance();

    soundManager.Add(
        SoundManager::TYPE::BGM,
        SoundManager::SOUND::BGM_TITLE,
        resourceManager.Load(ResourceManager::SRC::BGM_TITLE).handleId_
    );
    soundManager.Add(
        SoundManager::TYPE::SE,
        SoundManager::SOUND::SE_PUSH,
        resourceManager.Load(ResourceManager::SRC::SE_PUSH).handleId_
    );
    soundManager.Add(
        SoundManager::TYPE::SE,
        SoundManager::SOUND::SE_SELECT,
        resourceManager.Load(ResourceManager::SRC::SE_SELECT).handleId_
    );

    soundManager.AdjustVolume(SoundManager::SOUND::BGM_TITLE, BGM_VOLUME);
    soundManager.AdjustVolume(SoundManager::SOUND::SE_PUSH, SE_PUSH_VOLUME);
    soundManager.AdjustVolume(SoundManager::SOUND::SE_SELECT, SE_SELECT_VOLUME);

    soundManager.Play(SoundManager::SOUND::BGM_TITLE);

    movieHandle_ = LoadGraph((Application::PATH_MOVIE + "TitleMovie.mp4").c_str());
    PlayMovieToGraph(movieHandle_, MOVIE_LOOP_FLAG);
    SetMovieVolumeToGraph(movieHandle_, MOVIE_VOLUME);

    logoHandle_ = resourceManager.Load(ResourceManager::SRC::TITLE_LOGO).handleId_;
    operationHandle_ = resourceManager.Load(ResourceManager::SRC::OPERATION).handleId_;
    playHandle_ = resourceManager.Load(ResourceManager::SRC::PLAY_GUIDE).handleId_;
    playHandle2_ = resourceManager.Load(ResourceManager::SRC::PLAY_GUIDE2).handleId_;

    atelierHandle_ = resourceManager.Load(ResourceManager::SRC::ATELIER).handleId_;
    guildHandle_ = resourceManager.Load(ResourceManager::SRC::GUILD).handleId_;
    gardenHandle_ = resourceManager.Load(ResourceManager::SRC::GARDEN).handleId_;

    uiMain_->SetCurrentIndex(INITIAL_CURSOR_INDEX);
    showBlackBackground_ = INITIAL_FLAG_FALSE;
    isPlay_ = INITIAL_FLAG;

    pauseUiCount_ = PAUSE_UI_COUNT;
}

void SceneTitle::Update(void)
{
    const int INITIAL_PAGE_INDEX = 0;                       // ページなしの状態を表す値
    const int MENU_INDEX_START = 0;                         // 「開始」メニューのインデックス
    const int MENU_INDEX_HOW_TO_PLAY = 1;                   // 「遊び方」メニューのインデックス
    const int MENU_INDEX_OPERATION = 2;                     // 「操作説明」メニューのインデックス
    const int MENU_INDEX_CREDIT = 3;                        // 「クレジット」メニューのインデックス

    const int SUB_INDEX_TARGET = 1;                         // 遊び方サブメニュー：目標
    const int SUB_INDEX_ALCHEMY = 2;                        // 遊び方サブメニュー：錬金
    const int SUB_INDEX_ATELIER = 3;                        // 遊び方サブメニュー：アトリエ
    const int SUB_INDEX_GUILD = 4;                          // 遊び方サブメニュー：ギルド
    const int SUB_INDEX_GARDEN = 5;                         // 遊び方サブメニュー：ガーデン

    const int SUB_MENU_CHOICE_TARGET = 0;                   // 選択肢インデックス：目標
    const int SUB_MENU_CHOICE_ALCHEMY = 1;                  // 選択肢インデックス：錬金
    const int SUB_MENU_CHOICE_ATELIER = 2;                  // 選択肢インデックス：アトリエ
    const int SUB_MENU_CHOICE_GUILD = 3;                    // 選択肢インデックス：ギルド
    const int SUB_MENU_CHOICE_GARDEN = 4;                   // 選択肢インデックス：ガーデン
    const int SUB_MENU_CHOICE_BACK = 5;                     // 選択肢インデックス：戻る

    const int INDEX_STEP = 1;                               // インデックス増減ステップ値
    const bool FLAG_TRUE = true;                            // 有効フラグ
    const bool FLAG_FALSE = false;                          // 無効フラグ

    auto& soundManager = SoundManager::GetInstance();
    auto& inputManager = InputManager::GetInstance();

    if (showBlackBackground_)
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            soundManager.Play(SoundManager::SOUND::SE_CANCEL);
            showBlackBackground_ = FLAG_FALSE;
            uiMain_->SetCurrentIndex(MENU_INDEX_START);
        }
        return;
    }

    if (howToPlayPage_ > INITIAL_PAGE_INDEX)
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            soundManager.Play(SoundManager::SOUND::SE_CANCEL);
            howToPlayPage_ = INITIAL_PAGE_INDEX;
            uiMain_->SetCurrentIndex(MENU_INDEX_START);
        }
        return;
    }

    if (!inHowToPlayMenu_)
    {
        auto sceneUi = uiMain_.get();
        int currentIndex = sceneUi->GetCurrentIndex();
        int maxIndex = sceneUi->GetMaxIndex() - INDEX_STEP;
        int totalItemCount = maxIndex + INDEX_STEP;

        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentIndex = (currentIndex - INDEX_STEP + totalItemCount) % totalItemCount;
            sceneUi->SetCurrentIndex(currentIndex);
        }
        else if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentIndex = (currentIndex + INDEX_STEP) % totalItemCount;
            sceneUi->SetCurrentIndex(currentIndex);
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            Application::GetInstance().SetActiveUI(FLAG_TRUE);
            int selected = sceneUi->GetCurrentIndex();

            if (selected == MENU_INDEX_START)
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                soundManager.Stop(SoundManager::SOUND::BGM_TITLE);
                SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
                return;
            }
            else if (selected == MENU_INDEX_HOW_TO_PLAY)
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                inHowToPlayMenu_ = FLAG_TRUE;
                uiHowToPlay_->SetCurrentIndex(INITIAL_PAGE_INDEX);
            }
            else if (selected == maxIndex)
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                exitRequested_ = FLAG_TRUE;
                return;
            }
            else
            {
                showBlackBackground_ = FLAG_TRUE;
            }
        }
    }
    else
    {
        auto sceneUi = uiHowToPlay_.get();
        int currentIndex = sceneUi->GetCurrentIndex();
        int maxIndex = sceneUi->GetMaxIndex() - INDEX_STEP;
        int totalItemCount = maxIndex + INDEX_STEP;

        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentIndex = (currentIndex - INDEX_STEP + totalItemCount) % totalItemCount;
            sceneUi->SetCurrentIndex(currentIndex);
        }
        else if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentIndex = (currentIndex + INDEX_STEP) % totalItemCount;
            sceneUi->SetCurrentIndex(currentIndex);
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            int selected = sceneUi->GetCurrentIndex();

            if (selected == SUB_MENU_CHOICE_TARGET)
            {
                howToPlayPage_ = SUB_INDEX_TARGET;
            }
            else if (selected == SUB_MENU_CHOICE_ALCHEMY)
            {
                howToPlayPage_ = SUB_INDEX_ALCHEMY;
            }
            else if (selected == SUB_MENU_CHOICE_ATELIER)
            {
                howToPlayPage_ = SUB_INDEX_ATELIER;
            }
            else if (selected == SUB_MENU_CHOICE_GUILD)
            {
                howToPlayPage_ = SUB_INDEX_GUILD;
            }
            else if (selected == SUB_MENU_CHOICE_GARDEN)
            {
                howToPlayPage_ = SUB_INDEX_GARDEN;
            }
            else if (selected == SUB_MENU_CHOICE_BACK)
            {
                inHowToPlayMenu_ = FLAG_FALSE;
            }
        }
    }
}

void SceneTitle::Draw(void)
{
    const int BG_POS_X = 0;                                 // 背景描画位置X
    const int BG_POS_Y = 0;                                 // 背景描画位置Y
    const float BG_SCALE_X = 1.0f;                          // 背景スケールX
    const float BG_SCALE_Y = 1.0f;                          // 背景スケールY
    const double BG_ROTATION = 0.0;                         // 背景回転角
    const bool BG_TRANSPARENT_FALSE = false;                // 背景透過フラグ（無効）
    const bool BG_TRANSPARENT_TRUE = true;                  // 背景透過フラグ（有効）
    const int INITIAL_PAGE = 0;                             // ページなし
    const int PAGE_TARGET = 1;                              // ページ：目標
    const int PAGE_ALCHEMY = 2;                             // ページ：錬金
    const int PAGE_ATELIER = 3;                             // ページ：アトリエ
    const int PAGE_GUILD = 4;                               // ページ：ギルド
    const int PAGE_GARDEN = 5;                              // ページ：ガーデン
    const int COLOR_BLACK = GetColor(0, 0, 0);              // 黒色
    const int COLOR_WHITE = GetColor(255, 255, 255);        // 白色
    const int COLOR_GRAY = GetColor(200, 200, 200);         // 灰色テキスト
    const int SCREEN_HALF_DIVISOR = 2;                      // 画面半分除数
    const int LOGO_OFFSET_X = 55;                           // ロゴ描画Xオフセット
    const int OP_BG_OFFSET_X = 50;                          // 操作説明背景Xオフセット
    const int OP_BG_OFFSET_Y = 50;                          // 操作説明背景Yオフセット
    const int HELP_TEXT_POS_X = 50;                         // ヘルプテキストX座標
    const int HELP_TEXT_POS_Y_OFFSET = 30;                  // ヘルプテキストYオフセット

    const double SCALE_NORMAL = 1.0;                        // 標準スケール
    const double ROTATION_ZERO = 0.0;                       // 回転ゼロ

    DrawRotaGraph3(
        BG_POS_X,
        BG_POS_Y,
        BG_POS_X,
        BG_POS_Y,
        BG_SCALE_X,
        BG_SCALE_Y,
        BG_ROTATION,
        movieHandle_,
        BG_TRANSPARENT_FALSE
    );

    if (howToPlayPage_ > INITIAL_PAGE)
    {
        DrawBox(
            BG_POS_X,
            BG_POS_Y,
            Application::FULL_SCREEN_SIZE_X,
            Application::FULL_SCREEN_SIZE_Y,
            COLOR_BLACK,
            BG_TRANSPARENT_TRUE
        );

        if (howToPlayPage_ == PAGE_TARGET)
        {
            DrawRotaGraph(
                Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR,
                Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR,
                SCALE_NORMAL,
                ROTATION_ZERO,
                playHandle_,
                BG_TRANSPARENT_TRUE
            );
        }
        else if (howToPlayPage_ == PAGE_ALCHEMY)
        {
            DrawRotaGraph(
                Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR,
                Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR,
                SCALE_NORMAL,
                ROTATION_ZERO,
                playHandle2_,
                BG_TRANSPARENT_TRUE
            );
        }
        else if (howToPlayPage_ == PAGE_ATELIER)
        {
            DrawRotaGraph(
                Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR,
                Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR,
                SCALE_NORMAL,
                ROTATION_ZERO,
                atelierHandle_,
                BG_TRANSPARENT_TRUE
            );
        }
        else if (howToPlayPage_ == PAGE_GUILD)
        {
            DrawRotaGraph(
                Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR,
                Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR,
                SCALE_NORMAL,
                ROTATION_ZERO,
                guildHandle_,
                BG_TRANSPARENT_TRUE
            );
        }
        else if (howToPlayPage_ == PAGE_GARDEN)
        {
            DrawRotaGraph(
                Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR,
                Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR,
                SCALE_NORMAL,
                ROTATION_ZERO,
                gardenHandle_,
                BG_TRANSPARENT_TRUE
            );
        }

        DrawString(
            HELP_TEXT_POS_X,
            Application::FULL_SCREEN_SIZE_Y - HELP_TEXT_POS_Y_OFFSET,
            "ESCキーで戻る",
            COLOR_GRAY
        );

        return;
    }

    if (!inHowToPlayMenu_)
    {
        DrawRotaGraph(
            Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR + LOGO_OFFSET_X,
            Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR,
            SCALE_NORMAL,
            ROTATION_ZERO,
            logoHandle_,
            BG_TRANSPARENT_TRUE
        );
        uiMain_->Draw(Application::FULL_SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR);

        if (showBlackBackground_)
        {
            DrawBox(
                BG_POS_X,
                BG_POS_Y,
                Application::FULL_SCREEN_SIZE_X,
                Application::FULL_SCREEN_SIZE_Y,
                COLOR_BLACK,
                BG_TRANSPARENT_TRUE
            );

            int selected = uiMain_->GetCurrentIndex();
            const int MENU_INDEX_OPERATION = 2;             // 操作説明インデックス
            const int MENU_INDEX_CREDIT = 3;                // クレジットインデックス

            if (selected == MENU_INDEX_OPERATION)
            {
                DrawRotaGraph3(
                    OP_BG_OFFSET_X,
                    OP_BG_OFFSET_Y,
                    BG_POS_X,
                    BG_POS_Y,
                    1.0f,
                    1.0f,
                    0,
                    operationHandle_,
                    BG_TRANSPARENT_TRUE
                );
            }
            else if (selected == MENU_INDEX_CREDIT)
            {
                auto& font = Font::GetInstance();
                std::vector<std::string> lines =
                {
                    "クレジット",
                    "効果音ラボ: カーソル移動音2, キラッ2",
                    "ニコニコ・コモンズ: キャンセル音 k45mm, 午後の庭園 kenapo",
                    "BGM: Stream D (ju-nya)",
                    "効果音工房: 決定音01, 決定音19",
                    "ポケットサウンド: ファンファーレ",
                    "魔王魂: 民族10",
                    "H/MIX GALLERY: ホシノキセキ"
                };

                const int FONT_SIZE = 28;                       // フォントサイズ
                const int FONT_TYPE = DX_FONTTYPE_ANTIALIASING; // フォントタイプ
                const int LINE_SPACING_OFFSET = 24;             // 行間追加オフセット
                const int LOOP_START_INDEX = 0;                 // ループ開始インデックス

                int centerX = Application::SCREEN_SIZE_X / SCREEN_HALF_DIVISOR;
                int centerY = Application::SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR;
                int lineSpacing = FONT_SIZE + LINE_SPACING_OFFSET;

                int totalHeight = static_cast<int>(lines.size()) * lineSpacing;
                int startY = centerY - totalHeight / SCREEN_HALF_DIVISOR;

                for (size_t i = LOOP_START_INDEX; i < lines.size(); i++)
                {
                    int textWidth = font.GetDefaultTextWidth(lines[i]);
                    int drawX = centerX - textWidth / SCREEN_HALF_DIVISOR;
                    int drawY = startY + static_cast<int>(i) * lineSpacing;

                    font.DrawDefaultText(drawX, drawY, lines[i].c_str(), COLOR_WHITE, FONT_SIZE, FONT_TYPE);
                }
            }
        }
    }
    else
    {
        DrawBox(
            BG_POS_X,
            BG_POS_Y,
            Application::FULL_SCREEN_SIZE_X,
            Application::FULL_SCREEN_SIZE_Y,
            COLOR_BLACK,
            BG_TRANSPARENT_TRUE
        );

        const int SUB_MENU_OFFSET_Y = 100;                
        int centerY = Application::FULL_SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR;
        int offsetY = centerY - SUB_MENU_OFFSET_Y;

        uiHowToPlay_->Draw(offsetY);
    }
}

void SceneTitle::Release(void)
{
    DeleteGraph(movieHandle_);
    grid_->Release();
    delete grid_;
    grid_ = nullptr;
}

bool SceneTitle::IsExitRequested(void) const
{
    return exitRequested_;
}

void SceneTitle::DrawDebug(void)
{
}