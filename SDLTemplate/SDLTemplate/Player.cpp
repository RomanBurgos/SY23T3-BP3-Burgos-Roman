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
	x = 100;
	y = 100;
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
	explodeSound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	explodeSound->volume = 10;
}

void Player::update()
{
	// when they go off screen, delete the bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
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
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// after firing reset reload timer
		currentReloadTime = reloadTime;
	}
	// second bullet function
	if (app.keyboard[SDL_SCANCODE_G] && extraCurrentTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet1 = new Bullet(x + width, y - 5 + height / 9, 1, 0, 10, Side::PLAYER_SIDE);
		Bullet* bullet2 = new Bullet(x + width, y - 4 + height, 1, 0, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet1);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet1);
		getScene()->addGameObject(bullet2);

		//reload timer resets
		extraCurrentTime = extraReloadTime;
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
			SoundManager::playSound(explodeSound);
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
