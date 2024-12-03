#pragma once
#include "stdafx.h"

class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	//fonctions
	int initSprite();
	void initTexture();
	void initWindow();
	//taille de l'écran
	int mapWidth = 1920;
	int mapHeight = 1080;
	Sprite spriteMap;
	Texture texture;
public:
	Game();
	~Game();

	const bool windowIsOpen();
	void update();
	void render();

};

