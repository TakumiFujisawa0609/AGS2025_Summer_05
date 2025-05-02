#include<DxLib.h>
#include"player.h""

void Player::Init(void)
{
	// プレイヤーモデルID
	ModelId_ = MV1LoadModel("Data/Model/player/YUH姉貴ver1.0a/YUH姉貴.pmx");
	//プレイヤーの位置
	pos_ = INIT_POS;
	// 座標をモデルに設定
	MV1SetPosition(ModelId_, pos_);

	isAlive_ = true;
}

void Player::Update(void)
{
	if (isAlive_)
	{
		// プレイヤーの左右移動
		if (CheckHitKey(KEY_INPUT_D))
		{
			pos_.x += MOVE_POW_X;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			pos_.x -= MOVE_POW_X;
		}
		// プレイヤーの前後移動
		if (CheckHitKey(KEY_INPUT_W))
		{
			pos_.z += MOVE_POW_Z;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			pos_.z -= MOVE_POW_Z;
		}
	}

	//プレイヤーの移動制限
	if (pos_.x > MOVE_LIMIT)
	{
		pos_.x = MOVE_LIMIT;
	}
	if (pos_.y < MOVE_LIMIT)
	{
		pos_.y = MOVE_LIMIT;
	}

	// 座標をモデルに設定
	MV1SetPosition(ModelId_, pos_);
}

void Player::Draw(void)
{
	// プレイヤーの描画
	if (isAlive_)
	{
		MV1DrawModel(ModelId_);
	}
#ifdef DEBUG
	// プレイヤーの衝突判定確認用球体描画
	DrawSphere3D(playerPos_, 80.0f, 10, 0x0000ff, 0x0000ff, false);
#endif
}

void Player::Release(void)
{
	// プレイヤーモデルの解放
	MV1DeleteModel(ModelId_);
}

VECTOR Player::GetPos(void)
{
	return pos_;
}

bool Player::IsAlive(void)
{
	return isAlive_;
}

void Player::SetAlive(bool isAlive)
{
	isAlive_ = isAlive;
}