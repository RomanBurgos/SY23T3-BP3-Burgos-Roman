#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;

	// enemy spawner logic	
	float spawnTime;
	float currentSpawnTime;
	std::vector<Enemy*> spawnedEnemies;

	void spawn();
};

