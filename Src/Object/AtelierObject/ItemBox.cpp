#include "ItemBox.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/SceneUI/InventoryUI.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "../player.h"

ItemBox::ItemBox(void)
    : isShowUI_(false),
    isInventoryOpen_(false),
    inventoryUI_(new InventoryUI())
{
}

ItemBox::~ItemBox(void)
{
    delete inventoryUI_;
    inventoryUI_ = nullptr;
}

void ItemBox::SetPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
}

void ItemBox::Init(void)
{
    const float INITIAL_ROTATION_ANGLE = 0.0f;          
    auto& resourceManager = ResourceManager::GetInstance();
    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::BOX));
    transform_.position = MODEL_POSITION;
    transform_.scale = SCALE;
    transform_.rotation = VGet(
        INITIAL_ROTATION_ANGLE,
        INITIAL_ROTATION_ANGLE,
        INITIAL_ROTATION_ANGLE
    );
    radius_ = RADIUS;

    if (inventoryUI_ != nullptr)
    {
        inventoryUI_->Init();
    }
}

void ItemBox::Update(void)
{
    auto& inputManager = InputManager::GetInstance();

    if (isShowUI_ && !isInventoryOpen_)
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            Application::GetInstance().SetActiveUI(true);
            SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
            isInventoryOpen_ = true;

            if (inventoryUI_ != nullptr)
            {
                inventoryUI_->Show();
            }
        }
    }

    if (isInventoryOpen_ && inventoryUI_ != nullptr)
    {
        inventoryUI_->Update();

        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            Application::GetInstance().SetActiveUI(true);
            SoundManager::GetInstance().Play(SoundManager::SOUND::SE_CANCEL);
            isInventoryOpen_ = false;
            inventoryUI_->Hide();
        }
    }
}

void ItemBox::Draw(void)
{
    const int INVALID_MODEL_ID = 0;                     

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void ItemBox::DrawUI(void)
{
    const int screenWidth = Application::FULL_SCREEN_SIZE_X;
    const int screenHeight = Application::FULL_SCREEN_SIZE_Y;

    const int FONT_SIZE = 24;                           // フォントサイズ
    const int BOX_WIDTH_PADDING = 30;                   // 背景ボックス横パディング
    const int BOX_HEIGHT = 30;                          // 背景ボックス縦幅
    const int SCREEN_HALF_DIVISOR = 2;                  // 画面中央除数
    const int BOX_CENTER_OFFSET_Y = 180;                // メッセージボックスYオフセット
    const int FRAME_OFFSET_LEFT = 20;                   // 枠描画の左オフセット
    const int FRAME_OFFSET_TOP = 10;                    // 枠描画の上オフセット
    const int FRAME_EXPAND_RIGHT = 60;                  // 枠描画の右拡張幅
    const int FRAME_EXPAND_BOTTOM = 10;                 // 枠描画の下拡張幅
    const int TEXT_PADDING_X = 5;                       // テキスト表示Xパディング
    const int TEXT_PADDING_Y = 5;                       // テキスト表示Yパディング

    if (isShowUI_ && !isInventoryOpen_)
    {
        const char* text = "アイテムボックス";
        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + BOX_WIDTH_PADDING;
        int boxX = (screenWidth - boxWidth) / SCREEN_HALF_DIVISOR;
        int boxY = (screenHeight / SCREEN_HALF_DIVISOR) + BOX_CENTER_OFFSET_Y;

        DrawBox(
            boxX - FRAME_OFFSET_LEFT,
            boxY - FRAME_OFFSET_TOP,
            boxX + boxWidth + FRAME_EXPAND_RIGHT,
            boxY + BOX_HEIGHT + FRAME_EXPAND_BOTTOM,
            GetColor(0, 0, 0),
            true
        );

        DrawBox(
            boxX - FRAME_OFFSET_LEFT,
            boxY - FRAME_OFFSET_TOP,
            boxX + boxWidth + FRAME_EXPAND_RIGHT,
            boxY + BOX_HEIGHT + FRAME_EXPAND_BOTTOM,
            GetColor(255, 255, 255),
            false
        );

        Font::GetInstance().DrawDefaultText(
            boxX + TEXT_PADDING_X,
            boxY + TEXT_PADDING_Y,
            text,
            GetColor(255, 255, 255),
            FONT_SIZE
        );
    }

    if (isInventoryOpen_ && inventoryUI_ != nullptr)
    {
        inventoryUI_->Draw();
    }
}

void ItemBox::Release(void)
{
    const int INVALID_MODEL_ID = 0;                     // 有効モデルIDの下限
    const int MODEL_UNLOAD_ID = -1;                     // モデル破棄後のID

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.modelId = MODEL_UNLOAD_ID;
    }

    delete inventoryUI_;
    inventoryUI_ = nullptr;
}

HitObject::HIT_TYPE ItemBox::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR ItemBox::GetHitPosition(void) const
{
    return transform_.position;
}

float ItemBox::GetHitRadius(void) const
{
    return radius_;
}

void ItemBox::ShowUI(void)
{
    isShowUI_ = true;
}

void ItemBox::HideUI(void)
{
    isShowUI_ = false;
    isInventoryOpen_ = false;

    if (inventoryUI_ != nullptr)
    {
        inventoryUI_->Hide();
    }
}

bool ItemBox::IsValid(void) const
{
    return true;
}

void ItemBox::OnPlayerHit(void)
{
    ShowUI();
}

void ItemBox::OnPlayerExit(void)
{
    HideUI();
}

bool ItemBox::IsVisible(void) const
{
    if (inventoryUI_ == nullptr)
    {
        return false;
    }

    return inventoryUI_->IsVisible();
}