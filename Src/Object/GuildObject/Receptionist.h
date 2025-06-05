#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
#include "../Interact/HitObject.h"
#include "../UnitBase.h"

// ItemTypeの定義
enum class ItemType
{
    HEALTH_POTION = 0,
    ANTIDOTE_POTION,
    MAGIC_POTION,
    ITEM_COUNT
};

class Receptionist : public HitObject, public UnitBase
{
public:
    // 定数
    static constexpr float RADIUS = 50.0f;
    static constexpr VECTOR SCALE = { 1.0f, 1.0f, 1.0f };
    static constexpr VECTOR MODEL_POS = { 0.0f, 0.0f, 0.0f };

    // コンストラクタ
    Receptionist(void);
    // デストラクタ
    ~Receptionist(void);

    // 初期化処理
    void Init(void);
    // 更新処理
    void Update(void) override;
    // 描画処理
    void Draw(void) override;
    // 解放
    void Release(void) override;

    // HitObjectを継承
    VECTOR GetHitPosition(void) const override;
    float GetHitRadius(void) const override;

    // 表示UI
    void ShowUI(void) override;
    // 非表示UI
    void HideUI(void) override;
    bool IsValid(void) const override;

    // アイテム関連
    bool DeliverItem(ItemType itemType, int quantity);
    void SetItemCount(ItemType itemType, int count);
    int GetItemCount(ItemType itemType) const;
    int GetMaxDeliveryQuantity() const;
    const char* GetItemName(ItemType itemType) const;
    std::string GetItemId(ItemType itemType) const;

private:
    // UI制御
    bool isShowUI_;
    bool isShowDeliveryMenu_;
    int selectedItem_;
    bool isSelectingQuantity_;
    int selectedQuantity_;

    // メッセージ表示
    int deliveryMessageTimer_;
    std::string lastDeliveryMessage_;

    // アイテム情報
    std::string itemNames_[static_cast<int>(ItemType::ITEM_COUNT)];
    std::string itemIds_[static_cast<int>(ItemType::ITEM_COUNT)];
};