#include "FpsControll.h"

#include <math.h>
#include <DxLib.h>

Fps::Fps(void)
    : startTime_(0), frameCount_(0), currentFps_(0.0f)
{
}

Fps::~Fps(void)
{
}

void Fps::FpsControll_Initialize(void)
{
    startTime_ = GetNowCount();
    frameCount_ = 0;
    currentFps_ = 0.0f;
}

bool Fps::FpsControll_Update(void)
{
    if (frameCount_ == 0)
    {
        startTime_ = GetNowCount();
    }

    if (frameCount_ == SAMPLE_COUNT)
    {
        const float MILLISECONDS_PER_SECOND = 1000.0f;

        int currentTime = GetNowCount();

        // 100文字を超えないように計算式を改行
        currentFps_ = MILLISECONDS_PER_SECOND /
            ((currentTime - startTime_) / static_cast<float>(SAMPLE_COUNT));

        frameCount_ = 0;
        startTime_ = currentTime;
    }

    frameCount_++;

    return true;
}

void Fps::FpsControll_Draw(void)
{
    const int DRAW_POSITION_X = 0;             // 描画位置X座標
    const int DRAW_POSITION_Y = 0;             // 描画位置Y座標
    const unsigned int COLOR_WHITE = 0xffffff; // 描画色（白色）

    DrawFormatString(DRAW_POSITION_X, DRAW_POSITION_Y, COLOR_WHITE, "%.1f", currentFps_);
}

void Fps::FpsControll_Wait(void)
{
    const int MILLISECONDS_PER_SECOND = 1000; // 1秒間のミリ秒数

    int tookTime = GetNowCount() - startTime_;                                    // かかった時間
    int waitTime = frameCount_ * MILLISECONDS_PER_SECOND / TARGET_FPS - tookTime; // 待つべき時間

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}