#pragma once

#include "Framework.h"
#include <unordered_set>
#include <vector>

class Doodle;
class Enemy;
class Pickup;
class Platform;
class Projectile;
class Score;

class DoodleJump : public Framework 
{
public:

	virtual ~DoodleJump() override;

	virtual void PreInit(int& width, int& height, bool& fullscreen) override;
	virtual bool Init() override;
	virtual void Close() override;

	virtual bool Tick() override;

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	virtual void onKeyPressed(FRKey k) override;
	virtual void onKeyReleased(FRKey k) override;

	virtual const char* GetTitle() override;

	void setScreenSize(int width, int height, bool fullscreen);

private:

	bool isGameOver() const;

	void startGame();
	void restartGame();
	void clearGameObjects();

	void handleInput();
	bool isKeyPressed(FRKey k) const;
	
	void updatePlayer(float deltaTime);
	void updatePlatforms(float deltaTime);
	void updateProjectiles(float deltaTime);
	void updateEnemies(float deltaTime);
	void updatePickups(float deltaTime);

	void onPlayerFellOutScreen();
	void generateRandomPlatforms();

	void handlePlatformCollision(Platform* platform);
	void handleProjectileCollision(Projectile* projectile);
	void handleEnemyCollision(Enemy* enemy);
	void handlePickupCollision(Pickup* pickup);
	
	void adjustEntityPositionsY(float deltaTime);
	int getPositionYAdjustment(float deltaTime);

	void draw(float deltaTime);

private:

	int screenWidth = 800;
	int screenHeight = 600;
	bool bFullscreen = false;

	unsigned int lastTickCount;
	unsigned int currentTickCount;

	int mousePositionX;
	int mousePositionY;

	float horizontalSpeedMultiplier = 0.005f;

	int maxPlatforms = 30;
	int distanceMin = 20;
	int distanceMax = 100;

	int enemySpawnChance = 5;
	int timedPlatformSpawnChance = 10;
	int immunitySpawnChance = 10;

	int numKilledEnemiesForAbility = 5;

	int fallOutOfScreenDamage = 1;

	Score* score;
	Doodle* doodle;

	std::vector<Platform*> platforms;
	std::vector<Projectile*> projectiles;
	std::vector<Enemy*> enemies;
	std::vector<Pickup*> pickups;

	std::unordered_set<FRKey> pressedKeys;
};
