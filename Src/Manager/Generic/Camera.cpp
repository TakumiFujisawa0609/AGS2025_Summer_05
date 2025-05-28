#include "Camera.h"

#include <EffekseerForDXLib.h>

#include "../../Application.h"
#include "../../Utility/Utility.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "../../Object/Common/Transform.h"

Camera::Camera(void)
{
	//モードの初期化
	mode_ = MODE::NONE;

	//座標の初期化
	pos_ = Utility::VECTOR_ZERO;

	//追従対象の座標
	targetPos_ = Utility::VECTOR_ZERO;

	//回転
	rot_ = Quaternion::Identity();
}

Camera::~Camera(void)
{

}

//初期化処理
void Camera::Init(void)
{
	//関数ポインタの設定
	setBeforeDrawMode_.emplace(MODE::NONE, std::bind(&Camera::SetBeforeDrawFollow, this));
	setBeforeDrawMode_.emplace(MODE::FIXED_POINT, std::bind(&Camera::SetBeforeDrawFixedPoint, this));
	setBeforeDrawMode_.emplace(MODE::FREE, std::bind(&Camera::SetBeforeDrawFree, this));
	setBeforeDrawMode_.emplace(MODE::FOLLOW, std::bind(&Camera::SetBeforeDrawFollow, this));
	setBeforeDrawMode_.emplace(MODE::FOLLOW_SPRING, std::bind(&Camera::SetBeforeDrawFollowSpring, this));
	setBeforeDrawMode_.emplace(MODE::FOLLOW_PERSPECTIVE, std::bind(&Camera::SetBeforeDrawFollowPerspective, this));
	setBeforeDrawMode_.emplace(MODE::SHAKE, std::bind(&Camera::SetBeforeDrawShake, this));

	//カメラの初期設定
	SetDefault();

	//カメラのライト設定
	SetLighting();
}

//更新処理
void Camera::Update(void)
{
	//ライトの移動
	SetLightPositionHandle(spotLight_, pos_);

	//ライトの向き更新
	SetLightDirectionHandle(spotLight_, rot_.ToEuler());
}

void Camera::SetBeforeDraw(void)
{
	//クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	//モードによる設定切り替え
	setBeforeDrawMode_[mode_]();

	//カメラの設定(位置と注視点による制御)
	SetCameraPositionAndTargetAndUpVec
	(
		pos_,
		targetPos_,
		cameraUp_
	);

	//DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();

}

//定点カメラ
void Camera::SetBeforeDrawFixedPoint(void)
{

}

//フリーカメラ
void Camera::SetBeforeDrawFree(void)
{
	auto& ins = InputManager::GetInstance();

	//移動操作
	ProcessMove();

	//減速
	Decelerate(MOVE_DEC);

	//移動
	Move();
}

//追従カメラ
void Camera::SetBeforeDrawFollow(void)
{
	//追従対象の位置
	VECTOR followPos = followTransform_->pos;

	//追従対象の向き
	Quaternion followRot = followTransform_->quaRot;

	//追従対象からカメラまでの相対座標
	VECTOR relativeCPos = followRot.PosAxis(RELATIVE_F2C_POS_FOLLOW);

	//カメラの位置の更新
	pos_ = VAdd(followPos, relativeCPos);

	//カメラ位置から注視点までの相対座標
	VECTOR relativeTPos = followRot.PosAxis(RELATIVE_C2T_POS);

	//注視点の更新
	targetPos_ = VAdd(pos_, relativeTPos);

	//カメラの上方向
	cameraUp_ = followRot.PosAxis(rot_.GetUp());
}

//ばね付き追従カメラ
void Camera::SetBeforeDrawFollowSpring(void)
{
	auto& ins = InputManager::GetInstance();

	//Cキー押下でカメラを揺らす
	if (ins.IsTrgDown(KEY_INPUT_C))
	{
		currentMode_ = mode_;
		ChangeMode(MODE::SHAKE);
	}

	//ばね定数(ばねの強さ)
	float POW_SPRING = 50.0f;

	//ばね定数(ばねの抵抗)
	float dampening = 2.0f * sqrt(POW_SPRING);

	//デルタタイム
	float delta = SceneManager::GetInstance().GetDeltaTime();

	//3D酔いする人用
	//delta = 1.0f / 60.0f;

	//追従対象の位置
	VECTOR followPos = followTransform_->pos;

	//追従対象の向き
	Quaternion followRot = followTransform_->quaRot;
	VECTOR zero = { 0.0f, 0.0f, 0.0f };

	//カメラの方向を固定する用
	Quaternion forward = Quaternion::Euler(zero);

	//追従対象からカメラまでの相対座標
	VECTOR relativeCPos = forward.PosAxis(RELATIVE_F2C_POS_FOLLOW);

	//理想位置
	VECTOR idealPos = VAdd(followPos, relativeCPos);

	//実際と理想の差
	VECTOR diff = VSub(pos_, idealPos);

	//力 =- ばねの強さ × ばねの伸び - 抵抗 × カメラ速度
	VECTOR force = VScale(diff, -POW_SPRING);
	force = VSub(force, VScale(velocity_, dampening));

	//速度の更新
	velocity_ = VAdd(pos_, VScale(velocity_, delta));

	//カメラ位置の更新
	pos_ = VAdd(pos_, VScale(velocity_, delta));

	//カメラ位置から注視点までの相対座標
	VECTOR relativeTPos = forward.PosAxis(RELATIVE_C2T_POS);

	//注視点の更新
	targetPos_ = VAdd(pos_, relativeTPos);

	//カメラの上方向
	cameraUp_ = forward.PosAxis(rot_.GetUp());
}

//追従対象視点カメラ
void Camera::SetBeforeDrawFollowPerspective(void)
{
	//追従対象の位置
	VECTOR followPos = followTransform_->pos;

	//追従対象の向き
	Quaternion followRot = followTransform_->
}
