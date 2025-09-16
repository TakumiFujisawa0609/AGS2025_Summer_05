// OreObject.cpp

#include "OreObject.h"

#include <DxLib.h>
#include <random>

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/Font.h"
#include "../Manager/ItemManager.h"
#include "../../Application.h"

OreObject::OreObject(void)
    : radius_(40.0f), isUIVisible_(false), wantsToShowUI_(false),
    isOnCooldown_(false), cooldownState_(COOL_DOWNSTATE::READY),
    minedTime_(0.0f), modelId_(-1) {
}

OreObject::~OreObject(void)
{
    if (modelId_ >= 0) {
        MV1DeleteModel(modelId_);
    }
}

void OreObject::Init(void)
{
    modelId_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::ORE_MODEL);
    trans_.modelId = modelId_;
    trans_.scl = VGet(0.03f, 0.03f, 0.03f);
    trans_.rot = VGet(0, 0, 0);
}

void OreObject::Update(void)
{
    // クールタイム状態の更新
    if (isOnCooldown_) {
        // クールダウン時間が経過したかチェック
        if (TimeManager::GetInstance().GetGameTime() - minedTime_ >= ORE_COOLDOWN_TIME) {
            isOnCooldown_ = false;
            cooldownState_ = COOL_DOWNSTATE::READY;
        }
        else {
            cooldownState_ = COOL_DOWNSTATE::COOLINGDOWN;
        }
    }
    else {
        cooldownState_ = COOL_DOWNSTATE::READY;
    }

    // 入力処理（PlantObjectと同じ構造）
    auto& input = InputManager::GetInstance();
    if (isUIVisible_ && (input.IsTrgDown(KEY_INPUT_RETURN) || input.IsTrgDown(KEY_INPUT_NUMPADENTER))) {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);

        if (cooldownState_ == COOL_DOWNSTATE::READY) {

            TryMine();
        }
    }
}

void OreObject::Draw(void)
{
    if (modelId_ >= 0) {
        MV1SetPosition(modelId_, trans_.pos);
        MV1SetScale(modelId_, trans_.scl);
        MV1SetRotationXYZ(modelId_, trans_.rot);
        MV1DrawModel(modelId_);
    }

    if (isUIVisible_)
    {
        const char* text = nullptr;
        if (cooldownState_ == COOL_DOWNSTATE::READY)
        {
            text = "採掘";
        }
        else if (cooldownState_ == COOL_DOWNSTATE::COOLINGDOWN)
        {
            text = "採掘不可";
        }

        const int screenWidth = Application::SCREEN_SIZE_X;
        const int screenHeight = Application::SCREEN_SIZE_Y;

        int fontSize = 24;
        int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
        int boxWidth = textWidth + 30;
        int boxHeight = 30;

        int boxX = screenWidth / 2 - boxWidth / 2;
        int boxY = screenHeight / 2 + 100;

        DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
        DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);

        Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);
    }



#ifdef _DEBUG
    DrawSphere3D(trans_.pos, radius_, 8, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
#endif
}

void OreObject::Release(void)
{
}

void OreObject::TryMine(void)
{
    if (cooldownState_ != COOL_DOWNSTATE::READY) return;

    // 確定アイテム
    auto herbItem = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById("IronOre"));
    if (herbItem) {
        ItemManager::GetInstance().AddQuantity(herbItem, 1);
    }

    // テスト用のダミーアイテムIDを追加
    std::vector<std::string> materials = {
        "FireMagicStone",
        "WaterMagicStone",
        "WindMagicStone",
        "EarthMagicStone",
        "IceMagicStone",
        "LightMagicStone",
        "DarkMagicStone",

        // TODO: 実際のアイテムIDに変更
    };

    // アイテムが存在しない場合でも採掘処理は実行する
    if (!materials.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, static_cast<int>(materials.size() - 1));

        int index = dist(gen);

        auto item = std::dynamic_pointer_cast<MaterialItem>(
            ItemManager::GetInstance().FindItemById(materials[index]));

        if (item) {
            ItemManager::GetInstance().AddQuantity(item, 1);
        }
    }

    // アイテムが追加されなくてもクールダウンは開始する
    StartCooldown();
    HideUI();
}

void OreObject::StartCooldown(void)
{
    minedTime_ = TimeManager::GetInstance().GetGameTime();
    isOnCooldown_ = true;
    cooldownState_ = COOL_DOWNSTATE::COOLINGDOWN;
}

bool OreObject::IsCooldownOver(void) const
{
    // クールダウン中でない場合は常にfalse
    // クールダウン中の場合は、経過時間をチェック
    return isOnCooldown_ && (TimeManager::GetInstance().GetGameTime() - minedTime_ >= ORE_COOLDOWN_TIME);
}

OreObject::HIT_TYPE OreObject::GetHitType(void) const
{
    return HIT_TYPE::SPHERE;
}

VECTOR OreObject::GetHitPosition(void) const
{
    return trans_.pos;
}

float OreObject::GetHitRadius(void) const
{
    return radius_;
}

bool OreObject::IsValid(void) const
{
    return true;
}

void OreObject::OnPlayerHit(void)
{
    isUIVisible_ = true;
}

void OreObject::ShowUI(void)
{
    isUIVisible_ = true;
}

void OreObject::HideUI(void)
{
    isUIVisible_ = false;
}

void OreObject::OnPlayerExit(void)
{
    HideUI();
}

Transform& OreObject::GetTransform(void)
{
    return trans_;
}