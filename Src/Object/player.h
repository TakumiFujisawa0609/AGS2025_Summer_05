#pragma once
#include<DxLib.h>

class AnimationController;
class Player
{
public:

	// アニメーション種別
	enum class ANIM_TYPE
	{
		DEATH,
		DUCK,
		HIT_REACT,
		IDLE,
		IDLE_ATTACK,
		IDLE_HOLD,
		JUMP,
		JUMP_IDLE,
		JUMP_LAND,
		NO,
		PUNCH,
		RUN,
		RUN_ATTACK,
		RUN_HOLD,
		WALK,
		WALK_HOLD,
		WAVE,
		YES,
		MAX,
	};

	// モデルの大きさ
	static constexpr VECTOR SCALES = { 0.5f, 0.5f, 0.5f };

	// 初期位置
	static constexpr VECTOR DEFAULT_POS = { 300.0f, 10.0f, 300.0f };

	// 標準の自己発光色
	static constexpr COLOR_F COLOR_EMI_DEFAULT = { 0.5f, 0.5f, 0.5f, 0.5f };

	// 移動スピード
	static constexpr float SPEED_MOVE = 10.0f;

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);

	//初期化
	void Init(void);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);	

	VECTOR GetPos(void) const;
	void SetPos(VECTOR pos);

	// 衝突判定
	void CollisionStage(VECTOR pos);

private:
	// モデルID
	int modelId_;
	VECTOR pos_;
	VECTOR angles_;
	VECTOR scales_;

	// 地面にいるかどうか
	bool isOnGround_;

	// アニメーション
	AnimationController* animationController_;

	// 行動制御
	void ProcessMove(void);
};