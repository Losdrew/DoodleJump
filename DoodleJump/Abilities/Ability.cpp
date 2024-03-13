#include "Ability.h"

#include "Doodle.h"

Ability::Ability() : Entity()
{
	bActive = false;
	doodle = nullptr;
}

void Ability::onGiveAbility(Doodle* doodle)
{
	this->doodle = doodle;
	setX(doodle->getX());
	setY(doodle->getY());
}

void Ability::activate()
{
	bActive = true;
}

void Ability::deactivate()
{
	bActive = false;
}
