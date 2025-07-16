#pragma once

#include<memory>
#include<chrono>
#include<vector>

#include"../../Application.h"
#include"../../Common/Fader.h"

class StageBase;
class Fader;
class Player;
class DateTimeManager;
class GameHUD;


class StageManager
{
public:

	//ステージID
	enum class STAGE_ID
	{
		NONE,
		ATELIER,
		GARDEN,
		GUILD,
		PRIVATE_ROOM,
	};

	//コンストラクタ
	StageManager(void);

	//デストラクタ
	~StageManager(void);

	//初期化処理
	void Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager);

	//破棄処理
	void Destroy(void);

	//更新処理
	void Update(void);

	//描画処理
	void Draw(void);

	//ステージ変更
	void ChangeStage(STAGE_ID nextId);

	//現在のステージIDの取得
	STAGE_ID GetStageID(void) const;

	//デルタタイム取得
	float GetDeltaTime(void) const;

	std::shared_ptr<Player> GetPlayer(void);

	void Fade(void);

private:

	//フェード
	std::unique_ptr<Fader> fader_;

	//現在のステージID
	STAGE_ID stageId_;

	//次のステージID
	STAGE_ID waitStageId_;

	//ステージ管理クラス
	StageBase* stage_;


	std::unique_ptr<GameHUD> gameHUD_;

	//遷移中かどうか
	bool isStageChanging_;

	//デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	//プレイヤー
	std::shared_ptr<Player> player_;

	//デルタタイムのリセット
	void ResetDeltaTime(void);

	//ステージ切り替え本体
	void DoChangeStage(STAGE_ID stageId);

};