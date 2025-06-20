#pragma once

class DateTimeManager
{
public:

	enum class TIME_ZONE
	{
		MORNING,
		DAY,
		EVENING,
		NIGHT,
	};

	//コンストラクタ
	DateTimeManager(void);

	//デストラクタ
	~DateTimeManager(void) = default;

	void Init(void);
	void Update(void);

	void Reset(void);

	int GetDay(void) const;
	TIME_ZONE GetTimeZone(void) const;

private:
	int currentDay_;

	int lastRecordedHour_;

	void CheckNewDay(void);
};

