#define NOMINMAX

#include "AlchemyManager.h"

#include <algorithm>

#include "../../Manager/Decoration/EffectManager.h"
#include "ItemManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/Font.h"
#include "../Item/Product/RecoveryPotion.h"
#include "../Item/Product/AntidotePotion.h"
#include "../Item/Product/MagicPotion.h"
#include "../Item/Product/AntiParalysisPotion.h"
#include "../Item/Product/Speed​​Potion.h"
#include "../Item/Product/PowerPotion.h"
#include "../Item/Product/DefensePotion.h"
#include "../Item/Product/FireSword.h"
#include "../Item/Product/WaterSword.h"
#include "../Item/Product/WindSword.h"
#include "../Item/Product/EarthSword.h"
#include "../Item/Product/IceSword.h"
#include "../Item/Product/LightSword.h"
#include "../Item/Product/DarkSword.h"
#include "../Item/Product/FireWand.h"
#include "../Item/Product/WaterWand.h"
#include "../Item/Product/WindWand.h"
#include "../Item/Product/EarthWand.h"
#include "../Item/Product/IceWand.h"
#include "../Item/Product/LightWand.h"
#include "../Item/Product/DarkWand.h"
#include "../Item/Product/Garbage.h"
#include "../Item/Material/Sword.h"
#include "../Item/Material/Wand.h"
#include "../../Application.h"
#include "../PlayerStop.h"


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
    selectedMaterialEditIndex_ = 0;
    selectedMaterialIndex_ = 0;
    resultMessageTimer_ = 0;
	isOpen_ = false;
    start_ = false;
    waitingForSEFinish_ = false;
    effectPlayedDuringAlchemy_ = false;
    alchemyResult_ = ALCHEMYRESULT::NONE;
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

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"麻痺草", 2}, { "水", 1 }},
        std::make_shared<AntiParalysisPotion>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"風走草", 2}, { "水", 1 }},
        std::make_shared<Speed​​Potion>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"鬼力草", 2}, { "水", 1 }},
        std::make_shared<PowerPotion>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"硬体草", 2}, { "水", 1 }},
        std::make_shared<DefensePotion>()
    );
    
    recipes_.emplace_back
    (
        std::map < std::string, int>{{"鉄鉱石", 3}, { "水", 1 }},
        std::make_shared<Sword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"鉄鉱石", 2}, { "水", 1 }},
        std::make_shared<Wand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"火の魔石", 2}, { "剣", 1 }},
        std::make_shared<FireSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"水の魔石", 2}, { "剣", 1 }},
        std::make_shared<WaterSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"風の魔石", 2}, { "剣", 1 }},
        std::make_shared<WindSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"土の魔石", 2}, { "剣", 1 }},
        std::make_shared<EarthSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"氷の魔石", 2}, { "剣", 1 }},
        std::make_shared<IceSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"光の魔石", 2}, { "剣", 1 }},
        std::make_shared<LightSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"闇の魔石", 2}, { "剣", 1 }},
        std::make_shared<DarkSword>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"火の魔石", 2}, { "杖", 1 }},
        std::make_shared<FireWand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"水の魔石", 2}, { "杖", 1 }},
        std::make_shared<WaterWand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"風の魔石", 2}, { "杖", 1 }},
        std::make_shared<WindWand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"土の魔石", 2}, { "杖", 1 }},
        std::make_shared<EarthWand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"氷の魔石", 2}, { "杖", 1 }},
        std::make_shared<IceWand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"光の魔石", 2}, { "杖", 1 }},
        std::make_shared<LightWand>()
    );

    recipes_.emplace_back
    (
        std::map < std::string, int>{{"闇の魔石", 2}, { "杖", 1 }},
        std::make_shared<DarkWand>()
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
    start_ = false;
	ResetSelection();
}

bool AlchemyManager::IsOpen(void) const
{
	return isOpen_;
}

// 改善されたShowRecipeDifferenceMessage関数
void AlchemyManager::ShowRecipeDifferenceMessage(const std::map<std::string, int>& selectedMap)
{
    std::string message = "錬金失敗\n";

    // 最も近いレシピを見つける
    const AlchemyRecipe* closestRecipe = FindClosestRecipe(selectedMap);

    if (closestRecipe != nullptr)
    {
        message += "不足している素材:\n";

        bool hasMissing = false;
        for (const auto& [reqName, reqAmount] : closestRecipe->GetMaterials())
        {
            int selectedAmount = selectedMap.count(reqName) ? selectedMap.at(reqName) : 0;
            if (selectedAmount < reqAmount)
            {
                int shortage = reqAmount - selectedAmount;
                message += "- " + reqName + " あと" + std::to_string(shortage) + "個\n";
                hasMissing = true;
            }
        }

        if (!hasMissing)
        {
            message = "錬金失敗\n素材の組み合わせが正しくありません";
        }
    }
    else
    {
        message = "錬金失敗\n該当するレシピが見つかりません";
    }

    resultMessage_ = message;
    resultMessageTimer_ = 240; // 4秒表示
}

// 最も近いレシピを見つける関数
const AlchemyRecipe* AlchemyManager::FindClosestRecipe(const std::map<std::string, int>& selectedMap)
{
    const AlchemyRecipe* bestMatch = nullptr;
    int bestScore = -1;

    for (const auto& recipe : recipes_)
    {
        int score = 0;

        // 選択した素材がレシピに含まれている数をカウント
        for (const auto& [selName, selAmount] : selectedMap)
        {
            if (recipe.GetMaterials().count(selName) > 0)
            {
                score++;
            }
        }

        // より多くの素材が一致するレシピを優先
        if (score > bestScore && score > 0)
        {
            bestScore = score;
            bestMatch = &recipe;
        }
    }

    return bestMatch;
}
void AlchemyManager::Update()
{
    if (!isOpen_) return;

    auto& input = InputManager::GetInstance();
    auto& itemManager = ItemManager::GetInstance();
    auto& sound = SoundManager::GetInstance();

    PlayerStop::GetInstance().StopMovement();

    // SEが鳴り終わるまで待つ処理
    if (waitingForSEFinish_)
    {
        if (sound.IsPlaying(SoundManager::SOUND::SE_ALCHEMY))
        {
            if (!effectPlayedDuringAlchemy_)
            {
                EffectManager::GetInstance().Play(EffectManager::EFFECT::EFFECT_ALCHENY, { 0.0f, 70.0f, -50.0f }, { 0.0f, 0.0f, 0.0f,1.0f }, 15.0f, SoundManager::SOUND::NONE);

                effectPlayedDuringAlchemy_ = true;
            }
           
            return; // 錬金SEが再生中 → まだ待つ
        }
        else
        {
            effectPlayedDuringAlchemy_ = false;
            // 錬金SEが終わった → 結果SEを再生
            if (alchemyResult_ == ALCHEMYRESULT::SUCCESS)
            {
                sound.Play(SoundManager::SOUND::SE_ALCHEMY_SUCCESS);
            }
            else if (alchemyResult_ == ALCHEMYRESULT::FAILURE)
            {
               
            }
            

            // 結果のリセットと表示時間
            alchemyResult_ = ALCHEMYRESULT::NONE;
            waitingForSEFinish_ = false;
            resultMessageTimer_ = 180; // 3秒表示
            return;
        }
    }


    if (input.IsTrgDown(KEY_INPUT_ESCAPE))
    {
        sound.Play(SoundManager::SOUND::SE_CANCEL);
        Close();

        PlayerStop::GetInstance().ResumeMovement();
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

    if (currentPhase_ == 0) // 素材選択フェーズ
    {
        // --- 移動処理（変更なし） ---
        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            int newRow = row - 1;
            if (newRow < 0)
                newRow = maxRow;
            int newIndex = newRow * MAX_COLUMNS + col;
            if (newIndex >= materialCount)
                newIndex = materialCount - 1;
            currentIndex_ = newIndex;
        }

        if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            int newRow = row + 1;
            if (newRow > maxRow)
                newRow = 0;
            int newIndex = newRow * MAX_COLUMNS + col;
            if (newIndex >= materialCount)
                newIndex = materialCount - 1;
            currentIndex_ = newIndex;
        }

        if (input.IsTrgDown(KEY_INPUT_LEFT))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            int newCol = col - 1;
            if (newCol < 0)
            {
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

        if (input.IsTrgDown(KEY_INPUT_RIGHT))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            int newCol = col + 1;
            if (newCol >= MAX_COLUMNS)
            {
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

        // TABキーで選択済み素材の編集モードに切り替え
        if (input.IsTrgDown(KEY_INPUT_TAB) && !selectedMaterials_.empty())
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);
            currentPhase_ = 2;
            selectedMaterialEditIndex_ = 0;
            return;
        }

       

        if (input.IsTrgUp(KEY_INPUT_RETURN))
        {
            start_ = true;
        }

        if (start_)
        {
            if (input.IsTrgDown(KEY_INPUT_RETURN))
            {
                sound.Play(SoundManager::SOUND::SE_PUSH);
                auto material = itemManager.GetMaterialItem(currentIndex_);
                if (material && selectedMaterials_.size() < 3)
                {
                    // 選択済みの同じ素材の合計数を計算
                    int alreadySelectedAmount = 0;
                    for (const auto& selected : selectedMaterials_)
                    {
                        if (selected.item->GetName() == material->GetName())
                        {
                            alreadySelectedAmount += selected.amount;
                        }
                    }

                    // 利用可能な残り個数を計算
                    int availableAmount = material->GetQuantity() - alreadySelectedAmount;

                    if (availableAmount > 0)
                    {
                        selectedMaterialIndex_ = currentIndex_;
                        currentPhase_ = 1;
                        currentAmount_ = 1;
                    }
                }
            }
        }
     

        if (input.IsTrgDown(KEY_INPUT_SPACE) && selectedMaterials_.size() >= 2)
        {
            sound.Play(SoundManager::SOUND::SE_ALCHEMY);
            ExecuteAlchemy();
            waitingForSEFinish_ = true;
            return;
        }
    }
    else if (currentPhase_ == 1) // 個数選択フェーズ
    {
        auto material = itemManager.GetMaterialItem(selectedMaterialIndex_);
        if (!material) return;

        // 選択済みの同じ素材の合計数を計算
        int alreadySelectedAmount = 0;
        for (const auto& selected : selectedMaterials_)
        {
            if (selected.item->GetName() == material->GetName())
            {
                alreadySelectedAmount += selected.amount;
            }
        }

        // 利用可能な最大個数を計算
        int maxAvailable = material->GetQuantity() - alreadySelectedAmount;

        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::min(currentAmount_ + 1, maxAvailable);
        }
        if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::max(1, currentAmount_ - 1);
        }
        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);
            selectedMaterials_.push_back({ material, currentAmount_ });
            currentPhase_ = 0;
        }
        if (input.IsTrgDown(KEY_INPUT_ESCAPE))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            currentPhase_ = 0; // キャンセル
        }
    }
    else if (currentPhase_ == 2) // 選択済み素材編集フェーズ
    {
        int selectedCount = static_cast<int>(selectedMaterials_.size());

        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            selectedMaterialEditIndex_ = (selectedMaterialEditIndex_ - 1 + selectedCount) % selectedCount;
        }
        if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            selectedMaterialEditIndex_ = (selectedMaterialEditIndex_ + 1) % selectedCount;
        }

        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentPhase_ = 3;
            currentAmount_ = selectedMaterials_[selectedMaterialEditIndex_].amount;
        }

        if (input.IsTrgDown(KEY_INPUT_DELETE))
        {
            selectedMaterials_.erase(selectedMaterials_.begin() + selectedMaterialEditIndex_);
            if (selectedMaterials_.empty())
            {
                currentPhase_ = 0;
            }
            else if (selectedMaterialEditIndex_ >= static_cast<int>(selectedMaterials_.size()))
            {
                selectedMaterialEditIndex_ = static_cast<int>(selectedMaterials_.size()) - 1;
            }
        }

        if (input.IsTrgDown(KEY_INPUT_TAB))
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);
            currentPhase_ = 0;
        }
    }
    else if (currentPhase_ == 3) // 選択済み素材の個数変更フェーズ
    {
        auto material = selectedMaterials_[selectedMaterialEditIndex_].item;

        // 他の選択済み同名素材の合計数を計算（編集中のものは除く）
        int otherSelectedAmount = 0;
        for (size_t i = 0; i < selectedMaterials_.size(); ++i)
        {
            if (i != static_cast<size_t>(selectedMaterialEditIndex_) &&
                selectedMaterials_[i].item->GetName() == material->GetName())
            {
                otherSelectedAmount += selectedMaterials_[i].amount;
            }
        }

        // 利用可能な最大個数を計算
        int maxAvailable = material->GetQuantity() - otherSelectedAmount;

        if (input.IsTrgDown(KEY_INPUT_UP))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::min(currentAmount_ + 1, maxAvailable);
        }
        if (input.IsTrgDown(KEY_INPUT_DOWN))
        {
            sound.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::max(0, currentAmount_ - 1);
        }
        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            sound.Play(SoundManager::SOUND::SE_PUSH);
            if (currentAmount_ == 0)
            {
                selectedMaterials_.erase(selectedMaterials_.begin() + selectedMaterialEditIndex_);
                if (selectedMaterials_.empty())
                {
                    currentPhase_ = 0;
                }
                else
                {
                    if (selectedMaterialEditIndex_ >= static_cast<int>(selectedMaterials_.size()))
                    {
                        selectedMaterialEditIndex_ = static_cast<int>(selectedMaterials_.size()) - 1;
                    }
                    currentPhase_ = 2;
                }
            }
            else
            {
                selectedMaterials_[selectedMaterialEditIndex_].amount = currentAmount_;
                currentPhase_ = 2;
            }
        }
        if (input.IsTrgDown(KEY_INPUT_ESCAPE))
        {
            sound.Play(SoundManager::SOUND::SE_CANCEL);
            currentPhase_ = 2;
        }
    }
}

void AlchemyManager::Draw(void)
{
    if (!isOpen_) return;

    auto& font = Font::GetInstance();
    auto& itemManager = ItemManager::GetInstance();

    const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
    const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

    const int startX = 100;
    const int startY = 100;

    // --- タイトル ---
    font.DrawDefaultText(startX, startY - 30, "錬金メニュー", 0xffffff, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);

    const int iconSize = 64;
    const int padding = 50;
    const int maxColumns = 5;

    int itemCount = itemManager.GetMaterialItemCount();
    int rowCount = (itemCount + maxColumns - 1) / maxColumns;

    // 左側背景サイズ
    int leftWidth = maxColumns * (iconSize + padding) - padding;
    int leftHeight = rowCount * (iconSize + padding + 20);

    // 右側のX開始位置（右端の1/3から）
    const int rightX = screenWidth * 3 / 5;

    // 右側背景
    const int rightBgLeft = rightX - 20;
    const int rightBgTop = startY - 50;
    const int rightBgRight = rightBgLeft + leftWidth;
    const int rightBgBottom = rightBgTop + leftHeight + Application::DEFA_SCREEN_SZIE_Y / 2 - 50;

    // --- 背景描画 ---

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    // 左背景 黒
    const int leftBgLeft = startX - 20;
    const int leftBgTop = startY - 40;
    const int leftBgRight = startX + leftWidth + 40;
    const int leftBgBottom = startY + leftHeight + Application::DEFA_SCREEN_SZIE_Y / 2 -100;

    DrawBox(leftBgLeft, leftBgTop, leftBgRight, leftBgBottom, GetColor(0, 0, 0), TRUE);

    // 右背景 黒
    DrawBox(rightBgLeft, rightBgTop, rightBgRight, rightBgBottom, GetColor(0, 0, 0), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // --- 白い外枠 ---
    const int borderThickness = 3;
    const int white = GetColor(255, 255, 255);

    for (int i = 0; i < borderThickness; ++i)
    {
        // 左側外枠
        DrawBox(leftBgLeft - i, leftBgTop - i, leftBgRight + i, leftBgBottom + i, white, FALSE);

        // 右側外枠
        DrawBox(rightBgLeft - i, rightBgTop - i, rightBgRight + i, rightBgBottom + i, white, FALSE);
    }

    // --- 左側：素材一覧表示 ---

    auto getItemFunc = [&](int i) -> std::shared_ptr<ItemBase> {
        return itemManager.GetMaterialItem(i);
        };

   // --- 左側：素材一覧表示 ---
for (int i = 0; i < itemCount; ++i)
{
    auto item = getItemFunc(i);
    if (!item) continue;

    int row = i / maxColumns;
    int col = i % maxColumns;

    int x = startX + col * (iconSize + padding);
    int y = startY + row * (iconSize + padding + 20);

    // アイコン
    DrawGraph(x, y, item->GetImageHandle(), true);

    // 名前
    font.DrawDefaultText(x, y + iconSize + 2, item->GetName().c_str(),
                         0xffffff, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);

    // --- 残り個数（shop 風に xN 表示） ---
    int alreadySelectedAmount = 0;
    for (const auto& selected : selectedMaterials_)
    {
        if (selected.item->GetName() == item->GetName())
        {
            alreadySelectedAmount += selected.amount;
        }
    }
    int remainingQuantity = item->GetQuantity() - alreadySelectedAmount;

    std::string quantityStr = "x" + std::to_string(remainingQuantity);
    int quantityColor = (remainingQuantity > 0) ? GetColor(200, 200, 200)
                                                : GetColor(255, 100, 100);

    font.DrawDefaultText(x, y + iconSize + 24, quantityStr.c_str(),
                         quantityColor, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);

    // --- 数量選択フェーズ（Shopみたいに数字だけ変化させる） ---
    if (currentPhase_ == 1 && i == selectedMaterialIndex_)
    {
        std::string selectStr = "▶ x" + std::to_string(currentAmount_);
        font.DrawDefaultText(x, y + iconSize + 50, selectStr.c_str(),
                             GetColor(255, 255, 0), 28, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }

    // 選択枠
    if (i == currentIndex_ && currentPhase_ == 0)
    {
        const int border = 3;
        int colYellow = GetColor(255, 255, 0);
        DrawBox(x - border, y - border, x + iconSize + border, y + iconSize + border, colYellow, false);
    }
}


    // --- 使用数選択フェーズ ---
if (currentPhase_ == 1)
{
    auto item = itemManager.GetMaterialItem(selectedMaterialIndex_);
    if (item)
    {
        int alreadySelectedAmount = 0;
        for (const auto& selected : selectedMaterials_)
        {
            if (selected.item->GetName() == item->GetName())
            {
                alreadySelectedAmount += selected.amount;
            }
        }

        int availableAmount = item->GetQuantity() - alreadySelectedAmount;

        std::string text = item->GetName() + " 使用数： " + std::to_string(currentAmount_) +
            " (利用可能: " + std::to_string(availableAmount) + ")";

        // --- 位置を画面中央に調整 ---
        int textWidth = font.GetDefaultTextWidth(text.c_str());
        int centerX = (screenWidth - textWidth) / 2;
        int centerY = screenHeight / 2 + 100;   // 画面中央より少し下（+100px）

        font.DrawDefaultText(centerX, centerY, text.c_str(),
            0xffffff, 28, Font::FONT_TYPE_ANTIALIASING_EDGE);

        // 操作説明も中央に
        std::string help = "↑↓：個数変更 Enter：決定  Esc：キャンセル";
        int helpWidth = font.GetDefaultTextWidth(help.c_str());
        font.DrawDefaultText((screenWidth - helpWidth) / 2,
            centerY + 40, help.c_str(),
            GetColor(150, 150, 150), 22, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }
}


    // --- 個数編集フェーズ ---
    if (currentPhase_ == 3)
    {
        const int offsetY = 50;
        auto material = selectedMaterials_[selectedMaterialEditIndex_].item;

        std::string text = material->GetName() + " 個数変更： " + std::to_string(currentAmount_) + " (0で削除)";

        // 右側の文字表示位置を右背景の左端 + 20pxに合わせる
        int rightTextX = rightBgLeft + 150;

        font.DrawDefaultText(rightTextX, offsetY + static_cast<int>(selectedMaterials_.size() * 40), text.c_str(), GetColor(255, 200, 100), 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
        font.DrawDefaultText(rightTextX, offsetY + static_cast<int>(selectedMaterials_.size() * 40) + 30, "↑↓：個数変更 Enter：決定", GetColor(150, 150, 150), 20, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }

    // --- 右側：選択中素材リスト ---
    {
        const int offsetY = 50;
        int rightTextX = rightBgLeft + 20;

        font.DrawDefaultText(rightTextX, offsetY, "選択中の素材：", 0xffffff, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);

        for (size_t i = 0; i < selectedMaterials_.size(); ++i)
        {
            std::string line = selectedMaterials_[i].item->GetName() + " x" + std::to_string(selectedMaterials_[i].amount);
            int textColor = 0xffffff;

            if (currentPhase_ == 2 && i == static_cast<size_t>(selectedMaterialEditIndex_))
            {
                textColor = GetColor(255, 255, 0);

                int textWidth = font.GetDefaultTextWidth(line.c_str());
                DrawBox(rightTextX - 5, offsetY + 35 + static_cast<int>(i * 40),
                    rightTextX + 10 + textWidth, offsetY + 65 + static_cast<int>(i * 40),
                    GetColor(50, 50, 0), true);
            }

            font.DrawDefaultText(rightTextX, offsetY + 40 + static_cast<int>(i * 40), line.c_str(), textColor, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
        }

        int startTextY = offsetY + 60 + static_cast<int>(selectedMaterials_.size() * 40);

        if (selectedMaterials_.size() >= 2)
        {
            font.DrawDefaultText(rightTextX, startTextY, "Space: 錬金開始", GetColor(0, 255, 0), 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
        }
        else
        {
            font.DrawDefaultText(rightTextX, startTextY, "2種類以上の素材を選択して錬金開始", GetColor(255, 255, 255), 20, Font::FONT_TYPE_ANTIALIASING_EDGE);
        }
    }

    // --- フェーズ別操作説明 ---
    std::string helpText;
    switch (currentPhase_)
    {
    case 0:
        helpText = "Enter：選択 Tab：編集 Space：錬金実行 ESC：閉じる";
        break;
    case 1:
        helpText = "↑↓：個数変更 Enter：決定";
        break;
    case 2:
        helpText = "↑↓：素材選択 Enter：個数変更 Tab：戻る";
        break;
    case 3:
        helpText = "↑↓：個数変更 Enter：決定";
        break;
    }

    int helpTextWidth = font.GetDefaultTextWidth(helpText.c_str());
    font.DrawDefaultText((screenWidth - helpTextWidth) / 2 + 50, screenHeight - 60, helpText.c_str(), GetColor(255, 255, 255), 24, Font::FONT_TYPE_ANTIALIASING_EDGE);

    // --- 結果メッセージ（画面下） ---
    if (resultMessageTimer_ > 0)
    {
        int resultTextWidth = font.GetDefaultTextWidth(resultMessage_.c_str());
        font.DrawDefaultText((screenWidth - resultTextWidth) / 2, (screenHeight / 2) + maxColumns * 4, resultMessage_.c_str(), 0xffaa00, 24, Font::FONT_TYPE_ANTIALIASING_EDGE);
        resultMessageTimer_--;
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
        const auto& required = recipe.GetMaterials();

        bool perfectMatch = true;

        if (selectedMap.size() != required.size())
        {
            perfectMatch = false;
        }
        else
        {
            for (const auto& [reqName, reqAmount] : required)
            {
                if (selectedMap.count(reqName) == 0 || selectedMap.at(reqName) != reqAmount)
                {
                    perfectMatch = false;
                    break;
                }
            }
            if (perfectMatch)
            {
                for (const auto& [selName, selAmount] : selectedMap)
                {
                    if (required.count(selName) == 0)
                    {
                        perfectMatch = false;
                        break;
                    }
                }
            }
        }

        if (perfectMatch)
        {
            auto item = ItemManager::GetInstance().FindItemById(recipe.GetResult()->GetId());
            ItemManager::GetInstance().AddQuantity(item, 1);

            for (const auto& m : selectedMaterials_)
            {
                ItemManager::GetInstance().SubtractQuantity(m.item, m.amount);
            }

            alchemyResult_ = ALCHEMYRESULT::SUCCESS;

            selectedMaterials_.clear();

            resultMessage_ = item->GetName() + " を作成しました！";

            return;
        }
    }

    // 失敗時はゴミアイテムを付与
    auto garbage = ItemManager::GetInstance().FindItemById("Garbage");
    ItemManager::GetInstance().AddQuantity(garbage, 1);

    // 失敗でも素材は消費
    for (const auto& m : selectedMaterials_)
    {
        ItemManager::GetInstance().SubtractQuantity(m.item, m.amount);
    }

    alchemyResult_ = ALCHEMYRESULT::FAILURE;

    SoundManager::GetInstance().Play(SoundManager::SOUND::SE_ALCHEMY_FAIL);

    ShowRecipeDifferenceMessage(selectedMap);

    effectPlayedDuringAlchemy_ = true;
    EffectManager::GetInstance().Play(EffectManager::EFFECT::EFFECT_BLAST, { 0.0f, 70.0f, -50.0f }, { 0.0f, 0.0f, 0.0f,1.0f }, 50.0f, SoundManager::SOUND::NONE);

    selectedMaterials_.clear();
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
    selectedMaterialEditIndex_ = 0;
}
