#include "ImageFader.h"
#include <DxLib.h>
#include "../Application.h"

void ImageFader::Draw(int imageHandle, Vector2 position, float scale,
    float angle, bool isTransparent, bool isReversed)
{
    switch (state_)
    {
    case Fader::STATE::NONE:
        return;
    case Fader::STATE::FADE_OUT:
    case Fader::STATE::FADE_IN:
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha_));

        DrawRotaGraph(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            scale,
            angle,
            imageHandle,
            isTransparent,
            isReversed
        );

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        break;
    }
}