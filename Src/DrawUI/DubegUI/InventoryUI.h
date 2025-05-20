#pragma once

class ItemManager;

class InventoryUI
{
public:
	InventoryUI(ItemManager& manager);

	void Update(void);

	void Draw(void);

	bool IsVisible(void) const { return isVisible_; }

private:

	ItemManager& itemManager_;

	bool isVisible_;

	int selectedItemIndex_;

	int frameCount_;
};

