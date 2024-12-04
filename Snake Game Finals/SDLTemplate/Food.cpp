#include "Food.h"

Food::Food()
{
}

Food::~Food()
{
}

void Food::start()
{
	//load texture
	texture = loadTexture("gfx/food.png");

	//initialize variables
	x = 100;
	y = 100;
	width = 0;
	height = 0;

	// query texture
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Food::update()
{
}

void Food::draw()
{
	blit(texture, x, y);
}

int Food::getPosX()
{
	return x;
}

int Food::getPosY()
{
	return y;
}

int Food::getWidth()
{
	return width;
}

int Food::getHeight()
{
	return height;
}

void Food::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}