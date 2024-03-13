#include "TimedPlatform.h"

TimedPlatform::TimedPlatform(int x, int y) : Platform(x, y)
{
	timer = 0;
	bActive = false;
	bPendingDestroy = false;
	setSprite(spritePath);
}

void TimedPlatform::update(float deltaTime)
{
	if (!isActive() || isPendingDestroy()) 
	{
		return;
	}

	timer += deltaTime;

	if (timer > activeDuration * 0.75f)
	{
		setSprite(redSpritePath);
	}

	if (timer > activeDuration)
	{
		timer = 0;
		bPendingDestroy = true;
	}
}

void TimedPlatform::activate()
{
	timer = 0;
	bActive = true;
}
