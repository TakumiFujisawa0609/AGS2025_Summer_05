#define NOMINMAX

#include "AlchemyManager.h"

#include <algorithm>

#include "ItemManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../DrawUI/Font.h"
#include "../Item/Product/RecoveryPotion.h"
#include "../Item/Product/AntidotePotion.h"
#include "../Item/Product/MagicPotion.h"
#include "../Item/Product/Garbage.h"


AlchemyManager* AlchemyManager::instance_ = nullptr;

void AlchemyManager::CreateInstance(void)
{
	if (!instance_)
	{
		instance_ = new AlchemyManager();
	}
}

AlchemyManager& AlchemyManager::GetInstance(void)
{
	return *instance_;
}

void AlchemyManager::Destroy(void)
{
	delete instance_;
	instance_ = nullptr;
}

AlchemyManager::AlchemyManager(void)
{
	currentPhase_ = 0;
	currentIndex_ = 0;
	currentAmount_ = 1;
	isOpen_ = false;
}

AlchemyManager::~AlchemyManager(void)
{

}

void AlchemyManager::Init(void)
{

	ResetSelection();

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"薬草", 2}, { "水", 1 }},
        std::make_shared<RecoveryPotion>()
    ); 

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"解毒草", 2}, { "水", 1 }},
        std::make_shared<AntidotePotion>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"魔力草", 2}, { "水", 1 }},
        std::make_shared<MagicPotion>()
    );

}

void AlchemyManager::Open(void)
{
	isOpen_ = true;
	ResetSelection();
}

void AlchemyManager::Close(void)
{
	isOpen_ = false;
	ResetSelection();
}

bool AlchemyManager::IsOpen(void) const
{
	return isOpen_;
}

void AlchemyManager::Update()
{
    if (!isOpen_) return;

    auto& input = InputManager::GetInstance();
    auto& itemManager = ItemManager::GetInstance();

    if (input.IsTrgDown(KEY_INPUT_X))
    {
        Close();
        return;
    }

    int materialCount = itemManager.GetMaterialItemCount();
    if (materialCount == 0)
    {
        currentIndex_ = -1;
        return;
    }

    // インデックスの範囲補正
    if (currentIndex_ < 0) currentIndex_ = 0;
    if (currentIndex_ >= materialCount) currentIndex_ = materialCount - 1;

    int row = currentIndex_ / MAX_COLUMNS;
    int col = currentIndex_ % MAX_COLUMNS;
    int maxRow = (materialCount - 1) / MAX_COLUMNS;

    if (currentPhase_ == 0)
    {
        // --- 上移動 ---
        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            int newRow = row - 1;
            if (newRow < 0)
                newRow = maxRow; // 端から上なら一番下に飛ぶ（ループさせたいなら）
            int newIndex = newRow * MAX_COLUMNS + col;
            if (newIndex >= materialCount) // 範囲外なら最後のアイテムへ
                newIndex = materialCount - 1;
            currentIndex_ = newIndex;
        }

        // --- 下移動 ---
        if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            int newRow = row + 1;
            if (newRow > maxRow)
                newRow = 0; // 一番上に戻る
            int newIndex = newRow * MAX_COLUMNS + col;
            if (newIndex >= materialCount)
                newIndex = materialCount - 1;
            currentIndex_ = newIndex;
        }

        // --- 左移動 ---
        if (input.IsTrgDown(KEY_INPUT_LEFT))
        {
            int newCol = col - 1;
            if (newCol < 0)
            {
                // 左端から左に行くなら前の行の最後の列へ
                int newRow = row - 1;
                if (newRow < 0) newRow = maxRow;
                newCol = MAX_COLUMNS - 1;
                int newIndex = newRow * MAX_COLUMNS + newCol;
                if (newIndex >= materialCount) newIndex = materialCount - 1;
                currentIndex_ = newIndex;
            }
            else
            {
                currentIndex_ = row * MAX_COLUMNS + newCol;
            }
        }

        // --- 右移動 ---
        if (input.IsTrgDown(KEY_INPUT_RIGHT))
        {
            int newCol = col + 1;
            if (newCol >= MAX_COLUMNS)
            {
                // 右端から右に行くなら次の行の一番左へ
                int newRow = row + 1;
                if (newRow > maxRow) newRow = 0;
                currentIndex_ = newRow * MAX_COLUMNS;
            }
            else
            {
                int newIndex = row * MAX_COLUMNS + newCol;
                if (newIndex >= materialCount)
                    newIndex = 0;
                currentIndex_ = newIndex;
            }
        }

        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            auto material = itemManager.GetMaterialItem(currentIndex_);
            if (material && material->GetQuantity() > 0 && selectedMaterials_.size() < 3)
            {
                selectedMaterialIndex_ = currentIndex_;
                currentPhase_ = 1;
                currentAmount_ = 1;
            }
        }

        if (input.IsTrgDown(KEY_INPUT_SPACE) && selectedMaterials_.size() >= 2)
        {
            ExecuteAlchemy();
        }
    }
    else if (currentPhase_ == 1)
    {
        auto material = itemManager.GetMaterialItem(selectedMaterialIndex_);
        if (!material) return;

        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            currentAmount_ = std::min(currentAmount_ + 1, material->GetQuantity());
        }
        if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            currentAmount_ = std::max(1, currentAmount_ - 1);
        }
        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            selectedMaterials_.push_back({ material, currentAmount_ });
            currentPhase_ = 0;
        }
    }
}

void AlchemyManager::Draw(void)
{
    if (!isOpen_) return;

    auto& font = Font::GetInstance();
    auto& itemManager = ItemManager::GetInstance();

    // 錬金メニュータイトル
    font.DrawDefaultText(10, 10, "錬金メニュー", 0xffffff);

    // 錬金メニューの素材リストを InventoryUI風に描画
    const int startX = 50;
    const int startY = 50;
    const int iconSize = 48;  // アイコンの大きさ（例）
    const int padding = 8;    // アイコン間の余白
    const int maxColumns = 5; // 1行あたりのアイテム数

    int itemCount = itemManager.GetMaterialItemCount();

    // アイテム取得用関数（素材アイテム固定）
    auto getItemFunc = [&](int i) -> std::shared_ptr<ItemBase> {
        return itemManager.GetMaterialItem(i);
        };

    // アイテム一覧描画
    for (int i = 0; i < itemCount; ++i)
    {
        auto item = getItemFunc(i);
        if (!item) continue;

        int row = i / maxColumns;
        int col = i % maxColumns;

        int x = startX + col * (iconSize + padding);
        int y = startY + row * (iconSize + padding + 20);  // 20はテキストの分の余白

        // アイテム画像描画（透過有効）
        DrawGraph(x, y, item->GetImageHandle(), true);

        // アイテム名描画
        font.DrawDefaultText(x, y + iconSize + 2, item->GetName().c_str(), 0xffffff, 12);

        // 所持数描画
        std::string quantityStr = "x" + std::to_string(item->GetQuantity());
        font.DrawDefaultText(x, y + iconSize + 18, quantityStr.c_str(), GetColor(200, 200, 200), 12);

        // 選択中アイテムに黄色枠
        if (i == currentIndex_ && currentPhase_ == 0)  // 素材選択中のみ枠
        {
            const int border = 3;
            int colYellow = GetColor(255, 255, 0);
            DrawBox(x - border, y - border, x + iconSize + border, y + iconSize + border, colYellow, false);
        }
    }

    // 使用数選択フェーズの表示
    if (currentPhase_ == 1)
    {
        auto item = itemManager.GetMaterialItem(selectedMaterialIndex_);
        if (item)
        {
            std::string text = item->GetName() + " 使用数： " + std::to_string(currentAmount_);
            font.DrawDefaultText(startX, startY + 200, text.c_str(), 0xffffff, 18);
        }
    }

    // 右側に選択中素材リスト（右寄せ）
    const int screenWidth = 640;
    const int rightX = screenWidth - 200;
    const int offsetY = 50;

    font.DrawDefaultText(rightX, offsetY, "選択中の素材：", 0xffffff);

    for (size_t i = 0; i < selectedMaterials_.size(); ++i)
    {
        std::string line = selectedMaterials_[i].item->GetName() + " x" + std::to_string(selectedMaterials_[i].amount);
        font.DrawDefaultText(rightX + 10, offsetY + 20 + (int)(i * 20), line.c_str(), 0xffffff);
    }

    // 補助説明
    font.DrawDefaultText(startX, offsetY + 250, "２つ以上の素材を選択で錬金実行", 0xffffff);

    // 錬金結果メッセージがあれば画面下に表示
    if (resultMessageTimer_ > 0)
    {
        font.DrawDefaultText(startX, 350, resultMessage_.c_str(), 0xffaa00);
    }
}

void AlchemyManager::ExecuteAlchemy()
{
    std::map<std::string, int> selectedMap;
    for (const auto& m : selectedMaterials_)
    {
        selectedMap[m.item->GetName()] += m.amount;
    }

    for (const auto& recipe : recipes_)
    {
        if (recipe.Match(selectedMap))
        {
            auto item = ItemManager::GetInstance().FindItemById(recipe.GetResult()->GetId());
            ItemManager::GetInstance().AddQuantity(item, 1);

            for (const auto& m : selectedMaterials_)
            {
                ItemManager::GetInstance().SubtractQuantity(m.item, m.amount);
            }

            selectedMaterials_.clear();

            // ★ メッセージ設定（成功）
            resultMessage_ = item->GetName() + " を作成しました！";
            resultMessageTimer_ = 180; // 3秒間表示（60fps想定）

            return;
        }
    }

    // 合致しなかった場合：ゴミアイテム付与
    auto garbage = ItemManager::GetInstance().FindItemById("Garbage");
    ItemManager::GetInstance().AddQuantity(garbage, 1);

    for (const auto& m : selectedMaterials_)
    {
        ItemManager::GetInstance().SubtractQuantity(m.item, m.amount);
    }

    selectedMaterials_.clear();

    // ★ メッセージ設定（失敗）
    resultMessage_ = "錬金に失敗し、ゴミができました…";
    resultMessageTimer_ = 180;
}


void AlchemyManager::ResetSelection(void)
{
    selectedMaterials_.clear();
    currentIndex_ = 0;
    currentAmount_ = 1; // 初期値1の方が自然
    currentPhase_ = 0;
    selectedMaterialIndex_ = 0;
    resultMessage_.clear();
    resultMessageTimer_ = 0;
}
