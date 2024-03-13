#include "Enemy.h"

Enemy::Enemy(int x, int y) : Entity(x, y)
{
	bDead = false;
	setSprite(spritePath);
}

void Enemy::takeDamage(int damage)
{
	lives -= damage;

	if (lives <= 0)
	{
		bDead = true;
	}
}

bool Enemy::isCollision(Entity* other) const
{
	// Can only take damage from the top
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
