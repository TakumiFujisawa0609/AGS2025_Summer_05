#include "Wand.h"

#include "../../../Manager/Generic/ResourceManager.h"

Wand::Wand(void)
	:MaterialItem
	(
		"Wand",
		"ñ",
		"“S‚Å‚Å‚«‚½ñ‚ÌŒ´Œ^\n‚Ù‚©‚Ì‘fŞ‚Æ¬‚º‚Ä˜B‹à‚·‚é‚±‚Æ‚Å\n–{Ši“I‚Èñ‚ğ‚Â‚­‚é‚±‚Æ‚ª‚Å‚«‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::WAND).handleId_,
		0
	)
{
}
