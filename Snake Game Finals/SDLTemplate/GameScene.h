#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Food.h"
#include "text.h"
#include "SoundManager.h"

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
	Mix_Chunk* soundFeed;
	Player* player;
	int score;
	int highScore;
	void resetGame();
	void updateScore();

	// FOOD AND LOGIC
	float spawnTime;
	float currentSpawnTime;
	std::vector<Food*> spawnedFood;
	void spawnFoodLogic();
	void foodCollisionLogic();
	void spawnFood();
	void despawnFood(Food* food);
	void despawnAllFood();
};

