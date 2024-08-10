#include "GameScene.h"

GameScene::GameScene() : player(new Player()), score(0), highScore(0)
{
	// Register and add game objects on constructor
	addGameObject(player);

	soundFeed = SoundManager::loadSound("sound/feed.ogg");
}

GameScene::~GameScene()
{
	delete player;
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
	//checkCollisions();
	updateScore();
	//spawnFoodLogic();
	//foodCollisionLogic();
}

void GameScene::resetGame()
{
	player->reset();
	//spawnFood();
	score = 0;
}

//void GameScene::spawnFood()
//{
//	int x = (rand() % (SCREEN_WIDTH / 10)) * 10;
//	int y = (rand() % (SCREEN_HEIGHT / 10)) * 10;
//	food->setPosition(x, y);
//	this->addGameObject(food);
//}

//void GameScene::checkCollisions()
//{
//	if (checkCollision(
//		player->getX(), player->getY(), player->getWidth(), player->getHeight(),
//		food->getPosX(), food->getPosY(), food->getWidth(), food->getHeight()))
//	{
//		player->grow();
//		spawnFood();
//		score += 1;
//		SoundManager::playSound(soundFeed);
//	}
//
//	if (!player->isAlive())
//	{
//		if (score > highScore)
//		{
//			highScore = score;
//		}
//	}
//}

void GameScene::updateScore()
{
	drawText(80, 5, 255, 255, 255, TEXT_CENTER, "SCORE: %d", score);
	drawText(360, 5, 255, 255, 255, TEXT_CENTER, "HIGH SCORE: %d", highScore);

	if (!player->isAlive())
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, 255, 255, 255, TEXT_CENTER, "PRESS 'SPACE' TO RESTART OR 'Q' TO QUIT");
	}
}

void GameScene::spawnFoodLogic()
{
}

void GameScene::foodCollisionLogic()
{
}

void GameScene::spawnFood()
{
}

void GameScene::despawnFood(Food* food)
{
}

void GameScene::despawnAllFood()
{
}

//void GameScene::spawnFoodLogic()
//{
//	if (currentSpawnTime > 0)
//		currentSpawnTime--;
//
//	if (currentSpawnTime <= 0)
//	{
//		spawnFood();
//		currentSpawnTime = spawnTime;
//	}
//}
//
//void GameScene::foodCollisionLogic()
//{
//	// check collisions
//	for (int i = 0; i < objects.size(); i++)
//	{
//		// cast Food
//		Food* selFood = dynamic_cast<Food*>(objects[i]);
//		// null check
//		if (selFood != NULL)
//		{
//			int collision = checkCollision(
//				player->getX(), player->getY(), player->getWidth(), player->getHeight(),
//				selFood->getPosX(), selFood->getPosY(), selFood->getWidth(), selFood->getHeight());
//			if (collision == 1) // if collided
//			{
//				SoundManager::playSound(soundFeed);
//				player->grow(); // grow the player
//				despawnFood(selFood);
//				score += 1;
//				break;
//			}
//		}
//	}
//	if (!player->isAlive() && score > highScore)
//	{
//		highScore = score;
//	}
//}
//
//void GameScene::despawnFood(Food* food)
//{
//	int index = -1;
//	for (int i = 0; i < spawnedFood.size(); i++) // linear search
//	{
//		if (food == spawnedFood[i]) // if the pointer match
//		{
//			index = i;
//			break;
//		}
//	}
//
//	if (index != -1) // if match is found
//	{
//		spawnedFood.erase(spawnedFood.begin() + index);
//		delete food;
//	}
//}
//
//void GameScene::despawnAllFood()
//{
//	for (int i = 0; i < spawnedFood.size(); i++)
//	{
//		delete spawnedFood[i];
//	}
//	spawnedFood.clear();
//}
