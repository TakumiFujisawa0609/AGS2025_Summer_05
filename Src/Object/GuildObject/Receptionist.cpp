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
    trans_ = Transform();
    // 3Dモデルを右側に配置
    trans_.pos = VGet(-150.0f, 0.0f, 0.0f);
    trans_.localPos = VAdd(trans_.pos, MODEL_POS);
    radius_ = 0.0f;
    speed_ = 0.0f;
    isShowUI_ = false;
    isShowDeliveryMenu_ = false;
    selectedItem_ = 0;
    isSelectingQuantity_ = false;
    selectedQuantity_ = 1;
    deliveryMessageTimer_ = 0;
    lastDeliveryMessage_ = "";
    currentMode_ = MENU_MODE::MAIN_SELECT;
    mainMenuSelected_ = 0;

    // アイテムIDを初期化
    itemIds_[static_cast<int>(IETEM_TYPE::HEALTH_POTION)] = "RecoveryPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::ANTIDOTE_POTION)] = "AntidotePotion";
    itemIds_[static_cast<int>(IETEM_TYPE::MAGIC_POTION)] = "MagicPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::GARBAGE)] = "Garbage";
    itemIds_[static_cast<int>(IETEM_TYPE::ANTIPARALYSIS_POTION)] = "AntiParalysisPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::SPEED_POTION)] = "SpeedPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::POWER_POTION)] = "PowerPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::DEFENSE_POTION)] = "DefensePotion";
    itemIds_[static_cast<int>(IETEM_TYPE::FIRE_SWORD)] = "FireSword";
    itemIds_[static_cast<int>(IETEM_TYPE::WATER_SWORD)] = "WaterSword";
    itemIds_[static_cast<int>(IETEM_TYPE::WIND_SWORD)] = "WindSword";
    itemIds_[static_cast<int>(IETEM_TYPE::EARTH_SWORD)] = "EarthSword";
    itemIds_[static_cast<int>(IETEM_TYPE::ICE_SWORD)] = "IIceSword";
    itemIds_[static_cast<int>(IETEM_TYPE::LIGHT_SWORD)] = "LightSword";
    itemIds_[static_cast<int>(IETEM_TYPE::DARK_SWORD)] = "DarkSword";
    itemIds_[static_cast<int>(IETEM_TYPE::FIER_WAND)] = "FireWand";
    itemIds_[static_cast<int>(IETEM_TYPE::WATER_WAND)] = "WaterWand";
    itemIds_[static_cast<int>(IETEM_TYPE::WIND_WAND)] = "WindWand";
    itemIds_[static_cast<int>(IETEM_TYPE::EARTH_WAND)] = "EarthWand";
    itemIds_[static_cast<int>(IETEM_TYPE::ICE_WAND)] = "IceWand";
    itemIds_[static_cast<int>(IETEM_TYPE::LIGHT_WAND)] = "LightWand";
    itemIds_[static_cast<int>(IETEM_TYPE::DARK_WAMD)] = "DarkWand";
}

Receptionist::~Receptionist(void)
{
}

void Receptionist::Init(void)
{
    auto& res = ResourceManager::GetInstance();

    // モデル（箱系のモデルを使用想定）
    trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::RECEPTIONIST));
    trans_.quaRot = Quaternion();
    trans_.quaRotLocal = Quaternion::AngleAxis(Utility::Deg2RadF(0.0f), Utility::AXIS_Y);
    trans_.scl = SCALE;
    // 3Dモデルを右側に配置（X軸方向に移動）
    trans_.pos = MODEL_POS;
    trans_.localPos = VAdd(trans_.pos, MODEL_POS);
    radius_ = RADIUS;
    speed_ = 0.0f;
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

    // アイテム名を初期化
    itemNames_[static_cast<int>(IETEM_TYPE::HEALTH_POTION)] = "回復ポーソン";
    itemNames_[static_cast<int>(IETEM_TYPE::ANTIDOTE_POTION)] = "解毒ポーソン";
    itemNames_[static_cast<int>(IETEM_TYPE::MAGIC_POTION)] = "魔法ポーソン";
    itemNames_[static_cast<int>(IETEM_TYPE::GARBAGE)] = "失敗の作品";
	itemNames_[static_cast<int>(IETEM_TYPE::ANTIPARALYSIS_POTION)] = "解麻痺ポーソン";
	itemNames_[static_cast<int>(IETEM_TYPE::SPEED_POTION)] = "俊敏ポーソン";
	itemNames_[static_cast<int>(IETEM_TYPE::POWER_POTION)] = "力のポーソン";
	itemNames_[static_cast<int>(IETEM_TYPE::DEFENSE_POTION)] = "硬化ポーソン";
	itemNames_[static_cast<int>(IETEM_TYPE::FIRE_SWORD)] = "フレイムソード";
	itemNames_[static_cast<int>(IETEM_TYPE::WATER_SWORD)] = "ウォーターソード";
	itemNames_[static_cast<int>(IETEM_TYPE::WIND_SWORD)] = "ウィンドソード";
	itemNames_[static_cast<int>(IETEM_TYPE::EARTH_SWORD)] = "アースソード";
	itemNames_[static_cast<int>(IETEM_TYPE::ICE_SWORD)] = "アイスソード";
	itemNames_[static_cast<int>(IETEM_TYPE::LIGHT_SWORD)] = "ライトソード";
	itemNames_[static_cast<int>(IETEM_TYPE::DARK_SWORD)] = "ダークソード";
	itemNames_[static_cast<int>(IETEM_TYPE::FIER_WAND)] = "フレイムワンド";
	itemNames_[static_cast<int>(IETEM_TYPE::WATER_WAND)] = "ウォーターワンド";
	itemNames_[static_cast<int>(IETEM_TYPE::WIND_WAND)] = "ウィンドワンド";
	itemNames_[static_cast<int>(IETEM_TYPE::EARTH_WAND)] = "アースワンド";
	itemNames_[static_cast<int>(IETEM_TYPE::ICE_WAND)] = "アイスワンド";
	itemNames_[static_cast<int>(IETEM_TYPE::LIGHT_WAND)] = "ライトワンド";
	itemNames_[static_cast<int>(IETEM_TYPE::DARK_WAMD)] = "ダークワンド";

    // アイテムIDを初期化
    itemIds_[static_cast<int>(IETEM_TYPE::HEALTH_POTION)] = "RecoveryPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::ANTIDOTE_POTION)] = "AntidotePotion";
    itemIds_[static_cast<int>(IETEM_TYPE::MAGIC_POTION)] = "MagicPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::GARBAGE)] = "Garbage";
    itemIds_[static_cast<int>(IETEM_TYPE::ANTIPARALYSIS_POTION)] = "AntiParalysisPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::SPEED_POTION)] = "SpeedPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::POWER_POTION)] = "PowerPotion";
    itemIds_[static_cast<int>(IETEM_TYPE::DEFENSE_POTION)] = "DefensePotion";
    itemIds_[static_cast<int>(IETEM_TYPE::FIRE_SWORD)] = "FireSword";
    itemIds_[static_cast<int>(IETEM_TYPE::WATER_SWORD)] = "WaterSword";
    itemIds_[static_cast<int>(IETEM_TYPE::WIND_SWORD)] = "WindSword";
    itemIds_[static_cast<int>(IETEM_TYPE::EARTH_SWORD)] = "EarthSword";
    itemIds_[static_cast<int>(IETEM_TYPE::ICE_SWORD)] = "IceSword";
    itemIds_[static_cast<int>(IETEM_TYPE::LIGHT_SWORD)] = "LightSword";
    itemIds_[static_cast<int>(IETEM_TYPE::DARK_SWORD)] = "DarkSword";
    itemIds_[static_cast<int>(IETEM_TYPE::FIER_WAND)] = "FireWand";
    itemIds_[static_cast<int>(IETEM_TYPE::WATER_WAND)] = "WaterWand";
    itemIds_[static_cast<int>(IETEM_TYPE::WIND_WAND)] = "WindWand";
    itemIds_[static_cast<int>(IETEM_TYPE::EARTH_WAND)] = "EarthWand";
    itemIds_[static_cast<int>(IETEM_TYPE::ICE_WAND)] = "IceWand";
    itemIds_[static_cast<int>(IETEM_TYPE::LIGHT_WAND)] = "LightWand";
    itemIds_[static_cast<int>(IETEM_TYPE::DARK_WAMD)] = "DarkWand";

    shop_ = std::make_shared<Shop>();
    shop_->Init();


}

void Receptionist::Update()
{
    auto& app = Application::GetInstance();

    if (app.GetActiveUI() == ActiveUI::TELEPORT || app.GetActiveUI() == ActiveUI::QUEST) {
        // テレポート中は受付嬢UIを無効化
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

        // ショップが非表示になったらメインメニューに戻る
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
    // ZバッファONでモデル描画
    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);
    if (trans_.modelId >= 0)
    {
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetPosition(trans_.modelId, { trans_.pos.x, trans_.pos.y,trans_.pos.z + 60 });
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }
}

void Receptionist::DrawUI(void)
{
    // UIを表示しない条件ならスキップ
    if (!isShowUI_ && deliveryMessageTimer_ <= 0) return;

    // ZバッファOFFでUI描画
    SetUseZBufferFlag(FALSE);
    SetWriteZBufferFlag(FALSE);

    switch (currentMode_)
    {
    case MENU_MODE::MAIN_SELECT:
        DrawMainMenu();
        break;
    case MENU_MODE::DELIVERY_MENU:
        DrawDeliveryMenu();
        break;
    case MENU_MODE::SHOP_MENU:
        if (shop_) shop_->Draw();
        break;
    default:
        break;
    }

    if (deliveryMessageTimer_ > 0)
    {
        Font::GetInstance().DrawDefaultText(100, 95, lastDeliveryMessage_.c_str(), 0x0, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
        deliveryMessageTimer_--;
    }

    // Zバッファ設定を戻す
    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);
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
    return trans_.pos;
}

float Receptionist::GetHitRadius(void) const
{
    return radius_;
}

void Receptionist::ShowUI(void)
{
    if (isUIForcedClosed_) return;
    isShowUI_ = true;
    currentMode_ = MENU_MODE::MAIN_SELECT;
    mainMenuSelected_ = 0;
    isShowDeliveryMenu_ = false;
    isSelectingQuantity_ = false;

    // アクティブな依頼に基づいて納品可能アイテムを絞る
    deliverableItems_.clear();

    auto& activeQuests = QuestUI::GetInstance().GetActiveQuests();
    for (const auto& quest : activeQuests)
    {
        const std::string& targetId = quest.targetItemId;

        // ItemTypeとIDを照合
        for (int i = 0; i < static_cast<int>(IETEM_TYPE::ITEM_COUNT); ++i)
        {
            if (GetItemId(static_cast<IETEM_TYPE>(i)) == targetId)
            {
                deliverableItems_.push_back(static_cast<IETEM_TYPE>(i));
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
void Receptionist::UpdateMainMenu()
{
    auto& input = InputManager::GetInstance();
    auto& sound = SoundManager::GetInstance();

    // 入力による選択変更
    if (input.IsTrgDown(KEY_INPUT_DOWN))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        mainMenuSelected_ = (mainMenuSelected_ + 1) % 2; // 納品と購入の2つだけ
    }
    else if (input.IsTrgDown(KEY_INPUT_UP))
    {
        sound.Play(SoundManager::SOUND::SE_SELECT);
        mainMenuSelected_ = (mainMenuSelected_ - 1 + 2) % 2;
    }

    if (input.IsTrgDown(KEY_INPUT_RETURN))
    {
        Application::GetInstance().SetActiveUI(true);
        sound.Play(SoundManager::SOUND::SE_PUSH);
        if (mainMenuSelected_ == 0)
        {
            // 納品メニューへ
            currentMode_ = MENU_MODE::DELIVERY_MENU;
            isShowDeliveryMenu_ = true;
        }
        else if (mainMenuSelected_ == 1)
        {
            // 購入メニュー（ショップ）を表示
            shop_->Show();
            currentMode_ = MENU_MODE::SHOP_MENU;
        }
    }
}

void Receptionist::UpdateShopMenu(void)
{
    auto& sound = SoundManager::GetInstance();
    auto& input = InputManager::GetInstance();

    // ショップメニューの入力処理

    if (input.IsTrgDown(KEY_INPUT_ESCAPE))
    {
        sound.Play(SoundManager::SOUND::SE_CANCEL);
        currentMode_ = MENU_MODE::MAIN_SELECT;
        PlayerStop::GetInstance().ResumeMovement();
        // 必要に応じてショップメニューのフラグをリセット
    }
}



void Receptionist::UpdateDeliveryMenu(void)
{
    auto& input = InputManager::GetInstance();

    /*if (!isSelectingQuantity_ && !deliverableItems_.empty())
    {
        int itemCount = static_cast<int>(deliverableItems_.size());
        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            selectedItem_ = (selectedItem_ - 1 + itemCount) % itemCount;
        }
        else if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            selectedItem_ = (selectedItem_ + 1) % itemCount;
        }
    }
    else if (isSelectingQuantity_)
    {
        int maxQuantity = GetMaxDeliveryQuantity();
        if (maxQuantity > 0)
        {
            if (input.IsTrgDown(KEY_INPUT_UP))
            {
                selectedQuantity_ = std::min(selectedQuantity_ + 1, maxQuantity);
            }
            else if (input.IsTrgDown(KEY_INPUT_DOWN))
            {
                selectedQuantity_ = std::max(selectedQuantity_ - 1, 1);
            }
        }
    }*/

    //if (input.IsTrgDown(KEY_INPUT_RETURN))
    //{
    //    if (!isSelectingQuantity_)
    //    {
    //        isSelectingQuantity_ = true;
    //        selectedQuantity_ = 1;
    //    }
    //    else
    //    {
    //        // 数量確定 → 納品実行
    //        if (DeliverSelectedQuantity())
    //        {
    //            isSelectingQuantity_ = false;
    //            isShowDeliveryMenu_ = false;
    //            currentMode_ = MENU_MODE::MAIN_SELECT;
    //        }
    //    }
    //}

    if (input.IsTrgDown(KEY_INPUT_RETURN))
    {
        // いきなり納品実行
        if (DeliverSelectedQuantity())
        {
            isShowDeliveryMenu_ = false;
            currentMode_ = MENU_MODE::MAIN_SELECT;
        }
    }

    if (input.IsTrgDown(KEY_INPUT_ESCAPE))
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

        for (int i = 0; i < static_cast<int>(IETEM_TYPE::ITEM_COUNT); ++i)
        {
            if (GetItemId(static_cast<IETEM_TYPE>(i)) == targetId)
            {
                deliverableItems_.push_back(static_cast<IETEM_TYPE>(i));
                break;
            }
        }
    }

    selectedItem_ = 0;
}

bool Receptionist::DeliverSelectedQuantity(void)
{
    if (selectedItem_ < 0 || selectedItem_ >= static_cast<int>(deliverableItems_.size()))
        return false;

    IETEM_TYPE itemType = deliverableItems_[selectedItem_];

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

    if (!matchedQuest)
    {
        lastDeliveryMessage_ = "このアイテムは依頼対象ではありません！";
        deliveryMessageTimer_ = 120;
        return false;
    }

    auto item = itemManager.FindItemById(itemId);
    if (!item || item->GetQuantity() < selectedQuantity_)
    {
        lastDeliveryMessage_ = "必要な数がそろっていません！";
        deliveryMessageTimer_ = 120;
        return false;
    }

    // 数量分だけ納品
    itemManager.SubtractQuantity(item, matchedQuest->requiredAmount);
    matchedQuest->currentAmount += selectedQuantity_;

    if (matchedQuest->currentAmount >= matchedQuest->requiredAmount)
    {
        matchedQuest->isCompleted = true;
        questUI.CompleteQuest(matchedQuest->id);

        if (player_)
        {
            player_->AddMoney(matchedQuest->rewardMoney);
        }

        lastDeliveryMessage_ = std::string(GetItemName(itemType)) + " を納品しました！依頼完了です！";
    }
    else
    {
        lastDeliveryMessage_ = std::string(GetItemName(itemType)) + " を " + std::to_string(selectedQuantity_) + "個 納品しました！";
    }

    deliveryMessageTimer_ = 120;

    // ✅ 納品メニューを閉じる
    isShowDeliveryMenu_ = false;
    currentMode_ = MENU_MODE::MAIN_SELECT;
    isSelectingQuantity_ = false;
    PlayerStop::GetInstance().ResumeMovement();

    return true;
}

void Receptionist::DrawMainMenu()
{
    const int screenWidth = Application::SCREEN_SIZE_X;
    const int screenHeight = Application::SCREEN_SIZE_Y;

    const char* menuItems[] = { "納品", "購入" };
    const int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);
    const int fontSize = 24;
    const int boxHeight = 30;

    int startY = screenHeight / 2 + 100;

    for (int i = 0; i < menuCount; i++)
    {
        const char* text = menuItems[i];
        int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
        int boxWidth = textWidth + 30;
        int boxX = (screenWidth - boxWidth) / 2;
        int boxY = startY + i * (boxHeight + 50);

        if (i == mainMenuSelected_)
        {
            DrawBox(boxX - 10, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
            DrawBox(boxX - 10, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
            Font::GetInstance().DrawDefaultText(boxX + 15, boxY + 5, text, GetColor(255, 255, 255), fontSize);
        }
        else
        {
            DrawBox(boxX - 10, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(64, 64, 64), TRUE);
            DrawBox(boxX - 10, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(128, 128, 128), FALSE);
            Font::GetInstance().DrawDefaultText(boxX + 15, boxY + 5, text, GetColor(255, 255, 255), fontSize);
        }
    }
}


void Receptionist::DrawDeliveryMenu(void)
{
    PlayerStop::GetInstance().StopMovement();

    const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
    const int screenHeight = Application::DEFA_SCREEN_SIZE_X;

    const int boxWidth = 1000;
    const int boxHeight = 800;
    const int boxX = (screenWidth - boxWidth) / 2;
    const int boxY = 150;

    DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
    DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);

    Font& font = Font::GetInstance();
    font.DrawDefaultText(boxX + 20, boxY + 20, "===== 納品メニュー =====", 0xffffff, 24);
    font.DrawDefaultText(boxX + 20, boxY + 50, "納品するアイテムを選択してください", 0xcccccc, 18);

    for (int i = 0; i < (int)deliverableItems_.size(); i++)
    {
        IETEM_TYPE itemType = deliverableItems_[i];
        int color = (i == selectedItem_) ? 0xff00ff : 0xffffff;
        int yPos = boxY + 80 + (i * 30);

        if (i == selectedItem_)
        {
            // font.DrawDefaultText(boxX + 20, yPos, "→", 0xff00ff, 24);
        }

        int itemCount = GetItemCount(itemType);
        int requiredCount = GetRemainingDeliveryAmount(itemType);

        // 色分け：必要数未満 → 赤、ちょうど → 白、余裕あり → 緑
        if (itemCount < requiredCount)
            color = 0xff4444;
        else if (itemCount == requiredCount)
            color = (i == selectedItem_) ? 0xff00ff : 0xffffff;
        else
            color = 0x00ff00;

        std::string itemInfo = std::string(GetItemName(itemType)) +
            " (所持数: " + std::to_string(itemCount) + " / 必要: " + std::to_string(requiredCount) + ")";

        font.DrawDefaultText(boxX + 250, yPos + 350, itemInfo.c_str(), color, 32);
    }
}


//bool Receptionist::DeliverItem(IETEM_TYPE itemType)
//{
//    auto& itemManager = ItemManager::GetInstance();
//    std::string itemId = GetItemId(itemType);
//
//    auto& questUI = QuestUI::GetInstance();
//
//    DeliveryQuest* matchedQuest = nullptr;
//    for (auto& quest : questUI.GetActiveQuests())
//    {
//        if (quest.targetItemId == itemId)
//        {
//            matchedQuest = &quest;
//            break;
//        }
//    }
//
//    if (!matchedQuest)
//    {
//        lastDeliveryMessage_ = "このアイテムは依頼対象ではありません！";
//        deliveryMessageTimer_ = 120;
//        return false;
//    }
//
//    // 必要数チェック
//    auto item = itemManager.FindItemById(itemId);
//    if (!item || item->GetQuantity() < matchedQuest->requiredAmount)
//    {
//        lastDeliveryMessage_ = "必要な数がそろっていません！";
//        deliveryMessageTimer_ = 120;
//        return false;
//    }
//
//    // 一括納品
//    itemManager.SubtractQuantity(item, matchedQuest->requiredAmount);
//    matchedQuest->isCompleted = true;
//    questUI.CompleteQuest(matchedQuest->id);
//
//    if (player_)
//    {
//        player_->AddMoney(matchedQuest->rewardMoney);
//    }
//
//    lastDeliveryMessage_ = std::string(GetItemName(itemType)) + " を納品しました！依頼完了です！";
//    deliveryMessageTimer_ = 120;
//
//    return true;
//}


void Receptionist::SetItemCount(IETEM_TYPE itemType, int count)
{
    auto& itemManager = ItemManager::GetInstance();
    std::string itemId = GetItemId(itemType);

    auto item = itemManager.FindItemById(itemId);
    if (item)
    {
        // 現在の所持数を0にしてから新しい数を設定
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

int Receptionist::GetItemCount(IETEM_TYPE itemType) const
{
    auto& itemManager = ItemManager::GetInstance();
    std::string itemId = GetItemId(itemType);

    auto item = itemManager.FindItemById(itemId);
    if (item)
    {
        return item->GetQuantity();
    }
    return 0;
}

int Receptionist::GetMaxDeliveryQuantity() const
{
    if (selectedItem_ < 0 || selectedItem_ >= static_cast<int>(deliverableItems_.size()))
        return 0;

    IETEM_TYPE itemType = deliverableItems_[selectedItem_];
    int remain = GetRemainingDeliveryAmount(itemType);
    int have = GetItemCount(itemType);
    return std::min(remain, have);
}

const char* Receptionist::GetItemName(IETEM_TYPE itemType) const
{
    int itemIndex = static_cast<int>(itemType);
    if (itemIndex >= 0 && itemIndex < static_cast<int>(IETEM_TYPE::ITEM_COUNT))
    {
        return itemNames_[itemIndex].c_str();
    }
    return "不明なアイテム";
}

std::string Receptionist::GetItemId(IETEM_TYPE itemType) const
{
    int itemIndex = static_cast<int>(itemType);
    if (itemIndex >= 0 && itemIndex < static_cast<int>(IETEM_TYPE::ITEM_COUNT))
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

int Receptionist::GetRemainingDeliveryAmount(IETEM_TYPE itemType) const
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
