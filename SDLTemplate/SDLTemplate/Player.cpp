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

	// query texture width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	//calling sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
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
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		// after firing reset reload timer
		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && extraCurrentTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet1 = new Bullet(x + width, y - 5 + height / 9, 1, 0, 10);
		Bullet* bullet2 = new Bullet(x + width, y - 4 + height, 1, 0, 10);
		bullets.push_back(bullet1);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet1);
		getScene()->addGameObject(bullet2);
		bullet1->start();
		bullet2->start();

		//reload timer resets
		extraCurrentTime = extraReloadTime;

	}

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
}

void Player::draw()
{
	blit(texture, x, y);
}
