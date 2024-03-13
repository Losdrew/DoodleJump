#pragma once

#include "Entity.h"

class Doodle;

class Pickup : public Entity
{
public:

	Pickup(int x, int y);
	virtual ~Pickup() = default;

	virtual void giveToPlayer(Doodle* doodle) = 0;
	
	bool isCollision(Entity* other) const;

	bool isPickedUp() const { return bPickedUp; }

protected:

	void setPickedUp(bool pickedUp) { bPickedUp = pickedUp; }

private:

	bool bPickedUp;
};
