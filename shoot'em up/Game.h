#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Ennemy.h"
#include "Menu.h"
#include "GameOver.h"
#include "Win.h"
#include "Boss.h"
#include "Bonus.h"
#include "Projectile.h"

class Game
{
public:
	enum GameState {
		MENU,
		OPTIONS,
		COMMANDS,
		EDITOR,
		LEVEL,
		DIFFICULTY,
		GAMEOVER,
		WIN,
		PAUSE,
		PLAYING
	};
private:
	RenderWindow* window;
	VideoMode videoMode;
	Player* player;
	Boss* boss;
	Font font;
	Text textScore;
	//fonctions
	int initSprite();
	void initPlayer();
	void initBoss();
	void initTexture();
	void initWindow();
	void initScore();
	void createEnnemy();
	void createProjectilesPlayer(float x, float y);
	void createProjectilesPlayerDiag(float x, float y, float xDiag, float yDiag);
	void createProjectilesEnnemy(float x, float y);
	void createProjectilesBoss(float x, float y);

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
	vector<Projectile*> projectilesBoss;

	//joueur
	int fireRate = 15;

	//Ennemi
	int pv = 2;
	int newPvPassif = 2;
	int newPvAggressif = 2;

	int score;
	int scoreBonus;
	int scoreBoss;
	int spawnBoss;
	int* scoreBossTest;
	int killStreak;

	// Menu
	Menu mainMenu;
	Menu pauseMenu;
	GameState currentState;
	bool isPaused;

	//Game over
	GameOver gameOver;
	
	Win win;
	//Spawn du boss
	bool bossSpawn;

	//Bonus

	vector<Bonus> bonus;
	vector<Vector2f> bonusZones;
	vector<bool> bonusActive;
	Texture bonusTexture[9];
	const int totalBonus = 9;
	bool vagueActif;
	int spawnBonusPhase;
	int bonusKit = 2;
	void initBonus();
	void initZones();
	void initBonusState();
	int bonusShotCount = 0;
	int bonusShieldDef = 5;
	int bonusShieldOff = 5;
	float bonusSpeed = 5.f;

	bool canHaveDamaged = true;

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
	bool checkCollisionsBonus(Player* player, Ennemy* ennemy);
	void shoot();
	void shootEnnemy();
	void shootingBoss();

	// Menu
	void handleMenuState(Event& event);
	void handleMenu();
	void renderMenuPause();

	//Game over
	void renderGameOver();
	void renderWin();
	//boss
	void renderBoss();
	void updateBoss();

	void update();
	void render();

	void fonduNiveau1();
	void renderNiveau1();
	//score

	void resetGame();
	
	Clock tpsTouch;
	Clock timeCheckCollision;
  
	//bonus

	void spawnBonus();
	void renderBonusZones();
	void updateBonusZones();
	void resetBonus();
	void activateBonus(Bonus::AllBonus bonusType);
	void deactivateBonus(Bonus::AllBonus bonusType);

	//Difficulté

	void easyLevel();
	void intermediaireLevel();
	void hardLevel();

	// Editeur
	void changeHealthPlayerPlus(int hp);
	void changeHealthPlayerMin(int hp);

	void changeSpeedPlayerPlus(int speed);
	void changeSpeedPlayerMin(int speed);

	void changeHealthEnnemy1Plus(int hp);
	void changeHealthEnnemy1Min(int hp);

	void changeHealthEnnemy2Plus(int hp);
	void changeSpeedEnnemyPlus(int speed);
	void changeSpeedEnnemyMin(int speed);
	void changeHealthEnnemy2Min(int hp);

};

