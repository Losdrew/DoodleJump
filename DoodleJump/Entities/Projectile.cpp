#include "Projectile.h"

#include <cmath>

Projectile::Projectile(int x, int y) : Entity(x, y)
{
	directionX = 0;
	directionY = 0;
	setSprite(spritePath);
}

void Projectile::move(int x, int y)
{
	Entity::move(x, y);
	wrapAroundScreen();
}

void Projectile::wrapAroundScreen()
{
	int screenWidth, screenHeight;
	getScreenSize(screenWidth, screenHeight);
	setX((this->getX() + screenWidth) % screenWidth);
}

void Projectile::setDirection(int x, int y)
{
	int deltaX = x - this->getX();
	int deltaY = y - this->getY();
    float angle = atan2(deltaY, deltaX);
	directionX = speed * std::cos(angle);
	directionY = speed * std::sin(angle);
}

void Projectile::updateVelocity(float deltaTime)
{
	int deltaX = static_cast<int>(directionX * deltaTime);
	int deltaY = static_cast<int>(directionY * deltaTime);
	move(deltaX, deltaY);
}

bool Projectile::isCollision(Entity* other) const
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
