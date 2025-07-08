#pragma once

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class WellObject : public HitObject, public UnitBase {
public:
    WellObject(void);
    ~WellObject(void);

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    HIT_TYPE GetHitType(void) const override;
    VECTOR GetHitPosition(void) const override;
    float GetHitRadius(void) const override;

    bool IsValid(void) const override;
    void ShowUI(void) override;
    void HideUI(void) override;
    void OnPlayerHit(void) override;
    void OnPlayerExit(void) override;

    Transform& GetTransform(void);

private:
    void TryDrawWater(void); // êÖÇÇ≠Ç›éÊÇÈèàóù
    bool IsCooldownOver(void) const;
    void StartCooldown(void);

private:
    bool isUIVisible_;
    bool wantsToShowUI_;
    bool isOnCooldown_;
    float minedTime_;

    static constexpr float radius_ = 40.0f;
    static constexpr float COOLDOWN_TIME = 400.0f; // 60ïb
};
