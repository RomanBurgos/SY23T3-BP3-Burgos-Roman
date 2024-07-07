#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player); // always do this to game objects
	points = 0;

	spawnedBoss = nullptr;
	bossSpawned = false;

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
	// orb timer
	pSpawnTimer = 1800;
	pCurrentTimer = 1800;
	pExpireTimer = 600;
	pCurrentExpireTimer = 600;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	int width;
	int height;
	blitScale(bgTexture, 0, 0, &width, &height, 2);
	Scene::draw();
	drawText(110, 840, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);
	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER");
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 255, 255, 255, TEXT_CENTER, "PRESS SPACE TO EXIT");
	}
}

void GameScene::update()
{
	Scene::update();
	collisionLogic();
	orbCollisionLogic();
	if (points >= 100 && !bossSpawned)
	{
		bossSpawned = true;
		despawnAllEnemies();
		spawnedBoss = new Boss();
		this->addGameObject(spawnedBoss);
		spawnedBoss->setPlayerTarget(player);
		spawnedBoss->setPosition(314, 150);
;	}

	if (bossSpawned)
	{
		if (!spawnedBoss->getIsAlive())
		{
			despawnBoss();
			bossSpawned = false;
			currentSpawnTime = spawnTime;
		}
	}
	else
	{
		spawnLogic();
		spawnOrbLogic();
	}
}

void GameScene::spawnLogic()
{
	if (bossSpawned) return; // if boss is alive then dont spawn

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
			else if (bullet->getSide() == Side::PLAYER_SIDE && bossSpawned && spawnedBoss->getIsAlive())
			{
				int collision = checkCollision(
					spawnedBoss->getPosX(), spawnedBoss->getPosY(), spawnedBoss->getWidth(), spawnedBoss->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());
				if (collision == 1)
				{
					spawnedBoss->damage(1); // do dmg
					points += 1;
					if (!spawnedBoss->getIsAlive())
					{
						points += 10;
						despawnBoss();
					}
				}
				break;
			}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);
	enemy->setPosition(100 + (rand() % 400), 100);
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
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::offScreenEnemies(Enemy* enemy)
{
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		enemy = spawnedEnemies[i];
		if (enemy->getPosX() > SCREEN_WIDTH + 300 || enemy->getPosX() < -300 ||
			enemy->getPosY() > SCREEN_HEIGHT + 300 || enemy->getPosY() < -300)
		{
			despawn(enemy);
		}
	}
}

void GameScene::despawnAllEnemies()
{
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		delete spawnedEnemies[i];
	}
	spawnedEnemies.clear();
}

void GameScene::spawnOrbLogic()
{
	if (pCurrentTimer > 0)
		pCurrentTimer--;

	if (pCurrentTimer <= 0)
	{
		spawnOrb();
		pCurrentTimer = pSpawnTimer;
		pCurrentExpireTimer = pExpireTimer;
	}

	if (pCurrentExpireTimer > 0) // expire timer
		pCurrentExpireTimer--;
	if (pCurrentExpireTimer <= 0) // despawn
	{
		despawnOrb(powers);
	}
}

void GameScene::orbCollisionLogic()
{
	// check collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast powerOrb
		PowerOrbs* orb = dynamic_cast<PowerOrbs*>(objects[i]);
		// null check
		if (orb != NULL)
		{
			int collision = checkCollision(
				player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight(),
				orb->getPosX(), orb->getPosY(), orb->getWidth(), orb->getHeight());
			if (collision == 1) // if collided
			{
				player->setOrbCount(1); // add
				despawnOrb(orb);
				break;
			}
		}
	}
}

void GameScene::spawnOrb() // new orb
{
	powers = new PowerOrbs();
	this->addGameObject(powers);
	powers->setPosition(1 + (rand() % 720), 100 + (rand() % 540));
}

void GameScene::despawnOrb(PowerOrbs* orb)
{
	delete orb;
}

void GameScene::despawnBoss()
{
	if (spawnedBoss != nullptr)
	{
		delete spawnedBoss;
		spawnedBoss = nullptr;
		bossSpawned = false;
	}
}