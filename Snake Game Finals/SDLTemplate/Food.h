#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"

class Food : public GameObject
{
public:
	Food();
	~Food();
	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	void setPosition(int x, int y);
private:
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
};

