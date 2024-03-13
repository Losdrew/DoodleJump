#pragma once

#include "Framework.h"

class Entity
{
public:

	Entity(int x = 0, int y = 0);
	virtual ~Entity();

	virtual void draw() const;
	virtual void move(int deltaX, int deltaY);

	void setSize(int width, int height);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	int getX() const { return x; }
	void setX(int x) { this->x = x; }

	int getY() const { return y; }
	void setY(int y) { this->y = y; }

protected:

	virtual void setSprite(const char* spritePath);

protected:

	Sprite* sprite;

private:

	int x;
	int y;

	int width;
	int height;
};
