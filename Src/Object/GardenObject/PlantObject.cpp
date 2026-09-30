#include "PlantObject.h"

#include <random>

#include "../../Manager/System/TimeManager.h"
#include "../Manager/ItemManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../Item/Seed/RandomSeed.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"

PlantObject::PlantObject(void)
{
    const float INITIAL_TIME = 0.0f;                    // 初期時刻
    const int INVALID_MODEL_ID = -1;                    // 無効なモデルID

    growthStage_ = GROW_STAGE::Sprout;
    isActive_ = false;
    isUIVisible_ = false;
    hasPlant_ = false;
    growthStartTime_ = INITIAL_TIME;

    sproutModelId_ = INVALID_MODEL_ID;
    midGrowthModelId_ = INVALID_MODEL_ID;
    matureModelId_ = INVALID_MODEL_ID;

    transform_.modelId = INVALID_MODEL_ID;
}

PlantObject::~PlantObject(void)
{
    Release();
}

void PlantObject::Init(void)
{
    const int INVALID_MODEL_ID = -1;                    // 無効なモデルID
    const float INITIAL_TIME = 0.0f;                    // 初期時刻
    const float POSITION_ZERO = 0.0f;                   // 座標ゼロ値
    const float SCALE_X = 0.04f;                        // スケールX
    const float SCALE_Y = 0.03f;                        // スケールY
    const float SCALE_Z = 0.04f;                        // スケールZ
    const float ROTATION_ZERO = 0.0f;                   // 回転ゼロ値
    const float ACTUAL_RADIUS = 0.1f;                   // 当たり判定半径

    if (sproutModelId_ < 0)
    {
        sproutModelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::SEED_MODEL);
        midGrowthModelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::GROWING_MODEL);
        matureModelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::MATURE_MODEL);
    }

    hasPlant_ = false;
    isActive_ = false;
    isUIVisible_ = false;
    growthStage_ = GROW_STAGE::Sprout;
    growthStartTime_ = INITIAL_TIME;

    transform_.modelId = INVALID_MODEL_ID;
    transform_.position = VGet(POSITION_ZERO, POSITION_ZERO, POSITION_ZERO);
    transform_.scale = VGet(SCALE_X, SCALE_Y, SCALE_Z);
    transform_.rotation = VGet(ROTATION_ZERO, ROTATION_ZERO, ROTATION_ZERO);

    radius_ = ACTUAL_RADIUS;
}

void PlantObject::Release(void)
{
    const int INVALID_MODEL_ID = -1;                    // 無効なモデルID

    sproutModelId_ = INVALID_MODEL_ID;
    midGrowthModelId_ = INVALID_MODEL_ID;
    matureModelId_ = INVALID_MODEL_ID;

    transform_.modelId = INVALID_MODEL_ID;
}

void PlantObject::Update(void)
{
    auto& inputManager = InputManager::GetInstance();

    float currentTime = TimeManager::GetInstance().GetGameTime();

    if (isUIVisible_ && (inputManager.IsTriggerDown(KEY_INPUT_RETURN) ||
        inputManager.IsTriggerDown(KEY_INPUT_NUMPADENTER)))
    {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);

        if (!hasPlant_)
        {
            TryPlant();
        }
        else if (CanHarvest())
        {
            TryHarvest();
        }
    }

    if (!isActive_)
    {
        return;
    }

    float elapsedTime = currentTime - growthStartTime_;
    UpdateGrowthStage(elapsedTime);
}

void PlantObject::UpdateGrowthStage(float elapsedTime)
{
    GROW_STAGE newStage = growthStage_;

    if (elapsedTime < GROWTH_DURATION_SPROUT)
    {
        newStage = GROW_STAGE::Sprout;
    }
    else if (elapsedTime < GROWTH_DURATION_MID)
    {
        newStage = GROW_STAGE::MidGrowth;
    }
    else
    {
        newStage = GROW_STAGE::Mature;
    }

    if (newStage != growthStage_)
    {
        growthStage_ = newStage;
        ChangeModelForStage(newStage);
    }
}

void PlantObject::ChangeModelForStage(GROW_STAGE stage)
{
    const int INVALID_MODEL_ID = 0;                     

    switch (stage)
    {
    case GROW_STAGE::Sprout:
        transform_.modelId = sproutModelId_;
        break;
    case GROW_STAGE::MidGrowth:
        transform_.modelId = midGrowthModelId_;
        break;
    case GROW_STAGE::Mature:
        transform_.modelId = matureModelId_;
        break;
    }

    if (transform_.modelId >= INVALID_MODEL_ID)
    {
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
    }
}

void PlantObject::Draw(void)
{
    if (isActive_)
    {
        MV1DrawModel(transform_.modelId);
    }

    if (isUIVisible_)
    {
        const char* text = nullptr;

        if (!hasPlant_)
        {
            text = "植える";
        }
        else if (CanHarvest())
        {
            text = "収穫";
        }

        if (text != nullptr)
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
            const int COLOR_BLACK = GetColor(0, 0, 0);      // 黒色
            const int COLOR_WHITE = GetColor(255, 255, 255); // 白色

            const int screenWidth = Application::SCREEN_SIZE_X;
            const int screenHeight = Application::SCREEN_SIZE_Y;

            int textWidth = GetDrawStringWidth(text, static_cast<int>(strlen(text)), FONT_SIZE);
            int boxWidth = textWidth + TEXT_PADDING_WIDTH;
            int boxPositionX = screenWidth / SCREEN_HALF_DIVISOR - boxWidth / SCREEN_HALF_DIVISOR;
            int boxPositionY = screenHeight / SCREEN_HALF_DIVISOR + BOX_OFFSET_Y;

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
    }

#ifdef _DEBUG
    const int SPHERE_DIVISIONS = 8;                     // 球体の分割数
    const int COLOR_RED = GetColor(255, 0, 0);          // 赤色

    DrawSphere3D(
        transform_.position,
        radius_,
        SPHERE_DIVISIONS,
        COLOR_RED,
        COLOR_RED,
        false
    );
#endif
}

PlantObject::HIT_TYPE PlantObject::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR PlantObject::GetHitPosition(void) const
{
    return transform_.position;
}

float PlantObject::GetHitRadius(void) const
{
    const float ZERO_RADIUS = 0.0f;                    

    if (!hasPlant_)
    {
        return ZERO_RADIUS;
    }

    return radius_;
}

void PlantObject::ShowUI(void)
{
    isUIVisible_ = true;
}

void PlantObject::HideUI(void)
{
    isUIVisible_ = false;
}

bool PlantObject::IsValid(void) const
{
    return true;
}

void PlantObject::OnPlayerHit(void)
{
    ShowUI();
}

void PlantObject::OnPlayerExit(void)
{
    HideUI();
}

bool PlantObject::CanHarvest(void) const
{
    return hasPlant_ && growthStage_ == GROW_STAGE::Mature;
}

PlantObject::GROW_STAGE PlantObject::GetGrowthStage(void) const
{
    return growthStage_;
}

void PlantObject::TryPlant(void)
{
    if (hasPlant_)
    {
        return;
    }

    const int MINIMUM_QUANTITY = 0;                     // 最低必要数チェック値
    const int SUBTRACT_AMOUNT = 1;                      // 減少数

    auto seedItem = std::dynamic_pointer_cast<SeedItem>(
        ItemManager::GetInstance().FindItemById("RandomSeed")
    );

    if (seedItem == nullptr || seedItem->GetQuantity() <= MINIMUM_QUANTITY)
    {
        return;
    }

    ItemManager::GetInstance().SubtractQuantity(seedItem, SUBTRACT_AMOUNT);

    hasPlant_ = true;
    isActive_ = true;
    growthStage_ = GROW_STAGE::Sprout;
    growthStartTime_ = TimeManager::GetInstance().GetGameTime();

    ChangeModelForStage(GROW_STAGE::Sprout);
    HideUI();
}

void PlantObject::TryHarvest(void)
{
    if (!hasPlant_ || growthStage_ != GROW_STAGE::Mature)
    {
        return;
    }

    const int ADD_AMOUNT = 1;                           // 収穫ごとの追加数

    auto herbItem = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById("Herb")
    );

    if (herbItem != nullptr)
    {
        ItemManager::GetInstance().AddQuantity(herbItem, ADD_AMOUNT);
    }

    std::vector<std::string> possibleItems = {
        "AntidoteHerb",
        "MagicFlower",
        "ParalysisHerb",
        "GaleHerb",
        "DemonPowerHerb",
        "HardbodyHerb"
    };

    if (!possibleItems.empty())
    {
        const int MIN_INDEX = 0;                        // ランダムインデックス最小値
        const int RANDOM_ITEM_COUNT = 2;                // 取得するランダムアイテムの数

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());
        std::uniform_int_distribution<> distribution(
            MIN_INDEX,
            static_cast<int>(possibleItems.size()) - 1
        );

        for (int i = 0; i < RANDOM_ITEM_COUNT; ++i)
        {
            int index = distribution(generator);

            auto randomItem = std::dynamic_pointer_cast<MaterialItem>(
                ItemManager::GetInstance().FindItemById(possibleItems[index])
            );

            if (randomItem != nullptr)
            {
                ItemManager::GetInstance().AddQuantity(randomItem, ADD_AMOUNT);
            }
        }
    }

    const float INITIAL_TIME = 0.0f;                    // リセット時刻
    const int INVALID_MODEL_ID = -1;                    // 無効なモデルID

    hasPlant_ = false;
    isActive_ = false;
    growthStage_ = GROW_STAGE::Sprout;
    growthStartTime_ = INITIAL_TIME;

    transform_.modelId = INVALID_MODEL_ID;

    HideUI();
}

void PlantObject::SetActive(bool active)
{
    isActive_ = active;

    if (!active)
    {
        HideUI();
    }
}

Transform& PlantObject::GetTransform(void)
{
    return transform_;
}