#include "Platform.h"

Platform::Platform(int inX, int inY) : Entity(inX, inY)
{
	setSprite(spritePath);
}

bool Platform::isCollision(Entity* other) const
{
	// Has collision only on top
	if ((other->getX() + other->getWidth() / 2 > this->getX() &&
		other->getX() - other->getWidth() / 2 < this->getX() &&
		other->getY() - other->getHeight() / 2 < this->getY() + this->getHeight() / 2 &&
		other->getY() + other->getHeight() / 2 > this->getY() - this->getHeight() / 2) &&
		other->getY() + other->getHeight() / 2 <= this->getY())
	{
		return true;
	}

	return false;
}
