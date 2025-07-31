#include "WellObject.h"
#include <DxLib.h>
#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/System/TimeManager.h"
#include "../../Object/Manager/ItemManager.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"

WellObject::WellObject()
    : isUIVisible_(false), wantsToShowUI_(false), isOnCooldown_(false), minedTime_(0.0f) {
}

WellObject::~WellObject() {
    Release();
}

void WellObject::Init() {
    trans_.modelId = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::WELL_MODEL);
    trans_.pos = VGet(0, -10, 0);
    trans_.scl = VGet(0.1f, 0.15f, 0.1f);
    trans_.rot = VGet(0, 0, 0);
}

void WellObject::Update() {
    if (isOnCooldown_ && IsCooldownOver()) {
        isOnCooldown_ = false;
    }

    isUIVisible_ = wantsToShowUI_;

    auto& input = InputManager::GetInstance();
    if (isUIVisible_ && (input.IsTrgDown(KEY_INPUT_RETURN) || input.IsTrgDown(KEY_INPUT_NUMPADENTER)))
    {
        SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
        if (!isOnCooldown_) {
            TryDrawWater();
        }
    }
}

void WellObject::Draw() {
    if (trans_.modelId >= 0) {
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }

    if (isUIVisible_) {
        const char* text = isOnCooldown_ ? "‹‚‚ß‚È‚¢" : "…‚ð‹‚‚Þ";

        int fontSize = 24;
        int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
        int boxWidth = textWidth + 30;
        int boxHeight = 30;

        int boxX = (Application::SCREEN_SIZE_X / 2) - boxWidth / 2;
        int boxY = (Application::SCREEN_SIZE_Y / 2) + 100;

        DrawBox(boxX - 10, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
        DrawBox(boxX - 10, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
        Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);


       
       
    }

#ifdef _DEBUG
    DrawSphere3D(trans_.pos, radius_, 8, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
#endif
}

void WellObject::Release() {
    if (trans_.modelId >= 0) {
        MV1DeleteModel(trans_.modelId);
        trans_.modelId = -1;
    }
}

Transform& WellObject::GetTransform() {
    return trans_;
}

bool WellObject::IsCooldownOver() const {
    return TimeManager::GetInstance().GetGameTime() - minedTime_ >= COOLDOWN_TIME;
}

void WellObject::StartCooldown() {
    minedTime_ = TimeManager::GetInstance().GetGameTime();
    isOnCooldown_ = true;
}

void WellObject::TryDrawWater() {
    auto waterItem = std::dynamic_pointer_cast<MaterialItem>(
        ItemManager::GetInstance().FindItemById("Water"));
    if (waterItem) {
        ItemManager::GetInstance().AddQuantity(waterItem, 5);
    }

    StartCooldown();
    HideUI();
}

// ƒqƒbƒgŠÖ˜A
HitObject::HIT_TYPE WellObject::GetHitType() const { return HIT_TYPE::SPHERE; }
VECTOR WellObject::GetHitPosition() const { return trans_.pos; }
float WellObject::GetHitRadius() const { return radius_; }
bool WellObject::IsValid() const { return true; }

void WellObject::ShowUI() { wantsToShowUI_ = true; }
void WellObject::HideUI() { wantsToShowUI_ = false; isUIVisible_ = false; }
void WellObject::OnPlayerHit() { ShowUI(); }
void WellObject::OnPlayerExit() { HideUI(); }
