#pragma once

#include <DxLib.h>
#include "../Interact/HitObject.h"
#include "../UnitBase.h"
#include "../../Utility/Utility.h"

class LibraryUI;

class Bookshelf : public HitObject, public UnitBase
{
public:
    static constexpr float WIDTH = 150.0f;
    static constexpr float HEIGHT = 150.0f;
    static constexpr float DEPTH = 10.0f;

    Bookshelf(void);
    ~Bookshelf(void);

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void DrawUI(void);
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

    bool isVisible(void) const;

    Transform& GetTransform(void);

private:
    VECTOR hitMin_;
    VECTOR hitMax_;

    LibraryUI* libraryUI_;

    bool isValid_;
    bool isShowUI_;          // UI接近表示（"アイテムボックス"）
    bool isLibraryOpen_;     // UI表示
};
