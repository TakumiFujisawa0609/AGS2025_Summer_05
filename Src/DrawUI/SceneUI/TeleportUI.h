#pragma once

#include "../../Object/Common/Transform.h"

class StageManager;

class Player;

class TeleportUI
{
public:
	enum class DESTINATION
	{
		GUILD,
		ATELIER,
		GARDEN,
		MAX
	};

	TeleportUI(StageManager* stageManager, Player* player);
	~TeleportUI(void) = default;

	void Init(void);
	void Update(void);
	void Draw(void);

	// ï\é¶êßå‰
	void Show(void);
	void Hide(void);
	bool IsVisible(void) const;

private:
	

private:
	bool isVisible_;
	DESTINATION selected_;
	StageManager* stageManager_;
	Player* player_;
};
