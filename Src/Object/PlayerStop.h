#pragma once

class Player;

class PlayerStop
{
public:
	static void CreateInstance(void);

	static PlayerStop& GetInstance(void);

	static void Destroy(void);

	void SetPlayer(Player* player);

	void StopMovement(void);

	void ResumeMovement(void);

	bool IsStopped(void) const;

private:
	PlayerStop(void);

	~PlayerStop(void);

	PlayerStop(const PlayerStop&) = delete;

	PlayerStop& operator=(const PlayerStop&) = delete;

	bool stopped_;

	Player* player_;

	static PlayerStop* instance_;
};

