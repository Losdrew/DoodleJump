#pragma once

#include "Entity.h"

class Projectile : public Entity
{
public:

    Projectile(int x, int y);

    virtual void move(int x, int y) override;

    void setDirection(int x, int y);
    void updateVelocity(float deltaTime);

    bool isCollision(Entity* other) const;

    int getDamage() const { return damage; }

private:

    void wrapAroundScreen();

private:

    int speed = 800;

    float directionX;
    float directionY;

    int damage = 1;

    const char* spritePath = "data/projectile.png";
};
