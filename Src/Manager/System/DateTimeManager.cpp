#include "DateTimeManager.h"

#include "TimeManager.h"
#include "../../Manager/Generic/InputManager.h"

DateTimeManager::DateTimeManager(void)
    : currentDay_(0), lastRecordedHour_(-1)
{
}

void DateTimeManager::Init(void)
{
    const int INITIAL_DAY = 0;
    currentDay_ = INITIAL_DAY;

    lastRecordedHour_ = TimeManager::GetInstance().GetGameHour();
}

void DateTimeManager::Update(void)
{
    auto& timeManager = TimeManager::GetInstance();

    if (InputManager::GetInstance().IsTriggerDown(KEY_INPUT_R))
    {
        currentDay_++;
    }

    while (timeManager.GetGameTime() >= HOURS_IN_DAY)
    {
        currentDay_++;
        timeManager.SetGameTime(timeManager.GetGameTime() - HOURS_IN_DAY);
    }
}

void DateTimeManager::Reset(void)
{
    const int INITIAL_DAY = 0;
    currentDay_ = INITIAL_DAY;

    lastRecordedHour_ = TimeManager::GetInstance().GetGameHour();
}

int DateTimeManager::GetDay(void) const
{
    return currentDay_;
}

DateTimeManager::TIME_ZONE DateTimeManager::GetTimeZone(void) const
{
    int currentHour = TimeManager::GetInstance().GetGameHour();

    // 時間帯の境界となる時間のローカル定数
    const int HOUR_MORNING_START = 6;   // 朝の開始時間
    const int HOUR_DAY_START = 10;      // 昼の開始時間
    const int HOUR_EVENING_START = 18;  // 夕方の開始時間
    const int HOUR_NIGHT_START = 22;    // 夜の開始時間

    if (currentHour >= HOUR_MORNING_START && currentHour < HOUR_DAY_START)
    {
        return TIME_ZONE::MORNING;
    }
    else if (currentHour >= HOUR_DAY_START && currentHour < HOUR_EVENING_START)
    {
        return TIME_ZONE::DAY;
    }
    else if (currentHour >= HOUR_EVENING_START && currentHour < HOUR_NIGHT_START)
    {
        return TIME_ZONE::EVENING;
    }
    else
    {
        return TIME_ZONE::NIGHT;
    }
}