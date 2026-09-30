#pragma once
#include "Fader.h"
#include "Vector2.h"

/// @brief 画像のフェードイン／フェードアウト描画を担当するクラス
class ImageFader : public Fader
{
public:

    /// @brief 指定された画像を画面上に描画します。位置、スケール、回転角度、透過、反転の各パラメータを指定できます。
    /// @param imageHandle 描画する画像のリソースID（ハンドル）
    /// @param position 画像の描画位置（2Dベクトル）
    /// @param scale 画像のスケール（1.0 は元のサイズ）
    /// @param angle 画像の回転角度（ラジアン単位）
    /// @param isTransparent 透過処理を行うかどうか
    /// @param isReversed 画像を左右反転させるかどうか
    /// @return なし
    void Draw(int imageHandle, Vector2 position, float scale, float angle, bool isTransparent, bool isReversed);
};