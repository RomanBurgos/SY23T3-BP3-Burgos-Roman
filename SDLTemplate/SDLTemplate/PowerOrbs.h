#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"

class PowerOrbs : public GameObject
{
public:
	PowerOrbs();
	~PowerOrbs();
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
	int speed;
	float directionX;
	float directionY;
};

