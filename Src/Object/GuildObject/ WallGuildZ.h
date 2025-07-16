#pragma once

#include <DxLib.h>
#include "../Interact/HitObject.h"
#include "../UnitBase.h"
#include "../../Utility/Utility.h"

class  WallGuildZ : public HitObject, public UnitBase
{
public:
    static constexpr float WIDTH =700.0f;
    static constexpr float HEIGHT = 500.0f;
    static constexpr float DEPTH = 150.0f;

    WallGuildZ(void);
    ~WallGuildZ(void);

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    VECTOR GetHitMin(void) const override;
    VECTOR GetHitMax(void) const override;

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
    VECTOR hitMin_;
    VECTOR hitMax_;
    bool isValid_;
};

