#include "BloodBag.h"

#include "../../../Manager/Generic/ResourceManager.h"

BloodBag::BloodBag(void)
	:MaterialItem
	(
		"BloodBag",
		"ŒŒ‘Ü",
		"‰½‚©‚ÌŒŒ‰t‚ª“ü‚Á‚Ä‚¢‚é",
		0,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BLOOD_BAG).handleId_,
		0
	)
{
}
