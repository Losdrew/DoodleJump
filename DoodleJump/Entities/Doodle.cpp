#include "Doodle.h"

#include "Ability.h"
#include "Entity.h"
#include "Projectile.h"
#include <cmath>

Doodle::Doodle(int x, int y) : Entity(x, y)
{
	velocityY = 0;
	bDead = false;
	bImmuneToFallDamage = false;
	bImmuneToEnemyDamage = false;

	setSprite(leftSpritePath);
}

Doodle::~Doodle()
{
	appliedAbilities.clear();
}

void Doodle::draw() const
{
	Entity::draw();

	for (auto& ability : appliedAbilities)
	{
		ability->draw();
	}
}

void Doodle::move(int deltaX, int deltaY)
{
	if (deltaX != 0)
	{
		setSprite(deltaX < 0 ? leftSpritePath : rightSpritePath);
	}

	Entity::move(deltaX, deltaY);

	for (auto& ability : appliedAbilities)
	{
		ability->move(deltaX, deltaY);
	}

	wrapAroundScreen();
}

void Doodle::wrapAroundScreen()
{
	int screenWidth, screenHeight;
	getScreenSize(screenWidth, screenHeight);
	setX((this->getX() + screenWidth) % screenWidth);

	for (auto& ability : appliedAbilities)
	{
		ability->setX((ability->getX() + screenWidth) % screenWidth);
	}
}

void Doodle::updateVelocity(float deltaTime)
{
	int deltaY = std::ceil(velocityY * deltaTime);
	move(0, deltaY);
}

void Doodle::applyGravity(float deltaTime)
{
	velocityY += gravity * deltaTime;
}

void Doodle::jump()
{
	velocityY = -jumpForce;
}

Projectile* Doodle::shoot()
{
	return new Projectile(getX(), getY());
}

bool Doodle::isCollision(Entity* other) const
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

void Doodle::takeEnemyDamage(int damage)
{
	if (bImmuneToEnemyDamage)
	{
		return;
	}

	takeDamage(damage);
}

void Doodle::takeFallDamage(int damage)
{
	if (bImmuneToFallDamage)
	{
		return;
	}

	takeDamage(damage);
}

void Doodle::setImmuneToFallDamage(bool bImmune)
{
	bImmuneToFallDamage = bImmune;
}

void Doodle::setImmuneToEnemyDamage(bool bImmune)
{
	bImmuneToEnemyDamage = bImmune;
}

void Doodle::takeDamage(int damage)
{
	lives -= damage;

	if (lives <= 0)
	{
		bDead = true;
	}
}

void Doodle::giveAbility(Ability* ability)
{
	ability->onGiveAbility(this);
	appliedAbilities.push_back(ability);

	if (!ability->isActive())
	{
		ability->activate();
	}
}

void Doodle::updateAbilities(float deltaTime)
{
	for (auto it = appliedAbilities.begin(); it != appliedAbilities.end(); )
	{
		Ability* ability = *it;

		if (!ability->isActive())
		{
			it = appliedAbilities.erase(it);
			delete ability;
		}
		else
		{
			ability->updateAbility(deltaTime);
			++it;
		}
	}
}
