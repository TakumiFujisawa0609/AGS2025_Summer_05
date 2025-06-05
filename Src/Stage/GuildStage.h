#pragma once

#include <memory>

#include "StageBase.h"

#include "../Object/GuildObject/BulletinBoard.h"
#include "../Object/GuildObject/Receptionist.h"
#include "../Object/GuildObject/TeleportMovement.h"

class GuildStage : public StageBase
{
public:
	//コンストラクタ
	GuildStage(void);

	//デストラクタ
	~GuildStage(void) = default;

	//初期化処理
	void Init(void) override;

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放処理
	void Release(void) override;

private:

	std::shared_ptr<BulletinBoard> bulletinBoard_;
	std::shared_ptr<Receptionist> receptionist_;
	std::shared_ptr<TeleportMovement> teleportMovement_;
};

