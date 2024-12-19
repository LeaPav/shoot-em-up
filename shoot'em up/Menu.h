#pragma once
#include <string>
#include "stdafx.h"
#include "Player.h"
#include "Boss.h"

class Menu
{
private:
	
	// button mainMenu
	Font fontMainMenu;
	Font fontPauseMenu;
	Text playButton;
	Text optionsButton;
	Text editorButton;
	Text quitButton;
	
	RectangleShape playButtonRect;
	RectangleShape optionsButtonRect;
	RectangleShape editorButtonRect;
	RectangleShape quitButtonRect;

	// button Options
	RectangleShape commandsButtonRect;
	RectangleShape difficultyButtonRect;
	RectangleShape settingsButtonRect;
	RectangleShape returnButtonRect;
	RectangleShape returnMenuOptionsButtonRect;
	
	Text commandsButton;
	Text difficultyButton;
	Text settingsButton;
	Text returnButton;
	Text returnMenuOptionsButton;

	// button difficulté
	RectangleShape easyButtonRect;
	RectangleShape normalButtonRect;
	RectangleShape hardCoreRect;

	Text easyButton;
	Text hardButton;
	Text hardCoreButton;
	// buton paramètres

	// button menu pause;
	Text resumeButton;
	Text settingsPauseButton;
	Text returnToMainMenuButton;
	Text pause;

	Sprite background, optionsBackground;
	Sprite spritePlayer, spriteEnnemy1, spriteEnnemy2, spriteBoss;
	Sprite ennemy1Groupe2, ennemy2Groupe2, ennemy3Groupe2, ennemy4Groupe2, 
		ennemy5Groupe2, ennemy6Groupe2, ennemy7Groupe2, ennemy8Groupe2;
	Sprite ennemy1Groupe1, ennemy2Groupe1, ennemy3Groupe1, ennemy4Groupe1, ennemy5Groupe1, 
		ennemy6Groupe1, ennemy7Groupe1, ennemy8Groupe1;
	Texture player, ennemy1, ennemy2, boss;
	Texture backgroundTexture;
	Texture optionsTexture;
	int indexButtonSelected;

	Clock mouseCooldownClock;
	const Time mouseCooldown = milliseconds(150);

	int initFont();
	int initBackground(); 
	void initSpritePlayer();
	void initSpriteEnnemies();
	void initSpriteBoss();
	void initTextureButton();
	void initButton();
	void initOptionsButton();
	void initEditorButton();
	void initCommandsButton();
	void initDifficultyButton();
	void initLevelButton();
	void initSoundsButton();

	// rectangle choix niveau;

	Sprite spriteLevel1, spriteLevel2;
	Texture textureLevel1, textureLevel2;
	Text dlcLevel2;
	RectangleShape level1Rect;
	RectangleShape level2Rect;
	RectangleShape level3Rect;
	

	// Bouton editeur
	RectangleShape playerHealthPlus1, playerHealthPlus2;
	RectangleShape playerHealthMin1, playerHealthMin2;
	RectangleShape ennemyHealthPlus1, ennemyHealthPlus2, ennemyHealthPlus3;
	RectangleShape ennemyHealthMin1, ennemyHealthMin2, ennemyHealthMin3;

	RectangleShape activateBossRect;
	RectangleShape bossHpPlus;
	RectangleShape bossHpMin;
	Text renderBossHp;
	Text activateBossButton;
	bool bossActivate = false;
	Text lifePlayer, TextRenderLifePlayer;
	Text speedPlayer, TextRenderSpeedPlayer;

	Text lifeEnnemy1, TextRenderLifeEnemy1;
	Text lifeEnnemy2, TextRenderLifeEnemy2;
	Text speedEnnemy;
	
	Texture playerButtonRight, playerButtonLeft;
	int initLevel1();
	int initLevel2();
	
	Text level1;
	Text level2;
	Text level3;
	Player player1;

	//bouton pour le son
	RectangleShape MonterMusic, MonterSon;
	RectangleShape BaisserMusic, BaisserSon;
	Text music, son;
	Text renderMusic, renderSon;

public:
	Menu();
	void updateEditorTexts(Player* player, int newPvAggressif, int newPvPassif, float speed, Boss* boss);
	void updateSettingsTexts(int bruitage, int musique);
	int handleInputMainMenu(RenderWindow& window, const Event& event);
	int handleInputMenuOptions(RenderWindow& window, const Event& event);
	int handleInputDifficulty(RenderWindow& window, const Event& event);
	int handleInputEditor(RenderWindow& window, const Event& event);
	int handleInputLevel(RenderWindow& window, const Event& event);
	int handleInputPauseMenu(RenderWindow& window, const Event& event);
	int handleInputSettingsMenu(RenderWindow& window, const Event& event);

	void render(RenderWindow& window);
	void renderOptions(RenderWindow& window);
	void renderEditor(RenderWindow& window);
	void renderCommands(RenderWindow& window);
	void renderDifficulty(RenderWindow& window);
	void renderPauseMenu(RenderWindow& window);
	void renderLevel(RenderWindow& window);
	void renderSettingsMenu(RenderWindow& window);
	void renderSettingsPauseMenu(RenderWindow& window);
	void setBackground(const string& backgroundImage);
	void handleMouseHover(const RenderWindow& window);

	bool isCooldownActive();
	void resetCooldown();
};

