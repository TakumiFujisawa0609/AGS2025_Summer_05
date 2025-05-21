#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/Generic/InputManager.h"
#include"player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(void)
{
	//モデルのロード
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "player/playerkari.mv1").c_str());

	// 座標設定
	pos_ = DEFAULT_POS;
	MV1SetPosition(modelId_, pos_);

	// 大きさ設定
	scales_ = SCALES;
	MV1SetScale(modelId_, scales_);

	// 色の調整(自己発光)
	MV1SetMaterialEmiColor(modelId_, 0, COLOR_EMI_DEFAULT);

	// モデルの角度
	angles_ = { 0.0f, Utility::Deg2RadF(180.0f), 0.0f };
	MV1SetRotationXYZ(modelId_, angles_);
}

void Player::Update(void)
{
	ProcessMove();
}

void Player::Draw(void)
{
	// プレイヤーの描画
	MV1DrawModel(modelId_);

#ifdef _DEBUG
	// プレイヤー座標
	DrawFormatString(0, 40, 0xffffff, "プレイヤー座標:(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
#endif //_DEBUG
}

void Player::Release(void)
{
	// プレイヤーモデルの解放
	MV1DeleteModel(modelId_);
}

void Player::GetPos(void)
{
	//return pos_;
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
		pos_ = VAdd(pos_, movePow);

		// モデルに座標を設定する
		MV1SetPosition(modelId_, pos_);

		// 方向から角度(ラジアン)に変換する
		angles_.y = atan2(moveDir.x, moveDir.z);

		// モデルの方向が正の負の方向を向いているので、補正する
		angles_.y += Utility::Deg2RadF(180.0f);

		MV1SetRotationXYZ(modelId_, angles_);
	}
}