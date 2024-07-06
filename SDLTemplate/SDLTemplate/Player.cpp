#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// memory management delete all bullets on death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear(); // clean vector
}

void Player::start()
{
	// load texture
	texture = loadTexture("gfx/player.png");
	explosionTexture = loadTexture("gfx/explosion.png");

	// initialize variables
	x = SCREEN_WIDTH / 2;
	y = 700;
	width = 0;
	height = 0;
	speed = 2;
	defaultSpeed = speed;
	reloadTime = 8;
	currentReloadTime = 0;
	extraReloadTime = 12;
	extraCurrentTime = 0;
	isAlive = true;
	explosionTimer = 30;

	// query texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	//calling sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	// when they go off screen, delete the bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionY() > SCREEN_HEIGHT)
		{
			// Cache the variable so delete later (leaker pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break; // delete bullet once per frame
		}
	}
	if (!isAlive) return;
	// move player
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = defaultSpeed;
	}

	// decrement timer extra
	if (extraCurrentTime > 0)
		extraCurrentTime--;

	//decrement the reload timer every frame
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 4 + width / 2, y - height / 2, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// after firing reset reload timer
		currentReloadTime = reloadTime;
		if (orbCounter != 0) // count null
		{
			for (int i = 0; i < orbCounter; i++) // counts
			{
				Bullet* bulletExtra = new Bullet(x + (rand() % width), y - height / 2, 0, -1, 10, Side::PLAYER_SIDE);
				bullets.push_back(bulletExtra);
				getScene()->addGameObject(bulletExtra);
				extraCurrentTime = extraReloadTime;
			}
		}
	}
}

void Player::draw()
{
	if (!isAlive)
	{
		if (explosionTimer > 0)
		{
			blit(explosionTexture, x, y);
			explosionTimer--;
		}
		return;
	}		
	blit(texture, x, y);
}

int Player::getPosX()
{
	return x;
}

int Player::getPosY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}

int Player::setOrbCount(int add)
{
	return orbCounter += add;
}
