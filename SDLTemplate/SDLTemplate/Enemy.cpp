#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	// memory management delete all bullets on death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear(); // clean vector
}

void Enemy::start()
{
	// load texture
	texture = loadTexture("gfx/enemy.png");

	// initialize variables
	directionX = 1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60; // 1 sec
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 120;
	currentChangeTime = 0;

	// query texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	//calling sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentChangeTime > 0)
		currentChangeTime--;

	if (currentChangeTime == 0)
	{
		directionX = -directionX;
		currentChangeTime = directionChangeTime;
	}

	//decrement the reload timer every frame
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0) // only fire when timer is avail
	{
		float dx = 1;
		float dy = -1;

		calcSlope(targetPlayer->getPosX(), targetPlayer->getPosY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width / 2, y + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// after firing reset reload timer
		currentReloadTime = reloadTime;
	}

	// when they go off screen, delete the bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT || bullets[i]->getPositionX() < 0 
			|| bullets[i]->getPositionX() > SCREEN_WIDTH )
		{
			// Cache the variable so delete later (leaker pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break; // delete bullet once per frame
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	targetPlayer = player;
}

void Enemy::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Enemy::getPosX()
{
	return x;
}

int Enemy::getPosY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}
