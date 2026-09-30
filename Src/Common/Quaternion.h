#pragma once

#include <DxLib.h>
#include <iostream>
#include <algorithm>

/// @brief 回転を表現するためのクォータニオンクラス
class Quaternion
{
public:

    /// @brief 正規化時の極小値（ゼロ割防止）
    static constexpr float kEpsilonNormalSqrt = 1e-15f;

    // クォータニオン成分
    double w; // クォータニオンのスカラー成分（回転量の余弦）
    double x; // クォータニオンのX成分（ベクトル部）
    double y; // クォータニオンのY成分（ベクトル部）
    double z; // クォータニオンのZ成分（ベクトル部）

    /// @brief デフォルトコンストラクタ
    Quaternion(void);

    /// @brief オイラー角（ラジアン）から初期化
    /// @param radian X, Y, Z軸の回転角
    /// @return なし
    Quaternion(const VECTOR& radian);

    /// @brief 各成分から初期化
    /// @param scalar スカラー成分
    /// @param vectorX X軸成分
    /// @param vectorY Y軸成分
    /// @param vectorZ Z軸成分
    /// @return なし
    Quaternion(double scalar, double vectorX, double vectorY, double vectorZ);

    /// @brief デストラクタ
    ~Quaternion(void);

    /// @brief オイラー角からクォータニオンを生成
    /// @param radian 各軸の回転角
    /// @return 生成されたクォータニオン
    static Quaternion Euler(const VECTOR& radian);

    /// @brief XYZ各軸からクォータニオンを生成
    /// @param radianX X軸角度
    /// @param radianY Y軸角度
    /// @param radianZ Z軸角度
    /// @return 生成されたクォータニオン
    static Quaternion Euler(double radianX, double radianY, double radianZ);

    /// @brief 2つのクォータニオンを合成
    /// @param quaternion1 第1クォータニオン
    /// @param quaternion2 第2クォータニオン
    /// @return 合成されたクォータニオン
    static Quaternion Mult(const Quaternion& quaternion1, const Quaternion& quaternion2);

    /// @brief 現在のクォータニオンと指定クォータニオンを合成
    /// @param quaternion 合成相手のクォータニオン
    /// @return 合成されたクォータニオン
    Quaternion Mult(const Quaternion& quaternion) const;

    /// @brief 指定軸・角度の回転を表すクォータニオンを生成
    /// @param radian 回転角
    /// @param axis 回転軸ベクトル
    /// @return 生成されたクォータニオン
    static Quaternion AngleAxis(double radian, VECTOR axis);

    /// @brief ベクトルを回転させる（静的）
    /// @param quaternion 回転クォータニオン
    /// @param axis 回転対象ベクトル
    /// @return 回転後のベクトル
    static VECTOR PosAxis(const Quaternion& quaternion, VECTOR axis);

    /// @brief ベクトルを回転させる（メンバ）
    /// @param position 回転対象ベクトル
    /// @return 回転後のベクトル
    VECTOR PosAxis(VECTOR position) const;

    /// @brief クォータニオンからオイラー角に変換（静的）
    /// @param quaternion 変換対象
    /// @return オイラー角
    static VECTOR ToEuler(const Quaternion& quaternion);

    /// @brief クォータニオンからオイラー角に変換（メンバ）
    /// @param void
    /// @return オイラー角
    VECTOR ToEuler(void) const;

    /// @brief クォータニオンを回転行列に変換（静的）
    /// @param quaternion 変換対象
    /// @return 回転行列
    static MATRIX ToMatrix(const Quaternion& quaternion);

    /// @brief クォータニオンを回転行列に変換（メンバ）
    /// @param void 
    /// @return 回転行列
    MATRIX ToMatrix(void) const;

    /// @brief 方向ベクトルからクォータニオンを生成（前方向のみ）
    /// @param direction 向く方向
    /// @return 生成されたクォータニオン
    static Quaternion LookRotation(VECTOR direction);

    /// @brief 方向ベクトルからクォータニオンを生成（前方向と上方向を指定）
    /// @param direction 向く方向
    /// @param up 上方向
    /// @return 生成されたクォータニオン
    static Quaternion LookRotation(VECTOR direction, VECTOR up);

    /// @brief 行列から回転クォータニオンを抽出
    /// @param matrix 回転行列
    /// @return 抽出されたクォータニオン
    static Quaternion GetRotation(MATRIX matrix);

    /// @brief 前方向ベクトルを取得
    /// @param void 
    /// @return 前方向ベクトル
    VECTOR GetForward(void) const;

    /// @brief 後方向ベクトルを取得
    /// @param void 
    /// @return 後方向ベクトル
    VECTOR GetBack(void) const;

    /// @brief 右方向ベクトルを取得
    /// @param void 
    /// @return 右方向ベクトル
    VECTOR GetRight(void) const;

    /// @brief 左方向ベクトルを取得
    /// @param void 
    /// @return 左方向ベクトル
    VECTOR GetLeft(void) const;

    /// @brief 上方向ベクトルを取得
    /// @param void 
    /// @return 上方向ベクトル
    VECTOR GetUp(void) const;

    /// @brief 下方向ベクトルを取得
    /// @param void 
    /// @return 下方向ベクトル
    VECTOR GetDown(void) const;

    /// @brief クォータニオンの内積を計算
    /// @param quaternion1 第1クォータニオン
    /// @param quaternion2 第2クォータニオン
    /// @return 内積値
    static double Dot(const Quaternion& quaternion1, const Quaternion& quaternion2);

    /// @brief 現在のクォータニオンと別のクォータニオンとの内積
    /// @param quaternion 比較対象
    /// @return 内積値
    double Dot(const Quaternion& quaternion) const;

    /// @brief クォータニオンを正規化（静的）
    /// @param quaternion 正規化対象
    /// @return 正規化されたクォータニオン
    static Quaternion Normalize(const Quaternion& quaternion);

    /// @brief 正規化されたクォータニオンを返す（非破壊）
    /// @param void 
    /// @return 正規化されたクォータニオン
    Quaternion Normalized(void) const;

    /// @brief クォータニオンを正規化（破壊的）
    /// @param void 
    /// @return なし
    void Normalize(void);

    /// @brief 逆クォータニオン（共役）を返す
    /// @param void 
    /// @return 逆クォータニオン
    Quaternion Inverse(void) const;

    /// @brief 球面線形補間（Slerp）
    /// @param from 開始回転
    /// @param to 終了回転
    /// @param ratio 補間率（0.0～1.0）
    /// @return 補間されたクォータニオン
    static Quaternion Slerp(Quaternion from, Quaternion to, double ratio);

    /// @brief fromからtoへの回転を取得
    /// @param fromDirection 開始方向
    /// @param toDirection 目標方向
    /// @return 回転を表すクォータニオン
    static Quaternion FromToRotation(VECTOR fromDirection, VECTOR toDirection);

    /// @brief 最大角度制限付きの回転補間
    /// @param from 現在の回転
    /// @param to 目標回転
    /// @param maxDegreesDelta 最大回転角（度）
    /// @return 補間されたクォータニオン
    static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);

    /// @brief 2つのクォータニオンの角度差を計算
    /// @param quaternion1 クォータニオン1
    /// @param quaternion2 クォータニオン2
    /// @return 角度差（度）
    static double Angle(const Quaternion& quaternion1, const Quaternion& quaternion2);

    /// @brief 補間率を制限しないSlerp
    /// @param from 開始クォータニオン
    /// @param to 終了クォータニオン
    /// @param ratio 補間係数
    /// @return 補間されたクォータニオン
    static Quaternion SlerpUnclamped(Quaternion from, Quaternion to, float ratio);

    /// @brief 単位クォータニオン（回転なし）を取得
    /// @param void 
    /// @return 単位クォータニオン
    static Quaternion Identity(void);

    /// @brief クォータニオンの長さを取得
    /// @param void 
    /// @return 長さ
    double Length(void) const;

    /// @brief クォータニオンの長さの2乗を取得
    /// @param void 
    /// @return 長さの2乗
    double LengthSquared(void) const;

    /// @brief x, y, z 成分をベクトルで取得
    /// @param void 
    /// @return x, y, z成分を持つベクトル
    VECTOR xyz(void) const;

    /// @brief クォータニオンを角度と軸に分解
    /// @param angle 抽出された角度（ラジアン）
    /// @param axis 抽出された回転軸
    /// @return なし
    void ToAngleAxis(float* angle, VECTOR* axis);

private:

    /// @brief 指定方向のベクトルを現在の回転で回す
    /// @param direction 方向ベクトル
    /// @return 回転後の方向ベクトル
    VECTOR GetDir(VECTOR direction) const;

    /// @brief スカラー乗算（破壊的）
    /// @param rhs 係数
    /// @return 乗算後のクォータニオン
    Quaternion operator*(float& rhs);

    /// @brief スカラー乗算（非破壊）
    /// @param rhs 係数
    /// @return 乗算後のクォータニオン
    const Quaternion operator*(const float& rhs);

    /// @brief 加算（破壊的）
    /// @param rhs 加算対象
    /// @return 加算後のクォータニオン
    Quaternion operator+(Quaternion& rhs);

    /// @brief 加算（非破壊）
    /// @param rhs 加算対象
    /// @return 加算後のクォータニオン
    const Quaternion operator+(const Quaternion& rhs);
};