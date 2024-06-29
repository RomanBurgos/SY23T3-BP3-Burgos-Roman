#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"

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

	void drawBackground(SDL_Texture* texture);
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

	// explosion logic
	SDL_Texture* explosion;
	Mix_Chunk* explosionSound;
	float explosionTimer;
	int points;
};

