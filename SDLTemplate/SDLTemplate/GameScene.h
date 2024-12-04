#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "PowerOrbs.h"
#include "Boss.h"

struct Explosion
{
	int x, y;
	float timer;
};

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	SDL_Texture* bgTexture;
	Player* player;

	// enemy spawner logic	
	float spawnTime;
	float currentSpawnTime;
	std::vector<Enemy*> spawnedEnemies;

	void spawnLogic();
	void collisionLogic();
	void spawn();
	void despawn(Enemy* enemy);
	void offScreenEnemies(Enemy* enemy);
	void despawnAllEnemies();

	// explosion logic
	SDL_Texture* explosion;
	Mix_Chunk* explosionSound;
	float explosionTimer;
	int points;

	// power up logic
	float pSpawnTimer;
	float pCurrentTimer;
	float pExpireTimer;
	float pCurrentExpireTimer;
	PowerOrbs* powers;
	void spawnOrbLogic();
	void orbCollisionLogic();
	void spawnOrb();
	void despawnOrb(PowerOrbs* orb);

	// boss logic
	Boss* spawnedBoss;
	bool bossSpawned;
	void despawnBoss();
};

