#include "Camera.h"
#include "Player.h"

void Camera::Init(void)
{
	pos_ = INIT_POS;
}

void Camera::Update(void)
{
	//プレイヤーの前進(移動量)と同じ移動量でカメラも動かす
	pos_.z += Player::MOVE_POW_Z;
}

void Camera::SetBeforeDraw(void)
{
	// カメラの設定
	// SetDrawScreenの後、描画処理の前にカメラを設定すること
	SetCameraPositionAndAngle(
		pos_, 0.0f, 0.0f, 0.0f
	);
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return pos_;
}