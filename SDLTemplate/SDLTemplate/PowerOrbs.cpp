#include "PowerOrbs.h"

PowerOrbs::PowerOrbs()
{
}

PowerOrbs::~PowerOrbs()
{
}

void PowerOrbs::start()
{
	// load texture
	texture = loadTexture("gfx/points.png");

	// initialize variables
	directionX = 0;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 1;

	// query texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerOrbs::update()
{
	y += directionY * speed;
}

void PowerOrbs::draw()
{
	blit(texture, x, y);
}

int PowerOrbs::getPosX()
{
    return x;
}

int PowerOrbs::getPosY()
{
    return y;
}

int PowerOrbs::getWidth()
{
    return width;
}

int PowerOrbs::getHeight()
{
    return height;
}

void PowerOrbs::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
