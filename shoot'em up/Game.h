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
		GAMEOVER,
		PAUSE,
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
	void initGameOver();
	void createEnnemy();
	void createProjectiles(float x, float y);
	void createProjectilesEnnemy(float x, float y);

	//taille de l'écran
	int mapWidth = 1920;
	int mapHeight = 1080;

	//Texture de la map
	Sprite spriteMap;
	Texture texture;

	//Texture niveau 1
	Texture bas_Sens1;
	Texture bas_invers1;
	Texture bas_Sens2;
	Texture bas_invers2;
	Texture haut_sens1;
	Texture haut_invers1;
	Texture haut_sens2;
	Texture haut_invers2;


	Sprite basSens1;
	Sprite basInvers1;
	Sprite basSens2;
	Sprite basInvers2;
	Sprite hautSens1;
	Sprite hautInvers1;
	Sprite hautSens2;
	Sprite hautInvers2;

	//vectors des entités 
	vector<Ennemy*> ennemies;
	vector<Projectile*> projectilesPlayer;
	vector<Projectile*> projectilesEnnemy;

	int score;

	// Menu
	Menu mainMenu;
	Menu pauseMenu;
	GameState currentState;
	bool isPaused;

	//Game over
	Font fontOver;
	Text gameOverText;
	Text retryButton;
	Text mainMenuButton;
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
	void shootEnnemy();

	// Menu
	void handleMenuState(Event& event);
	void handleMenu();
	void handleMenuPause();
	void renderMenuPause();

	void update();
	void render();

	void fonduNiveau1();
	void renderNiveau1();

};

