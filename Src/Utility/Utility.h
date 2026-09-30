#pragma once

#include <string>
#include <vector>
#include <DxLib.h>

#include "../Common/Vector2.h"
#include "../Common/Quaternion.h"

/// @brief 各種ベクトル・角度・補間などのユーティリティ関数群を提供する静的クラス
class Utility
{
public:

    // 角度変換定数関連
    static constexpr float RADIAN_TO_DEGREE = (180.0f / DX_PI_F); // ラジアンから度への変換
    static constexpr float DEGREE_TO_RADIAN = (DX_PI_F / 180.0f); // 度からラジアンへの変換

    // 基本ベクトル関連
    static constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };   // ゼロベクトル
    static constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };    // 単位ベクトル

    // 回転軸ベクトル関連
    static constexpr VECTOR AXIS_X = { 1.0f, 0.0f, 0.0f };        // X軸方向
    static constexpr VECTOR AXIS_Y = { 0.0f, 1.0f, 0.0f };        // Y軸方向
    static constexpr VECTOR AXIS_Z = { 0.0f, 0.0f, 1.0f };        // Z軸方向

    // 方向ベクトル関連
    static constexpr VECTOR DIRECTION_FORWARD = { 0.0f, 0.0f, 1.0f };  // 前方 (Z+)
    static constexpr VECTOR DIRECTION_BACKWARD = { 0.0f, 0.0f, -1.0f };// 後方 (Z-)
    static constexpr VECTOR DIRECTION_RIGHT = { 1.0f, 0.0f, 0.0f };    // 右 (X+)
    static constexpr VECTOR DIRECTION_LEFT = { -1.0f, 0.0f, 0.0f };    // 左 (X-)
    static constexpr VECTOR DIRECTION_UP = { 0.0f, 1.0f, 0.0f };       // 上 (Y+)
    static constexpr VECTOR DIRECTION_DOWN = { 0.0f, -1.0f, 0.0f };    // 下 (Y-)

    /// @brief 浮動小数点の誤差比較用の最小値
    static constexpr float EPSILON_NORMAL_SQRT = 1e-15F;

    /// @brief 小数を四捨五入して整数に変換する
    /// @param value 対象の値
    /// @return 四捨五入された整数
    static int Round(float value);

    /// @brief 文字列を指定文字で分割する
    /// @param line 分割対象の文字列
    /// @param delimiter 区切り文字
    /// @return 分割された文字列の配列
    static std::vector<std::string> Split(std::string& line, char delimiter);

    /// @brief ラジアンから度（double）へ変換
    /// @param radian ラジアン角
    /// @return 度
    static double RadianToDegreeDouble(double radian);

    /// @brief 度からラジアン（float）へ変換
    /// @param radian ラジアン角
    /// @return 度
    static float RadianToDegreeFloat(float radian);

    /// @brief ラジアンから度に変換（int）
    /// @param radian ラジアン値
    /// @return 度数値
    static int RadianToDegreeInt(int radian);

    /// @brief 度からラジアンに変換（double）
    /// @param degree 度数値
    /// @return ラジアン値
    static double DegreeToRadianDouble(double degree);

    /// @brief 度からラジアンに変換（float）
    /// @param degree 度数値
    /// @return ラジアン値
    static float DegreeToRadianFloat(float degree);

    /// @brief 度からラジアンに変換（int）
    /// @param degree 度数値
    /// @return ラジアン値
    static int DegreeToRadianInt(int degree);

    /// @brief 角度を0～360に正規化
    /// @param degree 入力角度（度）
    /// @return 0～360度の範囲に正規化された角度
    static double DegreeIn360(double degree);

    /// @brief 角度を0～2πに正規化
    /// @param radian 入力角度（ラジアン）
    /// @return 0～2πの範囲に正規化された角度
    static double RadianIn2PI(double radian);

    /// @brief 回転が少ない方の方向を判定（ラジアン）
    /// @param from 開始角度（ラジアン）
    /// @param to 終了角度（ラジアン）
    /// @return 回転方向（1: 時計回り, -1: 反時計回り）
    static int DirectionNearAroundRadian(float from, float to);

    /// @brief 回転が少ない方の方向を判定（度）
    /// @param from 開始角度（度）
    /// @param to 終了角度（度）
    /// @return 回転方向（1: 時計回り, -1: 反時計回り）
    static int DirectionNearAroundDegree(float from, float to);

    /// @brief 線形補間（int）
    /// @param start 開始値
    /// @param end 終了値
    /// @param factor 補間係数（0～1）
    /// @return 補間後の値
    static int Lerp(int start, int end, float factor);

    /// @brief 線形補間（float）
    /// @param start 開始値
    /// @param end 終了値
    /// @param factor 補間係数（0～1）
    /// @return 補間後の値
    static float Lerp(float start, float end, float factor);

    /// @brief 線形補間（double）
    /// @param start 開始値
    /// @param end 終了値
    /// @param factor 補間係数（0～1）
    /// @return 補間後の値
    static double Lerp(double start, double end, double factor);

    /// @brief 線形補間（Vector2）
    /// @param start 開始ベクトル
    /// @param end 終了ベクトル
    /// @param factor 補間係数（0～1）
    /// @return 補間後のベクトル
    static Vector2 Lerp(const Vector2& start, const Vector2& end, float factor);

    /// @brief 線形補間（VECTOR）
    /// @param start 開始ベクトル
    /// @param end 終了ベクトル
    /// @param factor 補間係数（0～1）
    /// @return 補間後のベクトル
    static VECTOR Lerp(const VECTOR& start, const VECTOR& end, float factor);

    /// @brief 角度の線形補間（度）
    /// @param start 開始角度（度）
    /// @param end 終了角度（度）
    /// @param factor 補間係数（0～1）
    /// @return 補間後の角度（度）
    static double LerpDegree(double start, double end, double factor);

    /// @brief 色の線形補間
    /// @param start 開始色
    /// @param end 終了色
    /// @param factor 補間係数（0～1）
    /// @return 補間後の色
    static COLOR_F Lerp(const COLOR_F& start, const COLOR_F& end, float factor);

    /// @brief 2Dベジェ曲線（Vector2）での位置計算
    /// @param point1 開始点
    /// @param point2 中間点
    /// @param point3 終了点
    /// @param factor 補間係数（0～1）
    /// @return 補間後の位置（ベジェ曲線上）
    static Vector2 Bezier(
        const Vector2& point1,
        const Vector2& point2,
        const Vector2& point3,
        float factor
    );

    /// @brief 3Dベジェ曲線（VECTOR）での位置計算
    /// @param point1 開始点
    /// @param point2 中間点
    /// @param point3 終了点
    /// @param factor 補間係数（0～1）
    /// @return 補間後の位置（ベジェ曲線上）
    static VECTOR Bezier(
        const VECTOR& point1,
        const VECTOR& point2,
        const VECTOR& point3,
        float factor
    );

    /// @brief Y軸を中心としたXZ平面での回転座標を求める
    /// @param centerPosition 回転中心位置
    /// @param radiusPosition 回転させる対象の位置
    /// @param radian 回転角度（ラジアン）
    /// @return 回転後の位置
    static VECTOR RotateXZPosition(
        const VECTOR& centerPosition,
        const VECTOR& radiusPosition,
        float radian
    );

    /// @brief ベクトルの長さ（2D）
    /// @param vector 対象のベクトル（2D）
    /// @return ベクトルの長さ
    static double Magnitude(const Vector2& vector);

    /// @brief ベクトルの長さ（3D）
    /// @param vector 対象のベクトル（3D）
    /// @return ベクトルの長さ
    static double Magnitude(const VECTOR& vector);

    /// @brief ベクトルの長さ（3D・float版）
    /// @param vector 対象のベクトル（3D）
    /// @return ベクトルの長さ
    static float MagnitudeF(const VECTOR& vector);

    /// @brief ベクトルの長さの2乗（2D）
    /// @param vector 対象のベクトル（2D）
    /// @return ベクトルの長さの2乗
    static int SqrMagnitude(const Vector2& vector);

    /// @brief ベクトルの長さの2乗（3D・float版）
    /// @param vector 対象のベクトル（3D）
    /// @return ベクトルの長さの2乗
    static float SqrMagnitudeF(const VECTOR& vector);

    /// @brief ベクトルの長さの2乗（3D）
    /// @param vector 対象のベクトル（3D）
    /// @return ベクトルの長さの2乗
    static double SqrMagnitude(const VECTOR& vector);

    /// @brief 2点間の距離の2乗（3D）
    /// @param vector1 開始ベクトル（3D）
    /// @param vector2 終了ベクトル（3D）
    /// @return 2点間の距離の2乗
    static double SqrMagnitude(const VECTOR& vector1, const VECTOR& vector2);

    /// @brief 2点間の距離（2D）
    /// @param vector1 開始ベクトル（2D）
    /// @param vector2 終了ベクトル（2D）
    /// @return 2点間の距離
    static double Distance(const Vector2& vector1, const Vector2& vector2);

    /// @brief 2点間の距離（3D）
    /// @param vector1 開始ベクトル（3D）
    /// @param vector2 終了ベクトル（3D）
    /// @return 2点間の距離
    static double Distance(const VECTOR& vector1, const VECTOR& vector2);

    /// @brief 2つのベクトルが等しいかを比較する
    /// @param vector1 比較するベクトル1
    /// @param vector2 比較するベクトル2
    /// @return 等しい場合はtrue、それ以外はfalse
    static bool Equals(const VECTOR& vector1, const VECTOR& vector2);

    /// @brief ベクトルがゼロベクトルかを判定する
    /// @param vector 対象のベクトル
    /// @return ゼロベクトルならtrue、それ以外はfalse
    static bool EqualsVZero(const VECTOR& vector);

    /// @brief ベクトルを正規化（2D→3D変換含む）
    /// @param vector 対象の2Dベクトル
    /// @return 正規化された3Dベクトル
    static VECTOR Normalize(const Vector2& vector);

    /// @brief ベクトルを正規化（3D）
    /// @param vector 対象の3Dベクトル
    /// @return 正規化された3Dベクトル
    static VECTOR VNormalize(const VECTOR& vector);

    /// @brief 2つのベクトルの間の角度（度）を返す
    /// @param fromVector 開始ベクトル
    /// @param toVector 終了ベクトル
    /// @return ベクトル間の角度（度）
    static double AngleDegree(const VECTOR& fromVector, const VECTOR& toVector);

    /// @brief 指定位置から方向ベクトルに向けて線を描画する
    /// @param position 開始位置
    /// @param direction 方向ベクトル
    /// @param color 色（DxLibの色コード）
    /// @param length 線の長さ（デフォルトは50.0f）
    static void DrawLineDirection(
        const VECTOR& position,
        const VECTOR& direction,
        int color,
        float length = 50.0f
    );

    /// @brief 指定位置から回転行列の軸方向に線を描画する
    /// @param position 開始位置
    /// @param rotation 回転行列
    /// @param length 線の長さ（デフォルトは50.0f）
    static void DrawLineXYZ(const VECTOR& position, const MATRIX& rotation, float length = 50.0f);

    /// @brief 指定位置からクォータニオンの軸方向に線を描画する
    /// @param position 開始位置
    /// @param rotation クォータニオン回転
    /// @param length 線の長さ（デフォルトは50.0f）
    static void DrawLineXYZ(
        const VECTOR& position,
        const Quaternion& rotation,
        float length = 50.0f
    );

    /// @brief 待機時間を超過しているか判断する
    /// @param totalTime 経過時間の合計
    /// @param waitTime 待機時間
    /// @return 時間を超過していればtrue
    static bool IsTimeOver(float& totalTime, const float& waitTime);
};