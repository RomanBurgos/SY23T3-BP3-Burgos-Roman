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
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
}