#pragma once
#include <string>
#include "stdafx.h"

class Menu
{
private:
	Font font;
	Text playButton;
	Text optionsButton;
	Text editorButton;
	Text quitButton;
	RectangleShape playButtonRect;
	RectangleShape optionsButtonRect;
	RectangleShape editorButtonRect;
	RectangleShape quitButtonRect;
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

	int handleInput(RenderWindow& window);

	void render(RenderWindow& window);
	void renderOptions(RenderWindow& window);
	void setBackground(const string& backgroundImage);
	void handleMouseHover(const RenderWindow& window);
	int getSelectedIndex();
};

