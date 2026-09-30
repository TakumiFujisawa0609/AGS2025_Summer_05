#include "PlayerStop.h"
#include "player.h"

PlayerStop* PlayerStop::instance_ = nullptr;

PlayerStop::PlayerStop(void)
    : isStopped_(false), player_(nullptr)
{
}

PlayerStop::~PlayerStop(void)
{
}

void PlayerStop::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new PlayerStop();
    }
}

PlayerStop& PlayerStop::GetInstance(void)
{
    if (instance_ == nullptr)
    {
        CreateInstance();
    }
    return *instance_;
}

void PlayerStop::Destroy(void)
{
    delete instance_;
    instance_ = nullptr;
}

void PlayerStop::SetPlayer(Player* player)
{
    player_ = player;
}

void PlayerStop::StopMovement(void)
{
    isStopped_ = true;

    if (player_ != nullptr)
    {
        player_->SetMovementEnabled(false);
    }
}

void PlayerStop::ResumeMovement(void)
{
    isStopped_ = false;

    if (player_ != nullptr)
    {
        player_->SetMovementEnabled(true);
    }
}

bool PlayerStop::IsStopped(void) const
{
    return isStopped_;
}