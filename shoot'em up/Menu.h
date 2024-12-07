#pragma once
#include <string>
#include "stdafx.h"

class Menu
{
private:
	Font font;
	vector<Text> buttons;
	Text playButton;
	Text optionsButton;
	Text editorButton;
	Text quitButton;
	Sprite background;
	Texture backgroundTexture;
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

	int getSelectedIndex();
};

