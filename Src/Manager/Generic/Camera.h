#pragma once

#include <DxLib.h>
#include <functional>
#include <map>
#include <cmath>
#include <DirectXMath.h>

#include "../../Common/Quaternion.h"

class Transform;

/// @brief カメラの管理・制御を行うクラス
class Camera
{
public:

    /// @brief カメラのモードを定義する列挙型
    enum class MODE
    {
        NONE,               // 指定なし
        FIXED_POINT,        // 定点カメラ
        FREE,               // フリーモード
        FOLLOW,             // 追従モード
        FOLLOW_SPRING,      // ばね付き追従モード
        FOLLOW_PERSPECTIVE, // 追従対象視点モード
        SHAKE               // カメラ揺らし
    };

    // カメラの描画域関連の定数
    static constexpr float CAMERA_SPEED = 10.0f;       // カメラスピード
    static constexpr float CAMERA_NEAR = 40.0f;        // カメラクリップ : NEAR
    static constexpr float CAMERA_FAR = 15000.0f;      // カメラクリップ : FAR

    // カメラの座標・ベクトル関連の定数
    static constexpr VECTOR DEFAULT_CAMERA_POSITION = { 0.0f, 400.0f, -500.0f };
    static constexpr VECTOR RELATIVE_CAMERA_TO_TARGET_POSITION = { 0.0f, -400.0f, 500.0f };
    static constexpr VECTOR RELATIVE_CAMERA_TO_TARGET_POSITION_PERSPECTIVE = { 0.0f, 0.0f, 200.0f };
    static constexpr VECTOR RELATIVE_FOLLOW_TO_CAMERA_POSITION = { 0.0f, 300.0f, -300.0f };

    // カメラの移動関連の定数
    static constexpr float MAX_MOVE_SPEED = 5.0f;      // 移動速度の最大値
    static constexpr float MOVE_ACCELERATION = 0.5f;   // 加速
    static constexpr float MOVE_DECELERATION = 0.5f;   // 減速

    // カメラ揺らし関連の定数
    static constexpr float SHAKE_TIME = 0.5f;          // 時間
    static constexpr float SHAKE_WIDTH = 5.0f;         // 幅
    static constexpr float SHAKE_SPEED = 40.0f;        // スピード

    /// @brief コンストラクタ
    Camera(void);

    /// @brief デストラクタ
    ~Camera(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief カメラの描画前設定
    void SetBeforeDraw(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief カメラの座標を取得する
    /// @return 現在のカメラ座標
    VECTOR GetPosition(void) const;

    /// @brief カメラモードを変更する
    /// @param mode 変更するモード
    void ChangeMode(MODE mode);

    /// @brief 追従対象を設定する
    /// @param follow 追従するTransform
    void SetFollow(const Transform* follow);

    /// @brief カメラの座標と注視点を設定する
    /// @param position カメラ座標
    /// @param targetPosition 注視点座標
    void SetPosition(const VECTOR& position, const VECTOR& targetPosition);

    /// @brief カメラの正面方向のベクトルを取得する
    /// @return 正規化された正面方向ベクトル
    VECTOR GetFrontVector(void) const;

private:

    // 追従対象のTransformポインタ
    const Transform* followTransform_; 

    // モード管理関連
    MODE mode_;                                                   // 現在のカメラモード
    MODE currentMode_;                                            // カメラ揺らし時の復帰用モード保存
    std::map<MODE, std::function<void(void)>> setBeforeDrawMode_; // 描画前処理のマップ

    // 座標・姿勢関連
    VECTOR position_;                  // カメラの位置
    VECTOR targetPosition_;            // カメラの注視点
    VECTOR cameraUp_;                  // カメラの上方向
    Quaternion rotation_;              // カメラの回転
    VECTOR defaultPosition_;           // カメラの基本座標（揺らし時などに使用）

    // 移動制御関連
    VECTOR velocity_;                  // カメラの速度（移動量）
    float moveSpeed_;                  // 現在の移動スピード
    VECTOR moveDirection_;             // 移動する向き

    // カメラ揺らし関連
    float shakeTimer_;                 // 画面揺らし用のタイマー
    VECTOR shakeDirection_;            // 揺らす方向

    // スポットライトのハンドル
    int spotLightHandle_;             

    /// @brief カメラを初期状態に戻す
    void SetDefault(void);

    /// @brief ライト設定を行う
    void SetLighting(void);

    /// @brief 定点カメラの描画前処理
    void SetBeforeDrawFixedPoint(void);

    /// @brief フリーカメラの描画前処理
    void SetBeforeDrawFree(void);

    /// @brief 追従カメラの描画前処理
    void SetBeforeDrawFollow(void);

    /// @brief ばね追従カメラの描画前処理
    void SetBeforeDrawFollowSpring(void);

    /// @brief 追従対象視点カメラの描画前処理
    void SetBeforeDrawFollowPerspective(void);

    /// @brief カメラ揺らし中の描画前処理
    void SetBeforeDrawShake(void);

    /// @brief 移動操作の入力処理
    void ProcessMove(void);

    /// @brief 移動処理
    void Move(void);

    /// @brief 加速処理
    /// @param speed 加算するスピード
    void Acceleration(float speed);

    /// @brief 減速処理
    /// @param speed 減算するスピード
    void Decelerate(float speed);
};