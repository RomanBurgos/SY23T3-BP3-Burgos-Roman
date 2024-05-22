#include "Player.h"

void Player::start()
{
	// load texture
	texture = loadTexture("gfx/player.png");

	// initialized variables
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	defaultSpeed = speed;
	// query texture width height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
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
}

void Player::draw()
{
	blit(texture, x, y);
}
