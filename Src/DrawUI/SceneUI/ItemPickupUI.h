#pragma once

#include <vector>
#include <string>



class ItemPickupUI
{
public:
	const int DISPLAY_TIME = 180;

	ItemPickupUI(void);

	~ItemPickupUI(void);

	void Init(void);

	void Update(void);

	void Draw(void);

private:

	struct PickupInfo
	{
		std::string itemName;

		int quantity;

		int timer;
	};

	std::vector<PickupInfo> pickups_;

	void AddPickup(const std::string& itemName, int quantity);
};

