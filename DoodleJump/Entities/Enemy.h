#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy(int x, int y);

	void takeDamage(int damage);

	bool isCollision(Entity* other) const;

	int getDamage() const { return damage; }

	bool isDead() const { return bDead; }

private:

	int damage = 5;

	int lives = 1;
	bool bDead;

	const char* spritePath = "data/enemy.png";
};
