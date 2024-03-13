#pragma once

#include "Entity.h"

class Doodle;

class Ability : public Entity
{
public:

	Ability();
	virtual ~Ability() = default;

	virtual void onGiveAbility(Doodle* doodle);

	virtual void activate();
	virtual void deactivate();

	virtual void updateAbility(float deltaTime) = 0;
	
	bool isActive() const { return bActive; }
	
protected:

	Doodle* getDoodle() const { return doodle; }

private:

	Doodle* doodle;

	bool bActive;
};
