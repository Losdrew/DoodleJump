#pragma once

#include "Ability.h"

class ImmunityAbility : public Ability
{
public:

	ImmunityAbility();

	virtual void activate() override;
	virtual void deactivate() override;

	virtual void updateAbility(float deltaTime) override;

private:

	float immunityTimer;
	float immunityDuration = 20.0f;
	
	const char* spritePath = "data/shield.png";
};
