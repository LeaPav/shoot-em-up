#include "Game.h"

int Game::initSprite()
{
	if (!this->texture.loadFromFile("test.png"));
	return -1;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnnemy()
{
	Ennemy* ennemy1 = new Ennemy();
	ennemy1->setPosition();
	ennemies.push_back(ennemy1);

	//Ennemy* ennemy2 = new Ennemy();

}

void Game::initTexture()
{
	this->spriteMap.setTexture(this->texture);
	this->spriteMap.setPosition(0, 0);
}

void Game::initWindow()
{
	this->videoMode.width = mapWidth;
	this->videoMode.height = mapHeight;
	this->window = new RenderWindow(this->videoMode, "StarWater");
	this->window->setFramerateLimit(60);
}

void Game::entityRender()
{
	this->player->render(*this->window);

	for (auto& ennemy : ennemies) {
		ennemy->render(*this->window);
	}
}

Game::Game()
{
	//this->initSprite();
	//this->initTexture();
	this->initWindow();
	this->initPlayer();
	this->initEnnemy();
}

Game::~Game()
{
	delete this->window;

}

const bool Game::windowIsOpen()
{
	return this->window->isOpen();
}

void Game::update()
{
	Event event;
	playerUpdate();
	while (this->window->pollEvent(event)) {
		if (event.type == Event::Closed) 
			this->window-> close();
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			this->window->close();
		}
	}
}

void Game::playerUpdate()
{
	this->player->playerUpdate();
	for (auto& ennemy : ennemies) {
		ennemy->update();
		if (ennemy->destroy()) {
			ennemies.clear();
		}
	}
}

void Game::render()
{
	this->window->clear();
	this->entityRender();
	this->window ->display();

}
