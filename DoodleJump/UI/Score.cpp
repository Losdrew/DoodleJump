#include "Score.h"

#include "Framework.h"

Score::Score(int x, int y) : Entity(x, y)
{
    int screenWidth, screenHeight;
    getScreenSize(screenWidth, screenHeight);

    setSprite(panelSpritePath);
    setSize(screenWidth, 0.05f * screenHeight);

    for (int i = 0; i < 10; ++i)
    {
        std::string spritePath = "data/" + std::to_string(i) + ".png";
        digitSprites[i] = createSprite(spritePath.c_str());
    }
}

Score::~Score()
{
    for (auto& sprite : digitSprites)
    {
        destroySprite(sprite);
    }
}

void Score::draw() const
{
    drawSprite(sprite, getX(), getY());
    drawPlatformsPassed();
    drawEnemiesKilled();
    drawDistancePassed();
}

void Score::drawPlatformsPassed() const
{
    int x = getX() + platformsPassedOffsetX;
    int y = getY() + platformsPassedOffsetY;
    drawNumberString(platformsPassed, x, y, false);
}

void Score::drawEnemiesKilled() const
{
    int x = getWidth() / 2;
    int y = getY() + platformsPassedOffsetY;
    drawNumberString(enemiesKilled, x, y, false);
}

void Score::drawDistancePassed() const
{
    int x = getWidth() + distancePassedOffsetX;
    int y = getY() + distancePassedOffsetY;
    drawNumberString(static_cast<int>(distancePassed), x, y, true);
}

void Score::drawNumberString(int value, int x, int y, bool bReversed) const
{
    std::string valueStr = std::to_string(value);
    int printOrderMultiplier = 1;

    if (bReversed)
    {
        std::reverse(valueStr.rbegin(), valueStr.rend());
        printOrderMultiplier = -1;
    }

    for (auto digitChar : valueStr)
    {
        int digitValue = digitChar - '0';
        if (digitValue >= 0 && digitValue < 10 && digitSprites[digitValue])
        {
            int digitWidth, digitHeight = 0;
            getSpriteSize(digitSprites[digitValue], digitWidth, digitHeight);
            drawSprite(digitSprites[digitValue], x, y);
            x += printOrderMultiplier * (digitWidth + 2);
        }
    }
}

void Score::addPlatformsPassed(int platforms)
{
    platformsPassed += platforms;
}

void Score::addDistancePassed(int distance)
{
    distancePassed += distance;
}

void Score::addEnemiesKilled(int enemies)
{
    enemiesKilled += enemies;
}
