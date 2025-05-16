#pragma once

#include<memory>

#include"StageBase.h"

class PrivateRoomStage : public StageBase
{
public:
	//コンストラクタ
	PrivateRoomStage(void);

	//デストラクタ
	~PrivateRoomStage(void) = default;

	//初期化処理
	void Init(void) override;

	//更新処理
	void Update(void) override;

	//描画処理
	void Draw(void) override;

	//解放処理
	void Release(void) override;

private:


};

