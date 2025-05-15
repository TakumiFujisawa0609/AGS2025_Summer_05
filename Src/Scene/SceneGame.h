#pragma once

#include<memory>

#include"SceneBase.h"
#include"../Application.h"

class Grid;

class SceneGame : public SceneBase
{
public:

	//コンストラクタ
	SceneGame(void);

	//デストラクタ
	~SceneGame(void) = default;

	//初期化処理
	void Init(void)override;

	//更新処理
	void Update(void)override;

	//描画処理
	void Draw(void)override;

	//解放処理
	void Release(void)override;

private:

	//スカイドーム

	
	//ステージ

	
	//プレイヤー

	//グリッド線
	Grid* grid_;

	//描画(デバッグ)
	void DrawDebug(void);

	//当たり判定
	void Collision(void);

	//ゲームのクリア処理
	void GameClear(void);

	//ゲームオーバー処理
	void GameOver(void);
};

