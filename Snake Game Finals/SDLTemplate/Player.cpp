#include "Player.h"

Player::Player()
{
	width = 0;
	height = 0;
	speed = 32;
	moveDelay = 10;
	moveCounter = 0;
	directionX = speed;
	directionY = speed;
	alive = true;
	body.push_back({ 32, 32 });
	body.push_back({ 32 - width, 32 });
	body.push_back({ 32 - 2 * width, 32 });
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
	Mix_FreeChunk(sound);
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/death.ogg");
}

void Player::update()
{
	if (!alive) return;
	handleInput();

	moveCounter++;
	if (moveCounter >= moveDelay)
	{
		move();
		moveCounter = 0;
	}
	checkCollision();
}

void Player::draw()
{
	if (!alive) return;

	for (const auto& segment : body)
	{
		blit(texture, segment.x, segment.y);
	}
}

int Player::getX()
{
	return body[0].x;
}

int Player::getY()
{
	return body[0].y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

void Player::handleInput()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W] && directionY == 0)
	{
		directionX = 0;
		directionY = -speed;
	}
	if (keys[SDL_SCANCODE_S] && directionY == 0)
	{
		directionX = 0;
		directionY = speed;
	}
	if (keys[SDL_SCANCODE_A] && directionX == 0)
	{
		directionX = -speed;
		directionY = 0;
	}
	if (keys[SDL_SCANCODE_D] && directionX == 0)
	{
		directionX = speed;
		directionY = 0;
	}
}

bool Player::isAlive() const
{
	return alive;
}

void Player::grow()
{
	if (!body.empty())
	{
		body.push_back(body.back());
	}
}

void Player::move()
{
	for (size_t i = body.size() - 1; i > 0; --i)
	{
		body[i] = body[i - 1];
	}

	body[0].x += directionX;
	body[0].y += directionY;
}

void Player::checkCollision()
{
	if (body[0].x < 0 || body[0].x + width > SCREEN_WIDTH || body[0].y < 0 || body[0].y + height > SCREEN_HEIGHT)
	{
		alive = false; // if player hits the wall
		SoundManager::playSound(sound);
		return;
	}

	for (size_t i = 1; i < body.size(); ++i) // check collision on itself
	{
		if (body[0].x == body[i].x && body[0].y == body[i].y)
		{
			alive = false;
			SoundManager::playSound(sound);
			return;
		}
	}
}

void Player::reset()
{
	body.clear();
	body.push_back({ 360, 360 });
	body.push_back({ 360 - width, 360 });
	body.push_back({ 360 - 2 * width, 360 });
	directionX = speed;
	directionY = 0;
	alive = true;
}
