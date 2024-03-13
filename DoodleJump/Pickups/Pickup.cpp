#include "Pickup.h"

Pickup::Pickup(int x, int y) : Entity(x, y)
{
	bPickedUp = false;
}

bool Pickup::isCollision(Entity* other) const
{
	// Has collision on all sides
	if (other->getX() + other->getWidth() / 2 > this->getX() &&
		other->getX() - other->getWidth() / 2 < this->getX() &&
		other->getY() - other->getHeight() / 2 < this->getY() + this->getHeight() / 2 &&
		other->getY() + other->getHeight() / 2 > this->getY() - this->getHeight() / 2)
	{
		return true;
	}

	return false;
}
