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
    if (instance_ == nullptr)
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
    const int INITIAL_PHASE = 0;                        // 初期フェーズ番号
    const int INITIAL_INDEX = 0;                        // カーソルの初期インデックス
    const int INITIAL_AMOUNT = 1;                       // 初期の選択個数
    const int INITIAL_TIMER = 0;                        // タイマーの初期値

    currentPhase_ = INITIAL_PHASE;
    currentIndex_ = INITIAL_INDEX;
    currentAmount_ = INITIAL_AMOUNT;
    selectedMaterialEditIndex_ = INITIAL_INDEX;
    selectedMaterialIndex_ = INITIAL_INDEX;
    resultMessageTimer_ = INITIAL_TIMER;
    isOpen_ = false;
    start_ = false;
    waitingForSEFinish_ = false;
    effectPlayedDuringAlchemy_ = false;
    alchemyResult_ = ALCHEMY_RESULT::NONE;
}

AlchemyManager::~AlchemyManager(void)
{
}

void AlchemyManager::Init(void)
{
    ResetSelection();

    const int REQUIRED_HERB_AMOUNT = 2;                 // 薬草類の必要個数
    const int REQUIRED_WATER_AMOUNT = 1;                // 水の必要個数
    const int REQUIRED_ORE_SWORD_AMOUNT = 3;            // 剣作成時の鉄鉱石必要個数
    const int REQUIRED_ORE_WAND_AMOUNT = 2;             // 杖作成時の鉄鉱石必要個数
    const int REQUIRED_STONE_AMOUNT = 2;                // 魔石の必要個数
    const int REQUIRED_BASE_WEAPON_AMOUNT = 1;          // ベース武器の必要個数

    recipes_.emplace_back(
        std::map<std::string, int>{{"薬草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<RecoveryPotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"解毒草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<AntidotePotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"魔力草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<MagicPotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"麻痺草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<AntiParalysisPotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"風走草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<SpeedPotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"鬼力草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<PowerPotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"硬体草", REQUIRED_HERB_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<DefensePotion>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"鉄鉱石", REQUIRED_ORE_SWORD_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<Sword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"鉄鉱石", REQUIRED_ORE_WAND_AMOUNT}, { "水", REQUIRED_WATER_AMOUNT }},
        std::make_shared<Wand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"火の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<FireSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"水の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<WaterSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"風の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<WindSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"土の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<EarthSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"氷の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<IceSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"光の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<LightSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"闇の魔石", REQUIRED_STONE_AMOUNT}, { "剣", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<DarkSword>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"火の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<FireWand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"水の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<WaterWand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"風の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<WindWand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"土の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<EarthWand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"氷の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<IceWand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"光の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
        std::make_shared<LightWand>()
    );

    recipes_.emplace_back(
        std::map<std::string, int>{{"闇の魔石", REQUIRED_STONE_AMOUNT}, { "杖", REQUIRED_BASE_WEAPON_AMOUNT }},
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

void AlchemyManager::ShowRecipeDifferenceMessage(const std::map<std::string, int>& selectedMap)
{
    const int EMPTY_COUNT = 0;                          // 空の個数
    const int MESSAGE_TIMER_LONG = 240;                 // 差分メッセージ表示時間（フレーム）

    std::string message = "錬金失敗\n";

    const AlchemyRecipe* closestRecipe = FindClosestRecipe(selectedMap);

    if (closestRecipe != nullptr)
    {
        message += "不足している素材:\n";

        bool hasMissing = false;

        for (const auto& [requiredName, requiredAmount] : closestRecipe->GetMaterials())
        {
            int selectedAmount = selectedMap.count(requiredName) ? selectedMap.at(requiredName) : EMPTY_COUNT;

            if (selectedAmount < requiredAmount)
            {
                int shortage = requiredAmount - selectedAmount;
                message += "- " + requiredName + " あと" + std::to_string(shortage) + "個\n";
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
    resultMessageTimer_ = MESSAGE_TIMER_LONG;
}

const AlchemyRecipe* AlchemyManager::FindClosestRecipe(const std::map<std::string, int>& selectedMap)
{
    const int EMPTY_COUNT = 0;                          // 空の個数
    const int INITIAL_SCORE = -1;                       // スコアの初期値

    const AlchemyRecipe* bestMatch = nullptr;
    int bestScore = INITIAL_SCORE;

    for (const auto& recipe : recipes_)
    {
        int score = EMPTY_COUNT;

        for (const auto& [selectedName, selectedAmount] : selectedMap)
        {
            if (recipe.GetMaterials().count(selectedName) > EMPTY_COUNT)
            {
                score++;
            }
        }

        if (score > bestScore && score > EMPTY_COUNT)
        {
            bestScore = score;
            bestMatch = &recipe;
        }
    }

    return bestMatch;
}

void AlchemyManager::Update(void)
{
    if (!isOpen_)
    {
        return;
    }

    const int INITIAL_INDEX = 0;                        // カーソルの初期インデックス
    const int INITIAL_AMOUNT = 1;                       // 初期の選択個数
    const int EMPTY_COUNT = 0;                          // 空の個数
    const int INVALID_INDEX = -1;                       // 無効なインデックス
    const int SINGLE_COUNT = 1;                         // 単一の個数
    const int PHASE_SELECT_MATERIAL = 0;                // 素材選択フェーズ
    const int PHASE_SELECT_AMOUNT = 1;                  // 個数選択フェーズ
    const int PHASE_EDIT_MATERIAL_LIST = 2;             // 選択済み素材編集フェーズ
    const int PHASE_EDIT_AMOUNT = 3;                    // 選択済み素材の個数変更フェーズ
    const int MAX_SELECTION_MATERIAL_TYPES = 3;         // 選択可能な素材種類の最大数
    const int MIN_SELECTION_TO_START_ALCHEMY = 2;       // 錬金開始に必要な最小素材種類数
    const int MESSAGE_TIMER_SHORT = 180;                // 結果SE待機後の表示時間（フレーム）
    const float EFFECT_POS_X = 0.0f;                    // エフェクトのX座標
    const float EFFECT_POS_Y = 70.0f;                   // エフェクトのY座標
    const float EFFECT_POS_Z = -50.0f;                  // エフェクトのZ座標
    const float EFFECT_ROTATION_W = 1.0f;               // エフェクト回転クォータニオンW成分
    const float EFFECT_SCALE_ALCHEMY = 15.0f;           // 錬金エフェクトのスケール

    auto& inputManager = InputManager::GetInstance();
    auto& itemManager = ItemManager::GetInstance();
    auto& soundManager = SoundManager::GetInstance();

    PlayerStop::GetInstance().StopMovement();

    if (waitingForSEFinish_)
    {
        if (soundManager.IsPlaying(SoundManager::SOUND::SE_ALCHEMY))
        {
            if (!effectPlayedDuringAlchemy_)
            {
                EffectManager::GetInstance().Play(
                    EffectManager::EFFECT::EFFECT_ALCHEMY,
                    { EFFECT_POS_X, EFFECT_POS_Y, EFFECT_POS_Z },
                    { 0.0f, 0.0f, 0.0f, EFFECT_ROTATION_W },
                    EFFECT_SCALE_ALCHEMY,
                    SoundManager::SOUND::NONE
                );

                effectPlayedDuringAlchemy_ = true;
            }

            return;
        }
        else
        {
            effectPlayedDuringAlchemy_ = false;

            if (alchemyResult_ == ALCHEMY_RESULT::SUCCESS)
            {
                soundManager.Play(SoundManager::SOUND::SE_ALCHEMY_SUCCESS);
            }
            else if (alchemyResult_ == ALCHEMY_RESULT::FAILURE)
            {
            }

            alchemyResult_ = ALCHEMY_RESULT::NONE;
            waitingForSEFinish_ = false;
            resultMessageTimer_ = MESSAGE_TIMER_SHORT;
            return;
        }
    }

    if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
    {
        soundManager.Play(SoundManager::SOUND::SE_CANCEL);
        Close();

        PlayerStop::GetInstance().ResumeMovement();
        return;
    }

    int materialCount = itemManager.GetMaterialItemCount();

    if (materialCount == EMPTY_COUNT)
    {
        currentIndex_ = INVALID_INDEX;
        return;
    }

    if (currentIndex_ < INITIAL_INDEX)
    {
        currentIndex_ = INITIAL_INDEX;
    }

    if (currentIndex_ >= materialCount)
    {
        currentIndex_ = materialCount - SINGLE_COUNT;
    }

    int row = currentIndex_ / MAX_COLUMNS;
    int col = currentIndex_ % MAX_COLUMNS;
    int maxRow = (materialCount - SINGLE_COUNT) / MAX_COLUMNS;

    if (currentPhase_ == PHASE_SELECT_MATERIAL)
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            int newRow = row - SINGLE_COUNT;

            if (newRow < INITIAL_INDEX)
            {
                newRow = maxRow;
            }

            int newIndex = newRow * MAX_COLUMNS + col;

            if (newIndex >= materialCount)
            {
                newIndex = materialCount - SINGLE_COUNT;
            }

            currentIndex_ = newIndex;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            int newRow = row + SINGLE_COUNT;

            if (newRow > maxRow)
            {
                newRow = INITIAL_INDEX;
            }

            int newIndex = newRow * MAX_COLUMNS + col;

            if (newIndex >= materialCount)
            {
                newIndex = materialCount - SINGLE_COUNT;
            }

            currentIndex_ = newIndex;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_LEFT))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            int newCol = col - SINGLE_COUNT;

            if (newCol < INITIAL_INDEX)
            {
                int newRow = row - SINGLE_COUNT;

                if (newRow < INITIAL_INDEX)
                {
                    newRow = maxRow;
                }

                newCol = MAX_COLUMNS - SINGLE_COUNT;
                int newIndex = newRow * MAX_COLUMNS + newCol;

                if (newIndex >= materialCount)
                {
                    newIndex = materialCount - SINGLE_COUNT;
                }

                currentIndex_ = newIndex;
            }
            else
            {
                currentIndex_ = row * MAX_COLUMNS + newCol;
            }
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RIGHT))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            int newCol = col + SINGLE_COUNT;

            if (newCol >= MAX_COLUMNS)
            {
                int newRow = row + SINGLE_COUNT;

                if (newRow > maxRow)
                {
                    newRow = INITIAL_INDEX;
                }

                currentIndex_ = newRow * MAX_COLUMNS;
            }
            else
            {
                int newIndex = row * MAX_COLUMNS + newCol;

                if (newIndex >= materialCount)
                {
                    newIndex = INITIAL_INDEX;
                }

                currentIndex_ = newIndex;
            }
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_TAB) && !selectedMaterials_.empty())
        {
            soundManager.Play(SoundManager::SOUND::SE_PUSH);
            currentPhase_ = PHASE_EDIT_MATERIAL_LIST;
            selectedMaterialEditIndex_ = INITIAL_INDEX;
            return;
        }

        if (inputManager.IsTriggerUp(KEY_INPUT_RETURN))
        {
            start_ = true;
        }

        if (start_)
        {
            if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
            {
                soundManager.Play(SoundManager::SOUND::SE_PUSH);
                auto material = itemManager.GetMaterialItem(currentIndex_);

                if (material != nullptr && selectedMaterials_.size() < MAX_SELECTION_MATERIAL_TYPES)
                {
                    int alreadySelectedAmount = EMPTY_COUNT;

                    for (const auto& selected : selectedMaterials_)
                    {
                        if (selected.item->GetName() == material->GetName())
                        {
                            alreadySelectedAmount += selected.amount;
                        }
                    }

                    int availableAmount = material->GetQuantity() - alreadySelectedAmount;

                    if (availableAmount > EMPTY_COUNT)
                    {
                        selectedMaterialIndex_ = currentIndex_;
                        currentPhase_ = PHASE_SELECT_AMOUNT;
                        currentAmount_ = INITIAL_AMOUNT;
                    }
                }
            }
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_SPACE) &&
            selectedMaterials_.size() >= MIN_SELECTION_TO_START_ALCHEMY)
        {
            soundManager.Play(SoundManager::SOUND::SE_ALCHEMY);
            ExecuteAlchemy();
            waitingForSEFinish_ = true;
            return;
        }
    }
    else if (currentPhase_ == PHASE_SELECT_AMOUNT)
    {
        auto material = itemManager.GetMaterialItem(selectedMaterialIndex_);

        if (material == nullptr)
        {
            return;
        }

        int alreadySelectedAmount = EMPTY_COUNT;

        for (const auto& selected : selectedMaterials_)
        {
            if (selected.item->GetName() == material->GetName())
            {
                alreadySelectedAmount += selected.amount;
            }
        }

        int maxAvailable = material->GetQuantity() - alreadySelectedAmount;

        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::min(currentAmount_ + SINGLE_COUNT, maxAvailable);
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::max(INITIAL_AMOUNT, currentAmount_ - SINGLE_COUNT);
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            soundManager.Play(SoundManager::SOUND::SE_PUSH);
            selectedMaterials_.push_back({ material, currentAmount_ });
            currentPhase_ = PHASE_SELECT_MATERIAL;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            soundManager.Play(SoundManager::SOUND::SE_CANCEL);
            currentPhase_ = PHASE_SELECT_MATERIAL;
        }
    }
    else if (currentPhase_ == PHASE_EDIT_MATERIAL_LIST)
    {
        int selectedCount = static_cast<int>(selectedMaterials_.size());

        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            selectedMaterialEditIndex_ = (selectedMaterialEditIndex_ - SINGLE_COUNT + selectedCount) % selectedCount;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            selectedMaterialEditIndex_ = (selectedMaterialEditIndex_ + SINGLE_COUNT) % selectedCount;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentPhase_ = PHASE_EDIT_AMOUNT;
            currentAmount_ = selectedMaterials_[selectedMaterialEditIndex_].amount;
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_DELETE))
        {
            selectedMaterials_.erase(selectedMaterials_.begin() + selectedMaterialEditIndex_);

            if (selectedMaterials_.empty())
            {
                currentPhase_ = PHASE_SELECT_MATERIAL;
            }
            else if (selectedMaterialEditIndex_ >= static_cast<int>(selectedMaterials_.size()))
            {
                selectedMaterialEditIndex_ = static_cast<int>(selectedMaterials_.size()) - SINGLE_COUNT;
            }
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_TAB))
        {
            soundManager.Play(SoundManager::SOUND::SE_PUSH);
            currentPhase_ = PHASE_SELECT_MATERIAL;
        }
    }
    else if (currentPhase_ == PHASE_EDIT_AMOUNT)
    {
        auto material = selectedMaterials_[selectedMaterialEditIndex_].item;

        int otherSelectedAmount = EMPTY_COUNT;

        for (size_t i = 0; i < selectedMaterials_.size(); ++i)
        {
            if (i != static_cast<size_t>(selectedMaterialEditIndex_) &&
                selectedMaterials_[i].item->GetName() == material->GetName())
            {
                otherSelectedAmount += selectedMaterials_[i].amount;
            }
        }

        int maxAvailable = material->GetQuantity() - otherSelectedAmount;

        if (inputManager.IsTriggerDown(KEY_INPUT_UP))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::min(currentAmount_ + SINGLE_COUNT, maxAvailable);
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_DOWN))
        {
            soundManager.Play(SoundManager::SOUND::SE_SELECT);
            currentAmount_ = std::max(EMPTY_COUNT, currentAmount_ - SINGLE_COUNT);
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN))
        {
            soundManager.Play(SoundManager::SOUND::SE_PUSH);

            if (currentAmount_ == EMPTY_COUNT)
            {
                selectedMaterials_.erase(selectedMaterials_.begin() + selectedMaterialEditIndex_);

                if (selectedMaterials_.empty())
                {
                    currentPhase_ = PHASE_SELECT_MATERIAL;
                }
                else
                {
                    if (selectedMaterialEditIndex_ >= static_cast<int>(selectedMaterials_.size()))
                    {
                        selectedMaterialEditIndex_ = static_cast<int>(selectedMaterials_.size()) - SINGLE_COUNT;
                    }
                    currentPhase_ = PHASE_EDIT_MATERIAL_LIST;
                }
            }
            else
            {
                selectedMaterials_[selectedMaterialEditIndex_].amount = currentAmount_;
                currentPhase_ = PHASE_EDIT_MATERIAL_LIST;
            }
        }

        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE))
        {
            soundManager.Play(SoundManager::SOUND::SE_CANCEL);
            currentPhase_ = PHASE_EDIT_MATERIAL_LIST;
        }
    }
}

void AlchemyManager::Draw(void)
{
    if (!isOpen_)
    {
        return;
    }

    const int SINGLE_COUNT = 1;                         // 単一の個数
    const int EMPTY_COUNT = 0;                          // 空の個数
    const int INITIAL_TIMER = 0;                        // タイマーの初期値
    const int PHASE_SELECT_MATERIAL = 0;                // 素材選択フェーズ
    const int PHASE_SELECT_AMOUNT = 1;                  // 個数選択フェーズ
    const int PHASE_EDIT_MATERIAL_LIST = 2;             // 選択済み素材編集フェーズ
    const int PHASE_EDIT_AMOUNT = 3;                    // 選択済み素材の個数変更フェーズ
    const int MIN_SELECTION_TO_START_ALCHEMY = 2;       // 錬金開始に必要な最小素材種類数
    const int COLOR_WHITE = 0xffffff;                   // 白色
    const int COLOR_YELLOW = 0xffff00;                  // 黄色
    const int COLOR_ORANGE = 0xffaa00;                  // オレンジ色
    const int FULL_OPACITY_ALPHA = 255;                 // 完全不透明のアルファ値
    const int NO_BLEND_ALPHA = 0;                       // ノーブレンド時のアルファ値
    const int UI_START_X = 100;                         // UI描画開始X座標
    const int UI_START_Y = 100;                         // UI描画開始Y座標
    const int TITLE_OFFSET_Y = 30;                      // タイトルY座標オフセット
    const int ICON_SIZE = 64;                           // アイコンの一辺のサイズ
    const int PADDING = 50;                             // アイコン間のパディング
    const int ROW_SPACING = 20;                         // 行間の追加スペース
    const int SELECTION_BORDER_THICKNESS = 3;           // 選択枠の太さ
    const int BACKGROUND_BORDER_THICKNESS = 3;          // 背景外枠の太さ
    const int LEFT_BG_OFFSET_X = 20;                    // 左背景の左オフセット
    const int LEFT_BG_OFFSET_Y = 40;                    // 左背景の上オフセット
    const int LEFT_BG_EXPAND_X = 40;                    // 左背景の右拡張幅
    const int LEFT_BG_SHRINK_BOTTOM = 100;              // 左背景の下部縮小幅
    const int RIGHT_BG_OFFSET_X = 20;                   // 右背景の左オフセット
    const int RIGHT_BG_OFFSET_Y = 50;                   // 右背景の上オフセット
    const int RIGHT_BG_SHRINK_BOTTOM = 50;              // 右背景の下部縮小幅
    const int RIGHT_X_MULTIPLIER = 3;                   // 右側X座標の画面幅乗数
    const int RIGHT_X_DIVISOR = 5;                      // 右側X座標の画面幅除数
    const int SCREEN_HALF_DIVISOR = 2;                  // 画面半分除数
    const int FONT_SIZE_DEFAULT = 24;                   // 標準フォントサイズ
    const int FONT_SIZE_LARGE = 28;                     // 強調フォントサイズ
    const int FONT_SIZE_SMALL = 20;                     // 小フォントサイズ
    const int FONT_SIZE_EXTRA_SMALL = 22;               // 補助説明フォントサイズ
    const int TEXT_OFFSET_NAME_Y = 2;                   // 名前テキストのYオフセット
    const int TEXT_OFFSET_QUANTITY_Y = 24;              // 個数テキストのYオフセット
    const int TEXT_OFFSET_AMOUNT_INPUT_Y = 50;          // 数量入力テキストのYオフセット
    const int CENTER_MESSAGE_OFFSET_Y = 100;            // 中央メッセージのYオフセット
    const int HELP_TEXT_OFFSET_Y = 40;                  // 操作説明テキストのYオフセット
    const int BOTTOM_HELP_OFFSET_Y = 60;                // 画面下部操作説明のYオフセット
    const int BOTTOM_HELP_OFFSET_X = 50;                // 画面下部操作説明のXオフセット
    const int EDIT_LIST_START_OFFSET_Y = 50;            // 編集リストの開始Yオフセット
    const int EDIT_LIST_LINE_HEIGHT = 40;               // 編集リストの行の高さ
    const int EDIT_SUB_TEXT_OFFSET_Y = 30;              // 編集補助説明のYオフセット
    const int EDIT_TEXT_MARGIN_X = 150;                 // 編集テキストのXマージン
    const int LIST_START_TEXT_OFFSET_Y = 60;            // リスト開始テキストのYオフセット
    const int HIGHLIGHT_MARGIN_X = 5;                   // 強調表示枠のXマージン
    const int HIGHLIGHT_TOP_OFFSET_Y = 35;              // 強調表示枠の上部Yオフセット
    const int HIGHLIGHT_BOTTOM_OFFSET_Y = 65;           // 強調表示枠の下部Yオフセット
    const int HIGHLIGHT_EXPAND_X = 10;                  // 強調表示枠の右側拡張幅
    const int RESULT_TIMER_ROW_MULTIPLIER = 4;          // 結果タイマー行オフセット乗数

    auto& font = Font::GetInstance();
    auto& itemManager = ItemManager::GetInstance();

    const int screenWidth = Application::FULL_SCREEN_SIZE_X;
    const int screenHeight = Application::FULL_SCREEN_SIZE_Y;

    const int startX = UI_START_X;
    const int startY = UI_START_Y;

    font.DrawDefaultText(
        startX,
        startY - TITLE_OFFSET_Y,
        "錬金メニュー",
        COLOR_WHITE,
        FONT_SIZE_LARGE,
        Font::FONT_TYPE_ANTIALIASING_EDGE
    );

    const int padding = PADDING;
    const int maxColumns = MAX_COLUMNS;

    int itemCount = itemManager.GetMaterialItemCount();
    int rowCount = (itemCount + maxColumns - SINGLE_COUNT) / maxColumns;

    int leftWidth = maxColumns * (ICON_SIZE + padding) - padding;
    int leftHeight = rowCount * (ICON_SIZE + padding + ROW_SPACING);

    const int rightX = screenWidth * RIGHT_X_MULTIPLIER / RIGHT_X_DIVISOR;

    const int rightBgLeft = rightX - RIGHT_BG_OFFSET_X;
    const int rightBgTop = startY - RIGHT_BG_OFFSET_Y;
    const int rightBgRight = rightBgLeft + leftWidth;
    const int rightBgBottom = rightBgTop + leftHeight +
        (Application::FULL_SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR) - RIGHT_BG_SHRINK_BOTTOM;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, FULL_OPACITY_ALPHA);

    const int leftBgLeft = startX - LEFT_BG_OFFSET_X;
    const int leftBgTop = startY - LEFT_BG_OFFSET_Y;
    const int leftBgRight = startX + leftWidth + LEFT_BG_EXPAND_X;
    const int leftBgBottom = startY + leftHeight +
        (Application::FULL_SCREEN_SIZE_Y / SCREEN_HALF_DIVISOR) - LEFT_BG_SHRINK_BOTTOM;

    DrawBox(leftBgLeft, leftBgTop, leftBgRight, leftBgBottom, GetColor(0, 0, 0), true);
    DrawBox(rightBgLeft, rightBgTop, rightBgRight, rightBgBottom, GetColor(0, 0, 0), true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, NO_BLEND_ALPHA);

    const int borderThickness = BACKGROUND_BORDER_THICKNESS;
    const int white = GetColor(255, 255, 255);

    for (int i = 0; i < borderThickness; ++i)
    {
        DrawBox(leftBgLeft - i, leftBgTop - i, leftBgRight + i, leftBgBottom + i, white, false);
        DrawBox(rightBgLeft - i, rightBgTop - i, rightBgRight + i, rightBgBottom + i, white, false);
    }

    auto getItemFunc = [&](int index) -> std::shared_ptr<ItemBase> {
        return itemManager.GetMaterialItem(index);
        };

    for (int i = 0; i < itemCount; ++i)
    {
        auto item = getItemFunc(i);

        if (item == nullptr)
        {
            continue;
        }

        int row = i / maxColumns;
        int col = i % maxColumns;

        int x = startX + col * (ICON_SIZE + padding);
        int y = startY + row * (ICON_SIZE + padding + ROW_SPACING);

        DrawGraph(x, y, item->GetImageHandle(), true);

        font.DrawDefaultText(
            x,
            y + ICON_SIZE + TEXT_OFFSET_NAME_Y,
            item->GetName().c_str(),
            COLOR_WHITE,
            FONT_SIZE_LARGE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );

        int alreadySelectedAmount = EMPTY_COUNT;

        for (const auto& selected : selectedMaterials_)
        {
            if (selected.item->GetName() == item->GetName())
            {
                alreadySelectedAmount += selected.amount;
            }
        }

        int remainingQuantity = item->GetQuantity() - alreadySelectedAmount;

        int quantityColor = (remainingQuantity > EMPTY_COUNT) ? GetColor(200, 200, 200)
            : GetColor(255, 100, 100);

        std::string quantityStr = "x" + std::to_string(remainingQuantity);

        font.DrawDefaultText(
            x,
            y + ICON_SIZE + TEXT_OFFSET_QUANTITY_Y,
            quantityStr.c_str(),
            quantityColor,
            FONT_SIZE_LARGE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );

        if (currentPhase_ == PHASE_SELECT_AMOUNT && i == selectedMaterialIndex_)
        {
            std::string selectStr = "▶ x" + std::to_string(currentAmount_);
            font.DrawDefaultText(
                x,
                y + ICON_SIZE + TEXT_OFFSET_AMOUNT_INPUT_Y,
                selectStr.c_str(),
                COLOR_YELLOW,
                FONT_SIZE_LARGE,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }

        if (i == currentIndex_ && currentPhase_ == PHASE_SELECT_MATERIAL)
        {
            const int border = SELECTION_BORDER_THICKNESS;
            int colYellow = GetColor(255, 255, 0);
            DrawBox(
                x - border,
                y - border,
                x + ICON_SIZE + border,
                y + ICON_SIZE + border,
                colYellow,
                false
            );
        }
    }

    if (currentPhase_ == PHASE_SELECT_AMOUNT)
    {
        auto item = itemManager.GetMaterialItem(selectedMaterialIndex_);

        if (item != nullptr)
        {
            int alreadySelectedAmount = EMPTY_COUNT;

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

            int textWidth = font.GetDefaultTextWidth(text.c_str());
            int centerX = (screenWidth - textWidth) / SCREEN_HALF_DIVISOR;
            int centerY = (screenHeight / SCREEN_HALF_DIVISOR) + CENTER_MESSAGE_OFFSET_Y;

            font.DrawDefaultText(
                centerX,
                centerY,
                text.c_str(),
                COLOR_WHITE,
                FONT_SIZE_LARGE + 4,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );

            std::string help = "↑↓：個数変更 Enter：決定  Esc：キャンセル";
            int helpWidth = font.GetDefaultTextWidth(help.c_str());

            font.DrawDefaultText(
                (screenWidth - helpWidth) / SCREEN_HALF_DIVISOR,
                centerY + HELP_TEXT_OFFSET_Y,
                help.c_str(),
                GetColor(150, 150, 150),
                FONT_SIZE_EXTRA_SMALL,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }
    }

    if (currentPhase_ == PHASE_EDIT_AMOUNT)
    {
        const int offsetY = EDIT_LIST_START_OFFSET_Y;
        auto material = selectedMaterials_[selectedMaterialEditIndex_].item;

        std::string text = material->GetName() + " 個数変更： " +
            std::to_string(currentAmount_) + " (0で削除)";

        int rightTextX = rightBgLeft + EDIT_TEXT_MARGIN_X;

        font.DrawDefaultText(
            rightTextX,
            offsetY + static_cast<int>(selectedMaterials_.size() * EDIT_LIST_LINE_HEIGHT),
            text.c_str(),
            GetColor(255, 200, 100),
            FONT_SIZE_LARGE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );

        font.DrawDefaultText(
            rightTextX,
            offsetY + static_cast<int>(selectedMaterials_.size() * EDIT_LIST_LINE_HEIGHT) + EDIT_SUB_TEXT_OFFSET_Y,
            "↑↓：個数変更 Enter：決定",
            GetColor(150, 150, 150),
            FONT_SIZE_SMALL,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );
    }

    {
        const int offsetY = EDIT_LIST_START_OFFSET_Y;
        int rightTextX = rightBgLeft + RIGHT_BG_OFFSET_X;

        font.DrawDefaultText(
            rightTextX,
            offsetY,
            "選択中の素材：",
            COLOR_WHITE,
            FONT_SIZE_LARGE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );

        for (size_t i = 0; i < selectedMaterials_.size(); ++i)
        {
            std::string line = selectedMaterials_[i].item->GetName() + " x" +
                std::to_string(selectedMaterials_[i].amount);
            int textColor = COLOR_WHITE;

            if (currentPhase_ == PHASE_EDIT_MATERIAL_LIST &&
                i == static_cast<size_t>(selectedMaterialEditIndex_))
            {
                textColor = COLOR_YELLOW;

                int textWidth = font.GetDefaultTextWidth(line.c_str());
                DrawBox(
                    rightTextX - HIGHLIGHT_MARGIN_X,
                    offsetY + HIGHLIGHT_TOP_OFFSET_Y + static_cast<int>(i * EDIT_LIST_LINE_HEIGHT),
                    rightTextX + HIGHLIGHT_EXPAND_X + textWidth,
                    offsetY + HIGHLIGHT_BOTTOM_OFFSET_Y + static_cast<int>(i * EDIT_LIST_LINE_HEIGHT),
                    GetColor(50, 50, 0),
                    true
                );
            }

            font.DrawDefaultText(
                rightTextX,
                offsetY + HELP_TEXT_OFFSET_Y + static_cast<int>(i * EDIT_LIST_LINE_HEIGHT),
                line.c_str(),
                textColor,
                FONT_SIZE_LARGE,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }

        int startTextY = offsetY + LIST_START_TEXT_OFFSET_Y +
            static_cast<int>(selectedMaterials_.size() * EDIT_LIST_LINE_HEIGHT);

        if (selectedMaterials_.size() >= MIN_SELECTION_TO_START_ALCHEMY)
        {
            font.DrawDefaultText(
                rightTextX,
                startTextY,
                "Space: 錬金開始",
                GetColor(0, 255, 0),
                FONT_SIZE_LARGE,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }
        else
        {
            font.DrawDefaultText(
                rightTextX,
                startTextY,
                "2種類以上の素材を選択して錬金開始",
                COLOR_WHITE,
                FONT_SIZE_SMALL,
                Font::FONT_TYPE_ANTIALIASING_EDGE
            );
        }
    }

    std::string helpText;

    switch (currentPhase_)
    {
    case PHASE_SELECT_MATERIAL:
        helpText = "Enter：選択 Tab：編集 Space：錬金実行 ESC：閉じる";
        break;
    case PHASE_SELECT_AMOUNT:
        helpText = "↑↓：個数変更 Enter：決定";
        break;
    case PHASE_EDIT_MATERIAL_LIST:
        helpText = "↑↓：素材選択 Enter：個数変更 Tab：戻る";
        break;
    case PHASE_EDIT_AMOUNT:
        helpText = "↑↓：個数変更 Enter：決定";
        break;
    }

    int helpTextWidth = font.GetDefaultTextWidth(helpText.c_str());
    font.DrawDefaultText(
        (screenWidth - helpTextWidth) / SCREEN_HALF_DIVISOR + BOTTOM_HELP_OFFSET_X,
        screenHeight - BOTTOM_HELP_OFFSET_Y,
        helpText.c_str(),
        COLOR_WHITE,
        FONT_SIZE_LARGE,
        Font::FONT_TYPE_ANTIALIASING_EDGE
    );

    if (resultMessageTimer_ > INITIAL_TIMER)
    {
        int resultTextWidth = font.GetDefaultTextWidth(resultMessage_.c_str());
        font.DrawDefaultText(
            (screenWidth - resultTextWidth) / SCREEN_HALF_DIVISOR,
            (screenHeight / SCREEN_HALF_DIVISOR) + maxColumns * RESULT_TIMER_ROW_MULTIPLIER,
            resultMessage_.c_str(),
            COLOR_ORANGE,
            FONT_SIZE_LARGE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );
        resultMessageTimer_--;
    }
}

void AlchemyManager::ExecuteAlchemy(void)
{
    const int SINGLE_COUNT = 1;                         // 単一の個数
    const int EMPTY_COUNT = 0;                          // 空の個数
    const float EFFECT_POS_X = 0.0f;                    // エフェクトのX座標
    const float EFFECT_POS_Y = 70.0f;                   // エフェクトのY座標
    const float EFFECT_POS_Z = -50.0f;                  // エフェクトのZ座標
    const float EFFECT_ROTATION_W = 1.0f;               // エフェクト回転クォータニオンW成分
    const float EFFECT_SCALE_BLAST = 50.0f;             // 爆発エフェクトのスケール

    std::map<std::string, int> selectedMap;

    for (const auto& material : selectedMaterials_)
    {
        selectedMap[material.item->GetName()] += material.amount;
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
            for (const auto& [requiredName, requiredAmount] : required)
            {
                if (selectedMap.count(requiredName) == EMPTY_COUNT ||
                    selectedMap.at(requiredName) != requiredAmount)
                {
                    perfectMatch = false;
                    break;
                }
            }

            if (perfectMatch)
            {
                for (const auto& [selectedName, selectedAmount] : selectedMap)
                {
                    if (required.count(selectedName) == EMPTY_COUNT)
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
            ItemManager::GetInstance().AddQuantity(item, SINGLE_COUNT);

            for (const auto& material : selectedMaterials_)
            {
                ItemManager::GetInstance().SubtractQuantity(material.item, material.amount);
            }

            alchemyResult_ = ALCHEMY_RESULT::SUCCESS;

            selectedMaterials_.clear();

            resultMessage_ = item->GetName() + " を作成しました！";

            return;
        }
    }

    auto garbage = ItemManager::GetInstance().FindItemById("Garbage");
    ItemManager::GetInstance().AddQuantity(garbage, SINGLE_COUNT);

    for (const auto& material : selectedMaterials_)
    {
        ItemManager::GetInstance().SubtractQuantity(material.item, material.amount);
    }

    alchemyResult_ = ALCHEMY_RESULT::FAILURE;

    SoundManager::GetInstance().Play(SoundManager::SOUND::SE_ALCHEMY_FAIL);

    ShowRecipeDifferenceMessage(selectedMap);

    effectPlayedDuringAlchemy_ = true;

    EffectManager::GetInstance().Play(
        EffectManager::EFFECT::EFFECT_BLAST,
        { EFFECT_POS_X, EFFECT_POS_Y, EFFECT_POS_Z },
        { 0.0f, 0.0f, 0.0f, EFFECT_ROTATION_W },
        EFFECT_SCALE_BLAST,
        SoundManager::SOUND::NONE
    );

    selectedMaterials_.clear();
}

void AlchemyManager::ResetSelection(void)
{
    const int INITIAL_INDEX = 0;                        // カーソルの初期インデックス
    const int INITIAL_AMOUNT = 1;                       // 初期の選択個数
    const int INITIAL_PHASE = 0;                        // 初期フェーズ番号
    const int INITIAL_TIMER = 0;                        // タイマーの初期値

    selectedMaterials_.clear();
    currentIndex_ = INITIAL_INDEX;
    currentAmount_ = INITIAL_AMOUNT;
    currentPhase_ = INITIAL_PHASE;
    selectedMaterialIndex_ = INITIAL_INDEX;
    resultMessage_.clear();
    resultMessageTimer_ = INITIAL_TIMER;
    selectedMaterialEditIndex_ = INITIAL_INDEX;
}