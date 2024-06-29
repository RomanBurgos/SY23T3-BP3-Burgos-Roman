#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player); // always do this to game objects
	points = 0;

	//calling sound
	explosionSound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	bgTexture = loadTexture("gfx/background.png");
	Scene::start();
	// Initialize any scene logic here
	explosion = loadTexture("gfx/explosion.png");
	initFonts();
	currentSpawnTime = 300;
	spawnTime = 300; // 5 secs
	explosionTimer = 60;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	drawBackground(bgTexture);
	Scene::draw();
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);
	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	Scene::update();
	spawnLogic();
	collisionLogic();
}

void GameScene::spawnLogic()
{
	if (currentSpawnTime > 0)
		currentSpawnTime--;

	if (currentSpawnTime <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}
		currentSpawnTime = spawnTime;
	}
}

void GameScene::collisionLogic()
{
	// check collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);
		// null check
		if (bullet != NULL)
		{
			// Check which side the bullet on
			if (bullet->getSide() == Side::ENEMY_SIDE) // If the enemy bullet collides with player
			{
				int collision = checkCollision(
					player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());
				if (collision == 1) // if collided
				{
					player->doDeath();
					break;
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE) // from the player, check against all enemy
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPosX(), currentEnemy->getPosY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());
					if (collision == 1)
					{
						despawn(currentEnemy);
						points++; // increment points
						// only despawn 1 at a time
						break;
					}
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);
	enemy->setPosition(1300, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
	currentSpawnTime = spawnTime;
}

void GameScene::despawn(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++) // linear search
	{
		if (enemy == spawnedEnemies[i]) // if the pointer match
		{
			SoundManager::playSound(explosionSound);
			if (explosionTimer > 0)
			{
				blit(explosion, enemy->getPosX(), enemy->getPosY());
				explosionTimer--;
			}
			index = i;
			break;
		}
	}

	if (index != -1) // if match is found
	{
		/*explosions.push_back({ enemy->getPosX(), enemy->getPosY(), explosionTimer });*/
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::drawBackground(SDL_Texture* texture)
{
	SDL_Rect desRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(app.renderer, texture, NULL, &desRect);
}