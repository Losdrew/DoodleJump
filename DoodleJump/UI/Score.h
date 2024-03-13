#pragma once

#include "Entity.h"
#include <array>
#include <string>

class Score : public Entity
{
public:

    Score(int x, int y);
    ~Score();

    virtual void draw() const override;

    void addPlatformsPassed(int platforms);
    void addDistancePassed(int distance);
    void addEnemiesKilled(int enemies);

    int getEnemiesKilled() const { return enemiesKilled; }

private:

    void drawPlatformsPassed() const;
    void drawEnemiesKilled() const;
    void drawDistancePassed() const;

    void drawNumberString(int value, int x, int y, bool bReversed) const;

private:

    int platformsPassed = 0;
    int distancePassed = 0;
    int enemiesKilled = 0;

    std::array<Sprite*, 10> digitSprites;

    int platformsPassedOffsetX = 10;
    int platformsPassedOffsetY = 10;

    int distancePassedOffsetX = -20;
    int distancePassedOffsetY = 10;

    const char* panelSpritePath = "data/top-score-panel.png";
};
