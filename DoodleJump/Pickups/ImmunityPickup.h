#pragma once

#include "Pickup.h"

class Doodle;

class ImmunityPickup : public Pickup
{
public:

	ImmunityPickup(int x, int y);

	virtual void giveToPlayer(Doodle* doodle) override;

private:

	const char* spritePath = "data/immunity.png";
};
