#include "ImmunityAbility.h"

#include "Doodle.h"

ImmunityAbility::ImmunityAbility() : Ability()
{
	immunityTimer = 0;
	setSprite(spritePath);
}

void ImmunityAbility::updateAbility(float deltaTime)
{
	if (!isActive())
	{
		return;
	}

	immunityTimer += deltaTime;
	if (immunityTimer >= immunityDuration)
	{
		immunityTimer = 0;
		deactivate();
	}
}

void ImmunityAbility::activate()
{
	getDoodle()->setImmuneToFallDamage(true);
	immunityTimer = 0;
	Ability::activate();
}

void ImmunityAbility::deactivate()
{
	getDoodle()->setImmuneToFallDamage(false);
	Ability::deactivate();
}
