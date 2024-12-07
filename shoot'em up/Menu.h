#pragma once
#include <string>
#include "stdafx.h"

class Menu
{
public:

private:
	
	// button mainMenu
	Font font;
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
	
	Text commandsButton;
	Text difficultyButton;
	Text settingsButton;

	Sprite background;
	Sprite optionsBackground;
	Texture backgroundTexture;
	Texture optionsTexture;
	int indexButtonSelected;


public:
	Menu();
	int initFont();
	int initBackground();
	void initButton();
	void initOptionsButton();

	int handleInputMainMenu(RenderWindow& window);
	int handleInputMenuOptions(RenderWindow& window);

	void render(RenderWindow& window);
	void renderOptions(RenderWindow& window);
	void renderEditor(RenderWindow& window);
	void renderCommands(RenderWindow& window);
	void setBackground(const string& backgroundImage);
	void handleMouseHover(const RenderWindow& window);
	int getSelectedIndex();
};

