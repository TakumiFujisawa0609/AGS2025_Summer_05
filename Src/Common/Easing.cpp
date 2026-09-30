#include "Easing.h"
#include <cmath>

float QuadIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return -difference * ratio * ratio + start;
}

float QuadOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return -difference * ratio * (ratio - HALF_DIVISOR) + start;
}

float QuadInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    if (ratio < 1.0f)
    {
        return difference / HALF_DIVISOR * ratio * ratio + start;
    }

    ratio = ratio - 1.0f;

    return -difference / HALF_DIVISOR * (ratio * (ratio - HALF_DIVISOR) - 1.0f) + start;
}

float CubicIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return difference * ratio * ratio * ratio * ratio * ratio + start;
}

float CubicOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;         // •Ï‰»—Ê
    float ratio = time / totalTime - 1.0f;  // Š„‡

    return difference * (ratio * ratio * ratio + 1.0f) + start;
}

float CubicInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    if (ratio < 1.0f)
    {
        return difference / HALF_DIVISOR * ratio * ratio * ratio + start;
    }

    ratio = ratio - HALF_DIVISOR;

    return difference / HALF_DIVISOR * (ratio * ratio * ratio + HALF_DIVISOR) + start;
}

float QuartIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return difference * ratio * ratio * ratio * ratio + start;
}

float QuartOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;         // •Ï‰»—Ê
    float ratio = time / totalTime - 1.0f;  // Š„‡

    return -difference * (ratio * ratio * ratio * ratio - 1.0f) + start;
}

float QuartInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    if (ratio < 1.0f)
    {
        return difference / HALF_DIVISOR * ratio * ratio * ratio * ratio + start;
    }

    ratio = ratio - HALF_DIVISOR;

    return -difference / HALF_DIVISOR * (ratio * ratio * ratio * ratio - HALF_DIVISOR) + start;
}

float QuintIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return difference * ratio * ratio * ratio * ratio * ratio + start;
}

float QuintOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;         // •Ï‰»—Ê
    float ratio = time / totalTime - 1.0f;  // Š„‡

    return difference * (ratio * ratio * ratio * ratio * ratio + 1.0f) + start;
}

float QuintInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    if (ratio < 1.0f)
    {
        return difference / HALF_DIVISOR * ratio * ratio * ratio * ratio * ratio + start;
    }

    ratio = ratio - HALF_DIVISOR;

    return difference / HALF_DIVISOR * (ratio * ratio * ratio * ratio * ratio + HALF_DIVISOR) + start;
}

float SineIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    return -difference * cos(time * HALF_PI_RADIANS / totalTime) + difference + start;
}

float SineOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    return difference * sin(time * HALF_PI_RADIANS / totalTime) + start;
}

float SineInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    return -difference / HALF_DIVISOR * (cos(time * DX_PI_F / totalTime) - 1.0f) + start;
}

float ExpIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    if (time == 0.0f)
    {
        return start;
    }

    return difference * powf(EXPONENTIAL_BASE, EXPONENTIAL_POWER * (time / totalTime - 1.0f)) + start;
}

float ExpOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    if (time == totalTime)
    {
        return end + start;
    }

    return difference * (-powf(EXPONENTIAL_BASE, -EXPONENTIAL_POWER * time / totalTime) + 1.0f) + start;
}

float ExpInOut(float time, float totalTime, float start, float end)
{
    if (time == 0.0f)
    {
        return start;
    }
    if (time == totalTime)
    {
        return end;
    }

    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    if (ratio < 1.0f)
    {
        return difference / HALF_DIVISOR * powf(EXPONENTIAL_BASE, EXPONENTIAL_POWER * (ratio - 1.0f)) + start;
    }

    ratio = ratio - 1.0f;

    return difference / HALF_DIVISOR * (-powf(EXPONENTIAL_BASE, -EXPONENTIAL_POWER * ratio) + HALF_DIVISOR) + start;
}

float CircIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return -difference * (sqrt(1.0f - ratio * ratio) - 1.0f) + start;
}

float CircOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;         // •Ï‰»—Ê
    float ratio = time / totalTime - 1.0f;  // Š„‡

    return difference * sqrt(1.0f - ratio * ratio) + start;
}

float CircInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    if (ratio < 1.0f)
    {
        return -difference / HALF_DIVISOR * (sqrt(1.0f - ratio * ratio) - 1.0f) + start;
    }

    ratio = ratio - HALF_DIVISOR;

    return difference / HALF_DIVISOR * (sqrt(1.0f - ratio * ratio) + 1.0f) + start;
}

float ElasticIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    float overshoot = ELASTIC_DEFAULT_OVERSHOOT;                  // •‘–—Ê
    float period = totalTime * ELASTIC_DEFAULT_PERIOD_MULTIPLIER; // üŠú
    float amplitude = difference;                                 // U•

    if (ratio == 0.0f)
    {
        return start;
    }
    if (ratio == 1.0f)
    {
        return start + difference;
    }

    if (amplitude < abs(difference))
    {
        amplitude = difference;
        overshoot = period / QUARTER_DIVISOR;
    }
    else
    {
        overshoot = period / CIRCLE_RADIANS * asin(difference / amplitude);
    }

    ratio = ratio - 1.0f;
    return -(amplitude * powf(EXPONENTIAL_BASE, EXPONENTIAL_POWER * ratio) * sin((ratio * totalTime - overshoot) * CIRCLE_RADIANS / period)) + start;
}

float ElasticOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    float overshoot = ELASTIC_DEFAULT_OVERSHOOT;                  // •‘–—Ê
    float period = totalTime * ELASTIC_DEFAULT_PERIOD_MULTIPLIER; // üŠú
    float amplitude = difference;                                 // U•

    if (ratio == 0.0f)
    {
        return start;
    }
    if (ratio == 1.0f)
    {
        return start + difference;
    }

    if (amplitude < abs(difference))
    {
        amplitude = difference;
        overshoot = period / QUARTER_DIVISOR;
    }
    else
    {
        overshoot = period / CIRCLE_RADIANS * asin(difference / amplitude);
    }

    return amplitude * powf(EXPONENTIAL_BASE, -EXPONENTIAL_POWER * ratio) * sin((ratio * totalTime - overshoot) * CIRCLE_RADIANS / period) + difference + start;
}

float ElasticInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;                  // •Ï‰»—Ê
    float ratio = time / (totalTime / HALF_DIVISOR); // Š„‡

    float overshoot = ELASTIC_DEFAULT_OVERSHOOT;                  // •‘–—Ê
    float period = totalTime * ELASTIC_INOUT_PERIOD_MULTIPLIER;   // üŠú
    float amplitude = difference;                                 // U•

    if (ratio == 0.0f)
    {
        return start;
    }
    if (ratio == HALF_DIVISOR)
    {
        return start + difference;
    }

    if (amplitude < abs(difference))
    {
        amplitude = difference;
        overshoot = period / QUARTER_DIVISOR;
    }
    else
    {
        overshoot = period / CIRCLE_RADIANS * asin(difference / amplitude);
    }

    if (ratio < 1.0f)
    {
        ratio -= 1.0f;
        return -HALF_MULTIPLIER * (amplitude * powf(EXPONENTIAL_BASE, EXPONENTIAL_POWER * ratio) * sin((ratio * totalTime - overshoot) * CIRCLE_RADIANS / period)) + start;
    }

    ratio = ratio - 1.0f;

    return amplitude * powf(EXPONENTIAL_BASE, -EXPONENTIAL_POWER * ratio) * sin((ratio * totalTime - overshoot) * CIRCLE_RADIANS / period) * HALF_MULTIPLIER + difference + start;
}

float BackIn(float time, float totalTime, float start, float end, float overshootAmount)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    return difference * ratio * ratio * ((overshootAmount + 1.0f) * ratio - overshootAmount) + start;
}

float BackOut(float time, float totalTime, float start, float end, float overshootAmount)
{
    float difference = end - start;         // •Ï‰»—Ê
    float ratio = time / totalTime - 1.0f;  // Š„‡

    return difference * (ratio * ratio * ((overshootAmount + 1.0f) * ratio + overshootAmount) + 1.0f) + start;
}

float BackInOut(float time, float totalTime, float start, float end, float overshootAmount)
{
    float difference = end - start;                                              // •Ï‰»—Ê
    float adjustedOvershoot = overshootAmount * BACK_INOUT_OVERSHOOT_MULTIPLIER; // ’²®‚³‚ê‚½•‘–—Ê
    float ratio = time / (totalTime / HALF_DIVISOR);                             // Š„‡

    if (ratio < 1.0f)
    {
        return difference / HALF_DIVISOR * (ratio * ratio * ((adjustedOvershoot + 1.0f) * ratio - adjustedOvershoot)) + start;
    }

    ratio = ratio - HALF_DIVISOR;

    return difference / HALF_DIVISOR * (ratio * ratio * ((adjustedOvershoot + 1.0f) * ratio + adjustedOvershoot) + HALF_DIVISOR) + start;
}

float BounceIn(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    return difference - BounceOut(totalTime - time, totalTime, 0.0f, difference) + start;
}

float BounceOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    float ratio = time / totalTime;  // Š„‡

    if (ratio < BOUNCE_THRESHOLD_FIRST)
    {
        return difference * (BOUNCE_COEFFICIENT * ratio * ratio) + start;
    }
    else if (ratio < BOUNCE_THRESHOLD_SECOND)
    {
        ratio -= BOUNCE_OFFSET_TIME_SECOND;
        return difference * (BOUNCE_COEFFICIENT * ratio * ratio + BOUNCE_OFFSET_VALUE_SECOND) + start;
    }
    else if (ratio < BOUNCE_THRESHOLD_THIRD)
    {
        ratio -= BOUNCE_OFFSET_TIME_THIRD;
        return difference * (BOUNCE_COEFFICIENT * ratio * ratio + BOUNCE_OFFSET_VALUE_THIRD) + start;
    }
    else
    {
        ratio -= BOUNCE_OFFSET_TIME_FOURTH;
        return difference * (BOUNCE_COEFFICIENT * ratio * ratio + BOUNCE_OFFSET_VALUE_FOURTH) + start;
    }
}

float BounceInOut(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê

    if (time < totalTime / HALF_DIVISOR)
    {
        return BounceIn(time * HALF_DIVISOR, totalTime, 0.0f, difference) * HALF_MULTIPLIER + start;
    }
    else
    {
        return BounceOut(time * HALF_DIVISOR - totalTime, totalTime, 0.0f, difference) * HALF_MULTIPLIER + start + difference * HALF_MULTIPLIER;
    }
}

float Linear(float time, float totalTime, float start, float end)
{
    float difference = end - start;  // •Ï‰»—Ê
    return difference * (time / totalTime) + start;
}