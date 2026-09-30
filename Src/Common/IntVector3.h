#pragma once
#include <DxLib.h>

/// @brief 整数の3次元ベクトルを表すクラス
class IntVector3
{
public:
    // 座標関連
    int x; // x座標
    int y; // y座標
    int z; // z座標

    /// @brief ゼロベクトルで初期化するコンストラクタ
    IntVector3(void);

    /// @brief 指定した3つの値で初期化するコンストラクタ
    /// @param valueX X成分
    /// @param valueY Y成分
    /// @param valueZ Z成分
    IntVector3(int valueX, int valueY, int valueZ);

    /// @brief DxLibのVECTOR構造体から初期化するコンストラクタ
    /// @param vector VECTOR型のベクトル
    /// @return なし
    IntVector3(VECTOR vector);

    /// @brief デストラクタ
    /// @param void 
    /// @return なし
    ~IntVector3(void);

    /// @brief 辞書順比較を行う演算子。主にstd::setなどでの順序付けに使用。
    /// @param value 比較対象のIntVector3
    /// @return this が value より小さい場合 true
    bool operator<(const IntVector3& value) const;

    /// @brief 全ての要素に整数値を加算する
    /// @param value 加算する整数値
    /// @return なし
    void Add(int value);

    /// @brief 全ての要素から整数値を減算する
    /// @param value 減算する整数値
    /// @return なし
    void Sub(int value);

    /// @brief 全ての要素を整数値でスケーリング（乗算）する
    /// @param value スケーリング係数
    /// @return なし
    void Scale(int value);
};