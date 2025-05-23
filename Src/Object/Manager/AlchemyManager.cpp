#include "AlchemyManager.h"

#include "../../Manager/Generic/InputManager.h"
#include "ItemManager.h"
#include "../../DrawUI/Font.h"

AlchemyManager* AlchemyManager::instance_ = nullptr;

void AlchemyManager::CreateInstance(void)
{
	if (!instance_)
	{
		instance_ = new AlchemyManager();
	}
}

AlchemyManager& AlchemyManager::GetInstance(void)
{
	return *instance_;
}

void AlchemyManager::Destroy(void)
{
	delete instance_;
	instance_ = nullptr;
}

AlchemyManager::AlchemyManager(void)
{
	currentPhase_ = 0;
	currentIndex_ = 0;
	currentAmount_ = 1;
	isOpen_ = false;
}

AlchemyManager::~AlchemyManager(void)
{

}

void 
