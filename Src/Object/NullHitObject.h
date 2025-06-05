#pragma once

#include <DxLib.h>

#include "Interact/HitObject.h"

class NullHitObject : public HitObject {
public:
    VECTOR GetHitPosition(void) const override;

    float GetHitRadius(void) const override;
    
    void ShowUI(void) override;
    
    void HideUI(void) override;
    
    bool IsValid(void) const override;
};


