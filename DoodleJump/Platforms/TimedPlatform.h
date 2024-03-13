#pragma once

#include "Platform.h"

class TimedPlatform : public Platform
{
public:

	TimedPlatform(int x, int y);

	void update(float deltaTime);

	void activate();
	
	bool isActive() const { return bActive; }
	bool isPendingDestroy() const { return bPendingDestroy; }

private:

	float timer;
	float activeDuration = 3.0f;

	bool bActive;
	bool bPendingDestroy;

	const char* spritePath = "data/timed-platform.png";
	const char* redSpritePath = "data/timed-platform-red.png";
};
