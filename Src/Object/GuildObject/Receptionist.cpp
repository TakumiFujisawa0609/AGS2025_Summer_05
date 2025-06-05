#include "Receptionist.h"
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/Resource.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Utility/Utility.h"
#include "../Manager/CollisionManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"
#include "./../../DrawUI/SceneUI/QuestUI.h"
#include "../Manager/ItemManager.h"

Receptionist::Receptionist(void)
{
    trans_ = Transform();
    // 3Dモデルを右側に配置
    trans_.pos = VGet(150.0f, 0.0f, 0.0f);
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

    // アイテムIDを初期化
    itemIds_[static_cast<int>(ItemType::HEALTH_POTION)] = "RecoveryPotion";
    itemIds_[static_cast<int>(ItemType::ANTIDOTE_POTION)] = "AntidotePotion";
    itemIds_[static_cast<int>(ItemType::MAGIC_POTION)] = "MagicPotion";
}

Receptionist::~Receptionist(void)
{
}

void Receptionist::Init(void)
{
    auto& res = ResourceManager::GetInstance();
    // モデル（箱系のモデルを使用想定）
    trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BULLETIN_BOARD));
    trans_.quaRot = Quaternion();
    trans_.quaRotLocal = Quaternion::AngleAxis(Utility::Deg2RadF(0.0f), Utility::AXIS_Y);
    trans_.scl = SCALE;
    // 3Dモデルを右側に配置（X軸方向に移動）
    trans_.pos = VGet(150.0f, 0.0f, 0.0f);
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

    // アイテム名を初期化
    itemNames_[static_cast<int>(ItemType::HEALTH_POTION)] = "回復ポーション";
    itemNames_[static_cast<int>(ItemType::ANTIDOTE_POTION)] = "解毒ポーション";
    itemNames_[static_cast<int>(ItemType::MAGIC_POTION)] = "魔法ポーション";

    // アイテムIDを初期化
    itemIds_[static_cast<int>(ItemType::HEALTH_POTION)] = "RecoveryPotion";
    itemIds_[static_cast<int>(ItemType::ANTIDOTE_POTION)] = "AntidotePotion";
    itemIds_[static_cast<int>(ItemType::MAGIC_POTION)] = "MagicPotion";

    // モデル制御
    trans_.Update();
}

void Receptionist::Update(void)
{
    auto& input = InputManager::GetInstance();
    trans_.Update();

    // 納品完了メッセージタイマー更新
    if (deliveryMessageTimer_ > 0)
    {
        deliveryMessageTimer_--;
    }

    if (!isShowUI_) return;

    // エンターキーが押された時の処理
    if (input.IsTrgDown(KEY_INPUT_RETURN))
    {
        if (!isShowDeliveryMenu_)
        {
            // 納品メニューを表示
            isShowDeliveryMenu_ = true;
            selectedItem_ = 0;
            isSelectingQuantity_ = false;
            selectedQuantity_ = 1;
        }
        else if (!isSelectingQuantity_)
        {
            // アイテムが選択された場合、数量選択に移行
            if (GetMaxDeliveryQuantity() > 0)
            {
                isSelectingQuantity_ = true;
                selectedQuantity_ = 1;
            }
        }
        else
        {
            // 数量が決定された場合、納品実行
            ItemType itemType = static_cast<ItemType>(selectedItem_);
            if (DeliverItem(itemType, selectedQuantity_))
            {
                // 納品成功
                lastDeliveryMessage_ = GetItemName(itemType) + std::string(" x") + std::to_string(selectedQuantity_) + std::string(" を納品しました！");
                deliveryMessageTimer_ = 120; // 2秒間表示

                // メニューを閉じる
                isShowDeliveryMenu_ = false;
                isSelectingQuantity_ = false;
            }
        }
    }

    // 納品メニュー表示中の処理
    if (isShowDeliveryMenu_)
    {
        if (!isSelectingQuantity_)
        {
            // アイテム選択中
            if (input.IsTrgDown(KEY_INPUT_UP))
            {
                selectedItem_ = (selectedItem_ - 1 + static_cast<int>(ItemType::ITEM_COUNT)) % static_cast<int>(ItemType::ITEM_COUNT);
            }
            else if (input.IsTrgDown(KEY_INPUT_DOWN))
            {
                selectedItem_ = (selectedItem_ + 1) % static_cast<int>(ItemType::ITEM_COUNT);
            }
        }
        else
        {
            // 数量選択中
            int maxQuantity = GetMaxDeliveryQuantity();
            if (maxQuantity > 0)
            {
                if (input.IsTrgDown(KEY_INPUT_UP))
                {
                    selectedQuantity_ = min(selectedQuantity_ + 1, maxQuantity);
                }
                else if (input.IsTrgDown(KEY_INPUT_DOWN))
                {
                    selectedQuantity_ = max(selectedQuantity_ - 1, 1);
                }
            }
        }

        // ESCキー（またはXキー）で戻る/閉じる
        if (input.IsTrgDown(KEY_INPUT_ESCAPE) || input.IsTrgDown(KEY_INPUT_X))
        {
            if (isSelectingQuantity_)
            {
                isSelectingQuantity_ = false;
            }
            else
            {
                isShowDeliveryMenu_ = false;
            }
        }
    }
}

void Receptionist::Draw(void)
{
    MV1DrawModel(trans_.modelId);

#ifdef _DEBUG
    const int screenWidth = Application::SCREEN_SIZE_X;
    const int screenHeight = Application::SCREEN_SIZE_Y;
#else
    const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
    const int screenHeight = Application::DEFA_SCREEN_SIZE_X;
#endif // _DEBUG

    if (isShowUI_)
    {
        if (!isShowDeliveryMenu_)
        {
            const char* text = "納品";
            int fontSize = 14;
            int textWidth = GetDrawStringWidth(text, strlen(text), -1);
            int boxWidth = textWidth + 30;  // 余白
            int boxHeight = 20;

            int boxX = (screenWidth - boxWidth) / 2;
            int boxY = (screenHeight / 4) + boxHeight;

            DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
            DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);
            Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 5, text, 0xffffff, fontSize);
        }
        else
        {
            const int boxWidth = 600;
            const int boxHeight = 300;
            const int boxX = (screenWidth - boxWidth) / 2;
            const int boxY = 150;

            DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
            DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);

            if (!isSelectingQuantity_)
            {
                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 20, "===== 納品メニュー =====", 0xffffff, 24);
                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 50, "納品するアイテムを選択してください", 0xcccccc, 18);

                for (int i = 0; i < static_cast<int>(ItemType::ITEM_COUNT); i++)
                {
                    int color = (i == selectedItem_) ? 0xff00ff : 0xffffff;
                    int yPos = boxY + 80 + (i * 30);

                    if (i == selectedItem_)
                    {
                        Font::GetInstance().DrawDefaultText(boxX + 20, yPos, "→", 0xff00ff, 24);
                    }

                    int itemCount = GetItemCount(static_cast<ItemType>(i));
                    std::string itemInfo = itemNames_[i] + " (所持数: " + std::to_string(itemCount) + ")";
                    Font::GetInstance().DrawDefaultText(boxX + 50, yPos, itemInfo.c_str(), color, 20);
                }

                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 260, "↑↓キー: 選択  Enter: 決定  X: 戻る", 0xcccccc, 16);
            }
            else
            {
                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 20, "===== 納品数量選択 =====", 0xffffff, 24);
                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 60, ("アイテム: " + itemNames_[selectedItem_]).c_str(), 0xffffff, 18);

                int itemCount = GetItemCount(static_cast<ItemType>(selectedItem_));
                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 90, ("所持数: " + std::to_string(itemCount)).c_str(), 0xffffff, 18);

                std::string quantityText = "納品数量: " + std::to_string(selectedQuantity_);
                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 140, quantityText.c_str(), 0xff00ff, 24);

                Font::GetInstance().DrawDefaultText(boxX + 20, boxY + 260, "↑↓キー: 数量変更  Enter: 納品実行  X: 戻る", 0xcccccc, 16);
            }
        }
    }

    if (deliveryMessageTimer_ > 0)
    {
        const int msgBoxWidth = 640;
        const int msgBoxHeight = 40;
        const int msgBoxX = (screenWidth - msgBoxWidth) / 2;
        const int msgBoxY = 100;

        DrawBox(msgBoxX, msgBoxY, msgBoxX + msgBoxWidth, msgBoxY + msgBoxHeight, GetColor(0, 150, 0), TRUE);
        DrawBox(msgBoxX, msgBoxY, msgBoxX + msgBoxWidth, msgBoxY + msgBoxHeight, GetColor(255, 255, 255), FALSE);
        Font::GetInstance().DrawDefaultText(msgBoxX + 20, msgBoxY + 10, lastDeliveryMessage_.c_str(), 0xffffff, 20);
    }
}


void Receptionist::Release(void)
{
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
    isShowUI_ = true;
    isShowDeliveryMenu_ = false;
    isSelectingQuantity_ = false;
}

void Receptionist::HideUI(void)
{
    isShowUI_ = false;
    isShowDeliveryMenu_ = false;
    isSelectingQuantity_ = false;
}

bool Receptionist::IsValid(void) const
{
    return true;
}

bool Receptionist::DeliverItem(ItemType itemType, int quantity)
{
    auto& itemManager = ItemManager::GetInstance();
    std::string itemId = GetItemId(itemType);

    // --- 依頼との照合を追加 ---
    auto& questUI = QuestUI::GetInstance();

    bool matchedQuestFound = false;
    int questId = -1;

    // アクティブな依頼の中から一致するアイテムIDを探す
    for (int i = 0; i < 3; ++i) // 仮に3つの依頼までと仮定（可変なら修正）
    {
        if (questUI.IsQuestActive(i))
        {
            const auto& quests = questUI; // 直接アクセスできないならQuestUIにgetterを追加する
            if (questUI.IsQuestCompleted(i)) continue;

            // アイテムID一致確認（内部的に一つだけアクティブな仕様前提）
            const auto& quest = questUI; // QuestUI側に GetActiveQuest() を追加するのが理想
            // ここではQuestUIに helper 関数がないので仮実装とします（後述）
        }
    }

    // 照合関数がないと無理なので、QuestUI側に次を追加：
    DeliveryQuest* activeQuest = questUI.GetActiveQuest(); // ←追加関数
    if (!activeQuest || activeQuest->targetItemId != itemId)
    {
        lastDeliveryMessage_ = "このアイテムは依頼対象ではありません！";
        deliveryMessageTimer_ = 120;
        return false;
    }

    // --- 所持アイテムチェック ---
    auto item = itemManager.FindItemById(itemId);
    if (!item || item->GetQuantity() < quantity)
    {
        return false;
    }

    // --- アイテム納品処理 ---
    itemManager.SubtractQuantity(item, quantity);

    // --- 進行数加算・更新 ---
    activeQuest->currentAmount += quantity;
    activeQuest->isCompleted = (activeQuest->currentAmount >= activeQuest->requiredAmount);

    lastDeliveryMessage_ = std::string(GetItemName(itemType)) + " x" + std::to_string(quantity) + " を納品しました！";
    deliveryMessageTimer_ = 120;

    // --- 依頼完了処理 ---
    if (activeQuest->isCompleted)
    {
        questUI.CompleteQuest(activeQuest->id);

        // 次の依頼を自動受注
        if (questUI.CanAcceptNewQuest())
        {
            questUI.AcceptQuest(activeQuest->id + 1); // 次の依頼ID（仮）
        }
    }

    return true;
}

void Receptionist::SetItemCount(ItemType itemType, int count)
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

int Receptionist::GetItemCount(ItemType itemType) const
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
    return GetItemCount(static_cast<ItemType>(selectedItem_));
}

const char* Receptionist::GetItemName(ItemType itemType) const
{
    int itemIndex = static_cast<int>(itemType);
    if (itemIndex >= 0 && itemIndex < static_cast<int>(ItemType::ITEM_COUNT))
    {
        return itemNames_[itemIndex].c_str();
    }
    return "不明なアイテム";
}

std::string Receptionist::GetItemId(ItemType itemType) const
{
    int itemIndex = static_cast<int>(itemType);
    if (itemIndex >= 0 && itemIndex < static_cast<int>(ItemType::ITEM_COUNT))
    {
        return itemIds_[itemIndex];
    }
    return "";
}