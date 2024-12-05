#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Ennemy.h"
class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Player* player;
	//fonctions
	int initSprite();
	void initPlayer();
	void initTexture();
	void initWindow();
	void createEnnemy();

	//taille de l'écran
	int mapWidth = 1920;
	int mapHeight = 1080;

	//Texture de la map
	Sprite spriteMap;
	Texture texture;

	//vectors des entités 
	vector<Ennemy*> ennemies;

public:
	Game();
	~Game();

	const bool windowIsOpen();
	void entityRender();
	void update();
	void playerUpdate();
	void render();

};

