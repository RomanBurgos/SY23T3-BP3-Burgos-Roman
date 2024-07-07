#include "Boss.h"
#include "Scene.h"

Boss::Boss()
{
}

Boss::~Boss()
{
	// memory management delete all bullets on death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear(); // clean vector
}

void Boss::start()
{
	// load texture
	texture = loadTexture("gfx/enemyBoss.png");

	hp = 100;
	directionX = 1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 1;
	reloadTime = 60; // cd
	reloadTimePattern = 20;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 120) + 60;
	currentChangeTime = 0;
	isAlive = true;
	//boss pattern
	isPattern = true;
	patternActive = false;
	switchTimer = 1800;

	// query texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	//calling sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Boss::update()
{
	movementPattern();
	reloadMechanics();
	offScreenBullets();
}

void Boss::draw()
{
	blit(texture, x, y);
}

void Boss::setPlayerTarget(Player* player)
{
	targetPlayer = player;
}

void Boss::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Boss::damage(int value)
{
	hp -= value;
	if (hp <= 0)
	{
		hp = 0;
		isDead();
	}
}

int Boss::getHP()
{
	return hp;
}

int Boss::getPosX()
{
	return x;
}

int Boss::getPosY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}

bool Boss::getIsAlive()
{
	return isAlive;
}

void Boss::isDead()
{
	isAlive = false;
}

void Boss::movementPattern()
{

	if (currentChangeTime > 0)
		currentChangeTime--;

	if (currentChangeTime == 0)
	{
		directionX = -directionX;
		currentChangeTime = directionChangeTime;
	}
}

void Boss::attackPattern1()
{
	float dx = 1;
	float dy = -1;

	calcSlope(targetPlayer->getPosX(), targetPlayer->getPosY(), x, y, &dx, &dy);

	SoundManager::playSound(sound);
	for (int i = 0; i < 5; i++)
	{
		Bullet* bullet = new Bullet(x + (rand() % width), y + height / 2, dx, dy, 8, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}

void Boss::attackPattern2()
{
	SoundManager::playSound(sound);
	int countBullet = 10; // number of bullets
	int step = 75; // distance
	for (int i = 1; i <= countBullet; i++)
	{
		Bullet* bulletRain = new Bullet(-20 + i * step, y, 0, 1, 15, Side::ENEMY_SIDE);
		bullets.push_back(bulletRain);
		getScene()->addGameObject(bulletRain);
		currentReloadTime = reloadTimePattern;
	}
}

void Boss::offScreenBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT ||
			bullets[i]->getPositionX() < 0
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

void Boss::reloadMechanics()
{
	if (switchTimer > 0)
	{
		switchTimer--;
	}
	else
	{
		isPattern = !isPattern;
		switchTimer = 1800;
	}

	// attack pattern
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0 && !patternActive) // only fire when timer is avail
	{
		patternActive = true;
		if (isPattern)
		{
			attackPattern1();
			currentReloadTime = reloadTime;
		}
		else
		{
			attackPattern2();
			currentReloadTime = reloadTimePattern;
		}
	}
	else
	{
		patternActive = false;
	}
}
