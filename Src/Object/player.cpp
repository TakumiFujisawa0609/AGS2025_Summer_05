#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/Generic/InputManager.h"
#include "../Manager/Generic/SceneManager.h"
#include "../Object/Common/AnimationController.h"
#include "../Object/Manager/CollisionManager.h"
#include"player.h"

Player::Player(void)
{
	//モデル
	modelId_ = 0;

	//所持金
	money_ = 0;

	blockedDirX_ = 0;

	blockedDirZ_ = 0;

	//角度
	angles_ = VECTOR();

	//大きさ
	scales_ = VECTOR();
}

Player::~Player(void)
{
}

void Player::Init(void)
{
	//モデルのロード
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "player/playerkari.mv1").c_str());

	// 座標設定
	//初期化
	trans_.pos = DEFAULT_POS;
	prePos_ = trans_.pos;
	MV1SetPosition(modelId_, trans_.pos);

	// 大きさ設定
	scales_ = SCALES;
	MV1SetScale(modelId_, scales_);

	//当たり判定の半径
	radius_ = RADIUS;

	// 色の調整(自己発光)
	MV1SetMaterialEmiColor(modelId_, 0, COLOR_EMI_DEFAULT);

	// モデルの角度
	angles_ = { 0.0f, Utility::Deg2RadF(180.0f), 0.0f };
	MV1SetRotationXYZ(modelId_, angles_);

	//モデルアニメーション制御の初期化
	animationController_ = new AnimationController(modelId_);
	for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
	{
		//animationController_->AddInFbx(i, 30.0f, i);
	}

	// 初期アニメーション再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE), true);
	//カメラ方向初期化
	axis_ = { 0.0f,0.0f,0.0f };

	//所持金の初期化
	money_ = 0;
}

void Player::Update(void)
{
	//移動前座標保存
	prePos_ = trans_.pos;

	ProcessMove();

	animationController_->Update();

	// プレイヤーの座標と半径を使って当たり判定
	CollisionManager::GetInstance().CheckHitWithPlayer(this, trans_.pos, radius_, GetHitMin(), GetHitMax());

}

void Player::Draw(void)
{
	// プレイヤーの描画
	MV1DrawModel(modelId_);
#ifdef _DEBUG
	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "プレイヤー座標:(%.2f, %.2f, %.2f)", trans_.pos.x, trans_.pos.y, trans_.pos.z);
	DrawSphere3D(trans_.pos, radius_, 16, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 120, 0xffffff,"所持金 :%d", money_);
	
#endif //_DEBUG
}

void Player::Release(void)
{
	// プレイヤーモデルの解放
	MV1DeleteModel(modelId_);

	// アニメーションコントローラの解放
	//animationController_->Release();
	delete animationController_;
}

VECTOR Player::GetPos(void) const
{
	return trans_.pos;
}

void Player::SetPos(VECTOR pos)
{
	trans_.pos = pos;
}

VECTOR Player::GetHitMin(void) const
{
	return {
		trans_.pos.x - radius_,
		trans_.pos.y - radius_,
		trans_.pos.z - radius_
	};
}

VECTOR Player::GetHitMax(void) const
{
	return {
		trans_.pos.x + radius_,
		trans_.pos.y + radius_,
		trans_.pos.z + radius_
	};
}

float Player::GetRadius(void) const
{
	return radius_;
}

int Player::GetMoney(void) const
{
	return money_;
}

void Player::AddMoney(int money)
{
	money_ += money;
}

void Player::SetBlockedDirX(int dir)
{
	blockedDirX_ = dir;
}

void Player::SetBlockedDirZ(int dir)
{
	blockedDirZ_ = dir;
}

void Player::ResetBlockDirs(void)
{
	blockedDirX_ = 0;
	blockedDirZ_ = 0;
}


void Player::ProcessMove(void)
{
	InputManager& ins = InputManager::GetInstance();

	ResetBlockDirs(); // 毎フレームリセット

	// 移動方向を決める
	VECTOR moveDir = Utility::VECTOR_ZERO;

	// Z方向（前後）
	if (ins.IsNew(KEY_INPUT_W) && blockedDirZ_ != 1) // 前方ブロックされてないなら前進OK
		moveDir = VAdd(moveDir, Utility::DIR_F);

	if (ins.IsNew(KEY_INPUT_S) && blockedDirZ_ != -1) // 後方ブロックされてないなら後退OK
		moveDir = VAdd(moveDir, Utility::DIR_B);

	// X方向（左右）
	if (ins.IsNew(KEY_INPUT_A) && blockedDirX_ != 1) // 左ブロックされてない
		moveDir = VAdd(moveDir, Utility::DIR_L);

	if (ins.IsNew(KEY_INPUT_D) && blockedDirX_ != -1) // 右ブロックされてない
		moveDir = VAdd(moveDir, Utility::DIR_R);

	if (!Utility::EqualsVZero(moveDir))
	{
		moveDir = VNorm(moveDir);
		VECTOR movePow = VScale(moveDir, SPEED_MOVE);

		trans_.pos = VAdd(trans_.pos, movePow);

		if (Utility::SqrMagnitudeF(moveDir) > 0.0f)
		{
			angles_.y = atan2f(moveDir.x, moveDir.z) + DX_PI_F;
		}

		MV1SetPosition(modelId_, trans_.pos);

		angles_.y = atan2(moveDir.x, moveDir.z);
		angles_.y += Utility::Deg2RadF(180.0f);
		MV1SetRotationXYZ(modelId_, angles_);
	}
}
