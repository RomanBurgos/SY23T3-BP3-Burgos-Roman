#pragma once
#include "GameObject.h"
#include <vector>
#include "common.h"
#include "draw.h"
#include "util.h"
#include "GameObject.h"
#include "SoundManager.h"

struct BodySegment
{
	int x, y;
};

class Player : public GameObject
{
public:
	Player();
	~Player();
	void start();
	void update();
	void draw();

	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void handleInput();
	bool isAlive() const;
	void grow();
	void reset();
private:
	std::vector<BodySegment> body;
	Mix_Chunk* sound;
	int width;
	int height;
	int directionX;
	int directionY;
	int speed;
	int moveDelay;
	int moveCounter;
	bool alive;

	SDL_Texture* texture;

	void move();
	void checkCollision();
};

