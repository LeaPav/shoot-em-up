#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Projectiles.h"


class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Player* player;
	JoueurProjo* projoJ;
	//fonctions
	int initSprite();
	void initPlayer();
	void initTexture();
	void initWindow();

	//taille de l'écran
	int mapWidth = 1920;
	int mapHeight = 1080;

	//Texture de la map
	Sprite spriteMap;
	Texture texture;

public:
	Game();
	~Game();

	const bool windowIsOpen();
	void playerRender();
	void update();
	void render();

};

