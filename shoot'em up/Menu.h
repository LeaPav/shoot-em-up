#pragma once
#include <string>
#include "stdafx.h"

class Menu
{
public:

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

	// buton paramètres

	// button menu pause;
	Text resumeButton;
	Text settingsPauseButton;
	Text returnToMainMenuButton;
	Text pause;

	Sprite background;
	Sprite optionsBackground;
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
public:
	Menu();

	int handleInputMainMenu(RenderWindow& window, const Event& event);
	int handleInputMenuOptions(RenderWindow& window, const Event& event);
	int handleInputPauseMenu(RenderWindow& window, const Event& event);
	int handleInputSettingsMenu(RenderWindow& window, const Event& event);

	void render(RenderWindow& window);
	void renderOptions(RenderWindow& window);
	void renderEditor(RenderWindow& window);
	void renderCommands(RenderWindow& window);
	void renderPauseMenu(RenderWindow& window);
	void renderSettingsMenu(RenderWindow& window);
	void renderSettingsPauseMenu(RenderWindow& window);
	void setBackground(const string& backgroundImage);
	void handleMouseHover(const RenderWindow& window);

	bool isCooldownActive();
	void resetCooldown();
};

