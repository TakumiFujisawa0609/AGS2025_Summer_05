#include "Fader.h"
#include <DxLib.h>
#include "../Application.h"

Fader::STATE Fader::GetState(void) const
{
    return state_;
}

bool Fader::IsEnd(void) const
{
    return isEnd_;
}

void Fader::SetFade(STATE state)
{
    state_ = state;
    if (state_ != STATE::NONE)
    {
        isPreEnd_ = false;
        isEnd_ = false;
    }
}

void Fader::SetAlpha(float alpha)
{
    alphaMax_ = alpha;
}

void Fader::Init(void)
{
    state_ = STATE::NONE;
    alpha_ = 0.0f;
    alphaMax_ = 0.0f;
    isPreEnd_ = true;
    isEnd_ = true;

    temporaryScene_ = MakeScreen(
        Application::FULL_SCREEN_SIZE_X,
        Application::FULL_SCREEN_SIZE_Y,
        true
    );
}

void Fader::Update(void)
{
    if (isEnd_ == true)
    {
        return;
    }

    switch (state_)
    {
    case STATE::NONE:
    case STATE::FADE_KEEP:
        return;

    case STATE::FADE_OUT:
        alpha_ += SPEED_ALPHA;
        if (alpha_ > ALPHA_MAX)
        {
            alpha_ = ALPHA_MAX;
            if (isPreEnd_ == true)
            {
                isEnd_ = true;
            }
            isPreEnd_ = true;
        }
        break;

    case STATE::FADE_IN:
        alpha_ -= SPEED_SCENE;
        if (alpha_ < 0.0f)
        {
            alpha_ = 0.0f;
            if (isPreEnd_ == true)
            {
                isEnd_ = true;
            }
            isPreEnd_ = true;
        }
        break;

    case STATE::SET_FADE_OUT:
        alpha_ += SPEED_ALPHA;
        if (alpha_ > alphaMax_)
        {
            alpha_ = LITTLE_ALPHA;
            if (isPreEnd_ == true)
            {
                isEnd_ = true;
            }
            isPreEnd_ = true;
        }
        break;

    default:
        return;
    }
}

void Fader::Draw(void)
{
    switch (state_)
    {
    case STATE::NONE:
        return;
    case STATE::FADE_KEEP:
    case STATE::SET_FADE_OUT:
    case STATE::FADE_OUT:
    case STATE::FADE_IN:
        CircleMask();
        break;
    }
}

void Fader::CircleMask(void)
{
    SetDrawScreen(temporaryScene_);

    DrawBox(
        0, 0,
        Application::FULL_SCREEN_SIZE_X,
        Application::FULL_SCREEN_SIZE_Y,
        0x000000, true
    );

    DrawCircle(
        (Application::FULL_SCREEN_SIZE_X / 2),
        Application::FULL_SCREEN_SIZE_Y / 2,
        static_cast<int>((ALPHA_MAX - alpha_) * 4),
        0xffffff, true
    );

    SetDrawScreen(DX_SCREEN_BACK);

    SetDrawBlendMode(DX_BLENDMODE_MUL, 0);

    DrawGraph(0, 0, temporaryScene_, false);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}