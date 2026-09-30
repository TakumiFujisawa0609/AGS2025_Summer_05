#define NOMINMAX
#include "Receptionist.h"

#include <algorithm>

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "./../../DrawUI/SceneUI/QuestUI.h"
#include "../Manager/ItemManager.h"
#include "../../Object/player.h"
#include "../../Object/GuildObject/Shop.h"
#include "../PlayerStop.h"

Receptionist::Receptionist(void)
{
    transform_ = Transform();
    transform_.position = VGet(-150.0f, 0.0f, 0.0f);
    transform_.localPosition = VAdd(transform_.position, MODEL_POS);
    radius_ = 0.0f;
    isShowUI_ = false;
    isShowDeliveryMenu_ = false;
    selectedItem_ = 0;
    isSelectingQuantity_ = false;
    selectedQuantity_ = 1;
    deliveryMessageTimer_ = 0;
    lastDeliveryMessage_ = "";
    currentMode_ = MENU_MODE::MAIN_SELECT;
    mainMenuSelected_ = 0;

    itemIds_[static_cast<int>(ITEM_TYPE::HEALTH_POTION)] = "RecoveryPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::ANTIDOTE_POTION)] = "AntidotePotion";
    itemIds_[static_cast<int>(ITEM_TYPE::MAGIC_POTION)] = "MagicPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::GARBAGE)] = "Garbage";
    itemIds_[static_cast<int>(ITEM_TYPE::ANTIPARALYSIS_POTION)] = "AntiParalysisPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::SPEED_POTION)] = "SpeedPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::POWER_POTION)] = "PowerPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::DEFENSE_POTION)] = "DefensePotion";
    itemIds_[static_cast<int>(ITEM_TYPE::FIRE_SWORD)] = "FireSword";
    itemIds_[static_cast<int>(ITEM_TYPE::WATER_SWORD)] = "WaterSword";
    itemIds_[static_cast<int>(ITEM_TYPE::WIND_SWORD)] = "WindSword";
    itemIds_[static_cast<int>(ITEM_TYPE::EARTH_SWORD)] = "EarthSword";
    itemIds_[static_cast<int>(ITEM_TYPE::ICE_SWORD)] = "IceSword";
    itemIds_[static_cast<int>(ITEM_TYPE::LIGHT_SWORD)] = "LightSword";
    itemIds_[static_cast<int>(ITEM_TYPE::DARK_SWORD)] = "DarkSword";
    itemIds_[static_cast<int>(ITEM_TYPE::FIRE_WAND)] = "FireWand";
    itemIds_[static_cast<int>(ITEM_TYPE::WATER_WAND)] = "WaterWand";
    itemIds_[static_cast<int>(ITEM_TYPE::WIND_WAND)] = "WindWand";
    itemIds_[static_cast<int>(ITEM_TYPE::EARTH_WAND)] = "EarthWand";
    itemIds_[static_cast<int>(ITEM_TYPE::ICE_WAND)] = "IceWand";
    itemIds_[static_cast<int>(ITEM_TYPE::LIGHT_WAND)] = "LightWand";
    itemIds_[static_cast<int>(ITEM_TYPE::DARK_WAND)] = "DarkWand";
}

Receptionist::~Receptionist(void)
{
}

void Receptionist::Init(void)
{
    auto& resourceManager = ResourceManager::GetInstance();

    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::RECEPTIONIST));
    transform_.quaternionRotation = Quaternion();
    transform_.quaternionRotationLocal = Quaternion::AngleAxis(Utility::DegreeToRadianDouble(0.0f), Utility::AXIS_Y);
    transform_.scale = SCALE;
    transform_.position = MODEL_POS;
    transform_.localPosition = VAdd(transform_.position, MODEL_POS);
    radius_ = RADIUS;
    isShowUI_ = false;
    isShowDeliveryMenu_ = false;
    selectedItem_ = 0;
    isSelectingQuantity_ = false;
    selectedQuantity_ = 1;
    deliveryMessageTimer_ = 0;
    lastDeliveryMessage_ = "";
    isUIForcedClosed_ = false;

    currentMode_ = MENU_MODE::MAIN_SELECT;
    mainMenuSelected_ = 0;

    itemNames_[static_cast<int>(ITEM_TYPE::HEALTH_POTION)] = "回復ポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::ANTIDOTE_POTION)] = "解毒ポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::MAGIC_POTION)] = "魔法ポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::GARBAGE)] = "失敗の作品";
    itemNames_[static_cast<int>(ITEM_TYPE::ANTIPARALYSIS_POTION)] = "解麻痺ポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::SPEED_POTION)] = "俊敏ポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::POWER_POTION)] = "力のポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::DEFENSE_POTION)] = "硬化ポーション";
    itemNames_[static_cast<int>(ITEM_TYPE::FIRE_SWORD)] = "フレイムソード";
    itemNames_[static_cast<int>(ITEM_TYPE::WATER_SWORD)] = "ウォーターソード";
    itemNames_[static_cast<int>(ITEM_TYPE::WIND_SWORD)] = "ウィンドソード";
    itemNames_[static_cast<int>(ITEM_TYPE::EARTH_SWORD)] = "アースソード";
    itemNames_[static_cast<int>(ITEM_TYPE::ICE_SWORD)] = "アイスソード";
    itemNames_[static_cast<int>(ITEM_TYPE::LIGHT_SWORD)] = "ライトソード";
    itemNames_[static_cast<int>(ITEM_TYPE::DARK_SWORD)] = "ダークソード";
    itemNames_[static_cast<int>(ITEM_TYPE::FIRE_WAND)] = "フレイムワンド";
    itemNames_[static_cast<int>(ITEM_TYPE::WATER_WAND)] = "ウォーターワンド";
    itemNames_[static_cast<int>(ITEM_TYPE::WIND_WAND)] = "ウィンドワンド";
    itemNames_[static_cast<int>(ITEM_TYPE::EARTH_WAND)] = "アースワンド";
    itemNames_[static_cast<int>(ITEM_TYPE::ICE_WAND)] = "アイスワンド";
    itemNames_[static_cast<int>(ITEM_TYPE::LIGHT_WAND)] = "ライトワンド";
    itemNames_[static_cast<int>(ITEM_TYPE::DARK_WAND)] = "ダークワンド";

    itemIds_[static_cast<int>(ITEM_TYPE::HEALTH_POTION)] = "RecoveryPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::ANTIDOTE_POTION)] = "AntidotePotion";
    itemIds_[static_cast<int>(ITEM_TYPE::MAGIC_POTION)] = "MagicPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::GARBAGE)] = "Garbage";
    itemIds_[static_cast<int>(ITEM_TYPE::ANTIPARALYSIS_POTION)] = "AntiParalysisPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::SPEED_POTION)] = "SpeedPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::POWER_POTION)] = "PowerPotion";
    itemIds_[static_cast<int>(ITEM_TYPE::DEFENSE_POTION)] = "DefensePotion";
    itemIds_[static_cast<int>(ITEM_TYPE::FIRE_SWORD)] = "FireSword";
    itemIds_[static_cast<int>(ITEM_TYPE::WATER_SWORD)] = "WaterSword";
    itemIds_[static_cast<int>(ITEM_TYPE::WIND_SWORD)] = "WindSword";
    itemIds_[static_cast<int>(ITEM_TYPE::EARTH_SWORD)] = "EarthSword";
    itemIds_[static_cast<int>(ITEM_TYPE::ICE_SWORD)] = "IceSword";
    itemIds_[static_cast<int>(ITEM_TYPE::LIGHT_SWORD)] = "LightSword";
    itemIds_[static_cast<int>(ITEM_TYPE::DARK_SWORD)] = "DarkSword";
    itemIds_[static_cast<int>(ITEM_TYPE::FIRE_WAND)] = "FireWand";
    itemIds_[static_cast<int>(ITEM_TYPE::WATER_WAND)] = "WaterWand";
    itemIds_[static_cast<int>(ITEM_TYPE::WIND_WAND)] = "WindWand";
    itemIds_[static_cast<int>(ITEM_TYPE::EARTH_WAND)] = "EarthWand";
    itemIds_[static_cast<int>(ITEM_TYPE::ICE_WAND)] = "IceWand";
    itemIds_[static_cast<int>(ITEM_TYPE::LIGHT_WAND)] = "LightWand";
    itemIds_[static_cast<int>(ITEM_TYPE::DARK_WAND)] = "DarkWand";

    shop_ = std::make_shared<Shop>();
    shop_->Init();
}

void Receptionist::Update(void)
{
    auto& application = Application::GetInstance();

    if (application.GetActiveUIType() == Application::ACTIVE_UI_TYPE::TELEPORT ||
        application.GetActiveUIType() == Application::ACTIVE_UI_TYPE::QUEST)
    {
        return;
    }

    switch (currentMode_)
    {
    case MENU_MODE::MAIN_SELECT:
        UpdateMainMenu();
        break;

    case MENU_MODE::DELIVERY_MENU:
        UpdateDeliveryMenu();
        break;

    case MENU_MODE::SHOP_MENU:
        shop_->Update();

        if (!shop_->IsVisible())
        {
            currentMode_ = MENU_MODE::MAIN_SELECT;
        }
        break;

    default:
        break;
    }
}

void Receptionist::Draw(void)
{
}

void Receptionist::DrawModel(void)
{
    SetUseZBufferFlag(true);
    SetWriteZBufferFlag(true);

    if (transform_.modelId >= 0)
    {
        const float Z_OFFSET = 60.0f;                   // 描画位置のZオフセット

        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, {
            transform_.position.x,
            transform_.position.y,
            transform_.position.z + Z_OFFSET
            });
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void Receptionist::DrawUI(void)
{
    if (!isShowUI_ && deliveryMessageTimer_ <= 0)
    {
        return;
    }

    SetUseZBufferFlag(false);
    SetWriteZBufferFlag(false);

    switch (currentMode_)
    {
    case MENU_MODE::MAIN_SELECT:
        DrawMainMenu();
        break;
    case MENU_MODE::DELIVERY_MENU:
        DrawDeliveryMenu();
        break;
    case MENU_MODE::SHOP_MENU:
        if (shop_ != nullptr)
        {
            shop_->Draw();
        }
        break;
    default:
        break;
    }

    if (deliveryMessageTimer_ > 0)
    {
        const int MESSAGE_POS_X = 100;                  // メッセージのX座標
        const int MESSAGE_POS_Y = 95;                   // メッセージのY座標
        const int FONT_SIZE = 24;                       // フォントサイズ

        Font::GetInstance().DrawDefaultText(
            MESSAGE_POS_X,
            MESSAGE_POS_Y,
            lastDeliveryMessage_.c_str(),
            0x0,
            FONT_SIZE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );
        deliveryMessageTimer_--;
    }

    SetUseZBufferFlag(true);
    SetWriteZBufferFlag(true);
}

void Receptionist::Release(void)
{
}

HitObject::HIT_TYPE Receptionist::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR Receptionist::GetHitPosition(void) const
{
    return transform_.position;
}

float Receptionist::GetHitRadius(void) const
{
    return radius_;
}

void Receptionist::ShowUI(void)
{
    if (isUIForcedClosed_)
    {
        return;
    }

    isShowUI_ = true;
    currentMode_ = MENU_MODE::MAIN_SELECT;
    mainMenuSelected_ = 0;
    isShowDeliveryMenu_ = false;
    isSelectingQuantity_ = false;

    deliverableItems_.clear();

    auto& activeQuests = QuestUI::GetInstance().GetActiveQuests();
    for (const auto& quest : activeQuests)
    {
        const std::string& targetId = quest.targetItemId;

        for (int i = 0; i < static_cast<int>(ITEM_TYPE::ITEM_COUNT); ++i)
        {
            if (GetItemId(static_cast<ITEM_TYPE>(i)) == targetId)
            {
                deliverableItems_.push_back(static_cast<ITEM_TYPE>(i));
                break;
            }
        }
    }

    selectedItem_ = 0;
}

void Receptionist::HideUI(void)
{
    isShowUI_ = false;
    isShowDeliveryMenu_ = false;
    isSelectingQuantity_ = false;
    isUIForcedClosed_ = true;
}

bool Receptionist::IsValid(void) const
{
    return true;
}

void Receptionist::OnPlayerHit(void)
{
    ShowUI();
}

void Receptionist::OnPlayerExit(void)
{
    HideUI();
    isUIForcedClosed_ = false;
}

void Receptionist::UpdateMainMenu(void)
{
    auto& inputManager = InputManager::GetInstance();
    auto& soundManager = SoundManager::GetInstance();

    if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
    {
        soundManager.Play(SoundManager::SOUND::SE_SELECT);
        mainMenuSelected_ = (mainMenuSelected_ + 1) % 2;
    }
    else if (inputManager.IsTriggerDown(KEY_INPUT_UP))
    {
        soundManager.Play(SoundManager::SOUND::SE_SELECT);
        mainMenuSelected_ = (mainMenuSelected_ - 1 + 2) % 2;
    }

    if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
    {
        Application::GetInstance().SetActiveUI(true);
        soundManager.Play(SoundManager::SOUND::SE_PUSH);

        if (mainMenuSelected_ == 0)
        {
            currentMode_ = MENU_MODE::DELIVERY_MENU;
            isShowDeliveryMenu_ = true;
        }
        else if (mainMenuSelected_ == 1)
        {
            shop_->Show();
            currentMode_ = MENU_MODE::SHOP_MENU;
        }
    }
}

void Receptionist::UpdateShopMenu(void)
{
    auto& soundManager = SoundManager::GetInstance();
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
    {
        soundManager.Play(SoundManager::SOUND::SE_CANCEL);
        currentMode_ = MENU_MODE::MAIN_SELECT;
        PlayerStop::GetInstance().ResumeMovement();
    }
}

void Receptionist::UpdateDeliveryMenu(void)
{
    auto& inputManager = InputManager::GetInstance();

    if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
    {
        if (DeliverSelectedQuantity())
        {
            isShowDeliveryMenu_ = false;
            currentMode_ = MENU_MODE::MAIN_SELECT;
        }
    }

    if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
    {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_CANCEL);

        if (isSelectingQuantity_)
        {
            isSelectingQuantity_ = false;
        }
        else
        {
            isShowDeliveryMenu_ = false;
            currentMode_ = MENU_MODE::MAIN_SELECT;
        }

        PlayerStop::GetInstance().ResumeMovement();
    }
}

void Receptionist::UpdateDeliverableItems(void)
{
    deliverableItems_.clear();

    auto& activeQuests = QuestUI::GetInstance().GetActiveQuests();
    for (const auto& quest : activeQuests)
    {
        const std::string& targetId = quest.targetItemId;

        for (int i = 0; i < static_cast<int>(ITEM_TYPE::ITEM_COUNT); ++i)
        {
            if (GetItemId(static_cast<ITEM_TYPE>(i)) == targetId)
            {
                deliverableItems_.push_back(static_cast<ITEM_TYPE>(i));
                break;
            }
        }
    }

    selectedItem_ = 0;
}

bool Receptionist::DeliverSelectedQuantity(void)
{
    if (selectedItem_ < 0 || selectedItem_ >= static_cast<int>(deliverableItems_.size()))
    {
        return false;
    }

    ITEM_TYPE itemType = deliverableItems_[selectedItem_];

    auto& itemManager = ItemManager::GetInstance();
    std::string itemId = GetItemId(itemType);

    auto& questUI = QuestUI::GetInstance();

    DeliveryQuest* matchedQuest = nullptr;

    for (auto& quest : questUI.GetActiveQuests())
    {
        if (quest.targetItemId == itemId)
        {
            matchedQuest = &quest;
            break;
        }
    }

    const int MESSAGE_TIMER_DURATION = 120;             

    if (matchedQuest == nullptr)
    {
        lastDeliveryMessage_ = "このアイテムは依頼対象ではありません！";
        deliveryMessageTimer_ = MESSAGE_TIMER_DURATION;
        return false;
    }

    auto item = itemManager.FindItemById(itemId);

    if (item == nullptr || item->GetQuantity() < selectedQuantity_)
    {
        lastDeliveryMessage_ = "必要な数がそろっていません！";
        deliveryMessageTimer_ = MESSAGE_TIMER_DURATION;
        return false;
    }

    itemManager.SubtractQuantity(item, matchedQuest->requiredAmount);
    matchedQuest->currentAmount += selectedQuantity_;

    if (matchedQuest->currentAmount >= matchedQuest->requiredAmount)
    {
        matchedQuest->isCompleted = true;
        questUI.CompleteQuest(matchedQuest->id);

        if (player_ != nullptr)
        {
            player_->AddMoney(matchedQuest->rewardMoney);
        }

        lastDeliveryMessage_ = std::string(GetItemName(itemType)) +
            " を納品しました！依頼完了です！";
    }
    else
    {
        lastDeliveryMessage_ = std::string(GetItemName(itemType)) + " を " +
            std::to_string(selectedQuantity_) + "個 納品しました！";
    }

    deliveryMessageTimer_ = MESSAGE_TIMER_DURATION;

    isShowDeliveryMenu_ = false;
    currentMode_ = MENU_MODE::MAIN_SELECT;
    isSelectingQuantity_ = false;
    PlayerStop::GetInstance().ResumeMovement();

    return true;
}

void Receptionist::DrawMainMenu(void)
{
    const int screenWidth = Application::SCREEN_SIZE_X;
    const int screenHeight = Application::SCREEN_SIZE_Y;

    const char* menuItems[] = { "納品", "購入" };
    const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);
    const int FONT_SIZE = 24;                           // フォントサイズ
    const int BOX_HEIGHT = 30;                          // 背景ボックスの高さ
    const int TEXT_PADDING_WIDTH = 30;                  // テキスト背景枠の余白幅
    const int Y_SPACING = 50;                           // メニュー間のY座標スペース
    const int BG_OFFSET_INNER = 10;                     // 背景内側オフセット
    const int BG_OFFSET_OUTER = 20;                     // 背景外側オフセット
    const int TEXT_OFFSET_X = 15;                       // テキストのX座標オフセット
    const int TEXT_OFFSET_Y = 5;                        // テキストのY座標オフセット

    int startY = screenHeight / 2 + 100;

    for (int i = 0; i < menuCount; i++)
    {
        const char* text = menuItems[i];
        int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_PADDING_WIDTH;
        int boxPositionX = (screenWidth - boxWidth) / 2;
        int boxPositionY = startY + i * (BOX_HEIGHT + Y_SPACING);

        if (i == mainMenuSelected_)
        {
            DrawBox(
                boxPositionX - BG_OFFSET_INNER,
                boxPositionY - BG_OFFSET_INNER,
                boxPositionX + boxWidth + BG_OFFSET_OUTER,
                boxPositionY + BOX_HEIGHT + BG_OFFSET_INNER,
                GetColor(0, 0, 0),
                true
            );
            DrawBox(
                boxPositionX - BG_OFFSET_INNER,
                boxPositionY - BG_OFFSET_INNER,
                boxPositionX + boxWidth + BG_OFFSET_OUTER,
                boxPositionY + BOX_HEIGHT + BG_OFFSET_INNER,
                GetColor(255, 255, 255),
                false
            );
            Font::GetInstance().DrawDefaultText(
                boxPositionX + TEXT_OFFSET_X,
                boxPositionY + TEXT_OFFSET_Y,
                text,
                GetColor(255, 255, 255),
                FONT_SIZE
            );
        }
        else
        {
            DrawBox(
                boxPositionX - BG_OFFSET_INNER,
                boxPositionY - BG_OFFSET_INNER,
                boxPositionX + boxWidth + BG_OFFSET_OUTER,
                boxPositionY + BOX_HEIGHT + BG_OFFSET_INNER,
                GetColor(64, 64, 64),
                true
            );
            DrawBox(
                boxPositionX - BG_OFFSET_INNER,
                boxPositionY - BG_OFFSET_INNER,
                boxPositionX + boxWidth + BG_OFFSET_OUTER,
                boxPositionY + BOX_HEIGHT + BG_OFFSET_INNER,
                GetColor(128, 128, 128),
                false
            );
            Font::GetInstance().DrawDefaultText(
                boxPositionX + TEXT_OFFSET_X,
                boxPositionY + TEXT_OFFSET_Y,
                text,
                GetColor(255, 255, 255),
                FONT_SIZE
            );
        }
    }
}

void Receptionist::DrawDeliveryMenu(void)
{
    PlayerStop::GetInstance().StopMovement();

    const int screenWidth = Application::FULL_SCREEN_SIZE_X;

    const int BOX_WIDTH = 1000;                         // 納品メニュー枠の幅
    const int BOX_HEIGHT = 800;                         // 納品メニュー枠の高さ
    const int boxPositionX = (screenWidth - BOX_WIDTH) / 2;
    const int boxPositionY = 150;                       // 納品メニューの表示開始Y座標

    const int COLOR_BLACK = GetColor(0, 0, 0);          // 黒色
    const int COLOR_WHITE = GetColor(255, 255, 255);    // 白色
    const int TEXT_COLOR_WHITE = 0xffffff;              // 白色テキスト
    const int TEXT_COLOR_GRAY = 0xcccccc;               // 灰色テキスト
    const int TEXT_COLOR_MAGENTA = 0xff00ff;            // マゼンタ色テキスト
    const int TEXT_COLOR_RED = 0xff4444;                // 赤色テキスト
    const int TEXT_COLOR_GREEN = 0x00ff00;              // 緑色テキスト

    DrawBox(
        boxPositionX,
        boxPositionY,
        boxPositionX + BOX_WIDTH,
        boxPositionY + BOX_HEIGHT,
        COLOR_BLACK,
        true
    );
    DrawBox(
        boxPositionX,
        boxPositionY,
        boxPositionX + BOX_WIDTH,
        boxPositionY + BOX_HEIGHT,
        COLOR_WHITE,
        false
    );

    Font& font = Font::GetInstance();

    const int TITLE_OFFSET_X = 20;                      // タイトルのXオフセット
    const int TITLE_OFFSET_Y = 20;                      // タイトルのYオフセット
    const int TITLE_FONT_SIZE = 24;                     // タイトルフォントサイズ
    const int SUBTITLE_OFFSET_Y = 50;                   // サブタイトルのYオフセット
    const int SUBTITLE_FONT_SIZE = 18;                  // サブタイトルフォントサイズ

    font.DrawDefaultText(
        boxPositionX + TITLE_OFFSET_X,
        boxPositionY + TITLE_OFFSET_Y,
        "===== 納品メニュー =====",
        TEXT_COLOR_WHITE,
        TITLE_FONT_SIZE
    );
    font.DrawDefaultText(
        boxPositionX + TITLE_OFFSET_X,
        boxPositionY + SUBTITLE_OFFSET_Y,
        "納品するアイテムを選択してください",
        TEXT_COLOR_GRAY,
        SUBTITLE_FONT_SIZE
    );

    const int LIST_START_OFFSET_Y = 80;                 // アイテムリスト開始Yオフセット
    const int LIST_ITEM_SPACING_Y = 30;                 // アイテムリスト行間
    const int INFO_TEXT_OFFSET_X = 250;                 // アイテム情報のXオフセット
    const int INFO_TEXT_OFFSET_Y = 350;                 // アイテム情報のYオフセット
    const int INFO_FONT_SIZE = 32;                      // アイテム情報フォントサイズ

    for (int i = 0; i < static_cast<int>(deliverableItems_.size()); i++)
    {
        ITEM_TYPE itemType = deliverableItems_[i];
        int color = (i == selectedItem_) ? TEXT_COLOR_MAGENTA : TEXT_COLOR_WHITE;
        int yPosition = boxPositionY + LIST_START_OFFSET_Y + (i * LIST_ITEM_SPACING_Y);

        int itemCount = GetItemCount(itemType);
        int requiredCount = GetRemainingDeliveryAmount(itemType);

        if (itemCount < requiredCount)
        {
            color = TEXT_COLOR_RED;
        }
        else if (itemCount == requiredCount)
        {
            color = (i == selectedItem_) ? TEXT_COLOR_MAGENTA : TEXT_COLOR_WHITE;
        }
        else
        {
            color = TEXT_COLOR_GREEN;
        }

        std::string itemInfo = std::string(GetItemName(itemType)) +
            " (所持数: " + std::to_string(itemCount) +
            " / 必要: " + std::to_string(requiredCount) + ")";

        font.DrawDefaultText(
            boxPositionX + INFO_TEXT_OFFSET_X,
            yPosition + INFO_TEXT_OFFSET_Y,
            itemInfo.c_str(),
            color,
            INFO_FONT_SIZE
        );
    }
}

void Receptionist::SetItemCount(ITEM_TYPE itemType, int count)
{
    auto& itemManager = ItemManager::GetInstance();
    std::string itemId = GetItemId(itemType);

    auto item = itemManager.FindItemById(itemId);

    if (item != nullptr)
    {
        int currentQuantity = item->GetQuantity();

        if (currentQuantity > 0)
        {
            itemManager.SubtractQuantity(item, currentQuantity);
        }

        if (count > 0)
        {
            itemManager.AddQuantity(item, count);
        }
    }
}

int Receptionist::GetItemCount(ITEM_TYPE itemType) const
{
    auto& itemManager = ItemManager::GetInstance();
    std::string itemId = GetItemId(itemType);

    auto item = itemManager.FindItemById(itemId);

    if (item != nullptr)
    {
        return item->GetQuantity();
    }

    return 0;
}

int Receptionist::GetMaxDeliveryQuantity(void) const
{
    if (selectedItem_ < 0 || selectedItem_ >= static_cast<int>(deliverableItems_.size()))
    {
        return 0;
    }

    ITEM_TYPE itemType = deliverableItems_[selectedItem_];
    int remainAmount = GetRemainingDeliveryAmount(itemType);
    int haveAmount = GetItemCount(itemType);

    return std::min(remainAmount, haveAmount);
}

const char* Receptionist::GetItemName(ITEM_TYPE itemType) const
{
    int itemIndex = static_cast<int>(itemType);

    if (itemIndex >= 0 && itemIndex < static_cast<int>(ITEM_TYPE::ITEM_COUNT))
    {
        return itemNames_[itemIndex].c_str();
    }

    return "不明なアイテム";
}

std::string Receptionist::GetItemId(ITEM_TYPE itemType) const
{
    int itemIndex = static_cast<int>(itemType);

    if (itemIndex >= 0 && itemIndex < static_cast<int>(ITEM_TYPE::ITEM_COUNT))
    {
        return itemIds_[itemIndex];
    }

    return "";
}

void Receptionist::SetPlayer(std::shared_ptr<Player> player)
{
    player_ = player;
    shop_->SetPlayer(player);
}

int Receptionist::GetRemainingDeliveryAmount(ITEM_TYPE itemType) const
{
    std::string targetId = GetItemId(itemType);

    for (const auto& quest : QuestUI::GetInstance().GetActiveQuests())
    {
        if (quest.targetItemId == targetId)
        {
            return std::max(0, quest.requiredAmount - quest.currentAmount);
        }
    }

    return 0;
}

bool Receptionist::GetShopUiVisible(void) const
{
    return shop_->IsVisible();
}

bool Receptionist::GetDeliveryMenu(void) const
{
    return isShowDeliveryMenu_;
}