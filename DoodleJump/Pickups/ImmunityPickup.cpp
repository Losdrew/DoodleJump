#include "ImmunityPickup.h"

#include "Doodle.h"
#include "ImmunityAbility.h"

ImmunityPickup::ImmunityPickup(int x, int y) : Pickup(x, y)
{
	setSprite(spritePath);
}

void ImmunityPickup::giveToPlayer(Doodle* doodle)
{
	// Don't give immunity ability if player already has it
	if (doodle->hasAbilityOfType<ImmunityAbility>())
	{
		return;
	}

	ImmunityAbility* immunityAbility = new ImmunityAbility();
	doodle->giveAbility(immunityAbility);
	setPickedUp(true);
}
