#pragma once

#include "Entity.h"
#include <vector>
#include <algorithm>

class Projectile;
class Ability;

class Doodle : public Entity
{
public:

	Doodle(int x, int y);
	~Doodle();

	virtual void draw() const override;
	virtual void move(int deltaX, int deltaY) override;

	void updateVelocity(float deltaTime);
	void applyGravity(float deltaTime);

	void jump();
	Projectile* shoot();

	bool isCollision(Entity* other) const;

	void takeEnemyDamage(int damage);
	void takeFallDamage(int damage);

	int getStompDamage() const { return stompDamage; }
	
	void setImmuneToFallDamage(bool bImmune);
	void setImmuneToEnemyDamage(bool bImmune);

	bool isDead() const { return bDead; }

	void giveAbility(Ability* ability);
	void updateAbilities(float deltaTime);

	template <typename T>
	bool hasAbilityOfType() const
	{
		return std::any_of(appliedAbilities.begin(), appliedAbilities.end(), [](Ability* ability)
		{
			return dynamic_cast<T*>(ability) != nullptr;
		});
	}

private:

	void wrapAroundScreen();
	void takeDamage(int damage);

private:

	int jumpForce = 500;
	int gravity = 400;

	float velocityY;

	int stompDamage = 1;

	int lives = 5;

	bool bImmuneToFallDamage;
	bool bImmuneToEnemyDamage;

	bool bDead;

	std::vector<Ability*> appliedAbilities;

	const char* leftSpritePath = "data/lik-left.png";
	const char* rightSpritePath = "data/lik-right.png";
};
