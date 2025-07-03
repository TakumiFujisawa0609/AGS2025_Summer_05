#include "PlayerStop.h"
#include "player.h"

PlayerStop* PlayerStop::instance_ = nullptr;

PlayerStop::PlayerStop(void)
	: stopped_(false), player_(nullptr)
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
		// ”O‚Ì‚½‚ßˆÀ‘S‘ÎôiŒÄ‚Ñ–Y‚êŽžj
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
	stopped_ = true;
	if (player_) player_->SetMovementEnabled(false);
}

void PlayerStop::ResumeMovement(void)
{
	stopped_ = false;
	if (player_) player_->SetMovementEnabled(true);
}

bool PlayerStop::IsStopped(void) const
{
	return stopped_;
}
