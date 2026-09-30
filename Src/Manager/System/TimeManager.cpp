#include "TimeManager.h"

TimeManager* TimeManager::instance_ = nullptr;

void TimeManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new TimeManager();
    }

    instance_->Init();
}

TimeManager& TimeManager::GetInstance(void)
{
    return *instance_;
}

void TimeManager::Destroy(void)
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

void TimeManager::Reset(void)
{
    const float INITIAL_TIME = 0.0f;
    gameTime_ = INITIAL_TIME;

    timers_.clear();
    prevTime_ = std::chrono::steady_clock::now();
}

void TimeManager::Init(void)
{
    const float INITIAL_TIME = 0.0f;
    const float DEFAULT_GAME_SPEED = 144.0f;

    gameTime_ = INITIAL_TIME;
    gameSpeed_ = DEFAULT_GAME_SPEED;
    timers_.clear();

    prevTime_ = std::chrono::steady_clock::now();
}

void TimeManager::Update(void)
{
    auto currentTime = std::chrono::steady_clock::now();

    std::chrono::duration<float> durationDifference = currentTime - prevTime_;

    prevTime_ = currentTime;

    float deltaTime = durationDifference.count();

    gameTime_ += deltaTime * gameSpeed_;

    const float TIME_FINISHED = 0.0f;

    for (auto& timerPair : timers_)
    {
        Timer& timer = timerPair.second;
        if (timer.timeLeft > TIME_FINISHED)
        {
            timer.timeLeft -= deltaTime;
        }
    }
}

float TimeManager::GetGameTime(void) const
{
    return gameTime_;
}

int TimeManager::GetGameHour(void) const
{
    const int SECONDS_PER_HOUR = 3600;
    return static_cast<int>(gameTime_) / SECONDS_PER_HOUR;
}

int TimeManager::GetGameMinute(void) const
{
    const int SECONDS_PER_MINUTE = 60;
    return (static_cast<int>(gameTime_) / SECONDS_PER_MINUTE) % SECONDS_PER_MINUTE;
}

int TimeManager::GetGameSecond(void) const
{
    const int SECONDS_PER_MINUTE = 60;
    return static_cast<int>(gameTime_) % SECONDS_PER_MINUTE;
}

void TimeManager::SetGameTime(float time)
{
    gameTime_ = time;
}

void TimeManager::StartTimer(const std::string& id, float duration)
{
    timers_[id] = { duration, duration };
}

bool TimeManager::IsTimerFinished(const std::string& id) const
{
    auto iterator = timers_.find(id);

    if (iterator == timers_.end())
    {
        return true;
    }

    const float TIME_FINISHED = 0.0f;

    if (iterator->second.timeLeft <= TIME_FINISHED)
    {
        return true;
    }

    return false;
}

void TimeManager::ResetTimer(const std::string& id)
{
    auto iterator = timers_.find(id);

    if (iterator != timers_.end())
    {
        iterator->second.timeLeft = iterator->second.duration;
    }
}