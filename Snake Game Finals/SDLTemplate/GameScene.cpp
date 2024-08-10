#include "GameScene.h"

GameScene::GameScene() : player(new Player()), score(0), highScore(0)
{
	// Register and add game objects on constructor
	addGameObject(player);
	spawnTime = 300;
	currentSpawnTime = 300;

	soundFeed = SoundManager::loadSound("sound/feed.ogg");
}

GameScene::~GameScene()
{
	delete player;
	despawnAllFood();
}

void GameScene::start()
{
	bgTexture = loadTexture("gfx/background.png");
	initFonts();
	Scene::start();
	// Initialize any scene logic here
	resetGame();
}

void GameScene::draw()
{
	blit(bgTexture, 0, 0);
	Scene::draw();
	updateScore();
}

void GameScene::update()
{
	if (!player->isAlive())
	{
		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			resetGame();
		}
		else if (app.keyboard[SDL_SCANCODE_Q])
		{
			exit(0);
		}
		return;
	}
	Scene::update();
	updateScore();
	foodCollisionLogic();
	spawnFoodLogic();

}

void GameScene::resetGame()
{
	player->reset();
	score = 0;
	despawnAllFood();
}


void GameScene::updateScore()
{
	drawText(80, 5, 255, 255, 255, TEXT_CENTER, "SCORE: %d", score);
	drawText(360, 5, 255, 255, 255, TEXT_CENTER, "HIGH SCORE: %d", highScore);
	if (!player->isAlive())
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, 255, 255, 255, TEXT_CENTER, "PRESS 'SPACE' TO RESTART OR 'Q' TO QUIT");
		if (highScore < score)
		{
			highScore = score;
		}
	}
}

void GameScene::spawnFoodLogic()
{
	if (currentSpawnTime > 0)
		currentSpawnTime--;

	if (currentSpawnTime <= 0)
	{
		spawnFood();
		currentSpawnTime = spawnTime;
	}
}

void GameScene::foodCollisionLogic()
{
	// check collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast powerOrb
		Food* selFood = dynamic_cast<Food*>(objects[i]);
		// null check
		if (selFood != NULL)
		{
			int collision = checkCollision(
				player->getX(), player->getY(), player->getWidth(), player->getHeight(),
				selFood->getPosX(), selFood->getPosY(), selFood->getWidth(), selFood->getHeight());
			if (collision == 1) // if collided
			{
				SoundManager::playSound(soundFeed);
				score += 1; // add
				despawnFood(selFood);
				player->grow();
				break;
			}
		}
	}
}

void GameScene::spawnFood()
{
	Food* food = new Food();
	this->addGameObject(food);
	food->setPosition(50 + (rand() % 600), 50 + (rand() % 600));
	spawnedFood.push_back(food);
}

void GameScene::despawnFood(Food* food)
{
	int index = -1;
	for (int i = 0; i < spawnedFood.size(); i++) // linear search
	{
		if (food == spawnedFood[i]) // if the pointer match
		{
			index = i;
			break;
		}
	}

	if (index != -1) // if match is found
	{
		spawnedFood.erase(spawnedFood.begin() + index);
		delete food;
	}
}

void GameScene::despawnAllFood()
{
	for (int i = 0; i < spawnedFood.size(); i++)
	{
		delete spawnedFood[i];
	}
	spawnedFood.clear();
}
