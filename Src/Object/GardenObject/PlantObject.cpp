#include "PlantObject.h"

#include <random>

#include "../../Manager/System/TimeManager.h"
#include "../Manager/ItemManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../Item/Seed/RandomSeed.h"
#include "../../DrawUI/Font.h"

// コンストラクタ
PlantObject::PlantObject(void)
{
    growthStage_ = GROW_STAGE::Sprout;
    isActive_ = true;
    isUIVisible_ = false;
    growthStartTime_ = 0.0f;
    sproutModelId_ = -1;
    midGrowthModelId_ = -1;
    matureModelId_ = -1;
}

// デストラクタ
PlantObject::~PlantObject(void)
{
    Release();
}

// 初期化
void PlantObject::Init(void)
{
    isActive_ = true;
    isUIVisible_ = false;
    growthStage_ = GROW_STAGE::Sprout;

    growthStartTime_ = TimeManager::GetInstance().GetGameTime();

    // モデル読み込み
    //sproutModelId_ = MV1LoadModel("Data/PlantSprout.mv1");
    //midGrowthModelId_ = MV1LoadModel("Data/PlantMidGrowth.mv1");
    //matureModelId_ = MV1LoadModel("Data/PlantMature.mv1");

   // trans_.modelId = sproutModelId_;
    trans_.pos = VGet(0, 0, 0);
    trans_.scl = VGet(1, 1, 1);
    trans_.rot = VGet(0, 0, 0);

    radius_ = 50.0f;
}

// 解放
void PlantObject::Release(void)
{
    //if (sproutModelId_ >= 0) MV1DeleteModel(sproutModelId_);
    //if (midGrowthModelId_ >= 0) MV1DeleteModel(midGrowthModelId_);
    //if (matureModelId_ >= 0) MV1DeleteModel(matureModelId_);

    sproutModelId_ = -1;
    midGrowthModelId_ = -1;
    matureModelId_ = -1;

    trans_.modelId = -1;
}

// 更新処理
void PlantObject::Update(void)
{
    auto& input = InputManager::GetInstance();

    float now = TimeManager::GetInstance().GetGameTime();

    if (isUIVisible_ && (input.IsTrgDown(KEY_INPUT_RETURN) || input.IsTrgDown(KEY_INPUT_NUMPADENTER)))
    {
        if (!isActive_)
        {
            // 植えてないなら植える処理
            TryPlant();
        }
        else if (growthStage_ == GROW_STAGE::Mature)
        {
            // 成長完了なら収穫処理
            TryHarvest();
        }
    }

    if (!isActive_)
    {
        // 植えていないなら成長処理は不要
        return;
    }

    float elapsed = now - growthStartTime_;
    UpdateGrowthStage(elapsed);
}


// 成長段階に応じてモデルを切り替える
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

// モデルをステージに応じて切り替える
void PlantObject::ChangeModelForStage(GROW_STAGE stage)
{
    //if (trans_.modelId >= 0)
    //{
    //    MV1DeleteModel(trans_.modelId);
    //}

    switch (stage)
    {
    case GROW_STAGE::Sprout:
        //trans_.modelId = sproutModelId_;
        break;
    case GROW_STAGE::MidGrowth:
        //trans_.modelId = midGrowthModelId_;
        break;
    case GROW_STAGE::Mature:
        //trans_.modelId = matureModelId_;
        break;
    }

    /*if (trans_.modelId >= 0)
    {
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
    }*/
}

// 描画
void PlantObject::Draw(void)
{
    if (isActive_)
    {
        // モデル描画（必要なら）
    }

    if (isUIVisible_)
    {
        const char* text = nullptr;

        if (!isActive_) {
            text = "植える";
        }
        else if (CanHarvest()) {
            text = "収穫";
        }

       if (text)
	{
		VECTOR screenPos;
		if (ConvWorldPosToScreenPos(trans_.pos, &screenPos) == FALSE)
		{
			// 変換失敗したら描画しない
			return;
		}

		SetUseZBuffer3D(FALSE); // UIはZバッファを無視して描画

		int fontSize = 18;
		int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
		int boxWidth = textWidth + 30;
		int boxHeight = 20;
		int boxX = static_cast<int>(screenPos.x) - boxWidth / 2;
		int boxY = static_cast<int>(screenPos.y) - 60;

		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(0, 0, 0), TRUE);
		DrawBox(boxX, boxY, boxX + boxWidth, boxY + boxHeight, GetColor(255, 255, 255), FALSE);
		Font::GetInstance().DrawDefaultText(boxX + 15, boxY + 5, text, GetColor(255, 255, 255), fontSize);

		SetUseZBuffer3D(TRUE);
	}

    // デバッグ用の当たり判定表示はそのまま
#ifdef _DEBUG
    DrawSphere3D(trans_.pos, radius_, 8, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
#endif
}

// ヒット判定系
PlantObject::HIT_TYPE PlantObject::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR PlantObject::GetHitPosition(void) const
{
    return trans_.pos;
}

float PlantObject::GetHitRadius(void) const
{
    return radius_;
}

// UI表示制御
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
    return growthStage_ == GROW_STAGE::Mature;
}

PlantObject::GROW_STAGE PlantObject::GetGrowthStage(void) const
{
    return growthStage_;
}

void PlantObject::TryPlant(void)
{
    // すでに植えてある or 無効状態なら何もしない
    if (isActive_) return;

    // RandomSeed の所持数チェック
    auto seedItem = std::dynamic_pointer_cast<SeedItem>(
        ItemManager::GetInstance().FindItemById("RandomSeed")
    );

    if (!seedItem || seedItem->GetQuantity() <= 0)
    {
        // 所持してないなら無視
        return;
    }

    // 植える処理
    ItemManager::GetInstance().SubtractQuantity(seedItem, 1); // 種を1つ減らす
    Init();                      // 成長スタート（モデル非表示ならInit内容に注意）
    HideUI();                    // UI非表示
}

void PlantObject::TryHarvest()
{
    // Herbを1つ加算
    auto herb = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById("Herb")
    );
    if (herb)
    {
        ItemManager::GetInstance().AddQuantity(herb, 1);
    }

    // ランダム素材加算
    std::vector<std::string> extraMaterials = {
        "AntidoteHerb",
        "MagicFlower",
    };
    int index = rand() % static_cast<int>(extraMaterials.size());
    auto extra = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById(extraMaterials[index])
    );
    if (extra)
    {
        ItemManager::GetInstance().AddQuantity(extra, 1);
    }

    // 植え直し可能にする準備（非アクティブ化）
    SetActive(false);       // 成長処理は止める
    growthStage_ = GROW_STAGE::Sprout;
    growthStartTime_ = 0.0f;

    // モデル切り替え・非表示（必要なら）
    trans_.modelId = -1;
    // → MV1DeleteModel はコメント化中なので呼ばなくてOK

    // UIは再度出せるように（触れたら「植える」と出る）
    ShowUI();
}

void PlantObject::SetActive(bool active)
{
    isActive_ = active;
    if (!active) HideUI();
}

Transform& PlantObject::GetTransforms(void)
{
    return trans_;
}
