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
}

void Player::Update(void)
{
	//移動前座標保存
	prePos_ = trans_.pos;

	ProcessMove();

	animationController_->Update();

	// プレイヤーの座標と半径を使って当たり判定
	CollisionManager::GetInstance().CheckHitWithPlayer(trans_.pos, radius_);

}

void Player::Draw(void)
{
	// プレイヤーの描画
	MV1DrawModel(modelId_);
#ifdef _DEBUG
	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "プレイヤー座標:(%.2f, %.2f, %.2f)", trans_.pos.x, trans_.pos.y, trans_.pos.z);
	DrawSphere3D(trans_.pos, radius_, 16, 0xffffff, 0xffffff, false);
	
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

void Player::ProcessMove(void)
{
	InputManager& ins = InputManager::GetInstance();

	// 移動方向を決める
	VECTOR moveDir = Utility::VECTOR_ZERO;
	if (ins.IsNew(KEY_INPUT_W)) { moveDir = VAdd(moveDir, Utility::DIR_F); }
	if (ins.IsNew(KEY_INPUT_S)) { moveDir = VAdd(moveDir, Utility::DIR_B); }
	if (ins.IsNew(KEY_INPUT_A)) { moveDir = VAdd(moveDir, Utility::DIR_L); }
	if (ins.IsNew(KEY_INPUT_D)) { moveDir = VAdd(moveDir, Utility::DIR_R); }

	if (!Utility::EqualsVZero(moveDir))
	{
		// 正規化
		moveDir = VNorm(moveDir);

		// 移動量を計算する(方向×スピード)
		VECTOR movePow = VScale(moveDir, SPEED_MOVE);

		// 移動処理(座標＋移動量)
		trans_.pos = VAdd(trans_.pos, movePow);

		// 方向がある時のみに角度を更新する
		if (Utility::SqrMagnitudeF(moveDir) > 0.0f)
		{
			// Y軸の向きだけ変更(XZ平面の向き)
			angles_.y = atan2f(moveDir.x, moveDir.z) + DX_PI_F;
		}

		// モデルに座標を設定する
		MV1SetPosition(modelId_, trans_.pos);

		// 方向から角度(ラジアン)に変換する
		angles_.y = atan2(moveDir.x, moveDir.z);

		// モデルの方向が正の負の方向を向いているので、補正する
		angles_.y += Utility::Deg2RadF(180.0f);
		
		// モデルに回転を設定する
		MV1SetRotationXYZ(modelId_, angles_);
	}
}  