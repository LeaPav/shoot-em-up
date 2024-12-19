#pragma once
#include <string>
#include "stdafx.h"

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
	Texture backgroundTexture;
	Texture optionsTexture;
	int indexButtonSelected;

	Clock mouseCooldownClock;
	const Time mouseCooldown = milliseconds(150);

	int initFont();
	int initBackground();
	void initButton();
	void initOptionsButton();
	void initCommandsButton();
	void initDifficultyButton();
	void initLevelButton();

	// rectangle choix niveau;

	Sprite spriteLevel1, spriteLevel2, spriteLevel3;
	Texture textureLevel1, textureLevel2, textureLevel3;

	RectangleShape level1Rect;
	RectangleShape level2Rect;
	RectangleShape level3Rect;

	int initLevel();
	
	Text level1;
	Text level2;
	Text level3;

public:
	Menu();

	int handleInputMainMenu(RenderWindow& window, const Event& event);
	int handleInputMenuOptions(RenderWindow& window, const Event& event);
	int handleInputDifficulty(RenderWindow& window, const Event& event);
	int handleInputLevel(RenderWindow& window, const Event& event);
	int handleInputPauseMenu(RenderWindow& window, const Event& event);

	void render(RenderWindow& window);
	void renderOptions(RenderWindow& window);
	void renderEditor(RenderWindow& window);
	void renderCommands(RenderWindow& window);
	void renderDifficulty(RenderWindow& window);
	void renderPauseMenu(RenderWindow& window);
	void renderLevel(RenderWindow& window);
	void renderSettingsPauseMenu(RenderWindow& window);
	void setBackground(const string& backgroundImage);
	void handleMouseHover(const RenderWindow& window);

	bool isCooldownActive();
	void resetCooldown();
};

