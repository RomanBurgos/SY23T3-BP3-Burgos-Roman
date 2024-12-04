#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Boss : public GameObject
{
public:
	Boss();
	~Boss();
	void start();
	void update();
	void draw();
	void setPlayerTarget(Player* player);
	void setPosition(int x, int y);
	void damage(int value);

	int getHP();
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	bool getIsAlive();
	void isDead();
	void movementPattern();
	void attackPattern1();
	void attackPattern2();
	void offScreenBullets();
	void reloadMechanics();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* targetPlayer;
	int hp;
	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;
	int speed;
	float reloadTime;
	float reloadTimePattern;
	float currentReloadTime;
	float directionChangeTime;
	float currentChangeTime;
	bool isAlive;
	std::vector<Bullet*> bullets;
	//atk pattern logic
	bool isPattern;
	bool patternActive;
	float switchTimer;
};