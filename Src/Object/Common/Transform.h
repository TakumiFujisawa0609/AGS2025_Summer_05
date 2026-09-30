#pragma once

#include <DxLib.h>

#include "../../Common/Quaternion.h"

/// @brief モデル制御の基本情報
/// 大きさ：VECTOR基準
/// 回転 ：Quaternion基準
/// 位置 ：VECTOR基準
class Transform
{
public:

    /// @brief デフォルトコンストラクタ
    Transform(void);

    /// @brief モデルを指定するコンストラクタ
    /// @param modelHandleId モデルのハンドルID
    Transform(int modelHandleId);

    /// @brief デストラクタ
    ~Transform(void);

    // モデルのハンドルID
    int modelId;

    // 基本ベクトル情報関連
    VECTOR scale;                       // 大きさ
    VECTOR rotation;                    // 回転（オイラー角）
    VECTOR position;                    // 位置
    VECTOR localPosition;               // ローカル位置

    // 行列情報関連
    MATRIX matrixScale;                 // 大きさの行列
    MATRIX matrixRotation;              // 回転の行列
    MATRIX matrixPosition;              // 位置の行列

    // クォータニオン情報関連
    Quaternion quaternionRotation;      // 回転
    Quaternion quaternionRotationLocal; // ローカル回転

    /// @brief モデル制御の基本情報更新
    void Update(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief モデルの設定
    /// @param modelHandleId モデルのハンドルID
    void SetModel(int modelHandleId);

    /// @brief 前方方向を取得
    /// @return 前方方向のベクトル
    VECTOR GetForward(void) const;

    /// @brief 後方方向を取得
    /// @return 後方方向のベクトル
    VECTOR GetBack(void) const;

    /// @brief 右方向を取得
    /// @return 右方向のベクトル
    VECTOR GetRight(void) const;

    /// @brief 左方向を取得
    /// @return 左方向のベクトル
    VECTOR GetLeft(void) const;

    /// @brief 上方向を取得
    /// @return 上方向のベクトル
    VECTOR GetUp(void) const;

    /// @brief 下方向を取得
    /// @return 下方向のベクトル
    VECTOR GetDown(void) const;

    /// @brief 対象方向を取得
    /// @param targetVector 基準となるベクトル
    /// @return 回転後の対象方向ベクトル
    VECTOR GetDirection(const VECTOR& targetVector) const;
};