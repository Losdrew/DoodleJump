#include "Entity.h"

Entity::Entity(int x, int y)
{
	this->x = x;
	this->y = y;

	width = 0;
	height = 0;

	sprite = nullptr;
}

Entity::~Entity()
{
	if (sprite != nullptr)
	{
		destroySprite(sprite);
	}
}

void Entity::draw() const
{
	drawSprite(sprite, x - width / 2, y - height / 2);
}

void Entity::move(int deltaX, int deltaY)
{
	setX(getX() + deltaX);
	setY(getY() + deltaY);
}

void Entity::setSize(int width, int height)
{
	if (sprite != nullptr)
	{
		setSpriteSize(sprite, width, height);
		this->width = width;
		this->height = height;
	}
}

void Entity::setSprite(const char* spritePath)
{
	if (sprite != nullptr)
	{
		destroySprite(sprite);
	}

	sprite = createSprite(spritePath);

	if (sprite != nullptr)
	{
		getSpriteSize(sprite, width, height);
	}
}
