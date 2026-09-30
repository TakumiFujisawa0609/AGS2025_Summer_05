#pragma once

#include <DxLib.h>

// 数学関連
constexpr float HALF_DIVISOR = 2.0f;                        // 半分にするための除数
constexpr float QUARTER_DIVISOR = 4.0f;                     // 4分割用の除数
constexpr float HALF_MULTIPLIER = 0.5f;                     // 半分にするための乗数
constexpr float CIRCLE_RADIANS = 2.0f * DX_PI_F;            // 360度のラジアン値
constexpr float HALF_PI_RADIANS = DX_PI_F * 90.0f / 180.0f; // 90度のラジアン値

// 指数関数関連
constexpr float EXPONENTIAL_BASE = 2.0f;					// 指数関数の底
constexpr float EXPONENTIAL_POWER = 10.0f;                  // 指数関数の乗数

// 弾性関数関連
constexpr float ELASTIC_DEFAULT_OVERSHOOT = 1.70158f;			// デフォルトの助走量
constexpr float ELASTIC_DEFAULT_PERIOD_MULTIPLIER = 0.3f;		// デフォルトの周期乗数
constexpr float ELASTIC_INOUT_PERIOD_MULTIPLIER = 0.3f * 1.5f;	// InOutの周期乗数

// バック関数関連
constexpr float BACK_INOUT_OVERSHOOT_MULTIPLIER = 1.525f;   // 助走量の乗数

// バウンド関数関連
constexpr float BOUNCE_COEFFICIENT = 7.5625f;							// バウンドの係数
constexpr float BOUNCE_DENOMINATOR = 2.75f;								// バウンドの分母
constexpr float BOUNCE_THRESHOLD_FIRST = 1.0f / BOUNCE_DENOMINATOR;		// 1回目のバウンドのしきい値
constexpr float BOUNCE_THRESHOLD_SECOND = 2.0f / BOUNCE_DENOMINATOR;	// 2回目のバウンドのしきい値
constexpr float BOUNCE_THRESHOLD_THIRD = 2.5f / BOUNCE_DENOMINATOR;		// 3回目のバウンドのしきい値
constexpr float BOUNCE_OFFSET_TIME_SECOND = 1.5f / BOUNCE_DENOMINATOR;  // 2回目のバウンドの時間オフセット
constexpr float BOUNCE_OFFSET_TIME_THIRD = 2.25f / BOUNCE_DENOMINATOR;	// 3回目のバウンドの時間オフセット
constexpr float BOUNCE_OFFSET_TIME_FOURTH = 2.625f / BOUNCE_DENOMINATOR;// 4回目のバウンドの時間オフセット
constexpr float BOUNCE_OFFSET_VALUE_SECOND = 0.75f;                     // 2回目のバウンドの値オフセット
constexpr float BOUNCE_OFFSET_VALUE_THIRD = 0.9375f;                    // 3回目のバウンドの値オフセット
constexpr float BOUNCE_OFFSET_VALUE_FOURTH = 0.984375f;                 // 4回目のバウンドの値オフセット

/// @brief 二次関数的なイージング。開始時に遅く、後半で速くなる加速
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuadIn(float time, float totalTime, float start, float end);

/// @brief 二次関数的なイージング。最初は速く、終わりに向かって減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuadOut(float time, float totalTime, float start, float end);

/// @brief 二次関数的なイージング。最初に加速し、最後に減速する（加速と減速の両方を含む）
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuadInOut(float time, float totalTime, float start, float end);

/// @brief 三次関数的なイージング。開始時に非常にゆっくり、後半で速くなる
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float CubicIn(float time, float totalTime, float start, float end);

/// @brief 三次関数的なイージング。最初は速く、後で減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float CubicOut(float time, float totalTime, float start, float end);

/// @brief 三次関数的なイージング。加速と減速の両方がある
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float CubicInOut(float time, float totalTime, float start, float end);

/// @brief 四次関数的なイージング。開始時に非常にゆっくり、後半で急激に加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuartIn(float time, float totalTime, float start, float end);

/// @brief 四次関数的なイージング。最初は速く、終わりに向かって急激に減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuartOut(float time, float totalTime, float start, float end);

/// @brief 四次関数的なイージング。加速と減速が両方ある
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuartInOut(float time, float totalTime, float start, float end);

/// @brief 五次関数的なイージングで最初は非常にゆっくり始まり後半で急激に加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuintIn(float time, float totalTime, float start, float end);

/// @brief 五次関数的なイージングで最初は速く後半に向かって滑らかに減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuintOut(float time, float totalTime, float start, float end);

/// @brief 五次関数的なイージングで最初は滑らかに加速し中盤で最速になり後半に向かって滑らかに減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float QuintInOut(float time, float totalTime, float start, float end);

/// @brief サイン関数的なイージング。最初に非常に遅く始まり、後半で急速に加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float SineIn(float time, float totalTime, float start, float end);

/// @brief サイン関数的なイージング。最初は速く、終わりに向かって急激に減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float SineOut(float time, float totalTime, float start, float end);

/// @brief サイン関数的なイージング。加速と減速が両方含まれており、サイン波のように滑らかに変化する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float SineInOut(float time, float totalTime, float start, float end);

/// @brief 指数関数的なイージング。最初は非常に遅く、後半で急激に加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float ExpIn(float time, float totalTime, float start, float end);

/// @brief 指数関数的なイージング。最初は速く、後半で急激に減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float ExpOut(float time, float totalTime, float start, float end);

/// @brief 指数関数的なイージング。加速と減速が両方含まれ、急激に変化する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float ExpInOut(float time, float totalTime, float start, float end);

/// @brief 円関数的なイージング。最初は遅く、後半で急激に加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float CircIn(float time, float totalTime, float start, float end);

/// @brief 円関数的なイージング。最初は速く、終わりに向かって減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float CircOut(float time, float totalTime, float start, float end);

/// @brief 円関数的なイージング。加速と減速の両方があり、円形のようにスムーズな動きを持つ
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float CircInOut(float time, float totalTime, float start, float end);

/// @brief 弾性関数的なイージング。最初はゆっくり始まり、途中で反発して加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float ElasticIn(float time, float totalTime, float start, float end);

/// @brief 弾性関数的なイージング。最初は速く、後半に反発しながら減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float ElasticOut(float time, float totalTime, float start, float end);

/// @brief 弾性関数的なイージング。加速と減速の間に弾性効果を含んだ動き
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float ElasticInOut(float time, float totalTime, float start, float end);

/// @brief バック関数的なイージング。最初に少し逆方向に動き、その後加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @param overshootAmount 助走量
/// @return 計算されたイージング値
float BackIn(float time, float totalTime, float start, float end, float overshootAmount);

/// @brief バック関数的なイージング。最初は速く、後半に少し逆方向に動いて減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @param overshootAmount 助走量
/// @return 計算されたイージング値
float BackOut(float time, float totalTime, float start, float end, float overshootAmount);

/// @brief バック関数的なイージング。加速と減速の両方があり、バック関数の特徴を含んでいる
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @param overshootAmount 助走量
/// @return 計算されたイージング値
float BackInOut(float time, float totalTime, float start, float end, float overshootAmount);

/// @brief バウンド関数的なイージング。最初に跳ねるような動きで加速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float BounceIn(float time, float totalTime, float start, float end);

/// @brief バウンド関数的なイージング。最初は速く、跳ねるように減速する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float BounceOut(float time, float totalTime, float start, float end);

/// @brief バウンド関数的なイージング。加速と減速が両方あり、跳ねる動きがある
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float BounceInOut(float time, float totalTime, float start, float end);

/// @brief 線形補間。加速も減速もなく、一定の速度で直線的に変化する
/// @param time 現在の時間（開始からの経過時間）
/// @param totalTime 全体の時間（アニメーションの総時間）
/// @param start 開始時の値
/// @param end 終了時の値
/// @return 計算されたイージング値
float Linear(float time, float totalTime, float start, float end);