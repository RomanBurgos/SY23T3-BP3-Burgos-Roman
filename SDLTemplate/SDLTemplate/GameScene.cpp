#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player); // always do this to game objects
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	currentSpawnTime = 300;
	spawnTime = 300; // 5 secs

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (currentSpawnTime > 0)
		currentSpawnTime--;

	if (currentSpawnTime <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
			currentSpawnTime = spawnTime;
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
