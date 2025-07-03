#pragma once

#include <string>
#include <vector>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"
#include "../../Utility/Utility.h"

class OreObject : public HitObject, public UnitBase
{
public:

    enum class COOL_DOWNSTATE
    {
        READY,      // 採掘可能
        COOLINGDOWN // クールタイム中
    };


   static constexpr float ORE_COOLDOWN_TIME = 120.0f;

    OreObject(void);
    ~OreObject(void);

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
    void TryMine(void);

    // ヒット判定用
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
    void StartCooldown(void);
    bool IsCooldownOver(void) const;

    Transform trans_;

    COOL_DOWNSTATE cooldownState_;


    float radius_;
    bool isUIVisible_;
    bool wantsToShowUI_;
    bool isOnCooldown_;
    float minedTime_;
    int modelId_;
};
