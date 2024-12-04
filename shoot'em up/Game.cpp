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

void Game::initTexture()
{
	this->spriteMap.setTexture(this->texture);
	this->spriteMap.setPosition(0, 0);
}

void Game::initWindow()
{
	this->videoMode.width = mapWidth;
	this->videoMode.height = mapHeight;
	this->window = new RenderWindow(this->videoMode, "StarWater", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::playerRender()
{
	this->player->render(*this->window);
}

Game::Game()
{
	//this->initSprite();
	//this->initTexture();
	this->initWindow();
	this->initPlayer();
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
	while (this->window->pollEvent(event)) {
		if (event.type == Event::Closed)
			this->window-> close();
	}
}

void Game::render()
{
	this->window->clear();
	this->playerRender();
	this->window ->display();

}
