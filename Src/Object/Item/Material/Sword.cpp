#include "Sword.h"

#include "../../../Manager/Generic/ResourceManager.h"

Sword::Sword(void)
	:MaterialItem
	(
		"Sword",
		"Œ•",
		"“S‚Å‚Å‚«‚½Œ•‚ÌŒ´Œ^\n‚Ù‚©‚Ì‘fŞ‚Æ¬‚º‚Ä˜B‹à‚·‚é‚±‚Æ‚Å\n–{Ši“I‚ÈŒ•‚ğ‚Â‚­‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SWORD).handleId_,
		0
	)
{
}
