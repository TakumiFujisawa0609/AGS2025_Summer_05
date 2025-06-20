#include "DateTimeManager.h"

#include "TimeManager.h"

DateTimeManager::DateTimeManager(void)
{
	currentDay_ = 0;

	lastRecordedHour_ = -1;
}

void DateTimeManager::Init(void)
{
	currentDay_ = 0;

	lastRecordedHour_ = TimeManager::GetInstance().GetGameHour();
}

void DateTimeManager::Update(void)
{
	int nowHour = TimeManager::GetInstance().GetGameHour();

	//日付チェック
	if (lastRecordedHour_ > nowHour)
	{
		currentDay_++;
	}

	lastRecordedHour_ = nowHour;
}

void DateTimeManager::Reset(void)
{
	currentDay_ = 0;
	lastRecordedHour_ = TimeManager::GetInstance().GetGameHour();
}

int DateTimeManager::GetDay(void) const
{
	return currentDay_;
}

DateTimeManager::TIME_ZONE DateTimeManager::GetTimeZone(void) const
{
	int hour = TimeManager::GetInstance().GetGameHour();

	if (hour >= 6 && hour < 10)
	{
		return TIME_ZONE::MORNING;
	}
	else if (hour >= 10 && hour < 18)
	{
		return TIME_ZONE::DAY;
	}
	else if (hour >= 18 && hour < 22)
	{
		return TIME_ZONE::EVENING;
	}
	else
	{
		return TIME_ZONE::NIGHT;
	}
}
