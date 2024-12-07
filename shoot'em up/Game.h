#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Ennemy.h"
#include "Menu.h"
#include "Projectile.h"

class Game
{
public:
	enum GameState {
		MENU,
		OPTIONS,
		COMMANDS,
		EDITOR,
		PLAYING
	};
private:
	RenderWindow* window;
	VideoMode videoMode;
	Player* player;
	Font font;
	Text textScore;
	//fonctions
	int initSprite();
	void initPlayer();
	void initTexture();
	void initWindow();
	void initScore();
	void createEnnemy();
	void createProjectiles(float x, float y);

	//taille de l'écran
	int mapWidth = 1920;
	int mapHeight = 1080;

	//Texture de la map
	Sprite spriteMap;
	Texture texture;

	//vectors des entités 
	vector<Ennemy*> ennemies;
	vector<Projectile*> projectiles;

	int score;

	// Menu
	Menu mainMenu;
	GameState currentState;
public:
	Game();
	~Game();

	const bool windowIsOpen();
	void entityRender();
	void playerUpdate();
	void projectileUpdate();
	void ennemyUpdate();
	void projectileRender();
	void checkCollisions();
	void shoot();

	// Menu
	void handleMenuState();
	void handleMenu();

	void update();
	void render();

};

