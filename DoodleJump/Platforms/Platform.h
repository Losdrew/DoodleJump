#pragma once

#include "Entity.h"

class Platform : public Entity
{
public:

    Platform(int x, int y);
    virtual ~Platform() = default;

    bool isCollision(Entity* other) const;

private:

    const char* spritePath = "data/platform.png";
};
