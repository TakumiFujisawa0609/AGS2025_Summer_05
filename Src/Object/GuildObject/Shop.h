// Shop.h

#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "../../Object/Item/Seed/SeedItem.h"

class Player;

class Shop
{
public:

    enum class SHOP_PHASE {
        SELECT_ITEM,
        SELECT_AMOUNT
    };

    enum class SHOP_AREA {
        ITEM_LIST,
        PURCHASE_LIST
    };

    static constexpr int SHOP_COLUMNS = 3;
    static constexpr int SHOP_ICON_SIZE = 64;
    static constexpr int SHOP_PADDING = 20;
    static constexpr int SHOP_ITEM_WIDTH = SHOP_ICON_SIZE + 10;
    static constexpr int SHOP_ITEM_HEIGHT = SHOP_ICON_SIZE + 45;

    Shop(void);
    ~Shop(void);

    void Init(void);
    void Show(void);
    void Hide(void);
    bool IsVisible(void) const;

    void Update(void);
    void Draw(void);
    void DrawRightSideUI(void);

    void SetPlayer(std::shared_ptr<Player> player);

private:
    std::vector<std::shared_ptr<SeedItem>> seedItems_;
    std::unordered_map<std::string, int> purchaseQuantities_;

    int selectedItemIndex_;
    bool isVisible_;
    bool skipFirstInputFrame_;
    SHOP_PHASE currentPhase_;
    int selectedQuantity_;

    SHOP_AREA currentArea_;
    int purchaseListSelectedIndex_;

    std::shared_ptr<Player> player_;

    int GetPrice(std::shared_ptr<SeedItem> item) const;
    int GetTotalPrice(void) const;
    int GetSelectedQuantity(void) const;
    void ConfirmPurchase(void);

    std::shared_ptr<SeedItem> GetSelectedItem(void) const;
};
