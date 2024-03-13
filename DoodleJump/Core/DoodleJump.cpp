#include "DoodleJump.h"

#include "Doodle.h"
#include "Enemy.h"
#include "ImmunityAbility.h"
#include "ImmunityPickup.h"
#include "Platform.h"
#include "Projectile.h"
#include "Score.h"
#include "TimedPlatform.h"
#include <iostream>

void DoodleJump::PreInit(int& width, int& height, bool& fullscreen)
{
	width = screenWidth;
	height = screenHeight;
	fullscreen = bFullscreen;
}

bool DoodleJump::Init() 
{
	srand(static_cast<unsigned int>(time(nullptr)));
	startGame();
	return true;
}

void DoodleJump::Close()
{
	clearGameObjects();
}

DoodleJump::~DoodleJump() 
{
	clearGameObjects();
}

bool DoodleJump::Tick()
{
	currentTickCount = getTickCount();

	float deltaTime = (currentTickCount - lastTickCount) / 1000.0f;

	if (isGameOver())
	{
		restartGame();
		return false;
	}

	adjustEntityPositionsY(deltaTime);

	updatePlayer(deltaTime);
	updatePlatforms(deltaTime);
	updateProjectiles(deltaTime);
	updateEnemies(deltaTime);
	updatePickups(deltaTime);

	drawTestBackground();
	draw(deltaTime);

	handleInput();

	lastTickCount = currentTickCount;

	return false;
}

void DoodleJump::onMouseMove(int x, int y, int xrelative, int yrelative) 
{
	mousePositionX = x;
	mousePositionY = y;
}

void DoodleJump::onMouseButtonClick(FRMouseButton button, bool isReleased) 
{
	if (button == FRMouseButton::LEFT && isReleased)
	{
		Projectile* projectile = doodle->shoot();
		projectile->setDirection(mousePositionX, mousePositionY);
		projectiles.push_back(projectile);
	}
}

void DoodleJump::onKeyPressed(FRKey k) 
{
	pressedKeys.insert(k);
}

void DoodleJump::onKeyReleased(FRKey k) 
{
	pressedKeys.erase(k);
}

const char* DoodleJump::GetTitle()
{
	return "Doodle Jump";
}

void DoodleJump::setScreenSize(int width, int height, bool fullscreen)
{
	screenWidth = width;
	screenHeight = height;
	bFullscreen = fullscreen;
}

bool DoodleJump::isGameOver() const
{
	return doodle->isDead();
}

void DoodleJump::startGame()
{
	score = new Score(0, 0);
	doodle = new Doodle(screenWidth / 2, screenHeight);
	doodle->jump();
}

void DoodleJump::restartGame()
{
	clearGameObjects();
	startGame();
}

void DoodleJump::clearGameObjects()
{
	delete doodle;
	delete score;

	platforms.clear();
	projectiles.clear();
	enemies.clear();
	pickups.clear();
	pressedKeys.clear();
}

void DoodleJump::handleInput()
{
	if (isKeyPressed(FRKey::LEFT))
    {
		doodle->move(-screenWidth * horizontalSpeedMultiplier, 0);
    }
    else if (isKeyPressed(FRKey::RIGHT))
    {
		doodle->move(screenWidth * horizontalSpeedMultiplier, 0);
    }
}

bool DoodleJump::isKeyPressed(FRKey k) const
{
	return pressedKeys.find(k) != pressedKeys.end();
}

void DoodleJump::updatePlayer(float deltaTime)
{
	if (doodle->getY() > screenHeight)
	{
		onPlayerFellOutScreen();
	}
	doodle->updateVelocity(deltaTime);
	doodle->applyGravity(deltaTime);
	doodle->updateAbilities(deltaTime);
}

void DoodleJump::onPlayerFellOutScreen()
{
	doodle->takeFallDamage(fallOutOfScreenDamage);

	Platform* lowestPlatform = platforms.front();
	int distanceToLowestPlatform = abs(doodle->getX() - lowestPlatform->getX());
	doodle->move(lowestPlatform->getX() - doodle->getX(), screenHeight - doodle->getY());

	doodle->jump();
}

void DoodleJump::updatePlatforms(float deltaTime)
{
	for (auto it = platforms.begin(); it != platforms.end(); )
	{
		Platform* platform = *it;

		bool bRemovePlatform = false;

		handlePlatformCollision(platform);

		if (platform->getY() > screenHeight)
		{
			bRemovePlatform = true;
		}

		if (TimedPlatform* timedPlatform = dynamic_cast<TimedPlatform*>(platform))
		{
			if (!timedPlatform->isActive() && timedPlatform->getY() > 0)
			{
				timedPlatform->activate();
			}
			if (timedPlatform->isPendingDestroy())
			{
				bRemovePlatform = true;
			}
			timedPlatform->update(deltaTime);
		}

		if (bRemovePlatform)
		{
			score->addPlatformsPassed(1);
			it = platforms.erase(it);
			delete platform;
			continue;
		}

		++it;
	}

	int numPlatformsToGenerate = maxPlatforms - platforms.size();

	for (int i = 0; i < numPlatformsToGenerate; ++i)
	{
		generateRandomPlatforms();
	}
}

void DoodleJump::handlePlatformCollision(Platform* platform)
{
	if (platform->isCollision(doodle))
	{
		doodle->jump();
	}
}

void DoodleJump::generateRandomPlatforms()
{
	if (platforms.empty())
	{
		Platform* basePlatform = new Platform(screenWidth / 2, screenHeight / 2 + screenHeight / 3);
		platforms.push_back(basePlatform);
		return;
	}

	int offset = rand() % (distanceMax - distanceMin + 1) + distanceMin;
	int x = rand() % screenWidth;
	int y = platforms.back()->getY() - offset;

	bool bShouldSpawnTimedPlatform = rand() % 100 < timedPlatformSpawnChance;

	Platform* newPlatform;

	if (bShouldSpawnTimedPlatform)
	{
		newPlatform = new TimedPlatform(x, y);
	}
	else
	{
		newPlatform = new Platform(x, y);
	}
		
	platforms.push_back(newPlatform);

	// Don't spawn enemies or pickups on timed platforms
	if (bShouldSpawnTimedPlatform)
	{
		return;
	}

	bool bShouldSpawnEnemy = rand() % 100 < enemySpawnChance;

	if (bShouldSpawnEnemy)
	{
		Enemy* enemy = new Enemy(x, y - newPlatform->getHeight());
		enemies.push_back(enemy);
	}

	if (!bShouldSpawnEnemy && score->getEnemiesKilled() >= numKilledEnemiesForAbility)
	{
		bool bShouldSpawnImmunityPickup = rand() % 100 < immunitySpawnChance;

		if (bShouldSpawnImmunityPickup)
		{
			ImmunityPickup* ability = new ImmunityPickup(x, y - newPlatform->getHeight());
			pickups.push_back(ability);
		}
	}
}

void DoodleJump::updateProjectiles(float deltaTime)
{
	for (auto it = projectiles.begin(); it != projectiles.end(); )
	{
		Projectile* projectile = *it;

		projectile->updateVelocity(deltaTime);

		// Is projectile out of screen?
		if (projectile->getY() < 0 || projectile->getY() > screenHeight)
		{
			it = projectiles.erase(it);
			delete projectile;
		}
		else
		{
			handleProjectileCollision(projectile);
			++it;
		}
	}
}

void DoodleJump::handleProjectileCollision(Projectile* projectile)
{
	for (auto& enemy : enemies)
	{
		if (projectile->isCollision(enemy))
		{
			enemy->takeDamage(projectile->getDamage());
			if (enemy->isDead())
			{
				score->addEnemiesKilled(1);
			}
		}
	}
}

void DoodleJump::updateEnemies(float deltaTime)
{
	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		Enemy* enemy = *it;

		if (enemy->getY() > screenHeight || enemy->isDead())
		{
			it = enemies.erase(it);
			delete enemy;
		}
		else
		{
			handleEnemyCollision(enemy);
			++it;
		}
	}
}

void DoodleJump::handleEnemyCollision(Enemy* enemy)
{
	// Was enemy stomped?
	if (enemy->isCollision(doodle))
	{
		enemy->takeDamage(doodle->getStompDamage());
		if (enemy->isDead())
		{
			score->addEnemiesKilled(1);
		}
	}

	else if (doodle->isCollision(enemy))
	{
		doodle->takeEnemyDamage(enemy->getDamage());
	}
}

void DoodleJump::updatePickups(float deltaTime)
{
	for (auto it = pickups.begin(); it != pickups.end(); )
	{
		Pickup* pickup = *it;

		if (pickup->getY() > screenHeight || pickup->isPickedUp())
		{
			it = pickups.erase(it);
			delete pickup;
		}
		else
		{
			handlePickupCollision(pickup);
			++it;
		}
	}
}

void DoodleJump::handlePickupCollision(Pickup* pickup)
{
	if (pickup->isCollision(doodle))
	{
		pickup->giveToPlayer(doodle);
	}
}

void DoodleJump::adjustEntityPositionsY(float deltaTime)
{
	int adjustmentY = getPositionYAdjustment(deltaTime);

	doodle->move(0, adjustmentY);

	for (auto& platform : platforms)
	{
		platform->move(0, adjustmentY);
	}

	for (auto& enemy : enemies)
	{
		enemy->move(0, adjustmentY);
	}

	for (auto& projectile : projectiles)
	{
		projectile->move(0, adjustmentY);
	}

	for (auto& pickup : pickups)
	{
		pickup->move(0, adjustmentY);
	}

	score->addDistancePassed(adjustmentY);
}

int DoodleJump::getPositionYAdjustment(float deltaTime)
{
	int cameraVelocity = -(doodle->getY() - doodle->getHeight() - screenHeight / 2);

	if (doodle->getY() < screenHeight / 2 - doodle->getHeight())
	{
		int cameraOffset = screenHeight / 2 - (doodle->getY() + doodle->getHeight() / 2);
		cameraVelocity += cameraOffset;
	}

	if (cameraVelocity > 0)
	{
		int deltaY = static_cast<int>(cameraVelocity * deltaTime);
		return deltaY;
	}

	return 0;
}

void DoodleJump::draw(float deltaTime)
{
	doodle->draw();

	for (auto& platform : platforms)
	{
		platform->draw();
	}

	for (auto& enemy : enemies)
	{
		enemy->draw();
	}

	for (auto& projectile : projectiles)
	{
		projectile->draw();
	}

	for (auto& pickup : pickups)
	{
		pickup->draw();
	}

	score->draw();
}
